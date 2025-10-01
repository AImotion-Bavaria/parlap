#include "_emx_main.h"
#include <string.h>

#define EMX_ALIGNED(X) (X + (EMX_RINGBUF_ALIGN-1)) & (-EMX_RINGBUF_ALIGN)

volatile uint32_t* emx_wr_pos_0_1;
volatile uint32_t* emx_rd_pos_0_1;
volatile uint8_t* emx_rb_buf_0_1;

void emx_send_array_0_1(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_0_1;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_0_1 + *emx_wr_pos_0_1), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_0_1, *emx_wr_pos_0_1 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_0_1 + *emx_wr_pos_0_1), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_0_1, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_0_1, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_0_1(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_0_1;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_0_1 + *emx_rd_pos_0_1), size);
		EMX_ATOMICWRITE(*emx_rd_pos_0_1, *emx_rd_pos_0_1 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_0_1 + *emx_rd_pos_0_1), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_0_1, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_0_1, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_0_1(uint8_t val) {
	while (emx_ringbuf_free_0_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_0_1 + *emx_wr_pos_0_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_1, *emx_wr_pos_0_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_1, 0);
	}
}

uint8_t EMX_Recv8_0_1() {
	uint8_t val;

	while (emx_ringbuf_size_0_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_0_1 + *emx_rd_pos_0_1);

	EMX_ATOMICWRITE(*emx_rd_pos_0_1, *emx_rd_pos_0_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_1, 0);
	}

	return val;
}

void EMX_Send16_0_1(uint16_t val) {
	while (emx_ringbuf_free_0_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_0_1 + *emx_wr_pos_0_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_1, *emx_wr_pos_0_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_1, 0);
	}
}

uint16_t EMX_Recv16_0_1() {
	uint16_t val;

	while (emx_ringbuf_size_0_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_0_1 + *emx_rd_pos_0_1);

	EMX_ATOMICWRITE(*emx_rd_pos_0_1, *emx_rd_pos_0_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_1, 0);
	}

	return val;
}

void EMX_Send32_0_1(uint32_t val) {
	while (emx_ringbuf_free_0_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_0_1 + *emx_wr_pos_0_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_1, *emx_wr_pos_0_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_1, 0);
	}
}

uint32_t EMX_Recv32_0_1() {
	uint32_t val;

	while (emx_ringbuf_size_0_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_0_1 + *emx_rd_pos_0_1);

	EMX_ATOMICWRITE(*emx_rd_pos_0_1, *emx_rd_pos_0_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_1, 0);
	}

	return val;
}

void EMX_Send64_0_1(uint64_t val) {
	while (emx_ringbuf_free_0_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_0_1 + *emx_wr_pos_0_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_1, *emx_wr_pos_0_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_1, 0);
	}
}

uint64_t EMX_Recv64_0_1() {
	uint64_t val;

	while (emx_ringbuf_size_0_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_0_1 + *emx_rd_pos_0_1);

	EMX_ATOMICWRITE(*emx_rd_pos_0_1, *emx_rd_pos_0_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_1, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_0_2;
volatile uint32_t* emx_rd_pos_0_2;
volatile uint8_t* emx_rb_buf_0_2;

void emx_send_array_0_2(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_0_2;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_0_2 + *emx_wr_pos_0_2), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_0_2, *emx_wr_pos_0_2 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_0_2 + *emx_wr_pos_0_2), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_0_2, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_0_2, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_0_2(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_0_2;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_0_2 + *emx_rd_pos_0_2), size);
		EMX_ATOMICWRITE(*emx_rd_pos_0_2, *emx_rd_pos_0_2 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_0_2 + *emx_rd_pos_0_2), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_0_2, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_0_2, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_0_2(uint8_t val) {
	while (emx_ringbuf_free_0_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_0_2 + *emx_wr_pos_0_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_2, *emx_wr_pos_0_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_2, 0);
	}
}

uint8_t EMX_Recv8_0_2() {
	uint8_t val;

	while (emx_ringbuf_size_0_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_0_2 + *emx_rd_pos_0_2);

	EMX_ATOMICWRITE(*emx_rd_pos_0_2, *emx_rd_pos_0_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_2, 0);
	}

	return val;
}

void EMX_Send16_0_2(uint16_t val) {
	while (emx_ringbuf_free_0_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_0_2 + *emx_wr_pos_0_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_2, *emx_wr_pos_0_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_2, 0);
	}
}

uint16_t EMX_Recv16_0_2() {
	uint16_t val;

	while (emx_ringbuf_size_0_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_0_2 + *emx_rd_pos_0_2);

	EMX_ATOMICWRITE(*emx_rd_pos_0_2, *emx_rd_pos_0_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_2, 0);
	}

	return val;
}

void EMX_Send32_0_2(uint32_t val) {
	while (emx_ringbuf_free_0_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_0_2 + *emx_wr_pos_0_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_2, *emx_wr_pos_0_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_2, 0);
	}
}

uint32_t EMX_Recv32_0_2() {
	uint32_t val;

	while (emx_ringbuf_size_0_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_0_2 + *emx_rd_pos_0_2);

	EMX_ATOMICWRITE(*emx_rd_pos_0_2, *emx_rd_pos_0_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_2, 0);
	}

	return val;
}

void EMX_Send64_0_2(uint64_t val) {
	while (emx_ringbuf_free_0_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_0_2 + *emx_wr_pos_0_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_2, *emx_wr_pos_0_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_2, 0);
	}
}

uint64_t EMX_Recv64_0_2() {
	uint64_t val;

	while (emx_ringbuf_size_0_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_0_2 + *emx_rd_pos_0_2);

	EMX_ATOMICWRITE(*emx_rd_pos_0_2, *emx_rd_pos_0_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_2, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_0_3;
volatile uint32_t* emx_rd_pos_0_3;
volatile uint8_t* emx_rb_buf_0_3;

void emx_send_array_0_3(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_0_3;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_0_3 + *emx_wr_pos_0_3), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_0_3, *emx_wr_pos_0_3 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_0_3 + *emx_wr_pos_0_3), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_0_3, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_0_3, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_0_3(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_0_3;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_0_3 + *emx_rd_pos_0_3), size);
		EMX_ATOMICWRITE(*emx_rd_pos_0_3, *emx_rd_pos_0_3 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_0_3 + *emx_rd_pos_0_3), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_0_3, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_0_3, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_0_3(uint8_t val) {
	while (emx_ringbuf_free_0_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_0_3 + *emx_wr_pos_0_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_3, *emx_wr_pos_0_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_3, 0);
	}
}

uint8_t EMX_Recv8_0_3() {
	uint8_t val;

	while (emx_ringbuf_size_0_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_0_3 + *emx_rd_pos_0_3);

	EMX_ATOMICWRITE(*emx_rd_pos_0_3, *emx_rd_pos_0_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_3, 0);
	}

	return val;
}

void EMX_Send16_0_3(uint16_t val) {
	while (emx_ringbuf_free_0_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_0_3 + *emx_wr_pos_0_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_3, *emx_wr_pos_0_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_3, 0);
	}
}

uint16_t EMX_Recv16_0_3() {
	uint16_t val;

	while (emx_ringbuf_size_0_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_0_3 + *emx_rd_pos_0_3);

	EMX_ATOMICWRITE(*emx_rd_pos_0_3, *emx_rd_pos_0_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_3, 0);
	}

	return val;
}

void EMX_Send32_0_3(uint32_t val) {
	while (emx_ringbuf_free_0_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_0_3 + *emx_wr_pos_0_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_3, *emx_wr_pos_0_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_3, 0);
	}
}

uint32_t EMX_Recv32_0_3() {
	uint32_t val;

	while (emx_ringbuf_size_0_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_0_3 + *emx_rd_pos_0_3);

	EMX_ATOMICWRITE(*emx_rd_pos_0_3, *emx_rd_pos_0_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_3, 0);
	}

	return val;
}

void EMX_Send64_0_3(uint64_t val) {
	while (emx_ringbuf_free_0_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_0_3 + *emx_wr_pos_0_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_3, *emx_wr_pos_0_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_3, 0);
	}
}

uint64_t EMX_Recv64_0_3() {
	uint64_t val;

	while (emx_ringbuf_size_0_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_0_3 + *emx_rd_pos_0_3);

	EMX_ATOMICWRITE(*emx_rd_pos_0_3, *emx_rd_pos_0_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_3, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_0_4;
volatile uint32_t* emx_rd_pos_0_4;
volatile uint8_t* emx_rb_buf_0_4;

void emx_send_array_0_4(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_0_4;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_0_4 + *emx_wr_pos_0_4), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_0_4, *emx_wr_pos_0_4 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_0_4 + *emx_wr_pos_0_4), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_0_4, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_0_4, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_0_4(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_0_4;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_0_4 + *emx_rd_pos_0_4), size);
		EMX_ATOMICWRITE(*emx_rd_pos_0_4, *emx_rd_pos_0_4 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_0_4 + *emx_rd_pos_0_4), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_0_4, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_0_4, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_0_4(uint8_t val) {
	while (emx_ringbuf_free_0_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_0_4 + *emx_wr_pos_0_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_4, *emx_wr_pos_0_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_4, 0);
	}
}

uint8_t EMX_Recv8_0_4() {
	uint8_t val;

	while (emx_ringbuf_size_0_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_0_4 + *emx_rd_pos_0_4);

	EMX_ATOMICWRITE(*emx_rd_pos_0_4, *emx_rd_pos_0_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_4, 0);
	}

	return val;
}

void EMX_Send16_0_4(uint16_t val) {
	while (emx_ringbuf_free_0_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_0_4 + *emx_wr_pos_0_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_4, *emx_wr_pos_0_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_4, 0);
	}
}

uint16_t EMX_Recv16_0_4() {
	uint16_t val;

	while (emx_ringbuf_size_0_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_0_4 + *emx_rd_pos_0_4);

	EMX_ATOMICWRITE(*emx_rd_pos_0_4, *emx_rd_pos_0_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_4, 0);
	}

	return val;
}

void EMX_Send32_0_4(uint32_t val) {
	while (emx_ringbuf_free_0_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_0_4 + *emx_wr_pos_0_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_4, *emx_wr_pos_0_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_4, 0);
	}
}

uint32_t EMX_Recv32_0_4() {
	uint32_t val;

	while (emx_ringbuf_size_0_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_0_4 + *emx_rd_pos_0_4);

	EMX_ATOMICWRITE(*emx_rd_pos_0_4, *emx_rd_pos_0_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_4, 0);
	}

	return val;
}

void EMX_Send64_0_4(uint64_t val) {
	while (emx_ringbuf_free_0_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_0_4 + *emx_wr_pos_0_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_4, *emx_wr_pos_0_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_4, 0);
	}
}

uint64_t EMX_Recv64_0_4() {
	uint64_t val;

	while (emx_ringbuf_size_0_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_0_4 + *emx_rd_pos_0_4);

	EMX_ATOMICWRITE(*emx_rd_pos_0_4, *emx_rd_pos_0_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_4, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_0_5;
volatile uint32_t* emx_rd_pos_0_5;
volatile uint8_t* emx_rb_buf_0_5;

void emx_send_array_0_5(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_0_5;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_0_5 + *emx_wr_pos_0_5), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_0_5, *emx_wr_pos_0_5 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_0_5 + *emx_wr_pos_0_5), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_0_5, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_0_5, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_0_5(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_0_5;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_0_5 + *emx_rd_pos_0_5), size);
		EMX_ATOMICWRITE(*emx_rd_pos_0_5, *emx_rd_pos_0_5 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_0_5 + *emx_rd_pos_0_5), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_0_5, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_0_5, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_0_5(uint8_t val) {
	while (emx_ringbuf_free_0_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_0_5 + *emx_wr_pos_0_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_5, *emx_wr_pos_0_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_5, 0);
	}
}

uint8_t EMX_Recv8_0_5() {
	uint8_t val;

	while (emx_ringbuf_size_0_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_0_5 + *emx_rd_pos_0_5);

	EMX_ATOMICWRITE(*emx_rd_pos_0_5, *emx_rd_pos_0_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_5, 0);
	}

	return val;
}

void EMX_Send16_0_5(uint16_t val) {
	while (emx_ringbuf_free_0_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_0_5 + *emx_wr_pos_0_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_5, *emx_wr_pos_0_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_5, 0);
	}
}

uint16_t EMX_Recv16_0_5() {
	uint16_t val;

	while (emx_ringbuf_size_0_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_0_5 + *emx_rd_pos_0_5);

	EMX_ATOMICWRITE(*emx_rd_pos_0_5, *emx_rd_pos_0_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_5, 0);
	}

	return val;
}

void EMX_Send32_0_5(uint32_t val) {
	while (emx_ringbuf_free_0_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_0_5 + *emx_wr_pos_0_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_5, *emx_wr_pos_0_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_5, 0);
	}
}

uint32_t EMX_Recv32_0_5() {
	uint32_t val;

	while (emx_ringbuf_size_0_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_0_5 + *emx_rd_pos_0_5);

	EMX_ATOMICWRITE(*emx_rd_pos_0_5, *emx_rd_pos_0_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_5, 0);
	}

	return val;
}

void EMX_Send64_0_5(uint64_t val) {
	while (emx_ringbuf_free_0_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_0_5 + *emx_wr_pos_0_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_5, *emx_wr_pos_0_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_5, 0);
	}
}

uint64_t EMX_Recv64_0_5() {
	uint64_t val;

	while (emx_ringbuf_size_0_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_0_5 + *emx_rd_pos_0_5);

	EMX_ATOMICWRITE(*emx_rd_pos_0_5, *emx_rd_pos_0_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_5, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_0_6;
volatile uint32_t* emx_rd_pos_0_6;
volatile uint8_t* emx_rb_buf_0_6;

void emx_send_array_0_6(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_0_6;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_0_6 + *emx_wr_pos_0_6), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_0_6, *emx_wr_pos_0_6 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_0_6 + *emx_wr_pos_0_6), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_0_6, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_0_6, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_0_6(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_0_6;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_0_6 + *emx_rd_pos_0_6), size);
		EMX_ATOMICWRITE(*emx_rd_pos_0_6, *emx_rd_pos_0_6 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_0_6 + *emx_rd_pos_0_6), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_0_6, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_0_6, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_0_6(uint8_t val) {
	while (emx_ringbuf_free_0_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_0_6 + *emx_wr_pos_0_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_6, *emx_wr_pos_0_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_6, 0);
	}
}

uint8_t EMX_Recv8_0_6() {
	uint8_t val;

	while (emx_ringbuf_size_0_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_0_6 + *emx_rd_pos_0_6);

	EMX_ATOMICWRITE(*emx_rd_pos_0_6, *emx_rd_pos_0_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_6, 0);
	}

	return val;
}

void EMX_Send16_0_6(uint16_t val) {
	while (emx_ringbuf_free_0_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_0_6 + *emx_wr_pos_0_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_6, *emx_wr_pos_0_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_6, 0);
	}
}

uint16_t EMX_Recv16_0_6() {
	uint16_t val;

	while (emx_ringbuf_size_0_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_0_6 + *emx_rd_pos_0_6);

	EMX_ATOMICWRITE(*emx_rd_pos_0_6, *emx_rd_pos_0_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_6, 0);
	}

	return val;
}

void EMX_Send32_0_6(uint32_t val) {
	while (emx_ringbuf_free_0_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_0_6 + *emx_wr_pos_0_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_6, *emx_wr_pos_0_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_6, 0);
	}
}

uint32_t EMX_Recv32_0_6() {
	uint32_t val;

	while (emx_ringbuf_size_0_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_0_6 + *emx_rd_pos_0_6);

	EMX_ATOMICWRITE(*emx_rd_pos_0_6, *emx_rd_pos_0_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_6, 0);
	}

	return val;
}

void EMX_Send64_0_6(uint64_t val) {
	while (emx_ringbuf_free_0_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_0_6 + *emx_wr_pos_0_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_6, *emx_wr_pos_0_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_6, 0);
	}
}

uint64_t EMX_Recv64_0_6() {
	uint64_t val;

	while (emx_ringbuf_size_0_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_0_6 + *emx_rd_pos_0_6);

	EMX_ATOMICWRITE(*emx_rd_pos_0_6, *emx_rd_pos_0_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_6, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_0_7;
volatile uint32_t* emx_rd_pos_0_7;
volatile uint8_t* emx_rb_buf_0_7;

void emx_send_array_0_7(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_0_7;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_0_7 + *emx_wr_pos_0_7), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_0_7, *emx_wr_pos_0_7 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_0_7 + *emx_wr_pos_0_7), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_0_7, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_0_7, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_0_7(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_0_7;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_0_7 + *emx_rd_pos_0_7), size);
		EMX_ATOMICWRITE(*emx_rd_pos_0_7, *emx_rd_pos_0_7 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_0_7 + *emx_rd_pos_0_7), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_0_7, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_0_7, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_0_7(uint8_t val) {
	while (emx_ringbuf_free_0_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_0_7 + *emx_wr_pos_0_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_7, *emx_wr_pos_0_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_7, 0);
	}
}

uint8_t EMX_Recv8_0_7() {
	uint8_t val;

	while (emx_ringbuf_size_0_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_0_7 + *emx_rd_pos_0_7);

	EMX_ATOMICWRITE(*emx_rd_pos_0_7, *emx_rd_pos_0_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_7, 0);
	}

	return val;
}

void EMX_Send16_0_7(uint16_t val) {
	while (emx_ringbuf_free_0_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_0_7 + *emx_wr_pos_0_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_7, *emx_wr_pos_0_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_7, 0);
	}
}

uint16_t EMX_Recv16_0_7() {
	uint16_t val;

	while (emx_ringbuf_size_0_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_0_7 + *emx_rd_pos_0_7);

	EMX_ATOMICWRITE(*emx_rd_pos_0_7, *emx_rd_pos_0_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_7, 0);
	}

	return val;
}

void EMX_Send32_0_7(uint32_t val) {
	while (emx_ringbuf_free_0_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_0_7 + *emx_wr_pos_0_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_7, *emx_wr_pos_0_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_7, 0);
	}
}

uint32_t EMX_Recv32_0_7() {
	uint32_t val;

	while (emx_ringbuf_size_0_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_0_7 + *emx_rd_pos_0_7);

	EMX_ATOMICWRITE(*emx_rd_pos_0_7, *emx_rd_pos_0_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_7, 0);
	}

	return val;
}

void EMX_Send64_0_7(uint64_t val) {
	while (emx_ringbuf_free_0_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_0_7 + *emx_wr_pos_0_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_0_7, *emx_wr_pos_0_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_0_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_0_7, 0);
	}
}

