#include <stdio.h>
#include "_emx_main.h"
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>

#define INF INT_MAX
#define VERBOSE 0
#define N 3000
#define N_50 1500

#define R 30
typedef struct bid bid;
struct bid {
	int bidder;
	int object;
	double amount;
};

void assignmentPhase(int assignment[N], int belong[N], double prices[N], bid bidders[N], int biddersCount) {
	size_t i2;
	size_t i3;
	size_t j2;
	int tmp;
	int tmp2;
	
	for (j2 = 0; j2 < N; j2 = j2 + 1) {
		bid bids_obj[biddersCount];
		int bids_objCount = 0;
		
		for (i2 = 0; i2 < biddersCount; i2 = i2 + 1) {
			if (bidders[i2].object == j2) {
				tmp2 = bids_objCount;
				bids_objCount = tmp2 + 1;
				
				tmp = tmp2;
				
				bids_obj[tmp] = bidders[i2];
			}
		}
		
		if (bids_objCount != 0) {
			double highest_bid = -0x7fffffff;
			int id;
			
			for (i3 = 0; i3 < bids_objCount; i3 = i3 + 1) {
				bid bid_i = bids_obj[i3];
				double curVal = bid_i.amount;
				
				if (curVal > highest_bid) {
					highest_bid = curVal;
					id = bid_i.bidder;
				}
			}
			
			{
				int previous_owner = belong[j2];
				
				if (previous_owner != (-1)) {
					assignment[previous_owner] = -1;
				}
				
				assignment[id] = j2;
				belong[j2] = id;
				prices[j2] = highest_bid;
			}
		}
	}
}


extern void biddingPhase_p0(double epsilon_p0, int cost_p0[N][N], int assignment_p0[N], double prices_p0[N], bid bidders_p0[N], _Bool Ids_p0[N]) {
	size_t i2_p0;
	_Bool ids_split1_p0[N_50];
	size_t i1_p0;
	size_t j1_p0;
	size_t i3_p0;
	_Bool ids_split2_p0[N_50];
	
	for (i2_p0 = 0; i2_p0 < N_50; i2_p0 = i2_p0 + 1) {
		_Bool val2_p0;
		
		val2_p0 = 0;
		ids_split1_p0[i2_p0 - 0] = val2_p0;
	}
	
	{
		bid bids_split1_p0[N_50];
		bid bids_split2_p0[N_50];
		
		for (i1_p0 = 0; i1_p0 < N_50; i1_p0 = i1_p0 + 1) {
			if (assignment_p0[i1_p0] == (-1)) {
				bid bid_i_p0;
				
				bid_i_p0.bidder = i1_p0;
				
				{
					int best_obj_p0;
					double price_obj_p0;
					double best_payoff_p0 = -0x7fffffff;
					double sec_payoff_p0 = -0x7fffffff;
					struct bid val2_p0;
					_Bool val3_p0;
					
					for (j1_p0 = 0; j1_p0 < N; j1_p0 = j1_p0 + 1) {
						double curVal_p0 = cost_p0[i1_p0][j1_p0] - prices_p0[j1_p0];
						
						if (curVal_p0 > best_payoff_p0) {
							sec_payoff_p0 = best_payoff_p0;
							best_payoff_p0 = curVal_p0;
							best_obj_p0 = j1_p0;
							price_obj_p0 = prices_p0[j1_p0];
						} else if (curVal_p0 > sec_payoff_p0) {
							sec_payoff_p0 = curVal_p0;
						}
						
					}
					
					bid_i_p0.amount = price_obj_p0 + best_payoff_p0 - sec_payoff_p0 + epsilon_p0;
					bid_i_p0.object = best_obj_p0;
					val2_p0 = bid_i_p0;
					bids_split1_p0[i1_p0 - 0] = val2_p0;
					val3_p0 = 1;
					ids_split1_p0[i1_p0 - 0] = val3_p0;
				}
			}
		}
		
		for (i1_p0 = N_50; i1_p0 < N; i1_p0 = i1_p0 + 1) {
		}
		
		for (i3_p0 = 0; i3_p0 < N_50; i3_p0 = i3_p0 + 1) {
			struct bid val2_p0;
			_Bool val3_p0;
			
			val2_p0 = bids_split1_p0[i3_p0 - 0];
			bidders_p0[i3_p0] = val2_p0;
			val3_p0 = ids_split1_p0[i3_p0 - 0];
			Ids_p0[i3_p0] = val3_p0;
		}
		
		EMX_Recv(1, 0, 5, -1, bids_split2_p0, N_50 * sizeof(*bids_split2_p0));
		
		EMX_Recv(1, 0, 4, -1, ids_split2_p0, N_50 * sizeof(*ids_split2_p0));
		
		for (i3_p0 = N_50; i3_p0 < N; i3_p0 = i3_p0 + 1) {
			struct bid val2_p0;
			_Bool val3_p0;
			
			val2_p0 = bids_split2_p0[i3_p0 - N_50];
			bidders_p0[i3_p0] = val2_p0;
			val3_p0 = ids_split2_p0[i3_p0 - N_50];
			Ids_p0[i3_p0] = val3_p0;
		}
	}
}


