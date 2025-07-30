#define _GNU_SOURCE

#include "emxapi_comm_ringbuf_fixed_fork.h"

#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include <sched.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/mman.h>

void emx_ringbuf_wait() {};

#define __USE_GNU 1

void run_main(int core);

static int pids[EMX_NUM_CORES] = {0};
int emx_core;

#ifdef __linux
#include <sys/sysinfo.h>
static void setaffinity(int rank) {
	cpu_set_t mask;
	int status;

	if (rank >= get_nprocs_conf()) {
		return;
	}

	CPU_ZERO(&mask);
	CPU_SET(rank, &mask);
	status = sched_setaffinity(0, sizeof(mask), &mask);
	if (status != 0) {
		perror("sched_setaffinity");
	}
}

#elif defined(__CYGWIN__ )

#include <windows.h>

static void setaffinity(int rank) {
	int cpu = rank * 2;

	DWORD res = SetThreadIdealProcessor(GetCurrentThread(), cpu);
	if (res == -1) {
		fprintf(stderr, "Affinity: %d\n", cpu);
		fprintf(stderr, "Warning: SetThreadIdealProcessor failed (code 0x%X)\n", GetLastError());
	}
}

#else

static void setaffinity(int rank) {
}

#endif

static void sigterm_handler(int signal, siginfo_t *info, void *_unused) {
	fprintf(stderr, "Received SIGTERM from process with pid = %u\n", info->si_pid);
	EMX_Finalize(0);

#ifdef EMX_PROF
	EMX_ProfFinalize();
#endif

	exit(0);
}

