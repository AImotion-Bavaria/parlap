#include <iostream>
#include <vector>
#include <limits>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <algorithm>

#include<string>
#include <cstring>
#include<fstream>
#include<ostream>

#include <cassert>
#include <stack>
#include <mutex>
#include <thread>
#include <list>
#include <future>

#include "include/thread-pool.hpp"

using namespace std;

#define inf numeric_limits<int>::max()
#define VERBOSE false

#define NUM_THREADS 4 
vector<int> test_cases = {2500, 5000, 7500, 10000, 12500, 15000, 17500, 20000};


// Init global variables
vector<vector<int>> cost; //cost matrix
int n;// number of jobs and workers

vector<int> ass_row; //row assignment
vector<int> ass_col; //col assignment
vector<bool> cov_row; //row cover
vector<bool> cov_col; //col cover

vector<double> dual_row; //dual variable row
vector<double> dual_col; //dual variable col
vector<double> slack; //column slack variable

vector<int> prv_row; //row predecessor
vector<int> prv_col; //col predecessor
vector<int> suc_row; //row successor
vector<int> suc_col; //col successor

vector<bool> active;
vector<bool> visited;
vector<bool> reverse_v;
vector<bool> augment;

vector<int> f_in;
vector<int> f_rev;
vector<int> f_aug;

double theta = inf;

// Init ThreadPool
vector<int> results(NUM_THREADS, 0);
ThreadPool thpool_(NUM_THREADS);

int div_ceil(int x, int y) {
    return x / y + (x % y > 0);
}

void init_dual_row(int thread_id){
	const int chunk = div_ceil(n, NUM_THREADS); // chunk size
	const int lower = thread_id * chunk; // lower task id
	const int upper = min(lower + chunk, n); // upper task id
	
	// Init dual row
	for (int i = lower; i < upper; i++){
        double temp = inf;
		// Find minimum value of row i
        for (int j = 0; j < n; j++){
            temp = min(temp, double(cost[i][j]));
        }
        dual_row[i] = temp;
    }
}

void init_dual_col(int thread_id){
	const int chunk = div_ceil(n, NUM_THREADS); // chunk size
	const int lower = thread_id * chunk; // lower task id
	const int upper = min(lower + chunk, n); // upper task id
	
	// Init dual col
	for (int j = lower; j < upper; j++){
        double temp = inf;
		// Find minimum value of col j
        for (int i = 0; i < n; i++){
            temp = min(temp, cost[i][j] - dual_row[i]);
        }
        dual_col[j] = temp;
    }
}

void init_potentials_parallel(){	
	// Schedule initialization of dual row
	for (int i=0; i < NUM_THREADS; i++){
		thpool_.schedule([i]{
            init_dual_row(i);
        }, i);
	}		
	for (int i=0; i < NUM_THREADS; i++){
		thpool_.wait(i);
	}
	
	// Schedule initialization of dual col
	for (int i=0; i < NUM_THREADS; i++){
		thpool_.schedule([i]{
            init_dual_col(i);
        }, i);
	}
	for (int i=0; i < NUM_THREADS; i++){
		thpool_.wait(i);
	}

}

int optimality_check(){
    // Init variables
    int match_count = 0;
	// Calculate the number of assigned resources
    for (int i=0; i<n; i++){
        if (ass_row[i] != -1){
            cov_row[i] = 1;
            match_count += 1;
        }
    }

	return match_count;
}

void reset_arrays(int thread_id){
	const int chunk = div_ceil(n, NUM_THREADS); // chunk size
	const int lower = thread_id * chunk; // lower task id
	const int upper = min(lower + chunk, n); // upper task id
	
	// Reset arrays before new augmenting path search
	for (int i=lower; i<upper; i++){
		cov_row[i] = 0;
        cov_col[i] = 0;  
        prv_row[i] = -1;
        prv_col[i] = -1;
        slack[i] = inf;
        suc_row[i] = -1;
        suc_col[i] = -1;
    }
}