uint64_t EMX_Recv64_0_7() {
	uint64_t val;

	while (emx_ringbuf_size_0_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_0_7 + *emx_rd_pos_0_7);

	EMX_ATOMICWRITE(*emx_rd_pos_0_7, *emx_rd_pos_0_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_0_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_0_7, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_1_0;
volatile uint32_t* emx_rd_pos_1_0;
volatile uint8_t* emx_rb_buf_1_0;

void emx_send_array_1_0(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_1_0;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_1_0 + *emx_wr_pos_1_0), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_1_0, *emx_wr_pos_1_0 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_1_0 + *emx_wr_pos_1_0), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_1_0, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_1_0, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_1_0(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_1_0;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_1_0 + *emx_rd_pos_1_0), size);
		EMX_ATOMICWRITE(*emx_rd_pos_1_0, *emx_rd_pos_1_0 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_1_0 + *emx_rd_pos_1_0), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_1_0, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_1_0, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_1_0(uint8_t val) {
	while (emx_ringbuf_free_1_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_1_0 + *emx_wr_pos_1_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_0, *emx_wr_pos_1_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_0, 0);
	}
}

uint8_t EMX_Recv8_1_0() {
	uint8_t val;

	while (emx_ringbuf_size_1_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_1_0 + *emx_rd_pos_1_0);

	EMX_ATOMICWRITE(*emx_rd_pos_1_0, *emx_rd_pos_1_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_0, 0);
	}

	return val;
}

void EMX_Send16_1_0(uint16_t val) {
	while (emx_ringbuf_free_1_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_1_0 + *emx_wr_pos_1_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_0, *emx_wr_pos_1_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_0, 0);
	}
}

uint16_t EMX_Recv16_1_0() {
	uint16_t val;

	while (emx_ringbuf_size_1_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_1_0 + *emx_rd_pos_1_0);

	EMX_ATOMICWRITE(*emx_rd_pos_1_0, *emx_rd_pos_1_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_0, 0);
	}

	return val;
}

void EMX_Send32_1_0(uint32_t val) {
	while (emx_ringbuf_free_1_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_1_0 + *emx_wr_pos_1_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_0, *emx_wr_pos_1_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_0, 0);
	}
}

uint32_t EMX_Recv32_1_0() {
	uint32_t val;

	while (emx_ringbuf_size_1_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_1_0 + *emx_rd_pos_1_0);

	EMX_ATOMICWRITE(*emx_rd_pos_1_0, *emx_rd_pos_1_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_0, 0);
	}

	return val;
}

void EMX_Send64_1_0(uint64_t val) {
	while (emx_ringbuf_free_1_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_1_0 + *emx_wr_pos_1_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_0, *emx_wr_pos_1_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_0, 0);
	}
}

uint64_t EMX_Recv64_1_0() {
	uint64_t val;

	while (emx_ringbuf_size_1_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_1_0 + *emx_rd_pos_1_0);

	EMX_ATOMICWRITE(*emx_rd_pos_1_0, *emx_rd_pos_1_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_0, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_1_2;
volatile uint32_t* emx_rd_pos_1_2;
volatile uint8_t* emx_rb_buf_1_2;

void emx_send_array_1_2(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_1_2;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_1_2 + *emx_wr_pos_1_2), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_1_2, *emx_wr_pos_1_2 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_1_2 + *emx_wr_pos_1_2), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_1_2, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_1_2, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_1_2(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_1_2;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_1_2 + *emx_rd_pos_1_2), size);
		EMX_ATOMICWRITE(*emx_rd_pos_1_2, *emx_rd_pos_1_2 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_1_2 + *emx_rd_pos_1_2), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_1_2, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_1_2, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_1_2(uint8_t val) {
	while (emx_ringbuf_free_1_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_1_2 + *emx_wr_pos_1_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_2, *emx_wr_pos_1_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_2, 0);
	}
}

uint8_t EMX_Recv8_1_2() {
	uint8_t val;

	while (emx_ringbuf_size_1_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_1_2 + *emx_rd_pos_1_2);

	EMX_ATOMICWRITE(*emx_rd_pos_1_2, *emx_rd_pos_1_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_2, 0);
	}

	return val;
}

void EMX_Send16_1_2(uint16_t val) {
	while (emx_ringbuf_free_1_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_1_2 + *emx_wr_pos_1_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_2, *emx_wr_pos_1_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_2, 0);
	}
}

uint16_t EMX_Recv16_1_2() {
	uint16_t val;

	while (emx_ringbuf_size_1_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_1_2 + *emx_rd_pos_1_2);

	EMX_ATOMICWRITE(*emx_rd_pos_1_2, *emx_rd_pos_1_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_2, 0);
	}

	return val;
}

void EMX_Send32_1_2(uint32_t val) {
	while (emx_ringbuf_free_1_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_1_2 + *emx_wr_pos_1_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_2, *emx_wr_pos_1_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_2, 0);
	}
}

uint32_t EMX_Recv32_1_2() {
	uint32_t val;

	while (emx_ringbuf_size_1_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_1_2 + *emx_rd_pos_1_2);

	EMX_ATOMICWRITE(*emx_rd_pos_1_2, *emx_rd_pos_1_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_2, 0);
	}

	return val;
}

void EMX_Send64_1_2(uint64_t val) {
	while (emx_ringbuf_free_1_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_1_2 + *emx_wr_pos_1_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_2, *emx_wr_pos_1_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_2, 0);
	}
}

uint64_t EMX_Recv64_1_2() {
	uint64_t val;

	while (emx_ringbuf_size_1_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_1_2 + *emx_rd_pos_1_2);

	EMX_ATOMICWRITE(*emx_rd_pos_1_2, *emx_rd_pos_1_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_2, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_1_3;
volatile uint32_t* emx_rd_pos_1_3;
volatile uint8_t* emx_rb_buf_1_3;

void emx_send_array_1_3(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_1_3;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_1_3 + *emx_wr_pos_1_3), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_1_3, *emx_wr_pos_1_3 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_1_3 + *emx_wr_pos_1_3), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_1_3, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_1_3, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_1_3(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_1_3;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_1_3 + *emx_rd_pos_1_3), size);
		EMX_ATOMICWRITE(*emx_rd_pos_1_3, *emx_rd_pos_1_3 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_1_3 + *emx_rd_pos_1_3), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_1_3, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_1_3, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_1_3(uint8_t val) {
	while (emx_ringbuf_free_1_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_1_3 + *emx_wr_pos_1_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_3, *emx_wr_pos_1_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_3, 0);
	}
}

uint8_t EMX_Recv8_1_3() {
	uint8_t val;

	while (emx_ringbuf_size_1_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_1_3 + *emx_rd_pos_1_3);

	EMX_ATOMICWRITE(*emx_rd_pos_1_3, *emx_rd_pos_1_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_3, 0);
	}

	return val;
}

void EMX_Send16_1_3(uint16_t val) {
	while (emx_ringbuf_free_1_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_1_3 + *emx_wr_pos_1_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_3, *emx_wr_pos_1_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_3, 0);
	}
}

uint16_t EMX_Recv16_1_3() {
	uint16_t val;

	while (emx_ringbuf_size_1_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_1_3 + *emx_rd_pos_1_3);

	EMX_ATOMICWRITE(*emx_rd_pos_1_3, *emx_rd_pos_1_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_3, 0);
	}

	return val;
}

void EMX_Send32_1_3(uint32_t val) {
	while (emx_ringbuf_free_1_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_1_3 + *emx_wr_pos_1_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_3, *emx_wr_pos_1_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_3, 0);
	}
}

uint32_t EMX_Recv32_1_3() {
	uint32_t val;

	while (emx_ringbuf_size_1_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_1_3 + *emx_rd_pos_1_3);

	EMX_ATOMICWRITE(*emx_rd_pos_1_3, *emx_rd_pos_1_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_3, 0);
	}

	return val;
}

void EMX_Send64_1_3(uint64_t val) {
	while (emx_ringbuf_free_1_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_1_3 + *emx_wr_pos_1_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_3, *emx_wr_pos_1_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_3, 0);
	}
}

uint64_t EMX_Recv64_1_3() {
	uint64_t val;

	while (emx_ringbuf_size_1_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_1_3 + *emx_rd_pos_1_3);

	EMX_ATOMICWRITE(*emx_rd_pos_1_3, *emx_rd_pos_1_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_3, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_1_4;
volatile uint32_t* emx_rd_pos_1_4;
volatile uint8_t* emx_rb_buf_1_4;

void emx_send_array_1_4(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_1_4;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_1_4 + *emx_wr_pos_1_4), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_1_4, *emx_wr_pos_1_4 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_1_4 + *emx_wr_pos_1_4), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_1_4, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_1_4, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_1_4(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_1_4;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_1_4 + *emx_rd_pos_1_4), size);
		EMX_ATOMICWRITE(*emx_rd_pos_1_4, *emx_rd_pos_1_4 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_1_4 + *emx_rd_pos_1_4), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_1_4, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_1_4, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_1_4(uint8_t val) {
	while (emx_ringbuf_free_1_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_1_4 + *emx_wr_pos_1_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_4, *emx_wr_pos_1_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_4, 0);
	}
}

uint8_t EMX_Recv8_1_4() {
	uint8_t val;

	while (emx_ringbuf_size_1_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_1_4 + *emx_rd_pos_1_4);

	EMX_ATOMICWRITE(*emx_rd_pos_1_4, *emx_rd_pos_1_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_4, 0);
	}

	return val;
}

void EMX_Send16_1_4(uint16_t val) {
	while (emx_ringbuf_free_1_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_1_4 + *emx_wr_pos_1_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_4, *emx_wr_pos_1_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_4, 0);
	}
}

uint16_t EMX_Recv16_1_4() {
	uint16_t val;

	while (emx_ringbuf_size_1_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_1_4 + *emx_rd_pos_1_4);

	EMX_ATOMICWRITE(*emx_rd_pos_1_4, *emx_rd_pos_1_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_4, 0);
	}

	return val;
}

void EMX_Send32_1_4(uint32_t val) {
	while (emx_ringbuf_free_1_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_1_4 + *emx_wr_pos_1_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_4, *emx_wr_pos_1_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_4, 0);
	}
}

uint32_t EMX_Recv32_1_4() {
	uint32_t val;

	while (emx_ringbuf_size_1_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_1_4 + *emx_rd_pos_1_4);

	EMX_ATOMICWRITE(*emx_rd_pos_1_4, *emx_rd_pos_1_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_4, 0);
	}

	return val;
}

void EMX_Send64_1_4(uint64_t val) {
	while (emx_ringbuf_free_1_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_1_4 + *emx_wr_pos_1_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_4, *emx_wr_pos_1_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_4, 0);
	}
}

uint64_t EMX_Recv64_1_4() {
	uint64_t val;

	while (emx_ringbuf_size_1_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_1_4 + *emx_rd_pos_1_4);

	EMX_ATOMICWRITE(*emx_rd_pos_1_4, *emx_rd_pos_1_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_4, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_1_5;
volatile uint32_t* emx_rd_pos_1_5;
volatile uint8_t* emx_rb_buf_1_5;

void emx_send_array_1_5(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_1_5;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_1_5 + *emx_wr_pos_1_5), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_1_5, *emx_wr_pos_1_5 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_1_5 + *emx_wr_pos_1_5), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_1_5, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_1_5, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_1_5(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_1_5;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_1_5 + *emx_rd_pos_1_5), size);
		EMX_ATOMICWRITE(*emx_rd_pos_1_5, *emx_rd_pos_1_5 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_1_5 + *emx_rd_pos_1_5), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_1_5, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_1_5, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_1_5(uint8_t val) {
	while (emx_ringbuf_free_1_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_1_5 + *emx_wr_pos_1_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_5, *emx_wr_pos_1_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_5, 0);
	}
}

uint8_t EMX_Recv8_1_5() {
	uint8_t val;

	while (emx_ringbuf_size_1_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_1_5 + *emx_rd_pos_1_5);

	EMX_ATOMICWRITE(*emx_rd_pos_1_5, *emx_rd_pos_1_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_5, 0);
	}

	return val;
}

void EMX_Send16_1_5(uint16_t val) {
	while (emx_ringbuf_free_1_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_1_5 + *emx_wr_pos_1_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_5, *emx_wr_pos_1_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_5, 0);
	}
}

uint16_t EMX_Recv16_1_5() {
	uint16_t val;

	while (emx_ringbuf_size_1_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_1_5 + *emx_rd_pos_1_5);

	EMX_ATOMICWRITE(*emx_rd_pos_1_5, *emx_rd_pos_1_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_5, 0);
	}

	return val;
}

void EMX_Send32_1_5(uint32_t val) {
	while (emx_ringbuf_free_1_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_1_5 + *emx_wr_pos_1_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_5, *emx_wr_pos_1_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_5, 0);
	}
}

uint32_t EMX_Recv32_1_5() {
	uint32_t val;

	while (emx_ringbuf_size_1_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_1_5 + *emx_rd_pos_1_5);

	EMX_ATOMICWRITE(*emx_rd_pos_1_5, *emx_rd_pos_1_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_5, 0);
	}

	return val;
}

void EMX_Send64_1_5(uint64_t val) {
	while (emx_ringbuf_free_1_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_1_5 + *emx_wr_pos_1_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_5, *emx_wr_pos_1_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_5, 0);
	}
}

uint64_t EMX_Recv64_1_5() {
	uint64_t val;

	while (emx_ringbuf_size_1_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_1_5 + *emx_rd_pos_1_5);

	EMX_ATOMICWRITE(*emx_rd_pos_1_5, *emx_rd_pos_1_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_5, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_1_6;
volatile uint32_t* emx_rd_pos_1_6;
volatile uint8_t* emx_rb_buf_1_6;

void emx_send_array_1_6(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_1_6;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_1_6 + *emx_wr_pos_1_6), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_1_6, *emx_wr_pos_1_6 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_1_6 + *emx_wr_pos_1_6), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_1_6, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_1_6, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_1_6(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_1_6;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_1_6 + *emx_rd_pos_1_6), size);
		EMX_ATOMICWRITE(*emx_rd_pos_1_6, *emx_rd_pos_1_6 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_1_6 + *emx_rd_pos_1_6), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_1_6, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_1_6, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_1_6(uint8_t val) {
	while (emx_ringbuf_free_1_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_1_6 + *emx_wr_pos_1_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_6, *emx_wr_pos_1_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_6, 0);
	}
}

uint8_t EMX_Recv8_1_6() {
	uint8_t val;

	while (emx_ringbuf_size_1_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_1_6 + *emx_rd_pos_1_6);

	EMX_ATOMICWRITE(*emx_rd_pos_1_6, *emx_rd_pos_1_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_6, 0);
	}

	return val;
}

void EMX_Send16_1_6(uint16_t val) {
	while (emx_ringbuf_free_1_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_1_6 + *emx_wr_pos_1_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_6, *emx_wr_pos_1_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_6, 0);
	}
}

uint16_t EMX_Recv16_1_6() {
	uint16_t val;

	while (emx_ringbuf_size_1_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_1_6 + *emx_rd_pos_1_6);

	EMX_ATOMICWRITE(*emx_rd_pos_1_6, *emx_rd_pos_1_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_6, 0);
	}

	return val;
}

void EMX_Send32_1_6(uint32_t val) {
	while (emx_ringbuf_free_1_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_1_6 + *emx_wr_pos_1_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_6, *emx_wr_pos_1_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_6, 0);
	}
}

uint32_t EMX_Recv32_1_6() {
	uint32_t val;

	while (emx_ringbuf_size_1_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_1_6 + *emx_rd_pos_1_6);

	EMX_ATOMICWRITE(*emx_rd_pos_1_6, *emx_rd_pos_1_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_6, 0);
	}

	return val;
}

void EMX_Send64_1_6(uint64_t val) {
	while (emx_ringbuf_free_1_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_1_6 + *emx_wr_pos_1_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_6, *emx_wr_pos_1_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_6, 0);
	}
}

uint64_t EMX_Recv64_1_6() {
	uint64_t val;

	while (emx_ringbuf_size_1_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_1_6 + *emx_rd_pos_1_6);

	EMX_ATOMICWRITE(*emx_rd_pos_1_6, *emx_rd_pos_1_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_6, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_1_7;
volatile uint32_t* emx_rd_pos_1_7;
volatile uint8_t* emx_rb_buf_1_7;

void emx_send_array_1_7(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_1_7;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_1_7 + *emx_wr_pos_1_7), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_1_7, *emx_wr_pos_1_7 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_1_7 + *emx_wr_pos_1_7), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_1_7, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_1_7, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_1_7(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_1_7;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_1_7 + *emx_rd_pos_1_7), size);
		EMX_ATOMICWRITE(*emx_rd_pos_1_7, *emx_rd_pos_1_7 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_1_7 + *emx_rd_pos_1_7), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_1_7, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_1_7, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_1_7(uint8_t val) {
	while (emx_ringbuf_free_1_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_1_7 + *emx_wr_pos_1_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_7, *emx_wr_pos_1_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_7, 0);
	}
}

uint8_t EMX_Recv8_1_7() {
	uint8_t val;

	while (emx_ringbuf_size_1_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_1_7 + *emx_rd_pos_1_7);

	EMX_ATOMICWRITE(*emx_rd_pos_1_7, *emx_rd_pos_1_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_7, 0);
	}

	return val;
}

void EMX_Send16_1_7(uint16_t val) {
	while (emx_ringbuf_free_1_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_1_7 + *emx_wr_pos_1_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_7, *emx_wr_pos_1_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_7, 0);
	}
}

uint16_t EMX_Recv16_1_7() {
	uint16_t val;

	while (emx_ringbuf_size_1_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_1_7 + *emx_rd_pos_1_7);

	EMX_ATOMICWRITE(*emx_rd_pos_1_7, *emx_rd_pos_1_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_7, 0);
	}

	return val;
}

void EMX_Send32_1_7(uint32_t val) {
	while (emx_ringbuf_free_1_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_1_7 + *emx_wr_pos_1_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_7, *emx_wr_pos_1_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_7, 0);
	}
}

uint32_t EMX_Recv32_1_7() {
	uint32_t val;

	while (emx_ringbuf_size_1_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_1_7 + *emx_rd_pos_1_7);

	EMX_ATOMICWRITE(*emx_rd_pos_1_7, *emx_rd_pos_1_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_7, 0);
	}

	return val;
}

void EMX_Send64_1_7(uint64_t val) {
	while (emx_ringbuf_free_1_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_1_7 + *emx_wr_pos_1_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_1_7, *emx_wr_pos_1_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_1_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_1_7, 0);
	}
}

uint64_t EMX_Recv64_1_7() {
	uint64_t val;

	while (emx_ringbuf_size_1_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_1_7 + *emx_rd_pos_1_7);

	EMX_ATOMICWRITE(*emx_rd_pos_1_7, *emx_rd_pos_1_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_1_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_1_7, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_2_0;
volatile uint32_t* emx_rd_pos_2_0;
volatile uint8_t* emx_rb_buf_2_0;

void emx_send_array_2_0(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_2_0;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_2_0 + *emx_wr_pos_2_0), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_2_0, *emx_wr_pos_2_0 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_2_0 + *emx_wr_pos_2_0), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_2_0, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_2_0, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_2_0(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_2_0;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_2_0 + *emx_rd_pos_2_0), size);
		EMX_ATOMICWRITE(*emx_rd_pos_2_0, *emx_rd_pos_2_0 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_2_0 + *emx_rd_pos_2_0), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_2_0, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_2_0, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_2_0(uint8_t val) {
	while (emx_ringbuf_free_2_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_2_0 + *emx_wr_pos_2_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_0, *emx_wr_pos_2_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_0, 0);
	}
}

