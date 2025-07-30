#include <stdio.h>
#include "_emx_main.h"
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

#define inf INT_MAX
#define N 100
#define N_50 50 

#define R 50 

const int n = N;
int **cost;
_Bool verbose = 0;
_Bool maximum = 0;

int optimality_check(int n, _Bool cov_row[N], int ass_row[N]) {
	size_t i1;
	int match_count = 0;
	
	for (i1 = 0u; i1 < N; i1 = i1 + 1) {
		if (ass_row[i1] != (-1)) {
			cov_row[i1] = 1;
			match_count = match_count + 1;
		}
	}
	
	return match_count;
}


void forward_bfs(int cost[N][N], int n, int f_in[N], int f_in_size, _Bool active[N], _Bool reverse[N], _Bool visited[N], int ass_col[N], _Bool cov_row[N], _Bool cov_col[N], double dual_row[N], double dual_col[N], double slack[N], int prv_row[N], int prv_col[N]) {
	size_t j1;
	size_t x1;
	
	for (j1 = 0u; j1 < N; j1 = j1 + 1) {
		if (!cov_col[j1]) {
			for (x1 = 0u; x1 < f_in_size; x1 = x1 + 1) {
				int i = f_in[x1];
				
				if (slack[j1] > (cost[i][j1] - dual_row[i] - dual_col[j1])) {
					slack[j1] = cost[i][j1] - dual_row[i] - dual_col[j1];
					prv_col[j1] = i;
				}
				
				{
					int i_new = ass_col[j1];
					
					if (slack[j1] == 0) {
						if (i_new != (-1)) {
							prv_row[i_new] = j1;
							cov_row[i_new] = 0;
							cov_col[j1] = 1;
							
							if (!active[i_new]) {
								active[i_new] = 1;
							}
						} else {
							reverse[j1] = 1;
						}
					}
					
					visited[i] = 1;
				}
			}
		}
	}
}


void reverse_bfs(int f_rev[N], int f_rev_size, _Bool augment[N], int suc_row[N], int suc_col[N], int prv_row[N], int prv_col[N]) {
	size_t x1;
	
	for (x1 = 0u; x1 < f_rev_size; x1 = x1 + 1) {
		int j = f_rev[x1];
		int r_cur = -1;
		int c_cur = j;
		
		while (c_cur != (-1)) {
			suc_col[c_cur] = r_cur;
			r_cur = prv_col[c_cur];
			suc_row[r_cur] = c_cur;
			c_cur = prv_row[r_cur];
		}
		
		augment[r_cur] = 1;
	}
}


void augment_pass(int f_aug[N], int f_aug_size, int ass_row[N], int ass_col[N], int suc_row[N], int suc_col[N]) {
	size_t x1;
	
	for (x1 = 0u; x1 < f_aug_size; x1 = x1 + 1) {
		int i = f_aug[x1];
		int r_cur = i;
		int c_cur = -1;
		
		while (r_cur != (-1)) {
			c_cur = suc_row[r_cur];
			ass_row[r_cur] = c_cur;
			ass_col[c_cur] = r_cur;
			r_cur = suc_col[c_cur];
		}
	}
}


int compare(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}


float findMedian_duplicate2(double arr[R], int n) {
	int (*callarg)(const void *, const void *);
	
	callarg = compare;
	
	qsort(arr, n, sizeof(int), callarg);
	
	if ((n % 2) == 0) {
		return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
	} else {
		return arr[n / 2];
	}
}


extern void init_potentials_p0(int cost_p0[N][N], int n_p0, double dual_row_p0[N], double dual_col_p0[N]) {
	size_t i1_p0;
	double d_row_split1_p0[N_50];
	size_t j1_p0;
	size_t i3_p0;
	double d_row_split2_p0[N_50];
	size_t j2_p0;
	double d_col_split1_p0[N_50];
	size_t i2_p0;
	size_t i4_p0;
	double d_col_split2_p0[N_50];
	
	for (i1_p0 = 0u; i1_p0 < N_50; i1_p0 = i1_p0 + 1) {
		double temp_p0 = 0x7fffffff;
		double val2_p0;
		
		for (j1_p0 = 0u; j1_p0 < N; j1_p0 = j1_p0 + 1) {
			if (temp_p0 > ((double)cost_p0[i1_p0][j1_p0])) {
				temp_p0 = (double)cost_p0[i1_p0][j1_p0];
			}
		}
		
		val2_p0 = temp_p0;
		d_row_split1_p0[i1_p0 - 0] = val2_p0;
	}
	
	for (i1_p0 = N_50; i1_p0 < N; i1_p0 = i1_p0 + 1) {
		for (j1_p0 = 0u; j1_p0 < N; j1_p0 = j1_p0 + 1) {
		}
	}
	
	for (i3_p0 = 0u; i3_p0 < N_50; i3_p0 = i3_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_row_split1_p0[i3_p0 - 0];
		dual_row_p0[i3_p0] = val2_p0;
	}
	
	EMX_Recv(1, 0, 18, -1, d_row_split2_p0, N_50 * sizeof(*d_row_split2_p0));
	
	for (i3_p0 = N_50; i3_p0 < N; i3_p0 = i3_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_row_split2_p0[i3_p0 - N_50];
		dual_row_p0[i3_p0] = val2_p0;
	}
	
	for (j2_p0 = 0u; j2_p0 < N_50; j2_p0 = j2_p0 + 1) {
		double temp_p0 = 0x7fffffff;
		double val2_p0;
		
		for (i2_p0 = 0u; i2_p0 < N; i2_p0 = i2_p0 + 1) {
			if (temp_p0 > (cost_p0[i2_p0][j2_p0] - dual_row_p0[i2_p0])) {
				temp_p0 = cost_p0[i2_p0][j2_p0] - dual_row_p0[i2_p0];
			}
		}
		
		val2_p0 = temp_p0;
		d_col_split1_p0[j2_p0 - 0] = val2_p0;
	}
	
	EMX_Send(0, 1, 17, -1, dual_row_p0, N * sizeof(*dual_row_p0));
	
	for (j2_p0 = N_50; j2_p0 < N; j2_p0 = j2_p0 + 1) {
		for (i2_p0 = 0u; i2_p0 < N; i2_p0 = i2_p0 + 1) {
		}
	}
	
	for (i4_p0 = 0u; i4_p0 < N_50; i4_p0 = i4_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_col_split1_p0[i4_p0 - 0];
		dual_col_p0[i4_p0] = val2_p0;
	}
	
	EMX_Recv(1, 0, 19, -1, d_col_split2_p0, N_50 * sizeof(*d_col_split2_p0));
	
	for (i4_p0 = N_50; i4_p0 < N; i4_p0 = i4_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_col_split2_p0[i4_p0 - N_50];
		dual_col_p0[i4_p0] = val2_p0;
	}
}