void forward_bfs(int thread_id){
    const int chunk = div_ceil(n, NUM_THREADS); // chunk size
	const int lower = thread_id * chunk; // lower task id
	const int upper = min(lower + chunk, n); // upper task id
	
	// Breadth-first search that produces vertex-disjoint trees
	for (int j=lower; j<upper; j++){
		if(cov_col[j] == 0){
			// Loop over frontier
			for(size_t x=0; x<f_in.size(); x++){ 
				// Index of active row
				int i = f_in[x];
				double comp = cost[i][j] - dual_row[i] - dual_col[j];
				// Check if new slack is smaller than current slack of column j
				if(slack[j] > comp){
					// Update minimum slack value of column j
                    slack[j] = comp;
					// Row gets safed as predessecor to j
                    prv_col[j] = i;
                }
				// Get row that is assigned to j
                int i_new = ass_col[j];
                if (slack[j] == 0){
					// Check if i_new is unassigned
                    if (i_new != -1){
                        prv_row[i_new] = j;
                        cov_row[i_new] = 0;
                        cov_col[j] = 1; 
						// Mark i_new as active for next forward_bfs
                        if (!active[i_new]){
                            active[i_new] = true;
                        }
                    }
                    else{
						// Mark j as reverse
                        reverse_v[j] = true;
                    }
                } 
        	}
        }
    }
}

void reverse_bfs(int thread_id){
    const int chunk = div_ceil(f_rev.size(), NUM_THREADS); // chunk size
	const int lower = thread_id * chunk; // lower task id
	const int upper = min(lower + chunk, (int)f_rev.size()); // upper task id
	
	// Reverse pass to identify alternating, vertex-disjoint paths by traversing the trees generated by the forward_bfs
	for (int x=lower; x < upper; x++){
        int j = f_rev[x];
        int r_cur = -1;
        int c_cur = j;
		
		// Traverse tree stored in predecessor vectors
        while (c_cur != -1){
            suc_col[c_cur] = r_cur;
            r_cur = prv_col[c_cur];
            suc_row[r_cur] = c_cur;
            c_cur = prv_row[r_cur];
        }
		// Mark r_cur for augment pass
        augment[r_cur] = true;
    }
}

void augment_pass(int thread_id){
	const int chunk = div_ceil(f_aug.size(), NUM_THREADS); // chunk size
	const int lower = thread_id * chunk; // lower task id
	const int upper = min(lower + chunk, (int)f_aug.size()); // upper task id
	
	// Augment pass to augment the assignment
    for (int x=lower; x < upper; x++){
        int i = f_aug[x];
        int r_cur = i;
        int c_cur = -1;
		// Traverse tree stored in successor vectors
        while (r_cur != -1){
            c_cur = suc_row[r_cur];
            ass_row[r_cur] = c_cur;
            ass_col[c_cur] = r_cur;
            r_cur = suc_col[c_cur];
        }
    }
}

void update_pass(int thread_id){
	const int chunk = div_ceil(n, NUM_THREADS); // chunk size
	const int lower = thread_id * chunk; // lower task id
	const int upper = min(lower + chunk, n); // upper task id
	
	// Update dual variables and slack
	for(int k=lower; k<upper; k++){
        if (cov_row[k] == 0){
            dual_row[k] = dual_row[k] + theta/2;
        }
        else{
            dual_row[k] = dual_row[k] - theta/2;
        }
        if (cov_col[k] == 0){
            dual_col[k] = dual_col[k] + theta/2;
        }
        else{
            dual_col[k] = dual_col[k] - theta/2;
        }
        if (slack[k] > 0){
            slack[k] = slack[k] - theta;
			// Mark predecessor rows with zero slack as active
            if (slack[k] == 0){
                active[prv_col[k]] = true;
            }
        }
    }
}

