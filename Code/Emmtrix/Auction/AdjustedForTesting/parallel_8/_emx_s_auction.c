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

#define N_18 375 
#define N_28 750 
#define N_38 1125 
#define N_48 1500 
#define N_58 1875 
#define N_68 2250 
#define N_78 2625 

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
	_Bool ids_split1_p0[N_18];
	size_t i1_p0;
	size_t j1_p0;
	size_t i3_p0;
	_Bool ids_split2_p0[N_18];
	_Bool ids_split3_p0[N_18];
	_Bool ids_split4_p0[N_18];
	_Bool ids_split5_p0[N_18];
	_Bool ids_split6_p0[N_18];
	_Bool ids_split7_p0[N_18];
	_Bool ids_split8_p0[N_18];
	
	for (i2_p0 = 0; i2_p0 < N_18; i2_p0 = i2_p0 + 1) {
		_Bool val2_p0;
		
		val2_p0 = 0;
		ids_split1_p0[i2_p0 - 0] = val2_p0;
	}
	
	{
		bid bids_split1_p0[N_18];
		bid bids_split2_p0[N_18];
		bid bids_split3_p0[N_18];
		bid bids_split4_p0[N_18];
		bid bids_split5_p0[N_18];
		bid bids_split6_p0[N_18];
		bid bids_split7_p0[N_18];
		bid bids_split8_p0[N_18];
		
		for (i1_p0 = 0; i1_p0 < N_18; i1_p0 = i1_p0 + 1) {
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
		
		for (i1_p0 = N_18; i1_p0 < N_28; i1_p0 = i1_p0 + 1) {
		}
		
		for (i1_p0 = N_28; i1_p0 < N_38; i1_p0 = i1_p0 + 1) {
		}
		
		for (i1_p0 = N_38; i1_p0 < N_48; i1_p0 = i1_p0 + 1) {
		}
		
		for (i1_p0 = N_48; i1_p0 < N_58; i1_p0 = i1_p0 + 1) {
		}
		
		for (i1_p0 = N_58; i1_p0 < N_68; i1_p0 = i1_p0 + 1) {
		}
		
		for (i1_p0 = N_68; i1_p0 < N_78; i1_p0 = i1_p0 + 1) {
		}
		
		for (i1_p0 = N_78; i1_p0 < N; i1_p0 = i1_p0 + 1) {
		}
		
		for (i3_p0 = 0; i3_p0 < N_18; i3_p0 = i3_p0 + 1) {
			struct bid val2_p0;
			_Bool val3_p0;
			
			val2_p0 = bids_split1_p0[i3_p0 - 0];
			bidders_p0[i3_p0] = val2_p0;
			val3_p0 = ids_split1_p0[i3_p0 - 0];
			Ids_p0[i3_p0] = val3_p0;
		}
		
		EMX_Recv(1, 0, 35, -1, bids_split2_p0, N_18 * sizeof(*bids_split2_p0));
		
		EMX_Recv(1, 0, 28, -1, ids_split2_p0, N_18 * sizeof(*ids_split2_p0));
		
		for (i3_p0 = N_18; i3_p0 < N_28; i3_p0 = i3_p0 + 1) {
			struct bid val2_p0;
			_Bool val3_p0;
			
			val2_p0 = bids_split2_p0[i3_p0 - N_18];
			bidders_p0[i3_p0] = val2_p0;
			val3_p0 = ids_split2_p0[i3_p0 - N_18];
			Ids_p0[i3_p0] = val3_p0;
		}
		
		EMX_Recv(2, 0, 36, -1, bids_split3_p0, N_18 * sizeof(*bids_split3_p0));
		
		EMX_Recv(2, 0, 29, -1, ids_split3_p0, N_18 * sizeof(*ids_split3_p0));
		
		for (i3_p0 = N_28; i3_p0 < N_38; i3_p0 = i3_p0 + 1) {
			struct bid val2_p0;
			_Bool val3_p0;
			
			val2_p0 = bids_split3_p0[i3_p0 - N_28];
			bidders_p0[i3_p0] = val2_p0;
			val3_p0 = ids_split3_p0[i3_p0 - N_28];
			Ids_p0[i3_p0] = val3_p0;
		}
		
		EMX_Recv(3, 0, 37, -1, bids_split4_p0, N_18 * sizeof(*bids_split4_p0));
		
		EMX_Recv(3, 0, 30, -1, ids_split4_p0, N_18 * sizeof(*ids_split4_p0));
		
		for (i3_p0 = N_38; i3_p0 < N_48; i3_p0 = i3_p0 + 1) {
			struct bid val2_p0;
			_Bool val3_p0;
			
			val2_p0 = bids_split4_p0[i3_p0 - N_38];
			bidders_p0[i3_p0] = val2_p0;
			val3_p0 = ids_split4_p0[i3_p0 - N_38];
			Ids_p0[i3_p0] = val3_p0;
		}
		
		EMX_Recv(4, 0, 38, -1, bids_split5_p0, N_18 * sizeof(*bids_split5_p0));
		
		EMX_Recv(4, 0, 31, -1, ids_split5_p0, N_18 * sizeof(*ids_split5_p0));
		
		for (i3_p0 = N_48; i3_p0 < N_58; i3_p0 = i3_p0 + 1) {
			struct bid val2_p0;
			_Bool val3_p0;
			
			val2_p0 = bids_split5_p0[i3_p0 - N_48];
			bidders_p0[i3_p0] = val2_p0;
			val3_p0 = ids_split5_p0[i3_p0 - N_48];
			Ids_p0[i3_p0] = val3_p0;
		}
		
		EMX_Recv(5, 0, 39, -1, bids_split6_p0, N_18 * sizeof(*bids_split6_p0));
		
		EMX_Recv(5, 0, 32, -1, ids_split6_p0, N_18 * sizeof(*ids_split6_p0));
		
		for (i3_p0 = N_58; i3_p0 < N_68; i3_p0 = i3_p0 + 1) {
			struct bid val2_p0;
			_Bool val3_p0;
			
			val2_p0 = bids_split6_p0[i3_p0 - N_58];
			bidders_p0[i3_p0] = val2_p0;
			val3_p0 = ids_split6_p0[i3_p0 - N_58];
			Ids_p0[i3_p0] = val3_p0;
		}
		
		EMX_Recv(6, 0, 40, -1, bids_split7_p0, N_18 * sizeof(*bids_split7_p0));
		
		EMX_Recv(6, 0, 33, -1, ids_split7_p0, N_18 * sizeof(*ids_split7_p0));
		
		for (i3_p0 = N_68; i3_p0 < N_78; i3_p0 = i3_p0 + 1) {
			struct bid val2_p0;
			_Bool val3_p0;
			
			val2_p0 = bids_split7_p0[i3_p0 - N_68];
			bidders_p0[i3_p0] = val2_p0;
			val3_p0 = ids_split7_p0[i3_p0 - N_68];
			Ids_p0[i3_p0] = val3_p0;
		}
		
		EMX_Recv(7, 0, 41, -1, bids_split8_p0, N_18 * sizeof(*bids_split8_p0));
		
		EMX_Recv(7, 0, 34, -1, ids_split8_p0, N_18 * sizeof(*ids_split8_p0));
		
		for (i3_p0 = N_78; i3_p0 < N; i3_p0 = i3_p0 + 1) {
			struct bid val2_p0;
			_Bool val3_p0;
			
			val2_p0 = bids_split8_p0[i3_p0 - N_78];
			bidders_p0[i3_p0] = val2_p0;
			val3_p0 = ids_split8_p0[i3_p0 - N_78];
			Ids_p0[i3_p0] = val3_p0;
		}
	}
}