uint8_t EMX_Recv8_2_0() {
	uint8_t val;

	while (emx_ringbuf_size_2_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_2_0 + *emx_rd_pos_2_0);

	EMX_ATOMICWRITE(*emx_rd_pos_2_0, *emx_rd_pos_2_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_0, 0);
	}

	return val;
}

void EMX_Send16_2_0(uint16_t val) {
	while (emx_ringbuf_free_2_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_2_0 + *emx_wr_pos_2_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_0, *emx_wr_pos_2_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_0, 0);
	}
}

uint16_t EMX_Recv16_2_0() {
	uint16_t val;

	while (emx_ringbuf_size_2_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_2_0 + *emx_rd_pos_2_0);

	EMX_ATOMICWRITE(*emx_rd_pos_2_0, *emx_rd_pos_2_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_0, 0);
	}

	return val;
}

void EMX_Send32_2_0(uint32_t val) {
	while (emx_ringbuf_free_2_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_2_0 + *emx_wr_pos_2_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_0, *emx_wr_pos_2_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_0, 0);
	}
}

uint32_t EMX_Recv32_2_0() {
	uint32_t val;

	while (emx_ringbuf_size_2_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_2_0 + *emx_rd_pos_2_0);

	EMX_ATOMICWRITE(*emx_rd_pos_2_0, *emx_rd_pos_2_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_0, 0);
	}

	return val;
}

void EMX_Send64_2_0(uint64_t val) {
	while (emx_ringbuf_free_2_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_2_0 + *emx_wr_pos_2_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_0, *emx_wr_pos_2_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_0, 0);
	}
}

uint64_t EMX_Recv64_2_0() {
	uint64_t val;

	while (emx_ringbuf_size_2_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_2_0 + *emx_rd_pos_2_0);

	EMX_ATOMICWRITE(*emx_rd_pos_2_0, *emx_rd_pos_2_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_0, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_2_1;
volatile uint32_t* emx_rd_pos_2_1;
volatile uint8_t* emx_rb_buf_2_1;

void emx_send_array_2_1(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_2_1;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_2_1 + *emx_wr_pos_2_1), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_2_1, *emx_wr_pos_2_1 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_2_1 + *emx_wr_pos_2_1), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_2_1, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_2_1, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_2_1(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_2_1;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_2_1 + *emx_rd_pos_2_1), size);
		EMX_ATOMICWRITE(*emx_rd_pos_2_1, *emx_rd_pos_2_1 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_2_1 + *emx_rd_pos_2_1), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_2_1, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_2_1, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_2_1(uint8_t val) {
	while (emx_ringbuf_free_2_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_2_1 + *emx_wr_pos_2_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_1, *emx_wr_pos_2_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_1, 0);
	}
}

uint8_t EMX_Recv8_2_1() {
	uint8_t val;

	while (emx_ringbuf_size_2_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_2_1 + *emx_rd_pos_2_1);

	EMX_ATOMICWRITE(*emx_rd_pos_2_1, *emx_rd_pos_2_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_1, 0);
	}

	return val;
}

void EMX_Send16_2_1(uint16_t val) {
	while (emx_ringbuf_free_2_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_2_1 + *emx_wr_pos_2_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_1, *emx_wr_pos_2_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_1, 0);
	}
}

uint16_t EMX_Recv16_2_1() {
	uint16_t val;

	while (emx_ringbuf_size_2_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_2_1 + *emx_rd_pos_2_1);

	EMX_ATOMICWRITE(*emx_rd_pos_2_1, *emx_rd_pos_2_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_1, 0);
	}

	return val;
}

void EMX_Send32_2_1(uint32_t val) {
	while (emx_ringbuf_free_2_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_2_1 + *emx_wr_pos_2_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_1, *emx_wr_pos_2_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_1, 0);
	}
}

uint32_t EMX_Recv32_2_1() {
	uint32_t val;

	while (emx_ringbuf_size_2_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_2_1 + *emx_rd_pos_2_1);

	EMX_ATOMICWRITE(*emx_rd_pos_2_1, *emx_rd_pos_2_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_1, 0);
	}

	return val;
}

void EMX_Send64_2_1(uint64_t val) {
	while (emx_ringbuf_free_2_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_2_1 + *emx_wr_pos_2_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_1, *emx_wr_pos_2_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_1, 0);
	}
}

uint64_t EMX_Recv64_2_1() {
	uint64_t val;

	while (emx_ringbuf_size_2_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_2_1 + *emx_rd_pos_2_1);

	EMX_ATOMICWRITE(*emx_rd_pos_2_1, *emx_rd_pos_2_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_1, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_2_3;
volatile uint32_t* emx_rd_pos_2_3;
volatile uint8_t* emx_rb_buf_2_3;

void emx_send_array_2_3(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_2_3;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_2_3 + *emx_wr_pos_2_3), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_2_3, *emx_wr_pos_2_3 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_2_3 + *emx_wr_pos_2_3), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_2_3, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_2_3, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_2_3(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_2_3;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_2_3 + *emx_rd_pos_2_3), size);
		EMX_ATOMICWRITE(*emx_rd_pos_2_3, *emx_rd_pos_2_3 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_2_3 + *emx_rd_pos_2_3), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_2_3, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_2_3, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_2_3(uint8_t val) {
	while (emx_ringbuf_free_2_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_2_3 + *emx_wr_pos_2_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_3, *emx_wr_pos_2_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_3, 0);
	}
}

uint8_t EMX_Recv8_2_3() {
	uint8_t val;

	while (emx_ringbuf_size_2_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_2_3 + *emx_rd_pos_2_3);

	EMX_ATOMICWRITE(*emx_rd_pos_2_3, *emx_rd_pos_2_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_3, 0);
	}

	return val;
}

void EMX_Send16_2_3(uint16_t val) {
	while (emx_ringbuf_free_2_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_2_3 + *emx_wr_pos_2_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_3, *emx_wr_pos_2_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_3, 0);
	}
}

uint16_t EMX_Recv16_2_3() {
	uint16_t val;

	while (emx_ringbuf_size_2_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_2_3 + *emx_rd_pos_2_3);

	EMX_ATOMICWRITE(*emx_rd_pos_2_3, *emx_rd_pos_2_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_3, 0);
	}

	return val;
}

void EMX_Send32_2_3(uint32_t val) {
	while (emx_ringbuf_free_2_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_2_3 + *emx_wr_pos_2_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_3, *emx_wr_pos_2_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_3, 0);
	}
}

uint32_t EMX_Recv32_2_3() {
	uint32_t val;

	while (emx_ringbuf_size_2_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_2_3 + *emx_rd_pos_2_3);

	EMX_ATOMICWRITE(*emx_rd_pos_2_3, *emx_rd_pos_2_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_3, 0);
	}

	return val;
}

void EMX_Send64_2_3(uint64_t val) {
	while (emx_ringbuf_free_2_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_2_3 + *emx_wr_pos_2_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_3, *emx_wr_pos_2_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_3, 0);
	}
}

uint64_t EMX_Recv64_2_3() {
	uint64_t val;

	while (emx_ringbuf_size_2_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_2_3 + *emx_rd_pos_2_3);

	EMX_ATOMICWRITE(*emx_rd_pos_2_3, *emx_rd_pos_2_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_3, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_2_4;
volatile uint32_t* emx_rd_pos_2_4;
volatile uint8_t* emx_rb_buf_2_4;

void emx_send_array_2_4(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_2_4;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_2_4 + *emx_wr_pos_2_4), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_2_4, *emx_wr_pos_2_4 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_2_4 + *emx_wr_pos_2_4), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_2_4, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_2_4, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_2_4(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_2_4;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_2_4 + *emx_rd_pos_2_4), size);
		EMX_ATOMICWRITE(*emx_rd_pos_2_4, *emx_rd_pos_2_4 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_2_4 + *emx_rd_pos_2_4), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_2_4, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_2_4, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_2_4(uint8_t val) {
	while (emx_ringbuf_free_2_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_2_4 + *emx_wr_pos_2_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_4, *emx_wr_pos_2_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_4, 0);
	}
}

uint8_t EMX_Recv8_2_4() {
	uint8_t val;

	while (emx_ringbuf_size_2_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_2_4 + *emx_rd_pos_2_4);

	EMX_ATOMICWRITE(*emx_rd_pos_2_4, *emx_rd_pos_2_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_4, 0);
	}

	return val;
}

void EMX_Send16_2_4(uint16_t val) {
	while (emx_ringbuf_free_2_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_2_4 + *emx_wr_pos_2_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_4, *emx_wr_pos_2_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_4, 0);
	}
}

uint16_t EMX_Recv16_2_4() {
	uint16_t val;

	while (emx_ringbuf_size_2_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_2_4 + *emx_rd_pos_2_4);

	EMX_ATOMICWRITE(*emx_rd_pos_2_4, *emx_rd_pos_2_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_4, 0);
	}

	return val;
}

void EMX_Send32_2_4(uint32_t val) {
	while (emx_ringbuf_free_2_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_2_4 + *emx_wr_pos_2_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_4, *emx_wr_pos_2_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_4, 0);
	}
}

uint32_t EMX_Recv32_2_4() {
	uint32_t val;

	while (emx_ringbuf_size_2_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_2_4 + *emx_rd_pos_2_4);

	EMX_ATOMICWRITE(*emx_rd_pos_2_4, *emx_rd_pos_2_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_4, 0);
	}

	return val;
}

void EMX_Send64_2_4(uint64_t val) {
	while (emx_ringbuf_free_2_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_2_4 + *emx_wr_pos_2_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_4, *emx_wr_pos_2_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_4, 0);
	}
}

uint64_t EMX_Recv64_2_4() {
	uint64_t val;

	while (emx_ringbuf_size_2_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_2_4 + *emx_rd_pos_2_4);

	EMX_ATOMICWRITE(*emx_rd_pos_2_4, *emx_rd_pos_2_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_4, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_2_5;
volatile uint32_t* emx_rd_pos_2_5;
volatile uint8_t* emx_rb_buf_2_5;

void emx_send_array_2_5(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_2_5;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_2_5 + *emx_wr_pos_2_5), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_2_5, *emx_wr_pos_2_5 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_2_5 + *emx_wr_pos_2_5), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_2_5, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_2_5, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_2_5(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_2_5;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_2_5 + *emx_rd_pos_2_5), size);
		EMX_ATOMICWRITE(*emx_rd_pos_2_5, *emx_rd_pos_2_5 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_2_5 + *emx_rd_pos_2_5), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_2_5, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_2_5, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_2_5(uint8_t val) {
	while (emx_ringbuf_free_2_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_2_5 + *emx_wr_pos_2_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_5, *emx_wr_pos_2_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_5, 0);
	}
}

uint8_t EMX_Recv8_2_5() {
	uint8_t val;

	while (emx_ringbuf_size_2_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_2_5 + *emx_rd_pos_2_5);

	EMX_ATOMICWRITE(*emx_rd_pos_2_5, *emx_rd_pos_2_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_5, 0);
	}

	return val;
}

void EMX_Send16_2_5(uint16_t val) {
	while (emx_ringbuf_free_2_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_2_5 + *emx_wr_pos_2_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_5, *emx_wr_pos_2_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_5, 0);
	}
}

uint16_t EMX_Recv16_2_5() {
	uint16_t val;

	while (emx_ringbuf_size_2_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_2_5 + *emx_rd_pos_2_5);

	EMX_ATOMICWRITE(*emx_rd_pos_2_5, *emx_rd_pos_2_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_5, 0);
	}

	return val;
}

void EMX_Send32_2_5(uint32_t val) {
	while (emx_ringbuf_free_2_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_2_5 + *emx_wr_pos_2_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_5, *emx_wr_pos_2_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_5, 0);
	}
}

uint32_t EMX_Recv32_2_5() {
	uint32_t val;

	while (emx_ringbuf_size_2_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_2_5 + *emx_rd_pos_2_5);

	EMX_ATOMICWRITE(*emx_rd_pos_2_5, *emx_rd_pos_2_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_5, 0);
	}

	return val;
}

void EMX_Send64_2_5(uint64_t val) {
	while (emx_ringbuf_free_2_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_2_5 + *emx_wr_pos_2_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_5, *emx_wr_pos_2_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_5, 0);
	}
}

uint64_t EMX_Recv64_2_5() {
	uint64_t val;

	while (emx_ringbuf_size_2_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_2_5 + *emx_rd_pos_2_5);

	EMX_ATOMICWRITE(*emx_rd_pos_2_5, *emx_rd_pos_2_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_5, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_2_6;
volatile uint32_t* emx_rd_pos_2_6;
volatile uint8_t* emx_rb_buf_2_6;

void emx_send_array_2_6(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_2_6;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_2_6 + *emx_wr_pos_2_6), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_2_6, *emx_wr_pos_2_6 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_2_6 + *emx_wr_pos_2_6), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_2_6, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_2_6, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_2_6(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_2_6;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_2_6 + *emx_rd_pos_2_6), size);
		EMX_ATOMICWRITE(*emx_rd_pos_2_6, *emx_rd_pos_2_6 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_2_6 + *emx_rd_pos_2_6), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_2_6, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_2_6, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_2_6(uint8_t val) {
	while (emx_ringbuf_free_2_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_2_6 + *emx_wr_pos_2_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_6, *emx_wr_pos_2_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_6, 0);
	}
}

uint8_t EMX_Recv8_2_6() {
	uint8_t val;

	while (emx_ringbuf_size_2_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_2_6 + *emx_rd_pos_2_6);

	EMX_ATOMICWRITE(*emx_rd_pos_2_6, *emx_rd_pos_2_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_6, 0);
	}

	return val;
}

void EMX_Send16_2_6(uint16_t val) {
	while (emx_ringbuf_free_2_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_2_6 + *emx_wr_pos_2_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_6, *emx_wr_pos_2_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_6, 0);
	}
}

uint16_t EMX_Recv16_2_6() {
	uint16_t val;

	while (emx_ringbuf_size_2_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_2_6 + *emx_rd_pos_2_6);

	EMX_ATOMICWRITE(*emx_rd_pos_2_6, *emx_rd_pos_2_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_6, 0);
	}

	return val;
}

void EMX_Send32_2_6(uint32_t val) {
	while (emx_ringbuf_free_2_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_2_6 + *emx_wr_pos_2_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_6, *emx_wr_pos_2_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_6, 0);
	}
}

uint32_t EMX_Recv32_2_6() {
	uint32_t val;

	while (emx_ringbuf_size_2_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_2_6 + *emx_rd_pos_2_6);

	EMX_ATOMICWRITE(*emx_rd_pos_2_6, *emx_rd_pos_2_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_6, 0);
	}

	return val;
}

void EMX_Send64_2_6(uint64_t val) {
	while (emx_ringbuf_free_2_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_2_6 + *emx_wr_pos_2_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_6, *emx_wr_pos_2_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_6, 0);
	}
}

uint64_t EMX_Recv64_2_6() {
	uint64_t val;

	while (emx_ringbuf_size_2_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_2_6 + *emx_rd_pos_2_6);

	EMX_ATOMICWRITE(*emx_rd_pos_2_6, *emx_rd_pos_2_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_6, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_2_7;
volatile uint32_t* emx_rd_pos_2_7;
volatile uint8_t* emx_rb_buf_2_7;

void emx_send_array_2_7(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_2_7;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_2_7 + *emx_wr_pos_2_7), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_2_7, *emx_wr_pos_2_7 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_2_7 + *emx_wr_pos_2_7), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_2_7, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_2_7, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_2_7(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_2_7;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_2_7 + *emx_rd_pos_2_7), size);
		EMX_ATOMICWRITE(*emx_rd_pos_2_7, *emx_rd_pos_2_7 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_2_7 + *emx_rd_pos_2_7), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_2_7, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_2_7, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_2_7(uint8_t val) {
	while (emx_ringbuf_free_2_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_2_7 + *emx_wr_pos_2_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_7, *emx_wr_pos_2_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_7, 0);
	}
}

uint8_t EMX_Recv8_2_7() {
	uint8_t val;

	while (emx_ringbuf_size_2_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_2_7 + *emx_rd_pos_2_7);

	EMX_ATOMICWRITE(*emx_rd_pos_2_7, *emx_rd_pos_2_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_7, 0);
	}

	return val;
}

void EMX_Send16_2_7(uint16_t val) {
	while (emx_ringbuf_free_2_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_2_7 + *emx_wr_pos_2_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_7, *emx_wr_pos_2_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_7, 0);
	}
}

uint16_t EMX_Recv16_2_7() {
	uint16_t val;

	while (emx_ringbuf_size_2_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_2_7 + *emx_rd_pos_2_7);

	EMX_ATOMICWRITE(*emx_rd_pos_2_7, *emx_rd_pos_2_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_7, 0);
	}

	return val;
}

void EMX_Send32_2_7(uint32_t val) {
	while (emx_ringbuf_free_2_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_2_7 + *emx_wr_pos_2_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_7, *emx_wr_pos_2_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_7, 0);
	}
}

uint32_t EMX_Recv32_2_7() {
	uint32_t val;

	while (emx_ringbuf_size_2_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_2_7 + *emx_rd_pos_2_7);

	EMX_ATOMICWRITE(*emx_rd_pos_2_7, *emx_rd_pos_2_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_7, 0);
	}

	return val;
}

void EMX_Send64_2_7(uint64_t val) {
	while (emx_ringbuf_free_2_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_2_7 + *emx_wr_pos_2_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_2_7, *emx_wr_pos_2_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_2_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_2_7, 0);
	}
}

uint64_t EMX_Recv64_2_7() {
	uint64_t val;

	while (emx_ringbuf_size_2_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_2_7 + *emx_rd_pos_2_7);

	EMX_ATOMICWRITE(*emx_rd_pos_2_7, *emx_rd_pos_2_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_2_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_2_7, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_3_0;
volatile uint32_t* emx_rd_pos_3_0;
volatile uint8_t* emx_rb_buf_3_0;

void emx_send_array_3_0(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_3_0;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_3_0 + *emx_wr_pos_3_0), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_3_0, *emx_wr_pos_3_0 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_3_0 + *emx_wr_pos_3_0), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_3_0, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_3_0, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_3_0(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_3_0;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_3_0 + *emx_rd_pos_3_0), size);
		EMX_ATOMICWRITE(*emx_rd_pos_3_0, *emx_rd_pos_3_0 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_3_0 + *emx_rd_pos_3_0), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_3_0, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_3_0, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_3_0(uint8_t val) {
	while (emx_ringbuf_free_3_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_3_0 + *emx_wr_pos_3_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_0, *emx_wr_pos_3_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_0, 0);
	}
}