bool augmenting_path_search(){
    bool check_flag = false;
	
	// Set unassigend rows to active and assigned rows to inactive
    for (int i=0; i<n; i++){
		visited[i] = false;
		reverse_v[i] = false;
		augment[i] = false;
		
        if (ass_row[i] == -1||active[i]){
            active[i] = true;
        }
        else{
            active[i] = false;
        }
    }

	// Repeat forward_bfs until there are no more active rows
    while (true){
		// Init frontier for forward_bfs
        f_in.clear();
        int active_count = 0;
        for (int i=0; i<n; i++){
			if (visited[i]){
				active[i] = false;
			}
            if(active[i]){
                f_in.push_back(i);
                active_count += 1;
            }
        }
		// Check if any active rows are left
        if (active_count == 0){
            break;
        }

		for (int i=0; i < NUM_THREADS; i++){
			thpool_.schedule([i]{
                forward_bfs(i);
            }, i);
		}
		for (int i=0; i < NUM_THREADS; i++){
			thpool_.wait(i);
		}
		
		// Mark all rows in f_in as visited so that they aren't taken into consideration for next frontier
		for (int x=0; x<f_in.size(); x++){
			int i = f_in[x];
			visited[i] = true;
		}
		
    }
	
	// Init frontier for reverse_bfs
	f_rev.clear();
    for (int j=0; j<n; j++){
        if (reverse_v[j] == true){
            f_rev.push_back(j);
        }
    }

	// Check if any columns were marked for reverse_bfs
    if (f_rev.size() > 0){
		for (int i=0; i < NUM_THREADS; i++){
			thpool_.schedule([i]{
                reverse_bfs(i);
            }, i);
		}
		for (int i=0; i < NUM_THREADS; i++){
			thpool_.wait(i);
		}
		
		// Init frontier for augment pass
		f_aug.clear();
        for (int j=0; j<n; j++){
            if (augment[j] == true){
                f_aug.push_back(j);
            }
        }
		
		for (int i=0; i < NUM_THREADS; i++){
			thpool_.schedule([i]{
                augment_pass(i);
            }, i);
		}
		for (int i=0; i < NUM_THREADS; i++){
			thpool_.wait(i);
		}
		// Set flag which indicates if optimality check should be executed (True) or not (False)
        check_flag = true;
    }
    else{
		// If reverse pass wasn't executed update dual variables to introduce new zero slack
		theta = inf;
		// Find minimum non-zero slack
		for (int j=0; j<n; j++){
			if (slack[j] > 0){
				theta = min(theta, slack[j]);
			}
		}
	
		for (int i=0; i < NUM_THREADS; i++){
			thpool_.schedule([i]{
                update_pass(i);
            }, i);
		}
		for (int i=0; i < NUM_THREADS; i++){
			thpool_.wait(i);
		}
		// Set flag which indicates if optimality check should be executed (True) or not (False)
        check_flag = false;
    }
    return check_flag;
}

int hungarian_parallel(){
    int ret = 0; //weight of the optimal matching

    bool check_flag = true;
	
	init_potentials_parallel();
    while (true){
        if(check_flag){
            /* Reset arrays to initial state */
			for (int i=0; i < NUM_THREADS; i++){
				thpool_.schedule([i]{
                    reset_arrays(i);
                }, i);
			}
			for (int i=0; i < NUM_THREADS; i++){
				thpool_.wait(i);
			}
			
			/* Check if optimality is reached */
			int match_count = 0;
			match_count = optimality_check();
            if (match_count == n){
                break;
            }
        }

        check_flag = augmenting_path_search();
    }

	// Calculate total cost of assignment
    for (int i = 0; i < n; i++) {
        ret += cost[i][ass_row[i]];
    }

    return ret;
}

void create_matrix(vector<vector<int>>& mat, int size){
	srand (time(NULL)); 
	
	mat.resize(size);
	for(int i=0;i<size;++i){
        mat[i].resize(size);
        for(int j=0;j<size;++j){
            mat[i][j] = rand() % size + 1;
        }
    }
}

// Reset all vectors before solving new assignment problem
void reset(){
	for (int i=0; i<n; i++){
		ass_row[i] = -1;
		ass_col[i] = -1;
		cov_row[i] = 0;
		cov_col[i] = 0;
		
		dual_row[i] = 0.0;
		dual_col[i] = 0.0;
		slack[i] = inf;
		
		prv_row[i] = -1;
		prv_col[i] = -1;
		suc_row[i] = -1;
		suc_col[i] = -1;
		
		active[i] = false;
	}
}