int EMX_Init(int argc, char *argv[]) {
	int i;

	emx_rb_buf_0_1 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_0_1 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_0_1 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_0_1 = 0;
	*emx_wr_pos_0_1 = 0;
	emx_rb_buf_0_2 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_0_2 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_0_2 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_0_2 = 0;
	*emx_wr_pos_0_2 = 0;
	emx_rb_buf_0_3 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_0_3 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_0_3 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_0_3 = 0;
	*emx_wr_pos_0_3 = 0;
	emx_rb_buf_0_4 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_0_4 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_0_4 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_0_4 = 0;
	*emx_wr_pos_0_4 = 0;
	emx_rb_buf_0_5 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_0_5 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_0_5 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_0_5 = 0;
	*emx_wr_pos_0_5 = 0;
	emx_rb_buf_0_6 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_0_6 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_0_6 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_0_6 = 0;
	*emx_wr_pos_0_6 = 0;
	emx_rb_buf_0_7 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_0_7 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_0_7 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_0_7 = 0;
	*emx_wr_pos_0_7 = 0;
	emx_rb_buf_1_0 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_1_0 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_1_0 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_1_0 = 0;
	*emx_wr_pos_1_0 = 0;
	emx_rb_buf_1_2 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_1_2 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_1_2 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_1_2 = 0;
	*emx_wr_pos_1_2 = 0;
	emx_rb_buf_1_3 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_1_3 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_1_3 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_1_3 = 0;
	*emx_wr_pos_1_3 = 0;
	emx_rb_buf_1_4 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_1_4 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_1_4 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_1_4 = 0;
	*emx_wr_pos_1_4 = 0;
	emx_rb_buf_1_5 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_1_5 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_1_5 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_1_5 = 0;
	*emx_wr_pos_1_5 = 0;
	emx_rb_buf_1_6 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_1_6 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_1_6 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_1_6 = 0;
	*emx_wr_pos_1_6 = 0;
	emx_rb_buf_1_7 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_1_7 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_1_7 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_1_7 = 0;
	*emx_wr_pos_1_7 = 0;
	emx_rb_buf_2_0 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_2_0 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_2_0 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_2_0 = 0;
	*emx_wr_pos_2_0 = 0;
	emx_rb_buf_2_1 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_2_1 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_2_1 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_2_1 = 0;
	*emx_wr_pos_2_1 = 0;
	emx_rb_buf_2_3 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_2_3 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_2_3 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_2_3 = 0;
	*emx_wr_pos_2_3 = 0;
	emx_rb_buf_2_4 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_2_4 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_2_4 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_2_4 = 0;
	*emx_wr_pos_2_4 = 0;
	emx_rb_buf_2_5 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_2_5 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_2_5 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_2_5 = 0;
	*emx_wr_pos_2_5 = 0;
	emx_rb_buf_2_6 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_2_6 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_2_6 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_2_6 = 0;
	*emx_wr_pos_2_6 = 0;
	emx_rb_buf_2_7 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_2_7 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_2_7 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_2_7 = 0;
	*emx_wr_pos_2_7 = 0;
	emx_rb_buf_3_0 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_3_0 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_3_0 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_3_0 = 0;
	*emx_wr_pos_3_0 = 0;
	emx_rb_buf_3_1 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_3_1 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_3_1 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_3_1 = 0;
	*emx_wr_pos_3_1 = 0;
	emx_rb_buf_3_2 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_3_2 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_3_2 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_3_2 = 0;
	*emx_wr_pos_3_2 = 0;
	emx_rb_buf_3_4 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_3_4 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_3_4 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_3_4 = 0;
	*emx_wr_pos_3_4 = 0;
	emx_rb_buf_3_5 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_3_5 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_3_5 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_3_5 = 0;
	*emx_wr_pos_3_5 = 0;
	emx_rb_buf_3_6 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_3_6 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_3_6 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_3_6 = 0;
	*emx_wr_pos_3_6 = 0;
	emx_rb_buf_3_7 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_3_7 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_3_7 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_3_7 = 0;
	*emx_wr_pos_3_7 = 0;
	emx_rb_buf_4_0 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_4_0 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_4_0 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_4_0 = 0;
	*emx_wr_pos_4_0 = 0;
	emx_rb_buf_4_1 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_4_1 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_4_1 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_4_1 = 0;
	*emx_wr_pos_4_1 = 0;
	emx_rb_buf_4_2 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_4_2 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_4_2 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_4_2 = 0;
	*emx_wr_pos_4_2 = 0;
	emx_rb_buf_4_3 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_4_3 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_4_3 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_4_3 = 0;
	*emx_wr_pos_4_3 = 0;
	emx_rb_buf_4_5 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_4_5 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_4_5 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_4_5 = 0;
	*emx_wr_pos_4_5 = 0;
	emx_rb_buf_4_6 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_4_6 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_4_6 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_4_6 = 0;
	*emx_wr_pos_4_6 = 0;
	emx_rb_buf_4_7 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_4_7 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_4_7 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_4_7 = 0;
	*emx_wr_pos_4_7 = 0;
	emx_rb_buf_5_0 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_5_0 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_5_0 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_5_0 = 0;
	*emx_wr_pos_5_0 = 0;
	emx_rb_buf_5_1 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_5_1 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_5_1 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_5_1 = 0;
	*emx_wr_pos_5_1 = 0;
	emx_rb_buf_5_2 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_5_2 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_5_2 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_5_2 = 0;
	*emx_wr_pos_5_2 = 0;
	emx_rb_buf_5_3 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_5_3 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_5_3 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_5_3 = 0;
	*emx_wr_pos_5_3 = 0;
	emx_rb_buf_5_4 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_5_4 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_5_4 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_5_4 = 0;
	*emx_wr_pos_5_4 = 0;
	emx_rb_buf_5_6 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_5_6 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_5_6 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_5_6 = 0;
	*emx_wr_pos_5_6 = 0;
	emx_rb_buf_5_7 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_5_7 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_5_7 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_5_7 = 0;
	*emx_wr_pos_5_7 = 0;
	emx_rb_buf_6_0 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_6_0 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_6_0 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_6_0 = 0;
	*emx_wr_pos_6_0 = 0;
	emx_rb_buf_6_1 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_6_1 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_6_1 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_6_1 = 0;
	*emx_wr_pos_6_1 = 0;
	emx_rb_buf_6_2 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_6_2 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_6_2 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_6_2 = 0;
	*emx_wr_pos_6_2 = 0;
	emx_rb_buf_6_3 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_6_3 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_6_3 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_6_3 = 0;
	*emx_wr_pos_6_3 = 0;
	emx_rb_buf_6_4 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_6_4 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_6_4 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_6_4 = 0;
	*emx_wr_pos_6_4 = 0;
	emx_rb_buf_6_5 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_6_5 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_6_5 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_6_5 = 0;
	*emx_wr_pos_6_5 = 0;
	emx_rb_buf_6_7 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_6_7 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_6_7 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_6_7 = 0;
	*emx_wr_pos_6_7 = 0;
	emx_rb_buf_7_0 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_7_0 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_7_0 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_7_0 = 0;
	*emx_wr_pos_7_0 = 0;
	emx_rb_buf_7_1 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_7_1 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_7_1 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_7_1 = 0;
	*emx_wr_pos_7_1 = 0;
	emx_rb_buf_7_2 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_7_2 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_7_2 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_7_2 = 0;
	*emx_wr_pos_7_2 = 0;
	emx_rb_buf_7_3 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_7_3 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_7_3 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_7_3 = 0;
	*emx_wr_pos_7_3 = 0;
	emx_rb_buf_7_4 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_7_4 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_7_4 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_7_4 = 0;
	*emx_wr_pos_7_4 = 0;
	emx_rb_buf_7_5 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_7_5 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_7_5 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_7_5 = 0;
	*emx_wr_pos_7_5 = 0;
	emx_rb_buf_7_6 = mmap(0, EMX_RINGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_rd_pos_7_6 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	emx_wr_pos_7_6 = mmap(0, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*emx_rd_pos_7_6 = 0;
	*emx_wr_pos_7_6 = 0;

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	fflush(stdout);

	pids[0] = getpid();
	emx_core = 0;

	for (i = 1; i < EMX_NUM_CORES; ++i) {
		pid_t pid = fork();

		if (pid != 0) {
			pids[i] = pid;
		}

		if (pid == 0) {
			emx_core = i;
			break;
		}
	}

#ifdef __linux
	struct sigaction action = {0};
	action.sa_sigaction = sigterm_handler;
	action.sa_flags = SA_SIGINFO;

	sigaction(SIGTERM, &action, NULL);
#endif

	setaffinity(emx_core);

	return emx_core;
}

void EMX_Finalize() {
}

void EMX_Run() {
	run_main(emx_core);
}

void EMX_Join() {
	int i;

	if (emx_core == 0) {
		for (i = 1; i < EMX_NUM_CORES; ++i) {
			waitpid(pids[i], NULL, 0);
		}
	} else {
		exit(0);
	}
}