uint8_t EMX_Recv8_3_0() {
	uint8_t val;

	while (emx_ringbuf_size_3_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_3_0 + *emx_rd_pos_3_0);

	EMX_ATOMICWRITE(*emx_rd_pos_3_0, *emx_rd_pos_3_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_0, 0);
	}

	return val;
}

void EMX_Send16_3_0(uint16_t val) {
	while (emx_ringbuf_free_3_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_3_0 + *emx_wr_pos_3_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_0, *emx_wr_pos_3_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_0, 0);
	}
}

uint16_t EMX_Recv16_3_0() {
	uint16_t val;

	while (emx_ringbuf_size_3_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_3_0 + *emx_rd_pos_3_0);

	EMX_ATOMICWRITE(*emx_rd_pos_3_0, *emx_rd_pos_3_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_0, 0);
	}

	return val;
}

void EMX_Send32_3_0(uint32_t val) {
	while (emx_ringbuf_free_3_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_3_0 + *emx_wr_pos_3_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_0, *emx_wr_pos_3_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_0, 0);
	}
}

uint32_t EMX_Recv32_3_0() {
	uint32_t val;

	while (emx_ringbuf_size_3_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_3_0 + *emx_rd_pos_3_0);

	EMX_ATOMICWRITE(*emx_rd_pos_3_0, *emx_rd_pos_3_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_0, 0);
	}

	return val;
}

void EMX_Send64_3_0(uint64_t val) {
	while (emx_ringbuf_free_3_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_3_0 + *emx_wr_pos_3_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_0, *emx_wr_pos_3_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_0, 0);
	}
}

uint64_t EMX_Recv64_3_0() {
	uint64_t val;

	while (emx_ringbuf_size_3_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_3_0 + *emx_rd_pos_3_0);

	EMX_ATOMICWRITE(*emx_rd_pos_3_0, *emx_rd_pos_3_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_0, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_3_1;
volatile uint32_t* emx_rd_pos_3_1;
volatile uint8_t* emx_rb_buf_3_1;

void emx_send_array_3_1(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_3_1;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_3_1 + *emx_wr_pos_3_1), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_3_1, *emx_wr_pos_3_1 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_3_1 + *emx_wr_pos_3_1), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_3_1, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_3_1, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_3_1(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_3_1;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_3_1 + *emx_rd_pos_3_1), size);
		EMX_ATOMICWRITE(*emx_rd_pos_3_1, *emx_rd_pos_3_1 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_3_1 + *emx_rd_pos_3_1), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_3_1, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_3_1, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_3_1(uint8_t val) {
	while (emx_ringbuf_free_3_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_3_1 + *emx_wr_pos_3_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_1, *emx_wr_pos_3_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_1, 0);
	}
}

uint8_t EMX_Recv8_3_1() {
	uint8_t val;

	while (emx_ringbuf_size_3_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_3_1 + *emx_rd_pos_3_1);

	EMX_ATOMICWRITE(*emx_rd_pos_3_1, *emx_rd_pos_3_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_1, 0);
	}

	return val;
}

void EMX_Send16_3_1(uint16_t val) {
	while (emx_ringbuf_free_3_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_3_1 + *emx_wr_pos_3_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_1, *emx_wr_pos_3_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_1, 0);
	}
}

uint16_t EMX_Recv16_3_1() {
	uint16_t val;

	while (emx_ringbuf_size_3_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_3_1 + *emx_rd_pos_3_1);

	EMX_ATOMICWRITE(*emx_rd_pos_3_1, *emx_rd_pos_3_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_1, 0);
	}

	return val;
}

void EMX_Send32_3_1(uint32_t val) {
	while (emx_ringbuf_free_3_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_3_1 + *emx_wr_pos_3_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_1, *emx_wr_pos_3_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_1, 0);
	}
}

uint32_t EMX_Recv32_3_1() {
	uint32_t val;

	while (emx_ringbuf_size_3_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_3_1 + *emx_rd_pos_3_1);

	EMX_ATOMICWRITE(*emx_rd_pos_3_1, *emx_rd_pos_3_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_1, 0);
	}

	return val;
}

void EMX_Send64_3_1(uint64_t val) {
	while (emx_ringbuf_free_3_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_3_1 + *emx_wr_pos_3_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_1, *emx_wr_pos_3_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_1, 0);
	}
}

uint64_t EMX_Recv64_3_1() {
	uint64_t val;

	while (emx_ringbuf_size_3_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_3_1 + *emx_rd_pos_3_1);

	EMX_ATOMICWRITE(*emx_rd_pos_3_1, *emx_rd_pos_3_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_1, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_3_2;
volatile uint32_t* emx_rd_pos_3_2;
volatile uint8_t* emx_rb_buf_3_2;

void emx_send_array_3_2(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_3_2;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_3_2 + *emx_wr_pos_3_2), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_3_2, *emx_wr_pos_3_2 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_3_2 + *emx_wr_pos_3_2), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_3_2, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_3_2, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_3_2(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_3_2;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_3_2 + *emx_rd_pos_3_2), size);
		EMX_ATOMICWRITE(*emx_rd_pos_3_2, *emx_rd_pos_3_2 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_3_2 + *emx_rd_pos_3_2), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_3_2, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_3_2, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_3_2(uint8_t val) {
	while (emx_ringbuf_free_3_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_3_2 + *emx_wr_pos_3_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_2, *emx_wr_pos_3_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_2, 0);
	}
}

uint8_t EMX_Recv8_3_2() {
	uint8_t val;

	while (emx_ringbuf_size_3_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_3_2 + *emx_rd_pos_3_2);

	EMX_ATOMICWRITE(*emx_rd_pos_3_2, *emx_rd_pos_3_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_2, 0);
	}

	return val;
}

void EMX_Send16_3_2(uint16_t val) {
	while (emx_ringbuf_free_3_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_3_2 + *emx_wr_pos_3_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_2, *emx_wr_pos_3_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_2, 0);
	}
}

uint16_t EMX_Recv16_3_2() {
	uint16_t val;

	while (emx_ringbuf_size_3_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_3_2 + *emx_rd_pos_3_2);

	EMX_ATOMICWRITE(*emx_rd_pos_3_2, *emx_rd_pos_3_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_2, 0);
	}

	return val;
}

void EMX_Send32_3_2(uint32_t val) {
	while (emx_ringbuf_free_3_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_3_2 + *emx_wr_pos_3_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_2, *emx_wr_pos_3_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_2, 0);
	}
}

uint32_t EMX_Recv32_3_2() {
	uint32_t val;

	while (emx_ringbuf_size_3_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_3_2 + *emx_rd_pos_3_2);

	EMX_ATOMICWRITE(*emx_rd_pos_3_2, *emx_rd_pos_3_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_2, 0);
	}

	return val;
}

void EMX_Send64_3_2(uint64_t val) {
	while (emx_ringbuf_free_3_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_3_2 + *emx_wr_pos_3_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_2, *emx_wr_pos_3_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_2, 0);
	}
}

uint64_t EMX_Recv64_3_2() {
	uint64_t val;

	while (emx_ringbuf_size_3_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_3_2 + *emx_rd_pos_3_2);

	EMX_ATOMICWRITE(*emx_rd_pos_3_2, *emx_rd_pos_3_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_2, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_3_4;
volatile uint32_t* emx_rd_pos_3_4;
volatile uint8_t* emx_rb_buf_3_4;

void emx_send_array_3_4(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_3_4;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_3_4 + *emx_wr_pos_3_4), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_3_4, *emx_wr_pos_3_4 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_3_4 + *emx_wr_pos_3_4), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_3_4, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_3_4, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_3_4(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_3_4;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_3_4 + *emx_rd_pos_3_4), size);
		EMX_ATOMICWRITE(*emx_rd_pos_3_4, *emx_rd_pos_3_4 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_3_4 + *emx_rd_pos_3_4), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_3_4, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_3_4, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_3_4(uint8_t val) {
	while (emx_ringbuf_free_3_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_3_4 + *emx_wr_pos_3_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_4, *emx_wr_pos_3_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_4, 0);
	}
}

uint8_t EMX_Recv8_3_4() {
	uint8_t val;

	while (emx_ringbuf_size_3_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_3_4 + *emx_rd_pos_3_4);

	EMX_ATOMICWRITE(*emx_rd_pos_3_4, *emx_rd_pos_3_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_4, 0);
	}

	return val;
}

void EMX_Send16_3_4(uint16_t val) {
	while (emx_ringbuf_free_3_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_3_4 + *emx_wr_pos_3_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_4, *emx_wr_pos_3_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_4, 0);
	}
}

uint16_t EMX_Recv16_3_4() {
	uint16_t val;

	while (emx_ringbuf_size_3_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_3_4 + *emx_rd_pos_3_4);

	EMX_ATOMICWRITE(*emx_rd_pos_3_4, *emx_rd_pos_3_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_4, 0);
	}

	return val;
}

void EMX_Send32_3_4(uint32_t val) {
	while (emx_ringbuf_free_3_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_3_4 + *emx_wr_pos_3_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_4, *emx_wr_pos_3_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_4, 0);
	}
}

uint32_t EMX_Recv32_3_4() {
	uint32_t val;

	while (emx_ringbuf_size_3_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_3_4 + *emx_rd_pos_3_4);

	EMX_ATOMICWRITE(*emx_rd_pos_3_4, *emx_rd_pos_3_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_4, 0);
	}

	return val;
}

void EMX_Send64_3_4(uint64_t val) {
	while (emx_ringbuf_free_3_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_3_4 + *emx_wr_pos_3_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_4, *emx_wr_pos_3_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_4, 0);
	}
}

uint64_t EMX_Recv64_3_4() {
	uint64_t val;

	while (emx_ringbuf_size_3_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_3_4 + *emx_rd_pos_3_4);

	EMX_ATOMICWRITE(*emx_rd_pos_3_4, *emx_rd_pos_3_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_4, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_3_5;
volatile uint32_t* emx_rd_pos_3_5;
volatile uint8_t* emx_rb_buf_3_5;

void emx_send_array_3_5(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_3_5;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_3_5 + *emx_wr_pos_3_5), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_3_5, *emx_wr_pos_3_5 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_3_5 + *emx_wr_pos_3_5), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_3_5, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_3_5, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_3_5(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_3_5;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_3_5 + *emx_rd_pos_3_5), size);
		EMX_ATOMICWRITE(*emx_rd_pos_3_5, *emx_rd_pos_3_5 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_3_5 + *emx_rd_pos_3_5), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_3_5, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_3_5, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_3_5(uint8_t val) {
	while (emx_ringbuf_free_3_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_3_5 + *emx_wr_pos_3_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_5, *emx_wr_pos_3_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_5, 0);
	}
}

uint8_t EMX_Recv8_3_5() {
	uint8_t val;

	while (emx_ringbuf_size_3_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_3_5 + *emx_rd_pos_3_5);

	EMX_ATOMICWRITE(*emx_rd_pos_3_5, *emx_rd_pos_3_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_5, 0);
	}

	return val;
}

void EMX_Send16_3_5(uint16_t val) {
	while (emx_ringbuf_free_3_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_3_5 + *emx_wr_pos_3_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_5, *emx_wr_pos_3_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_5, 0);
	}
}

uint16_t EMX_Recv16_3_5() {
	uint16_t val;

	while (emx_ringbuf_size_3_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_3_5 + *emx_rd_pos_3_5);

	EMX_ATOMICWRITE(*emx_rd_pos_3_5, *emx_rd_pos_3_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_5, 0);
	}

	return val;
}

void EMX_Send32_3_5(uint32_t val) {
	while (emx_ringbuf_free_3_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_3_5 + *emx_wr_pos_3_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_5, *emx_wr_pos_3_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_5, 0);
	}
}

uint32_t EMX_Recv32_3_5() {
	uint32_t val;

	while (emx_ringbuf_size_3_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_3_5 + *emx_rd_pos_3_5);

	EMX_ATOMICWRITE(*emx_rd_pos_3_5, *emx_rd_pos_3_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_5, 0);
	}

	return val;
}

void EMX_Send64_3_5(uint64_t val) {
	while (emx_ringbuf_free_3_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_3_5 + *emx_wr_pos_3_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_5, *emx_wr_pos_3_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_5, 0);
	}
}

uint64_t EMX_Recv64_3_5() {
	uint64_t val;

	while (emx_ringbuf_size_3_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_3_5 + *emx_rd_pos_3_5);

	EMX_ATOMICWRITE(*emx_rd_pos_3_5, *emx_rd_pos_3_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_5, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_3_6;
volatile uint32_t* emx_rd_pos_3_6;
volatile uint8_t* emx_rb_buf_3_6;

void emx_send_array_3_6(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_3_6;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_3_6 + *emx_wr_pos_3_6), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_3_6, *emx_wr_pos_3_6 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_3_6 + *emx_wr_pos_3_6), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_3_6, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_3_6, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_3_6(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_3_6;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_3_6 + *emx_rd_pos_3_6), size);
		EMX_ATOMICWRITE(*emx_rd_pos_3_6, *emx_rd_pos_3_6 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_3_6 + *emx_rd_pos_3_6), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_3_6, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_3_6, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_3_6(uint8_t val) {
	while (emx_ringbuf_free_3_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_3_6 + *emx_wr_pos_3_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_6, *emx_wr_pos_3_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_6, 0);
	}
}

uint8_t EMX_Recv8_3_6() {
	uint8_t val;

	while (emx_ringbuf_size_3_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_3_6 + *emx_rd_pos_3_6);

	EMX_ATOMICWRITE(*emx_rd_pos_3_6, *emx_rd_pos_3_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_6, 0);
	}

	return val;
}

void EMX_Send16_3_6(uint16_t val) {
	while (emx_ringbuf_free_3_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_3_6 + *emx_wr_pos_3_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_6, *emx_wr_pos_3_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_6, 0);
	}
}

uint16_t EMX_Recv16_3_6() {
	uint16_t val;

	while (emx_ringbuf_size_3_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_3_6 + *emx_rd_pos_3_6);

	EMX_ATOMICWRITE(*emx_rd_pos_3_6, *emx_rd_pos_3_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_6, 0);
	}

	return val;
}

void EMX_Send32_3_6(uint32_t val) {
	while (emx_ringbuf_free_3_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_3_6 + *emx_wr_pos_3_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_6, *emx_wr_pos_3_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_6, 0);
	}
}

uint32_t EMX_Recv32_3_6() {
	uint32_t val;

	while (emx_ringbuf_size_3_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_3_6 + *emx_rd_pos_3_6);

	EMX_ATOMICWRITE(*emx_rd_pos_3_6, *emx_rd_pos_3_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_6, 0);
	}

	return val;
}

void EMX_Send64_3_6(uint64_t val) {
	while (emx_ringbuf_free_3_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_3_6 + *emx_wr_pos_3_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_6, *emx_wr_pos_3_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_6, 0);
	}
}

uint64_t EMX_Recv64_3_6() {
	uint64_t val;

	while (emx_ringbuf_size_3_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_3_6 + *emx_rd_pos_3_6);

	EMX_ATOMICWRITE(*emx_rd_pos_3_6, *emx_rd_pos_3_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_6, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_3_7;
volatile uint32_t* emx_rd_pos_3_7;
volatile uint8_t* emx_rb_buf_3_7;

void emx_send_array_3_7(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_3_7;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_3_7 + *emx_wr_pos_3_7), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_3_7, *emx_wr_pos_3_7 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_3_7 + *emx_wr_pos_3_7), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_3_7, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_3_7, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_3_7(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_3_7;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_3_7 + *emx_rd_pos_3_7), size);
		EMX_ATOMICWRITE(*emx_rd_pos_3_7, *emx_rd_pos_3_7 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_3_7 + *emx_rd_pos_3_7), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_3_7, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_3_7, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_3_7(uint8_t val) {
	while (emx_ringbuf_free_3_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_3_7 + *emx_wr_pos_3_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_7, *emx_wr_pos_3_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_7, 0);
	}
}

uint8_t EMX_Recv8_3_7() {
	uint8_t val;

	while (emx_ringbuf_size_3_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_3_7 + *emx_rd_pos_3_7);

	EMX_ATOMICWRITE(*emx_rd_pos_3_7, *emx_rd_pos_3_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_7, 0);
	}

	return val;
}

void EMX_Send16_3_7(uint16_t val) {
	while (emx_ringbuf_free_3_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_3_7 + *emx_wr_pos_3_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_7, *emx_wr_pos_3_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_7, 0);
	}
}

uint16_t EMX_Recv16_3_7() {
	uint16_t val;

	while (emx_ringbuf_size_3_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_3_7 + *emx_rd_pos_3_7);

	EMX_ATOMICWRITE(*emx_rd_pos_3_7, *emx_rd_pos_3_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_7, 0);
	}

	return val;
}

void EMX_Send32_3_7(uint32_t val) {
	while (emx_ringbuf_free_3_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_3_7 + *emx_wr_pos_3_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_7, *emx_wr_pos_3_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_7, 0);
	}
}

uint32_t EMX_Recv32_3_7() {
	uint32_t val;

	while (emx_ringbuf_size_3_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_3_7 + *emx_rd_pos_3_7);

	EMX_ATOMICWRITE(*emx_rd_pos_3_7, *emx_rd_pos_3_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_7, 0);
	}

	return val;
}

void EMX_Send64_3_7(uint64_t val) {
	while (emx_ringbuf_free_3_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_3_7 + *emx_wr_pos_3_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_3_7, *emx_wr_pos_3_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_3_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_3_7, 0);
	}
}

uint64_t EMX_Recv64_3_7() {
	uint64_t val;

	while (emx_ringbuf_size_3_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_3_7 + *emx_rd_pos_3_7);

	EMX_ATOMICWRITE(*emx_rd_pos_3_7, *emx_rd_pos_3_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_3_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_3_7, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_4_0;
volatile uint32_t* emx_rd_pos_4_0;
volatile uint8_t* emx_rb_buf_4_0;

void emx_send_array_4_0(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_4_0;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_4_0 + *emx_wr_pos_4_0), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_4_0, *emx_wr_pos_4_0 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_4_0 + *emx_wr_pos_4_0), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_4_0, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_4_0, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_4_0(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_4_0;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_4_0 + *emx_rd_pos_4_0), size);
		EMX_ATOMICWRITE(*emx_rd_pos_4_0, *emx_rd_pos_4_0 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_4_0 + *emx_rd_pos_4_0), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_4_0, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_4_0, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_4_0(uint8_t val) {
	while (emx_ringbuf_free_4_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_4_0 + *emx_wr_pos_4_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_0, *emx_wr_pos_4_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_0, 0);
	}
}