extern void biddingPhase_p1(double epsilon_p1, int cost_p1[N][N], int assignment_p1[N], double prices_p1[N]) {
	size_t i2_p1;
	_Bool ids_split2_p1[N_18];
	size_t i1_p1;
	size_t j1_p1;
	
	for (i2_p1 = N_18; i2_p1 < N_28; i2_p1 = i2_p1 + 1) {
		_Bool val2_p1;
		
		val2_p1 = 0;
		ids_split2_p1[i2_p1 - N_18] = val2_p1;
	}
	
	{
		bid bids_split2_p1[N_18];
		
		for (i1_p1 = N_18; i1_p1 < N_28; i1_p1 = i1_p1 + 1) {
			
			
			
			
			
			
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
					bids_split2_p1[i1_p1 - N_18] = val2_p1;
					val3_p1 = 1;
					ids_split2_p1[i1_p1 - N_18] = val3_p1;
				}
			}
			
		}
		
		
		
		
		
		
		
		EMX_Send(1, 0, 35, -1, bids_split2_p1, N_18 * sizeof(*bids_split2_p1));
		
		EMX_Send(1, 0, 28, -1, ids_split2_p1, N_18 * sizeof(*ids_split2_p1));
		
		
		
		
		
		
	}
}


extern void biddingPhase_p2(double epsilon_p2, int cost_p2[N][N], int assignment_p2[N], double prices_p2[N]) {
	size_t i2_p2;
	_Bool ids_split3_p2[N_18];
	size_t i1_p2;
	size_t j1_p2;
	
	for (i2_p2 = N_28; i2_p2 < N_38; i2_p2 = i2_p2 + 1) {
		_Bool val2_p2;
		
		val2_p2 = 0;
		ids_split3_p2[i2_p2 - N_28] = val2_p2;
	}
	
	{
		bid bids_split3_p2[N_18];
		
		
		for (i1_p2 = N_28; i1_p2 < N_38; i1_p2 = i1_p2 + 1) {
			
			
			
			
			
			if (assignment_p2[i1_p2] == (-1)) {
				bid bid_i_p2;
				
				bid_i_p2.bidder = i1_p2;
				
				{
					int best_obj_p2;
					double price_obj_p2;
					double best_payoff_p2 = -0x7fffffff;
					double sec_payoff_p2 = -0x7fffffff;
					struct bid val2_p2;
					_Bool val3_p2;
					
					for (j1_p2 = 0; j1_p2 < N; j1_p2 = j1_p2 + 1) {
						double curVal_p2 = cost_p2[i1_p2][j1_p2] - prices_p2[j1_p2];
						
						if (curVal_p2 > best_payoff_p2) {
							sec_payoff_p2 = best_payoff_p2;
							best_payoff_p2 = curVal_p2;
							best_obj_p2 = j1_p2;
							price_obj_p2 = prices_p2[j1_p2];
						} else if (curVal_p2 > sec_payoff_p2) {
							sec_payoff_p2 = curVal_p2;
						}
						
					}
					
					bid_i_p2.amount = price_obj_p2 + best_payoff_p2 - sec_payoff_p2 + epsilon_p2;
					bid_i_p2.object = best_obj_p2;
					val2_p2 = bid_i_p2;
					bids_split3_p2[i1_p2 - N_28] = val2_p2;
					val3_p2 = 1;
					ids_split3_p2[i1_p2 - N_28] = val3_p2;
				}
			}
			
			
		}
		
		
		
		
		
		
		
		EMX_Send(2, 0, 36, -1, bids_split3_p2, N_18 * sizeof(*bids_split3_p2));
		
		EMX_Send(2, 0, 29, -1, ids_split3_p2, N_18 * sizeof(*ids_split3_p2));
		
		
		
		
		
	}
}