extern void init_potentials_p1(int cost_p1[N][N]) {
	double dual_row_p1[N];
	size_t i1_p1;
	double d_row_split2_p1[N_50];
	size_t j1_p1;
	size_t j2_p1;
	double d_col_split2_p1[N_50];
	size_t i2_p1;
	
	for (i1_p1 = N_50; i1_p1 < N; i1_p1 = i1_p1 + 1) {
		double temp_p1 = 0x7fffffff;
		double val2_p1;
		
		
		
		
		
		
		
		for (j1_p1 = 0u; j1_p1 < N; j1_p1 = j1_p1 + 1) {
			
			
			
			
			
			
			if (temp_p1 > ((double)cost_p1[i1_p1][j1_p1])) {
				temp_p1 = (double)cost_p1[i1_p1][j1_p1];
			}
			
		}
		
		val2_p1 = temp_p1;
		d_row_split2_p1[i1_p1 - N_50] = val2_p1;
		
	}
	
	EMX_Send(1, 0, 18, -1, d_row_split2_p1, N_50 * sizeof(*d_row_split2_p1));
	
	EMX_Recv(0, 1, 17, -1, dual_row_p1, N * sizeof(*dual_row_p1));
	
	for (j2_p1 = N_50; j2_p1 < N; j2_p1 = j2_p1 + 1) {
		double temp_p1 = 0x7fffffff;
		double val2_p1;
		
		
		
		
		
		
		
		for (i2_p1 = 0u; i2_p1 < N; i2_p1 = i2_p1 + 1) {
			
			
			
			
			
			
			if (temp_p1 > (cost_p1[i2_p1][j2_p1] - dual_row_p1[i2_p1])) {
				temp_p1 = cost_p1[i2_p1][j2_p1] - dual_row_p1[i2_p1];
			}
			
		}
		
		val2_p1 = temp_p1;
		d_col_split2_p1[j2_p1 - N_50] = val2_p1;
		
	}
	
	EMX_Send(1, 0, 19, -1, d_col_split2_p1, N_50 * sizeof(*d_col_split2_p1));
}


extern void update_pass_p2(double theta_p2, _Bool cov_col_p2[N], double dual_row_p2[N], double dual_col_p2[N], double slack_p2[N]) {
	double d_row_split1_p2[N_50];
	size_t k1_p2;
	
	for (int i_p2 = 0; i_p2 < N_50; i_p2 = i_p2 + 1) {
		double val2_p2;
		
		val2_p2 = dual_row_p2[i_p2];
		d_row_split1_p2[i_p2 - 0] = val2_p2;
	}
	
	EMX_Send(2, 1, 38, -1, d_row_split1_p2, N_50 * sizeof(*d_row_split1_p2));
	
	{
		double d_col_split1_p2[N_50];
		
		for (int i_p2 = 0; i_p2 < N_50; i_p2 = i_p2 + 1) {
			double val2_p2;
			
			val2_p2 = dual_col_p2[i_p2];
			d_col_split1_p2[i_p2 - 0] = val2_p2;
		}
		
		{
			double sl_split1_p2[N_50];
			
			for (int i_p2 = 0; i_p2 < N_50; i_p2 = i_p2 + 1) {
				double val2_p2;
				
				val2_p2 = slack_p2[i_p2];
				sl_split1_p2[i_p2 - 0] = val2_p2;
			}
			
			EMX_Send(2, 3, 42, -1, sl_split1_p2, N_50 * sizeof(*sl_split1_p2));
			
			for (k1_p2 = 0u; k1_p2 < N_50; k1_p2 = k1_p2 + 1) {
				
				if (!cov_col_p2[k1_p2]) {
					double val22_p2;
					double val3_p2;
					
					val22_p2 = d_col_split1_p2[k1_p2 - 0];
					val3_p2 = val22_p2 + theta_p2 / 2;
					d_col_split1_p2[k1_p2 - 0] = val3_p2;
				} else {
					double val22_p2;
					double val3_p2;
					
					val22_p2 = d_col_split1_p2[k1_p2 - 0];
					val3_p2 = val22_p2 - theta_p2 / 2;
					d_col_split1_p2[k1_p2 - 0] = val3_p2;
				}
				
			}
			
			
			EMX_Send(2, 0, 40, -1, d_col_split1_p2, N_50 * sizeof(*d_col_split1_p2));
			
		}
	}
}


extern void update_pass_p3(double theta_p3, double dual_row_p3[N], double dual_col_p3[N], double slack_p3[N], int prv_col_p3[N]) {
	_Bool sync70_p3;
	_Bool sync71_p3;
	double d_row_split2_p3[N_50];
	size_t k1_p3;
	
	for (int i_p3 = N_50; i_p3 < N; i_p3 = i_p3 + 1) {
		double val2_p3;
		
		val2_p3 = dual_row_p3[i_p3];
		d_row_split2_p3[i_p3 - N_50] = val2_p3;
	}
	
	EMX_Send(3, 4, 39, -1, d_row_split2_p3, N_50 * sizeof(*d_row_split2_p3));
	
	{
		double d_col_split2_p3[N_50];
		
		for (int i_p3 = N_50; i_p3 < N; i_p3 = i_p3 + 1) {
			double val2_p3;
			
			val2_p3 = dual_col_p3[i_p3];
			d_col_split2_p3[i_p3 - N_50] = val2_p3;
		}
		
		EMX_Send(3, 5, 41, -1, d_col_split2_p3, N_50 * sizeof(*d_col_split2_p3));
		
		{
			double sl_split2_p3[N_50];
			double sl_split1_p3[N_50];
			
			for (int i_p3 = N_50; i_p3 < N; i_p3 = i_p3 + 1) {
				double val2_p3;
				
				val2_p3 = slack_p3[i_p3];
				sl_split2_p3[i_p3 - N_50] = val2_p3;
			}
			
			EMX_Send(3, 6, 43, -1, sl_split2_p3, N_50 * sizeof(*sl_split2_p3));
			
			EMX_Recv(2, 3, 42, -1, sl_split1_p3, N_50 * sizeof(*sl_split1_p3));
			
			{
				int act_split1_p3[N_50];
				
				for (k1_p3 = 0u; k1_p3 < N_50; k1_p3 = k1_p3 + 1) {
					EMX_Recv(1, 3, 44, -1, act_split1_p3, N_50 * sizeof(*act_split1_p3));
					
					{
						double val2_p3;
						int cond_p3;
						
						
						
						val2_p3 = sl_split1_p3[k1_p3 - 0];
						cond_p3 = (val2_p3 > 0);
						
						sync71_p3 = cond_p3;
						
						EMX_SendSync(3, 1, 71, -1, sync71_p3);
						
						if (cond_p3, sync71_p3) {
							double val32_p3;
							double val4_p3;
							double val3_p3;
							int cond2_p3;
							
							val32_p3 = sl_split1_p3[k1_p3 - 0];
							val4_p3 = val32_p3 - theta_p3;
							sl_split1_p3[k1_p3 - 0] = val4_p3;
							val3_p3 = sl_split1_p3[k1_p3 - 0];
							cond2_p3 = (val3_p3 == 0);
							
							sync70_p3 = cond2_p3;
							
							EMX_SendSync(3, 1, 70, -1, sync70_p3);
							
							if (cond2_p3, sync70_p3) {
								int val5_p3;
								
								val5_p3 = prv_col_p3[k1_p3];
								act_split1_p3[k1_p3 - 0] = val5_p3;
								
								EMX_Send(3, 1, 49, -1, act_split1_p3, N_50 * sizeof(*act_split1_p3));
							}
						}
					}
				}
				
				
				EMX_Send(3, 0, 47, -1, sl_split1_p3, N_50 * sizeof(*sl_split1_p3));
				
			}
		}
	}
}