uint8_t EMX_Recv8_4_0() {
	uint8_t val;

	while (emx_ringbuf_size_4_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_4_0 + *emx_rd_pos_4_0);

	EMX_ATOMICWRITE(*emx_rd_pos_4_0, *emx_rd_pos_4_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_0, 0);
	}

	return val;
}

void EMX_Send16_4_0(uint16_t val) {
	while (emx_ringbuf_free_4_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_4_0 + *emx_wr_pos_4_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_0, *emx_wr_pos_4_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_0, 0);
	}
}

uint16_t EMX_Recv16_4_0() {
	uint16_t val;

	while (emx_ringbuf_size_4_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_4_0 + *emx_rd_pos_4_0);

	EMX_ATOMICWRITE(*emx_rd_pos_4_0, *emx_rd_pos_4_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_0, 0);
	}

	return val;
}

void EMX_Send32_4_0(uint32_t val) {
	while (emx_ringbuf_free_4_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_4_0 + *emx_wr_pos_4_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_0, *emx_wr_pos_4_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_0, 0);
	}
}

uint32_t EMX_Recv32_4_0() {
	uint32_t val;

	while (emx_ringbuf_size_4_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_4_0 + *emx_rd_pos_4_0);

	EMX_ATOMICWRITE(*emx_rd_pos_4_0, *emx_rd_pos_4_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_0, 0);
	}

	return val;
}

void EMX_Send64_4_0(uint64_t val) {
	while (emx_ringbuf_free_4_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_4_0 + *emx_wr_pos_4_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_0, *emx_wr_pos_4_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_0, 0);
	}
}

uint64_t EMX_Recv64_4_0() {
	uint64_t val;

	while (emx_ringbuf_size_4_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_4_0 + *emx_rd_pos_4_0);

	EMX_ATOMICWRITE(*emx_rd_pos_4_0, *emx_rd_pos_4_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_0, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_4_1;
volatile uint32_t* emx_rd_pos_4_1;
volatile uint8_t* emx_rb_buf_4_1;

void emx_send_array_4_1(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_4_1;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_4_1 + *emx_wr_pos_4_1), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_4_1, *emx_wr_pos_4_1 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_4_1 + *emx_wr_pos_4_1), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_4_1, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_4_1, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_4_1(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_4_1;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_4_1 + *emx_rd_pos_4_1), size);
		EMX_ATOMICWRITE(*emx_rd_pos_4_1, *emx_rd_pos_4_1 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_4_1 + *emx_rd_pos_4_1), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_4_1, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_4_1, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_4_1(uint8_t val) {
	while (emx_ringbuf_free_4_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_4_1 + *emx_wr_pos_4_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_1, *emx_wr_pos_4_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_1, 0);
	}
}

uint8_t EMX_Recv8_4_1() {
	uint8_t val;

	while (emx_ringbuf_size_4_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_4_1 + *emx_rd_pos_4_1);

	EMX_ATOMICWRITE(*emx_rd_pos_4_1, *emx_rd_pos_4_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_1, 0);
	}

	return val;
}

void EMX_Send16_4_1(uint16_t val) {
	while (emx_ringbuf_free_4_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_4_1 + *emx_wr_pos_4_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_1, *emx_wr_pos_4_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_1, 0);
	}
}

uint16_t EMX_Recv16_4_1() {
	uint16_t val;

	while (emx_ringbuf_size_4_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_4_1 + *emx_rd_pos_4_1);

	EMX_ATOMICWRITE(*emx_rd_pos_4_1, *emx_rd_pos_4_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_1, 0);
	}

	return val;
}

void EMX_Send32_4_1(uint32_t val) {
	while (emx_ringbuf_free_4_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_4_1 + *emx_wr_pos_4_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_1, *emx_wr_pos_4_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_1, 0);
	}
}

uint32_t EMX_Recv32_4_1() {
	uint32_t val;

	while (emx_ringbuf_size_4_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_4_1 + *emx_rd_pos_4_1);

	EMX_ATOMICWRITE(*emx_rd_pos_4_1, *emx_rd_pos_4_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_1, 0);
	}

	return val;
}

void EMX_Send64_4_1(uint64_t val) {
	while (emx_ringbuf_free_4_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_4_1 + *emx_wr_pos_4_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_1, *emx_wr_pos_4_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_1, 0);
	}
}

uint64_t EMX_Recv64_4_1() {
	uint64_t val;

	while (emx_ringbuf_size_4_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_4_1 + *emx_rd_pos_4_1);

	EMX_ATOMICWRITE(*emx_rd_pos_4_1, *emx_rd_pos_4_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_1, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_4_2;
volatile uint32_t* emx_rd_pos_4_2;
volatile uint8_t* emx_rb_buf_4_2;

void emx_send_array_4_2(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_4_2;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_4_2 + *emx_wr_pos_4_2), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_4_2, *emx_wr_pos_4_2 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_4_2 + *emx_wr_pos_4_2), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_4_2, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_4_2, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_4_2(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_4_2;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_4_2 + *emx_rd_pos_4_2), size);
		EMX_ATOMICWRITE(*emx_rd_pos_4_2, *emx_rd_pos_4_2 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_4_2 + *emx_rd_pos_4_2), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_4_2, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_4_2, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_4_2(uint8_t val) {
	while (emx_ringbuf_free_4_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_4_2 + *emx_wr_pos_4_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_2, *emx_wr_pos_4_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_2, 0);
	}
}

uint8_t EMX_Recv8_4_2() {
	uint8_t val;

	while (emx_ringbuf_size_4_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_4_2 + *emx_rd_pos_4_2);

	EMX_ATOMICWRITE(*emx_rd_pos_4_2, *emx_rd_pos_4_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_2, 0);
	}

	return val;
}

void EMX_Send16_4_2(uint16_t val) {
	while (emx_ringbuf_free_4_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_4_2 + *emx_wr_pos_4_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_2, *emx_wr_pos_4_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_2, 0);
	}
}

uint16_t EMX_Recv16_4_2() {
	uint16_t val;

	while (emx_ringbuf_size_4_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_4_2 + *emx_rd_pos_4_2);

	EMX_ATOMICWRITE(*emx_rd_pos_4_2, *emx_rd_pos_4_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_2, 0);
	}

	return val;
}

void EMX_Send32_4_2(uint32_t val) {
	while (emx_ringbuf_free_4_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_4_2 + *emx_wr_pos_4_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_2, *emx_wr_pos_4_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_2, 0);
	}
}

uint32_t EMX_Recv32_4_2() {
	uint32_t val;

	while (emx_ringbuf_size_4_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_4_2 + *emx_rd_pos_4_2);

	EMX_ATOMICWRITE(*emx_rd_pos_4_2, *emx_rd_pos_4_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_2, 0);
	}

	return val;
}

void EMX_Send64_4_2(uint64_t val) {
	while (emx_ringbuf_free_4_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_4_2 + *emx_wr_pos_4_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_2, *emx_wr_pos_4_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_2, 0);
	}
}

uint64_t EMX_Recv64_4_2() {
	uint64_t val;

	while (emx_ringbuf_size_4_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_4_2 + *emx_rd_pos_4_2);

	EMX_ATOMICWRITE(*emx_rd_pos_4_2, *emx_rd_pos_4_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_2, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_4_3;
volatile uint32_t* emx_rd_pos_4_3;
volatile uint8_t* emx_rb_buf_4_3;

void emx_send_array_4_3(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_4_3;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_4_3 + *emx_wr_pos_4_3), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_4_3, *emx_wr_pos_4_3 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_4_3 + *emx_wr_pos_4_3), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_4_3, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_4_3, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_4_3(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_4_3;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_4_3 + *emx_rd_pos_4_3), size);
		EMX_ATOMICWRITE(*emx_rd_pos_4_3, *emx_rd_pos_4_3 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_4_3 + *emx_rd_pos_4_3), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_4_3, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_4_3, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_4_3(uint8_t val) {
	while (emx_ringbuf_free_4_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_4_3 + *emx_wr_pos_4_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_3, *emx_wr_pos_4_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_3, 0);
	}
}

uint8_t EMX_Recv8_4_3() {
	uint8_t val;

	while (emx_ringbuf_size_4_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_4_3 + *emx_rd_pos_4_3);

	EMX_ATOMICWRITE(*emx_rd_pos_4_3, *emx_rd_pos_4_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_3, 0);
	}

	return val;
}

void EMX_Send16_4_3(uint16_t val) {
	while (emx_ringbuf_free_4_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_4_3 + *emx_wr_pos_4_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_3, *emx_wr_pos_4_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_3, 0);
	}
}

uint16_t EMX_Recv16_4_3() {
	uint16_t val;

	while (emx_ringbuf_size_4_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_4_3 + *emx_rd_pos_4_3);

	EMX_ATOMICWRITE(*emx_rd_pos_4_3, *emx_rd_pos_4_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_3, 0);
	}

	return val;
}

void EMX_Send32_4_3(uint32_t val) {
	while (emx_ringbuf_free_4_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_4_3 + *emx_wr_pos_4_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_3, *emx_wr_pos_4_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_3, 0);
	}
}

uint32_t EMX_Recv32_4_3() {
	uint32_t val;

	while (emx_ringbuf_size_4_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_4_3 + *emx_rd_pos_4_3);

	EMX_ATOMICWRITE(*emx_rd_pos_4_3, *emx_rd_pos_4_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_3, 0);
	}

	return val;
}

void EMX_Send64_4_3(uint64_t val) {
	while (emx_ringbuf_free_4_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_4_3 + *emx_wr_pos_4_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_3, *emx_wr_pos_4_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_3, 0);
	}
}

uint64_t EMX_Recv64_4_3() {
	uint64_t val;

	while (emx_ringbuf_size_4_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_4_3 + *emx_rd_pos_4_3);

	EMX_ATOMICWRITE(*emx_rd_pos_4_3, *emx_rd_pos_4_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_3, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_4_5;
volatile uint32_t* emx_rd_pos_4_5;
volatile uint8_t* emx_rb_buf_4_5;

void emx_send_array_4_5(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_4_5;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_4_5 + *emx_wr_pos_4_5), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_4_5, *emx_wr_pos_4_5 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_4_5 + *emx_wr_pos_4_5), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_4_5, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_4_5, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_4_5(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_4_5;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_4_5 + *emx_rd_pos_4_5), size);
		EMX_ATOMICWRITE(*emx_rd_pos_4_5, *emx_rd_pos_4_5 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_4_5 + *emx_rd_pos_4_5), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_4_5, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_4_5, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_4_5(uint8_t val) {
	while (emx_ringbuf_free_4_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_4_5 + *emx_wr_pos_4_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_5, *emx_wr_pos_4_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_5, 0);
	}
}

uint8_t EMX_Recv8_4_5() {
	uint8_t val;

	while (emx_ringbuf_size_4_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_4_5 + *emx_rd_pos_4_5);

	EMX_ATOMICWRITE(*emx_rd_pos_4_5, *emx_rd_pos_4_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_5, 0);
	}

	return val;
}

void EMX_Send16_4_5(uint16_t val) {
	while (emx_ringbuf_free_4_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_4_5 + *emx_wr_pos_4_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_5, *emx_wr_pos_4_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_5, 0);
	}
}

uint16_t EMX_Recv16_4_5() {
	uint16_t val;

	while (emx_ringbuf_size_4_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_4_5 + *emx_rd_pos_4_5);

	EMX_ATOMICWRITE(*emx_rd_pos_4_5, *emx_rd_pos_4_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_5, 0);
	}

	return val;
}

void EMX_Send32_4_5(uint32_t val) {
	while (emx_ringbuf_free_4_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_4_5 + *emx_wr_pos_4_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_5, *emx_wr_pos_4_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_5, 0);
	}
}

uint32_t EMX_Recv32_4_5() {
	uint32_t val;

	while (emx_ringbuf_size_4_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_4_5 + *emx_rd_pos_4_5);

	EMX_ATOMICWRITE(*emx_rd_pos_4_5, *emx_rd_pos_4_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_5, 0);
	}

	return val;
}

void EMX_Send64_4_5(uint64_t val) {
	while (emx_ringbuf_free_4_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_4_5 + *emx_wr_pos_4_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_5, *emx_wr_pos_4_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_5, 0);
	}
}

uint64_t EMX_Recv64_4_5() {
	uint64_t val;

	while (emx_ringbuf_size_4_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_4_5 + *emx_rd_pos_4_5);

	EMX_ATOMICWRITE(*emx_rd_pos_4_5, *emx_rd_pos_4_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_5, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_4_6;
volatile uint32_t* emx_rd_pos_4_6;
volatile uint8_t* emx_rb_buf_4_6;

void emx_send_array_4_6(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_4_6;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_4_6 + *emx_wr_pos_4_6), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_4_6, *emx_wr_pos_4_6 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_4_6 + *emx_wr_pos_4_6), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_4_6, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_4_6, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_4_6(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_4_6;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_4_6 + *emx_rd_pos_4_6), size);
		EMX_ATOMICWRITE(*emx_rd_pos_4_6, *emx_rd_pos_4_6 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_4_6 + *emx_rd_pos_4_6), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_4_6, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_4_6, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_4_6(uint8_t val) {
	while (emx_ringbuf_free_4_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_4_6 + *emx_wr_pos_4_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_6, *emx_wr_pos_4_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_6, 0);
	}
}

uint8_t EMX_Recv8_4_6() {
	uint8_t val;

	while (emx_ringbuf_size_4_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_4_6 + *emx_rd_pos_4_6);

	EMX_ATOMICWRITE(*emx_rd_pos_4_6, *emx_rd_pos_4_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_6, 0);
	}

	return val;
}

void EMX_Send16_4_6(uint16_t val) {
	while (emx_ringbuf_free_4_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_4_6 + *emx_wr_pos_4_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_6, *emx_wr_pos_4_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_6, 0);
	}
}

uint16_t EMX_Recv16_4_6() {
	uint16_t val;

	while (emx_ringbuf_size_4_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_4_6 + *emx_rd_pos_4_6);

	EMX_ATOMICWRITE(*emx_rd_pos_4_6, *emx_rd_pos_4_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_6, 0);
	}

	return val;
}

void EMX_Send32_4_6(uint32_t val) {
	while (emx_ringbuf_free_4_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_4_6 + *emx_wr_pos_4_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_6, *emx_wr_pos_4_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_6, 0);
	}
}

uint32_t EMX_Recv32_4_6() {
	uint32_t val;

	while (emx_ringbuf_size_4_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_4_6 + *emx_rd_pos_4_6);

	EMX_ATOMICWRITE(*emx_rd_pos_4_6, *emx_rd_pos_4_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_6, 0);
	}

	return val;
}

void EMX_Send64_4_6(uint64_t val) {
	while (emx_ringbuf_free_4_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_4_6 + *emx_wr_pos_4_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_6, *emx_wr_pos_4_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_6, 0);
	}
}

uint64_t EMX_Recv64_4_6() {
	uint64_t val;

	while (emx_ringbuf_size_4_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_4_6 + *emx_rd_pos_4_6);

	EMX_ATOMICWRITE(*emx_rd_pos_4_6, *emx_rd_pos_4_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_6, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_4_7;
volatile uint32_t* emx_rd_pos_4_7;
volatile uint8_t* emx_rb_buf_4_7;

void emx_send_array_4_7(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_4_7;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_4_7 + *emx_wr_pos_4_7), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_4_7, *emx_wr_pos_4_7 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_4_7 + *emx_wr_pos_4_7), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_4_7, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_4_7, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_4_7(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_4_7;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_4_7 + *emx_rd_pos_4_7), size);
		EMX_ATOMICWRITE(*emx_rd_pos_4_7, *emx_rd_pos_4_7 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_4_7 + *emx_rd_pos_4_7), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_4_7, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_4_7, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_4_7(uint8_t val) {
	while (emx_ringbuf_free_4_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_4_7 + *emx_wr_pos_4_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_7, *emx_wr_pos_4_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_7, 0);
	}
}

uint8_t EMX_Recv8_4_7() {
	uint8_t val;

	while (emx_ringbuf_size_4_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_4_7 + *emx_rd_pos_4_7);

	EMX_ATOMICWRITE(*emx_rd_pos_4_7, *emx_rd_pos_4_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_7, 0);
	}

	return val;
}

void EMX_Send16_4_7(uint16_t val) {
	while (emx_ringbuf_free_4_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_4_7 + *emx_wr_pos_4_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_7, *emx_wr_pos_4_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_7, 0);
	}
}

uint16_t EMX_Recv16_4_7() {
	uint16_t val;

	while (emx_ringbuf_size_4_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_4_7 + *emx_rd_pos_4_7);

	EMX_ATOMICWRITE(*emx_rd_pos_4_7, *emx_rd_pos_4_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_7, 0);
	}

	return val;
}

void EMX_Send32_4_7(uint32_t val) {
	while (emx_ringbuf_free_4_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_4_7 + *emx_wr_pos_4_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_7, *emx_wr_pos_4_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_7, 0);
	}
}

uint32_t EMX_Recv32_4_7() {
	uint32_t val;

	while (emx_ringbuf_size_4_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_4_7 + *emx_rd_pos_4_7);

	EMX_ATOMICWRITE(*emx_rd_pos_4_7, *emx_rd_pos_4_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_7, 0);
	}

	return val;
}

void EMX_Send64_4_7(uint64_t val) {
	while (emx_ringbuf_free_4_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_4_7 + *emx_wr_pos_4_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_4_7, *emx_wr_pos_4_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_4_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_4_7, 0);
	}
}

uint64_t EMX_Recv64_4_7() {
	uint64_t val;

	while (emx_ringbuf_size_4_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_4_7 + *emx_rd_pos_4_7);

	EMX_ATOMICWRITE(*emx_rd_pos_4_7, *emx_rd_pos_4_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_4_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_4_7, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_5_0;
volatile uint32_t* emx_rd_pos_5_0;
volatile uint8_t* emx_rb_buf_5_0;

void emx_send_array_5_0(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_5_0;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_5_0 + *emx_wr_pos_5_0), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_5_0, *emx_wr_pos_5_0 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_5_0 + *emx_wr_pos_5_0), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_5_0, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_5_0, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_5_0(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_5_0;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_5_0 + *emx_rd_pos_5_0), size);
		EMX_ATOMICWRITE(*emx_rd_pos_5_0, *emx_rd_pos_5_0 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_5_0 + *emx_rd_pos_5_0), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_5_0, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_5_0, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_5_0(uint8_t val) {
	while (emx_ringbuf_free_5_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_5_0 + *emx_wr_pos_5_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_0, *emx_wr_pos_5_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_0, 0);
	}
}

uint8_t EMX_Recv8_5_0() {
	uint8_t val;

	while (emx_ringbuf_size_5_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_5_0 + *emx_rd_pos_5_0);

	EMX_ATOMICWRITE(*emx_rd_pos_5_0, *emx_rd_pos_5_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_0, 0);
	}

	return val;
}

