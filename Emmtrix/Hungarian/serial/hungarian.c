#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

#define inf INT_MAX
#define N 2600
#define R 50
const int n=N;// number of jobs and workers

int** cost; // cost matrix

bool verbose = false;
bool maximum = false;

void init_potentials(int cost[N][N], int n, double dual_row[N], double dual_col[N]);
int optimality_check(int n, bool cov_row[N], int ass_row[N]);
void forward_bfs(int cost[N][N], int n, int f_in[N], int f_in_size, bool active[N], bool reverse[N], bool visited[N], int ass_col[N], bool cov_row[N], bool cov_col[N], double dual_row[N], double dual_col[N], double slack[N], int prv_row[N], int prv_col[N]);
void reverse_bfs(int f_rev[N], int f_rev_size, bool augment[N], int suc_row[N], int suc_col[N], int prv_row[N], int prv_col[N]);
void augment_pass(int f_aug[N], int f_aug_size, int ass_row[N], int ass_col[N], int suc_row[N], int suc_col[N]);
void update_pass(int n, double theta, bool active[N], bool cov_row[N], bool cov_col[N], double dual_row[N], double dual_col[N], double slack[N], int prv_col[N]);
bool augmenting_path_search(int cost[N][N], int n, bool active[N], int ass_row[N], int ass_col[N], bool cov_row[N], bool cov_col[N], double dual_row[N], double dual_col[N], double slack[N], int prv_row[N], int prv_col[N], int suc_row[N], int suc_col[N]);


void init_potentials(int cost[N][N], int n, double dual_row[N], double dual_col[N]) {
	size_t i1;
	size_t i2;
	size_t i3;
	size_t i4;
	size_t j1;
	size_t j2;

	double d_row[N];
	double d_col[N];

    for (i1 = 0u; i1 < N; i1++) {
        double temp = inf;
        for (j1 = 0u; j1 < N; j1++) {
        	if (temp > (double)cost[i1][j1]){
        		temp = (double)cost[i1][j1];
        	}
        }
        d_row[i1] = temp;
    }

	for (i3=0u; i3<N; i3++){
		dual_row[i3] = d_row[i3];
	}

    for (j2 = 0u; j2 < N; j2++) {
        double temp = inf;
        for (i2 = 0u; i2 < N; i2++) {
        	if (temp > (cost[i2][j2] - dual_row[i2])){
        		temp = cost[i2][j2] - dual_row[i2];
        	}
        }
        d_col[j2] = temp;
    }

	for (i4=0u; i4<N; i4++){
		dual_col[i4] = d_col[i4];
	}
}

int optimality_check(int n, bool cov_row[N], int ass_row[N]) {
	size_t i1;
    int match_count = 0;

    for (i1 = 0u; i1 < N; i1++) {
        if (ass_row[i1] != -1) {
            cov_row[i1] = true;
            match_count += 1;
        }
    }

   return match_count;
}

void forward_bfs(int cost[N][N], int n, int f_in[N], int f_in_size, bool active[N], bool reverse[N], bool visited[N], int ass_col[N], bool cov_row[N], bool cov_col[N], double dual_row[N], double dual_col[N], double slack[N], int prv_row[N], int prv_col[N]) {
    size_t j1;
	size_t x1;

	for (j1 = 0u; j1 < N; j1++) {
        if (!cov_col[j1]) {
            for (x1 = 0u; x1 < f_in_size; x1++) {
                int i = f_in[x1];
                if (slack[j1] > cost[i][j1] - dual_row[i] - dual_col[j1]) {
                    slack[j1] = cost[i][j1] - dual_row[i] - dual_col[j1];
                    prv_col[j1] = i;
                }
                int i_new = ass_col[j1];
                if (slack[j1] == 0) {
                    if (i_new != -1) {
                        prv_row[i_new] = j1;
                        cov_row[i_new] = false;
                        cov_col[j1] = true;
                        if (!active[i_new]) {
                            active[i_new] = true;
                        }
                    } else {
                        reverse[j1] = true;
                    }
                }
                visited[i] = true;
            }
        }
    }
}


void reverse_bfs(int f_rev[N], int f_rev_size, bool augment[N], int suc_row[N], int suc_col[N], int prv_row[N], int prv_col[N]) {
	size_t x1;

    for (x1 = 0u; x1 < f_rev_size; x1++) {
        int j = f_rev[x1];
        int r_cur = -1;
        int c_cur = j;

        while (c_cur != -1) {
            suc_col[c_cur] = r_cur;
            r_cur = prv_col[c_cur];
            suc_row[r_cur] = c_cur;
            c_cur = prv_row[r_cur];
        }
        augment[r_cur] = true;
    }
}