extern void biddingPhase_p3(double epsilon_p3, int cost_p3[N][N], int assignment_p3[N], double prices_p3[N]) {
	size_t i2_p3;
	_Bool ids_split4_p3[N_18];
	size_t i1_p3;
	size_t j1_p3;
	
	for (i2_p3 = N_38; i2_p3 < N_48; i2_p3 = i2_p3 + 1) {
		_Bool val2_p3;
		
		val2_p3 = 0;
		ids_split4_p3[i2_p3 - N_38] = val2_p3;
	}
	
	{
		bid bids_split4_p3[N_18];
		
		
		
		for (i1_p3 = N_38; i1_p3 < N_48; i1_p3 = i1_p3 + 1) {
			
			
			
			
			if (assignment_p3[i1_p3] == (-1)) {
				bid bid_i_p3;
				
				bid_i_p3.bidder = i1_p3;
				
				{
					int best_obj_p3;
					double price_obj_p3;
					double best_payoff_p3 = -0x7fffffff;
					double sec_payoff_p3 = -0x7fffffff;
					struct bid val2_p3;
					_Bool val3_p3;
					
					for (j1_p3 = 0; j1_p3 < N; j1_p3 = j1_p3 + 1) {
						double curVal_p3 = cost_p3[i1_p3][j1_p3] - prices_p3[j1_p3];
						
						if (curVal_p3 > best_payoff_p3) {
							sec_payoff_p3 = best_payoff_p3;
							best_payoff_p3 = curVal_p3;
							best_obj_p3 = j1_p3;
							price_obj_p3 = prices_p3[j1_p3];
						} else if (curVal_p3 > sec_payoff_p3) {
							sec_payoff_p3 = curVal_p3;
						}
						
					}
					
					bid_i_p3.amount = price_obj_p3 + best_payoff_p3 - sec_payoff_p3 + epsilon_p3;
					bid_i_p3.object = best_obj_p3;
					val2_p3 = bid_i_p3;
					bids_split4_p3[i1_p3 - N_38] = val2_p3;
					val3_p3 = 1;
					ids_split4_p3[i1_p3 - N_38] = val3_p3;
				}
			}
			
			
			
		}
		
		
		
		
		
		
		
		EMX_Send(3, 0, 37, -1, bids_split4_p3, N_18 * sizeof(*bids_split4_p3));
		
		EMX_Send(3, 0, 30, -1, ids_split4_p3, N_18 * sizeof(*ids_split4_p3));
		
		
		
		
	}
}