void EMX_Send16_5_0(uint16_t val) {
	while (emx_ringbuf_free_5_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_5_0 + *emx_wr_pos_5_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_0, *emx_wr_pos_5_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_0, 0);
	}
}

uint16_t EMX_Recv16_5_0() {
	uint16_t val;

	while (emx_ringbuf_size_5_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_5_0 + *emx_rd_pos_5_0);

	EMX_ATOMICWRITE(*emx_rd_pos_5_0, *emx_rd_pos_5_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_0, 0);
	}

	return val;
}

void EMX_Send32_5_0(uint32_t val) {
	while (emx_ringbuf_free_5_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_5_0 + *emx_wr_pos_5_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_0, *emx_wr_pos_5_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_0, 0);
	}
}

uint32_t EMX_Recv32_5_0() {
	uint32_t val;

	while (emx_ringbuf_size_5_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_5_0 + *emx_rd_pos_5_0);

	EMX_ATOMICWRITE(*emx_rd_pos_5_0, *emx_rd_pos_5_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_0, 0);
	}

	return val;
}

void EMX_Send64_5_0(uint64_t val) {
	while (emx_ringbuf_free_5_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_5_0 + *emx_wr_pos_5_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_0, *emx_wr_pos_5_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_0, 0);
	}
}

uint64_t EMX_Recv64_5_0() {
	uint64_t val;

	while (emx_ringbuf_size_5_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_5_0 + *emx_rd_pos_5_0);

	EMX_ATOMICWRITE(*emx_rd_pos_5_0, *emx_rd_pos_5_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_0, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_5_1;
volatile uint32_t* emx_rd_pos_5_1;
volatile uint8_t* emx_rb_buf_5_1;

void emx_send_array_5_1(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_5_1;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_5_1 + *emx_wr_pos_5_1), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_5_1, *emx_wr_pos_5_1 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_5_1 + *emx_wr_pos_5_1), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_5_1, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_5_1, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_5_1(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_5_1;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_5_1 + *emx_rd_pos_5_1), size);
		EMX_ATOMICWRITE(*emx_rd_pos_5_1, *emx_rd_pos_5_1 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_5_1 + *emx_rd_pos_5_1), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_5_1, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_5_1, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_5_1(uint8_t val) {
	while (emx_ringbuf_free_5_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_5_1 + *emx_wr_pos_5_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_1, *emx_wr_pos_5_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_1, 0);
	}
}

uint8_t EMX_Recv8_5_1() {
	uint8_t val;

	while (emx_ringbuf_size_5_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_5_1 + *emx_rd_pos_5_1);

	EMX_ATOMICWRITE(*emx_rd_pos_5_1, *emx_rd_pos_5_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_1, 0);
	}

	return val;
}

void EMX_Send16_5_1(uint16_t val) {
	while (emx_ringbuf_free_5_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_5_1 + *emx_wr_pos_5_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_1, *emx_wr_pos_5_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_1, 0);
	}
}

uint16_t EMX_Recv16_5_1() {
	uint16_t val;

	while (emx_ringbuf_size_5_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_5_1 + *emx_rd_pos_5_1);

	EMX_ATOMICWRITE(*emx_rd_pos_5_1, *emx_rd_pos_5_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_1, 0);
	}

	return val;
}

void EMX_Send32_5_1(uint32_t val) {
	while (emx_ringbuf_free_5_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_5_1 + *emx_wr_pos_5_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_1, *emx_wr_pos_5_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_1, 0);
	}
}

uint32_t EMX_Recv32_5_1() {
	uint32_t val;

	while (emx_ringbuf_size_5_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_5_1 + *emx_rd_pos_5_1);

	EMX_ATOMICWRITE(*emx_rd_pos_5_1, *emx_rd_pos_5_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_1, 0);
	}

	return val;
}

void EMX_Send64_5_1(uint64_t val) {
	while (emx_ringbuf_free_5_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_5_1 + *emx_wr_pos_5_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_1, *emx_wr_pos_5_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_1, 0);
	}
}

uint64_t EMX_Recv64_5_1() {
	uint64_t val;

	while (emx_ringbuf_size_5_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_5_1 + *emx_rd_pos_5_1);

	EMX_ATOMICWRITE(*emx_rd_pos_5_1, *emx_rd_pos_5_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_1, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_5_2;
volatile uint32_t* emx_rd_pos_5_2;
volatile uint8_t* emx_rb_buf_5_2;

void emx_send_array_5_2(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_5_2;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_5_2 + *emx_wr_pos_5_2), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_5_2, *emx_wr_pos_5_2 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_5_2 + *emx_wr_pos_5_2), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_5_2, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_5_2, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_5_2(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_5_2;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_5_2 + *emx_rd_pos_5_2), size);
		EMX_ATOMICWRITE(*emx_rd_pos_5_2, *emx_rd_pos_5_2 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_5_2 + *emx_rd_pos_5_2), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_5_2, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_5_2, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_5_2(uint8_t val) {
	while (emx_ringbuf_free_5_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_5_2 + *emx_wr_pos_5_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_2, *emx_wr_pos_5_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_2, 0);
	}
}

uint8_t EMX_Recv8_5_2() {
	uint8_t val;

	while (emx_ringbuf_size_5_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_5_2 + *emx_rd_pos_5_2);

	EMX_ATOMICWRITE(*emx_rd_pos_5_2, *emx_rd_pos_5_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_2, 0);
	}

	return val;
}

void EMX_Send16_5_2(uint16_t val) {
	while (emx_ringbuf_free_5_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_5_2 + *emx_wr_pos_5_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_2, *emx_wr_pos_5_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_2, 0);
	}
}

uint16_t EMX_Recv16_5_2() {
	uint16_t val;

	while (emx_ringbuf_size_5_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_5_2 + *emx_rd_pos_5_2);

	EMX_ATOMICWRITE(*emx_rd_pos_5_2, *emx_rd_pos_5_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_2, 0);
	}

	return val;
}

void EMX_Send32_5_2(uint32_t val) {
	while (emx_ringbuf_free_5_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_5_2 + *emx_wr_pos_5_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_2, *emx_wr_pos_5_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_2, 0);
	}
}

uint32_t EMX_Recv32_5_2() {
	uint32_t val;

	while (emx_ringbuf_size_5_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_5_2 + *emx_rd_pos_5_2);

	EMX_ATOMICWRITE(*emx_rd_pos_5_2, *emx_rd_pos_5_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_2, 0);
	}

	return val;
}

void EMX_Send64_5_2(uint64_t val) {
	while (emx_ringbuf_free_5_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_5_2 + *emx_wr_pos_5_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_2, *emx_wr_pos_5_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_2, 0);
	}
}

uint64_t EMX_Recv64_5_2() {
	uint64_t val;

	while (emx_ringbuf_size_5_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_5_2 + *emx_rd_pos_5_2);

	EMX_ATOMICWRITE(*emx_rd_pos_5_2, *emx_rd_pos_5_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_2, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_5_3;
volatile uint32_t* emx_rd_pos_5_3;
volatile uint8_t* emx_rb_buf_5_3;

void emx_send_array_5_3(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_5_3;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_5_3 + *emx_wr_pos_5_3), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_5_3, *emx_wr_pos_5_3 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_5_3 + *emx_wr_pos_5_3), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_5_3, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_5_3, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_5_3(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_5_3;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_5_3 + *emx_rd_pos_5_3), size);
		EMX_ATOMICWRITE(*emx_rd_pos_5_3, *emx_rd_pos_5_3 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_5_3 + *emx_rd_pos_5_3), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_5_3, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_5_3, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_5_3(uint8_t val) {
	while (emx_ringbuf_free_5_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_5_3 + *emx_wr_pos_5_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_3, *emx_wr_pos_5_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_3, 0);
	}
}

uint8_t EMX_Recv8_5_3() {
	uint8_t val;

	while (emx_ringbuf_size_5_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_5_3 + *emx_rd_pos_5_3);

	EMX_ATOMICWRITE(*emx_rd_pos_5_3, *emx_rd_pos_5_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_3, 0);
	}

	return val;
}

void EMX_Send16_5_3(uint16_t val) {
	while (emx_ringbuf_free_5_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_5_3 + *emx_wr_pos_5_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_3, *emx_wr_pos_5_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_3, 0);
	}
}

uint16_t EMX_Recv16_5_3() {
	uint16_t val;

	while (emx_ringbuf_size_5_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_5_3 + *emx_rd_pos_5_3);

	EMX_ATOMICWRITE(*emx_rd_pos_5_3, *emx_rd_pos_5_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_3, 0);
	}

	return val;
}

void EMX_Send32_5_3(uint32_t val) {
	while (emx_ringbuf_free_5_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_5_3 + *emx_wr_pos_5_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_3, *emx_wr_pos_5_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_3, 0);
	}
}

uint32_t EMX_Recv32_5_3() {
	uint32_t val;

	while (emx_ringbuf_size_5_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_5_3 + *emx_rd_pos_5_3);

	EMX_ATOMICWRITE(*emx_rd_pos_5_3, *emx_rd_pos_5_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_3, 0);
	}

	return val;
}

void EMX_Send64_5_3(uint64_t val) {
	while (emx_ringbuf_free_5_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_5_3 + *emx_wr_pos_5_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_3, *emx_wr_pos_5_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_3, 0);
	}
}

uint64_t EMX_Recv64_5_3() {
	uint64_t val;

	while (emx_ringbuf_size_5_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_5_3 + *emx_rd_pos_5_3);

	EMX_ATOMICWRITE(*emx_rd_pos_5_3, *emx_rd_pos_5_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_3, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_5_4;
volatile uint32_t* emx_rd_pos_5_4;
volatile uint8_t* emx_rb_buf_5_4;

void emx_send_array_5_4(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_5_4;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_5_4 + *emx_wr_pos_5_4), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_5_4, *emx_wr_pos_5_4 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_5_4 + *emx_wr_pos_5_4), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_5_4, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_5_4, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_5_4(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_5_4;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_5_4 + *emx_rd_pos_5_4), size);
		EMX_ATOMICWRITE(*emx_rd_pos_5_4, *emx_rd_pos_5_4 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_5_4 + *emx_rd_pos_5_4), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_5_4, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_5_4, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_5_4(uint8_t val) {
	while (emx_ringbuf_free_5_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_5_4 + *emx_wr_pos_5_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_4, *emx_wr_pos_5_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_4, 0);
	}
}

uint8_t EMX_Recv8_5_4() {
	uint8_t val;

	while (emx_ringbuf_size_5_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_5_4 + *emx_rd_pos_5_4);

	EMX_ATOMICWRITE(*emx_rd_pos_5_4, *emx_rd_pos_5_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_4, 0);
	}

	return val;
}

void EMX_Send16_5_4(uint16_t val) {
	while (emx_ringbuf_free_5_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_5_4 + *emx_wr_pos_5_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_4, *emx_wr_pos_5_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_4, 0);
	}
}

uint16_t EMX_Recv16_5_4() {
	uint16_t val;

	while (emx_ringbuf_size_5_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_5_4 + *emx_rd_pos_5_4);

	EMX_ATOMICWRITE(*emx_rd_pos_5_4, *emx_rd_pos_5_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_4, 0);
	}

	return val;
}

void EMX_Send32_5_4(uint32_t val) {
	while (emx_ringbuf_free_5_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_5_4 + *emx_wr_pos_5_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_4, *emx_wr_pos_5_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_4, 0);
	}
}

uint32_t EMX_Recv32_5_4() {
	uint32_t val;

	while (emx_ringbuf_size_5_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_5_4 + *emx_rd_pos_5_4);

	EMX_ATOMICWRITE(*emx_rd_pos_5_4, *emx_rd_pos_5_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_4, 0);
	}

	return val;
}

void EMX_Send64_5_4(uint64_t val) {
	while (emx_ringbuf_free_5_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_5_4 + *emx_wr_pos_5_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_4, *emx_wr_pos_5_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_4, 0);
	}
}

uint64_t EMX_Recv64_5_4() {
	uint64_t val;

	while (emx_ringbuf_size_5_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_5_4 + *emx_rd_pos_5_4);

	EMX_ATOMICWRITE(*emx_rd_pos_5_4, *emx_rd_pos_5_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_4, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_5_6;
volatile uint32_t* emx_rd_pos_5_6;
volatile uint8_t* emx_rb_buf_5_6;

void emx_send_array_5_6(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_5_6;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_5_6 + *emx_wr_pos_5_6), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_5_6, *emx_wr_pos_5_6 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_5_6 + *emx_wr_pos_5_6), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_5_6, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_5_6, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_5_6(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_5_6;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_5_6 + *emx_rd_pos_5_6), size);
		EMX_ATOMICWRITE(*emx_rd_pos_5_6, *emx_rd_pos_5_6 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_5_6 + *emx_rd_pos_5_6), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_5_6, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_5_6, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_5_6(uint8_t val) {
	while (emx_ringbuf_free_5_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_5_6 + *emx_wr_pos_5_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_6, *emx_wr_pos_5_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_6, 0);
	}
}

uint8_t EMX_Recv8_5_6() {
	uint8_t val;

	while (emx_ringbuf_size_5_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_5_6 + *emx_rd_pos_5_6);

	EMX_ATOMICWRITE(*emx_rd_pos_5_6, *emx_rd_pos_5_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_6, 0);
	}

	return val;
}

void EMX_Send16_5_6(uint16_t val) {
	while (emx_ringbuf_free_5_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_5_6 + *emx_wr_pos_5_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_6, *emx_wr_pos_5_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_6, 0);
	}
}

uint16_t EMX_Recv16_5_6() {
	uint16_t val;

	while (emx_ringbuf_size_5_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_5_6 + *emx_rd_pos_5_6);

	EMX_ATOMICWRITE(*emx_rd_pos_5_6, *emx_rd_pos_5_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_6, 0);
	}

	return val;
}

void EMX_Send32_5_6(uint32_t val) {
	while (emx_ringbuf_free_5_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_5_6 + *emx_wr_pos_5_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_6, *emx_wr_pos_5_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_6, 0);
	}
}

uint32_t EMX_Recv32_5_6() {
	uint32_t val;

	while (emx_ringbuf_size_5_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_5_6 + *emx_rd_pos_5_6);

	EMX_ATOMICWRITE(*emx_rd_pos_5_6, *emx_rd_pos_5_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_6, 0);
	}

	return val;
}

void EMX_Send64_5_6(uint64_t val) {
	while (emx_ringbuf_free_5_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_5_6 + *emx_wr_pos_5_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_6, *emx_wr_pos_5_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_6, 0);
	}
}

uint64_t EMX_Recv64_5_6() {
	uint64_t val;

	while (emx_ringbuf_size_5_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_5_6 + *emx_rd_pos_5_6);

	EMX_ATOMICWRITE(*emx_rd_pos_5_6, *emx_rd_pos_5_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_6, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_5_7;
volatile uint32_t* emx_rd_pos_5_7;
volatile uint8_t* emx_rb_buf_5_7;

void emx_send_array_5_7(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_5_7;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_5_7 + *emx_wr_pos_5_7), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_5_7, *emx_wr_pos_5_7 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_5_7 + *emx_wr_pos_5_7), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_5_7, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_5_7, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_5_7(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_5_7;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_5_7 + *emx_rd_pos_5_7), size);
		EMX_ATOMICWRITE(*emx_rd_pos_5_7, *emx_rd_pos_5_7 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_5_7 + *emx_rd_pos_5_7), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_5_7, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_5_7, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_5_7(uint8_t val) {
	while (emx_ringbuf_free_5_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_5_7 + *emx_wr_pos_5_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_7, *emx_wr_pos_5_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_7, 0);
	}
}

uint8_t EMX_Recv8_5_7() {
	uint8_t val;

	while (emx_ringbuf_size_5_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_5_7 + *emx_rd_pos_5_7);

	EMX_ATOMICWRITE(*emx_rd_pos_5_7, *emx_rd_pos_5_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_7, 0);
	}

	return val;
}

void EMX_Send16_5_7(uint16_t val) {
	while (emx_ringbuf_free_5_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_5_7 + *emx_wr_pos_5_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_7, *emx_wr_pos_5_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_7, 0);
	}
}

uint16_t EMX_Recv16_5_7() {
	uint16_t val;

	while (emx_ringbuf_size_5_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_5_7 + *emx_rd_pos_5_7);

	EMX_ATOMICWRITE(*emx_rd_pos_5_7, *emx_rd_pos_5_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_7, 0);
	}

	return val;
}

void EMX_Send32_5_7(uint32_t val) {
	while (emx_ringbuf_free_5_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_5_7 + *emx_wr_pos_5_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_7, *emx_wr_pos_5_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_7, 0);
	}
}

uint32_t EMX_Recv32_5_7() {
	uint32_t val;

	while (emx_ringbuf_size_5_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_5_7 + *emx_rd_pos_5_7);

	EMX_ATOMICWRITE(*emx_rd_pos_5_7, *emx_rd_pos_5_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_7, 0);
	}

	return val;
}

void EMX_Send64_5_7(uint64_t val) {
	while (emx_ringbuf_free_5_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_5_7 + *emx_wr_pos_5_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_5_7, *emx_wr_pos_5_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_5_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_5_7, 0);
	}
}

uint64_t EMX_Recv64_5_7() {
	uint64_t val;

	while (emx_ringbuf_size_5_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_5_7 + *emx_rd_pos_5_7);

	EMX_ATOMICWRITE(*emx_rd_pos_5_7, *emx_rd_pos_5_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_5_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_5_7, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_6_0;
volatile uint32_t* emx_rd_pos_6_0;
volatile uint8_t* emx_rb_buf_6_0;

void emx_send_array_6_0(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_6_0;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_6_0 + *emx_wr_pos_6_0), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_6_0, *emx_wr_pos_6_0 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_6_0 + *emx_wr_pos_6_0), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_6_0, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_6_0, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_6_0(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_6_0;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_6_0 + *emx_rd_pos_6_0), size);
		EMX_ATOMICWRITE(*emx_rd_pos_6_0, *emx_rd_pos_6_0 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_6_0 + *emx_rd_pos_6_0), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_6_0, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_6_0, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_6_0(uint8_t val) {
	while (emx_ringbuf_free_6_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_6_0 + *emx_wr_pos_6_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_0, *emx_wr_pos_6_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_0, 0);
	}
}

uint8_t EMX_Recv8_6_0() {
	uint8_t val;

	while (emx_ringbuf_size_6_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_6_0 + *emx_rd_pos_6_0);

	EMX_ATOMICWRITE(*emx_rd_pos_6_0, *emx_rd_pos_6_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_0, 0);
	}

	return val;
}

void EMX_Send16_6_0(uint16_t val) {
	while (emx_ringbuf_free_6_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_6_0 + *emx_wr_pos_6_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_0, *emx_wr_pos_6_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_0, 0);
	}
}

uint16_t EMX_Recv16_6_0() {
	uint16_t val;

	while (emx_ringbuf_size_6_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_6_0 + *emx_rd_pos_6_0);

	EMX_ATOMICWRITE(*emx_rd_pos_6_0, *emx_rd_pos_6_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_0, 0);
	}

	return val;
}