void augment_pass(int f_aug[N], int f_aug_size, int ass_row[N], int ass_col[N], int suc_row[N], int suc_col[N]) {
	size_t x1;

    for (x1 = 0u; x1 < f_aug_size; x1++) {
        int i = f_aug[x1];
        int r_cur = i;
        int c_cur = -1;

        while (r_cur != -1) {
            c_cur = suc_row[r_cur];
            ass_row[r_cur] = c_cur;
            ass_col[c_cur] = r_cur;
            r_cur = suc_col[c_cur];
        }
    }
}

void update_pass(int n, double theta, bool active[N], bool cov_row[N], bool cov_col[N], double dual_row[N], double dual_col[N], double slack[N], int prv_col[N]) {
    size_t k1;

	double d_row[N];
	for (int i=0; i<N; i++){
		d_row[i] = dual_row[i];
	}

	double d_col[N];
	for (int i=0; i<N; i++){
		d_col[i] = dual_col[i];
	}

	double sl[N];
	for (int i=0; i<N; i++){
		sl[i] = slack[i];
	}

	int act[N];
	for (int i=0; i<N; i++){
		act[i] = -1;
	}

    for (k1 = 0u; k1 < N; k1++) {
        if (!cov_row[k1]) {
            d_row[k1] += theta / 2;
        } else {
            d_row[k1] -= theta / 2;
        }
        if (!cov_col[k1]) {
            d_col[k1] += theta / 2;
        } else {
            d_col[k1] -= theta / 2;
        }
        if (sl[k1] > 0) {
            sl[k1] -= theta;
            if (sl[k1] == 0) {
				act[k1] = prv_col[k1];
            }
        }
    }

	for (int i=0; i<N; i++){
		if(act[i] != -1){
			int tmp = act[i];
			active[tmp] = true;
		}
		dual_row[i] = d_row[i];
		dual_col[i] = d_col[i];
		slack[i] = sl[i];
	}
}

bool augmenting_path_search(int cost[N][N], int n, bool active[N], int ass_row[N], int ass_col[N], bool cov_row[N], bool cov_col[N], double dual_row[N], double dual_col[N], double slack[N], int prv_row[N], int prv_col[N], int suc_row[N], int suc_col[N]) {
    bool check_flag = false;

	bool visited[N];
	bool reverse[N];
	bool augment[N];

	for (int i=0; i<N; i++){
		visited[i] = false;
		reverse[i] = false;
		augment[i] = false;
	}

	int active_count = 0;
	int f_in[N];
    for (int i = 0; i < n; i++) {
		if(ass_row[i] == -1 || active[i]){
			active[i] = true;
			f_in[active_count++] = i;
		}
		else{
			active[i] = false;
		}
    }


    while (active_count > 0) {
        forward_bfs(cost, n, f_in, active_count, active, reverse, visited, ass_col, cov_row, cov_col, dual_row, dual_col, slack, prv_row, prv_col);

		active_count = 0;
        for (int i = 0; i < n; i++) {
			if (visited[i]){
				active[i] = false;
			}
            if (active[i]) {
                f_in[active_count++] = i;
            }
        }
    }

    int f_rev[N];
    int f_rev_size = 0;
    for (int j = 0; j < n; j++) {
        if (reverse[j]) {
            f_rev[f_rev_size++] = j;
        }
    }

    if (f_rev_size > 0) {
        reverse_bfs(f_rev, f_rev_size, augment, suc_row, suc_col, prv_row, prv_col);

        int f_aug[N];
        int f_aug_size = 0;
        for (int j = 0; j < n; j++) {
            if (augment[j]) {
                f_aug[f_aug_size++] = j;
            }
        }
        augment_pass(f_aug, f_aug_size, ass_row, ass_col, suc_row, suc_col);
        check_flag = true;
    } else {
		double theta = inf;

		for (int j = 0; j < n; j++) {
			if (slack[j] > 0) {
				theta = (theta < slack[j]) ? theta : slack[j];
			}
		}

        update_pass(n, theta, active, cov_row, cov_col, dual_row, dual_col, slack, prv_col);
        check_flag = false;
    }

    return check_flag;
}