extern void biddingPhase_p4(double epsilon_p4, int cost_p4[N][N], int assignment_p4[N], double prices_p4[N]) {
	size_t i2_p4;
	_Bool ids_split5_p4[N_18];
	size_t i1_p4;
	size_t j1_p4;
	
	for (i2_p4 = N_48; i2_p4 < N_58; i2_p4 = i2_p4 + 1) {
		_Bool val2_p4;
		
		val2_p4 = 0;
		ids_split5_p4[i2_p4 - N_48] = val2_p4;
	}
	
	{
		bid bids_split5_p4[N_18];
		
		
		
		
		for (i1_p4 = N_48; i1_p4 < N_58; i1_p4 = i1_p4 + 1) {
			
			
			
			if (assignment_p4[i1_p4] == (-1)) {
				bid bid_i_p4;
				
				bid_i_p4.bidder = i1_p4;
				
				{
					int best_obj_p4;
					double price_obj_p4;
					double best_payoff_p4 = -0x7fffffff;
					double sec_payoff_p4 = -0x7fffffff;
					struct bid val2_p4;
					_Bool val3_p4;
					
					for (j1_p4 = 0; j1_p4 < N; j1_p4 = j1_p4 + 1) {
						double curVal_p4 = cost_p4[i1_p4][j1_p4] - prices_p4[j1_p4];
						
						if (curVal_p4 > best_payoff_p4) {
							sec_payoff_p4 = best_payoff_p4;
							best_payoff_p4 = curVal_p4;
							best_obj_p4 = j1_p4;
							price_obj_p4 = prices_p4[j1_p4];
						} else if (curVal_p4 > sec_payoff_p4) {
							sec_payoff_p4 = curVal_p4;
						}
						
					}
					
					bid_i_p4.amount = price_obj_p4 + best_payoff_p4 - sec_payoff_p4 + epsilon_p4;
					bid_i_p4.object = best_obj_p4;
					val2_p4 = bid_i_p4;
					bids_split5_p4[i1_p4 - N_48] = val2_p4;
					val3_p4 = 1;
					ids_split5_p4[i1_p4 - N_48] = val3_p4;
				}
			}
			
			
			
			
		}
		
		
		
		
		
		
		
		EMX_Send(4, 0, 38, -1, bids_split5_p4, N_18 * sizeof(*bids_split5_p4));
		
		EMX_Send(4, 0, 31, -1, ids_split5_p4, N_18 * sizeof(*ids_split5_p4));
		
		
		
	}
}


extern void biddingPhase_p5(double epsilon_p5, int cost_p5[N][N], int assignment_p5[N], double prices_p5[N]) {
	size_t i2_p5;
	_Bool ids_split6_p5[N_18];
	size_t i1_p5;
	size_t j1_p5;
	
	for (i2_p5 = N_58; i2_p5 < N_68; i2_p5 = i2_p5 + 1) {
		_Bool val2_p5;
		
		val2_p5 = 0;
		ids_split6_p5[i2_p5 - N_58] = val2_p5;
	}
	
	{
		bid bids_split6_p5[N_18];
		
		
		
		
		
		for (i1_p5 = N_58; i1_p5 < N_68; i1_p5 = i1_p5 + 1) {
			
			
			if (assignment_p5[i1_p5] == (-1)) {
				bid bid_i_p5;
				
				bid_i_p5.bidder = i1_p5;
				
				{
					int best_obj_p5;
					double price_obj_p5;
					double best_payoff_p5 = -0x7fffffff;
					double sec_payoff_p5 = -0x7fffffff;
					struct bid val2_p5;
					_Bool val3_p5;
					
					for (j1_p5 = 0; j1_p5 < N; j1_p5 = j1_p5 + 1) {
						double curVal_p5 = cost_p5[i1_p5][j1_p5] - prices_p5[j1_p5];
						
						if (curVal_p5 > best_payoff_p5) {
							sec_payoff_p5 = best_payoff_p5;
							best_payoff_p5 = curVal_p5;
							best_obj_p5 = j1_p5;
							price_obj_p5 = prices_p5[j1_p5];
						} else if (curVal_p5 > sec_payoff_p5) {
							sec_payoff_p5 = curVal_p5;
						}
						
					}
					
					bid_i_p5.amount = price_obj_p5 + best_payoff_p5 - sec_payoff_p5 + epsilon_p5;
					bid_i_p5.object = best_obj_p5;
					val2_p5 = bid_i_p5;
					bids_split6_p5[i1_p5 - N_58] = val2_p5;
					val3_p5 = 1;
					ids_split6_p5[i1_p5 - N_58] = val3_p5;
				}
			}
			
			
			
			
			
		}
		
		
		
		
		
		
		
		EMX_Send(5, 0, 39, -1, bids_split6_p5, N_18 * sizeof(*bids_split6_p5));
		
		EMX_Send(5, 0, 32, -1, ids_split6_p5, N_18 * sizeof(*ids_split6_p5));
		
		
	}
}