extern void biddingPhase_p1(double epsilon_p1, int cost_p1[N][N], int assignment_p1[N], double prices_p1[N]) {
	size_t i2_p1;
	_Bool ids_split2_p1[N_50];
	size_t i1_p1;
	size_t j1_p1;
	
	for (i2_p1 = N_50; i2_p1 < N; i2_p1 = i2_p1 + 1) {
		_Bool val2_p1;
		
		val2_p1 = 0;
		ids_split2_p1[i2_p1 - N_50] = val2_p1;
	}
	
	{
		bid bids_split2_p1[N_50];
		
		for (i1_p1 = N_50; i1_p1 < N; i1_p1 = i1_p1 + 1) {
			
			
			
			
			
			
			if (assignment_p1[i1_p1] == (-1)) {
				bid bid_i_p1;
				
				bid_i_p1.bidder = i1_p1;
				
				{
					int best_obj_p1;
					double price_obj_p1;
					double best_payoff_p1 = -0x7fffffff;
					double sec_payoff_p1 = -0x7fffffff;
					struct bid val2_p1;
					_Bool val3_p1;
					
					for (j1_p1 = 0; j1_p1 < N; j1_p1 = j1_p1 + 1) {
						double curVal_p1 = cost_p1[i1_p1][j1_p1] - prices_p1[j1_p1];
						
						if (curVal_p1 > best_payoff_p1) {
							sec_payoff_p1 = best_payoff_p1;
							best_payoff_p1 = curVal_p1;
							best_obj_p1 = j1_p1;
							price_obj_p1 = prices_p1[j1_p1];
						} else if (curVal_p1 > sec_payoff_p1) {
							sec_payoff_p1 = curVal_p1;
						}
						
					}
					
					bid_i_p1.amount = price_obj_p1 + best_payoff_p1 - sec_payoff_p1 + epsilon_p1;
					bid_i_p1.object = best_obj_p1;
					val2_p1 = bid_i_p1;
					bids_split2_p1[i1_p1 - N_50] = val2_p1;
					val3_p1 = 1;
					ids_split2_p1[i1_p1 - N_50] = val3_p1;
				}
			}
			
		}
		
		EMX_Send(1, 0, 5, -1, bids_split2_p1, N_50 * sizeof(*bids_split2_p1));
		
		EMX_Send(1, 0, 4, -1, ids_split2_p1, N_50 * sizeof(*ids_split2_p1));
	}
}


extern int auction_p0(int cost_p0[N][N]) {
	_Bool sync_p0;
	int cost_p02[N][N];
	double prices_p0[N];
	int assignment_p0[N];
	int belong_p0[N];
	int tmp2_p0;
	int tmp_p0;
	
	for (int i_p0 = 0; i_p0 < N; i_p0 = i_p0 + 1) {
		assignment_p0[i_p0] = -1;
		belong_p0[i_p0] = -1;
		prices_p0[i_p0] = 1.0;
	}
	
	{
		double epsilon_p0 = 1.0;
		int iter_p0 = 1;
		
		while (sync_p0 = (epsilon_p0 > (1.0 / N)), EMX_SendSync(0, 1, 9, -1, sync_p0), sync_p0) {
			EMX_Send64F(0, 1, 3, -1, epsilon_p0);
			
			
			
			
			
			
			
			for (int i_p0 = 0; i_p0 < N; i_p0 = i_p0 + 1) {
				assignment_p0[i_p0] = -1;
				belong_p0[i_p0] = -1;
			}
			
			{
				int assignment_count_p0 = 0;
				
				while (sync_p0 = (assignment_count_p0 != N), EMX_SendSync(0, 1, 8, -1, sync_p0), sync_p0) {
					EMX_Send(0, 1, 2, -1, assignment_p0, N * sizeof(*assignment_p0));
					
					EMX_Send(0, 1, 1, -1, prices_p0, N * sizeof(*prices_p0));
					
					
					
					
					
					
					
					{
						bid bidders_p0[N];
						_Bool Ids_p0[N];
						
						biddingPhase_p0(epsilon_p0, cost_p0, assignment_p0, prices_p0, bidders_p0, Ids_p0);
						
						{
							bid bidders_as_p0[N];
							int biddersCount_p0 = 0;
							
							for (int i_p0 = 0; i_p0 < N; i_p0 = i_p0 + 1) {
								if (Ids_p0[i_p0]) {
									tmp2_p0 = biddersCount_p0;
									biddersCount_p0 = tmp2_p0 + 1;
									
									tmp_p0 = tmp2_p0;
									
									bidders_as_p0[tmp_p0] = bidders_p0[i_p0];
								}
							}
							
							assignmentPhase(assignment_p0, belong_p0, prices_p0, bidders_as_p0, biddersCount_p0);
							
							assignment_count_p0 = EMX_Recv32(1, 0, 6, -1);
							
							for (size_t i_p0 = 0; i_p0 < N; i_p0 = i_p0 + 1) {
								if (assignment_p0[i_p0] != (-1)) {
									assignment_count_p0 = assignment_count_p0 + 1;
								}
							}
						}
					}
				}
			}
			
			epsilon_p0 = EMX_Recv64F(1, 0, 7, -1);
		}
		
		{
			int result_p0 = 0;
			
			for (int i_p0 = 0; i_p0 < N; i_p0 = i_p0 + 1) {
				result_p0 = result_p0 + cost_p0[i_p0][assignment_p0[i_p0]];
			}
			
			result_p0 = result_p0 * -1;
			return result_p0;
		}
	}
}


