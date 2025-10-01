#include <stdio.h>
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
#define R 50

typedef struct bid bid;

struct bid {
    int bidder;
    int object;      // Id of object that bidder bidded for
    double amount;   // Amount of bid of bidder
};


/* Pre-declare functions to allow arbitrary call ordering  */
int auction(int cost[N][N]);
void biddingPhase(double epsilon, int cost[N][N], int assignment[N], double prices[N], bid bidders[N], bool Ids[N]);
void assignmentPhase(int assignment[N], int belong[N], double prices[N], bid bidders[N], int biddersCount);



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

bool comp_bids (bid x, bid y){
	return x. bidder == y.bidder && x.object == y.object && x.amount == y.amount;
}

int main()
{

	FILE *f;
	FILE *f_mean;

	// Open a file in write mode
	f = fopen("auc_emmtrix_ser.txt", "w");
	fprintf(f, "Auction Seriell Emmtrix: \n");
	fprintf(f, "Size\t\t\t\tCost\t\t\t\tTotal Time in s\t\t\tTotal CPU time in ms\n");
	fclose(f);

	f_mean = fopen("auc_emmtrix_ser_mean.txt", "w");
	fprintf(f_mean, "Auction Seriell Emmtrix (%d runs): \n", R);
	fprintf(f_mean, "Size\t\t\t\tMean Time in s\t\t\tMean CPU time in ms\t\t\tMedian Time in s\t\t\tMedian CPU Time in ms\n");
	fclose(f_mean);

	int sum_time = 0;
	int sum_timing = 0;
	double times[R];
	double timings[R];


	for (int r=0; r<R; r++){

		/* Create Matrix */
		int cost[N][N];

		srand(time(NULL));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
			{
				cost[i][j] = (rand() % N + 1) * (-1);
			}
		}

		long t1,t2;
		struct timeval timecheck;

		// Begin Time
		gettimeofday(&timecheck, NULL);
		t1 = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
		clock_t start = clock();

		int result = auction(cost);

		// End Time
		clock_t end = clock();
		gettimeofday(&timecheck, NULL);
		t2 = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;

		double time = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
		double timing = (long)(t2 - t1);

		times[r] = time;
		timings[r] = timing;

		sum_timing += timing;
		sum_time += time;

		// Open a file in append mode
		f = fopen("auc_emmtrix_ser.txt", "a");
		fprintf(f, "%d\t\t\t\t%d\t\t\t\t%f\t\t\t\t%f\n", N, result, timing / 1000.0, time);
		fclose(f);

	}

	double mean_timing = sum_timing / R;
	double mean_time = sum_time / R;

	double median_timing = findMedian(timings, R);
	double median_time = findMedian(times, R);

	// Open a file in append mode
	f_mean = fopen("auc_emmtrix_ser_mean.txt", "a");
	fprintf(f_mean, "%d\t\t\t\t%f\t\t\t\t%f\t\t\t\t%f\t\t\t\t%f\n", N, mean_timing / 1000.0, mean_time, median_timing / 1000.0, median_time);
	fclose(f_mean);

	return 0;
}

int auction(int cost[N][N])
{
	int assignment[N];
    double prices[N];
    int belong[N];

    for (int i=0; i<N; i++){
    	assignment[i] = -1;
    	belong[i] = -1;
    	prices[i] = 1.0;
    }

    double epsilon = 1.0;
    int iter = 1;



    while (epsilon > 1.0 / N) {
		for (int i=0; i < N; i++) {
			assignment[i] = -1;
			belong[i] = -1;
		}

		int assignment_count = 0;
		while (assignment_count != N) {
			/* Start Auction Round */
            iter++;
            bid bidders[N];
            bool Ids[N];
            biddingPhase(epsilon, cost, assignment, prices, bidders, Ids);

            int biddersCount = 0;
			bid bidders_as[N];
            for (int i=0; i<N; i++){
            	if (Ids[i]){
            		bidders_as[biddersCount++] = bidders[i];
            	}
            }

            assignmentPhase(assignment, belong, prices, bidders_as, biddersCount);
			/* Check if unassigned persons are left */
			assignment_count = 0;
			for(size_t i=0; i<N; i++){
				if(assignment[i] != -1){
					assignment_count++;
				}
			}
		}

		epsilon *= 0.25;
    }

    int result = 0;
    for (int i = 0; i < N; i++) {
        result += cost[i][assignment[i]];
    }
    result *= -1;
    return result;
}

void biddingPhase(double epsilon, int cost[N][N], int assignment[N], double prices[N], bid bidders[N], bool Ids[N])
{
	size_t i1;
	size_t i2;
	size_t i3;
	size_t j1;

	bool ids[N];
	for (i2=0; i2<N; i2++){
		ids[i2] = false;
	}

	bid bids[N];

    /* Compute the bids of each unassigned individual and store them in temp */
    for (i1 = 0; i1 < N; i1++)
    {
        if (assignment[i1] == -1)
        {
            bid bid_i;
            bid_i.bidder = i1;

            double best_payoff = -INF;
            double sec_payoff = -INF;
            int best_obj;
            double price_obj;
            for (j1 = 0; j1 < N; j1++)
            {
                double curVal = cost[i1][j1] - prices[j1];
                if (curVal > best_payoff)
                {
                    sec_payoff = best_payoff;
                    best_payoff = curVal;
                    best_obj = j1;
                    price_obj = prices[j1];
                }
                else if (curVal > sec_payoff)
                {
                    sec_payoff = curVal;
                }
            }

            bid_i.amount = price_obj + best_payoff - sec_payoff + epsilon;
            bid_i.object = best_obj;

            bids[i1] = bid_i;
            ids[i1] = true;
        }
    }

	for (i3=0; i3<N; i3++){
		bidders[i3] = bids[i3];
		Ids[i3] = ids[i3];
	}

}

    /*
        Assignment Phase of the Auction Iteration:
        Each object that has received a bid, increases its price to the highest bid received.
    */
void assignmentPhase(int assignment[N], int belong[N], double prices[N], bid bidders[N], int biddersCount)
{
	size_t i2;
	size_t i3;
	size_t j2;

    for (j2 = 0; j2 < N; j2++)
    {
        bid bids_obj[biddersCount];
        int bids_objCount = 0;
        for (i2 = 0; i2 < biddersCount; i2++) {
            if (bidders[i2].object == j2) {
                bids_obj[bids_objCount++] = bidders[i2];
            }
        }

        if (bids_objCount != 0)
        {
            double highest_bid = -INF; // amount of highest bid received by the object
            int id; //id of new bidder assigned to object j
            for (i3 = 0; i3 < bids_objCount; i3++)
            {
                bid bid_i = bids_obj[i3];
                double curVal = bid_i.amount;
                if (curVal > highest_bid)
                {
                    highest_bid = curVal;
                    id = bid_i.bidder;
                }
            }

            int previous_owner = belong[j2];
            if (previous_owner != -1) {
                assignment[previous_owner] = -1;
            }
            assignment[id] = j2;
            belong[j2] = id;
            prices[j2] = highest_bid;
        }
    }
}