extern void biddingPhase_p6(double epsilon_p6, int cost_p6[N][N], int assignment_p6[N], double prices_p6[N]) {
	size_t i2_p6;
	_Bool ids_split7_p6[N_18];
	size_t i1_p6;
	size_t j1_p6;
	
	for (i2_p6 = N_68; i2_p6 < N_78; i2_p6 = i2_p6 + 1) {
		_Bool val2_p6;
		
		val2_p6 = 0;
		ids_split7_p6[i2_p6 - N_68] = val2_p6;
	}
	
	{
		bid bids_split7_p6[N_18];
		
		
		
		
		
		
		for (i1_p6 = N_68; i1_p6 < N_78; i1_p6 = i1_p6 + 1) {
			
			if (assignment_p6[i1_p6] == (-1)) {
				bid bid_i_p6;
				
				bid_i_p6.bidder = i1_p6;
				
				{
					int best_obj_p6;
					double price_obj_p6;
					double best_payoff_p6 = -0x7fffffff;
					double sec_payoff_p6 = -0x7fffffff;
					struct bid val2_p6;
					_Bool val3_p6;
					
					for (j1_p6 = 0; j1_p6 < N; j1_p6 = j1_p6 + 1) {
						double curVal_p6 = cost_p6[i1_p6][j1_p6] - prices_p6[j1_p6];
						
						if (curVal_p6 > best_payoff_p6) {
							sec_payoff_p6 = best_payoff_p6;
							best_payoff_p6 = curVal_p6;
							best_obj_p6 = j1_p6;
							price_obj_p6 = prices_p6[j1_p6];
						} else if (curVal_p6 > sec_payoff_p6) {
							sec_payoff_p6 = curVal_p6;
						}
						
					}
					
					bid_i_p6.amount = price_obj_p6 + best_payoff_p6 - sec_payoff_p6 + epsilon_p6;
					bid_i_p6.object = best_obj_p6;
					val2_p6 = bid_i_p6;
					bids_split7_p6[i1_p6 - N_68] = val2_p6;
					val3_p6 = 1;
					ids_split7_p6[i1_p6 - N_68] = val3_p6;
				}
			}
			
			
			
			
			
			
		}
		
		
		
		
		
		
		
		EMX_Send(6, 0, 40, -1, bids_split7_p6, N_18 * sizeof(*bids_split7_p6));
		
		EMX_Send(6, 0, 33, -1, ids_split7_p6, N_18 * sizeof(*ids_split7_p6));
		
	}
}