void EMX_Send32_6_0(uint32_t val) {
	while (emx_ringbuf_free_6_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_6_0 + *emx_wr_pos_6_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_0, *emx_wr_pos_6_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_0, 0);
	}
}

uint32_t EMX_Recv32_6_0() {
	uint32_t val;

	while (emx_ringbuf_size_6_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_6_0 + *emx_rd_pos_6_0);

	EMX_ATOMICWRITE(*emx_rd_pos_6_0, *emx_rd_pos_6_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_0, 0);
	}

	return val;
}

void EMX_Send64_6_0(uint64_t val) {
	while (emx_ringbuf_free_6_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_6_0 + *emx_wr_pos_6_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_0, *emx_wr_pos_6_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_0, 0);
	}
}

uint64_t EMX_Recv64_6_0() {
	uint64_t val;

	while (emx_ringbuf_size_6_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_6_0 + *emx_rd_pos_6_0);

	EMX_ATOMICWRITE(*emx_rd_pos_6_0, *emx_rd_pos_6_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_0, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_6_1;
volatile uint32_t* emx_rd_pos_6_1;
volatile uint8_t* emx_rb_buf_6_1;

void emx_send_array_6_1(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_6_1;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_6_1 + *emx_wr_pos_6_1), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_6_1, *emx_wr_pos_6_1 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_6_1 + *emx_wr_pos_6_1), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_6_1, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_6_1, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_6_1(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_6_1;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_6_1 + *emx_rd_pos_6_1), size);
		EMX_ATOMICWRITE(*emx_rd_pos_6_1, *emx_rd_pos_6_1 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_6_1 + *emx_rd_pos_6_1), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_6_1, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_6_1, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_6_1(uint8_t val) {
	while (emx_ringbuf_free_6_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_6_1 + *emx_wr_pos_6_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_1, *emx_wr_pos_6_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_1, 0);
	}
}

uint8_t EMX_Recv8_6_1() {
	uint8_t val;

	while (emx_ringbuf_size_6_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_6_1 + *emx_rd_pos_6_1);

	EMX_ATOMICWRITE(*emx_rd_pos_6_1, *emx_rd_pos_6_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_1, 0);
	}

	return val;
}

void EMX_Send16_6_1(uint16_t val) {
	while (emx_ringbuf_free_6_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_6_1 + *emx_wr_pos_6_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_1, *emx_wr_pos_6_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_1, 0);
	}
}

uint16_t EMX_Recv16_6_1() {
	uint16_t val;

	while (emx_ringbuf_size_6_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_6_1 + *emx_rd_pos_6_1);

	EMX_ATOMICWRITE(*emx_rd_pos_6_1, *emx_rd_pos_6_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_1, 0);
	}

	return val;
}

void EMX_Send32_6_1(uint32_t val) {
	while (emx_ringbuf_free_6_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_6_1 + *emx_wr_pos_6_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_1, *emx_wr_pos_6_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_1, 0);
	}
}

uint32_t EMX_Recv32_6_1() {
	uint32_t val;

	while (emx_ringbuf_size_6_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_6_1 + *emx_rd_pos_6_1);

	EMX_ATOMICWRITE(*emx_rd_pos_6_1, *emx_rd_pos_6_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_1, 0);
	}

	return val;
}

void EMX_Send64_6_1(uint64_t val) {
	while (emx_ringbuf_free_6_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_6_1 + *emx_wr_pos_6_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_1, *emx_wr_pos_6_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_1, 0);
	}
}

uint64_t EMX_Recv64_6_1() {
	uint64_t val;

	while (emx_ringbuf_size_6_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_6_1 + *emx_rd_pos_6_1);

	EMX_ATOMICWRITE(*emx_rd_pos_6_1, *emx_rd_pos_6_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_1, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_6_2;
volatile uint32_t* emx_rd_pos_6_2;
volatile uint8_t* emx_rb_buf_6_2;

void emx_send_array_6_2(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_6_2;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_6_2 + *emx_wr_pos_6_2), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_6_2, *emx_wr_pos_6_2 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_6_2 + *emx_wr_pos_6_2), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_6_2, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_6_2, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_6_2(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_6_2;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_6_2 + *emx_rd_pos_6_2), size);
		EMX_ATOMICWRITE(*emx_rd_pos_6_2, *emx_rd_pos_6_2 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_6_2 + *emx_rd_pos_6_2), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_6_2, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_6_2, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_6_2(uint8_t val) {
	while (emx_ringbuf_free_6_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_6_2 + *emx_wr_pos_6_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_2, *emx_wr_pos_6_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_2, 0);
	}
}

uint8_t EMX_Recv8_6_2() {
	uint8_t val;

	while (emx_ringbuf_size_6_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_6_2 + *emx_rd_pos_6_2);

	EMX_ATOMICWRITE(*emx_rd_pos_6_2, *emx_rd_pos_6_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_2, 0);
	}

	return val;
}

void EMX_Send16_6_2(uint16_t val) {
	while (emx_ringbuf_free_6_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_6_2 + *emx_wr_pos_6_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_2, *emx_wr_pos_6_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_2, 0);
	}
}

uint16_t EMX_Recv16_6_2() {
	uint16_t val;

	while (emx_ringbuf_size_6_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_6_2 + *emx_rd_pos_6_2);

	EMX_ATOMICWRITE(*emx_rd_pos_6_2, *emx_rd_pos_6_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_2, 0);
	}

	return val;
}

void EMX_Send32_6_2(uint32_t val) {
	while (emx_ringbuf_free_6_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_6_2 + *emx_wr_pos_6_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_2, *emx_wr_pos_6_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_2, 0);
	}
}

uint32_t EMX_Recv32_6_2() {
	uint32_t val;

	while (emx_ringbuf_size_6_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_6_2 + *emx_rd_pos_6_2);

	EMX_ATOMICWRITE(*emx_rd_pos_6_2, *emx_rd_pos_6_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_2, 0);
	}

	return val;
}

void EMX_Send64_6_2(uint64_t val) {
	while (emx_ringbuf_free_6_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_6_2 + *emx_wr_pos_6_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_2, *emx_wr_pos_6_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_2, 0);
	}
}

uint64_t EMX_Recv64_6_2() {
	uint64_t val;

	while (emx_ringbuf_size_6_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_6_2 + *emx_rd_pos_6_2);

	EMX_ATOMICWRITE(*emx_rd_pos_6_2, *emx_rd_pos_6_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_2, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_6_3;
volatile uint32_t* emx_rd_pos_6_3;
volatile uint8_t* emx_rb_buf_6_3;

void emx_send_array_6_3(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_6_3;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_6_3 + *emx_wr_pos_6_3), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_6_3, *emx_wr_pos_6_3 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_6_3 + *emx_wr_pos_6_3), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_6_3, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_6_3, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_6_3(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_6_3;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_6_3 + *emx_rd_pos_6_3), size);
		EMX_ATOMICWRITE(*emx_rd_pos_6_3, *emx_rd_pos_6_3 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_6_3 + *emx_rd_pos_6_3), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_6_3, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_6_3, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_6_3(uint8_t val) {
	while (emx_ringbuf_free_6_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_6_3 + *emx_wr_pos_6_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_3, *emx_wr_pos_6_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_3, 0);
	}
}

uint8_t EMX_Recv8_6_3() {
	uint8_t val;

	while (emx_ringbuf_size_6_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_6_3 + *emx_rd_pos_6_3);

	EMX_ATOMICWRITE(*emx_rd_pos_6_3, *emx_rd_pos_6_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_3, 0);
	}

	return val;
}

void EMX_Send16_6_3(uint16_t val) {
	while (emx_ringbuf_free_6_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_6_3 + *emx_wr_pos_6_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_3, *emx_wr_pos_6_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_3, 0);
	}
}

uint16_t EMX_Recv16_6_3() {
	uint16_t val;

	while (emx_ringbuf_size_6_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_6_3 + *emx_rd_pos_6_3);

	EMX_ATOMICWRITE(*emx_rd_pos_6_3, *emx_rd_pos_6_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_3, 0);
	}

	return val;
}

void EMX_Send32_6_3(uint32_t val) {
	while (emx_ringbuf_free_6_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_6_3 + *emx_wr_pos_6_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_3, *emx_wr_pos_6_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_3, 0);
	}
}

uint32_t EMX_Recv32_6_3() {
	uint32_t val;

	while (emx_ringbuf_size_6_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_6_3 + *emx_rd_pos_6_3);

	EMX_ATOMICWRITE(*emx_rd_pos_6_3, *emx_rd_pos_6_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_3, 0);
	}

	return val;
}

void EMX_Send64_6_3(uint64_t val) {
	while (emx_ringbuf_free_6_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_6_3 + *emx_wr_pos_6_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_3, *emx_wr_pos_6_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_3, 0);
	}
}

uint64_t EMX_Recv64_6_3() {
	uint64_t val;

	while (emx_ringbuf_size_6_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_6_3 + *emx_rd_pos_6_3);

	EMX_ATOMICWRITE(*emx_rd_pos_6_3, *emx_rd_pos_6_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_3, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_6_4;
volatile uint32_t* emx_rd_pos_6_4;
volatile uint8_t* emx_rb_buf_6_4;

void emx_send_array_6_4(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_6_4;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_6_4 + *emx_wr_pos_6_4), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_6_4, *emx_wr_pos_6_4 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_6_4 + *emx_wr_pos_6_4), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_6_4, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_6_4, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_6_4(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_6_4;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_6_4 + *emx_rd_pos_6_4), size);
		EMX_ATOMICWRITE(*emx_rd_pos_6_4, *emx_rd_pos_6_4 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_6_4 + *emx_rd_pos_6_4), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_6_4, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_6_4, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_6_4(uint8_t val) {
	while (emx_ringbuf_free_6_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_6_4 + *emx_wr_pos_6_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_4, *emx_wr_pos_6_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_4, 0);
	}
}

uint8_t EMX_Recv8_6_4() {
	uint8_t val;

	while (emx_ringbuf_size_6_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_6_4 + *emx_rd_pos_6_4);

	EMX_ATOMICWRITE(*emx_rd_pos_6_4, *emx_rd_pos_6_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_4, 0);
	}

	return val;
}

void EMX_Send16_6_4(uint16_t val) {
	while (emx_ringbuf_free_6_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_6_4 + *emx_wr_pos_6_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_4, *emx_wr_pos_6_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_4, 0);
	}
}

uint16_t EMX_Recv16_6_4() {
	uint16_t val;

	while (emx_ringbuf_size_6_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_6_4 + *emx_rd_pos_6_4);

	EMX_ATOMICWRITE(*emx_rd_pos_6_4, *emx_rd_pos_6_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_4, 0);
	}

	return val;
}

void EMX_Send32_6_4(uint32_t val) {
	while (emx_ringbuf_free_6_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_6_4 + *emx_wr_pos_6_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_4, *emx_wr_pos_6_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_4, 0);
	}
}

uint32_t EMX_Recv32_6_4() {
	uint32_t val;

	while (emx_ringbuf_size_6_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_6_4 + *emx_rd_pos_6_4);

	EMX_ATOMICWRITE(*emx_rd_pos_6_4, *emx_rd_pos_6_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_4, 0);
	}

	return val;
}

void EMX_Send64_6_4(uint64_t val) {
	while (emx_ringbuf_free_6_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_6_4 + *emx_wr_pos_6_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_4, *emx_wr_pos_6_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_4, 0);
	}
}

uint64_t EMX_Recv64_6_4() {
	uint64_t val;

	while (emx_ringbuf_size_6_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_6_4 + *emx_rd_pos_6_4);

	EMX_ATOMICWRITE(*emx_rd_pos_6_4, *emx_rd_pos_6_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_4, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_6_5;
volatile uint32_t* emx_rd_pos_6_5;
volatile uint8_t* emx_rb_buf_6_5;

void emx_send_array_6_5(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_6_5;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_6_5 + *emx_wr_pos_6_5), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_6_5, *emx_wr_pos_6_5 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_6_5 + *emx_wr_pos_6_5), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_6_5, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_6_5, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_6_5(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_6_5;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_6_5 + *emx_rd_pos_6_5), size);
		EMX_ATOMICWRITE(*emx_rd_pos_6_5, *emx_rd_pos_6_5 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_6_5 + *emx_rd_pos_6_5), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_6_5, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_6_5, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_6_5(uint8_t val) {
	while (emx_ringbuf_free_6_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_6_5 + *emx_wr_pos_6_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_5, *emx_wr_pos_6_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_5, 0);
	}
}

uint8_t EMX_Recv8_6_5() {
	uint8_t val;

	while (emx_ringbuf_size_6_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_6_5 + *emx_rd_pos_6_5);

	EMX_ATOMICWRITE(*emx_rd_pos_6_5, *emx_rd_pos_6_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_5, 0);
	}

	return val;
}

void EMX_Send16_6_5(uint16_t val) {
	while (emx_ringbuf_free_6_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_6_5 + *emx_wr_pos_6_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_5, *emx_wr_pos_6_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_5, 0);
	}
}

uint16_t EMX_Recv16_6_5() {
	uint16_t val;

	while (emx_ringbuf_size_6_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_6_5 + *emx_rd_pos_6_5);

	EMX_ATOMICWRITE(*emx_rd_pos_6_5, *emx_rd_pos_6_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_5, 0);
	}

	return val;
}

void EMX_Send32_6_5(uint32_t val) {
	while (emx_ringbuf_free_6_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_6_5 + *emx_wr_pos_6_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_5, *emx_wr_pos_6_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_5, 0);
	}
}

uint32_t EMX_Recv32_6_5() {
	uint32_t val;

	while (emx_ringbuf_size_6_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_6_5 + *emx_rd_pos_6_5);

	EMX_ATOMICWRITE(*emx_rd_pos_6_5, *emx_rd_pos_6_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_5, 0);
	}

	return val;
}

void EMX_Send64_6_5(uint64_t val) {
	while (emx_ringbuf_free_6_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_6_5 + *emx_wr_pos_6_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_5, *emx_wr_pos_6_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_5, 0);
	}
}

uint64_t EMX_Recv64_6_5() {
	uint64_t val;

	while (emx_ringbuf_size_6_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_6_5 + *emx_rd_pos_6_5);

	EMX_ATOMICWRITE(*emx_rd_pos_6_5, *emx_rd_pos_6_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_5, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_6_7;
volatile uint32_t* emx_rd_pos_6_7;
volatile uint8_t* emx_rb_buf_6_7;

void emx_send_array_6_7(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_6_7;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_6_7 + *emx_wr_pos_6_7), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_6_7, *emx_wr_pos_6_7 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_6_7 + *emx_wr_pos_6_7), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_6_7, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_6_7, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_6_7(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_6_7;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_6_7 + *emx_rd_pos_6_7), size);
		EMX_ATOMICWRITE(*emx_rd_pos_6_7, *emx_rd_pos_6_7 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_6_7 + *emx_rd_pos_6_7), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_6_7, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_6_7, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_6_7(uint8_t val) {
	while (emx_ringbuf_free_6_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_6_7 + *emx_wr_pos_6_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_7, *emx_wr_pos_6_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_7, 0);
	}
}

uint8_t EMX_Recv8_6_7() {
	uint8_t val;

	while (emx_ringbuf_size_6_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_6_7 + *emx_rd_pos_6_7);

	EMX_ATOMICWRITE(*emx_rd_pos_6_7, *emx_rd_pos_6_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_7, 0);
	}

	return val;
}

void EMX_Send16_6_7(uint16_t val) {
	while (emx_ringbuf_free_6_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_6_7 + *emx_wr_pos_6_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_7, *emx_wr_pos_6_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_7, 0);
	}
}

uint16_t EMX_Recv16_6_7() {
	uint16_t val;

	while (emx_ringbuf_size_6_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_6_7 + *emx_rd_pos_6_7);

	EMX_ATOMICWRITE(*emx_rd_pos_6_7, *emx_rd_pos_6_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_7, 0);
	}

	return val;
}

void EMX_Send32_6_7(uint32_t val) {
	while (emx_ringbuf_free_6_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_6_7 + *emx_wr_pos_6_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_7, *emx_wr_pos_6_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_7, 0);
	}
}

uint32_t EMX_Recv32_6_7() {
	uint32_t val;

	while (emx_ringbuf_size_6_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_6_7 + *emx_rd_pos_6_7);

	EMX_ATOMICWRITE(*emx_rd_pos_6_7, *emx_rd_pos_6_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_7, 0);
	}

	return val;
}

void EMX_Send64_6_7(uint64_t val) {
	while (emx_ringbuf_free_6_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_6_7 + *emx_wr_pos_6_7) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_6_7, *emx_wr_pos_6_7 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_6_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_6_7, 0);
	}
}

uint64_t EMX_Recv64_6_7() {
	uint64_t val;

	while (emx_ringbuf_size_6_7() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_6_7 + *emx_rd_pos_6_7);

	EMX_ATOMICWRITE(*emx_rd_pos_6_7, *emx_rd_pos_6_7 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_6_7 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_6_7, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_7_0;
volatile uint32_t* emx_rd_pos_7_0;
volatile uint8_t* emx_rb_buf_7_0;

void emx_send_array_7_0(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_7_0;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_7_0 + *emx_wr_pos_7_0), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_7_0, *emx_wr_pos_7_0 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_7_0 + *emx_wr_pos_7_0), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_7_0, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_7_0, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_7_0(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_7_0;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_7_0 + *emx_rd_pos_7_0), size);
		EMX_ATOMICWRITE(*emx_rd_pos_7_0, *emx_rd_pos_7_0 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_7_0 + *emx_rd_pos_7_0), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_7_0, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_7_0, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_7_0(uint8_t val) {
	while (emx_ringbuf_free_7_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_7_0 + *emx_wr_pos_7_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_0, *emx_wr_pos_7_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_0, 0);
	}
}

uint8_t EMX_Recv8_7_0() {
	uint8_t val;

	while (emx_ringbuf_size_7_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_7_0 + *emx_rd_pos_7_0);

	EMX_ATOMICWRITE(*emx_rd_pos_7_0, *emx_rd_pos_7_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_0, 0);
	}

	return val;
}

void EMX_Send16_7_0(uint16_t val) {
	while (emx_ringbuf_free_7_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_7_0 + *emx_wr_pos_7_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_0, *emx_wr_pos_7_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_0, 0);
	}
}

uint16_t EMX_Recv16_7_0() {
	uint16_t val;

	while (emx_ringbuf_size_7_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_7_0 + *emx_rd_pos_7_0);

	EMX_ATOMICWRITE(*emx_rd_pos_7_0, *emx_rd_pos_7_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_0, 0);
	}

	return val;
}

void EMX_Send32_7_0(uint32_t val) {
	while (emx_ringbuf_free_7_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_7_0 + *emx_wr_pos_7_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_0, *emx_wr_pos_7_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_0, 0);
	}
}