extern void update_pass_p1(double theta_p1, _Bool cov_row_p1[N]) {
	_Bool sync74_p1;
	_Bool sync75_p1;
	_Bool active_p1[N];
	size_t k1_p1;
	double d_row_split1_p1[N_50];
	
	EMX_Recv(2, 1, 38, -1, d_row_split1_p1, N_50 * sizeof(*d_row_split1_p1));
	
	{
		int act_split1_p1[N_50];
		int act_split2_p1[N_50];
		
		for (int i_p1 = 0; i_p1 < N_50; i_p1 = i_p1 + 1) {
			int val2_p1;
			
			val2_p1 = -1;
			act_split1_p1[i_p1 - 0] = val2_p1;
		}
		
		for (k1_p1 = 0u; k1_p1 < N_50; k1_p1 = k1_p1 + 1) {
			EMX_Send(1, 3, 44, -1, act_split1_p1, N_50 * sizeof(*act_split1_p1));
			
			
			
			
			
			
			
			
			
			
			
			
			
			if (!cov_row_p1[k1_p1]) {
				double val22_p1;
				double val3_p1;
				
				val22_p1 = d_row_split1_p1[k1_p1 - 0];
				val3_p1 = val22_p1 + theta_p1 / 2;
				d_row_split1_p1[k1_p1 - 0] = val3_p1;
			} else {
				double val22_p1;
				double val3_p1;
				
				val22_p1 = d_row_split1_p1[k1_p1 - 0];
				val3_p1 = val22_p1 - theta_p1 / 2;
				d_row_split1_p1[k1_p1 - 0] = val3_p1;
			}
			
			
			if (EMX_RecvSync(3, 1, 71, -1)) {
				if (EMX_RecvSync(3, 1, 70, -1)) {
					EMX_Recv(3, 1, 49, -1, act_split1_p1, N_50 * sizeof(*act_split1_p1));
				}
			}
			
			
			
		}
		
		
		EMX_Send(1, 0, 48, -1, d_row_split1_p1, N_50 * sizeof(*d_row_split1_p1));
		
		for (int i_p1 = 0; i_p1 < N_50; i_p1 = i_p1 + 1) {
			int val5_p1;
			int cond_p1;
			
			val5_p1 = act_split1_p1[i_p1 - 0];
			cond_p1 = (val5_p1 != (-1));
			
			EMX_Recv(0, 1, 36, -1, active_p1, N * sizeof(*active_p1));
			
			sync74_p1 = cond_p1;
			
			EMX_SendSync(1, 0, 74, -1, sync74_p1);
			
			if (cond_p1, sync74_p1) {
				int val6_p1;
				int tmp_p1;
				
				val6_p1 = act_split1_p1[i_p1 - 0];
				tmp_p1 = val6_p1;
				active_p1[tmp_p1] = 1;
				
				EMX_Send(1, 0, 59, -1, active_p1, N * sizeof(*active_p1));
			}
		}
		
		EMX_Recv(4, 1, 50, -1, act_split2_p1, N_50 * sizeof(*act_split2_p1));
		
		for (int i_p1 = N_50; i_p1 < N; i_p1 = i_p1 + 1) {
			int val5_p1;
			int cond_p1;
			
			val5_p1 = act_split2_p1[i_p1 - N_50];
			cond_p1 = (val5_p1 != (-1));
			
			EMX_Recv(0, 1, 37, -1, active_p1, N * sizeof(*active_p1));
			
			sync75_p1 = cond_p1;
			
			EMX_SendSync(1, 0, 75, -1, sync75_p1);
			
			if (cond_p1, sync75_p1) {
				int val6_p1;
				int tmp_p1;
				
				val6_p1 = act_split2_p1[i_p1 - N_50];
				tmp_p1 = val6_p1;
				active_p1[tmp_p1] = 1;
				
				EMX_Send(1, 0, 60, -1, active_p1, N * sizeof(*active_p1));
			}
		}
	}
}


extern void update_pass_p0(int n_p0, _Bool active_p0[N], double dual_row_p0[N], double dual_col_p0[N], double slack_p0[N]) {
	double d_row_split1_p0[N_50];
	double d_row_split2_p0[N_50];
	size_t k1_p0;
	double d_col_split1_p0[N_50];
	double d_col_split2_p0[N_50];
	double sl_split1_p0[N_50];
	double sl_split2_p0[N_50];
	
	for (k1_p0 = 0u; k1_p0 < N_50; k1_p0 = k1_p0 + 1) {
		
		
	}
	
	for (k1_p0 = N_50; k1_p0 < N; k1_p0 = k1_p0 + 1) {
		
		
	}
	
	EMX_Recv(1, 0, 48, -1, d_row_split1_p0, N_50 * sizeof(*d_row_split1_p0));
	
	EMX_Recv(3, 0, 47, -1, sl_split1_p0, N_50 * sizeof(*sl_split1_p0));
	
	EMX_Recv(2, 0, 40, -1, d_col_split1_p0, N_50 * sizeof(*d_col_split1_p0));
	
	for (int i_p0 = 0; i_p0 < N_50; i_p0 = i_p0 + 1) {
		double val2_p0;
		double val3_p0;
		double val4_p0;
		
		
		
		
		
		
		
		val2_p0 = d_row_split1_p0[i_p0 - 0];
		dual_row_p0[i_p0] = val2_p0;
		val3_p0 = d_col_split1_p0[i_p0 - 0];
		dual_col_p0[i_p0] = val3_p0;
		val4_p0 = sl_split1_p0[i_p0 - 0];
		slack_p0[i_p0] = val4_p0;
		
		EMX_Send(0, 1, 36, -1, active_p0, N * sizeof(*active_p0));
		
		if (EMX_RecvSync(1, 0, 74, -1)) {
			EMX_Recv(1, 0, 59, -1, active_p0, N * sizeof(*active_p0));
		}
		
	}
	
	EMX_Recv(4, 0, 56, -1, d_row_split2_p0, N_50 * sizeof(*d_row_split2_p0));
	
	EMX_Recv(5, 0, 55, -1, d_col_split2_p0, N_50 * sizeof(*d_col_split2_p0));
	
	EMX_Recv(6, 0, 54, -1, sl_split2_p0, N_50 * sizeof(*sl_split2_p0));
	
	for (int i_p0 = N_50; i_p0 < N; i_p0 = i_p0 + 1) {
		double val2_p0;
		double val3_p0;
		double val4_p0;
		
		
		
		
		
		
		
		val2_p0 = d_row_split2_p0[i_p0 - N_50];
		dual_row_p0[i_p0] = val2_p0;
		val3_p0 = d_col_split2_p0[i_p0 - N_50];
		dual_col_p0[i_p0] = val3_p0;
		val4_p0 = sl_split2_p0[i_p0 - N_50];
		slack_p0[i_p0] = val4_p0;
		
		EMX_Send(0, 1, 37, -1, active_p0, N * sizeof(*active_p0));
		
		if (EMX_RecvSync(1, 0, 75, -1)) {
			EMX_Recv(1, 0, 60, -1, active_p0, N * sizeof(*active_p0));
		}
		
	}
}