extern void biddingPhase_p7(double epsilon_p7, int cost_p7[N][N], int assignment_p7[N], double prices_p7[N]) {
	size_t i2_p7;
	_Bool ids_split8_p7[N_18];
	size_t i1_p7;
	size_t j1_p7;
	
	for (i2_p7 = N_78; i2_p7 < N; i2_p7 = i2_p7 + 1) {
		_Bool val2_p7;
		
		val2_p7 = 0;
		ids_split8_p7[i2_p7 - N_78] = val2_p7;
	}
	
	{
		bid bids_split8_p7[N_18];
		
		
		
		
		
		
		
		for (i1_p7 = N_78; i1_p7 < N; i1_p7 = i1_p7 + 1) {
			if (assignment_p7[i1_p7] == (-1)) {
				bid bid_i_p7;
				
				bid_i_p7.bidder = i1_p7;
				
				{
					int best_obj_p7;
					double price_obj_p7;
					double best_payoff_p7 = -0x7fffffff;
					double sec_payoff_p7 = -0x7fffffff;
					struct bid val2_p7;
					_Bool val3_p7;
					
					for (j1_p7 = 0; j1_p7 < N; j1_p7 = j1_p7 + 1) {
						double curVal_p7 = cost_p7[i1_p7][j1_p7] - prices_p7[j1_p7];
						
						if (curVal_p7 > best_payoff_p7) {
							sec_payoff_p7 = best_payoff_p7;
							best_payoff_p7 = curVal_p7;
							best_obj_p7 = j1_p7;
							price_obj_p7 = prices_p7[j1_p7];
						} else if (curVal_p7 > sec_payoff_p7) {
							sec_payoff_p7 = curVal_p7;
						}
						
					}
					
					bid_i_p7.amount = price_obj_p7 + best_payoff_p7 - sec_payoff_p7 + epsilon_p7;
					bid_i_p7.object = best_obj_p7;
					val2_p7 = bid_i_p7;
					bids_split8_p7[i1_p7 - N_78] = val2_p7;
					val3_p7 = 1;
					ids_split8_p7[i1_p7 - N_78] = val3_p7;
				}
			}
			
			
			
			
			
			
			
		}
		
		
		
		
		
		
		
		EMX_Send(7, 0, 41, -1, bids_split8_p7, N_18 * sizeof(*bids_split8_p7));
		
		EMX_Send(7, 0, 34, -1, ids_split8_p7, N_18 * sizeof(*ids_split8_p7));
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
		
		while (sync_p0 = (epsilon_p0 > (1.0 / N)), EMX_SendSync(0, 1, 51, -1, sync_p0), EMX_SendSync(0, 2, 52, -1, sync_p0), EMX_SendSync(0, 3, 53, -1, sync_p0), EMX_SendSync(0, 4, 54, -1, sync_p0), EMX_SendSync(0, 5, 55, -1, sync_p0), EMX_SendSync(0, 6, 56, -1, sync_p0), EMX_SendSync(0, 7, 57, -1, sync_p0), sync_p0) {
			EMX_Send64F(0, 1, 27, -1, epsilon_p0);
			
			EMX_Send64F(0, 2, 26, -1, epsilon_p0);
			
			EMX_Send64F(0, 5, 25, -1, epsilon_p0);
			
			EMX_Send64F(0, 6, 24, -1, epsilon_p0);
			
			EMX_Send64F(0, 3, 23, -1, epsilon_p0);
			
			EMX_Send64F(0, 4, 22, -1, epsilon_p0);
			
			EMX_Send64F(0, 7, 21, -1, epsilon_p0);
			
			for (int i_p0 = 0; i_p0 < N; i_p0 = i_p0 + 1) {
				assignment_p0[i_p0] = -1;
				belong_p0[i_p0] = -1;
			}
			
			{
				int assignment_count_p0 = 0;
				
				while (sync_p0 = (assignment_count_p0 != N), EMX_SendSync(0, 1, 44, -1, sync_p0), EMX_SendSync(0, 2, 45, -1, sync_p0), EMX_SendSync(0, 3, 46, -1, sync_p0), EMX_SendSync(0, 4, 47, -1, sync_p0), EMX_SendSync(0, 5, 48, -1, sync_p0), EMX_SendSync(0, 6, 49, -1, sync_p0), EMX_SendSync(0, 7, 50, -1, sync_p0), sync_p0) {
					EMX_Send(0, 1, 20, -1, assignment_p0, N * sizeof(*assignment_p0));
					
					EMX_Send(0, 2, 19, -1, assignment_p0, N * sizeof(*assignment_p0));
					
					EMX_Send(0, 5, 18, -1, assignment_p0, N * sizeof(*assignment_p0));
					
					EMX_Send(0, 6, 17, -1, assignment_p0, N * sizeof(*assignment_p0));
					
					EMX_Send(0, 3, 16, -1, assignment_p0, N * sizeof(*assignment_p0));
					
					EMX_Send(0, 4, 15, -1, assignment_p0, N * sizeof(*assignment_p0));
					
					EMX_Send(0, 7, 14, -1, assignment_p0, N * sizeof(*assignment_p0));
					
					EMX_Send(0, 1, 13, -1, prices_p0, N * sizeof(*prices_p0));
					
					EMX_Send(0, 2, 12, -1, prices_p0, N * sizeof(*prices_p0));
					
					EMX_Send(0, 5, 11, -1, prices_p0, N * sizeof(*prices_p0));
					
					EMX_Send(0, 6, 10, -1, prices_p0, N * sizeof(*prices_p0));
					
					EMX_Send(0, 3, 9, -1, prices_p0, N * sizeof(*prices_p0));
					
					EMX_Send(0, 4, 8, -1, prices_p0, N * sizeof(*prices_p0));
					
					EMX_Send(0, 7, 7, -1, prices_p0, N * sizeof(*prices_p0));
					
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
							
							assignment_count_p0 = EMX_Recv32(1, 0, 42, -1);
							
							for (size_t i_p0 = 0; i_p0 < N; i_p0 = i_p0 + 1) {
								if (assignment_p0[i_p0] != (-1)) {
									assignment_count_p0 = assignment_count_p0 + 1;
								}
							}
						}
					}
				}
			}
			
			epsilon_p0 = EMX_Recv64F(1, 0, 43, -1);
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
	int assignment_p1[N];
	double prices_p1[N];
	double epsilon_p1;
	int iter_p1 = 1;
	
	while (EMX_RecvSync(0, 1, 51, -1)) {
		epsilon_p1 = EMX_Recv64F(0, 1, 27, -1);
		
		{
			int assignment_count_p1 = 0;
			
			while (EMX_RecvSync(0, 1, 44, -1)) {
				EMX_Recv(0, 1, 20, -1, assignment_p1, N * sizeof(*assignment_p1));
				
				EMX_Recv(0, 1, 13, -1, prices_p1, N * sizeof(*prices_p1));
				
				biddingPhase_p1(epsilon_p1, cost_p1, assignment_p1, prices_p1);
				
				assignment_count_p1 = 0;
				
				EMX_Send32(1, 0, 42, -1, assignment_count_p1);
				
				iter_p1 = iter_p1 + 1;
			}
			
			epsilon_p1 = epsilon_p1 * 0.25;
		}
		EMX_Send64F(1, 0, 43, -1, epsilon_p1);
	}
}