extern void auction_p1(int cost_p1[N][N]) {
	int cost_p12[N][N];
	double prices_p1[N];
	int assignment_p1[N];
	double epsilon_p1;
	int iter_p1 = 1;
	
	while (EMX_RecvSync(0, 1, 9, -1)) {
		epsilon_p1 = EMX_Recv64F(0, 1, 3, -1);
		
		{
			int assignment_count_p1 = 0;
			
			while (EMX_RecvSync(0, 1, 8, -1)) {
				EMX_Recv(0, 1, 2, -1, assignment_p1, N * sizeof(*assignment_p1));
				
				EMX_Recv(0, 1, 1, -1, prices_p1, N * sizeof(*prices_p1));
				
				biddingPhase_p1(epsilon_p1, cost_p1, assignment_p1, prices_p1);
				
				assignment_count_p1 = 0;
				
				EMX_Send32(1, 0, 6, -1, assignment_count_p1);
				
				iter_p1 = iter_p1 + 1;
			}
			
			epsilon_p1 = epsilon_p1 * 0.25;
		}
		EMX_Send64F(1, 0, 7, -1, epsilon_p1);
	}
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

int main_p0() {
	long callarg2_p0;
	int callarg3_p0;
	
	FILE *f;
	FILE *f_mean;

	// Open a file in write mode
	f = fopen("auc_emmtrix_2.txt", "a");
	fprintf(f, "Auction Parallel Emmtrix(2 Cores): \n");
	fprintf(f, "Size\t\t\t\tCost\t\t\t\tTotal Time in s\t\t\tTotal CPU time in ms\n");
	fclose(f);

	f_mean = fopen("auc_emmtrix_2_mean.txt", "a");
	fprintf(f_mean, "Auction Parallel Emmtrix (2 Cores, %d runs): \n", R);
	fprintf(f_mean, "Size\t\t\t\tMean Time in s\t\t\tMean CPU time in ms\t\t\tMedian Time in s\t\t\tMedian CPU Time in ms\n");
	fclose(f_mean);

	int sum_time = 0;
	int sum_timing = 0;
	double times[R];
	double timings[R];
	
	for (int r_p0 = 0; r_p0 < R; r_p0 = r_p0 + 1) {
		int cost_p0[N][N];
		
		srand(time(NULL));
		for (int i_p0 = 0; i_p0 < N; i_p0 = i_p0 + 1) {
			for (int j_p0 = 0; j_p0 < N; j_p0 = j_p0 + 1) {
				cost_p0[i_p0][j_p0] = (rand() % N + 1) * -1;
			}
		}
		
		{
			long t1,t2;
			struct timeval timecheck;

			// Begin Time
			gettimeofday(&timecheck, NULL);
			t1 = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
			clock_t start = clock();
			
			int result_p0;
			
			EMX_Send(0, 1, 0, -1, cost_p0, N * sizeof(*cost_p0));
			
			callarg3_p0 = auction_p0(cost_p0);
			
			result_p0 = callarg3_p0;
			
			// End Time
			clock_t end = clock();
			gettimeofday(&timecheck, NULL);
			t2 = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;

			double time = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
			double timing = (long)(t2 - t1);

			times[r_p0] = time;
			timings[r_p0] = timing;

			sum_timing += timing;
			sum_time += time;

			// Open a file in append mode
			f = fopen("auc_emmtrix_2.txt", "a");
			fprintf(f, "%d\t\t\t\t%d\t\t\t\t%f\t\t\t\t%f\n", N, result_p0, timing / 1000.0, time);
			fclose(f);
		}
		
		
		{
		}
	}
	
	double mean_timing = sum_timing / R;
	double mean_time = sum_time / R;

	double median_timing = findMedian(timings, R);
	double median_time = findMedian(times, R);

	// Open a file in append mode
	f_mean = fopen("auc_emmtrix_2_mean.txt", "a");
	fprintf(f_mean, "%d\t\t\t\t%f\t\t\t\t%f\t\t\t\t%f\t\t\t\t%f\n", N, mean_timing / 1000.0, mean_time, median_timing / 1000.0, median_time);
	fclose(f_mean);
	
	return 0;
}


void main_p1() {
	time_t callarg_p1;
	
	for (int r_p1 = 0; r_p1 < R; r_p1 = r_p1 + 1) {
		int cost_p1[N][N];
		
		EMX_Recv(0, 1, 0, -1, cost_p1, N * sizeof(*cost_p1));
		
		auction_p1(cost_p1);
		
		callarg_p1 = time((void *)0);
		
		srand(callarg_p1);
	}
}


void main_p2() {
}


void main_p3() {
}


void main_p4() {
}


void main_p5() {
}


void main_p6() {
}


void main_p7() {
}

