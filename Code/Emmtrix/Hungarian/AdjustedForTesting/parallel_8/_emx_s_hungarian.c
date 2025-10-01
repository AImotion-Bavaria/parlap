#include <stdio.h>
#include "_emx_main.h"
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

#define inf INT_MAX

#define N 80 
#define N_18 10 
#define N_28 20 
#define N_38 30 
#define N_48 40 
#define N_58 50 
#define N_68 60 
#define N_78 70 

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
	double d_row_split1_p0[N_18];
	size_t j1_p0;
	size_t i3_p0;
	double d_row_split2_p0[N_18];
	double d_row_split3_p0[N_18];
	double d_row_split4_p0[N_18];
	double d_row_split5_p0[N_18];
	double d_row_split6_p0[N_18];
	double d_row_split7_p0[N_18];
	double d_row_split8_p0[N_18];
	size_t j2_p0;
	double d_col_split1_p0[N_18];
	size_t i2_p0;
	size_t i4_p0;
	double d_col_split2_p0[N_18];
	double d_col_split3_p0[N_18];
	double d_col_split4_p0[N_18];
	double d_col_split5_p0[N_18];
	double d_col_split6_p0[N_18];
	double d_col_split7_p0[N_18];
	double d_col_split8_p0[N_18];
	
	for (i1_p0 = 0u; i1_p0 < N_18; i1_p0 = i1_p0 + 1) {
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
	
	for (i1_p0 = N_18; i1_p0 < N_28; i1_p0 = i1_p0 + 1) {
		for (j1_p0 = 0u; j1_p0 < N; j1_p0 = j1_p0 + 1) {
		}
	}
	
	for (i1_p0 = N_28; i1_p0 < N_38; i1_p0 = i1_p0 + 1) {
		for (j1_p0 = 0u; j1_p0 < N; j1_p0 = j1_p0 + 1) {
		}
	}
	
	for (i1_p0 = N_38; i1_p0 < N_48; i1_p0 = i1_p0 + 1) {
		for (j1_p0 = 0u; j1_p0 < N; j1_p0 = j1_p0 + 1) {
		}
	}
	
	for (i1_p0 = N_48; i1_p0 < N_58; i1_p0 = i1_p0 + 1) {
		for (j1_p0 = 0u; j1_p0 < N; j1_p0 = j1_p0 + 1) {
		}
	}
	
	for (i1_p0 = N_58; i1_p0 < N_68; i1_p0 = i1_p0 + 1) {
		for (j1_p0 = 0u; j1_p0 < N; j1_p0 = j1_p0 + 1) {
		}
	}
	
	for (i1_p0 = N_68; i1_p0 < N_78; i1_p0 = i1_p0 + 1) {
		for (j1_p0 = 0u; j1_p0 < N; j1_p0 = j1_p0 + 1) {
		}
	}
	
	for (i1_p0 = N_78; i1_p0 < N; i1_p0 = i1_p0 + 1) {
		for (j1_p0 = 0u; j1_p0 < N; j1_p0 = j1_p0 + 1) {
		}
	}
	
	for (i3_p0 = 0u; i3_p0 < N_18; i3_p0 = i3_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_row_split1_p0[i3_p0 - 0];
		dual_row_p0[i3_p0] = val2_p0;
	}
	
	EMX_Recv(1, 0, 38, -1, d_row_split2_p0, N_18 * sizeof(*d_row_split2_p0));
	
	for (i3_p0 = N_18; i3_p0 < N_28; i3_p0 = i3_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_row_split2_p0[i3_p0 - N_18];
		dual_row_p0[i3_p0] = val2_p0;
	}
	
	EMX_Recv(2, 0, 39, -1, d_row_split3_p0, N_18 * sizeof(*d_row_split3_p0));
	
	for (i3_p0 = N_28; i3_p0 < N_38; i3_p0 = i3_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_row_split3_p0[i3_p0 - N_28];
		dual_row_p0[i3_p0] = val2_p0;
	}
	
	EMX_Recv(3, 0, 40, -1, d_row_split4_p0, N_18 * sizeof(*d_row_split4_p0));
	
	for (i3_p0 = N_38; i3_p0 < N_48; i3_p0 = i3_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_row_split4_p0[i3_p0 - N_38];
		dual_row_p0[i3_p0] = val2_p0;
	}
	
	EMX_Recv(4, 0, 41, -1, d_row_split5_p0, N_18 * sizeof(*d_row_split5_p0));
	
	for (i3_p0 = N_48; i3_p0 < N_58; i3_p0 = i3_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_row_split5_p0[i3_p0 - N_48];
		dual_row_p0[i3_p0] = val2_p0;
	}
	
	EMX_Recv(5, 0, 42, -1, d_row_split6_p0, N_18 * sizeof(*d_row_split6_p0));
	
	for (i3_p0 = N_58; i3_p0 < N_68; i3_p0 = i3_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_row_split6_p0[i3_p0 - N_58];
		dual_row_p0[i3_p0] = val2_p0;
	}
	
	EMX_Recv(6, 0, 43, -1, d_row_split7_p0, N_18 * sizeof(*d_row_split7_p0));
	
	for (i3_p0 = N_68; i3_p0 < N_78; i3_p0 = i3_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_row_split7_p0[i3_p0 - N_68];
		dual_row_p0[i3_p0] = val2_p0;
	}
	
	EMX_Recv(7, 0, 44, -1, d_row_split8_p0, N_18 * sizeof(*d_row_split8_p0));
	
	for (i3_p0 = N_78; i3_p0 < N; i3_p0 = i3_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_row_split8_p0[i3_p0 - N_78];
		dual_row_p0[i3_p0] = val2_p0;
	}
	
	for (j2_p0 = 0u; j2_p0 < N_18; j2_p0 = j2_p0 + 1) {
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
	
	EMX_Send(0, 1, 32, -1, dual_row_p0, N * sizeof(*dual_row_p0));
	
	for (j2_p0 = N_18; j2_p0 < N_28; j2_p0 = j2_p0 + 1) {
		for (i2_p0 = 0u; i2_p0 < N; i2_p0 = i2_p0 + 1) {
		}
	}
	
	EMX_Send(0, 2, 31, -1, dual_row_p0, N * sizeof(*dual_row_p0));
	
	for (j2_p0 = N_28; j2_p0 < N_38; j2_p0 = j2_p0 + 1) {
		for (i2_p0 = 0u; i2_p0 < N; i2_p0 = i2_p0 + 1) {
		}
	}
	
	EMX_Send(0, 3, 33, -1, dual_row_p0, N * sizeof(*dual_row_p0));
	
	for (j2_p0 = N_38; j2_p0 < N_48; j2_p0 = j2_p0 + 1) {
		for (i2_p0 = 0u; i2_p0 < N; i2_p0 = i2_p0 + 1) {
		}
	}
	
	EMX_Send(0, 4, 35, -1, dual_row_p0, N * sizeof(*dual_row_p0));
	
	for (j2_p0 = N_48; j2_p0 < N_58; j2_p0 = j2_p0 + 1) {
		for (i2_p0 = 0u; i2_p0 < N; i2_p0 = i2_p0 + 1) {
		}
	}
	
	EMX_Send(0, 5, 34, -1, dual_row_p0, N * sizeof(*dual_row_p0));
	
	for (j2_p0 = N_58; j2_p0 < N_68; j2_p0 = j2_p0 + 1) {
		for (i2_p0 = 0u; i2_p0 < N; i2_p0 = i2_p0 + 1) {
		}
	}
	
	EMX_Send(0, 6, 37, -1, dual_row_p0, N * sizeof(*dual_row_p0));
	
	for (j2_p0 = N_68; j2_p0 < N_78; j2_p0 = j2_p0 + 1) {
		for (i2_p0 = 0u; i2_p0 < N; i2_p0 = i2_p0 + 1) {
		}
	}
	
	EMX_Send(0, 7, 36, -1, dual_row_p0, N * sizeof(*dual_row_p0));
	
	for (j2_p0 = N_78; j2_p0 < N; j2_p0 = j2_p0 + 1) {
		for (i2_p0 = 0u; i2_p0 < N; i2_p0 = i2_p0 + 1) {
		}
	}
	
	for (i4_p0 = 0u; i4_p0 < N_18; i4_p0 = i4_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_col_split1_p0[i4_p0 - 0];
		dual_col_p0[i4_p0] = val2_p0;
	}
	
	EMX_Recv(1, 0, 45, -1, d_col_split2_p0, N_18 * sizeof(*d_col_split2_p0));
	
	for (i4_p0 = N_18; i4_p0 < N_28; i4_p0 = i4_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_col_split2_p0[i4_p0 - N_18];
		dual_col_p0[i4_p0] = val2_p0;
	}
	
	EMX_Recv(2, 0, 46, -1, d_col_split3_p0, N_18 * sizeof(*d_col_split3_p0));
	
	for (i4_p0 = N_28; i4_p0 < N_38; i4_p0 = i4_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_col_split3_p0[i4_p0 - N_28];
		dual_col_p0[i4_p0] = val2_p0;
	}
	
	EMX_Recv(3, 0, 47, -1, d_col_split4_p0, N_18 * sizeof(*d_col_split4_p0));
	
	for (i4_p0 = N_38; i4_p0 < N_48; i4_p0 = i4_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_col_split4_p0[i4_p0 - N_38];
		dual_col_p0[i4_p0] = val2_p0;
	}
	
	EMX_Recv(4, 0, 48, -1, d_col_split5_p0, N_18 * sizeof(*d_col_split5_p0));
	
	for (i4_p0 = N_48; i4_p0 < N_58; i4_p0 = i4_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_col_split5_p0[i4_p0 - N_48];
		dual_col_p0[i4_p0] = val2_p0;
	}
	
	EMX_Recv(5, 0, 49, -1, d_col_split6_p0, N_18 * sizeof(*d_col_split6_p0));
	
	for (i4_p0 = N_58; i4_p0 < N_68; i4_p0 = i4_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_col_split6_p0[i4_p0 - N_58];
		dual_col_p0[i4_p0] = val2_p0;
	}
	
	EMX_Recv(6, 0, 50, -1, d_col_split7_p0, N_18 * sizeof(*d_col_split7_p0));
	
	for (i4_p0 = N_68; i4_p0 < N_78; i4_p0 = i4_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_col_split7_p0[i4_p0 - N_68];
		dual_col_p0[i4_p0] = val2_p0;
	}
	
	EMX_Recv(7, 0, 51, -1, d_col_split8_p0, N_18 * sizeof(*d_col_split8_p0));
	
	for (i4_p0 = N_78; i4_p0 < N; i4_p0 = i4_p0 + 1) {
		double val2_p0;
		
		val2_p0 = d_col_split8_p0[i4_p0 - N_78];
		dual_col_p0[i4_p0] = val2_p0;
	}
}


extern void init_potentials_p1(int cost_p1[N][N]) {
	double dual_row_p1[N];
	size_t i1_p1;
	double d_row_split2_p1[N_18];
	size_t j1_p1;
	size_t j2_p1;
	double d_col_split2_p1[N_18];
	size_t i2_p1;
	
	for (i1_p1 = N_18; i1_p1 < N_28; i1_p1 = i1_p1 + 1) {
		double temp_p1 = 0x7fffffff;
		double val2_p1;
		
		
		
		
		
		
		
		for (j1_p1 = 0u; j1_p1 < N; j1_p1 = j1_p1 + 1) {
			
			
			
			
			
			
			if (temp_p1 > ((double)cost_p1[i1_p1][j1_p1])) {
				temp_p1 = (double)cost_p1[i1_p1][j1_p1];
			}
			
		}
		
		val2_p1 = temp_p1;
		d_row_split2_p1[i1_p1 - N_18] = val2_p1;
		
	}
	
	
	
	
	
	
	
	EMX_Send(1, 0, 38, -1, d_row_split2_p1, N_18 * sizeof(*d_row_split2_p1));
	
	
	
	
	
	
	
	EMX_Recv(0, 1, 32, -1, dual_row_p1, N * sizeof(*dual_row_p1));
	
	for (j2_p1 = N_18; j2_p1 < N_28; j2_p1 = j2_p1 + 1) {
		double temp_p1 = 0x7fffffff;
		double val2_p1;
		
		
		
		
		
		
		
		for (i2_p1 = 0u; i2_p1 < N; i2_p1 = i2_p1 + 1) {
			
			
			
			
			
			
			if (temp_p1 > (cost_p1[i2_p1][j2_p1] - dual_row_p1[i2_p1])) {
				temp_p1 = cost_p1[i2_p1][j2_p1] - dual_row_p1[i2_p1];
			}
			
		}
		
		val2_p1 = temp_p1;
		d_col_split2_p1[j2_p1 - N_18] = val2_p1;
		
	}
	
	
	
	
	
	
	
	EMX_Send(1, 0, 45, -1, d_col_split2_p1, N_18 * sizeof(*d_col_split2_p1));
	
	
	
	
	
	
}


extern void init_potentials_p2(int cost_p2[N][N]) {
	double dual_row_p2[N];
	size_t i1_p2;
	double d_row_split3_p2[N_18];
	size_t j1_p2;
	size_t j2_p2;
	double d_col_split3_p2[N_18];
	size_t i2_p2;
	
	
	for (i1_p2 = N_28; i1_p2 < N_38; i1_p2 = i1_p2 + 1) {
		double temp_p2 = 0x7fffffff;
		double val2_p2;
		
		
		
		
		
		
		for (j1_p2 = 0u; j1_p2 < N; j1_p2 = j1_p2 + 1) {
			
			
			
			
			
			if (temp_p2 > ((double)cost_p2[i1_p2][j1_p2])) {
				temp_p2 = (double)cost_p2[i1_p2][j1_p2];
			}
			
			
		}
		
		val2_p2 = temp_p2;
		d_row_split3_p2[i1_p2 - N_28] = val2_p2;
		
		
	}
	
	
	
	
	
	
	
	EMX_Send(2, 0, 39, -1, d_row_split3_p2, N_18 * sizeof(*d_row_split3_p2));
	
	
	
	
	
	
	
	EMX_Recv(0, 2, 31, -1, dual_row_p2, N * sizeof(*dual_row_p2));
	
	for (j2_p2 = N_28; j2_p2 < N_38; j2_p2 = j2_p2 + 1) {
		double temp_p2 = 0x7fffffff;
		double val2_p2;
		
		
		
		
		
		
		for (i2_p2 = 0u; i2_p2 < N; i2_p2 = i2_p2 + 1) {
			
			
			
			
			
			if (temp_p2 > (cost_p2[i2_p2][j2_p2] - dual_row_p2[i2_p2])) {
				temp_p2 = cost_p2[i2_p2][j2_p2] - dual_row_p2[i2_p2];
			}
			
			
		}
		
		val2_p2 = temp_p2;
		d_col_split3_p2[j2_p2 - N_28] = val2_p2;
		
		
	}
	
	
	
	
	
	
	
	EMX_Send(2, 0, 46, -1, d_col_split3_p2, N_18 * sizeof(*d_col_split3_p2));
	
	
	
	
	
}


extern void init_potentials_p3(int cost_p3[N][N]) {
	double dual_row_p3[N];
	size_t i1_p3;
	double d_row_split4_p3[N_18];
	size_t j1_p3;
	size_t j2_p3;
	double d_col_split4_p3[N_18];
	size_t i2_p3;
	
	
	
	for (i1_p3 = N_38; i1_p3 < N_48; i1_p3 = i1_p3 + 1) {
		double temp_p3 = 0x7fffffff;
		double val2_p3;
		
		
		
		
		
		for (j1_p3 = 0u; j1_p3 < N; j1_p3 = j1_p3 + 1) {
			
			
			
			
			if (temp_p3 > ((double)cost_p3[i1_p3][j1_p3])) {
				temp_p3 = (double)cost_p3[i1_p3][j1_p3];
			}
			
			
			
		}
		
		val2_p3 = temp_p3;
		d_row_split4_p3[i1_p3 - N_38] = val2_p3;
		
		
		
	}
	
	
	
	
	
	
	
	EMX_Send(3, 0, 40, -1, d_row_split4_p3, N_18 * sizeof(*d_row_split4_p3));
	
	
	
	
	
	
	
	EMX_Recv(0, 3, 33, -1, dual_row_p3, N * sizeof(*dual_row_p3));
	
	for (j2_p3 = N_38; j2_p3 < N_48; j2_p3 = j2_p3 + 1) {
		double temp_p3 = 0x7fffffff;
		double val2_p3;
		
		
		
		
		
		for (i2_p3 = 0u; i2_p3 < N; i2_p3 = i2_p3 + 1) {
			
			
			
			
			if (temp_p3 > (cost_p3[i2_p3][j2_p3] - dual_row_p3[i2_p3])) {
				temp_p3 = cost_p3[i2_p3][j2_p3] - dual_row_p3[i2_p3];
			}
			
			
			
		}
		
		val2_p3 = temp_p3;
		d_col_split4_p3[j2_p3 - N_38] = val2_p3;
		
		
		
	}
	
	
	
	
	
	
	
	EMX_Send(3, 0, 47, -1, d_col_split4_p3, N_18 * sizeof(*d_col_split4_p3));
	
	
	
	
}


extern void init_potentials_p4(int cost_p4[N][N]) {
	double dual_row_p4[N];
	size_t i1_p4;
	double d_row_split5_p4[N_18];
	size_t j1_p4;
	size_t j2_p4;
	double d_col_split5_p4[N_18];
	size_t i2_p4;
	
	
	
	
	for (i1_p4 = N_48; i1_p4 < N_58; i1_p4 = i1_p4 + 1) {
		double temp_p4 = 0x7fffffff;
		double val2_p4;
		
		
		
		
		for (j1_p4 = 0u; j1_p4 < N; j1_p4 = j1_p4 + 1) {
			
			
			
			if (temp_p4 > ((double)cost_p4[i1_p4][j1_p4])) {
				temp_p4 = (double)cost_p4[i1_p4][j1_p4];
			}
			
			
			
			
		}
		
		val2_p4 = temp_p4;
		d_row_split5_p4[i1_p4 - N_48] = val2_p4;
		
		
		
		
	}
	
	
	
	
	
	
	
	EMX_Send(4, 0, 41, -1, d_row_split5_p4, N_18 * sizeof(*d_row_split5_p4));
	
	
	
	
	
	
	
	EMX_Recv(0, 4, 35, -1, dual_row_p4, N * sizeof(*dual_row_p4));
	
	for (j2_p4 = N_48; j2_p4 < N_58; j2_p4 = j2_p4 + 1) {
		double temp_p4 = 0x7fffffff;
		double val2_p4;
		
		
		
		
		for (i2_p4 = 0u; i2_p4 < N; i2_p4 = i2_p4 + 1) {
			
			
			
			if (temp_p4 > (cost_p4[i2_p4][j2_p4] - dual_row_p4[i2_p4])) {
				temp_p4 = cost_p4[i2_p4][j2_p4] - dual_row_p4[i2_p4];
			}
			
			
			
			
		}
		
		val2_p4 = temp_p4;
		d_col_split5_p4[j2_p4 - N_48] = val2_p4;
		
		
		
		
	}
	
	
	
	
	
	
	
	EMX_Send(4, 0, 48, -1, d_col_split5_p4, N_18 * sizeof(*d_col_split5_p4));
	
	
	
}


extern void init_potentials_p5(int cost_p5[N][N]) {
	double dual_row_p5[N];
	size_t i1_p5;
	double d_row_split6_p5[N_18];
	size_t j1_p5;
	size_t j2_p5;
	double d_col_split6_p5[N_18];
	size_t i2_p5;
	
	
	
	
	
	for (i1_p5 = N_58; i1_p5 < N_68; i1_p5 = i1_p5 + 1) {
		double temp_p5 = 0x7fffffff;
		double val2_p5;
		
		
		
		for (j1_p5 = 0u; j1_p5 < N; j1_p5 = j1_p5 + 1) {
			
			
			if (temp_p5 > ((double)cost_p5[i1_p5][j1_p5])) {
				temp_p5 = (double)cost_p5[i1_p5][j1_p5];
			}
			
			
			
			
			
		}
		
		val2_p5 = temp_p5;
		d_row_split6_p5[i1_p5 - N_58] = val2_p5;
		
		
		
		
		
	}
	
	
	
	
	
	
	
	EMX_Send(5, 0, 42, -1, d_row_split6_p5, N_18 * sizeof(*d_row_split6_p5));
	
	
	
	
	
	
	
	EMX_Recv(0, 5, 34, -1, dual_row_p5, N * sizeof(*dual_row_p5));
	
	for (j2_p5 = N_58; j2_p5 < N_68; j2_p5 = j2_p5 + 1) {
		double temp_p5 = 0x7fffffff;
		double val2_p5;
		
		
		
		for (i2_p5 = 0u; i2_p5 < N; i2_p5 = i2_p5 + 1) {
			
			
			if (temp_p5 > (cost_p5[i2_p5][j2_p5] - dual_row_p5[i2_p5])) {
				temp_p5 = cost_p5[i2_p5][j2_p5] - dual_row_p5[i2_p5];
			}
			
			
			
			
			
		}
		
		val2_p5 = temp_p5;
		d_col_split6_p5[j2_p5 - N_58] = val2_p5;
		
		
		
		
		
	}
	
	
	
	
	
	
	
	EMX_Send(5, 0, 49, -1, d_col_split6_p5, N_18 * sizeof(*d_col_split6_p5));
	
	
}


extern void init_potentials_p6(int cost_p6[N][N]) {
	double dual_row_p6[N];
	size_t i1_p6;
	double d_row_split7_p6[N_18];
	size_t j1_p6;
	size_t j2_p6;
	double d_col_split7_p6[N_18];
	size_t i2_p6;
	
	
	
	
	
	
	for (i1_p6 = N_68; i1_p6 < N_78; i1_p6 = i1_p6 + 1) {
		double temp_p6 = 0x7fffffff;
		double val2_p6;
		
		
		for (j1_p6 = 0u; j1_p6 < N; j1_p6 = j1_p6 + 1) {
			
			if (temp_p6 > ((double)cost_p6[i1_p6][j1_p6])) {
				temp_p6 = (double)cost_p6[i1_p6][j1_p6];
			}
			
			
			
			
			
			
		}
		
		val2_p6 = temp_p6;
		d_row_split7_p6[i1_p6 - N_68] = val2_p6;
		
		
		
		
		
		
	}
	
	
	
	
	
	
	
	EMX_Send(6, 0, 43, -1, d_row_split7_p6, N_18 * sizeof(*d_row_split7_p6));
	
	
	
	
	
	
	
	EMX_Recv(0, 6, 37, -1, dual_row_p6, N * sizeof(*dual_row_p6));
	
	for (j2_p6 = N_68; j2_p6 < N_78; j2_p6 = j2_p6 + 1) {
		double temp_p6 = 0x7fffffff;
		double val2_p6;
		
		
		for (i2_p6 = 0u; i2_p6 < N; i2_p6 = i2_p6 + 1) {
			
			if (temp_p6 > (cost_p6[i2_p6][j2_p6] - dual_row_p6[i2_p6])) {
				temp_p6 = cost_p6[i2_p6][j2_p6] - dual_row_p6[i2_p6];
			}
			
			
			
			
			
			
		}
		
		val2_p6 = temp_p6;
		d_col_split7_p6[j2_p6 - N_68] = val2_p6;
		
		
		
		
		
		
	}
	
	
	
	
	
	
	
	EMX_Send(6, 0, 50, -1, d_col_split7_p6, N_18 * sizeof(*d_col_split7_p6));
	
}


extern void init_potentials_p7(int cost_p7[N][N]) {
	double dual_row_p7[N];
	size_t i1_p7;
	double d_row_split8_p7[N_18];
	size_t j1_p7;
	size_t j2_p7;
	double d_col_split8_p7[N_18];
	size_t i2_p7;
	
	
	
	
	
	
	
	for (i1_p7 = N_78; i1_p7 < N; i1_p7 = i1_p7 + 1) {
		double temp_p7 = 0x7fffffff;
		double val2_p7;
		
		for (j1_p7 = 0u; j1_p7 < N; j1_p7 = j1_p7 + 1) {
			if (temp_p7 > ((double)cost_p7[i1_p7][j1_p7])) {
				temp_p7 = (double)cost_p7[i1_p7][j1_p7];
			}
			
			
			
			
			
			
			
		}
		
		val2_p7 = temp_p7;
		d_row_split8_p7[i1_p7 - N_78] = val2_p7;
		
		
		
		
		
		
		
	}
	
	
	
	
	
	
	
	EMX_Send(7, 0, 44, -1, d_row_split8_p7, N_18 * sizeof(*d_row_split8_p7));
	
	
	
	
	
	
	
	EMX_Recv(0, 7, 36, -1, dual_row_p7, N * sizeof(*dual_row_p7));
	
	for (j2_p7 = N_78; j2_p7 < N; j2_p7 = j2_p7 + 1) {
		double temp_p7 = 0x7fffffff;
		double val2_p7;
		
		for (i2_p7 = 0u; i2_p7 < N; i2_p7 = i2_p7 + 1) {
			if (temp_p7 > (cost_p7[i2_p7][j2_p7] - dual_row_p7[i2_p7])) {
				temp_p7 = cost_p7[i2_p7][j2_p7] - dual_row_p7[i2_p7];
			}
			
			
			
			
			
			
			
		}
		
		val2_p7 = temp_p7;
		d_col_split8_p7[j2_p7 - N_78] = val2_p7;
		
		
		
		
		
		
		
	}
	
	
	
	
	
	
	
	EMX_Send(7, 0, 51, -1, d_col_split8_p7, N_18 * sizeof(*d_col_split8_p7));
}


extern void update_pass_p2(double theta_p2, _Bool cov_col_p2[N], double dual_row_p2[N], double dual_col_p2[N], double slack_p2[N]) {
	double d_row_split1_p2[N_18];
	double d_row_split7_p2[N_18];
	size_t k1_p2;
	
	for (int i_p2 = 0; i_p2 < N_18; i_p2 = i_p2 + 1) {
		double val2_p2;
		
		val2_p2 = dual_row_p2[i_p2];
		d_row_split1_p2[i_p2 - 0] = val2_p2;
	}
	
	for (int i_p2 = N_68; i_p2 < N_78; i_p2 = i_p2 + 1) {
		double val2_p2;
		
		val2_p2 = dual_row_p2[i_p2];
		d_row_split7_p2[i_p2 - N_68] = val2_p2;
	}
	
	EMX_Send(2, 5, 92, -1, d_row_split7_p2, N_18 * sizeof(*d_row_split7_p2));
	
	EMX_Send(2, 1, 86, -1, d_row_split1_p2, N_18 * sizeof(*d_row_split1_p2));
	
	{
		double d_col_split1_p2[N_18];
		double d_col_split7_p2[N_18];
		double d_col_split4_p2[N_18];
		double d_col_split6_p2[N_18];
		
		for (int i_p2 = 0; i_p2 < N_18; i_p2 = i_p2 + 1) {
			double val2_p2;
			
			val2_p2 = dual_col_p2[i_p2];
			d_col_split1_p2[i_p2 - 0] = val2_p2;
		}
		
		for (int i_p2 = N_68; i_p2 < N_78; i_p2 = i_p2 + 1) {
			double val2_p2;
			
			val2_p2 = dual_col_p2[i_p2];
			d_col_split7_p2[i_p2 - N_68] = val2_p2;
		}
		
		EMX_Send(2, 6, 100, -1, d_col_split7_p2, N_18 * sizeof(*d_col_split7_p2));
		
		EMX_Recv(7, 2, 99, -1, d_col_split6_p2, N_18 * sizeof(*d_col_split6_p2));
		
		EMX_Recv(5, 2, 97, -1, d_col_split4_p2, N_18 * sizeof(*d_col_split4_p2));
		
		{
			double sl_split1_p2[N_18];
			double sl_split7_p2[N_18];
			
			for (int i_p2 = 0; i_p2 < N_18; i_p2 = i_p2 + 1) {
				double val2_p2;
				
				val2_p2 = slack_p2[i_p2];
				sl_split1_p2[i_p2 - 0] = val2_p2;
			}
			
			for (int i_p2 = N_68; i_p2 < N_78; i_p2 = i_p2 + 1) {
				double val2_p2;
				
				val2_p2 = slack_p2[i_p2];
				sl_split7_p2[i_p2 - N_68] = val2_p2;
			}
			
			EMX_Send(2, 5, 108, -1, sl_split7_p2, N_18 * sizeof(*sl_split7_p2));
			
			EMX_Send(2, 3, 102, -1, sl_split1_p2, N_18 * sizeof(*sl_split1_p2));
			
			{
				int act_split4_p2[N_18];
				int act_split6_p2[N_18];
				
				for (k1_p2 = 0u; k1_p2 < N_18; k1_p2 = k1_p2 + 1) {
					
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
				
				
				
				for (int i_p2 = N_38; i_p2 < N_48; i_p2 = i_p2 + 1) {
					int val2_p2;
					
					val2_p2 = -1;
					act_split4_p2[i_p2 - N_38] = val2_p2;
				}
				
				for (k1_p2 = N_38; k1_p2 < N_48; k1_p2 = k1_p2 + 1) {
					EMX_Send(2, 3, 135, -1, act_split4_p2, N_18 * sizeof(*act_split4_p2));
					
					
					if (!cov_col_p2[k1_p2]) {
						double val22_p2;
						double val3_p2;
						
						val22_p2 = d_col_split4_p2[k1_p2 - N_38];
						val3_p2 = val22_p2 + theta_p2 / 2;
						d_col_split4_p2[k1_p2 - N_38] = val3_p2;
					} else {
						double val22_p2;
						double val3_p2;
						
						val22_p2 = d_col_split4_p2[k1_p2 - N_38];
						val3_p2 = val22_p2 - theta_p2 / 2;
						d_col_split4_p2[k1_p2 - N_38] = val3_p2;
					}
					
					if (EMX_RecvSync(3, 2, 187, -1)) {
						if (EMX_RecvSync(3, 2, 186, -1)) {
							EMX_Recv(3, 2, 139, -1, act_split4_p2, N_18 * sizeof(*act_split4_p2));
						}
					}
				}
				
				EMX_Send(2, 0, 94, -1, d_col_split1_p2, N_18 * sizeof(*d_col_split1_p2));
				
				
				for (int i_p2 = N_58; i_p2 < N_68; i_p2 = i_p2 + 1) {
					int val2_p2;
					
					val2_p2 = -1;
					act_split6_p2[i_p2 - N_58] = val2_p2;
				}
				
				for (k1_p2 = N_58; k1_p2 < N_68; k1_p2 = k1_p2 + 1) {
					EMX_Send(2, 3, 146, -1, act_split6_p2, N_18 * sizeof(*act_split6_p2));
					
					
					if (!cov_col_p2[k1_p2]) {
						double val22_p2;
						double val3_p2;
						
						val22_p2 = d_col_split6_p2[k1_p2 - N_58];
						val3_p2 = val22_p2 + theta_p2 / 2;
						d_col_split6_p2[k1_p2 - N_58] = val3_p2;
					} else {
						double val22_p2;
						double val3_p2;
						
						val22_p2 = d_col_split6_p2[k1_p2 - N_58];
						val3_p2 = val22_p2 - theta_p2 / 2;
						d_col_split6_p2[k1_p2 - N_58] = val3_p2;
					}
					
					if (EMX_RecvSync(3, 2, 191, -1)) {
						if (EMX_RecvSync(3, 2, 190, -1)) {
							EMX_Recv(3, 2, 150, -1, act_split6_p2, N_18 * sizeof(*act_split6_p2));
						}
					}
				}
				
				
				EMX_Send(2, 0, 137, -1, d_col_split4_p2, N_18 * sizeof(*d_col_split4_p2));
				
				
				EMX_Send(2, 1, 134, -1, act_split4_p2, N_18 * sizeof(*act_split4_p2));
				
				EMX_Send(2, 0, 148, -1, d_col_split6_p2, N_18 * sizeof(*d_col_split6_p2));
				
				
				EMX_Send(2, 1, 145, -1, act_split6_p2, N_18 * sizeof(*act_split6_p2));
				
				
			}
		}
	}
}


extern void update_pass_p3(double theta_p3, double dual_row_p3[N], double dual_col_p3[N], double slack_p3[N], int prv_col_p3[N]) {
	_Bool sync182_p3;
	_Bool sync183_p3;
	_Bool sync186_p3;
	_Bool sync187_p3;
	_Bool sync190_p3;
	_Bool sync191_p3;
	double d_row_split2_p3[N_18];
	double d_row_split8_p3[N_18];
	size_t k1_p3;
	
	for (int i_p3 = N_18; i_p3 < N_28; i_p3 = i_p3 + 1) {
		double val2_p3;
		
		val2_p3 = dual_row_p3[i_p3];
		d_row_split2_p3[i_p3 - N_18] = val2_p3;
	}
	
	for (int i_p3 = N_78; i_p3 < N; i_p3 = i_p3 + 1) {
		double val2_p3;
		
		val2_p3 = dual_row_p3[i_p3];
		d_row_split8_p3[i_p3 - N_78] = val2_p3;
	}
	
	EMX_Send(3, 7, 93, -1, d_row_split8_p3, N_18 * sizeof(*d_row_split8_p3));
	
	EMX_Send(3, 4, 87, -1, d_row_split2_p3, N_18 * sizeof(*d_row_split2_p3));
	
	{
		double d_col_split2_p3[N_18];
		double d_col_split8_p3[N_18];
		
		for (int i_p3 = N_18; i_p3 < N_28; i_p3 = i_p3 + 1) {
			double val2_p3;
			
			val2_p3 = dual_col_p3[i_p3];
			d_col_split2_p3[i_p3 - N_18] = val2_p3;
		}
		
		for (int i_p3 = N_78; i_p3 < N; i_p3 = i_p3 + 1) {
			double val2_p3;
			
			val2_p3 = dual_col_p3[i_p3];
			d_col_split8_p3[i_p3 - N_78] = val2_p3;
		}
		
		EMX_Send(3, 7, 101, -1, d_col_split8_p3, N_18 * sizeof(*d_col_split8_p3));
		
		EMX_Send(3, 5, 95, -1, d_col_split2_p3, N_18 * sizeof(*d_col_split2_p3));
		
		{
			double sl_split2_p3[N_18];
			double sl_split8_p3[N_18];
			double sl_split1_p3[N_18];
			double sl_split4_p3[N_18];
			double sl_split6_p3[N_18];
			
			for (int i_p3 = N_18; i_p3 < N_28; i_p3 = i_p3 + 1) {
				double val2_p3;
				
				val2_p3 = slack_p3[i_p3];
				sl_split2_p3[i_p3 - N_18] = val2_p3;
			}
			
			for (int i_p3 = N_78; i_p3 < N; i_p3 = i_p3 + 1) {
				double val2_p3;
				
				val2_p3 = slack_p3[i_p3];
				sl_split8_p3[i_p3 - N_78] = val2_p3;
			}
			
			EMX_Send(3, 7, 109, -1, sl_split8_p3, N_18 * sizeof(*sl_split8_p3));
			
			EMX_Recv(7, 3, 107, -1, sl_split6_p3, N_18 * sizeof(*sl_split6_p3));
			
			EMX_Recv(5, 3, 105, -1, sl_split4_p3, N_18 * sizeof(*sl_split4_p3));
			
			EMX_Send(3, 6, 103, -1, sl_split2_p3, N_18 * sizeof(*sl_split2_p3));
			
			EMX_Recv(2, 3, 102, -1, sl_split1_p3, N_18 * sizeof(*sl_split1_p3));
			
			{
				int act_split1_p3[N_18];
				int act_split4_p3[N_18];
				int act_split6_p3[N_18];
				
				for (k1_p3 = 0u; k1_p3 < N_18; k1_p3 = k1_p3 + 1) {
					EMX_Recv(1, 3, 111, -1, act_split1_p3, N_18 * sizeof(*act_split1_p3));
					
					{
						double val2_p3;
						int cond_p3;
						
						
						
						val2_p3 = sl_split1_p3[k1_p3 - 0];
						cond_p3 = (val2_p3 > 0);
						
						sync183_p3 = cond_p3;
						
						EMX_SendSync(3, 1, 183, -1, sync183_p3);
						
						if (cond_p3, sync183_p3) {
							double val32_p3;
							double val4_p3;
							double val3_p3;
							int cond2_p3;
							
							val32_p3 = sl_split1_p3[k1_p3 - 0];
							val4_p3 = val32_p3 - theta_p3;
							sl_split1_p3[k1_p3 - 0] = val4_p3;
							val3_p3 = sl_split1_p3[k1_p3 - 0];
							cond2_p3 = (val3_p3 == 0);
							
							sync182_p3 = cond2_p3;
							
							EMX_SendSync(3, 1, 182, -1, sync182_p3);
							
							if (cond2_p3, sync182_p3) {
								int val5_p3;
								
								val5_p3 = prv_col_p3[k1_p3];
								act_split1_p3[k1_p3 - 0] = val5_p3;
								
								EMX_Send(3, 1, 120, -1, act_split1_p3, N_18 * sizeof(*act_split1_p3));
							}
						}
					}
				}
				
				
				
				for (k1_p3 = N_38; k1_p3 < N_48; k1_p3 = k1_p3 + 1) {
					EMX_Recv(2, 3, 135, -1, act_split4_p3, N_18 * sizeof(*act_split4_p3));
					
					{
						double val2_p3;
						int cond_p3;
						
						
						
						val2_p3 = sl_split4_p3[k1_p3 - N_38];
						cond_p3 = (val2_p3 > 0);
						
						sync187_p3 = cond_p3;
						
						EMX_SendSync(3, 2, 187, -1, sync187_p3);
						
						if (cond_p3, sync187_p3) {
							double val32_p3;
							double val4_p3;
							double val3_p3;
							int cond2_p3;
							
							val32_p3 = sl_split4_p3[k1_p3 - N_38];
							val4_p3 = val32_p3 - theta_p3;
							sl_split4_p3[k1_p3 - N_38] = val4_p3;
							val3_p3 = sl_split4_p3[k1_p3 - N_38];
							cond2_p3 = (val3_p3 == 0);
							
							sync186_p3 = cond2_p3;
							
							EMX_SendSync(3, 2, 186, -1, sync186_p3);
							
							if (cond2_p3, sync186_p3) {
								int val5_p3;
								
								val5_p3 = prv_col_p3[k1_p3];
								act_split4_p3[k1_p3 - N_38] = val5_p3;
								
								EMX_Send(3, 2, 139, -1, act_split4_p3, N_18 * sizeof(*act_split4_p3));
							}
						}
					}
				}
				
				EMX_Send(3, 0, 118, -1, sl_split1_p3, N_18 * sizeof(*sl_split1_p3));
				
				
				for (k1_p3 = N_58; k1_p3 < N_68; k1_p3 = k1_p3 + 1) {
					EMX_Recv(2, 3, 146, -1, act_split6_p3, N_18 * sizeof(*act_split6_p3));
					
					{
						double val2_p3;
						int cond_p3;
						
						
						
						val2_p3 = sl_split6_p3[k1_p3 - N_58];
						cond_p3 = (val2_p3 > 0);
						
						sync191_p3 = cond_p3;
						
						EMX_SendSync(3, 2, 191, -1, sync191_p3);
						
						if (cond_p3, sync191_p3) {
							double val32_p3;
							double val4_p3;
							double val3_p3;
							int cond2_p3;
							
							val32_p3 = sl_split6_p3[k1_p3 - N_58];
							val4_p3 = val32_p3 - theta_p3;
							sl_split6_p3[k1_p3 - N_58] = val4_p3;
							val3_p3 = sl_split6_p3[k1_p3 - N_58];
							cond2_p3 = (val3_p3 == 0);
							
							sync190_p3 = cond2_p3;
							
							EMX_SendSync(3, 2, 190, -1, sync190_p3);
							
							if (cond2_p3, sync190_p3) {
								int val5_p3;
								
								val5_p3 = prv_col_p3[k1_p3];
								act_split6_p3[k1_p3 - N_58] = val5_p3;
								
								EMX_Send(3, 2, 150, -1, act_split6_p3, N_18 * sizeof(*act_split6_p3));
							}
						}
					}
				}
				
				
				EMX_Send(3, 0, 136, -1, sl_split4_p3, N_18 * sizeof(*sl_split4_p3));
				
				
				
				EMX_Send(3, 0, 147, -1, sl_split6_p3, N_18 * sizeof(*sl_split6_p3));
				
				
				
				
			}
		}
	}
}


extern void update_pass_p4(double theta_p4, _Bool cov_row_p4[N], double dual_row_p4[N], double dual_col_p4[N], double slack_p4[N]) {
	_Bool sync192_p4;
	_Bool active_p4[N];
	double d_row_split3_p4[N_18];
	size_t k1_p4;
	double d_row_split2_p4[N_18];
	double d_row_split5_p4[N_18];
	
	for (int i_p4 = N_28; i_p4 < N_38; i_p4 = i_p4 + 1) {
		double val2_p4;
		
		val2_p4 = dual_row_p4[i_p4];
		d_row_split3_p4[i_p4 - N_28] = val2_p4;
	}
	
	EMX_Recv(6, 4, 90, -1, d_row_split5_p4, N_18 * sizeof(*d_row_split5_p4));
	
	EMX_Send(4, 7, 88, -1, d_row_split3_p4, N_18 * sizeof(*d_row_split3_p4));
	
	EMX_Recv(3, 4, 87, -1, d_row_split2_p4, N_18 * sizeof(*d_row_split2_p4));
	
	{
		double d_col_split3_p4[N_18];
		
		for (int i_p4 = N_28; i_p4 < N_38; i_p4 = i_p4 + 1) {
			double val2_p4;
			
			val2_p4 = dual_col_p4[i_p4];
			d_col_split3_p4[i_p4 - N_28] = val2_p4;
		}
		
		EMX_Send(4, 7, 96, -1, d_col_split3_p4, N_18 * sizeof(*d_col_split3_p4));
		
		{
			double sl_split3_p4[N_18];
			
			for (int i_p4 = N_28; i_p4 < N_38; i_p4 = i_p4 + 1) {
				double val2_p4;
				
				val2_p4 = slack_p4[i_p4];
				sl_split3_p4[i_p4 - N_28] = val2_p4;
			}
			
			EMX_Send(4, 7, 104, -1, sl_split3_p4, N_18 * sizeof(*sl_split3_p4));
			
			{
				int act_split2_p4[N_18];
				
				
				for (int i_p4 = N_18; i_p4 < N_28; i_p4 = i_p4 + 1) {
					int val2_p4;
					
					val2_p4 = -1;
					act_split2_p4[i_p4 - N_18] = val2_p4;
				}
				
				for (k1_p4 = N_18; k1_p4 < N_28; k1_p4 = k1_p4 + 1) {
					EMX_Send(4, 6, 121, -1, act_split2_p4, N_18 * sizeof(*act_split2_p4));
					
					
					
					
					if (!cov_row_p4[k1_p4]) {
						double val22_p4;
						double val3_p4;
						
						val22_p4 = d_row_split2_p4[k1_p4 - N_18];
						val3_p4 = val22_p4 + theta_p4 / 2;
						d_row_split2_p4[k1_p4 - N_18] = val3_p4;
					} else {
						double val22_p4;
						double val3_p4;
						
						val22_p4 = d_row_split2_p4[k1_p4 - N_18];
						val3_p4 = val22_p4 - theta_p4 / 2;
						d_row_split2_p4[k1_p4 - N_18] = val3_p4;
					}
					
					
					if (EMX_RecvSync(6, 4, 185, -1)) {
						if (EMX_RecvSync(6, 4, 184, -1)) {
							EMX_Recv(6, 4, 129, -1, act_split2_p4, N_18 * sizeof(*act_split2_p4));
						}
					}
					
					
					
					
					
					
					
					
					
					
					
					
				}
				
				
				
				for (k1_p4 = N_48; k1_p4 < N_58; k1_p4 = k1_p4 + 1) {
					
					
					
					if (!cov_row_p4[k1_p4]) {
						double val22_p4;
						double val3_p4;
						
						val22_p4 = d_row_split5_p4[k1_p4 - N_48];
						val3_p4 = val22_p4 + theta_p4 / 2;
						d_row_split5_p4[k1_p4 - N_48] = val3_p4;
					} else {
						double val22_p4;
						double val3_p4;
						
						val22_p4 = d_row_split5_p4[k1_p4 - N_48];
						val3_p4 = val22_p4 - theta_p4 / 2;
						d_row_split5_p4[k1_p4 - N_48] = val3_p4;
					}
					
					
					
					
					
					
					
					
					
					
					
					
					
					
				}
				
				
				EMX_Send(4, 0, 128, -1, d_row_split2_p4, N_18 * sizeof(*d_row_split2_p4));
				
				for (int i_p4 = N_18; i_p4 < N_28; i_p4 = i_p4 + 1) {
					int val5_p4;
					int cond_p4;
					
					val5_p4 = act_split2_p4[i_p4 - N_18];
					cond_p4 = (val5_p4 != (-1));
					
					EMX_Recv(0, 4, 85, -1, active_p4, N * sizeof(*active_p4));
					
					sync192_p4 = cond_p4;
					
					EMX_SendSync(4, 0, 192, -1, sync192_p4);
					
					if (cond_p4, sync192_p4) {
						int val6_p4;
						int tmp_p4;
						
						val6_p4 = act_split2_p4[i_p4 - N_18];
						tmp_p4 = val6_p4;
						active_p4[tmp_p4] = 1;
						
						EMX_Send(4, 0, 152, -1, active_p4, N * sizeof(*active_p4));
					}
				}
				
				
				
				EMX_Send(4, 0, 143, -1, d_row_split5_p4, N_18 * sizeof(*d_row_split5_p4));
				
				
				
				
				
			}
		}
	}
}


extern void update_pass_p5(double theta_p5, _Bool cov_row_p5[N], _Bool cov_col_p5[N], double dual_row_p5[N], double dual_col_p5[N], double slack_p5[N], int prv_col_p5[N]) {
	double d_row_split4_p5[N_18];
	size_t k1_p5;
	double d_row_split7_p5[N_18];
	
	for (int i_p5 = N_38; i_p5 < N_48; i_p5 = i_p5 + 1) {
		double val2_p5;
		
		val2_p5 = dual_row_p5[i_p5];
		d_row_split4_p5[i_p5 - N_38] = val2_p5;
	}
	
	EMX_Recv(2, 5, 92, -1, d_row_split7_p5, N_18 * sizeof(*d_row_split7_p5));
	
	EMX_Send(5, 1, 89, -1, d_row_split4_p5, N_18 * sizeof(*d_row_split4_p5));
	
	{
		double d_col_split4_p5[N_18];
		double d_col_split2_p5[N_18];
		double d_col_split5_p5[N_18];
		
		for (int i_p5 = N_38; i_p5 < N_48; i_p5 = i_p5 + 1) {
			double val2_p5;
			
			val2_p5 = dual_col_p5[i_p5];
			d_col_split4_p5[i_p5 - N_38] = val2_p5;
		}
		
		EMX_Recv(6, 5, 98, -1, d_col_split5_p5, N_18 * sizeof(*d_col_split5_p5));
		
		EMX_Send(5, 2, 97, -1, d_col_split4_p5, N_18 * sizeof(*d_col_split4_p5));
		
		EMX_Recv(3, 5, 95, -1, d_col_split2_p5, N_18 * sizeof(*d_col_split2_p5));
		
		{
			double sl_split4_p5[N_18];
			double sl_split7_p5[N_18];
			
			for (int i_p5 = N_38; i_p5 < N_48; i_p5 = i_p5 + 1) {
				double val2_p5;
				
				val2_p5 = slack_p5[i_p5];
				sl_split4_p5[i_p5 - N_38] = val2_p5;
			}
			
			EMX_Recv(2, 5, 108, -1, sl_split7_p5, N_18 * sizeof(*sl_split7_p5));
			
			EMX_Send(5, 3, 105, -1, sl_split4_p5, N_18 * sizeof(*sl_split4_p5));
			
			{
				int act_split5_p5[N_18];
				int act_split7_p5[N_18];
				
				
				for (k1_p5 = N_18; k1_p5 < N_28; k1_p5 = k1_p5 + 1) {
					
					if (!cov_col_p5[k1_p5]) {
						double val22_p5;
						double val3_p5;
						
						val22_p5 = d_col_split2_p5[k1_p5 - N_18];
						val3_p5 = val22_p5 + theta_p5 / 2;
						d_col_split2_p5[k1_p5 - N_18] = val3_p5;
					} else {
						double val22_p5;
						double val3_p5;
						
						val22_p5 = d_col_split2_p5[k1_p5 - N_18];
						val3_p5 = val22_p5 - theta_p5 / 2;
						d_col_split2_p5[k1_p5 - N_18] = val3_p5;
					}
					
				}
				
				
				
				for (int i_p5 = N_48; i_p5 < N_58; i_p5 = i_p5 + 1) {
					int val2_p5;
					
					val2_p5 = -1;
					act_split5_p5[i_p5 - N_48] = val2_p5;
				}
				
				for (k1_p5 = N_48; k1_p5 < N_58; k1_p5 = k1_p5 + 1) {
					EMX_Send(5, 6, 141, -1, act_split5_p5, N_18 * sizeof(*act_split5_p5));
					
					
					if (!cov_col_p5[k1_p5]) {
						double val22_p5;
						double val3_p5;
						
						val22_p5 = d_col_split5_p5[k1_p5 - N_48];
						val3_p5 = val22_p5 + theta_p5 / 2;
						d_col_split5_p5[k1_p5 - N_48] = val3_p5;
					} else {
						double val22_p5;
						double val3_p5;
						
						val22_p5 = d_col_split5_p5[k1_p5 - N_48];
						val3_p5 = val22_p5 - theta_p5 / 2;
						d_col_split5_p5[k1_p5 - N_48] = val3_p5;
					}
					
					if (EMX_RecvSync(6, 5, 189, -1)) {
						if (EMX_RecvSync(6, 5, 188, -1)) {
							EMX_Recv(6, 5, 144, -1, act_split5_p5, N_18 * sizeof(*act_split5_p5));
						}
					}
				}
				
				
				EMX_Send(5, 0, 127, -1, d_col_split2_p5, N_18 * sizeof(*d_col_split2_p5));
				
				
				for (int i_p5 = N_68; i_p5 < N_78; i_p5 = i_p5 + 1) {
					int val2_p5;
					
					val2_p5 = -1;
					act_split7_p5[i_p5 - N_68] = val2_p5;
				}
				
				for (k1_p5 = N_68; k1_p5 < N_78; k1_p5 = k1_p5 + 1) {
					double val2_p5;
					int cond_p5;
					
					
					
					
					if (!cov_row_p5[k1_p5]) {
						double val22_p5;
						double val3_p5;
						
						val22_p5 = d_row_split7_p5[k1_p5 - N_68];
						val3_p5 = val22_p5 + theta_p5 / 2;
						d_row_split7_p5[k1_p5 - N_68] = val3_p5;
					} else {
						double val22_p5;
						double val3_p5;
						
						val22_p5 = d_row_split7_p5[k1_p5 - N_68];
						val3_p5 = val22_p5 - theta_p5 / 2;
						d_row_split7_p5[k1_p5 - N_68] = val3_p5;
					}
					
					
					val2_p5 = sl_split7_p5[k1_p5 - N_68];
					cond_p5 = (val2_p5 > 0);
					
					if (cond_p5) {
						double val32_p5;
						double val4_p5;
						double val3_p5;
						int cond2_p5;
						
						val32_p5 = sl_split7_p5[k1_p5 - N_68];
						val4_p5 = val32_p5 - theta_p5;
						sl_split7_p5[k1_p5 - N_68] = val4_p5;
						val3_p5 = sl_split7_p5[k1_p5 - N_68];
						cond2_p5 = (val3_p5 == 0);
						
						if (cond2_p5) {
							int val5_p5;
							
							val5_p5 = prv_col_p5[k1_p5];
							act_split7_p5[k1_p5 - N_68] = val5_p5;
						}
					}
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
				}
				
				EMX_Send(5, 0, 142, -1, d_col_split5_p5, N_18 * sizeof(*d_col_split5_p5));
				
				EMX_Send(5, 1, 140, -1, act_split5_p5, N_18 * sizeof(*act_split5_p5));
				
				
				EMX_Send(5, 0, 164, -1, d_row_split7_p5, N_18 * sizeof(*d_row_split7_p5));
				
				EMX_Send(5, 0, 162, -1, sl_split7_p5, N_18 * sizeof(*sl_split7_p5));
				
				EMX_Send(5, 1, 160, -1, act_split7_p5, N_18 * sizeof(*act_split7_p5));
				
			}
		}
	}
}


extern void update_pass_p6(double theta_p6, _Bool cov_col_p6[N], double dual_row_p6[N], double dual_col_p6[N], double slack_p6[N], int prv_col_p6[N]) {
	_Bool sync184_p6;
	_Bool sync185_p6;
	_Bool sync188_p6;
	_Bool sync189_p6;
	double d_row_split5_p6[N_18];
	size_t k1_p6;
	
	for (int i_p6 = N_48; i_p6 < N_58; i_p6 = i_p6 + 1) {
		double val2_p6;
		
		val2_p6 = dual_row_p6[i_p6];
		d_row_split5_p6[i_p6 - N_48] = val2_p6;
	}
	
	EMX_Send(6, 4, 90, -1, d_row_split5_p6, N_18 * sizeof(*d_row_split5_p6));
	
	{
		double d_col_split5_p6[N_18];
		double d_col_split7_p6[N_18];
		
		for (int i_p6 = N_48; i_p6 < N_58; i_p6 = i_p6 + 1) {
			double val2_p6;
			
			val2_p6 = dual_col_p6[i_p6];
			d_col_split5_p6[i_p6 - N_48] = val2_p6;
		}
		
		EMX_Recv(2, 6, 100, -1, d_col_split7_p6, N_18 * sizeof(*d_col_split7_p6));
		
		EMX_Send(6, 5, 98, -1, d_col_split5_p6, N_18 * sizeof(*d_col_split5_p6));
		
		{
			double sl_split5_p6[N_18];
			double sl_split2_p6[N_18];
			
			for (int i_p6 = N_48; i_p6 < N_58; i_p6 = i_p6 + 1) {
				double val2_p6;
				
				val2_p6 = slack_p6[i_p6];
				sl_split5_p6[i_p6 - N_48] = val2_p6;
			}
			
			EMX_Recv(3, 6, 103, -1, sl_split2_p6, N_18 * sizeof(*sl_split2_p6));
			
			{
				int act_split2_p6[N_18];
				int act_split5_p6[N_18];
				
				
				for (k1_p6 = N_18; k1_p6 < N_28; k1_p6 = k1_p6 + 1) {
					EMX_Recv(4, 6, 121, -1, act_split2_p6, N_18 * sizeof(*act_split2_p6));
					
					{
						double val2_p6;
						int cond_p6;
						
						
						
						val2_p6 = sl_split2_p6[k1_p6 - N_18];
						cond_p6 = (val2_p6 > 0);
						
						sync185_p6 = cond_p6;
						
						EMX_SendSync(6, 4, 185, -1, sync185_p6);
						
						if (cond_p6, sync185_p6) {
							double val32_p6;
							double val4_p6;
							double val3_p6;
							int cond2_p6;
							
							val32_p6 = sl_split2_p6[k1_p6 - N_18];
							val4_p6 = val32_p6 - theta_p6;
							sl_split2_p6[k1_p6 - N_18] = val4_p6;
							val3_p6 = sl_split2_p6[k1_p6 - N_18];
							cond2_p6 = (val3_p6 == 0);
							
							sync184_p6 = cond2_p6;
							
							EMX_SendSync(6, 4, 184, -1, sync184_p6);
							
							if (cond2_p6, sync184_p6) {
								int val5_p6;
								
								val5_p6 = prv_col_p6[k1_p6];
								act_split2_p6[k1_p6 - N_18] = val5_p6;
								
								EMX_Send(6, 4, 129, -1, act_split2_p6, N_18 * sizeof(*act_split2_p6));
							}
						}
					}
				}
				
				
				
				for (k1_p6 = N_48; k1_p6 < N_58; k1_p6 = k1_p6 + 1) {
					EMX_Recv(5, 6, 141, -1, act_split5_p6, N_18 * sizeof(*act_split5_p6));
					
					{
						double val2_p6;
						int cond_p6;
						
						
						
						val2_p6 = sl_split5_p6[k1_p6 - N_48];
						cond_p6 = (val2_p6 > 0);
						
						sync189_p6 = cond_p6;
						
						EMX_SendSync(6, 5, 189, -1, sync189_p6);
						
						if (cond_p6, sync189_p6) {
							double val32_p6;
							double val4_p6;
							double val3_p6;
							int cond2_p6;
							
							val32_p6 = sl_split5_p6[k1_p6 - N_48];
							val4_p6 = val32_p6 - theta_p6;
							sl_split5_p6[k1_p6 - N_48] = val4_p6;
							val3_p6 = sl_split5_p6[k1_p6 - N_48];
							cond2_p6 = (val3_p6 == 0);
							
							sync188_p6 = cond2_p6;
							
							EMX_SendSync(6, 5, 188, -1, sync188_p6);
							
							if (cond2_p6, sync188_p6) {
								int val5_p6;
								
								val5_p6 = prv_col_p6[k1_p6];
								act_split5_p6[k1_p6 - N_48] = val5_p6;
								
								EMX_Send(6, 5, 144, -1, act_split5_p6, N_18 * sizeof(*act_split5_p6));
							}
						}
					}
				}
				
				
				EMX_Send(6, 0, 126, -1, sl_split2_p6, N_18 * sizeof(*sl_split2_p6));
				
				
				for (k1_p6 = N_68; k1_p6 < N_78; k1_p6 = k1_p6 + 1) {
					
					if (!cov_col_p6[k1_p6]) {
						double val22_p6;
						double val3_p6;
						
						val22_p6 = d_col_split7_p6[k1_p6 - N_68];
						val3_p6 = val22_p6 + theta_p6 / 2;
						d_col_split7_p6[k1_p6 - N_68] = val3_p6;
					} else {
						double val22_p6;
						double val3_p6;
						
						val22_p6 = d_col_split7_p6[k1_p6 - N_68];
						val3_p6 = val22_p6 - theta_p6 / 2;
						d_col_split7_p6[k1_p6 - N_68] = val3_p6;
					}
					
				}
				
				EMX_Send(6, 0, 106, -1, sl_split5_p6, N_18 * sizeof(*sl_split5_p6));
				
				
				
				EMX_Send(6, 0, 163, -1, d_col_split7_p6, N_18 * sizeof(*d_col_split7_p6));
				
				
			}
		}
	}
}


extern void update_pass_p7(double theta_p7, _Bool cov_row_p7[N], _Bool cov_col_p7[N], double dual_row_p7[N], double dual_col_p7[N], double slack_p7[N], int prv_col_p7[N]) {
	double d_row_split6_p7[N_18];
	size_t k1_p7;
	double d_row_split3_p7[N_18];
	double d_row_split8_p7[N_18];
	
	for (int i_p7 = N_58; i_p7 < N_68; i_p7 = i_p7 + 1) {
		double val2_p7;
		
		val2_p7 = dual_row_p7[i_p7];
		d_row_split6_p7[i_p7 - N_58] = val2_p7;
	}
	
	EMX_Recv(3, 7, 93, -1, d_row_split8_p7, N_18 * sizeof(*d_row_split8_p7));
	
	EMX_Send(7, 1, 91, -1, d_row_split6_p7, N_18 * sizeof(*d_row_split6_p7));
	
	EMX_Recv(4, 7, 88, -1, d_row_split3_p7, N_18 * sizeof(*d_row_split3_p7));
	
	{
		double d_col_split6_p7[N_18];
		double d_col_split3_p7[N_18];
		double d_col_split8_p7[N_18];
		
		for (int i_p7 = N_58; i_p7 < N_68; i_p7 = i_p7 + 1) {
			double val2_p7;
			
			val2_p7 = dual_col_p7[i_p7];
			d_col_split6_p7[i_p7 - N_58] = val2_p7;
		}
		
		EMX_Recv(3, 7, 101, -1, d_col_split8_p7, N_18 * sizeof(*d_col_split8_p7));
		
		EMX_Send(7, 2, 99, -1, d_col_split6_p7, N_18 * sizeof(*d_col_split6_p7));
		
		EMX_Recv(4, 7, 96, -1, d_col_split3_p7, N_18 * sizeof(*d_col_split3_p7));
		
		{
			double sl_split6_p7[N_18];
			double sl_split3_p7[N_18];
			double sl_split8_p7[N_18];
			
			for (int i_p7 = N_58; i_p7 < N_68; i_p7 = i_p7 + 1) {
				double val2_p7;
				
				val2_p7 = slack_p7[i_p7];
				sl_split6_p7[i_p7 - N_58] = val2_p7;
			}
			
			EMX_Recv(3, 7, 109, -1, sl_split8_p7, N_18 * sizeof(*sl_split8_p7));
			
			EMX_Send(7, 3, 107, -1, sl_split6_p7, N_18 * sizeof(*sl_split6_p7));
			
			EMX_Recv(4, 7, 104, -1, sl_split3_p7, N_18 * sizeof(*sl_split3_p7));
			
			{
				int act_split3_p7[N_18];
				int act_split8_p7[N_18];
				
				
				
				for (int i_p7 = N_28; i_p7 < N_38; i_p7 = i_p7 + 1) {
					int val2_p7;
					
					val2_p7 = -1;
					act_split3_p7[i_p7 - N_28] = val2_p7;
				}
				
				for (k1_p7 = N_28; k1_p7 < N_38; k1_p7 = k1_p7 + 1) {
					double val2_p7;
					int cond_p7;
					
					if (!cov_row_p7[k1_p7]) {
						double val22_p7;
						double val3_p7;
						
						val22_p7 = d_row_split3_p7[k1_p7 - N_28];
						val3_p7 = val22_p7 + theta_p7 / 2;
						d_row_split3_p7[k1_p7 - N_28] = val3_p7;
					} else {
						double val22_p7;
						double val3_p7;
						
						val22_p7 = d_row_split3_p7[k1_p7 - N_28];
						val3_p7 = val22_p7 - theta_p7 / 2;
						d_row_split3_p7[k1_p7 - N_28] = val3_p7;
					}
					
					if (!cov_col_p7[k1_p7]) {
						double val22_p7;
						double val3_p7;
						
						val22_p7 = d_col_split3_p7[k1_p7 - N_28];
						val3_p7 = val22_p7 + theta_p7 / 2;
						d_col_split3_p7[k1_p7 - N_28] = val3_p7;
					} else {
						double val22_p7;
						double val3_p7;
						
						val22_p7 = d_col_split3_p7[k1_p7 - N_28];
						val3_p7 = val22_p7 - theta_p7 / 2;
						d_col_split3_p7[k1_p7 - N_28] = val3_p7;
					}
					
					val2_p7 = sl_split3_p7[k1_p7 - N_28];
					cond_p7 = (val2_p7 > 0);
					
					if (cond_p7) {
						double val32_p7;
						double val4_p7;
						double val3_p7;
						int cond2_p7;
						
						val32_p7 = sl_split3_p7[k1_p7 - N_28];
						val4_p7 = val32_p7 - theta_p7;
						sl_split3_p7[k1_p7 - N_28] = val4_p7;
						val3_p7 = sl_split3_p7[k1_p7 - N_28];
						cond2_p7 = (val3_p7 == 0);
						
						if (cond2_p7) {
							int val5_p7;
							
							val5_p7 = prv_col_p7[k1_p7];
							act_split3_p7[k1_p7 - N_28] = val5_p7;
						}
					}
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
				}
				
				
				
				EMX_Send(7, 1, 130, -1, act_split3_p7, N_18 * sizeof(*act_split3_p7));
				
				EMX_Send(7, 0, 133, -1, d_row_split3_p7, N_18 * sizeof(*d_row_split3_p7));
				
				EMX_Send(7, 0, 132, -1, d_col_split3_p7, N_18 * sizeof(*d_col_split3_p7));
				
				EMX_Send(7, 0, 131, -1, sl_split3_p7, N_18 * sizeof(*sl_split3_p7));
				
				
				
				
				
				for (int i_p7 = N_78; i_p7 < N; i_p7 = i_p7 + 1) {
					int val2_p7;
					
					val2_p7 = -1;
					act_split8_p7[i_p7 - N_78] = val2_p7;
				}
				
				for (k1_p7 = N_78; k1_p7 < N; k1_p7 = k1_p7 + 1) {
					double val2_p7;
					int cond_p7;
					
					if (!cov_row_p7[k1_p7]) {
						double val22_p7;
						double val3_p7;
						
						val22_p7 = d_row_split8_p7[k1_p7 - N_78];
						val3_p7 = val22_p7 + theta_p7 / 2;
						d_row_split8_p7[k1_p7 - N_78] = val3_p7;
					} else {
						double val22_p7;
						double val3_p7;
						
						val22_p7 = d_row_split8_p7[k1_p7 - N_78];
						val3_p7 = val22_p7 - theta_p7 / 2;
						d_row_split8_p7[k1_p7 - N_78] = val3_p7;
					}
					
					if (!cov_col_p7[k1_p7]) {
						double val22_p7;
						double val3_p7;
						
						val22_p7 = d_col_split8_p7[k1_p7 - N_78];
						val3_p7 = val22_p7 + theta_p7 / 2;
						d_col_split8_p7[k1_p7 - N_78] = val3_p7;
					} else {
						double val22_p7;
						double val3_p7;
						
						val22_p7 = d_col_split8_p7[k1_p7 - N_78];
						val3_p7 = val22_p7 - theta_p7 / 2;
						d_col_split8_p7[k1_p7 - N_78] = val3_p7;
					}
					
					val2_p7 = sl_split8_p7[k1_p7 - N_78];
					cond_p7 = (val2_p7 > 0);
					
					if (cond_p7) {
						double val32_p7;
						double val4_p7;
						double val3_p7;
						int cond2_p7;
						
						val32_p7 = sl_split8_p7[k1_p7 - N_78];
						val4_p7 = val32_p7 - theta_p7;
						sl_split8_p7[k1_p7 - N_78] = val4_p7;
						val3_p7 = sl_split8_p7[k1_p7 - N_78];
						cond2_p7 = (val3_p7 == 0);
						
						if (cond2_p7) {
							int val5_p7;
							
							val5_p7 = prv_col_p7[k1_p7];
							act_split8_p7[k1_p7 - N_78] = val5_p7;
						}
					}
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
				}
				
				
				EMX_Send(7, 0, 170, -1, d_row_split8_p7, N_18 * sizeof(*d_row_split8_p7));
				
				EMX_Send(7, 0, 169, -1, d_col_split8_p7, N_18 * sizeof(*d_col_split8_p7));
				
				EMX_Send(7, 0, 168, -1, sl_split8_p7, N_18 * sizeof(*sl_split8_p7));
				
				EMX_Send(7, 1, 167, -1, act_split8_p7, N_18 * sizeof(*act_split8_p7));
			}
		}
	}
}


extern void update_pass_p1(double theta_p1, _Bool cov_row_p1[N]) {
	_Bool sync193_p1;
	_Bool sync194_p1;
	_Bool sync195_p1;
	_Bool sync196_p1;
	_Bool sync197_p1;
	_Bool sync198_p1;
	_Bool active_p1[N];
	size_t k1_p1;
	double d_row_split1_p1[N_18];
	double d_row_split4_p1[N_18];
	double d_row_split6_p1[N_18];
	
	EMX_Recv(7, 1, 91, -1, d_row_split6_p1, N_18 * sizeof(*d_row_split6_p1));
	
	EMX_Recv(5, 1, 89, -1, d_row_split4_p1, N_18 * sizeof(*d_row_split4_p1));
	
	EMX_Recv(2, 1, 86, -1, d_row_split1_p1, N_18 * sizeof(*d_row_split1_p1));
	
	{
		int act_split1_p1[N_18];
		int act_split3_p1[N_18];
		int act_split4_p1[N_18];
		int act_split5_p1[N_18];
		int act_split6_p1[N_18];
		int act_split7_p1[N_18];
		int act_split8_p1[N_18];
		
		for (int i_p1 = 0; i_p1 < N_18; i_p1 = i_p1 + 1) {
			int val2_p1;
			
			val2_p1 = -1;
			act_split1_p1[i_p1 - 0] = val2_p1;
		}
		
		for (k1_p1 = 0u; k1_p1 < N_18; k1_p1 = k1_p1 + 1) {
			EMX_Send(1, 3, 111, -1, act_split1_p1, N_18 * sizeof(*act_split1_p1));
			
			
			
			
			
			
			
			
			
			
			
			
			
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
			
			
			if (EMX_RecvSync(3, 1, 183, -1)) {
				if (EMX_RecvSync(3, 1, 182, -1)) {
					EMX_Recv(3, 1, 120, -1, act_split1_p1, N_18 * sizeof(*act_split1_p1));
				}
			}
			
			
			
		}
		
		
		
		EMX_Send(1, 0, 119, -1, d_row_split1_p1, N_18 * sizeof(*d_row_split1_p1));
		
		EMX_Send(1, 0, 110, -1, act_split1_p1, N_18 * sizeof(*act_split1_p1));
		
		for (k1_p1 = N_38; k1_p1 < N_48; k1_p1 = k1_p1 + 1) {
			
			
			
			
			
			
			
			
			
			
			
			
			if (!cov_row_p1[k1_p1]) {
				double val22_p1;
				double val3_p1;
				
				val22_p1 = d_row_split4_p1[k1_p1 - N_38];
				val3_p1 = val22_p1 + theta_p1 / 2;
				d_row_split4_p1[k1_p1 - N_38] = val3_p1;
			} else {
				double val22_p1;
				double val3_p1;
				
				val22_p1 = d_row_split4_p1[k1_p1 - N_38];
				val3_p1 = val22_p1 - theta_p1 / 2;
				d_row_split4_p1[k1_p1 - N_38] = val3_p1;
			}
			
			
			
			
			
		}
		
		
		for (k1_p1 = N_58; k1_p1 < N_68; k1_p1 = k1_p1 + 1) {
			
			
			
			
			
			
			
			
			
			
			
			
			if (!cov_row_p1[k1_p1]) {
				double val22_p1;
				double val3_p1;
				
				val22_p1 = d_row_split6_p1[k1_p1 - N_58];
				val3_p1 = val22_p1 + theta_p1 / 2;
				d_row_split6_p1[k1_p1 - N_58] = val3_p1;
			} else {
				double val22_p1;
				double val3_p1;
				
				val22_p1 = d_row_split6_p1[k1_p1 - N_58];
				val3_p1 = val22_p1 - theta_p1 / 2;
				d_row_split6_p1[k1_p1 - N_58] = val3_p1;
			}
			
			
			
			
			
		}
		
		EMX_Recv(7, 1, 130, -1, act_split3_p1, N_18 * sizeof(*act_split3_p1));
		
		
		for (int i_p1 = N_28; i_p1 < N_38; i_p1 = i_p1 + 1) {
			int val5_p1;
			int cond_p1;
			
			val5_p1 = act_split3_p1[i_p1 - N_28];
			cond_p1 = (val5_p1 != (-1));
			
			EMX_Recv(0, 1, 79, -1, active_p1, N * sizeof(*active_p1));
			
			sync193_p1 = cond_p1;
			
			EMX_SendSync(1, 0, 193, -1, sync193_p1);
			
			if (cond_p1, sync193_p1) {
				int val6_p1;
				int tmp_p1;
				
				val6_p1 = act_split3_p1[i_p1 - N_28];
				tmp_p1 = val6_p1;
				active_p1[tmp_p1] = 1;
				
				EMX_Send(1, 0, 154, -1, active_p1, N * sizeof(*active_p1));
			}
		}
		
		
		EMX_Send(1, 0, 138, -1, d_row_split4_p1, N_18 * sizeof(*d_row_split4_p1));
		
		EMX_Recv(2, 1, 134, -1, act_split4_p1, N_18 * sizeof(*act_split4_p1));
		
		for (int i_p1 = N_38; i_p1 < N_48; i_p1 = i_p1 + 1) {
			int val5_p1;
			int cond_p1;
			
			val5_p1 = act_split4_p1[i_p1 - N_38];
			cond_p1 = (val5_p1 != (-1));
			
			EMX_Recv(0, 1, 80, -1, active_p1, N * sizeof(*active_p1));
			
			sync194_p1 = cond_p1;
			
			EMX_SendSync(1, 0, 194, -1, sync194_p1);
			
			if (cond_p1, sync194_p1) {
				int val6_p1;
				int tmp_p1;
				
				val6_p1 = act_split4_p1[i_p1 - N_38];
				tmp_p1 = val6_p1;
				active_p1[tmp_p1] = 1;
				
				EMX_Send(1, 0, 155, -1, active_p1, N * sizeof(*active_p1));
			}
		}
		
		EMX_Recv(5, 1, 140, -1, act_split5_p1, N_18 * sizeof(*act_split5_p1));
		
		for (int i_p1 = N_48; i_p1 < N_58; i_p1 = i_p1 + 1) {
			int val5_p1;
			int cond_p1;
			
			val5_p1 = act_split5_p1[i_p1 - N_48];
			cond_p1 = (val5_p1 != (-1));
			
			EMX_Recv(0, 1, 81, -1, active_p1, N * sizeof(*active_p1));
			
			sync195_p1 = cond_p1;
			
			EMX_SendSync(1, 0, 195, -1, sync195_p1);
			
			if (cond_p1, sync195_p1) {
				int val6_p1;
				int tmp_p1;
				
				val6_p1 = act_split5_p1[i_p1 - N_48];
				tmp_p1 = val6_p1;
				active_p1[tmp_p1] = 1;
				
				EMX_Send(1, 0, 156, -1, active_p1, N * sizeof(*active_p1));
			}
		}
		
		
		EMX_Send(1, 0, 149, -1, d_row_split6_p1, N_18 * sizeof(*d_row_split6_p1));
		
		EMX_Recv(2, 1, 145, -1, act_split6_p1, N_18 * sizeof(*act_split6_p1));
		
		for (int i_p1 = N_58; i_p1 < N_68; i_p1 = i_p1 + 1) {
			int val5_p1;
			int cond_p1;
			
			val5_p1 = act_split6_p1[i_p1 - N_58];
			cond_p1 = (val5_p1 != (-1));
			
			EMX_Recv(0, 1, 82, -1, active_p1, N * sizeof(*active_p1));
			
			sync196_p1 = cond_p1;
			
			EMX_SendSync(1, 0, 196, -1, sync196_p1);
			
			if (cond_p1, sync196_p1) {
				int val6_p1;
				int tmp_p1;
				
				val6_p1 = act_split6_p1[i_p1 - N_58];
				tmp_p1 = val6_p1;
				active_p1[tmp_p1] = 1;
				
				EMX_Send(1, 0, 157, -1, active_p1, N * sizeof(*active_p1));
			}
		}
		
		EMX_Recv(5, 1, 160, -1, act_split7_p1, N_18 * sizeof(*act_split7_p1));
		
		for (int i_p1 = N_68; i_p1 < N_78; i_p1 = i_p1 + 1) {
			int val5_p1;
			int cond_p1;
			
			val5_p1 = act_split7_p1[i_p1 - N_68];
			cond_p1 = (val5_p1 != (-1));
			
			EMX_Recv(0, 1, 83, -1, active_p1, N * sizeof(*active_p1));
			
			sync197_p1 = cond_p1;
			
			EMX_SendSync(1, 0, 197, -1, sync197_p1);
			
			if (cond_p1, sync197_p1) {
				int val6_p1;
				int tmp_p1;
				
				val6_p1 = act_split7_p1[i_p1 - N_68];
				tmp_p1 = val6_p1;
				active_p1[tmp_p1] = 1;
				
				EMX_Send(1, 0, 158, -1, active_p1, N * sizeof(*active_p1));
			}
		}
		
		EMX_Recv(7, 1, 167, -1, act_split8_p1, N_18 * sizeof(*act_split8_p1));
		
		for (int i_p1 = N_78; i_p1 < N; i_p1 = i_p1 + 1) {
			int val5_p1;
			int cond_p1;
			
			val5_p1 = act_split8_p1[i_p1 - N_78];
			cond_p1 = (val5_p1 != (-1));
			
			EMX_Recv(0, 1, 84, -1, active_p1, N * sizeof(*active_p1));
			
			sync198_p1 = cond_p1;
			
			EMX_SendSync(1, 0, 198, -1, sync198_p1);
			
			if (cond_p1, sync198_p1) {
				int val6_p1;
				int tmp_p1;
				
				val6_p1 = act_split8_p1[i_p1 - N_78];
				tmp_p1 = val6_p1;
				active_p1[tmp_p1] = 1;
				
				EMX_Send(1, 0, 159, -1, active_p1, N * sizeof(*active_p1));
			}
		}
	}
}


extern void update_pass_p0(int n_p0, _Bool active_p0[N], double dual_row_p0[N], double dual_col_p0[N], double slack_p0[N]) {
	double d_row_split1_p0[N_18];
	double d_row_split2_p0[N_18];
	double d_row_split3_p0[N_18];
	double d_row_split4_p0[N_18];
	double d_row_split5_p0[N_18];
	double d_row_split6_p0[N_18];
	double d_row_split7_p0[N_18];
	double d_row_split8_p0[N_18];
	size_t k1_p0;
	double d_col_split1_p0[N_18];
	double d_col_split2_p0[N_18];
	double d_col_split3_p0[N_18];
	double d_col_split4_p0[N_18];
	double d_col_split5_p0[N_18];
	double d_col_split6_p0[N_18];
	double d_col_split7_p0[N_18];
	double d_col_split8_p0[N_18];
	double sl_split1_p0[N_18];
	double sl_split2_p0[N_18];
	double sl_split3_p0[N_18];
	double sl_split4_p0[N_18];
	double sl_split5_p0[N_18];
	double sl_split6_p0[N_18];
	double sl_split7_p0[N_18];
	double sl_split8_p0[N_18];
	int act_split1_p0[N_18];
	
	for (k1_p0 = 0u; k1_p0 < N_18; k1_p0 = k1_p0 + 1) {
		
		
	}
	
	for (k1_p0 = N_18; k1_p0 < N_28; k1_p0 = k1_p0 + 1) {
		
		
	}
	
	for (k1_p0 = N_28; k1_p0 < N_38; k1_p0 = k1_p0 + 1) {
		
		
	}
	
	EMX_Recv(1, 0, 119, -1, d_row_split1_p0, N_18 * sizeof(*d_row_split1_p0));
	
	EMX_Recv(1, 0, 110, -1, act_split1_p0, N_18 * sizeof(*act_split1_p0));
	
	for (k1_p0 = N_38; k1_p0 < N_48; k1_p0 = k1_p0 + 1) {
		
		
	}
	
	EMX_Recv(3, 0, 118, -1, sl_split1_p0, N_18 * sizeof(*sl_split1_p0));
	
	EMX_Recv(2, 0, 94, -1, d_col_split1_p0, N_18 * sizeof(*d_col_split1_p0));
	
	for (k1_p0 = N_48; k1_p0 < N_58; k1_p0 = k1_p0 + 1) {
		
		
	}
	
	for (int i_p0 = 0; i_p0 < N_18; i_p0 = i_p0 + 1) {
		double val2_p0;
		double val3_p0;
		double val4_p0;
		int val5_p0;
		int cond_p0;
		
		val2_p0 = d_row_split1_p0[i_p0 - 0];
		dual_row_p0[i_p0] = val2_p0;
		val3_p0 = d_col_split1_p0[i_p0 - 0];
		dual_col_p0[i_p0] = val3_p0;
		val4_p0 = sl_split1_p0[i_p0 - 0];
		slack_p0[i_p0] = val4_p0;
		
		val5_p0 = act_split1_p0[i_p0 - 0];
		cond_p0 = (val5_p0 != (-1));
		
		if (cond_p0) {
			int val6_p0;
			int tmp_p0;
			
			val6_p0 = act_split1_p0[i_p0 - 0];
			tmp_p0 = val6_p0;
			active_p0[tmp_p0] = 1;
		}
	}
	
	for (k1_p0 = N_58; k1_p0 < N_68; k1_p0 = k1_p0 + 1) {
		
		
	}
	
	EMX_Recv(4, 0, 128, -1, d_row_split2_p0, N_18 * sizeof(*d_row_split2_p0));
	
	EMX_Recv(5, 0, 127, -1, d_col_split2_p0, N_18 * sizeof(*d_col_split2_p0));
	
	EMX_Recv(6, 0, 126, -1, sl_split2_p0, N_18 * sizeof(*sl_split2_p0));
	
	for (int i_p0 = N_18; i_p0 < N_28; i_p0 = i_p0 + 1) {
		double val2_p0;
		double val3_p0;
		double val4_p0;
		
		
		
		
		
		
		
		val2_p0 = d_row_split2_p0[i_p0 - N_18];
		dual_row_p0[i_p0] = val2_p0;
		val3_p0 = d_col_split2_p0[i_p0 - N_18];
		dual_col_p0[i_p0] = val3_p0;
		val4_p0 = sl_split2_p0[i_p0 - N_18];
		slack_p0[i_p0] = val4_p0;
		
		EMX_Send(0, 4, 85, -1, active_p0, N * sizeof(*active_p0));
		
		if (EMX_RecvSync(4, 0, 192, -1)) {
			EMX_Recv(4, 0, 152, -1, active_p0, N * sizeof(*active_p0));
		}
		
	}
	
	EMX_Recv(7, 0, 133, -1, d_row_split3_p0, N_18 * sizeof(*d_row_split3_p0));
	
	EMX_Recv(7, 0, 132, -1, d_col_split3_p0, N_18 * sizeof(*d_col_split3_p0));
	
	EMX_Recv(7, 0, 131, -1, sl_split3_p0, N_18 * sizeof(*sl_split3_p0));
	
	for (int i_p0 = N_28; i_p0 < N_38; i_p0 = i_p0 + 1) {
		double val2_p0;
		double val3_p0;
		double val4_p0;
		
		
		
		
		
		
		
		val2_p0 = d_row_split3_p0[i_p0 - N_28];
		dual_row_p0[i_p0] = val2_p0;
		val3_p0 = d_col_split3_p0[i_p0 - N_28];
		dual_col_p0[i_p0] = val3_p0;
		val4_p0 = sl_split3_p0[i_p0 - N_28];
		slack_p0[i_p0] = val4_p0;
		
		EMX_Send(0, 1, 79, -1, active_p0, N * sizeof(*active_p0));
		
		if (EMX_RecvSync(1, 0, 193, -1)) {
			EMX_Recv(1, 0, 154, -1, active_p0, N * sizeof(*active_p0));
		}
		
	}
	
	EMX_Recv(2, 0, 137, -1, d_col_split4_p0, N_18 * sizeof(*d_col_split4_p0));
	
	EMX_Recv(3, 0, 136, -1, sl_split4_p0, N_18 * sizeof(*sl_split4_p0));
	
	for (k1_p0 = N_68; k1_p0 < N_78; k1_p0 = k1_p0 + 1) {
		
		
	}
	
	EMX_Recv(1, 0, 138, -1, d_row_split4_p0, N_18 * sizeof(*d_row_split4_p0));
	
	for (int i_p0 = N_38; i_p0 < N_48; i_p0 = i_p0 + 1) {
		double val2_p0;
		double val3_p0;
		double val4_p0;
		
		
		
		
		
		
		
		val2_p0 = d_row_split4_p0[i_p0 - N_38];
		dual_row_p0[i_p0] = val2_p0;
		val3_p0 = d_col_split4_p0[i_p0 - N_38];
		dual_col_p0[i_p0] = val3_p0;
		val4_p0 = sl_split4_p0[i_p0 - N_38];
		slack_p0[i_p0] = val4_p0;
		
		EMX_Send(0, 1, 80, -1, active_p0, N * sizeof(*active_p0));
		
		if (EMX_RecvSync(1, 0, 194, -1)) {
			EMX_Recv(1, 0, 155, -1, active_p0, N * sizeof(*active_p0));
		}
		
	}
	
	EMX_Recv(4, 0, 143, -1, d_row_split5_p0, N_18 * sizeof(*d_row_split5_p0));
	
	EMX_Recv(5, 0, 142, -1, d_col_split5_p0, N_18 * sizeof(*d_col_split5_p0));
	
	EMX_Recv(6, 0, 106, -1, sl_split5_p0, N_18 * sizeof(*sl_split5_p0));
	
	for (int i_p0 = N_48; i_p0 < N_58; i_p0 = i_p0 + 1) {
		double val2_p0;
		double val3_p0;
		double val4_p0;
		
		
		
		
		
		
		
		val2_p0 = d_row_split5_p0[i_p0 - N_48];
		dual_row_p0[i_p0] = val2_p0;
		val3_p0 = d_col_split5_p0[i_p0 - N_48];
		dual_col_p0[i_p0] = val3_p0;
		val4_p0 = sl_split5_p0[i_p0 - N_48];
		slack_p0[i_p0] = val4_p0;
		
		EMX_Send(0, 1, 81, -1, active_p0, N * sizeof(*active_p0));
		
		if (EMX_RecvSync(1, 0, 195, -1)) {
			EMX_Recv(1, 0, 156, -1, active_p0, N * sizeof(*active_p0));
		}
		
	}
	
	EMX_Recv(2, 0, 148, -1, d_col_split6_p0, N_18 * sizeof(*d_col_split6_p0));
	
	EMX_Recv(3, 0, 147, -1, sl_split6_p0, N_18 * sizeof(*sl_split6_p0));
	
	for (k1_p0 = N_78; k1_p0 < N; k1_p0 = k1_p0 + 1) {
		
		
	}
	
	EMX_Recv(1, 0, 149, -1, d_row_split6_p0, N_18 * sizeof(*d_row_split6_p0));
	
	for (int i_p0 = N_58; i_p0 < N_68; i_p0 = i_p0 + 1) {
		double val2_p0;
		double val3_p0;
		double val4_p0;
		
		
		
		
		
		
		
		val2_p0 = d_row_split6_p0[i_p0 - N_58];
		dual_row_p0[i_p0] = val2_p0;
		val3_p0 = d_col_split6_p0[i_p0 - N_58];
		dual_col_p0[i_p0] = val3_p0;
		val4_p0 = sl_split6_p0[i_p0 - N_58];
		slack_p0[i_p0] = val4_p0;
		
		EMX_Send(0, 1, 82, -1, active_p0, N * sizeof(*active_p0));
		
		if (EMX_RecvSync(1, 0, 196, -1)) {
			EMX_Recv(1, 0, 157, -1, active_p0, N * sizeof(*active_p0));
		}
		
	}
	
	EMX_Recv(5, 0, 164, -1, d_row_split7_p0, N_18 * sizeof(*d_row_split7_p0));
	
	EMX_Recv(6, 0, 163, -1, d_col_split7_p0, N_18 * sizeof(*d_col_split7_p0));
	
	EMX_Recv(5, 0, 162, -1, sl_split7_p0, N_18 * sizeof(*sl_split7_p0));
	
	for (int i_p0 = N_68; i_p0 < N_78; i_p0 = i_p0 + 1) {
		double val2_p0;
		double val3_p0;
		double val4_p0;
		
		
		
		
		
		
		
		val2_p0 = d_row_split7_p0[i_p0 - N_68];
		dual_row_p0[i_p0] = val2_p0;
		val3_p0 = d_col_split7_p0[i_p0 - N_68];
		dual_col_p0[i_p0] = val3_p0;
		val4_p0 = sl_split7_p0[i_p0 - N_68];
		slack_p0[i_p0] = val4_p0;
		
		EMX_Send(0, 1, 83, -1, active_p0, N * sizeof(*active_p0));
		
		if (EMX_RecvSync(1, 0, 197, -1)) {
			EMX_Recv(1, 0, 158, -1, active_p0, N * sizeof(*active_p0));
		}
		
	}
	
	EMX_Recv(7, 0, 170, -1, d_row_split8_p0, N_18 * sizeof(*d_row_split8_p0));
	
	EMX_Recv(7, 0, 169, -1, d_col_split8_p0, N_18 * sizeof(*d_col_split8_p0));
	
	EMX_Recv(7, 0, 168, -1, sl_split8_p0, N_18 * sizeof(*sl_split8_p0));
	
	for (int i_p0 = N_78; i_p0 < N; i_p0 = i_p0 + 1) {
		double val2_p0;
		double val3_p0;
		double val4_p0;
		
		
		
		
		
		
		
		val2_p0 = d_row_split8_p0[i_p0 - N_78];
		dual_row_p0[i_p0] = val2_p0;
		val3_p0 = d_col_split8_p0[i_p0 - N_78];
		dual_col_p0[i_p0] = val3_p0;
		val4_p0 = sl_split8_p0[i_p0 - N_78];
		slack_p0[i_p0] = val4_p0;
		
		EMX_Send(0, 1, 84, -1, active_p0, N * sizeof(*active_p0));
		
		if (EMX_RecvSync(1, 0, 198, -1)) {
			EMX_Recv(1, 0, 159, -1, active_p0, N * sizeof(*active_p0));
		}
		
	}
}


extern _Bool augmenting_path_search_p0(int cost_p0[N][N], int n_p0, _Bool active_p0[N], int ass_row_p0[N], int ass_col_p0[N], _Bool cov_row_p0[N], _Bool cov_col_p0[N], double dual_row_p0[N], double dual_col_p0[N], double slack_p0[N], int prv_row_p0[N], int prv_col_p0[N], int suc_row_p0[N], int suc_col_p0[N]) {
	_Bool sync_p0;
	_Bool sync199_p0;
	_Bool active_p02[N];
	double slack_p02[N];
	double dual_row_p02[N];
	int n_p02;
	double dual_col_p02[N];
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
		int active_count_p0 = 0;
		
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
		
		while (sync_p0 = (active_count_p0 > 0), EMX_SendSync(0, 1, 180, -1, sync_p0), sync_p0) {
			
			
			
			
			
			
			forward_bfs(cost_p0, n_p0, f_in_p0, active_count_p0, active_p0, reverse_p0, visited_p0, ass_col_p0, cov_row_p0, cov_col_p0, dual_row_p0, dual_col_p0, slack_p0, prv_row_p0, prv_col_p0);
			
			active_count_p0 = EMX_Recv32(1, 0, 70, -1);
			
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
			
			EMX_Send(0, 6, 69, -1, prv_col_p0, N * sizeof(*prv_col_p0));
			
			EMX_Send(0, 7, 68, -1, prv_col_p0, N * sizeof(*prv_col_p0));
			
			EMX_Send(0, 5, 67, -1, prv_col_p0, N * sizeof(*prv_col_p0));
			
			EMX_Send(0, 3, 66, -1, prv_col_p0, N * sizeof(*prv_col_p0));
			
			EMX_Send(0, 6, 65, -1, slack_p0, N * sizeof(*slack_p0));
			
			EMX_Send(0, 7, 64, -1, slack_p0, N * sizeof(*slack_p0));
			
			EMX_Send(0, 4, 63, -1, slack_p0, N * sizeof(*slack_p0));
			
			EMX_Send(0, 5, 62, -1, slack_p0, N * sizeof(*slack_p0));
			
			EMX_Send(0, 3, 61, -1, slack_p0, N * sizeof(*slack_p0));
			
			EMX_Send(0, 2, 60, -1, slack_p0, N * sizeof(*slack_p0));
			
			EMX_Send(0, 6, 59, -1, cov_col_p0, N * sizeof(*cov_col_p0));
			
			EMX_Send(0, 7, 58, -1, cov_col_p0, N * sizeof(*cov_col_p0));
			
			EMX_Send(0, 5, 57, -1, cov_col_p0, N * sizeof(*cov_col_p0));
			
			EMX_Send(0, 2, 56, -1, cov_col_p0, N * sizeof(*cov_col_p0));
			
			EMX_Send(0, 7, 55, -1, cov_row_p0, N * sizeof(*cov_row_p0));
			
			EMX_Send(0, 4, 54, -1, cov_row_p0, N * sizeof(*cov_row_p0));
			
			EMX_Send(0, 5, 53, -1, cov_row_p0, N * sizeof(*cov_row_p0));
			
			EMX_Send(0, 1, 52, -1, cov_row_p0, N * sizeof(*cov_row_p0));
			
			for (int j_p0 = 0; j_p0 < n_p0; j_p0 = j_p0 + 1) {
				if (reverse_p0[j_p0]) {
					tmp7_p0 = f_rev_size_p0;
					f_rev_size_p0 = tmp7_p0 + 1;
					
					tmp3_p0 = tmp7_p0;
					
					f_rev_p0[tmp3_p0] = j_p0;
				}
			}
			
			sync199_p0 = (f_rev_size_p0 > 0);
			
			EMX_SendSync(0, 7, 206, -1, sync199_p0);
			
			EMX_SendSync(0, 6, 205, -1, sync199_p0);
			
			EMX_SendSync(0, 5, 204, -1, sync199_p0);
			
			EMX_SendSync(0, 4, 203, -1, sync199_p0);
			
			EMX_SendSync(0, 3, 202, -1, sync199_p0);
			
			EMX_SendSync(0, 2, 201, -1, sync199_p0);
			
			EMX_SendSync(0, 1, 200, -1, sync199_p0);
			
			if (sync199_p0) {
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
				check_flag_p0 = EMX_Recv8(1, 0, 71, -1);
			} else {
				double theta_p0 = 0x7fffffff;
				
				for (int j_p0 = 0; EMX_RecvSync(2, 0, 181, -1); j_p0 = j_p0 + 1) {
				}
				
				theta_p0 = EMX_Recv64F(2, 0, 72, -1);
				
				update_pass_p0(n_p0, active_p0, dual_row_p0, dual_col_p0, slack_p0);
				
				check_flag_p0 = EMX_Recv8(3, 0, 174, -1);
			}
			
			return check_flag_p0;
		}
	}
}


extern void augmenting_path_search_p1(void) {
	_Bool cov_row_p1[N];
	_Bool check_flag_p1 = 0;
	int active_count_p1;
	
	while (EMX_RecvSync(0, 1, 180, -1)) {
		active_count_p1 = 0;
		
		EMX_Send32(1, 0, 70, -1, active_count_p1);
	}
	
	EMX_Recv(0, 1, 52, -1, cov_row_p1, N * sizeof(*cov_row_p1));
	
	if (EMX_RecvSync(0, 1, 200, -1)) {
		check_flag_p1 = 1;
		
		EMX_Send8(1, 0, 71, -1, check_flag_p1);
	} else {
		double theta_p1;
		
		
		theta_p1 = EMX_Recv64F(2, 1, 73, -1);
		
		update_pass_p1(theta_p1, cov_row_p1);
	}
}


extern void augmenting_path_search_p2(int n_p2, double dual_row_p2[N], double dual_col_p2[N]) {
	_Bool sync_p2;
	double dual_row_p22[N];
	double slack_p2[N];
	_Bool cov_col_p2[N];
	double dual_col_p22[N];
	
	
	EMX_Recv(0, 2, 60, -1, slack_p2, N * sizeof(*slack_p2));
	
	EMX_Recv(0, 2, 56, -1, cov_col_p2, N * sizeof(*cov_col_p2));
	
	if (EMX_RecvSync(0, 2, 201, -1)) {
	} else {
		double theta_p2 = 0x7fffffff;
		
		for (int j_p2 = 0; sync_p2 = (j_p2 < n_p2), EMX_SendSync(2, 0, 181, -1, sync_p2), sync_p2; j_p2 = j_p2 + 1) {
			
			
			
			
			
			if (slack_p2[j_p2] > 0) {
				theta_p2 = (theta_p2 < slack_p2[j_p2] ? theta_p2 : slack_p2[j_p2]);
			}
			
			
		}
		
		EMX_Send64F(2, 0, 72, -1, theta_p2);
		
		EMX_Send64F(2, 1, 73, -1, theta_p2);
		
		EMX_Send64F(2, 3, 74, -1, theta_p2);
		
		EMX_Send64F(2, 5, 75, -1, theta_p2);
		
		EMX_Send64F(2, 4, 76, -1, theta_p2);
		
		EMX_Send64F(2, 7, 77, -1, theta_p2);
		
		EMX_Send64F(2, 6, 78, -1, theta_p2);
		
		update_pass_p2(theta_p2, cov_col_p2, dual_row_p2, dual_col_p2, slack_p2);
	}
}


extern void augmenting_path_search_p3(double dual_row_p3[N], double dual_col_p3[N]) {
	double slack_p3[N];
	int prv_col_p3[N];
	double dual_col_p32[N];
	double dual_row_p32[N];
	_Bool check_flag_p3 = 0;
	
	
	EMX_Recv(0, 3, 66, -1, prv_col_p3, N * sizeof(*prv_col_p3));
	
	EMX_Recv(0, 3, 61, -1, slack_p3, N * sizeof(*slack_p3));
	
	if (EMX_RecvSync(0, 3, 202, -1)) {
	} else {
		double theta_p3;
		
		
		theta_p3 = EMX_Recv64F(2, 3, 74, -1);
		
		update_pass_p3(theta_p3, dual_row_p3, dual_col_p3, slack_p3, prv_col_p3);
		
		check_flag_p3 = 0;
		
		EMX_Send8(3, 0, 174, -1, check_flag_p3);
	}
}


extern void augmenting_path_search_p4(double dual_row_p4[N], double dual_col_p4[N]) {
	_Bool cov_row_p4[N];
	double dual_row_p42[N];
	double slack_p4[N];
	double dual_col_p42[N];
	
	
	EMX_Recv(0, 4, 63, -1, slack_p4, N * sizeof(*slack_p4));
	
	EMX_Recv(0, 4, 54, -1, cov_row_p4, N * sizeof(*cov_row_p4));
	
	if (EMX_RecvSync(0, 4, 203, -1)) {
	} else {
		double theta_p4;
		
		
		theta_p4 = EMX_Recv64F(2, 4, 76, -1);
		
		update_pass_p4(theta_p4, cov_row_p4, dual_row_p4, dual_col_p4, slack_p4);
	}
}


extern void augmenting_path_search_p5(double dual_row_p5[N], double dual_col_p5[N]) {
	_Bool cov_col_p5[N];
	int prv_col_p5[N];
	double dual_col_p52[N];
	_Bool cov_row_p5[N];
	double dual_row_p52[N];
	double slack_p5[N];
	
	
	EMX_Recv(0, 5, 67, -1, prv_col_p5, N * sizeof(*prv_col_p5));
	
	EMX_Recv(0, 5, 62, -1, slack_p5, N * sizeof(*slack_p5));
	
	EMX_Recv(0, 5, 57, -1, cov_col_p5, N * sizeof(*cov_col_p5));
	
	EMX_Recv(0, 5, 53, -1, cov_row_p5, N * sizeof(*cov_row_p5));
	
	if (EMX_RecvSync(0, 5, 204, -1)) {
	} else {
		double theta_p5;
		
		
		theta_p5 = EMX_Recv64F(2, 5, 75, -1);
		
		update_pass_p5(theta_p5, cov_row_p5, cov_col_p5, dual_row_p5, dual_col_p5, slack_p5, prv_col_p5);
	}
}


extern void augmenting_path_search_p6(double dual_row_p6[N], double dual_col_p6[N]) {
	double dual_row_p62[N];
	double slack_p6[N];
	_Bool cov_col_p6[N];
	int prv_col_p6[N];
	double dual_col_p62[N];
	
	
	EMX_Recv(0, 6, 69, -1, prv_col_p6, N * sizeof(*prv_col_p6));
	
	EMX_Recv(0, 6, 65, -1, slack_p6, N * sizeof(*slack_p6));
	
	EMX_Recv(0, 6, 59, -1, cov_col_p6, N * sizeof(*cov_col_p6));
	
	if (EMX_RecvSync(0, 6, 205, -1)) {
	} else {
		double theta_p6;
		
		
		theta_p6 = EMX_Recv64F(2, 6, 78, -1);
		
		update_pass_p6(theta_p6, cov_col_p6, dual_row_p6, dual_col_p6, slack_p6, prv_col_p6);
	}
}


extern void augmenting_path_search_p7(double dual_row_p7[N], double dual_col_p7[N]) {
	_Bool cov_col_p7[N];
	int prv_col_p7[N];
	double dual_col_p72[N];
	_Bool cov_row_p7[N];
	double dual_row_p72[N];
	double slack_p7[N];
	
	
	EMX_Recv(0, 7, 68, -1, prv_col_p7, N * sizeof(*prv_col_p7));
	
	EMX_Recv(0, 7, 64, -1, slack_p7, N * sizeof(*slack_p7));
	
	EMX_Recv(0, 7, 58, -1, cov_col_p7, N * sizeof(*cov_col_p7));
	
	EMX_Recv(0, 7, 55, -1, cov_row_p7, N * sizeof(*cov_row_p7));
	
	if (EMX_RecvSync(0, 7, 206, -1)) {
	} else {
		double theta_p7;
		
		
		theta_p7 = EMX_Recv64F(2, 7, 77, -1);
		
		update_pass_p7(theta_p7, cov_row_p7, cov_col_p7, dual_row_p7, dual_col_p7, slack_p7, prv_col_p7);
	}
}


extern int hungarian_parallel_p0(int cost_p0[N][N], int n_p0) {
	_Bool sync_p0;
	int n_p02;
	int cost_p02[N][N];
	double dual_row_p0[N];
	double dual_col_p0[N];
	_Bool cov_row_p0[N];
	int prv_row_p0[N];
	int prv_col_p0[N];
	double slack_p0[N];
	int ass_row_p0[N];
	int suc_row_p0[N];
	int suc_col_p0[N];
	int ass_col_p0[N];
	_Bool cov_col_p0[N];
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
		
		while (sync_p0 = (match_count_p0 < n_p0), EMX_SendSync(0, 1, 207, -1, sync_p0), EMX_SendSync(0, 2, 208, -1, sync_p0), EMX_SendSync(0, 3, 209, -1, sync_p0), EMX_SendSync(0, 4, 210, -1, sync_p0), EMX_SendSync(0, 5, 211, -1, sync_p0), EMX_SendSync(0, 6, 212, -1, sync_p0), EMX_SendSync(0, 7, 213, -1, sync_p0), sync_p0) {
			EMX_Send(0, 6, 30, -1, dual_col_p0, N * sizeof(*dual_col_p0));
			
			EMX_Send(0, 7, 29, -1, dual_col_p0, N * sizeof(*dual_col_p0));
			
			EMX_Send(0, 4, 28, -1, dual_col_p0, N * sizeof(*dual_col_p0));
			
			EMX_Send(0, 5, 27, -1, dual_col_p0, N * sizeof(*dual_col_p0));
			
			EMX_Send(0, 3, 26, -1, dual_col_p0, N * sizeof(*dual_col_p0));
			
			EMX_Send(0, 2, 25, -1, dual_col_p0, N * sizeof(*dual_col_p0));
			
			EMX_Send(0, 6, 24, -1, dual_row_p0, N * sizeof(*dual_row_p0));
			
			EMX_Send(0, 7, 23, -1, dual_row_p0, N * sizeof(*dual_row_p0));
			
			EMX_Send(0, 4, 22, -1, dual_row_p0, N * sizeof(*dual_row_p0));
			
			EMX_Send(0, 5, 21, -1, dual_row_p0, N * sizeof(*dual_row_p0));
			
			EMX_Send(0, 3, 20, -1, dual_row_p0, N * sizeof(*dual_row_p0));
			
			EMX_Send(0, 2, 19, -1, dual_row_p0, N * sizeof(*dual_row_p0));
			
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
	
	while (EMX_RecvSync(0, 1, 207, -1)) {
		augmenting_path_search_p1();
	}
}


extern void hungarian_parallel_p2(int cost_p2[N][N], int n_p2) {
	int cost_p22[N][N];
	int n_p22;
	double dual_col_p2[N];
	double dual_row_p2[N];
	
	init_potentials_p2(cost_p2);
	
	while (EMX_RecvSync(0, 2, 208, -1)) {
		EMX_Recv(0, 2, 25, -1, dual_col_p2, N * sizeof(*dual_col_p2));
		
		EMX_Recv(0, 2, 19, -1, dual_row_p2, N * sizeof(*dual_row_p2));
		
		augmenting_path_search_p2(n_p2, dual_row_p2, dual_col_p2);
	}
}


extern void hungarian_parallel_p3(int cost_p3[N][N]) {
	int cost_p32[N][N];
	double dual_col_p3[N];
	double dual_row_p3[N];
	
	init_potentials_p3(cost_p3);
	
	while (EMX_RecvSync(0, 3, 209, -1)) {
		EMX_Recv(0, 3, 26, -1, dual_col_p3, N * sizeof(*dual_col_p3));
		
		EMX_Recv(0, 3, 20, -1, dual_row_p3, N * sizeof(*dual_row_p3));
		
		augmenting_path_search_p3(dual_row_p3, dual_col_p3);
	}
}


extern void hungarian_parallel_p4(int cost_p4[N][N]) {
	int cost_p42[N][N];
	double dual_col_p4[N];
	double dual_row_p4[N];
	
	init_potentials_p4(cost_p4);
	
	while (EMX_RecvSync(0, 4, 210, -1)) {
		EMX_Recv(0, 4, 28, -1, dual_col_p4, N * sizeof(*dual_col_p4));
		
		EMX_Recv(0, 4, 22, -1, dual_row_p4, N * sizeof(*dual_row_p4));
		
		augmenting_path_search_p4(dual_row_p4, dual_col_p4);
	}
}


extern void hungarian_parallel_p5(int cost_p5[N][N]) {
	int cost_p52[N][N];
	double dual_col_p5[N];
	double dual_row_p5[N];
	
	init_potentials_p5(cost_p5);
	
	while (EMX_RecvSync(0, 5, 211, -1)) {
		EMX_Recv(0, 5, 27, -1, dual_col_p5, N * sizeof(*dual_col_p5));
		
		EMX_Recv(0, 5, 21, -1, dual_row_p5, N * sizeof(*dual_row_p5));
		
		augmenting_path_search_p5(dual_row_p5, dual_col_p5);
	}
}


extern void hungarian_parallel_p6(int cost_p6[N][N]) {
	int cost_p62[N][N];
	double dual_row_p6[N];
	double dual_col_p6[N];
	
	init_potentials_p6(cost_p6);
	
	while (EMX_RecvSync(0, 6, 212, -1)) {
		EMX_Recv(0, 6, 30, -1, dual_col_p6, N * sizeof(*dual_col_p6));
		
		EMX_Recv(0, 6, 24, -1, dual_row_p6, N * sizeof(*dual_row_p6));
		
		augmenting_path_search_p6(dual_row_p6, dual_col_p6);
	}
}


extern void hungarian_parallel_p7(int cost_p7[N][N]) {
	int cost_p72[N][N];
	double dual_row_p7[N];
	double dual_col_p7[N];
	
	init_potentials_p7(cost_p7);
	
	while (EMX_RecvSync(0, 7, 213, -1)) {
		EMX_Recv(0, 7, 29, -1, dual_col_p7, N * sizeof(*dual_col_p7));
		
		EMX_Recv(0, 7, 23, -1, dual_row_p7, N * sizeof(*dual_row_p7));
		
		augmenting_path_search_p7(dual_row_p7, dual_col_p7);
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
	f = fopen("hun_emmtrix_8.txt", "a");
	f_mean = fopen("hun_emmtrix_8_mean.txt", "a");

	fprintf(f, "Hungarian Parallel Emmtrix (8 Threads): \n");
	fprintf(f, "Size\t\t\t\tCost\t\t\t\tTotal Time in s\t\t\tTotal CPU time in ms\n");

	fprintf(f_mean, "Hungarian Parallel Emmtrix (8 Threads, %d runs): \n", num_test_runs_p0);
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
		
		for (int i_p0 = 0; sync_p0 = (i_p0 < num_test_runs_p0), EMX_SendSync(0, 1, 214, -1, sync_p0), EMX_SendSync(0, 2, 215, -1, sync_p0), EMX_SendSync(0, 3, 216, -1, sync_p0), EMX_SendSync(0, 4, 217, -1, sync_p0), EMX_SendSync(0, 5, 218, -1, sync_p0), EMX_SendSync(0, 6, 219, -1, sync_p0), EMX_SendSync(0, 7, 220, -1, sync_p0), sync_p0; i_p0 = i_p0 + 1) {
			EMX_Send32(0, 1, 17, -1, i_p0);
			
			//EMX_Send64(0, 1, 1, -1, *f_p0);
			
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
				
				EMX_Send(0, 1, 11, -1, cost_p0, N * sizeof(*cost_p0));
				
				EMX_Send(0, 2, 10, -1, cost_p0, N * sizeof(*cost_p0));
				
				EMX_Send(0, 3, 12, -1, cost_p0, N * sizeof(*cost_p0));
				
				EMX_Send(0, 5, 13, -1, cost_p0, N * sizeof(*cost_p0));
				
				EMX_Send(0, 4, 14, -1, cost_p0, N * sizeof(*cost_p0));
				
				EMX_Send(0, 7, 15, -1, cost_p0, N * sizeof(*cost_p0));
				
				EMX_Send(0, 6, 16, -1, cost_p0, N * sizeof(*cost_p0));
				
				callarg4_p0 = hungarian_parallel_p0(cost_p0, n);
				
				EMX_Send32(0, 1, 18, -1, callarg4_p0);
				
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
				f = fopen("hun_emmtrix_8.txt", "a");
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
			
			EMX_Send64F(0, 2, 178, -1, median_timing_p0);
			
			double mean_timing = sum_timing / num_test_runs_p0;
			double mean_time = sum_time / num_test_runs_p0;

			double median_timing = findMedian_p1(timings, num_test_runs_p0);
			double median_time = findMedian_p1(times, num_test_runs_p0);

			// Open a file in append mode
			f_mean = fopen("hun_emmtrix_8_mean.txt", "a");
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
		
		for (int i_p1 = 0; EMX_RecvSync(0, 1, 214, -1); i_p1 = i_p1 + 1) {
			i_p1 = EMX_Recv32(0, 1, 17, -1);
			
			{
				int cost_p1[N][N];
				
				EMX_Recv(0, 1, 11, -1, cost_p1, N * sizeof(*cost_p1));
				
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
					
					callarg4_p1 = EMX_Recv32(0, 1, 18, -1);
					
					times_p1[i_p1] = time_p1;
					timings_p1[i_p1] = timing_p1;
					sum_timing_p1 = sum_timing_p1 + timing_p1;
					sum_time_p1 = sum_time_p1 + time_p1;
					
					callarg6_p1 = timing_p1 / 1000.0;
					
					result_p1 = callarg4_p1;
					
				}
				callarg_p1 = EMX_Recv64(2, 1, 175, -1);
				
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
			
			mean_timing_p1 = EMX_Recv64F(2, 1, 176, -1);
			
			callarg9_p1 = mean_timing_p1 / 1000.0;
			
			median_time_p1 = callarg8_p1;
			
			callarg10_p1 = EMX_Recv64F(2, 1, 179, -1);
			

		}
	}
}


void main_p2() {
	time_t callarg_p2;
	int num_test_runs_p2 = R;
	double callarg10_p2;
	int sum_timing_p2 = 0;
	int sum_time_p2 = 0;
	
	for (int i_p2 = 0; EMX_RecvSync(0, 2, 215, -1); i_p2 = i_p2 + 1) {
		int cost_p2[N][N];
		
		EMX_Recv(0, 2, 10, -1, cost_p2, N * sizeof(*cost_p2));
		
		hungarian_parallel_p2(cost_p2, n);
		
		callarg_p2 = time((void *)0);
		
		EMX_Send64(2, 1, 175, -1, callarg_p2);
	}
	
	{
		double mean_timing_p2 = sum_timing_p2 / num_test_runs_p2;
		double mean_time_p2 = sum_time_p2 / num_test_runs_p2;
		double median_timing_p2;
		
		sum_timing_p2 = EMX_Recv32(1, 2, 7, -1);
		
		sum_time_p2 = EMX_Recv32(1, 2, 6, -1);
		
		median_timing_p2 = EMX_Recv64F(0, 2, 178, -1);
		
		EMX_Send64F(2, 1, 176, -1, mean_timing_p2);
		
		callarg10_p2 = median_timing_p2 / 1000.0;
		
		EMX_Send64F(2, 1, 179, -1, callarg10_p2);
		
		EMX_Send64F(2, 1, 177, -1, mean_time_p2);
	}
}


void main_p3() {
	for (int i_p3 = 0; EMX_RecvSync(0, 3, 216, -1); i_p3 = i_p3 + 1) {
		int cost_p3[N][N];
		
		EMX_Recv(0, 3, 12, -1, cost_p3, N * sizeof(*cost_p3));
		
		hungarian_parallel_p3(cost_p3);
	}
	
}


void main_p4() {
	for (int i_p4 = 0; EMX_RecvSync(0, 4, 217, -1); i_p4 = i_p4 + 1) {
		int cost_p4[N][N];
		
		EMX_Recv(0, 4, 14, -1, cost_p4, N * sizeof(*cost_p4));
		
		hungarian_parallel_p4(cost_p4);
	}
	
}


void main_p5() {
	for (int i_p5 = 0; EMX_RecvSync(0, 5, 218, -1); i_p5 = i_p5 + 1) {
		int cost_p5[N][N];
		
		EMX_Recv(0, 5, 13, -1, cost_p5, N * sizeof(*cost_p5));
		
		hungarian_parallel_p5(cost_p5);
	}
	
}


void main_p6() {
	for (int i_p6 = 0; EMX_RecvSync(0, 6, 219, -1); i_p6 = i_p6 + 1) {
		int cost_p6[N][N];
		
		EMX_Recv(0, 6, 16, -1, cost_p6, N * sizeof(*cost_p6));
		
		hungarian_parallel_p6(cost_p6);
	}
	
}


void main_p7() {
	for (int i_p7 = 0; EMX_RecvSync(0, 7, 220, -1); i_p7 = i_p7 + 1) {
		int cost_p7[N][N];
		
		EMX_Recv(0, 7, 15, -1, cost_p7, N * sizeof(*cost_p7));
		
		hungarian_parallel_p7(cost_p7);
	}
	
}

