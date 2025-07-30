#include "_emx_main.h"

EMX_COMM_CODE_SECTION(0, EMX_Send_0_1) void EMX_Send_0_1(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_0_1(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_0_1(buf, size);
}

EMX_COMM_CODE_SECTION(1, EMX_Recv_0_1) void EMX_Recv_0_1(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_0_1(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_0_1(buf, size);
}

EMX_COMM_CODE_SECTION(0, EMX_Send_0_2) void EMX_Send_0_2(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_0_2(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_0_2(buf, size);
}

EMX_COMM_CODE_SECTION(2, EMX_Recv_0_2) void EMX_Recv_0_2(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_0_2(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_0_2(buf, size);
}

EMX_COMM_CODE_SECTION(0, EMX_Send_0_3) void EMX_Send_0_3(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_0_3(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_0_3(buf, size);
}

EMX_COMM_CODE_SECTION(3, EMX_Recv_0_3) void EMX_Recv_0_3(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_0_3(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_0_3(buf, size);
}

EMX_COMM_CODE_SECTION(0, EMX_Send_0_4) void EMX_Send_0_4(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_0_4(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_0_4(buf, size);
}

EMX_COMM_CODE_SECTION(4, EMX_Recv_0_4) void EMX_Recv_0_4(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_0_4(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_0_4(buf, size);
}

EMX_COMM_CODE_SECTION(0, EMX_Send_0_5) void EMX_Send_0_5(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_0_5(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_0_5(buf, size);
}

EMX_COMM_CODE_SECTION(5, EMX_Recv_0_5) void EMX_Recv_0_5(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_0_5(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_0_5(buf, size);
}

EMX_COMM_CODE_SECTION(0, EMX_Send_0_6) void EMX_Send_0_6(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_0_6(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_0_6(buf, size);
}

EMX_COMM_CODE_SECTION(6, EMX_Recv_0_6) void EMX_Recv_0_6(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_0_6(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_0_6(buf, size);
}

EMX_COMM_CODE_SECTION(0, EMX_Send_0_7) void EMX_Send_0_7(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_0_7(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_0_7(buf, size);
}

EMX_COMM_CODE_SECTION(7, EMX_Recv_0_7) void EMX_Recv_0_7(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_0_7(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_0_7(buf, size);
}

EMX_COMM_CODE_SECTION(1, EMX_Send_1_0) void EMX_Send_1_0(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_1_0(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_1_0(buf, size);
}

EMX_COMM_CODE_SECTION(0, EMX_Recv_1_0) void EMX_Recv_1_0(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_1_0(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_1_0(buf, size);
}

EMX_COMM_CODE_SECTION(1, EMX_Send_1_2) void EMX_Send_1_2(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_1_2(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_1_2(buf, size);
}

EMX_COMM_CODE_SECTION(2, EMX_Recv_1_2) void EMX_Recv_1_2(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_1_2(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_1_2(buf, size);
}

EMX_COMM_CODE_SECTION(1, EMX_Send_1_3) void EMX_Send_1_3(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_1_3(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_1_3(buf, size);
}

EMX_COMM_CODE_SECTION(3, EMX_Recv_1_3) void EMX_Recv_1_3(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_1_3(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_1_3(buf, size);
}

EMX_COMM_CODE_SECTION(1, EMX_Send_1_4) void EMX_Send_1_4(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_1_4(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_1_4(buf, size);
}

EMX_COMM_CODE_SECTION(4, EMX_Recv_1_4) void EMX_Recv_1_4(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_1_4(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_1_4(buf, size);
}

EMX_COMM_CODE_SECTION(1, EMX_Send_1_5) void EMX_Send_1_5(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_1_5(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_1_5(buf, size);
}

EMX_COMM_CODE_SECTION(5, EMX_Recv_1_5) void EMX_Recv_1_5(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_1_5(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_1_5(buf, size);
}

EMX_COMM_CODE_SECTION(1, EMX_Send_1_6) void EMX_Send_1_6(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_1_6(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_1_6(buf, size);
}

EMX_COMM_CODE_SECTION(6, EMX_Recv_1_6) void EMX_Recv_1_6(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_1_6(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_1_6(buf, size);
}

EMX_COMM_CODE_SECTION(1, EMX_Send_1_7) void EMX_Send_1_7(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_1_7(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_1_7(buf, size);
}

EMX_COMM_CODE_SECTION(7, EMX_Recv_1_7) void EMX_Recv_1_7(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_1_7(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_1_7(buf, size);
}

EMX_COMM_CODE_SECTION(2, EMX_Send_2_0) void EMX_Send_2_0(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_2_0(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_2_0(buf, size);
}

EMX_COMM_CODE_SECTION(0, EMX_Recv_2_0) void EMX_Recv_2_0(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_2_0(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_2_0(buf, size);
}

EMX_COMM_CODE_SECTION(2, EMX_Send_2_1) void EMX_Send_2_1(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_2_1(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_2_1(buf, size);
}

EMX_COMM_CODE_SECTION(1, EMX_Recv_2_1) void EMX_Recv_2_1(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_2_1(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_2_1(buf, size);
}

EMX_COMM_CODE_SECTION(2, EMX_Send_2_3) void EMX_Send_2_3(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_2_3(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_2_3(buf, size);
}

EMX_COMM_CODE_SECTION(3, EMX_Recv_2_3) void EMX_Recv_2_3(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_2_3(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_2_3(buf, size);
}

EMX_COMM_CODE_SECTION(2, EMX_Send_2_4) void EMX_Send_2_4(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_2_4(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_2_4(buf, size);
}

EMX_COMM_CODE_SECTION(4, EMX_Recv_2_4) void EMX_Recv_2_4(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_2_4(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_2_4(buf, size);
}

EMX_COMM_CODE_SECTION(2, EMX_Send_2_5) void EMX_Send_2_5(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_2_5(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_2_5(buf, size);
}

EMX_COMM_CODE_SECTION(5, EMX_Recv_2_5) void EMX_Recv_2_5(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_2_5(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_2_5(buf, size);
}

EMX_COMM_CODE_SECTION(2, EMX_Send_2_6) void EMX_Send_2_6(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_2_6(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_2_6(buf, size);
}

EMX_COMM_CODE_SECTION(6, EMX_Recv_2_6) void EMX_Recv_2_6(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_2_6(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_2_6(buf, size);
}

EMX_COMM_CODE_SECTION(2, EMX_Send_2_7) void EMX_Send_2_7(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_2_7(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_2_7(buf, size);
}

EMX_COMM_CODE_SECTION(7, EMX_Recv_2_7) void EMX_Recv_2_7(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_2_7(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_2_7(buf, size);
}

EMX_COMM_CODE_SECTION(3, EMX_Send_3_0) void EMX_Send_3_0(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_3_0(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_3_0(buf, size);
}

EMX_COMM_CODE_SECTION(0, EMX_Recv_3_0) void EMX_Recv_3_0(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_3_0(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_3_0(buf, size);
}

EMX_COMM_CODE_SECTION(3, EMX_Send_3_1) void EMX_Send_3_1(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_3_1(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_3_1(buf, size);
}

EMX_COMM_CODE_SECTION(1, EMX_Recv_3_1) void EMX_Recv_3_1(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_3_1(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_3_1(buf, size);
}

EMX_COMM_CODE_SECTION(3, EMX_Send_3_2) void EMX_Send_3_2(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_3_2(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_3_2(buf, size);
}

EMX_COMM_CODE_SECTION(2, EMX_Recv_3_2) void EMX_Recv_3_2(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_3_2(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_3_2(buf, size);
}

EMX_COMM_CODE_SECTION(3, EMX_Send_3_4) void EMX_Send_3_4(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_3_4(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_3_4(buf, size);
}

EMX_COMM_CODE_SECTION(4, EMX_Recv_3_4) void EMX_Recv_3_4(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_3_4(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_3_4(buf, size);
}

EMX_COMM_CODE_SECTION(3, EMX_Send_3_5) void EMX_Send_3_5(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_3_5(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_3_5(buf, size);
}

EMX_COMM_CODE_SECTION(5, EMX_Recv_3_5) void EMX_Recv_3_5(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_3_5(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_3_5(buf, size);
}

EMX_COMM_CODE_SECTION(3, EMX_Send_3_6) void EMX_Send_3_6(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_3_6(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_3_6(buf, size);
}

EMX_COMM_CODE_SECTION(6, EMX_Recv_3_6) void EMX_Recv_3_6(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_3_6(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_3_6(buf, size);
}

EMX_COMM_CODE_SECTION(3, EMX_Send_3_7) void EMX_Send_3_7(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_3_7(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_3_7(buf, size);
}

EMX_COMM_CODE_SECTION(7, EMX_Recv_3_7) void EMX_Recv_3_7(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_3_7(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_3_7(buf, size);
}

EMX_COMM_CODE_SECTION(4, EMX_Send_4_0) void EMX_Send_4_0(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_4_0(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_4_0(buf, size);
}

EMX_COMM_CODE_SECTION(0, EMX_Recv_4_0) void EMX_Recv_4_0(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_4_0(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_4_0(buf, size);
}

EMX_COMM_CODE_SECTION(4, EMX_Send_4_1) void EMX_Send_4_1(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_4_1(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_4_1(buf, size);
}

EMX_COMM_CODE_SECTION(1, EMX_Recv_4_1) void EMX_Recv_4_1(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_4_1(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_4_1(buf, size);
}

EMX_COMM_CODE_SECTION(4, EMX_Send_4_2) void EMX_Send_4_2(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_4_2(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_4_2(buf, size);
}

EMX_COMM_CODE_SECTION(2, EMX_Recv_4_2) void EMX_Recv_4_2(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_4_2(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_4_2(buf, size);
}

EMX_COMM_CODE_SECTION(4, EMX_Send_4_3) void EMX_Send_4_3(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_4_3(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_4_3(buf, size);
}

EMX_COMM_CODE_SECTION(3, EMX_Recv_4_3) void EMX_Recv_4_3(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_4_3(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_4_3(buf, size);
}

EMX_COMM_CODE_SECTION(4, EMX_Send_4_5) void EMX_Send_4_5(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_4_5(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_4_5(buf, size);
}

EMX_COMM_CODE_SECTION(5, EMX_Recv_4_5) void EMX_Recv_4_5(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_4_5(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_4_5(buf, size);
}

EMX_COMM_CODE_SECTION(4, EMX_Send_4_6) void EMX_Send_4_6(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_4_6(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_4_6(buf, size);
}

EMX_COMM_CODE_SECTION(6, EMX_Recv_4_6) void EMX_Recv_4_6(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_4_6(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_4_6(buf, size);
}

EMX_COMM_CODE_SECTION(4, EMX_Send_4_7) void EMX_Send_4_7(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_4_7(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_4_7(buf, size);
}

EMX_COMM_CODE_SECTION(7, EMX_Recv_4_7) void EMX_Recv_4_7(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_4_7(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_4_7(buf, size);
}

EMX_COMM_CODE_SECTION(5, EMX_Send_5_0) void EMX_Send_5_0(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_5_0(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_5_0(buf, size);
}

EMX_COMM_CODE_SECTION(0, EMX_Recv_5_0) void EMX_Recv_5_0(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_5_0(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_5_0(buf, size);
}

EMX_COMM_CODE_SECTION(5, EMX_Send_5_1) void EMX_Send_5_1(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_5_1(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_5_1(buf, size);
}

EMX_COMM_CODE_SECTION(1, EMX_Recv_5_1) void EMX_Recv_5_1(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_5_1(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_5_1(buf, size);
}

EMX_COMM_CODE_SECTION(5, EMX_Send_5_2) void EMX_Send_5_2(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_5_2(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_5_2(buf, size);
}

EMX_COMM_CODE_SECTION(2, EMX_Recv_5_2) void EMX_Recv_5_2(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_5_2(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_5_2(buf, size);
}

EMX_COMM_CODE_SECTION(5, EMX_Send_5_3) void EMX_Send_5_3(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_5_3(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_5_3(buf, size);
}

EMX_COMM_CODE_SECTION(3, EMX_Recv_5_3) void EMX_Recv_5_3(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_5_3(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_5_3(buf, size);
}

EMX_COMM_CODE_SECTION(5, EMX_Send_5_4) void EMX_Send_5_4(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_5_4(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_5_4(buf, size);
}

EMX_COMM_CODE_SECTION(4, EMX_Recv_5_4) void EMX_Recv_5_4(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_5_4(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_5_4(buf, size);
}

EMX_COMM_CODE_SECTION(5, EMX_Send_5_6) void EMX_Send_5_6(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_5_6(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_5_6(buf, size);
}

EMX_COMM_CODE_SECTION(6, EMX_Recv_5_6) void EMX_Recv_5_6(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_5_6(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_5_6(buf, size);
}

EMX_COMM_CODE_SECTION(5, EMX_Send_5_7) void EMX_Send_5_7(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_5_7(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_5_7(buf, size);
}

EMX_COMM_CODE_SECTION(7, EMX_Recv_5_7) void EMX_Recv_5_7(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_5_7(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_5_7(buf, size);
}

EMX_COMM_CODE_SECTION(6, EMX_Send_6_0) void EMX_Send_6_0(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_6_0(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_6_0(buf, size);
}

EMX_COMM_CODE_SECTION(0, EMX_Recv_6_0) void EMX_Recv_6_0(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_6_0(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_6_0(buf, size);
}

EMX_COMM_CODE_SECTION(6, EMX_Send_6_1) void EMX_Send_6_1(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_6_1(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_6_1(buf, size);
}

EMX_COMM_CODE_SECTION(1, EMX_Recv_6_1) void EMX_Recv_6_1(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_6_1(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_6_1(buf, size);
}

EMX_COMM_CODE_SECTION(6, EMX_Send_6_2) void EMX_Send_6_2(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_6_2(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_6_2(buf, size);
}

EMX_COMM_CODE_SECTION(2, EMX_Recv_6_2) void EMX_Recv_6_2(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_6_2(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_6_2(buf, size);
}

EMX_COMM_CODE_SECTION(6, EMX_Send_6_3) void EMX_Send_6_3(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_6_3(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_6_3(buf, size);
}

EMX_COMM_CODE_SECTION(3, EMX_Recv_6_3) void EMX_Recv_6_3(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_6_3(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_6_3(buf, size);
}

EMX_COMM_CODE_SECTION(6, EMX_Send_6_4) void EMX_Send_6_4(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_6_4(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_6_4(buf, size);
}

EMX_COMM_CODE_SECTION(4, EMX_Recv_6_4) void EMX_Recv_6_4(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_6_4(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_6_4(buf, size);
}

EMX_COMM_CODE_SECTION(6, EMX_Send_6_5) void EMX_Send_6_5(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_6_5(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_6_5(buf, size);
}

EMX_COMM_CODE_SECTION(5, EMX_Recv_6_5) void EMX_Recv_6_5(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_6_5(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_6_5(buf, size);
}

EMX_COMM_CODE_SECTION(6, EMX_Send_6_7) void EMX_Send_6_7(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_6_7(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_6_7(buf, size);
}

EMX_COMM_CODE_SECTION(7, EMX_Recv_6_7) void EMX_Recv_6_7(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_6_7(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_6_7(buf, size);
}

EMX_COMM_CODE_SECTION(7, EMX_Send_7_0) void EMX_Send_7_0(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_7_0(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_7_0(buf, size);
}

EMX_COMM_CODE_SECTION(0, EMX_Recv_7_0) void EMX_Recv_7_0(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_7_0(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_7_0(buf, size);
}

EMX_COMM_CODE_SECTION(7, EMX_Send_7_1) void EMX_Send_7_1(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_7_1(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_7_1(buf, size);
}

EMX_COMM_CODE_SECTION(1, EMX_Recv_7_1) void EMX_Recv_7_1(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_7_1(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_7_1(buf, size);
}

EMX_COMM_CODE_SECTION(7, EMX_Send_7_2) void EMX_Send_7_2(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_7_2(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_7_2(buf, size);
}

EMX_COMM_CODE_SECTION(2, EMX_Recv_7_2) void EMX_Recv_7_2(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_7_2(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_7_2(buf, size);
}

EMX_COMM_CODE_SECTION(7, EMX_Send_7_3) void EMX_Send_7_3(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_7_3(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_7_3(buf, size);
}

EMX_COMM_CODE_SECTION(3, EMX_Recv_7_3) void EMX_Recv_7_3(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_7_3(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_7_3(buf, size);
}

EMX_COMM_CODE_SECTION(7, EMX_Send_7_4) void EMX_Send_7_4(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_7_4(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_7_4(buf, size);
}

EMX_COMM_CODE_SECTION(4, EMX_Recv_7_4) void EMX_Recv_7_4(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_7_4(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_7_4(buf, size);
}

EMX_COMM_CODE_SECTION(7, EMX_Send_7_5) void EMX_Send_7_5(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_7_5(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_7_5(buf, size);
}

EMX_COMM_CODE_SECTION(5, EMX_Recv_7_5) void EMX_Recv_7_5(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_7_5(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_7_5(buf, size);
}

EMX_COMM_CODE_SECTION(7, EMX_Send_7_6) void EMX_Send_7_6(const void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_send_7_6(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_send_7_6(buf, size);
}

EMX_COMM_CODE_SECTION(6, EMX_Recv_7_6) void EMX_Recv_7_6(void *buf, uint32_t size) {
	for (; size >= EMX_RINGBUF_CHUNK_SIZE; size -= EMX_RINGBUF_CHUNK_SIZE) {
		emx_recv_7_6(buf, EMX_RINGBUF_CHUNK_SIZE);
		buf += EMX_RINGBUF_CHUNK_SIZE;
	}

	emx_recv_7_6(buf, size);
}


static void (*emx_sync_functions[EMX_NUM_CORES][2])() = {
	{ EMX_Signal_0_7, EMX_Wait_1_0 },
	{ EMX_Signal_1_0, EMX_Wait_2_1 },
	{ EMX_Signal_2_1, EMX_Wait_3_2 },
	{ EMX_Signal_3_2, EMX_Wait_4_3 },
	{ EMX_Signal_4_3, EMX_Wait_5_4 },
	{ EMX_Signal_5_4, EMX_Wait_6_5 },
	{ EMX_Signal_6_5, EMX_Wait_7_6 },
	{ EMX_Signal_7_6, EMX_Wait_0_7 }
};

void EMX_SyncCores(int core) {
	if (core == EMX_NUM_CORES - 1) {
		(*emx_sync_functions[core][0])();
	}

	(*emx_sync_functions[core][1])();

	if (core != EMX_NUM_CORES - 1) {
		(*emx_sync_functions[core][0])();
	}
}