extern void update_pass_p4(double theta_p4, _Bool cov_row_p4[N]) {
	size_t k1_p4;
	double d_row_split2_p4[N_50];
	
	EMX_Recv(3, 4, 39, -1, d_row_split2_p4, N_50 * sizeof(*d_row_split2_p4));
	
	{
		int act_split2_p4[N_50];
		
		
		for (int i_p4 = N_50; i_p4 < N; i_p4 = i_p4 + 1) {
			int val2_p4;
			
			val2_p4 = -1;
			act_split2_p4[i_p4 - N_50] = val2_p4;
		}
		
		for (k1_p4 = N_50; k1_p4 < N; k1_p4 = k1_p4 + 1) {
			EMX_Send(4, 6, 51, -1, act_split2_p4, N_50 * sizeof(*act_split2_p4));
			
			
			
			
			if (!cov_row_p4[k1_p4]) {
				double val22_p4;
				double val3_p4;
				
				val22_p4 = d_row_split2_p4[k1_p4 - N_50];
				val3_p4 = val22_p4 + theta_p4 / 2;
				d_row_split2_p4[k1_p4 - N_50] = val3_p4;
			} else {
				double val22_p4;
				double val3_p4;
				
				val22_p4 = d_row_split2_p4[k1_p4 - N_50];
				val3_p4 = val22_p4 - theta_p4 / 2;
				d_row_split2_p4[k1_p4 - N_50] = val3_p4;
			}
			
			
			if (EMX_RecvSync(6, 4, 73, -1)) {
				if (EMX_RecvSync(6, 4, 72, -1)) {
					EMX_Recv(6, 4, 57, -1, act_split2_p4, N_50 * sizeof(*act_split2_p4));
				}
			}
			
			
			
			
			
			
			
			
			
			
			
			
		}
		
		EMX_Send(4, 0, 56, -1, d_row_split2_p4, N_50 * sizeof(*d_row_split2_p4));
		
		EMX_Send(4, 1, 50, -1, act_split2_p4, N_50 * sizeof(*act_split2_p4));
	}
}


extern void update_pass_p5(double theta_p5, _Bool cov_col_p5[N]) {
	size_t k1_p5;
	double d_col_split2_p5[N_50];
	
	EMX_Recv(3, 5, 41, -1, d_col_split2_p5, N_50 * sizeof(*d_col_split2_p5));
	
	
	for (k1_p5 = N_50; k1_p5 < N; k1_p5 = k1_p5 + 1) {
		
		if (!cov_col_p5[k1_p5]) {
			double val22_p5;
			double val3_p5;
			
			val22_p5 = d_col_split2_p5[k1_p5 - N_50];
			val3_p5 = val22_p5 + theta_p5 / 2;
			d_col_split2_p5[k1_p5 - N_50] = val3_p5;
		} else {
			double val22_p5;
			double val3_p5;
			
			val22_p5 = d_col_split2_p5[k1_p5 - N_50];
			val3_p5 = val22_p5 - theta_p5 / 2;
			d_col_split2_p5[k1_p5 - N_50] = val3_p5;
		}
		
	}
	
	EMX_Send(5, 0, 55, -1, d_col_split2_p5, N_50 * sizeof(*d_col_split2_p5));
	
}


extern void update_pass_p6(double theta_p6, int prv_col_p6[N]) {
	_Bool sync72_p6;
	_Bool sync73_p6;
	size_t k1_p6;
	double sl_split2_p6[N_50];
	
	EMX_Recv(3, 6, 43, -1, sl_split2_p6, N_50 * sizeof(*sl_split2_p6));
	
	{
		int act_split2_p6[N_50];
		
		
		for (k1_p6 = N_50; k1_p6 < N; k1_p6 = k1_p6 + 1) {
			EMX_Recv(4, 6, 51, -1, act_split2_p6, N_50 * sizeof(*act_split2_p6));
			
			{
				double val2_p6;
				int cond_p6;
				
				
				
				val2_p6 = sl_split2_p6[k1_p6 - N_50];
				cond_p6 = (val2_p6 > 0);
				
				sync73_p6 = cond_p6;
				
				EMX_SendSync(6, 4, 73, -1, sync73_p6);
				
				if (cond_p6, sync73_p6) {
					double val32_p6;
					double val4_p6;
					double val3_p6;
					int cond2_p6;
					
					val32_p6 = sl_split2_p6[k1_p6 - N_50];
					val4_p6 = val32_p6 - theta_p6;
					sl_split2_p6[k1_p6 - N_50] = val4_p6;
					val3_p6 = sl_split2_p6[k1_p6 - N_50];
					cond2_p6 = (val3_p6 == 0);
					
					sync72_p6 = cond2_p6;
					
					EMX_SendSync(6, 4, 72, -1, sync72_p6);
					
					if (cond2_p6, sync72_p6) {
						int val5_p6;
						
						val5_p6 = prv_col_p6[k1_p6];
						act_split2_p6[k1_p6 - N_50] = val5_p6;
						
						EMX_Send(6, 4, 57, -1, act_split2_p6, N_50 * sizeof(*act_split2_p6));
					}
				}
			}
		}
		
		EMX_Send(6, 0, 54, -1, sl_split2_p6, N_50 * sizeof(*sl_split2_p6));
		
	}
}