uint32_t EMX_Recv32_7_0() {
	uint32_t val;

	while (emx_ringbuf_size_7_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_7_0 + *emx_rd_pos_7_0);

	EMX_ATOMICWRITE(*emx_rd_pos_7_0, *emx_rd_pos_7_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_0, 0);
	}

	return val;
}

void EMX_Send64_7_0(uint64_t val) {
	while (emx_ringbuf_free_7_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_7_0 + *emx_wr_pos_7_0) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_0, *emx_wr_pos_7_0 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_0, 0);
	}
}

uint64_t EMX_Recv64_7_0() {
	uint64_t val;

	while (emx_ringbuf_size_7_0() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_7_0 + *emx_rd_pos_7_0);

	EMX_ATOMICWRITE(*emx_rd_pos_7_0, *emx_rd_pos_7_0 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_0 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_0, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_7_1;
volatile uint32_t* emx_rd_pos_7_1;
volatile uint8_t* emx_rb_buf_7_1;

void emx_send_array_7_1(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_7_1;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_7_1 + *emx_wr_pos_7_1), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_7_1, *emx_wr_pos_7_1 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_7_1 + *emx_wr_pos_7_1), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_7_1, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_7_1, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_7_1(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_7_1;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_7_1 + *emx_rd_pos_7_1), size);
		EMX_ATOMICWRITE(*emx_rd_pos_7_1, *emx_rd_pos_7_1 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_7_1 + *emx_rd_pos_7_1), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_7_1, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_7_1, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_7_1(uint8_t val) {
	while (emx_ringbuf_free_7_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_7_1 + *emx_wr_pos_7_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_1, *emx_wr_pos_7_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_1, 0);
	}
}

uint8_t EMX_Recv8_7_1() {
	uint8_t val;

	while (emx_ringbuf_size_7_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_7_1 + *emx_rd_pos_7_1);

	EMX_ATOMICWRITE(*emx_rd_pos_7_1, *emx_rd_pos_7_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_1, 0);
	}

	return val;
}

void EMX_Send16_7_1(uint16_t val) {
	while (emx_ringbuf_free_7_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_7_1 + *emx_wr_pos_7_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_1, *emx_wr_pos_7_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_1, 0);
	}
}

uint16_t EMX_Recv16_7_1() {
	uint16_t val;

	while (emx_ringbuf_size_7_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_7_1 + *emx_rd_pos_7_1);

	EMX_ATOMICWRITE(*emx_rd_pos_7_1, *emx_rd_pos_7_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_1, 0);
	}

	return val;
}

void EMX_Send32_7_1(uint32_t val) {
	while (emx_ringbuf_free_7_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_7_1 + *emx_wr_pos_7_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_1, *emx_wr_pos_7_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_1, 0);
	}
}

uint32_t EMX_Recv32_7_1() {
	uint32_t val;

	while (emx_ringbuf_size_7_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_7_1 + *emx_rd_pos_7_1);

	EMX_ATOMICWRITE(*emx_rd_pos_7_1, *emx_rd_pos_7_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_1, 0);
	}

	return val;
}

void EMX_Send64_7_1(uint64_t val) {
	while (emx_ringbuf_free_7_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_7_1 + *emx_wr_pos_7_1) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_1, *emx_wr_pos_7_1 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_1, 0);
	}
}

uint64_t EMX_Recv64_7_1() {
	uint64_t val;

	while (emx_ringbuf_size_7_1() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_7_1 + *emx_rd_pos_7_1);

	EMX_ATOMICWRITE(*emx_rd_pos_7_1, *emx_rd_pos_7_1 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_1 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_1, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_7_2;
volatile uint32_t* emx_rd_pos_7_2;
volatile uint8_t* emx_rb_buf_7_2;

void emx_send_array_7_2(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_7_2;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_7_2 + *emx_wr_pos_7_2), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_7_2, *emx_wr_pos_7_2 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_7_2 + *emx_wr_pos_7_2), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_7_2, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_7_2, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_7_2(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_7_2;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_7_2 + *emx_rd_pos_7_2), size);
		EMX_ATOMICWRITE(*emx_rd_pos_7_2, *emx_rd_pos_7_2 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_7_2 + *emx_rd_pos_7_2), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_7_2, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_7_2, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_7_2(uint8_t val) {
	while (emx_ringbuf_free_7_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_7_2 + *emx_wr_pos_7_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_2, *emx_wr_pos_7_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_2, 0);
	}
}

uint8_t EMX_Recv8_7_2() {
	uint8_t val;

	while (emx_ringbuf_size_7_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_7_2 + *emx_rd_pos_7_2);

	EMX_ATOMICWRITE(*emx_rd_pos_7_2, *emx_rd_pos_7_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_2, 0);
	}

	return val;
}

void EMX_Send16_7_2(uint16_t val) {
	while (emx_ringbuf_free_7_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_7_2 + *emx_wr_pos_7_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_2, *emx_wr_pos_7_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_2, 0);
	}
}

uint16_t EMX_Recv16_7_2() {
	uint16_t val;

	while (emx_ringbuf_size_7_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_7_2 + *emx_rd_pos_7_2);

	EMX_ATOMICWRITE(*emx_rd_pos_7_2, *emx_rd_pos_7_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_2, 0);
	}

	return val;
}

void EMX_Send32_7_2(uint32_t val) {
	while (emx_ringbuf_free_7_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_7_2 + *emx_wr_pos_7_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_2, *emx_wr_pos_7_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_2, 0);
	}
}

uint32_t EMX_Recv32_7_2() {
	uint32_t val;

	while (emx_ringbuf_size_7_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_7_2 + *emx_rd_pos_7_2);

	EMX_ATOMICWRITE(*emx_rd_pos_7_2, *emx_rd_pos_7_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_2, 0);
	}

	return val;
}

void EMX_Send64_7_2(uint64_t val) {
	while (emx_ringbuf_free_7_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_7_2 + *emx_wr_pos_7_2) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_2, *emx_wr_pos_7_2 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_2, 0);
	}
}

uint64_t EMX_Recv64_7_2() {
	uint64_t val;

	while (emx_ringbuf_size_7_2() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_7_2 + *emx_rd_pos_7_2);

	EMX_ATOMICWRITE(*emx_rd_pos_7_2, *emx_rd_pos_7_2 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_2 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_2, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_7_3;
volatile uint32_t* emx_rd_pos_7_3;
volatile uint8_t* emx_rb_buf_7_3;

void emx_send_array_7_3(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_7_3;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_7_3 + *emx_wr_pos_7_3), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_7_3, *emx_wr_pos_7_3 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_7_3 + *emx_wr_pos_7_3), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_7_3, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_7_3, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_7_3(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_7_3;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_7_3 + *emx_rd_pos_7_3), size);
		EMX_ATOMICWRITE(*emx_rd_pos_7_3, *emx_rd_pos_7_3 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_7_3 + *emx_rd_pos_7_3), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_7_3, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_7_3, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_7_3(uint8_t val) {
	while (emx_ringbuf_free_7_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_7_3 + *emx_wr_pos_7_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_3, *emx_wr_pos_7_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_3, 0);
	}
}

uint8_t EMX_Recv8_7_3() {
	uint8_t val;

	while (emx_ringbuf_size_7_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_7_3 + *emx_rd_pos_7_3);

	EMX_ATOMICWRITE(*emx_rd_pos_7_3, *emx_rd_pos_7_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_3, 0);
	}

	return val;
}

void EMX_Send16_7_3(uint16_t val) {
	while (emx_ringbuf_free_7_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_7_3 + *emx_wr_pos_7_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_3, *emx_wr_pos_7_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_3, 0);
	}
}

uint16_t EMX_Recv16_7_3() {
	uint16_t val;

	while (emx_ringbuf_size_7_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_7_3 + *emx_rd_pos_7_3);

	EMX_ATOMICWRITE(*emx_rd_pos_7_3, *emx_rd_pos_7_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_3, 0);
	}

	return val;
}

void EMX_Send32_7_3(uint32_t val) {
	while (emx_ringbuf_free_7_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_7_3 + *emx_wr_pos_7_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_3, *emx_wr_pos_7_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_3, 0);
	}
}

uint32_t EMX_Recv32_7_3() {
	uint32_t val;

	while (emx_ringbuf_size_7_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_7_3 + *emx_rd_pos_7_3);

	EMX_ATOMICWRITE(*emx_rd_pos_7_3, *emx_rd_pos_7_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_3, 0);
	}

	return val;
}

void EMX_Send64_7_3(uint64_t val) {
	while (emx_ringbuf_free_7_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_7_3 + *emx_wr_pos_7_3) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_3, *emx_wr_pos_7_3 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_3, 0);
	}
}

uint64_t EMX_Recv64_7_3() {
	uint64_t val;

	while (emx_ringbuf_size_7_3() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_7_3 + *emx_rd_pos_7_3);

	EMX_ATOMICWRITE(*emx_rd_pos_7_3, *emx_rd_pos_7_3 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_3 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_3, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_7_4;
volatile uint32_t* emx_rd_pos_7_4;
volatile uint8_t* emx_rb_buf_7_4;

void emx_send_array_7_4(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_7_4;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_7_4 + *emx_wr_pos_7_4), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_7_4, *emx_wr_pos_7_4 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_7_4 + *emx_wr_pos_7_4), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_7_4, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_7_4, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_7_4(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_7_4;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_7_4 + *emx_rd_pos_7_4), size);
		EMX_ATOMICWRITE(*emx_rd_pos_7_4, *emx_rd_pos_7_4 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_7_4 + *emx_rd_pos_7_4), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_7_4, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_7_4, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_7_4(uint8_t val) {
	while (emx_ringbuf_free_7_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_7_4 + *emx_wr_pos_7_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_4, *emx_wr_pos_7_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_4, 0);
	}
}

uint8_t EMX_Recv8_7_4() {
	uint8_t val;

	while (emx_ringbuf_size_7_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_7_4 + *emx_rd_pos_7_4);

	EMX_ATOMICWRITE(*emx_rd_pos_7_4, *emx_rd_pos_7_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_4, 0);
	}

	return val;
}

void EMX_Send16_7_4(uint16_t val) {
	while (emx_ringbuf_free_7_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_7_4 + *emx_wr_pos_7_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_4, *emx_wr_pos_7_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_4, 0);
	}
}

uint16_t EMX_Recv16_7_4() {
	uint16_t val;

	while (emx_ringbuf_size_7_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_7_4 + *emx_rd_pos_7_4);

	EMX_ATOMICWRITE(*emx_rd_pos_7_4, *emx_rd_pos_7_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_4, 0);
	}

	return val;
}

void EMX_Send32_7_4(uint32_t val) {
	while (emx_ringbuf_free_7_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_7_4 + *emx_wr_pos_7_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_4, *emx_wr_pos_7_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_4, 0);
	}
}

uint32_t EMX_Recv32_7_4() {
	uint32_t val;

	while (emx_ringbuf_size_7_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_7_4 + *emx_rd_pos_7_4);

	EMX_ATOMICWRITE(*emx_rd_pos_7_4, *emx_rd_pos_7_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_4, 0);
	}

	return val;
}

void EMX_Send64_7_4(uint64_t val) {
	while (emx_ringbuf_free_7_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_7_4 + *emx_wr_pos_7_4) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_4, *emx_wr_pos_7_4 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_4, 0);
	}
}

uint64_t EMX_Recv64_7_4() {
	uint64_t val;

	while (emx_ringbuf_size_7_4() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_7_4 + *emx_rd_pos_7_4);

	EMX_ATOMICWRITE(*emx_rd_pos_7_4, *emx_rd_pos_7_4 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_4 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_4, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_7_5;
volatile uint32_t* emx_rd_pos_7_5;
volatile uint8_t* emx_rb_buf_7_5;

void emx_send_array_7_5(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_7_5;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_7_5 + *emx_wr_pos_7_5), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_7_5, *emx_wr_pos_7_5 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_7_5 + *emx_wr_pos_7_5), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_7_5, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_7_5, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_7_5(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_7_5;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_7_5 + *emx_rd_pos_7_5), size);
		EMX_ATOMICWRITE(*emx_rd_pos_7_5, *emx_rd_pos_7_5 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_7_5 + *emx_rd_pos_7_5), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_7_5, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_7_5, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_7_5(uint8_t val) {
	while (emx_ringbuf_free_7_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_7_5 + *emx_wr_pos_7_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_5, *emx_wr_pos_7_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_5, 0);
	}
}

uint8_t EMX_Recv8_7_5() {
	uint8_t val;

	while (emx_ringbuf_size_7_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_7_5 + *emx_rd_pos_7_5);

	EMX_ATOMICWRITE(*emx_rd_pos_7_5, *emx_rd_pos_7_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_5, 0);
	}

	return val;
}

void EMX_Send16_7_5(uint16_t val) {
	while (emx_ringbuf_free_7_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_7_5 + *emx_wr_pos_7_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_5, *emx_wr_pos_7_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_5, 0);
	}
}

uint16_t EMX_Recv16_7_5() {
	uint16_t val;

	while (emx_ringbuf_size_7_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_7_5 + *emx_rd_pos_7_5);

	EMX_ATOMICWRITE(*emx_rd_pos_7_5, *emx_rd_pos_7_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_5, 0);
	}

	return val;
}

void EMX_Send32_7_5(uint32_t val) {
	while (emx_ringbuf_free_7_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_7_5 + *emx_wr_pos_7_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_5, *emx_wr_pos_7_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_5, 0);
	}
}

uint32_t EMX_Recv32_7_5() {
	uint32_t val;

	while (emx_ringbuf_size_7_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_7_5 + *emx_rd_pos_7_5);

	EMX_ATOMICWRITE(*emx_rd_pos_7_5, *emx_rd_pos_7_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_5, 0);
	}

	return val;
}

void EMX_Send64_7_5(uint64_t val) {
	while (emx_ringbuf_free_7_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_7_5 + *emx_wr_pos_7_5) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_5, *emx_wr_pos_7_5 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_5, 0);
	}
}

uint64_t EMX_Recv64_7_5() {
	uint64_t val;

	while (emx_ringbuf_size_7_5() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_7_5 + *emx_rd_pos_7_5);

	EMX_ATOMICWRITE(*emx_rd_pos_7_5, *emx_rd_pos_7_5 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_5 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_5, 0);
	}

	return val;
}

volatile uint32_t* emx_wr_pos_7_6;
volatile uint32_t* emx_rd_pos_7_6;
volatile uint8_t* emx_rb_buf_7_6;

void emx_send_array_7_6(const void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_wr_pos_7_6;
	if (remain >= size) {
		memcpy((void*)(emx_rb_buf_7_6 + *emx_wr_pos_7_6), (uint8_t*)buf, size);
		EMX_ATOMICWRITE(*emx_wr_pos_7_6, *emx_wr_pos_7_6 + EMX_ALIGNED(size));
	} else {
		memcpy((void*)(emx_rb_buf_7_6 + *emx_wr_pos_7_6), (uint8_t*)buf, remain);
		memcpy((void*)emx_rb_buf_7_6, (uint8_t*)buf + remain, size - remain);
		EMX_ATOMICWRITE(*emx_wr_pos_7_6, EMX_ALIGNED(size - remain));
	}
}

void emx_recv_array_7_6(void *buf, uint32_t size) {
	uint32_t remain = EMX_RINGBUF_SIZE - *emx_rd_pos_7_6;
	if (remain >= size) {
		memcpy(buf, (void*)(emx_rb_buf_7_6 + *emx_rd_pos_7_6), size);
		EMX_ATOMICWRITE(*emx_rd_pos_7_6, *emx_rd_pos_7_6 + EMX_ALIGNED(size));
	} else {
		memcpy(buf, (void*)(emx_rb_buf_7_6 + *emx_rd_pos_7_6), remain);
		memcpy(buf + remain, (void*)emx_rb_buf_7_6, size - remain);
		EMX_ATOMICWRITE(*emx_rd_pos_7_6, EMX_ALIGNED(size - remain));
	}
}

void EMX_Send8_7_6(uint8_t val) {
	while (emx_ringbuf_free_7_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint8_t*)(emx_rb_buf_7_6 + *emx_wr_pos_7_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_6, *emx_wr_pos_7_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_6, 0);
	}
}

uint8_t EMX_Recv8_7_6() {
	uint8_t val;

	while (emx_ringbuf_size_7_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint8_t*)(emx_rb_buf_7_6 + *emx_rd_pos_7_6);

	EMX_ATOMICWRITE(*emx_rd_pos_7_6, *emx_rd_pos_7_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_6, 0);
	}

	return val;
}

void EMX_Send16_7_6(uint16_t val) {
	while (emx_ringbuf_free_7_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint16_t*)(emx_rb_buf_7_6 + *emx_wr_pos_7_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_6, *emx_wr_pos_7_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_6, 0);
	}
}

uint16_t EMX_Recv16_7_6() {
	uint16_t val;

	while (emx_ringbuf_size_7_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint16_t*)(emx_rb_buf_7_6 + *emx_rd_pos_7_6);

	EMX_ATOMICWRITE(*emx_rd_pos_7_6, *emx_rd_pos_7_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_6, 0);
	}

	return val;
}

void EMX_Send32_7_6(uint32_t val) {
	while (emx_ringbuf_free_7_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint32_t*)(emx_rb_buf_7_6 + *emx_wr_pos_7_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_6, *emx_wr_pos_7_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_6, 0);
	}
}

uint32_t EMX_Recv32_7_6() {
	uint32_t val;

	while (emx_ringbuf_size_7_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint32_t*)(emx_rb_buf_7_6 + *emx_rd_pos_7_6);

	EMX_ATOMICWRITE(*emx_rd_pos_7_6, *emx_rd_pos_7_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_6, 0);
	}

	return val;
}

void EMX_Send64_7_6(uint64_t val) {
	while (emx_ringbuf_free_7_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	*(uint64_t*)(emx_rb_buf_7_6 + *emx_wr_pos_7_6) = val;

	EMX_ATOMICWRITE(*emx_wr_pos_7_6, *emx_wr_pos_7_6 + EMX_RINGBUF_ALIGN);

	if (*emx_wr_pos_7_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_wr_pos_7_6, 0);
	}
}

uint64_t EMX_Recv64_7_6() {
	uint64_t val;

	while (emx_ringbuf_size_7_6() < EMX_RINGBUF_ALIGN) {
		emx_ringbuf_wait();
	}

	val = *(uint64_t*)(emx_rb_buf_7_6 + *emx_rd_pos_7_6);

	EMX_ATOMICWRITE(*emx_rd_pos_7_6, *emx_rd_pos_7_6 + EMX_RINGBUF_ALIGN);

	if (*emx_rd_pos_7_6 >= EMX_RINGBUF_SIZE) {
		EMX_ATOMICWRITE(*emx_rd_pos_7_6, 0);
	}

	return val;
}