extern void auction_p2(int cost_p2[N][N]) {
	int cost_p22[N][N];
	int assignment_p2[N];
	double prices_p2[N];
	double epsilon_p2;
	
	while (EMX_RecvSync(0, 2, 52, -1)) {
		epsilon_p2 = EMX_Recv64F(0, 2, 26, -1);
		
		while (EMX_RecvSync(0, 2, 45, -1)) {
			EMX_Recv(0, 2, 19, -1, assignment_p2, N * sizeof(*assignment_p2));
			
			EMX_Recv(0, 2, 12, -1, prices_p2, N * sizeof(*prices_p2));
			
			biddingPhase_p2(epsilon_p2, cost_p2, assignment_p2, prices_p2);
			
		}
	}
}


extern void auction_p3(int cost_p3[N][N]) {
	int cost_p32[N][N];
	int assignment_p3[N];
	double prices_p3[N];
	double epsilon_p3;
	
	while (EMX_RecvSync(0, 3, 53, -1)) {
		epsilon_p3 = EMX_Recv64F(0, 3, 23, -1);
		
		while (EMX_RecvSync(0, 3, 46, -1)) {
			EMX_Recv(0, 3, 16, -1, assignment_p3, N * sizeof(*assignment_p3));
			
			EMX_Recv(0, 3, 9, -1, prices_p3, N * sizeof(*prices_p3));
			
			biddingPhase_p3(epsilon_p3, cost_p3, assignment_p3, prices_p3);
			
		}
	}
}


extern void auction_p4(int cost_p4[N][N]) {
	int cost_p42[N][N];
	int assignment_p4[N];
	double prices_p4[N];
	double epsilon_p4;
	
	while (EMX_RecvSync(0, 4, 54, -1)) {
		epsilon_p4 = EMX_Recv64F(0, 4, 22, -1);
		
		while (EMX_RecvSync(0, 4, 47, -1)) {
			EMX_Recv(0, 4, 15, -1, assignment_p4, N * sizeof(*assignment_p4));
			
			EMX_Recv(0, 4, 8, -1, prices_p4, N * sizeof(*prices_p4));
			
			biddingPhase_p4(epsilon_p4, cost_p4, assignment_p4, prices_p4);
			
		}
	}
}


extern void auction_p5(int cost_p5[N][N]) {
	int cost_p52[N][N];
	double prices_p5[N];
	int assignment_p5[N];
	double epsilon_p5;
	
	while (EMX_RecvSync(0, 5, 55, -1)) {
		epsilon_p5 = EMX_Recv64F(0, 5, 25, -1);
		
		while (EMX_RecvSync(0, 5, 48, -1)) {
			EMX_Recv(0, 5, 18, -1, assignment_p5, N * sizeof(*assignment_p5));
			
			EMX_Recv(0, 5, 11, -1, prices_p5, N * sizeof(*prices_p5));
			
			biddingPhase_p5(epsilon_p5, cost_p5, assignment_p5, prices_p5);
			
		}
	}
}


extern void auction_p6(int cost_p6[N][N]) {
	int cost_p62[N][N];
	int assignment_p6[N];
	double prices_p6[N];
	double epsilon_p6;
	
	while (EMX_RecvSync(0, 6, 56, -1)) {
		epsilon_p6 = EMX_Recv64F(0, 6, 24, -1);
		
		while (EMX_RecvSync(0, 6, 49, -1)) {
			EMX_Recv(0, 6, 17, -1, assignment_p6, N * sizeof(*assignment_p6));
			
			EMX_Recv(0, 6, 10, -1, prices_p6, N * sizeof(*prices_p6));
			
			biddingPhase_p6(epsilon_p6, cost_p6, assignment_p6, prices_p6);
			
		}
	}
}


