#include <stdio.h>
#include "_emx_main.h"
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#define inf INT_MAX
#define N 200
const int n = 200;
int **cost;
_Bool verbose = 0;
_Bool maximum = 0;

int optimality_check(int n, _Bool cov_row[200], int ass_row[200]) {
	size_t i1;
	int match_count = 0;
	
	for (i1 = 0u; i1 < 200; i1 = i1 + 1) {
		if (ass_row[i1] != (-1)) {
			cov_row[i1] = 1;
			match_count = match_count + 1;
		}
	}
	
	return match_count;
}


void forward_bfs(int cost[200][200], int n, int f_in[200], int f_in_size, _Bool active[200], _Bool reverse[200], _Bool visited[200], int ass_col[200], _Bool cov_row[200], _Bool cov_col[200], double dual_row[200], double dual_col[200], double slack[200], int prv_row[200], int prv_col[200]) {
	size_t j1;
	size_t x1;
	
	for (j1 = 0u; j1 < 200; j1 = j1 + 1) {
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


void reverse_bfs(int f_rev[200], int f_rev_size, _Bool augment[200], int suc_row[200], int suc_col[200], int prv_row[200], int prv_col[200]) {
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


void augment_pass(int f_aug[200], int f_aug_size, int ass_row[200], int ass_col[200], int suc_row[200], int suc_col[200]) {
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


extern void init_potentials_p0(int cost_p0[200][200], int n_p0, double dual_row_p0[200], double dual_col_p0[200]) {
	size_t i1_p0;
	double d_row_split1_p0[50];
	size_t j1_p0;
	size_t i3_p0;
	double d_row_split2_p0[50];
	double d_row_split3_p0[50];
	double d_row_split4_p0[50];
	size_t j2_p0;
	double d_col_split1_p0[50];
	size_t i2_p0;
	size_t i4_p0;
	double d_col_split2_p0[50];
	double d_col_split3_p0[50];
	double d_col_split4_p0[50];
	
	for (i1_p0 = 0u; i1_p0 < 50; i1_p0 = i1_p0 + 1) {
		double temp_p0 = 0x7fffffff;
		double val2_p0;
		
		for (j1_p0 = 0u; j1_p0 < 200; j1_p0 = j1_p0 + 1) {
			if (temp_p0 > ((double)cost_p0[i1_p0][j1_p0])) {
				temp_p0 = (double)cost_p0[i1_p0][j1_p0];
			}
		}
		
		val2_p0 = temp_p0;
		d_row_split1_p0[i1_p0 - 0] = val2_p0;
	}
	
	for (i1_p0 = 50; i1_p0 < 100; i1_p0 = i1_p0 + 1) {
		for (j1_p0 = 0u; j1_p0 < 200; j1_p0 = j1_p0 + 1) {
		}
	}
	
	for (i1_p0 = 100; i1_p0 < 150; i1_p0 = i1_p0 + 1) {
		for (j1_p0 = 0u; j1_p0 < 200; j1_p0 = j1_p0 + 1) {
		}
	}
	
	for (i1_p0 = 150; i1_p0 < 200; i1_p0 = i1_p0 + 1) {
		for (j1_p0 = 0u; j1_p0 < 200; j1_p0 = j1_p0 + 1) {
		}
	}
	
	for (i3_p0 = 0u; i3_p0 < 50; i3_p0 = i3_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_row_split1_p0[i3_p0 - 0];
		dual_row_p0[i3_p0] = val2_p0;
	}
	
	EMX_Recv(1, 0, 15, -1, d_row_split2_p0, 50 * sizeof(*d_row_split2_p0));
	
	for (i3_p0 = 50; i3_p0 < 100; i3_p0 = i3_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_row_split2_p0[i3_p0 - 50];
		dual_row_p0[i3_p0] = val2_p0;
	}
	
	EMX_Recv(2, 0, 16, -1, d_row_split3_p0, 50 * sizeof(*d_row_split3_p0));
	
	for (i3_p0 = 100; i3_p0 < 150; i3_p0 = i3_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_row_split3_p0[i3_p0 - 100];
		dual_row_p0[i3_p0] = val2_p0;
	}
	
	EMX_Recv(3, 0, 17, -1, d_row_split4_p0, 50 * sizeof(*d_row_split4_p0));
	
	for (i3_p0 = 150; i3_p0 < 200; i3_p0 = i3_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_row_split4_p0[i3_p0 - 150];
		dual_row_p0[i3_p0] = val2_p0;
	}
	
	for (j2_p0 = 0u; j2_p0 < 50; j2_p0 = j2_p0 + 1) {
		double temp_p0 = 0x7fffffff;
		double val2_p0;
		
		for (i2_p0 = 0u; i2_p0 < 200; i2_p0 = i2_p0 + 1) {
			if (temp_p0 > (cost_p0[i2_p0][j2_p0] - dual_row_p0[i2_p0])) {
				temp_p0 = cost_p0[i2_p0][j2_p0] - dual_row_p0[i2_p0];
			}
		}
		
		val2_p0 = temp_p0;
		d_col_split1_p0[j2_p0 - 0] = val2_p0;
	}
	
	EMX_Send(0, 1, 13, -1, dual_row_p0, 200 * sizeof(*dual_row_p0));
	
	for (j2_p0 = 50; j2_p0 < 100; j2_p0 = j2_p0 + 1) {
		for (i2_p0 = 0u; i2_p0 < 200; i2_p0 = i2_p0 + 1) {
		}
	}
	
	EMX_Send(0, 2, 12, -1, dual_row_p0, 200 * sizeof(*dual_row_p0));
	
	for (j2_p0 = 100; j2_p0 < 150; j2_p0 = j2_p0 + 1) {
		for (i2_p0 = 0u; i2_p0 < 200; i2_p0 = i2_p0 + 1) {
		}
	}
	
	EMX_Send(0, 3, 14, -1, dual_row_p0, 200 * sizeof(*dual_row_p0));
	
	for (j2_p0 = 150; j2_p0 < 200; j2_p0 = j2_p0 + 1) {
		for (i2_p0 = 0u; i2_p0 < 200; i2_p0 = i2_p0 + 1) {
		}
	}
	
	for (i4_p0 = 0u; i4_p0 < 50; i4_p0 = i4_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_col_split1_p0[i4_p0 - 0];
		dual_col_p0[i4_p0] = val2_p0;
	}
	
	EMX_Recv(1, 0, 18, -1, d_col_split2_p0, 50 * sizeof(*d_col_split2_p0));
	
	for (i4_p0 = 50; i4_p0 < 100; i4_p0 = i4_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_col_split2_p0[i4_p0 - 50];
		dual_col_p0[i4_p0] = val2_p0;
	}
	
	EMX_Recv(2, 0, 19, -1, d_col_split3_p0, 50 * sizeof(*d_col_split3_p0));
	
	for (i4_p0 = 100; i4_p0 < 150; i4_p0 = i4_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_col_split3_p0[i4_p0 - 100];
		dual_col_p0[i4_p0] = val2_p0;
	}
	
	EMX_Recv(3, 0, 20, -1, d_col_split4_p0, 50 * sizeof(*d_col_split4_p0));
	
	for (i4_p0 = 150; i4_p0 < 200; i4_p0 = i4_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_col_split4_p0[i4_p0 - 150];
		dual_col_p0[i4_p0] = val2_p0;
	}
}


extern void init_potentials_p1(int cost_p1[200][200]) {
	double dual_row_p1[200];
	size_t i1_p1;
	double d_row_split2_p1[50];
	size_t j1_p1;
	size_t j2_p1;
	double d_col_split2_p1[50];
	size_t i2_p1;
	
	for (i1_p1 = 50; i1_p1 < 100; i1_p1 = i1_p1 + 1) {
		double temp_p1 = 0x7fffffff;
		double val2_p1;
		
		
		
		
		
		
		
		for (j1_p1 = 0u; j1_p1 < 200; j1_p1 = j1_p1 + 1) {
			
			
			
			
			
			
			if (temp_p1 > ((double)cost_p1[i1_p1][j1_p1])) {
				temp_p1 = (double)cost_p1[i1_p1][j1_p1];
			}
			
		}
		
		val2_p1 = temp_p1;
		d_row_split2_p1[i1_p1 - 50] = val2_p1;
		
	}
	
	
	
	EMX_Send(1, 0, 15, -1, d_row_split2_p1, 50 * sizeof(*d_row_split2_p1));
	
	
	
	EMX_Recv(0, 1, 13, -1, dual_row_p1, 200 * sizeof(*dual_row_p1));
	
	for (j2_p1 = 50; j2_p1 < 100; j2_p1 = j2_p1 + 1) {
		double temp_p1 = 0x7fffffff;
		double val2_p1;
		
		
		
		
		
		
		
		for (i2_p1 = 0u; i2_p1 < 200; i2_p1 = i2_p1 + 1) {
			
			
			
			
			
			
			if (temp_p1 > (cost_p1[i2_p1][j2_p1] - dual_row_p1[i2_p1])) {
				temp_p1 = cost_p1[i2_p1][j2_p1] - dual_row_p1[i2_p1];
			}
			
		}
		
		val2_p1 = temp_p1;
		d_col_split2_p1[j2_p1 - 50] = val2_p1;
		
	}
	
	
	
	EMX_Send(1, 0, 18, -1, d_col_split2_p1, 50 * sizeof(*d_col_split2_p1));
	
	
}


extern void init_potentials_p2(int cost_p2[200][200]) {
	double dual_row_p2[200];
	size_t i1_p2;
	double d_row_split3_p2[50];
	size_t j1_p2;
	size_t j2_p2;
	double d_col_split3_p2[50];
	size_t i2_p2;
	
	
	for (i1_p2 = 100; i1_p2 < 150; i1_p2 = i1_p2 + 1) {
		double temp_p2 = 0x7fffffff;
		double val2_p2;
		
		
		
		
		
		
		for (j1_p2 = 0u; j1_p2 < 200; j1_p2 = j1_p2 + 1) {
			
			
			
			
			
			if (temp_p2 > ((double)cost_p2[i1_p2][j1_p2])) {
				temp_p2 = (double)cost_p2[i1_p2][j1_p2];
			}
			
			
		}
		
		val2_p2 = temp_p2;
		d_row_split3_p2[i1_p2 - 100] = val2_p2;
		
		
	}
	
	
	
	EMX_Send(2, 0, 16, -1, d_row_split3_p2, 50 * sizeof(*d_row_split3_p2));
	
	
	
	EMX_Recv(0, 2, 12, -1, dual_row_p2, 200 * sizeof(*dual_row_p2));
	
	for (j2_p2 = 100; j2_p2 < 150; j2_p2 = j2_p2 + 1) {
		double temp_p2 = 0x7fffffff;
		double val2_p2;
		
		
		
		
		
		
		for (i2_p2 = 0u; i2_p2 < 200; i2_p2 = i2_p2 + 1) {
			
			
			
			
			
			if (temp_p2 > (cost_p2[i2_p2][j2_p2] - dual_row_p2[i2_p2])) {
				temp_p2 = cost_p2[i2_p2][j2_p2] - dual_row_p2[i2_p2];
			}
			
			
		}
		
		val2_p2 = temp_p2;
		d_col_split3_p2[j2_p2 - 100] = val2_p2;
		
		
	}
	
	
	
	EMX_Send(2, 0, 19, -1, d_col_split3_p2, 50 * sizeof(*d_col_split3_p2));
	
}


extern void init_potentials_p3(int cost_p3[200][200]) {
	double dual_row_p3[200];
	size_t i1_p3;
	double d_row_split4_p3[50];
	size_t j1_p3;
	size_t j2_p3;
	double d_col_split4_p3[50];
	size_t i2_p3;
	
	
	
	for (i1_p3 = 150; i1_p3 < 200; i1_p3 = i1_p3 + 1) {
		double temp_p3 = 0x7fffffff;
		double val2_p3;
		
		
		
		
		
		for (j1_p3 = 0u; j1_p3 < 200; j1_p3 = j1_p3 + 1) {
			
			
			
			
			if (temp_p3 > ((double)cost_p3[i1_p3][j1_p3])) {
				temp_p3 = (double)cost_p3[i1_p3][j1_p3];
			}
			
			
			
		}
		
		val2_p3 = temp_p3;
		d_row_split4_p3[i1_p3 - 150] = val2_p3;
		
		
		
	}
	
	
	
	EMX_Send(3, 0, 17, -1, d_row_split4_p3, 50 * sizeof(*d_row_split4_p3));
	
	
	
	EMX_Recv(0, 3, 14, -1, dual_row_p3, 200 * sizeof(*dual_row_p3));
	
	for (j2_p3 = 150; j2_p3 < 200; j2_p3 = j2_p3 + 1) {
		double temp_p3 = 0x7fffffff;
		double val2_p3;
		
		
		
		
		
		for (i2_p3 = 0u; i2_p3 < 200; i2_p3 = i2_p3 + 1) {
			
			
			
			
			if (temp_p3 > (cost_p3[i2_p3][j2_p3] - dual_row_p3[i2_p3])) {
				temp_p3 = cost_p3[i2_p3][j2_p3] - dual_row_p3[i2_p3];
			}
			
			
			
		}
		
		val2_p3 = temp_p3;
		d_col_split4_p3[j2_p3 - 150] = val2_p3;
		
		
		
	}
	
	
	
	EMX_Send(3, 0, 20, -1, d_col_split4_p3, 50 * sizeof(*d_col_split4_p3));
}


extern void update_pass_p2(double theta_p2, _Bool cov_row_p2[200], _Bool cov_col_p2[200], double dual_row_p2[200], double dual_col_p2[200], double slack_p2[200]) {
	double d_row_split1_p2[50];
	size_t k1_p2;
	double d_row_split4_p2[50];
	
	for (int i_p2 = 0; i_p2 < 50; i_p2 = i_p2 + 1) {
		double val2_p2;
		
		val2_p2 = dual_row_p2[i_p2];
		d_row_split1_p2[i_p2 - 0] = val2_p2;
	}
	
	EMX_Recv(5, 2, 53, -1, d_row_split4_p2, 50 * sizeof(*d_row_split4_p2));
	
	EMX_Send(2, 1, 50, -1, d_row_split1_p2, 50 * sizeof(*d_row_split1_p2));
	
	{
		double d_col_split1_p2[50];
		
		for (int i_p2 = 0; i_p2 < 50; i_p2 = i_p2 + 1) {
			double val2_p2;
			
			val2_p2 = dual_col_p2[i_p2];
			d_col_split1_p2[i_p2 - 0] = val2_p2;
		}
		
		{
			double sl_split1_p2[50];
			
			for (int i_p2 = 0; i_p2 < 50; i_p2 = i_p2 + 1) {
				double val2_p2;
				
				val2_p2 = slack_p2[i_p2];
				sl_split1_p2[i_p2 - 0] = val2_p2;
			}
			
			EMX_Send(2, 3, 58, -1, sl_split1_p2, 50 * sizeof(*sl_split1_p2));
			
			{
				int act_split4_p2[50];
				
				for (k1_p2 = 0u; k1_p2 < 50; k1_p2 = k1_p2 + 1) {
					
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
				
				
				
				EMX_Send(2, 0, 54, -1, d_col_split1_p2, 50 * sizeof(*d_col_split1_p2));
				
				for (int i_p2 = 150; i_p2 < 200; i_p2 = i_p2 + 1) {
					int val2_p2;
					
					val2_p2 = -1;
					act_split4_p2[i_p2 - 150] = val2_p2;
				}
				
				for (k1_p2 = 150; k1_p2 < 200; k1_p2 = k1_p2 + 1) {
					EMX_Send(2, 4, 86, -1, act_split4_p2, 50 * sizeof(*act_split4_p2));
					
					
					
					
					
					
					
					
					
					
					if (!cov_row_p2[k1_p2]) {
						double val22_p2;
						double val3_p2;
						
						val22_p2 = d_row_split4_p2[k1_p2 - 150];
						val3_p2 = val22_p2 + theta_p2 / 2;
						d_row_split4_p2[k1_p2 - 150] = val3_p2;
					} else {
						double val22_p2;
						double val3_p2;
						
						val22_p2 = d_row_split4_p2[k1_p2 - 150];
						val3_p2 = val22_p2 - theta_p2 / 2;
						d_row_split4_p2[k1_p2 - 150] = val3_p2;
					}
					
					
					if (EMX_RecvSync(4, 2, 106, -1)) {
						if (EMX_RecvSync(4, 2, 105, -1)) {
							EMX_Recv(4, 2, 92, -1, act_split4_p2, 50 * sizeof(*act_split4_p2));
						}
					}
					
					
					
					
					
					
				}
				
				
				EMX_Send(2, 0, 91, -1, d_row_split4_p2, 50 * sizeof(*d_row_split4_p2));
				
				EMX_Send(2, 1, 85, -1, act_split4_p2, 50 * sizeof(*act_split4_p2));
			}
		}
	}
}


extern void update_pass_p3(double theta_p3, _Bool cov_col_p3[200], double dual_row_p3[200], double dual_col_p3[200], double slack_p3[200], int prv_col_p3[200]) {
	_Bool sync100_p3;
	_Bool sync101_p3;
	double d_row_split2_p3[50];
	size_t k1_p3;
	
	for (int i_p3 = 50; i_p3 < 100; i_p3 = i_p3 + 1) {
		double val2_p3;
		
		val2_p3 = dual_row_p3[i_p3];
		d_row_split2_p3[i_p3 - 50] = val2_p3;
	}
	
	EMX_Send(3, 4, 51, -1, d_row_split2_p3, 50 * sizeof(*d_row_split2_p3));
	
	{
		double d_col_split2_p3[50];
		double d_col_split4_p3[50];
		
		for (int i_p3 = 50; i_p3 < 100; i_p3 = i_p3 + 1) {
			double val2_p3;
			
			val2_p3 = dual_col_p3[i_p3];
			d_col_split2_p3[i_p3 - 50] = val2_p3;
		}
		
		EMX_Recv(5, 3, 57, -1, d_col_split4_p3, 50 * sizeof(*d_col_split4_p3));
		
		EMX_Send(3, 5, 55, -1, d_col_split2_p3, 50 * sizeof(*d_col_split2_p3));
		
		{
			double sl_split2_p3[50];
			double sl_split1_p3[50];
			
			for (int i_p3 = 50; i_p3 < 100; i_p3 = i_p3 + 1) {
				double val2_p3;
				
				val2_p3 = slack_p3[i_p3];
				sl_split2_p3[i_p3 - 50] = val2_p3;
			}
			
			EMX_Send(3, 6, 59, -1, sl_split2_p3, 50 * sizeof(*sl_split2_p3));
			
			EMX_Recv(2, 3, 58, -1, sl_split1_p3, 50 * sizeof(*sl_split1_p3));
			
			{
				int act_split1_p3[50];
				
				for (k1_p3 = 0u; k1_p3 < 50; k1_p3 = k1_p3 + 1) {
					EMX_Recv(1, 3, 62, -1, act_split1_p3, 50 * sizeof(*act_split1_p3));
					
					{
						double val2_p3;
						int cond_p3;
						
						
						
						val2_p3 = sl_split1_p3[k1_p3 - 0];
						cond_p3 = (val2_p3 > 0);
						
						sync101_p3 = cond_p3;
						
						EMX_SendSync(3, 1, 101, -1, sync101_p3);
						
						if (cond_p3, sync101_p3) {
							double val32_p3;
							double val4_p3;
							double val3_p3;
							int cond2_p3;
							
							val32_p3 = sl_split1_p3[k1_p3 - 0];
							val4_p3 = val32_p3 - theta_p3;
							sl_split1_p3[k1_p3 - 0] = val4_p3;
							val3_p3 = sl_split1_p3[k1_p3 - 0];
							cond2_p3 = (val3_p3 == 0);
							
							sync100_p3 = cond2_p3;
							
							EMX_SendSync(3, 1, 100, -1, sync100_p3);
							
							if (cond2_p3, sync100_p3) {
								int val5_p3;
								
								val5_p3 = prv_col_p3[k1_p3];
								act_split1_p3[k1_p3 - 0] = val5_p3;
								
								EMX_Send(3, 1, 67, -1, act_split1_p3, 50 * sizeof(*act_split1_p3));
							}
						}
					}
				}
				
				
				
				EMX_Send(3, 0, 65, -1, sl_split1_p3, 50 * sizeof(*sl_split1_p3));
				
				for (k1_p3 = 150; k1_p3 < 200; k1_p3 = k1_p3 + 1) {
					
					if (!cov_col_p3[k1_p3]) {
						double val22_p3;
						double val3_p3;
						
						val22_p3 = d_col_split4_p3[k1_p3 - 150];
						val3_p3 = val22_p3 + theta_p3 / 2;
						d_col_split4_p3[k1_p3 - 150] = val3_p3;
					} else {
						double val22_p3;
						double val3_p3;
						
						val22_p3 = d_col_split4_p3[k1_p3 - 150];
						val3_p3 = val22_p3 - theta_p3 / 2;
						d_col_split4_p3[k1_p3 - 150] = val3_p3;
					}
					
				}
				
				
				EMX_Send(3, 0, 90, -1, d_col_split4_p3, 50 * sizeof(*d_col_split4_p3));
				
			}
		}
	}
}


extern void update_pass_p4(double theta_p4, _Bool cov_row_p4[200], double dual_row_p4[200], double dual_col_p4[200], double slack_p4[200], int prv_col_p4[200]) {
	_Bool sync105_p4;
	_Bool sync106_p4;
	double d_row_split3_p4[50];
	size_t k1_p4;
	double d_row_split2_p4[50];
	
	for (int i_p4 = 100; i_p4 < 150; i_p4 = i_p4 + 1) {
		double val2_p4;
		
		val2_p4 = dual_row_p4[i_p4];
		d_row_split3_p4[i_p4 - 100] = val2_p4;
	}
	
	EMX_Send(4, 7, 52, -1, d_row_split3_p4, 50 * sizeof(*d_row_split3_p4));
	
	EMX_Recv(3, 4, 51, -1, d_row_split2_p4, 50 * sizeof(*d_row_split2_p4));
	
	{
		double d_col_split3_p4[50];
		
		for (int i_p4 = 100; i_p4 < 150; i_p4 = i_p4 + 1) {
			double val2_p4;
			
			val2_p4 = dual_col_p4[i_p4];
			d_col_split3_p4[i_p4 - 100] = val2_p4;
		}
		
		EMX_Send(4, 7, 56, -1, d_col_split3_p4, 50 * sizeof(*d_col_split3_p4));
		
		{
			double sl_split3_p4[50];
			double sl_split4_p4[50];
			
			for (int i_p4 = 100; i_p4 < 150; i_p4 = i_p4 + 1) {
				double val2_p4;
				
				val2_p4 = slack_p4[i_p4];
				sl_split3_p4[i_p4 - 100] = val2_p4;
			}
			
			EMX_Recv(5, 4, 61, -1, sl_split4_p4, 50 * sizeof(*sl_split4_p4));
			
			EMX_Send(4, 7, 60, -1, sl_split3_p4, 50 * sizeof(*sl_split3_p4));
			
			{
				int act_split2_p4[50];
				int act_split4_p4[50];
				
				
				for (int i_p4 = 50; i_p4 < 100; i_p4 = i_p4 + 1) {
					int val2_p4;
					
					val2_p4 = -1;
					act_split2_p4[i_p4 - 50] = val2_p4;
				}
				
				for (k1_p4 = 50; k1_p4 < 100; k1_p4 = k1_p4 + 1) {
					EMX_Send(4, 6, 69, -1, act_split2_p4, 50 * sizeof(*act_split2_p4));
					
					
					
					
					if (!cov_row_p4[k1_p4]) {
						double val22_p4;
						double val3_p4;
						
						val22_p4 = d_row_split2_p4[k1_p4 - 50];
						val3_p4 = val22_p4 + theta_p4 / 2;
						d_row_split2_p4[k1_p4 - 50] = val3_p4;
					} else {
						double val22_p4;
						double val3_p4;
						
						val22_p4 = d_row_split2_p4[k1_p4 - 50];
						val3_p4 = val22_p4 - theta_p4 / 2;
						d_row_split2_p4[k1_p4 - 50] = val3_p4;
					}
					
					
					if (EMX_RecvSync(6, 4, 103, -1)) {
						if (EMX_RecvSync(6, 4, 102, -1)) {
							EMX_Recv(6, 4, 75, -1, act_split2_p4, 50 * sizeof(*act_split2_p4));
						}
					}
					
					
					
					
					
					
					
					
					
					
					
					
				}
				
				
				
				for (k1_p4 = 150; k1_p4 < 200; k1_p4 = k1_p4 + 1) {
					EMX_Recv(2, 4, 86, -1, act_split4_p4, 50 * sizeof(*act_split4_p4));
					
					{
						double val2_p4;
						int cond_p4;
						
						
						
						val2_p4 = sl_split4_p4[k1_p4 - 150];
						cond_p4 = (val2_p4 > 0);
						
						sync106_p4 = cond_p4;
						
						EMX_SendSync(4, 2, 106, -1, sync106_p4);
						
						if (cond_p4, sync106_p4) {
							double val32_p4;
							double val4_p4;
							double val3_p4;
							int cond2_p4;
							
							val32_p4 = sl_split4_p4[k1_p4 - 150];
							val4_p4 = val32_p4 - theta_p4;
							sl_split4_p4[k1_p4 - 150] = val4_p4;
							val3_p4 = sl_split4_p4[k1_p4 - 150];
							cond2_p4 = (val3_p4 == 0);
							
							sync105_p4 = cond2_p4;
							
							EMX_SendSync(4, 2, 105, -1, sync105_p4);
							
							if (cond2_p4, sync105_p4) {
								int val5_p4;
								
								val5_p4 = prv_col_p4[k1_p4];
								act_split4_p4[k1_p4 - 150] = val5_p4;
								
								EMX_Send(4, 2, 92, -1, act_split4_p4, 50 * sizeof(*act_split4_p4));
							}
						}
					}
				}
				
				EMX_Send(4, 0, 74, -1, d_row_split2_p4, 50 * sizeof(*d_row_split2_p4));
				
				EMX_Send(4, 1, 68, -1, act_split2_p4, 50 * sizeof(*act_split2_p4));
				
				
				EMX_Send(4, 0, 89, -1, sl_split4_p4, 50 * sizeof(*sl_split4_p4));
				
			}
		}
	}
}


extern void update_pass_p5(double theta_p5, _Bool cov_col_p5[200], double dual_row_p5[200], double dual_col_p5[200], double slack_p5[200]) {
	double d_row_split4_p5[50];
	size_t k1_p5;
	
	for (int i_p5 = 150; i_p5 < 200; i_p5 = i_p5 + 1) {
		double val2_p5;
		
		val2_p5 = dual_row_p5[i_p5];
		d_row_split4_p5[i_p5 - 150] = val2_p5;
	}
	
	EMX_Send(5, 2, 53, -1, d_row_split4_p5, 50 * sizeof(*d_row_split4_p5));
	
	{
		double d_col_split4_p5[50];
		double d_col_split2_p5[50];
		
		for (int i_p5 = 150; i_p5 < 200; i_p5 = i_p5 + 1) {
			double val2_p5;
			
			val2_p5 = dual_col_p5[i_p5];
			d_col_split4_p5[i_p5 - 150] = val2_p5;
		}
		
		EMX_Send(5, 3, 57, -1, d_col_split4_p5, 50 * sizeof(*d_col_split4_p5));
		
		EMX_Recv(3, 5, 55, -1, d_col_split2_p5, 50 * sizeof(*d_col_split2_p5));
		
		{
			double sl_split4_p5[50];
			
			for (int i_p5 = 150; i_p5 < 200; i_p5 = i_p5 + 1) {
				double val2_p5;
				
				val2_p5 = slack_p5[i_p5];
				sl_split4_p5[i_p5 - 150] = val2_p5;
			}
			
			EMX_Send(5, 4, 61, -1, sl_split4_p5, 50 * sizeof(*sl_split4_p5));
			
			
			for (k1_p5 = 50; k1_p5 < 100; k1_p5 = k1_p5 + 1) {
				
				if (!cov_col_p5[k1_p5]) {
					double val22_p5;
					double val3_p5;
					
					val22_p5 = d_col_split2_p5[k1_p5 - 50];
					val3_p5 = val22_p5 + theta_p5 / 2;
					d_col_split2_p5[k1_p5 - 50] = val3_p5;
				} else {
					double val22_p5;
					double val3_p5;
					
					val22_p5 = d_col_split2_p5[k1_p5 - 50];
					val3_p5 = val22_p5 - theta_p5 / 2;
					d_col_split2_p5[k1_p5 - 50] = val3_p5;
				}
				
			}
			
			
			EMX_Send(5, 0, 73, -1, d_col_split2_p5, 50 * sizeof(*d_col_split2_p5));
			
			
			
			
		}
	}
}


extern void update_pass_p1(double theta_p1, _Bool cov_row_p1[200]) {
	_Bool sync104_p1;
	_Bool sync107_p1;
	_Bool sync108_p1;
	_Bool sync109_p1;
	_Bool active_p1[200];
	size_t k1_p1;
	double d_row_split1_p1[50];
	
	EMX_Recv(2, 1, 50, -1, d_row_split1_p1, 50 * sizeof(*d_row_split1_p1));
	
	{
		int act_split1_p1[50];
		int act_split2_p1[50];
		int act_split3_p1[50];
		int act_split4_p1[50];
		
		for (int i_p1 = 0; i_p1 < 50; i_p1 = i_p1 + 1) {
			int val2_p1;
			
			val2_p1 = -1;
			act_split1_p1[i_p1 - 0] = val2_p1;
		}
		
		for (k1_p1 = 0u; k1_p1 < 50; k1_p1 = k1_p1 + 1) {
			EMX_Send(1, 3, 62, -1, act_split1_p1, 50 * sizeof(*act_split1_p1));
			
			
			
			
			
			
			
			
			
			
			
			
			
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
			
			
			if (EMX_RecvSync(3, 1, 101, -1)) {
				if (EMX_RecvSync(3, 1, 100, -1)) {
					EMX_Recv(3, 1, 67, -1, act_split1_p1, 50 * sizeof(*act_split1_p1));
				}
			}
			
			
			
		}
		
		
		
		EMX_Send(1, 0, 66, -1, d_row_split1_p1, 50 * sizeof(*d_row_split1_p1));
		
		for (int i_p1 = 0; i_p1 < 50; i_p1 = i_p1 + 1) {
			int val5_p1;
			int cond_p1;
			
			val5_p1 = act_split1_p1[i_p1 - 0];
			cond_p1 = (val5_p1 != (-1));
			
			EMX_Recv(0, 1, 46, -1, active_p1, 200 * sizeof(*active_p1));
			
			sync104_p1 = cond_p1;
			
			EMX_SendSync(1, 0, 104, -1, sync104_p1);
			
			if (cond_p1, sync104_p1) {
				int val6_p1;
				int tmp_p1;
				
				val6_p1 = act_split1_p1[i_p1 - 0];
				tmp_p1 = val6_p1;
				active_p1[tmp_p1] = 1;
				
				EMX_Send(1, 0, 81, -1, active_p1, 200 * sizeof(*active_p1));
			}
		}
		
		EMX_Recv(4, 1, 68, -1, act_split2_p1, 50 * sizeof(*act_split2_p1));
		
		for (int i_p1 = 50; i_p1 < 100; i_p1 = i_p1 + 1) {
			int val5_p1;
			int cond_p1;
			
			val5_p1 = act_split2_p1[i_p1 - 50];
			cond_p1 = (val5_p1 != (-1));
			
			EMX_Recv(0, 1, 47, -1, active_p1, 200 * sizeof(*active_p1));
			
			sync107_p1 = cond_p1;
			
			EMX_SendSync(1, 0, 107, -1, sync107_p1);
			
			if (cond_p1, sync107_p1) {
				int val6_p1;
				int tmp_p1;
				
				val6_p1 = act_split2_p1[i_p1 - 50];
				tmp_p1 = val6_p1;
				active_p1[tmp_p1] = 1;
				
				EMX_Send(1, 0, 82, -1, active_p1, 200 * sizeof(*active_p1));
			}
		}
		
		EMX_Recv(7, 1, 76, -1, act_split3_p1, 50 * sizeof(*act_split3_p1));
		
		for (int i_p1 = 100; i_p1 < 150; i_p1 = i_p1 + 1) {
			int val5_p1;
			int cond_p1;
			
			val5_p1 = act_split3_p1[i_p1 - 100];
			cond_p1 = (val5_p1 != (-1));
			
			EMX_Recv(0, 1, 48, -1, active_p1, 200 * sizeof(*active_p1));
			
			sync108_p1 = cond_p1;
			
			EMX_SendSync(1, 0, 108, -1, sync108_p1);
			
			if (cond_p1, sync108_p1) {
				int val6_p1;
				int tmp_p1;
				
				val6_p1 = act_split3_p1[i_p1 - 100];
				tmp_p1 = val6_p1;
				active_p1[tmp_p1] = 1;
				
				EMX_Send(1, 0, 83, -1, active_p1, 200 * sizeof(*active_p1));
			}
		}
		
		EMX_Recv(2, 1, 85, -1, act_split4_p1, 50 * sizeof(*act_split4_p1));
		
		for (int i_p1 = 150; i_p1 < 200; i_p1 = i_p1 + 1) {
			int val5_p1;
			int cond_p1;
			
			val5_p1 = act_split4_p1[i_p1 - 150];
			cond_p1 = (val5_p1 != (-1));
			
			EMX_Recv(0, 1, 49, -1, active_p1, 200 * sizeof(*active_p1));
			
			sync109_p1 = cond_p1;
			
			EMX_SendSync(1, 0, 109, -1, sync109_p1);
			
			if (cond_p1, sync109_p1) {
				int val6_p1;
				int tmp_p1;
				
				val6_p1 = act_split4_p1[i_p1 - 150];
				tmp_p1 = val6_p1;
				active_p1[tmp_p1] = 1;
				
				EMX_Send(1, 0, 84, -1, active_p1, 200 * sizeof(*active_p1));
			}
		}
	}
}


extern void update_pass_p0(int n_p0, _Bool active_p0[200], double dual_row_p0[200], double dual_col_p0[200], double slack_p0[200]) {
	double d_row_split1_p0[50];
	double d_row_split2_p0[50];
	double d_row_split3_p0[50];
	double d_row_split4_p0[50];
	size_t k1_p0;
	double d_col_split1_p0[50];
	double d_col_split2_p0[50];
	double d_col_split3_p0[50];
	double d_col_split4_p0[50];
	double sl_split1_p0[50];
	double sl_split2_p0[50];
	double sl_split3_p0[50];
	double sl_split4_p0[50];
	
	for (k1_p0 = 0u; k1_p0 < 50; k1_p0 = k1_p0 + 1) {
		
		
	}
	
	for (k1_p0 = 50; k1_p0 < 100; k1_p0 = k1_p0 + 1) {
		
		
	}
	
	for (k1_p0 = 100; k1_p0 < 150; k1_p0 = k1_p0 + 1) {
		
		
	}
	
	EMX_Recv(1, 0, 66, -1, d_row_split1_p0, 50 * sizeof(*d_row_split1_p0));
	
	EMX_Recv(3, 0, 65, -1, sl_split1_p0, 50 * sizeof(*sl_split1_p0));
	
	EMX_Recv(2, 0, 54, -1, d_col_split1_p0, 50 * sizeof(*d_col_split1_p0));
	
	for (int i_p0 = 0; i_p0 < 50; i_p0 = i_p0 + 1) {
		double val2_p0;
		double val3_p0;
		double val4_p0;
		
		
		
		
		
		
		
		val2_p0 = d_row_split1_p0[i_p0 - 0];
		dual_row_p0[i_p0] = val2_p0;
		val3_p0 = d_col_split1_p0[i_p0 - 0];
		dual_col_p0[i_p0] = val3_p0;
		val4_p0 = sl_split1_p0[i_p0 - 0];
		slack_p0[i_p0] = val4_p0;
		
		EMX_Send(0, 1, 46, -1, active_p0, 200 * sizeof(*active_p0));
		
		if (EMX_RecvSync(1, 0, 104, -1)) {
			EMX_Recv(1, 0, 81, -1, active_p0, 200 * sizeof(*active_p0));
		}
		
	}
	
	EMX_Recv(5, 0, 73, -1, d_col_split2_p0, 50 * sizeof(*d_col_split2_p0));
	
	EMX_Recv(6, 0, 72, -1, sl_split2_p0, 50 * sizeof(*sl_split2_p0));
	
	for (k1_p0 = 150; k1_p0 < 200; k1_p0 = k1_p0 + 1) {
		
		
	}
	
	EMX_Recv(4, 0, 74, -1, d_row_split2_p0, 50 * sizeof(*d_row_split2_p0));
	
	for (int i_p0 = 50; i_p0 < 100; i_p0 = i_p0 + 1) {
		double val2_p0;
		double val3_p0;
		double val4_p0;
		
		
		
		
		
		
		
		val2_p0 = d_row_split2_p0[i_p0 - 50];
		dual_row_p0[i_p0] = val2_p0;
		val3_p0 = d_col_split2_p0[i_p0 - 50];
		dual_col_p0[i_p0] = val3_p0;
		val4_p0 = sl_split2_p0[i_p0 - 50];
		slack_p0[i_p0] = val4_p0;
		
		EMX_Send(0, 1, 47, -1, active_p0, 200 * sizeof(*active_p0));
		
		if (EMX_RecvSync(1, 0, 107, -1)) {
			EMX_Recv(1, 0, 82, -1, active_p0, 200 * sizeof(*active_p0));
		}
		
	}
	
	EMX_Recv(7, 0, 79, -1, d_row_split3_p0, 50 * sizeof(*d_row_split3_p0));
	
	EMX_Recv(7, 0, 78, -1, d_col_split3_p0, 50 * sizeof(*d_col_split3_p0));
	
	EMX_Recv(7, 0, 77, -1, sl_split3_p0, 50 * sizeof(*sl_split3_p0));
	
	for (int i_p0 = 100; i_p0 < 150; i_p0 = i_p0 + 1) {
		double val2_p0;
		double val3_p0;
		double val4_p0;
		
		
		
		
		
		
		
		val2_p0 = d_row_split3_p0[i_p0 - 100];
		dual_row_p0[i_p0] = val2_p0;
		val3_p0 = d_col_split3_p0[i_p0 - 100];
		dual_col_p0[i_p0] = val3_p0;
		val4_p0 = sl_split3_p0[i_p0 - 100];
		slack_p0[i_p0] = val4_p0;
		
		EMX_Send(0, 1, 48, -1, active_p0, 200 * sizeof(*active_p0));
		
		if (EMX_RecvSync(1, 0, 108, -1)) {
			EMX_Recv(1, 0, 83, -1, active_p0, 200 * sizeof(*active_p0));
		}
		
	}
	
	EMX_Recv(2, 0, 91, -1, d_row_split4_p0, 50 * sizeof(*d_row_split4_p0));
	
	EMX_Recv(3, 0, 90, -1, d_col_split4_p0, 50 * sizeof(*d_col_split4_p0));
	
	EMX_Recv(4, 0, 89, -1, sl_split4_p0, 50 * sizeof(*sl_split4_p0));
	
	for (int i_p0 = 150; i_p0 < 200; i_p0 = i_p0 + 1) {
		double val2_p0;
		double val3_p0;
		double val4_p0;
		
		
		
		
		
		
		
		val2_p0 = d_row_split4_p0[i_p0 - 150];
		dual_row_p0[i_p0] = val2_p0;
		val3_p0 = d_col_split4_p0[i_p0 - 150];
		dual_col_p0[i_p0] = val3_p0;
		val4_p0 = sl_split4_p0[i_p0 - 150];
		slack_p0[i_p0] = val4_p0;
		
		EMX_Send(0, 1, 49, -1, active_p0, 200 * sizeof(*active_p0));
		
		if (EMX_RecvSync(1, 0, 109, -1)) {
			EMX_Recv(1, 0, 84, -1, active_p0, 200 * sizeof(*active_p0));
		}
		
	}
}


extern void update_pass_p6(double theta_p6, int prv_col_p6[200]) {
	_Bool sync102_p6;
	_Bool sync103_p6;
	size_t k1_p6;
	double sl_split2_p6[50];
	
	EMX_Recv(3, 6, 59, -1, sl_split2_p6, 50 * sizeof(*sl_split2_p6));
	
	{
		int act_split2_p6[50];
		
		
		for (k1_p6 = 50; k1_p6 < 100; k1_p6 = k1_p6 + 1) {
			EMX_Recv(4, 6, 69, -1, act_split2_p6, 50 * sizeof(*act_split2_p6));
			
			{
				double val2_p6;
				int cond_p6;
				
				
				
				val2_p6 = sl_split2_p6[k1_p6 - 50];
				cond_p6 = (val2_p6 > 0);
				
				sync103_p6 = cond_p6;
				
				EMX_SendSync(6, 4, 103, -1, sync103_p6);
				
				if (cond_p6, sync103_p6) {
					double val32_p6;
					double val4_p6;
					double val3_p6;
					int cond2_p6;
					
					val32_p6 = sl_split2_p6[k1_p6 - 50];
					val4_p6 = val32_p6 - theta_p6;
					sl_split2_p6[k1_p6 - 50] = val4_p6;
					val3_p6 = sl_split2_p6[k1_p6 - 50];
					cond2_p6 = (val3_p6 == 0);
					
					sync102_p6 = cond2_p6;
					
					EMX_SendSync(6, 4, 102, -1, sync102_p6);
					
					if (cond2_p6, sync102_p6) {
						int val5_p6;
						
						val5_p6 = prv_col_p6[k1_p6];
						act_split2_p6[k1_p6 - 50] = val5_p6;
						
						EMX_Send(6, 4, 75, -1, act_split2_p6, 50 * sizeof(*act_split2_p6));
					}
				}
			}
		}
		
		
		EMX_Send(6, 0, 72, -1, sl_split2_p6, 50 * sizeof(*sl_split2_p6));
		
		
		
		
	}
}


extern void update_pass_p7(double theta_p7, _Bool cov_row_p7[200], _Bool cov_col_p7[200], int prv_col_p7[200]) {
	size_t k1_p7;
	double d_row_split3_p7[50];
	
	EMX_Recv(4, 7, 52, -1, d_row_split3_p7, 50 * sizeof(*d_row_split3_p7));
	
	{
		double d_col_split3_p7[50];
		
		EMX_Recv(4, 7, 56, -1, d_col_split3_p7, 50 * sizeof(*d_col_split3_p7));
		
		{
			double sl_split3_p7[50];
			
			EMX_Recv(4, 7, 60, -1, sl_split3_p7, 50 * sizeof(*sl_split3_p7));
			
			{
				int act_split3_p7[50];
				
				
				
				for (int i_p7 = 100; i_p7 < 150; i_p7 = i_p7 + 1) {
					int val2_p7;
					
					val2_p7 = -1;
					act_split3_p7[i_p7 - 100] = val2_p7;
				}
				
				for (k1_p7 = 100; k1_p7 < 150; k1_p7 = k1_p7 + 1) {
					double val2_p7;
					int cond_p7;
					
					if (!cov_row_p7[k1_p7]) {
						double val22_p7;
						double val3_p7;
						
						val22_p7 = d_row_split3_p7[k1_p7 - 100];
						val3_p7 = val22_p7 + theta_p7 / 2;
						d_row_split3_p7[k1_p7 - 100] = val3_p7;
					} else {
						double val22_p7;
						double val3_p7;
						
						val22_p7 = d_row_split3_p7[k1_p7 - 100];
						val3_p7 = val22_p7 - theta_p7 / 2;
						d_row_split3_p7[k1_p7 - 100] = val3_p7;
					}
					
					if (!cov_col_p7[k1_p7]) {
						double val22_p7;
						double val3_p7;
						
						val22_p7 = d_col_split3_p7[k1_p7 - 100];
						val3_p7 = val22_p7 + theta_p7 / 2;
						d_col_split3_p7[k1_p7 - 100] = val3_p7;
					} else {
						double val22_p7;
						double val3_p7;
						
						val22_p7 = d_col_split3_p7[k1_p7 - 100];
						val3_p7 = val22_p7 - theta_p7 / 2;
						d_col_split3_p7[k1_p7 - 100] = val3_p7;
					}
					
					val2_p7 = sl_split3_p7[k1_p7 - 100];
					cond_p7 = (val2_p7 > 0);
					
					if (cond_p7) {
						double val32_p7;
						double val4_p7;
						double val3_p7;
						int cond2_p7;
						
						val32_p7 = sl_split3_p7[k1_p7 - 100];
						val4_p7 = val32_p7 - theta_p7;
						sl_split3_p7[k1_p7 - 100] = val4_p7;
						val3_p7 = sl_split3_p7[k1_p7 - 100];
						cond2_p7 = (val3_p7 == 0);
						
						if (cond2_p7) {
							int val5_p7;
							
							val5_p7 = prv_col_p7[k1_p7];
							act_split3_p7[k1_p7 - 100] = val5_p7;
						}
					}
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
				}
				
				
				
				EMX_Send(7, 0, 79, -1, d_row_split3_p7, 50 * sizeof(*d_row_split3_p7));
				
				EMX_Send(7, 0, 78, -1, d_col_split3_p7, 50 * sizeof(*d_col_split3_p7));
				
				EMX_Send(7, 0, 77, -1, sl_split3_p7, 50 * sizeof(*sl_split3_p7));
				
				EMX_Send(7, 1, 76, -1, act_split3_p7, 50 * sizeof(*act_split3_p7));
				
			}
		}
	}
}


extern _Bool augmenting_path_search_p0(int cost_p0[200][200], int n_p0, _Bool active_p0[200], int ass_row_p0[200], int ass_col_p0[200], _Bool cov_row_p0[200], _Bool cov_col_p0[200], double dual_row_p0[200], double dual_col_p0[200], double slack_p0[200], int prv_row_p0[200], int prv_col_p0[200], int suc_row_p0[200], int suc_col_p0[200]) {
	_Bool sync_p0;
	_Bool sync110_p0;
	_Bool active_p02[200];
	double slack_p02[200];
	int n_p02;
	double dual_row_p02[200];
	double dual_col_p02[200];
	_Bool augment_p0[200];
	_Bool reverse_p0[200];
	_Bool visited_p0[200];
	int tmp5_p0;
	int tmp_p0;
	int tmp6_p0;
	int tmp2_p0;
	int tmp7_p0;
	int tmp3_p0;
	int tmp8_p0;
	int tmp4_p0;
	_Bool check_flag_p0 = 0;
	
	for (int i_p0 = 0; i_p0 < 200; i_p0 = i_p0 + 1) {
		visited_p0[i_p0] = 0;
		reverse_p0[i_p0] = 0;
		augment_p0[i_p0] = 0;
	}
	
	{
		int f_in_p0[200];
		int active_count_p0;
		
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
		
		while (sync_p0 = (active_count_p0 > 0), EMX_SendSync(0, 1, 98, -1, sync_p0), sync_p0) {
			
			
			
			
			
			
			forward_bfs(cost_p0, n_p0, f_in_p0, active_count_p0, active_p0, reverse_p0, visited_p0, ass_col_p0, cov_row_p0, cov_col_p0, dual_row_p0, dual_col_p0, slack_p0, prv_row_p0, prv_col_p0);
			
			active_count_p0 = EMX_Recv32(1, 0, 37, -1);
			
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
			int f_rev_p0[200];
			
			EMX_Send(0, 7, 36, -1, prv_col_p0, 200 * sizeof(*prv_col_p0));
			
			EMX_Send(0, 6, 35, -1, prv_col_p0, 200 * sizeof(*prv_col_p0));
			
			EMX_Send(0, 4, 34, -1, prv_col_p0, 200 * sizeof(*prv_col_p0));
			
			EMX_Send(0, 3, 33, -1, prv_col_p0, 200 * sizeof(*prv_col_p0));
			
			EMX_Send(0, 4, 32, -1, slack_p0, 200 * sizeof(*slack_p0));
			
			EMX_Send(0, 5, 31, -1, slack_p0, 200 * sizeof(*slack_p0));
			
			EMX_Send(0, 3, 30, -1, slack_p0, 200 * sizeof(*slack_p0));
			
			EMX_Send(0, 2, 29, -1, slack_p0, 200 * sizeof(*slack_p0));
			
			EMX_Send(0, 7, 28, -1, cov_col_p0, 200 * sizeof(*cov_col_p0));
			
			EMX_Send(0, 5, 27, -1, cov_col_p0, 200 * sizeof(*cov_col_p0));
			
			EMX_Send(0, 3, 26, -1, cov_col_p0, 200 * sizeof(*cov_col_p0));
			
			EMX_Send(0, 2, 25, -1, cov_col_p0, 200 * sizeof(*cov_col_p0));
			
			EMX_Send(0, 7, 24, -1, cov_row_p0, 200 * sizeof(*cov_row_p0));
			
			EMX_Send(0, 4, 23, -1, cov_row_p0, 200 * sizeof(*cov_row_p0));
			
			EMX_Send(0, 1, 22, -1, cov_row_p0, 200 * sizeof(*cov_row_p0));
			
			EMX_Send(0, 2, 21, -1, cov_row_p0, 200 * sizeof(*cov_row_p0));
			
			for (int j_p0 = 0; j_p0 < n_p0; j_p0 = j_p0 + 1) {
				if (reverse_p0[j_p0]) {
					tmp7_p0 = f_rev_size_p0;
					f_rev_size_p0 = tmp7_p0 + 1;
					
					tmp3_p0 = tmp7_p0;
					
					f_rev_p0[tmp3_p0] = j_p0;
				}
			}
			
			sync110_p0 = (f_rev_size_p0 > 0);
			
			EMX_SendSync(0, 7, 117, -1, sync110_p0);
			
			EMX_SendSync(0, 6, 116, -1, sync110_p0);
			
			EMX_SendSync(0, 5, 115, -1, sync110_p0);
			
			EMX_SendSync(0, 4, 114, -1, sync110_p0);
			
			EMX_SendSync(0, 3, 113, -1, sync110_p0);
			
			EMX_SendSync(0, 2, 112, -1, sync110_p0);
			
			EMX_SendSync(0, 1, 111, -1, sync110_p0);
			
			if (sync110_p0) {
				reverse_bfs(f_rev_p0, f_rev_size_p0, augment_p0, suc_row_p0, suc_col_p0, prv_row_p0, prv_col_p0);
				
				{
					int f_aug_size_p0 = 0;
					int f_aug_p0[200];
					
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
				check_flag_p0 = EMX_Recv8(1, 0, 38, -1);
			} else {
				double theta_p0 = 0x7fffffff;
				
				for (int j_p0 = 0; EMX_RecvSync(2, 0, 99, -1); j_p0 = j_p0 + 1) {
				}
				
				theta_p0 = EMX_Recv64F(2, 0, 39, -1);
				
				update_pass_p0(n_p0, active_p0, dual_row_p0, dual_col_p0, slack_p0);
				
				check_flag_p0 = EMX_Recv8(3, 0, 96, -1);
			}
			
			return check_flag_p0;
		}
	}
}


extern void augmenting_path_search_p1(void) {
	_Bool cov_row_p1[200];
	_Bool check_flag_p1 = 0;
	int active_count_p1;
	
	while (EMX_RecvSync(0, 1, 98, -1)) {
		active_count_p1 = 0;
		
		EMX_Send32(1, 0, 37, -1, active_count_p1);
	}
	
	EMX_Recv(0, 1, 22, -1, cov_row_p1, 200 * sizeof(*cov_row_p1));
	
	if (EMX_RecvSync(0, 1, 111, -1)) {
		check_flag_p1 = 1;
		
		EMX_Send8(1, 0, 38, -1, check_flag_p1);
	} else {
		double theta_p1;
		
		
		theta_p1 = EMX_Recv64F(2, 1, 40, -1);
		
		update_pass_p1(theta_p1, cov_row_p1);
	}
}


extern void augmenting_path_search_p2(int n_p2, double dual_row_p2[200], double dual_col_p2[200]) {
	_Bool sync_p2;
	double dual_col_p22[200];
	double dual_row_p22[200];
	double slack_p2[200];
	_Bool cov_row_p2[200];
	_Bool cov_col_p2[200];
	
	
	EMX_Recv(0, 2, 29, -1, slack_p2, 200 * sizeof(*slack_p2));
	
	EMX_Recv(0, 2, 25, -1, cov_col_p2, 200 * sizeof(*cov_col_p2));
	
	EMX_Recv(0, 2, 21, -1, cov_row_p2, 200 * sizeof(*cov_row_p2));
	
	if (EMX_RecvSync(0, 2, 112, -1)) {
	} else {
		double theta_p2 = 0x7fffffff;
		
		for (int j_p2 = 0; sync_p2 = (j_p2 < n_p2), EMX_SendSync(2, 0, 99, -1, sync_p2), sync_p2; j_p2 = j_p2 + 1) {
			
			
			
			
			
			if (slack_p2[j_p2] > 0) {
				theta_p2 = (theta_p2 < slack_p2[j_p2] ? theta_p2 : slack_p2[j_p2]);
			}
			
			
		}
		
		EMX_Send64F(2, 0, 39, -1, theta_p2);
		
		EMX_Send64F(2, 1, 40, -1, theta_p2);
		
		EMX_Send64F(2, 3, 41, -1, theta_p2);
		
		EMX_Send64F(2, 5, 42, -1, theta_p2);
		
		EMX_Send64F(2, 4, 43, -1, theta_p2);
		
		EMX_Send64F(2, 6, 44, -1, theta_p2);
		
		EMX_Send64F(2, 7, 45, -1, theta_p2);
		
		update_pass_p2(theta_p2, cov_row_p2, cov_col_p2, dual_row_p2, dual_col_p2, slack_p2);
	}
}


extern void augmenting_path_search_p3(double dual_row_p3[200], double dual_col_p3[200]) {
	_Bool cov_col_p3[200];
	double dual_col_p32[200];
	double slack_p3[200];
	double dual_row_p32[200];
	int prv_col_p3[200];
	_Bool check_flag_p3 = 0;
	
	
	EMX_Recv(0, 3, 33, -1, prv_col_p3, 200 * sizeof(*prv_col_p3));
	
	EMX_Recv(0, 3, 30, -1, slack_p3, 200 * sizeof(*slack_p3));
	
	EMX_Recv(0, 3, 26, -1, cov_col_p3, 200 * sizeof(*cov_col_p3));
	
	if (EMX_RecvSync(0, 3, 113, -1)) {
	} else {
		double theta_p3;
		
		
		theta_p3 = EMX_Recv64F(2, 3, 41, -1);
		
		update_pass_p3(theta_p3, cov_col_p3, dual_row_p3, dual_col_p3, slack_p3, prv_col_p3);
		
		check_flag_p3 = 0;
		
		EMX_Send8(3, 0, 96, -1, check_flag_p3);
	}
}


extern void augmenting_path_search_p4(double dual_row_p4[200], double dual_col_p4[200]) {
	double dual_col_p42[200];
	double dual_row_p42[200];
	double slack_p4[200];
	int prv_col_p4[200];
	_Bool cov_row_p4[200];
	
	
	EMX_Recv(0, 4, 34, -1, prv_col_p4, 200 * sizeof(*prv_col_p4));
	
	EMX_Recv(0, 4, 32, -1, slack_p4, 200 * sizeof(*slack_p4));
	
	EMX_Recv(0, 4, 23, -1, cov_row_p4, 200 * sizeof(*cov_row_p4));
	
	if (EMX_RecvSync(0, 4, 114, -1)) {
	} else {
		double theta_p4;
		
		
		theta_p4 = EMX_Recv64F(2, 4, 43, -1);
		
		update_pass_p4(theta_p4, cov_row_p4, dual_row_p4, dual_col_p4, slack_p4, prv_col_p4);
	}
}


extern void augmenting_path_search_p5(double dual_row_p5[200], double dual_col_p5[200]) {
	_Bool cov_col_p5[200];
	double dual_col_p52[200];
	double slack_p5[200];
	double dual_row_p52[200];
	
	
	EMX_Recv(0, 5, 31, -1, slack_p5, 200 * sizeof(*slack_p5));
	
	EMX_Recv(0, 5, 27, -1, cov_col_p5, 200 * sizeof(*cov_col_p5));
	
	if (EMX_RecvSync(0, 5, 115, -1)) {
	} else {
		double theta_p5;
		
		
		theta_p5 = EMX_Recv64F(2, 5, 42, -1);
		
		update_pass_p5(theta_p5, cov_col_p5, dual_row_p5, dual_col_p5, slack_p5);
	}
}


extern void augmenting_path_search_p6(void) {
	int prv_col_p6[200];
	
	
	EMX_Recv(0, 6, 35, -1, prv_col_p6, 200 * sizeof(*prv_col_p6));
	
	if (EMX_RecvSync(0, 6, 116, -1)) {
	} else {
		double theta_p6;
		
		
		theta_p6 = EMX_Recv64F(2, 6, 44, -1);
		
		update_pass_p6(theta_p6, prv_col_p6);
	}
}


extern void augmenting_path_search_p7(void) {
	_Bool cov_col_p7[200];
	_Bool cov_row_p7[200];
	int prv_col_p7[200];
	
	
	EMX_Recv(0, 7, 36, -1, prv_col_p7, 200 * sizeof(*prv_col_p7));
	
	EMX_Recv(0, 7, 28, -1, cov_col_p7, 200 * sizeof(*cov_col_p7));
	
	EMX_Recv(0, 7, 24, -1, cov_row_p7, 200 * sizeof(*cov_row_p7));
	
	if (EMX_RecvSync(0, 7, 117, -1)) {
	} else {
		double theta_p7;
		
		
		theta_p7 = EMX_Recv64F(2, 7, 45, -1);
		
		update_pass_p7(theta_p7, cov_row_p7, cov_col_p7, prv_col_p7);
	}
}


extern int hungarian_parallel_p0(int cost_p0[200][200], int n_p0) {
	_Bool sync_p0;
	int cost_p02[200][200];
	int n_p02;
	double dual_col_p0[200];
	double dual_row_p0[200];
	int prv_col_p0[200];
	int prv_row_p0[200];
	int suc_row_p0[200];
	_Bool cov_col_p0[200];
	int ass_row_p0[200];
	int ass_col_p0[200];
	double slack_p0[200];
	int suc_col_p0[200];
	_Bool cov_row_p0[200];
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
		_Bool active_p0[200];
		int match_count_p0 = 0;
		_Bool check_flag_p0 = 1;
		
		init_potentials_p0(cost_p0, n_p0, dual_row_p0, dual_col_p0);
		
		while (sync_p0 = (match_count_p0 < n_p0), EMX_SendSync(0, 1, 118, -1, sync_p0), EMX_SendSync(0, 2, 119, -1, sync_p0), EMX_SendSync(0, 3, 120, -1, sync_p0), EMX_SendSync(0, 4, 121, -1, sync_p0), EMX_SendSync(0, 5, 122, -1, sync_p0), EMX_SendSync(0, 6, 123, -1, sync_p0), EMX_SendSync(0, 7, 124, -1, sync_p0), sync_p0) {
			EMX_Send(0, 3, 9, -1, dual_col_p0, 200 * sizeof(*dual_col_p0));
			
			EMX_Send(0, 2, 8, -1, dual_col_p0, 200 * sizeof(*dual_col_p0));
			
			EMX_Send(0, 3, 5, -1, dual_row_p0, 200 * sizeof(*dual_row_p0));
			
			EMX_Send(0, 2, 4, -1, dual_row_p0, 200 * sizeof(*dual_row_p0));
			
			EMX_Send(0, 5, 6, -1, dual_row_p0, 200 * sizeof(*dual_row_p0));
			
			EMX_Send(0, 4, 7, -1, dual_row_p0, 200 * sizeof(*dual_row_p0));
			
			EMX_Send(0, 5, 10, -1, dual_col_p0, 200 * sizeof(*dual_col_p0));
			
			EMX_Send(0, 4, 11, -1, dual_col_p0, 200 * sizeof(*dual_col_p0));
			
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


extern void hungarian_parallel_p1(int cost_p1[200][200]) {
	int cost_p12[200][200];
	int ret_p1 = 0;
	_Bool check_flag_p1 = 1;
	int match_count_p1 = 0;
	
	init_potentials_p1(cost_p1);
	
	while (EMX_RecvSync(0, 1, 118, -1)) {
		augmenting_path_search_p1();
	}
}


extern void hungarian_parallel_p2(int cost_p2[200][200], int n_p2) {
	int cost_p22[200][200];
	int n_p22;
	double dual_row_p2[200];
	double dual_col_p2[200];
	
	init_potentials_p2(cost_p2);
	
	while (EMX_RecvSync(0, 2, 119, -1)) {
		EMX_Recv(0, 2, 8, -1, dual_col_p2, 200 * sizeof(*dual_col_p2));
		
		EMX_Recv(0, 2, 4, -1, dual_row_p2, 200 * sizeof(*dual_row_p2));
		
		augmenting_path_search_p2(n_p2, dual_row_p2, dual_col_p2);
	}
}


extern void hungarian_parallel_p3(int cost_p3[200][200]) {
	int cost_p32[200][200];
	double dual_row_p3[200];
	double dual_col_p3[200];
	
	init_potentials_p3(cost_p3);
	
	while (EMX_RecvSync(0, 3, 120, -1)) {
		EMX_Recv(0, 3, 9, -1, dual_col_p3, 200 * sizeof(*dual_col_p3));
		
		EMX_Recv(0, 3, 5, -1, dual_row_p3, 200 * sizeof(*dual_row_p3));
		
		augmenting_path_search_p3(dual_row_p3, dual_col_p3);
	}
}


extern void hungarian_parallel_p4(void) {
	double dual_col_p4[200];
	double dual_row_p4[200];
	
	while (EMX_RecvSync(0, 4, 121, -1)) {
		EMX_Recv(0, 4, 7, -1, dual_row_p4, 200 * sizeof(*dual_row_p4));
		
		EMX_Recv(0, 4, 11, -1, dual_col_p4, 200 * sizeof(*dual_col_p4));
		
		augmenting_path_search_p4(dual_row_p4, dual_col_p4);
	}
}


extern void hungarian_parallel_p5(void) {
	double dual_col_p5[200];
	double dual_row_p5[200];
	
	while (EMX_RecvSync(0, 5, 122, -1)) {
		EMX_Recv(0, 5, 6, -1, dual_row_p5, 200 * sizeof(*dual_row_p5));
		
		EMX_Recv(0, 5, 10, -1, dual_col_p5, 200 * sizeof(*dual_col_p5));
		
		augmenting_path_search_p5(dual_row_p5, dual_col_p5);
	}
}


extern void hungarian_parallel_p6(void) {
	while (EMX_RecvSync(0, 6, 123, -1)) {
		augmenting_path_search_p6();
	}
}


extern void hungarian_parallel_p7(void) {
	while (EMX_RecvSync(0, 7, 124, -1)) {
		augmenting_path_search_p7();
	}
}


int main_p0() {
	int cost_p0[200][200];
	long callarg2_p0;
	srand(time(NULL));	
	for (int i_p0 = 0; i_p0 < 200; i_p0 = i_p0 + 1) {
		for (int j_p0 = 0; j_p0 < 200; j_p0 = j_p0 + 1) {
			callarg2_p0 = rand();
			
			cost_p0[i_p0][j_p0] = callarg2_p0 % n + 1;
		}
	}
	
	EMX_Send(0, 3, 3, -1, cost_p0, 200 * sizeof(*cost_p0));
	
	EMX_Send(0, 1, 2, -1, cost_p0, 200 * sizeof(*cost_p0));
	
	EMX_Send(0, 2, 1, -1, cost_p0, 200 * sizeof(*cost_p0));
	
	{
		int x_p0;
	

		long t1, t2;
		struct timeval timecheck;		
	
		gettimeofday(&timecheck, NULL);
		t1 = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
		clock_t start = clock();	
		x_p0 = hungarian_parallel_p0(cost_p0, n);
		clock_t end = clock();	

		gettimeofday(&timecheck, NULL);
		t2 = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
	
		double time = (double)(end-start) / CLOCKS_PER_SEC * 1000.0;	
		long timing = (long)(t2-t1);	
		EMX_Wait(1, 0, 0, -1);
		
		{
			double time_p0;
			
			printf("Hungarian parallel:\n");
			
			time_p0 = EMX_Recv64F(1, 0, 97, -1);
			printf("Total Time:\t%f\n", timing / 1000.0);	

			printf("Total CPU time:\t%f\n", time);
			
			printf("Total Cost:\t%d\n\n", x_p0);
			
			return 0;
		}
	}
}


void main_p1() {
	int cost_p1[200][200];
	time_t callarg_p1;
	
	callarg_p1 = time((void *)0);
	
	srand(callarg_p1);
	
	EMX_Recv(0, 1, 2, -1, cost_p1, 200 * sizeof(*cost_p1));
	
	{
		clock_t start_p1;
		clock_t end_p1;
		
		hungarian_parallel_p1(cost_p1);
		
		printf("START PARALLEL\n");
		
		start_p1 = clock();
		
		end_p1 = clock();
		
		EMX_Signal(1, 0, 0, -1);
		
		{
			double time_p1 = (double)(end_p1 - start_p1) / CLOCKS_PER_SEC * 1000.0;
			
			EMX_Send64F(1, 0, 97, -1, time_p1);
		}
	}
}


void main_p2() {
	int cost_p2[200][200];
	
	EMX_Recv(0, 2, 1, -1, cost_p2, 200 * sizeof(*cost_p2));
	
	hungarian_parallel_p2(cost_p2, n);
	
}


void main_p3() {
	int cost_p3[200][200];
	
	EMX_Recv(0, 3, 3, -1, cost_p3, 200 * sizeof(*cost_p3));
	
	hungarian_parallel_p3(cost_p3);
	
}


void main_p4() {
	hungarian_parallel_p4();
	
}


void main_p5() {
	hungarian_parallel_p5();
	
}


void main_p6() {
	hungarian_parallel_p6();
	
}


void main_p7() {
	hungarian_parallel_p7();
	
}