extern _Bool augmenting_path_search_p0(int cost_p0[N][N], int n_p0, _Bool active_p0[N], int ass_row_p0[N], int ass_col_p0[N], _Bool cov_row_p0[N], _Bool cov_col_p0[N], double dual_row_p0[N], double dual_col_p0[N], double slack_p0[N], int prv_row_p0[N], int prv_col_p0[N], int suc_row_p0[N], int suc_col_p0[N]) {
	_Bool sync_p0;
	_Bool sync76_p0;
	double slack_p02[N];
	double dual_col_p02[N];
	_Bool active_p02[N];
	int n_p02;
	double dual_row_p02[N];
	_Bool augment_p0[N];
	_Bool reverse_p0[N];
	_Bool visited_p0[N];
	int tmp5_p0;
	int tmp_p0;
	int tmp6_p0;
	int tmp2_p0;
	int tmp7_p0;
	int tmp3_p0;
	int tmp8_p0;
	int tmp4_p0;
	_Bool check_flag_p0 = 0;
	
	for (int i_p0 = 0; i_p0 < N; i_p0 = i_p0 + 1) {
		visited_p0[i_p0] = 0;
		reverse_p0[i_p0] = 0;
		augment_p0[i_p0] = 0;
	}
	
	{
		int f_in_p0[N];
		int active_count_p0=0;
		
		for (int i_p0 = 0; i_p0 < n_p0; i_p0 = i_p0 + 1) {
			if (ass_row_p0[i_p0] == (-1) || active_p0[i_p0]) {
				tmp5_p0 = active_count_p0;
				active_count_p0 = tmp5_p0 + 1;
				
				tmp_p0 = tmp5_p0;
				
				f_in_p0[tmp_p0] = i_p0;
				
				active_p0[i_p0] = 1;
			} else {
				active_p0[i_p0] = 0;
			}
		}
		
		while (sync_p0 = (active_count_p0 > 0), EMX_SendSync(0, 1, 68, -1, sync_p0), sync_p0) {
			
			
			
			
			
			
			forward_bfs(cost_p0, n_p0, f_in_p0, active_count_p0, active_p0, reverse_p0, visited_p0, ass_col_p0, cov_row_p0, cov_col_p0, dual_row_p0, dual_col_p0, slack_p0, prv_row_p0, prv_col_p0);
			
			active_count_p0 = EMX_Recv32(1, 0, 28, -1);
			
			for (int i_p0 = 0; i_p0 < n_p0; i_p0 = i_p0 + 1) {
				if (visited_p0[i_p0]) {
					active_p0[i_p0] = 0;
				}
				
				if (active_p0[i_p0]) {
					tmp6_p0 = active_count_p0;
					active_count_p0 = tmp6_p0 + 1;
					
					tmp2_p0 = tmp6_p0;
					
					f_in_p0[tmp2_p0] = i_p0;
				}
			}
			
		}
		
		{
			int f_rev_size_p0 = 0;
			int f_rev_p0[N];
			
			EMX_Send(0, 6, 27, -1, prv_col_p0, N * sizeof(*prv_col_p0));
			
			EMX_Send(0, 3, 26, -1, prv_col_p0, N * sizeof(*prv_col_p0));
			
			EMX_Send(0, 3, 25, -1, slack_p0, N * sizeof(*slack_p0));
			
			EMX_Send(0, 2, 24, -1, slack_p0, N * sizeof(*slack_p0));
			
			EMX_Send(0, 5, 23, -1, cov_col_p0, N * sizeof(*cov_col_p0));
			
			EMX_Send(0, 2, 22, -1, cov_col_p0, N * sizeof(*cov_col_p0));
			
			EMX_Send(0, 4, 21, -1, cov_row_p0, N * sizeof(*cov_row_p0));
			
			EMX_Send(0, 1, 20, -1, cov_row_p0, N * sizeof(*cov_row_p0));
			
			for (int j_p0 = 0; j_p0 < n_p0; j_p0 = j_p0 + 1) {
				if (reverse_p0[j_p0]) {
					tmp7_p0 = f_rev_size_p0;
					f_rev_size_p0 = tmp7_p0 + 1;
					
					tmp3_p0 = tmp7_p0;
					
					f_rev_p0[tmp3_p0] = j_p0;
				}
			}
			
			sync76_p0 = (f_rev_size_p0 > 0);
			
			EMX_SendSync(0, 6, 82, -1, sync76_p0);
			
			EMX_SendSync(0, 5, 81, -1, sync76_p0);
			
			EMX_SendSync(0, 4, 80, -1, sync76_p0);
			
			EMX_SendSync(0, 3, 79, -1, sync76_p0);
			
			EMX_SendSync(0, 2, 78, -1, sync76_p0);
			
			EMX_SendSync(0, 1, 77, -1, sync76_p0);
			
			if (sync76_p0) {
				reverse_bfs(f_rev_p0, f_rev_size_p0, augment_p0, suc_row_p0, suc_col_p0, prv_row_p0, prv_col_p0);
				
				{
					int f_aug_size_p0 = 0;
					int f_aug_p0[N];
					
					for (int j_p0 = 0; j_p0 < n_p0; j_p0 = j_p0 + 1) {
						if (augment_p0[j_p0]) {
							tmp8_p0 = f_aug_size_p0;
							f_aug_size_p0 = tmp8_p0 + 1;
							
							tmp4_p0 = tmp8_p0;
							
							f_aug_p0[tmp4_p0] = j_p0;
						}
					}
					
					augment_pass(f_aug_p0, f_aug_size_p0, ass_row_p0, ass_col_p0, suc_row_p0, suc_col_p0);
				}
				check_flag_p0 = EMX_Recv8(1, 0, 29, -1);
			} else {
				double theta_p0 = 0x7fffffff;
				
				for (int j_p0 = 0; EMX_RecvSync(2, 0, 69, -1); j_p0 = j_p0 + 1) {
				}
				
				theta_p0 = EMX_Recv64F(2, 0, 30, -1);
				
				update_pass_p0(n_p0, active_p0, dual_row_p0, dual_col_p0, slack_p0);
				
				check_flag_p0 = EMX_Recv8(3, 0, 62, -1);
			}
			
			return check_flag_p0;
		}
	}
}