extern void auction_p7(int cost_p7[N][N]) {
	int cost_p72[N][N];
	double prices_p7[N];
	int assignment_p7[N];
	double epsilon_p7;
	
	while (EMX_RecvSync(0, 7, 57, -1)) {
		epsilon_p7 = EMX_Recv64F(0, 7, 21, -1);
		
		while (EMX_RecvSync(0, 7, 50, -1)) {
			EMX_Recv(0, 7, 14, -1, assignment_p7, N * sizeof(*assignment_p7));
			
			EMX_Recv(0, 7, 7, -1, prices_p7, N * sizeof(*prices_p7));
			
			biddingPhase_p7(epsilon_p7, cost_p7, assignment_p7, prices_p7);
			
		}
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
	f = fopen("auc_emmtrix_8.txt", "a");
	fprintf(f, "Auction Parallel Emmtrix(8 Cores): \n");
	fprintf(f, "Size\t\t\t\tCost\t\t\t\tTotal Time in s\t\t\tTotal CPU time in ms\n");
	fclose(f);

	f_mean = fopen("auc_emmtrix_8_mean.txt", "a");
	fprintf(f_mean, "Auction Parallel Emmtrix (8 Cores, %d runs): \n", R);
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
			
			EMX_Send(0, 7, 0, -1, cost_p0, N * sizeof(*cost_p0));
			
			EMX_Send(0, 4, 1, -1, cost_p0, N * sizeof(*cost_p0));
			
			EMX_Send(0, 3, 2, -1, cost_p0, N * sizeof(*cost_p0));
			
			EMX_Send(0, 6, 3, -1, cost_p0, N * sizeof(*cost_p0));
			
			EMX_Send(0, 5, 4, -1, cost_p0, N * sizeof(*cost_p0));
			
			EMX_Send(0, 2, 5, -1, cost_p0, N * sizeof(*cost_p0));
			
			EMX_Send(0, 1, 6, -1, cost_p0, N * sizeof(*cost_p0));
			
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
			f = fopen("auc_emmtrix_8.txt", "a");
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
	f_mean = fopen("auc_emmtrix_8_mean.txt", "a");
	fprintf(f_mean, "%d\t\t\t\t%f\t\t\t\t%f\t\t\t\t%f\t\t\t\t%f\n", N, mean_timing / 1000.0, mean_time, median_timing / 1000.0, median_time);
	fclose(f_mean);
	
	return 0;
}


void main_p1() {
	time_t callarg_p1;
	
	for (int r_p1 = 0; r_p1 < R; r_p1 = r_p1 + 1) {
		int cost_p1[N][N];
		
		EMX_Recv(0, 1, 6, -1, cost_p1, N * sizeof(*cost_p1));
		
		auction_p1(cost_p1);
		
		callarg_p1 = time((void *)0);
		
		srand(callarg_p1);
	}
}


void main_p2() {
	for (int r_p2 = 0; r_p2 < R; r_p2 = r_p2 + 1) {
		int cost_p2[N][N];
		
		EMX_Recv(0, 2, 5, -1, cost_p2, N * sizeof(*cost_p2));
		
		auction_p2(cost_p2);
	}
}


void main_p3() {
	for (int r_p3 = 0; r_p3 < R; r_p3 = r_p3 + 1) {
		int cost_p3[N][N];
		
		EMX_Recv(0, 3, 2, -1, cost_p3, N * sizeof(*cost_p3));
		
		auction_p3(cost_p3);
	}
}


void main_p4() {
	for (int r_p4 = 0; r_p4 < R; r_p4 = r_p4 + 1) {
		int cost_p4[N][N];
		
		EMX_Recv(0, 4, 1, -1, cost_p4, N * sizeof(*cost_p4));
		
		auction_p4(cost_p4);
	}
}


void main_p5() {
	for (int r_p5 = 0; r_p5 < R; r_p5 = r_p5 + 1) {
		int cost_p5[N][N];
		
		EMX_Recv(0, 5, 4, -1, cost_p5, N * sizeof(*cost_p5));
		
		auction_p5(cost_p5);
	}
}


void main_p6() {
	for (int r_p6 = 0; r_p6 < R; r_p6 = r_p6 + 1) {
		int cost_p6[N][N];
		
		EMX_Recv(0, 6, 3, -1, cost_p6, N * sizeof(*cost_p6));
		
		auction_p6(cost_p6);
	}
}


void main_p7() {
	for (int r_p7 = 0; r_p7 < R; r_p7 = r_p7 + 1) {
		int cost_p7[N][N];
		
		EMX_Recv(0, 7, 0, -1, cost_p7, N * sizeof(*cost_p7));
		
		auction_p7(cost_p7);
	}
}