int hungarian_parallel(int cost[N][N], int n) {
    int ret = 0; // weight of the optimal matching

	int ass_row[N]; // row assignment
	int ass_col[N]; // col assignment
	bool cov_row[N]; // row cover
	bool cov_col[N]; // col cover

	double dual_row[N]; // dual variable row
	double dual_col[N]; // dual variable col
	double slack[N]; // column slack variable

	int prv_row[N]; // row predecessor
	int prv_col[N]; // col predecessor
	int suc_row[N]; // row successor
	int suc_col[N]; // col successor

	for (int i=0; i<n; i++){
		ass_row[i] = -1;
		ass_col[i] = -1;
		cov_row[i] = false;
        cov_col[i] = false;
        prv_row[i] = -1;
        prv_col[i] = -1;
        slack[i] = inf;
        suc_row[i] = -1;
        suc_col[i] = -1;
	}

	bool active[N];

    bool check_flag = true;

    int match_count = 0;

    init_potentials(cost, n, dual_row, dual_col);
    while (match_count < n) {
        check_flag = augmenting_path_search(cost, n, active, ass_row, ass_col, cov_row, cov_col, dual_row, dual_col, slack, prv_row, prv_col, suc_row, suc_col);

        if (check_flag){
			// reset Cover Arrays and Predecessor Arrays to initial state
            for (int i = 0; i < n; i++) {
                cov_row[i] = false;
                cov_col[i] = false;
                prv_row[i] = -1;
                prv_col[i] = -1;
                slack[i] = inf;
                suc_row[i] = -1;
                suc_col[i] = -1;
            }

        	match_count = optimality_check(n, cov_row, ass_row);
        }
    }

    for (int i = 0; i < n; i++) { // forming answer there
        ret += cost[i][ass_row[i]];
    }

    return ret;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

float findMedian(double arr[R], int n) {
    qsort(arr, n, sizeof(int), compare);

  	// If even, median is the average of the two
  	// middle elements
    if (n % 2 == 0) {
        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
    }

  	// If odd, median is the middle element
  	else {
        return arr[n / 2];
    }
}

int main()
{
	FILE *f;
	FILE *f_mean;

	int num_test_runs = R;

	// Open a file in write mode
	f = fopen("hun_emmtrix_50_ser.txt", "w");
	f_mean = fopen("hun_emmtrix_50_ser_mean.txt", "w");

	fprintf(f, "Hungarian Parallel Emmtrix (4 Threads): \n");
	fprintf(f, "Size\t\t\t\tCost\t\t\t\tTotal Time in s\t\t\tTotal CPU time in ms\n");

	fprintf(f_mean, "Hungarian Parallel Emmtrix (4 Threads, %d runs): \n", num_test_runs);
	fprintf(f_mean, "Size\t\t\t\tMean Time in s\t\t\tMean CPU time in ms\t\t\tMedian Time in s\t\t\tMedian CPU Time in ms\n");

	// Close the file
	fclose(f);
	fclose(f_mean);
	int sum_time = 0;
	int sum_timing = 0;
	double times[R];
	double timings[R];

	for (int i=0; i<num_test_runs; i++){
		/* Create Matrix */
		int cost[N][N];
		srand(time(NULL));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
			{
				cost[i][j] = rand() % n + 1;
			}
		}

		long t1,t2;
		struct timeval timecheck;

		/* Begin Time */
		gettimeofday(&timecheck, NULL);
		t1 = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
		clock_t start = clock();

		int result = hungarian_parallel(cost, n);

		/* End Time */
		clock_t end = clock();
		gettimeofday(&timecheck, NULL);
		t2 = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;

		double time = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
		double timing = (long)(t2 - t1);

		times[i] = time;
		timings[i] = timing;

		sum_timing += timing;
		sum_time += time;

		// Open a file in append mode
		f = fopen("hun_emmtrix_50_ser.txt", "a");
		fprintf(f, "%d\t\t\t\t%d\t\t\t\t%f\t\t\t\t%f\n", N, result, timing / 1000.0, time);
		fclose(f);
	}

	double mean_timing = sum_timing / num_test_runs;
	double mean_time = sum_time / num_test_runs;

	double median_timing = findMedian(timings, num_test_runs);
	double median_time = findMedian(times, num_test_runs);

	// Open a file in append mode
	f_mean = fopen("hun_emmtrix_50_ser_mean.txt", "a");
	fprintf(f_mean, "%d\t\t\t\t%f\t\t\t\t%f\t\t\t\t%f\t\t\t\t%f\n", N, mean_timing / 1000.0, mean_time, median_timing / 1000.0, median_time);
	fclose(f_mean);

	return 0;
}