extern void augmenting_path_search_p1(void) {
	_Bool cov_row_p1[N];
	_Bool check_flag_p1 = 0;
	int active_count_p1;
	
	while (EMX_RecvSync(0, 1, 68, -1)) {
		active_count_p1 = 0;
		
		EMX_Send32(1, 0, 28, -1, active_count_p1);
	}
	
	EMX_Recv(0, 1, 20, -1, cov_row_p1, N * sizeof(*cov_row_p1));
	
	if (EMX_RecvSync(0, 1, 77, -1)) {
		check_flag_p1 = 1;
		
		EMX_Send8(1, 0, 29, -1, check_flag_p1);
	} else {
		double theta_p1;
		
		
		theta_p1 = EMX_Recv64F(2, 1, 31, -1);
		
		update_pass_p1(theta_p1, cov_row_p1);
	}
}


extern void augmenting_path_search_p2(int n_p2, double dual_row_p2[N], double dual_col_p2[N]) {
	_Bool sync_p2;
	_Bool cov_col_p2[N];
	double dual_row_p22[N];
	double slack_p2[N];
	double dual_col_p22[N];
	
	
	EMX_Recv(0, 2, 24, -1, slack_p2, N * sizeof(*slack_p2));
	
	EMX_Recv(0, 2, 22, -1, cov_col_p2, N * sizeof(*cov_col_p2));
	
	if (EMX_RecvSync(0, 2, 78, -1)) {
	} else {
		double theta_p2 = 0x7fffffff;
		
		for (int j_p2 = 0; sync_p2 = (j_p2 < n_p2), EMX_SendSync(2, 0, 69, -1, sync_p2), sync_p2; j_p2 = j_p2 + 1) {
			
			
			
			
			
			if (slack_p2[j_p2] > 0) {
				theta_p2 = (theta_p2 < slack_p2[j_p2] ? theta_p2 : slack_p2[j_p2]);
			}
			
			
		}
		
		EMX_Send64F(2, 0, 30, -1, theta_p2);
		
		EMX_Send64F(2, 1, 31, -1, theta_p2);
		
		EMX_Send64F(2, 3, 32, -1, theta_p2);
		
		EMX_Send64F(2, 6, 33, -1, theta_p2);
		
		EMX_Send64F(2, 5, 34, -1, theta_p2);
		
		EMX_Send64F(2, 4, 35, -1, theta_p2);
		
		update_pass_p2(theta_p2, cov_col_p2, dual_row_p2, dual_col_p2, slack_p2);
	}
}


extern void augmenting_path_search_p3(double dual_row_p3[N], double dual_col_p3[N]) {
	int prv_col_p3[N];
	double dual_row_p32[N];
	double slack_p3[N];
	double dual_col_p32[N];
	_Bool check_flag_p3 = 0;
	
	
	EMX_Recv(0, 3, 26, -1, prv_col_p3, N * sizeof(*prv_col_p3));
	
	EMX_Recv(0, 3, 25, -1, slack_p3, N * sizeof(*slack_p3));
	
	if (EMX_RecvSync(0, 3, 79, -1)) {
	} else {
		double theta_p3;
		
		
		theta_p3 = EMX_Recv64F(2, 3, 32, -1);
		
		update_pass_p3(theta_p3, dual_row_p3, dual_col_p3, slack_p3, prv_col_p3);
		
		check_flag_p3 = 0;
		
		EMX_Send8(3, 0, 62, -1, check_flag_p3);
	}
}


extern void augmenting_path_search_p4(void) {
	_Bool cov_row_p4[N];
	
	
	EMX_Recv(0, 4, 21, -1, cov_row_p4, N * sizeof(*cov_row_p4));
	
	if (EMX_RecvSync(0, 4, 80, -1)) {
	} else {
		double theta_p4;
		
		
		theta_p4 = EMX_Recv64F(2, 4, 35, -1);
		
		update_pass_p4(theta_p4, cov_row_p4);
	}
}


extern void augmenting_path_search_p5(void) {
	_Bool cov_col_p5[N];
	
	
	EMX_Recv(0, 5, 23, -1, cov_col_p5, N * sizeof(*cov_col_p5));
	
	if (EMX_RecvSync(0, 5, 81, -1)) {
	} else {
		double theta_p5;
		
		
		theta_p5 = EMX_Recv64F(2, 5, 34, -1);
		
		update_pass_p5(theta_p5, cov_col_p5);
	}
}


extern void augmenting_path_search_p6(void) {
	int prv_col_p6[N];
	
	
	EMX_Recv(0, 6, 27, -1, prv_col_p6, N * sizeof(*prv_col_p6));
	
	if (EMX_RecvSync(0, 6, 82, -1)) {
	} else {
		double theta_p6;
		
		
		theta_p6 = EMX_Recv64F(2, 6, 33, -1);
		
		update_pass_p6(theta_p6, prv_col_p6);
	}
}


extern int hungarian_parallel_p0(int cost_p0[N][N], int n_p0) {
	_Bool sync_p0;
	int n_p02;
	int cost_p02[N][N];
	double dual_col_p0[N];
	double dual_row_p0[N];
	int ass_row_p0[N];
	double slack_p0[N];
	_Bool cov_col_p0[N];
	int suc_row_p0[N];
	int prv_col_p0[N];
	int prv_row_p0[N];
	int suc_col_p0[N];
	_Bool cov_row_p0[N];
	int ass_col_p0[N];
	int ret_p0 = 0;
	
	for (int i_p0 = 0; i_p0 < n_p0; i_p0 = i_p0 + 1) {
		ass_row_p0[i_p0] = -1;
		ass_col_p0[i_p0] = -1;
		cov_row_p0[i_p0] = 0;
		cov_col_p0[i_p0] = 0;
		prv_row_p0[i_p0] = -1;
		prv_col_p0[i_p0] = -1;
		slack_p0[i_p0] = 0x7fffffff;
		suc_row_p0[i_p0] = -1;
		suc_col_p0[i_p0] = -1;
	}
	
	{
		_Bool active_p0[N];
		int match_count_p0 = 0;
		_Bool check_flag_p0 = 1;
		
		init_potentials_p0(cost_p0, n_p0, dual_row_p0, dual_col_p0);
		
		while (sync_p0 = (match_count_p0 < n_p0), EMX_SendSync(0, 1, 83, -1, sync_p0), EMX_SendSync(0, 2, 84, -1, sync_p0), EMX_SendSync(0, 3, 85, -1, sync_p0), EMX_SendSync(0, 4, 86, -1, sync_p0), EMX_SendSync(0, 5, 87, -1, sync_p0), EMX_SendSync(0, 6, 88, -1, sync_p0), sync_p0) {
			
			EMX_Send(0, 2, 13, -1, dual_row_p0, N * sizeof(*dual_row_p0));
			
			EMX_Send(0, 3, 14, -1, dual_row_p0, N * sizeof(*dual_row_p0));
			
			EMX_Send(0, 2, 15, -1, dual_col_p0, N * sizeof(*dual_col_p0));
			
			EMX_Send(0, 3, 16, -1, dual_col_p0, N * sizeof(*dual_col_p0));
			
			check_flag_p0 = augmenting_path_search_p0(cost_p0, n_p0, active_p0, ass_row_p0, ass_col_p0, cov_row_p0, cov_col_p0, dual_row_p0, dual_col_p0, slack_p0, prv_row_p0, prv_col_p0, suc_row_p0, suc_col_p0);
			
			if (check_flag_p0) {
				for (int i_p0 = 0; i_p0 < n_p0; i_p0 = i_p0 + 1) {
					cov_row_p0[i_p0] = 0;
					cov_col_p0[i_p0] = 0;
					prv_row_p0[i_p0] = -1;
					prv_col_p0[i_p0] = -1;
					slack_p0[i_p0] = 0x7fffffff;
					suc_row_p0[i_p0] = -1;
					suc_col_p0[i_p0] = -1;
				}
				
				match_count_p0 = optimality_check(n_p0, cov_row_p0, ass_row_p0);
			}
			
		}
		
		for (int i_p0 = 0; i_p0 < n_p0; i_p0 = i_p0 + 1) {
			ret_p0 = ret_p0 + cost_p0[i_p0][ass_row_p0[i_p0]];
		}
		
		return ret_p0;
	}
}