void resize(){
	// Resize all vectors to fit new assignment problem
	ass_row.resize(n); //row assignment
	ass_col.resize(n); //col assignment
	cov_row.resize(n); //row cover
	cov_col.resize(n); //col cover

	dual_row.resize(n); //dual variable row
	dual_col.resize(n); //dual variable col
	slack.resize(n); //column slack variable

	prv_row.resize(n); //row predecessor
	prv_col.resize(n); //col predecessor
	suc_row.resize(n); //row successor
	suc_col.resize(n); //col successor
		
	active.resize(n);
	visited.resize(n);
	reverse_v.resize(n);
	augment.resize(n);
}

double median(vector<double> v, int n)
{
    // Sort the vector
    sort(v.begin(), v.end());

    // Check if the number of elements is odd
    if (n % 2 != 0)
        return (double)v[n / 2];

    // If the number of elements is even, return the average
    // of the two middle elements
    return (double)(v[(n - 1) / 2] + v[n / 2]) / 2.0;
}

int main(int argc, char*argv[])
{
    if (argc != 3) {
        std::cerr << "Arguments must be presented as follows." << std::endl;
        std::cerr << "./name_test num_test_runs name_output_file" << std::endl;
        exit(1);
    }
	
	string output_path = "./data/";
	output_path.append(argv[2]);
	string filename_all_runs = output_path + ".txt";
	string filename_mean_runs = output_path + "_mean.txt";
        	

	int num_test_runs = atoi(argv[1]);
	
	ofstream out_file_all;
    out_file_all.open (filename_all_runs);
	out_file_all<<"Hungarian Parallel ThreadPool ("<<NUM_THREADS<<" Threads): \n";
	out_file_all<<"Size\t\t\t\tCost\t\t\t\tTotal Time in s\t\t\tTotal CPU time in ms\n";
	
	ofstream out_file_mean;
    out_file_mean.open (filename_mean_runs);
	out_file_mean<<"Hungarian Parallel ThreadPool ("<<NUM_THREADS<<" Threads, "<<num_test_runs<<" runs): \n";
	out_file_mean<<"Size\t\t\t\tMean Time in s\t\t\tMean CPU time in ms\t\t\tMedian Time in s\t\t\tMedian CPU Time in ms\n";
	
	
	for (int& t : test_cases){
		double sum_timing = 0;
		double sum_time = 0;
		
		vector<double> times(test_cases.size());
        vector<double> timings(test_cases.size());
		
		n = t;
		resize();

		for (int r=0; r < num_test_runs; r++){
			
			cout<<"Test Case:\t"<<n<<endl;
			/* init cost matrix for test case */
			reset();
			create_matrix(cost, n);

			int res; // result of algorithm
			clock_t start, end; // start and end time of algorithm

			/* Begin Time */
			auto t1 = std::chrono::high_resolution_clock::now();
			start = clock();

			res=hungarian_parallel();  
			end = clock();
	
			/* End Time */
			auto t2 = std::chrono::high_resolution_clock::now();
			double timing = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
			double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
			
			times.push_back(time);
			timings.push_back(timing);
				
			sum_timing += timing;
			sum_time += time;

			out_file_all<<n<<"\t\t\t\t"<<res<<"\t\t\t\t"<<timing / 1000.0<<"\t\t\t\t"<<time<<"\n";
		}
		
		double mean_timing = sum_timing / num_test_runs;
		double mean_time = sum_time / num_test_runs;
		
		double median_timing = median(timings, timings.size());
		double median_time = median(times, times.size());
		
		out_file_mean<<n<<"\t\t\t\t"<<mean_timing / 1000.0<<"\t\t\t\t"<<mean_time<<"\t\t\t\t"<<median_timing / 1000.0<<"\t\t\t\t"<<median_time<<"\n";
	}
	out_file_all.close();
	out_file_mean.close();
}