extern void hungarian_parallel_p1(int cost_p1[N][N]) {
	int cost_p12[N][N];
	int ret_p1 = 0;
	_Bool check_flag_p1 = 1;
	int match_count_p1 = 0;
	
	init_potentials_p1(cost_p1);
	
	while (EMX_RecvSync(0, 1, 83, -1)) {
		augmenting_path_search_p1();
	}
}


extern void hungarian_parallel_p2(int n_p2) {
	int n_p22;
	double dual_col_p2[N];
	double dual_row_p2[N];
	
	while (EMX_RecvSync(0, 2, 84, -1)) {
		EMX_Recv(0, 2, 13, -1, dual_row_p2, N * sizeof(*dual_row_p2));
		
		EMX_Recv(0, 2, 15, -1, dual_col_p2, N * sizeof(*dual_col_p2));
		
		augmenting_path_search_p2(n_p2, dual_row_p2, dual_col_p2);
	}
}


extern void hungarian_parallel_p3(void) {
	double dual_col_p3[N];
	double dual_row_p3[N];
	
	while (EMX_RecvSync(0, 3, 85, -1)) {
		EMX_Recv(0, 3, 14, -1, dual_row_p3, N * sizeof(*dual_row_p3));
		
		EMX_Recv(0, 3, 16, -1, dual_col_p3, N * sizeof(*dual_col_p3));
		
		augmenting_path_search_p3(dual_row_p3, dual_col_p3);
	}
}


extern void hungarian_parallel_p4(void) {
	while (EMX_RecvSync(0, 4, 86, -1)) {
		augmenting_path_search_p4();
	}
}


extern void hungarian_parallel_p5(void) {
	while (EMX_RecvSync(0, 5, 87, -1)) {
		augmenting_path_search_p5();
	}
}


extern void hungarian_parallel_p6(void) {
	while (EMX_RecvSync(0, 6, 88, -1)) {
		augmenting_path_search_p6();
	}
}


extern float findMedian_p1(double arr_p1[R], int n_p1) {
	int (*callarg_p1)(const void *, const void *);
	
	callarg_p1 = compare;
	
	qsort(arr_p1, n_p1, sizeof(int), callarg_p1);
	
	if ((n_p1 % 2) == 0) {
		return (arr_p1[n_p1 / 2 - 1] + arr_p1[n_p1 / 2]) / 2.0;
	} else {
		return arr_p1[n_p1 / 2];
	}
}


extern void findMedian_p0(void) {
}


int main_p0() {
	_Bool sync_p0;
	int num_test_runs_p0 = R;
	long callarg2_p0;
	int callarg4_p0;
	float callarg7_p0;
	
	FILE *f;
	FILE *f_mean;

	// Open a file in write mode
	f = fopen("hun_emmtrix_50_2.txt", "a");
	f_mean = fopen("hun_emmtrix_50_2_mean.txt", "a");

	fprintf(f, "Hungarian Parallel Emmtrix (2 Threads): \n");
	fprintf(f, "Size\t\t\t\tCost\t\t\t\tTotal Time in s\t\t\tTotal CPU time in ms\n");

	fprintf(f_mean, "Hungarian Parallel Emmtrix (2 Threads, %d runs): \n", num_test_runs_p0);
	fprintf(f_mean, "Size\t\t\t\tMean Time in s\t\t\tMean CPU time in ms\t\t\tMedian Time in s\t\t\tMedian CPU Time in ms\n");

	// Close the file
	fclose(f);
	fclose(f_mean);
	int sum_time = 0;
	int sum_timing = 0;
	double times[R];
	double timings[R];
	
	{
		int sum_time_p0 = 0;
		int sum_timing_p0 = 0;
		double timings_p0[R];
		double times_p0[R];
		
		for (int i_p0 = 0; sync_p0 = (i_p0 < num_test_runs_p0), EMX_SendSync(0, 1, 89, -1, sync_p0), EMX_SendSync(0, 2, 90, -1, sync_p0), EMX_SendSync(0, 3, 91, -1, sync_p0), EMX_SendSync(0, 4, 92, -1, sync_p0), EMX_SendSync(0, 5, 93, -1, sync_p0), EMX_SendSync(0, 6, 94, -1, sync_p0), sync_p0; i_p0 = i_p0 + 1) {
			EMX_Send32(0, 1, 11, -1, i_p0);
			
		//	EMX_Send64(0, 1, 1, -1, *f_p0);
			
			
			{
				int cost_p0[N][N];
				
				srand(time(NULL));
				for (int i_p0 = 0; i_p0 < N; i_p0 = i_p0 + 1) {
					for (int j_p0 = 0; j_p0 < N; j_p0 = j_p0 + 1) {
						callarg2_p0 = rand();
						
						cost_p0[i_p0][j_p0] = callarg2_p0 % n + 1;
					}
				}
				
				long t1,t2;
				struct timeval timecheck;

				/* Begin Time */
				gettimeofday(&timecheck, NULL);
				t1 = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
				clock_t start = clock();
				
				EMX_Send(0, 1, 10, -1, cost_p0, N * sizeof(*cost_p0));
				
				callarg4_p0 = hungarian_parallel_p0(cost_p0, n);
				
				EMX_Send32(0, 1, 12, -1, callarg4_p0);
				
				int result_p0 = callarg4_p0;
				
				/* End Time */
				clock_t end = clock();
				gettimeofday(&timecheck, NULL);
				t2 = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;

				double time = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
				double timing = (long)(t2 - t1);

				times[i_p0] = time;
				timings[i_p0] = timing;

				sum_timing += timing;
				sum_time += time;

				// Open a file in append mode
				f = fopen("hun_emmtrix_50_2.txt", "a");
				fprintf(f, "%d\t\t\t\t%d\t\t\t\t%f\t\t\t\t%f\n", N, result_p0, timing / 1000.0, time);
				fclose(f);
			}
			{
			}
		}
		
		EMX_Recv(1, 0, 8, -1, timings_p0, R * sizeof(*timings_p0));
		
		{
			double median_timing_p0;
			
			callarg7_p0 = findMedian_duplicate2(timings_p0, num_test_runs_p0);
			
			EMX_Recv(1, 0, 9, -1, times_p0, R * sizeof(*times_p0));
			
			findMedian_p0();
			
			median_timing_p0 = callarg7_p0;
			
			EMX_Send64F(0, 2, 66, -1, median_timing_p0);
			
			double mean_timing = sum_timing / num_test_runs_p0;
			double mean_time = sum_time / num_test_runs_p0;

			double median_timing = findMedian_p1(timings, num_test_runs_p0);
			double median_time = findMedian_p1(times, num_test_runs_p0);

			// Open a file in append mode
			f_mean = fopen("hun_emmtrix_50_2_mean.txt", "a");
			fprintf(f_mean, "%d\t\t\t\t%f\t\t\t\t%f\t\t\t\t%f\t\t\t\t%f\n", N, mean_timing / 1000.0, mean_time, median_timing / 1000.0, median_time);
			fclose(f_mean);

			return 0;
		}
	}
}


void main_p1() {
	int num_test_runs_p1 = R;
	clock_t callarg3_p1;
	clock_t callarg5_p1;
	double callarg6_p1;
	int callarg4_p1;
	time_t callarg_p1;
	float callarg8_p1;
	double callarg9_p1;
	double callarg10_p1;
		
	{
		double times_p1[R];
		int sum_time_p1 = 0;
		int sum_timing_p1 = 0;
		double timings_p1[R];
		
		for (int i_p1 = 0; EMX_RecvSync(0, 1, 89, -1); i_p1 = i_p1 + 1) {
			i_p1 = EMX_Recv32(0, 1, 11, -1);
			
//			*f_p1 = EMX_Recv64(0, 1, 1, -1);
			
			{
				int cost_p1[N][N];
				
				EMX_Recv(0, 1, 10, -1, cost_p1, N * sizeof(*cost_p1));
				
				{
					clock_t start_p1;
					clock_t end_p1;
					double time_p1;
					double timing_p1 = (long)(0 - 0);
					int result_p1;
					
					hungarian_parallel_p1(cost_p1);
					
					callarg3_p1 = clock();
					
					callarg5_p1 = clock();
					
					start_p1 = callarg3_p1;
					
					end_p1 = callarg5_p1;
					
					time_p1 = (double)(end_p1 - start_p1) / CLOCKS_PER_SEC * 1000.0;
					
					callarg4_p1 = EMX_Recv32(0, 1, 12, -1);
					
					times_p1[i_p1] = time_p1;
					timings_p1[i_p1] = timing_p1;
					sum_timing_p1 = sum_timing_p1 + timing_p1;
					sum_time_p1 = sum_time_p1 + time_p1;
					
					callarg6_p1 = timing_p1 / 1000.0;
					
					result_p1 = callarg4_p1;
					
			//		fprintf(f_p1, "%d\t\t\t\t%d\t\t\t\t%f\t\t\t\t%f\n", N, result_p1, callarg6_p1, time_p1);
					
			//		EMX_Send64(1, 0, 5, -1, *f_p1);
				}
				callarg_p1 = EMX_Recv64(2, 1, 63, -1);
				
				srand(callarg_p1);
			}
		}
		
		EMX_Send(1, 0, 8, -1, timings_p1, R * sizeof(*timings_p1));
		
		{
			double mean_timing_p1;
			double median_time_p1;
			double mean_time_p1;
			
			EMX_Send(1, 0, 9, -1, times_p1, R * sizeof(*times_p1));
			
			EMX_Send32(1, 2, 7, -1, sum_timing_p1);
			
			EMX_Send32(1, 2, 6, -1, sum_time_p1);
			
			callarg8_p1 = findMedian_p1(times_p1, num_test_runs_p1);
			
			mean_timing_p1 = EMX_Recv64F(2, 1, 64, -1);
			
			callarg9_p1 = mean_timing_p1 / 1000.0;
			
			median_time_p1 = callarg8_p1;
			
			callarg10_p1 = EMX_Recv64F(2, 1, 67, -1);
		}
	}
}


void main_p2() {
	time_t callarg_p2;
	int num_test_runs_p2 = R;
	double callarg10_p2;
	int sum_timing_p2 = 0;
	int sum_time_p2 = 0;
	
	for (int i_p2 = 0; EMX_RecvSync(0, 2, 90, -1); i_p2 = i_p2 + 1) {
		hungarian_parallel_p2(n);
		
		callarg_p2 = time((void *)0);
		
		EMX_Send64(2, 1, 63, -1, callarg_p2);
	}
	
	{
		double mean_timing_p2 = sum_timing_p2 / num_test_runs_p2;
		double mean_time_p2 = sum_time_p2 / num_test_runs_p2;
		double median_timing_p2;
		
		sum_timing_p2 = EMX_Recv32(1, 2, 7, -1);
		
		sum_time_p2 = EMX_Recv32(1, 2, 6, -1);
		
		median_timing_p2 = EMX_Recv64F(0, 2, 66, -1);
		
		EMX_Send64F(2, 1, 64, -1, mean_timing_p2);
		
		callarg10_p2 = median_timing_p2 / 1000.0;
		
		EMX_Send64F(2, 1, 67, -1, callarg10_p2);
		
		EMX_Send64F(2, 1, 65, -1, mean_time_p2);
	}
}


void main_p3() {
	for (int i_p3 = 0; EMX_RecvSync(0, 3, 91, -1); i_p3 = i_p3 + 1) {
		hungarian_parallel_p3();
	}
	
}


void main_p4() {
	for (int i_p4 = 0; EMX_RecvSync(0, 4, 92, -1); i_p4 = i_p4 + 1) {
		hungarian_parallel_p4();
	}
	
}


void main_p5() {
	for (int i_p5 = 0; EMX_RecvSync(0, 5, 93, -1); i_p5 = i_p5 + 1) {
		hungarian_parallel_p5();
	}
	
}


void main_p6() {
	for (int i_p6 = 0; EMX_RecvSync(0, 6, 94, -1); i_p6 = i_p6 + 1) {
		hungarian_parallel_p6();
	}
	
}


void main_p7() {
	
}

