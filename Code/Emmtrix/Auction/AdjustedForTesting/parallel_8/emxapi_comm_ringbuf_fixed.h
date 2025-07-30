#ifndef EMXAPI_COMM_RINGBUF_FIXED_H
#define EMXAPI_COMM_RINGBUF_FIXED_H

#include "emxapi_defines.h"
#include "emxapi_comm_ringbuf_config.h"
#include <stdint.h>

#define	EMX_RINGBUF_IMPL EMX_RINGBUF_IMPL_C11

#if EMX_RINGBUF_IMPL == EMX_RINGBUF_IMPL_C11
#include <stdatomic.h>

#define EMX_ATOMICREAD(x) atomic_load_explicit(&x, memory_order_acquire)
#define EMX_ATOMICWRITE(x,y) atomic_store_explicit(&x, y, memory_order_release)
#define EMX_ATOMICDECLARE(x) x
#elif EMX_RINGBUF_IMPL == EMX_RINGBUF_IMPL_CPP11
#include <atomic>

#define EMX_ATOMICREAD(x) std::atomic_load_explicit(&x, std::memory_order_acquire)
#define EMX_ATOMICWRITE(x,y) std::atomic_store_explicit(&x, y, std::memory_order_release)
#define EMX_ATOMICDECLARE(x) x
#elif EMX_RINGBUF_IMPL == EMX_RINGBUF_IMPL_VOLATILE
#define EMX_ATOMICREAD(x) x
#define EMX_ATOMICWRITE(x,y) x = y
#define EMX_ATOMICDECLARE(x) volatile x
#else
#error Invalid EMX_RINGBUF_IMPL
#endif

#if ((EMX_RINGBUF_ALIGN == 0) || ((EMX_RINGBUF_ALIGN &(EMX_RINGBUF_ALIGN - 1)) != 0))
#error The ringbuffer alignment (EMX_RINGBUF_ALIGN) must be a power of 2
#endif

#ifndef EMX_RINGBUF_CHUNK_SIZE
#define EMX_RINGBUF_CHUNK_SIZE (EMX_RINGBUF_SIZE/4)
#endif

#if defined(__GNUC__) || defined(__clang__) || defined(__MINGW32__) || defined(__MINGW64__)
#define EMX_ALWAYS_INLINE __attribute__ ((always_inline))
#else
#define EMX_ALWAYS_INLINE
#endif

int EMX_Init(int argc, char *argv[]);
void EMX_Finalize();
int EMX_RecvSync(int src, int dst, int id, int index);
void EMX_SendSync(int sync, int src, int dst, int id, int index);
void EMX_Wait(int src, int dst, int id, int index);
void EMX_Signal(int src, int dst, int id, int index);
void EMX_SyncCores(int core);

#define EMX_Send8(SRC, DST, ID, INDEX, VAL) EMX_Send8_##SRC##_##DST(VAL)
#define EMX_Recv8(SRC, DST, ID, INDEX) EMX_Recv8_##SRC##_##DST()
#define EMX_Send16(SRC, DST, ID, INDEX, VAL) EMX_Send16_##SRC##_##DST(VAL)
#define EMX_Recv16(SRC, DST, ID, INDEX) EMX_Recv16_##SRC##_##DST()
#define EMX_Send32(SRC, DST, ID, INDEX, VAL) EMX_Send32_##SRC##_##DST(VAL)
#define EMX_Recv32(SRC, DST, ID, INDEX) EMX_Recv32_##SRC##_##DST()
#define EMX_Send64(SRC, DST, ID, INDEX, VAL) EMX_Send64_##SRC##_##DST(VAL)
#define EMX_Recv64(SRC, DST, ID, INDEX) EMX_Recv64_##SRC##_##DST()
#define EMX_Send32F(SRC, DST, ID, INDEX, VAL) EMX_Send32F_##SRC##_##DST(VAL)
#define EMX_Recv32F(SRC, DST, ID, INDEX) EMX_Recv32F_##SRC##_##DST()
#define EMX_Send64F(SRC, DST, ID, INDEX, VAL) EMX_Send64F_##SRC##_##DST(VAL)
#define EMX_Recv64F(SRC, DST, ID, INDEX) EMX_Recv64F_##SRC##_##DST()
#define EMX_Send(SRC, DST, ID, INDEX, BUF, SIZE) EMX_Send_##SRC##_##DST(BUF, SIZE)
#define EMX_Recv(SRC, DST, ID, INDEX, BUF, SIZE) EMX_Recv_##SRC##_##DST(BUF, SIZE)
#define EMX_SendSync(SRC, DST, ID, INDEX, VAL) EMX_SendSync_##SRC##_##DST(VAL)
#define EMX_RecvSync(SRC, DST, ID, INDEX) EMX_RecvSync_##SRC##_##DST()
#define EMX_Signal(SRC, DST, ID, INDEX) EMX_Signal_##SRC##_##DST()
#define EMX_Wait(SRC, DST, ID, INDEX) EMX_Wait_##SRC##_##DST()

void emx_ringbuf_wait_0();

void EMX_Send8_0_1(register uint8_t);
uint8_t EMX_Recv8_0_1();
void EMX_Send16_0_1(register uint16_t);
uint16_t EMX_Recv16_0_1();
void EMX_Send32_0_1(register uint32_t);
uint32_t EMX_Recv32_0_1();
void EMX_Send64_0_1(register uint64_t);
uint64_t EMX_Recv64_0_1();
void emx_send_array_0_1(register const void *buf, register uint32_t size);
void emx_recv_array_0_1(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_0_1();
static inline uint32_t emx_ringbuf_size_0_1() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_0_1);
	return wr + ((wr < *emx_loc_rd_pos_0_1) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_0_1;
}

static inline uint32_t emx_ringbuf_free_0_1();
static inline uint32_t emx_ringbuf_free_0_1() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_0_1);
	return rd + ((*emx_loc_wr_pos_0_1 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_0_1 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_0_1(const register void *buf, register uint32_t size);

static inline void emx_send_0_1(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_0_1(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_0_1() < size) emx_ringbuf_wait_0();

	emx_send_array_0_1(buf, size);
}

void EMX_Send_0_1(const void *buf, uint32_t size);

extern void emx_recv_array_0_1(register void *buf, register uint32_t size);

static inline void emx_recv_0_1(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_0_1(void *buf, uint32_t size) {
	while (emx_ringbuf_size_0_1() < size) emx_ringbuf_wait_1();

	emx_recv_array_0_1(buf, size);
}

void EMX_Recv_0_1(void *buf, uint32_t size);

static inline void EMX_Send32F_0_1(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_0_1(float val) {
	EMX_Send32_0_1(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_0_1() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_0_1() {
	uint32_t r = EMX_Recv32_0_1();
	return *(float*)&r;
}

static inline void EMX_Send64F_0_1(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_0_1(double val) {
	EMX_Send64_0_1(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_0_1() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_0_1() {
	uint64_t r = EMX_Recv64_0_1();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_0_1() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_0_1() {
	return EMX_Recv8_0_1();
}

static inline void EMX_SendSync_0_1(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_0_1(uint8_t sync) {
	EMX_Send8_0_1(sync);
}

static inline void EMX_Wait_0_1() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_0_1() {
	EMX_Recv8_0_1();
}

static inline void EMX_Signal_0_1() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_0_1() {
	EMX_Send8_0_1(0);
}

void EMX_Send8_0_2(register uint8_t);
uint8_t EMX_Recv8_0_2();
void EMX_Send16_0_2(register uint16_t);
uint16_t EMX_Recv16_0_2();
void EMX_Send32_0_2(register uint32_t);
uint32_t EMX_Recv32_0_2();
void EMX_Send64_0_2(register uint64_t);
uint64_t EMX_Recv64_0_2();
void emx_send_array_0_2(register const void *buf, register uint32_t size);
void emx_recv_array_0_2(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_0_2();
static inline uint32_t emx_ringbuf_size_0_2() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_0_2);
	return wr + ((wr < *emx_loc_rd_pos_0_2) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_0_2;
}

static inline uint32_t emx_ringbuf_free_0_2();
static inline uint32_t emx_ringbuf_free_0_2() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_0_2);
	return rd + ((*emx_loc_wr_pos_0_2 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_0_2 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_0_2(const register void *buf, register uint32_t size);

static inline void emx_send_0_2(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_0_2(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_0_2() < size) emx_ringbuf_wait_0();

	emx_send_array_0_2(buf, size);
}

void EMX_Send_0_2(const void *buf, uint32_t size);

extern void emx_recv_array_0_2(register void *buf, register uint32_t size);

static inline void emx_recv_0_2(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_0_2(void *buf, uint32_t size) {
	while (emx_ringbuf_size_0_2() < size) emx_ringbuf_wait_2();

	emx_recv_array_0_2(buf, size);
}

void EMX_Recv_0_2(void *buf, uint32_t size);

static inline void EMX_Send32F_0_2(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_0_2(float val) {
	EMX_Send32_0_2(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_0_2() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_0_2() {
	uint32_t r = EMX_Recv32_0_2();
	return *(float*)&r;
}

static inline void EMX_Send64F_0_2(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_0_2(double val) {
	EMX_Send64_0_2(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_0_2() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_0_2() {
	uint64_t r = EMX_Recv64_0_2();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_0_2() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_0_2() {
	return EMX_Recv8_0_2();
}

static inline void EMX_SendSync_0_2(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_0_2(uint8_t sync) {
	EMX_Send8_0_2(sync);
}

static inline void EMX_Wait_0_2() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_0_2() {
	EMX_Recv8_0_2();
}

static inline void EMX_Signal_0_2() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_0_2() {
	EMX_Send8_0_2(0);
}

void EMX_Send8_0_3(register uint8_t);
uint8_t EMX_Recv8_0_3();
void EMX_Send16_0_3(register uint16_t);
uint16_t EMX_Recv16_0_3();
void EMX_Send32_0_3(register uint32_t);
uint32_t EMX_Recv32_0_3();
void EMX_Send64_0_3(register uint64_t);
uint64_t EMX_Recv64_0_3();
void emx_send_array_0_3(register const void *buf, register uint32_t size);
void emx_recv_array_0_3(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_0_3();
static inline uint32_t emx_ringbuf_size_0_3() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_0_3);
	return wr + ((wr < *emx_loc_rd_pos_0_3) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_0_3;
}

static inline uint32_t emx_ringbuf_free_0_3();
static inline uint32_t emx_ringbuf_free_0_3() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_0_3);
	return rd + ((*emx_loc_wr_pos_0_3 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_0_3 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_0_3(const register void *buf, register uint32_t size);

static inline void emx_send_0_3(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_0_3(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_0_3() < size) emx_ringbuf_wait_0();

	emx_send_array_0_3(buf, size);
}

void EMX_Send_0_3(const void *buf, uint32_t size);

extern void emx_recv_array_0_3(register void *buf, register uint32_t size);

static inline void emx_recv_0_3(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_0_3(void *buf, uint32_t size) {
	while (emx_ringbuf_size_0_3() < size) emx_ringbuf_wait_3();

	emx_recv_array_0_3(buf, size);
}

void EMX_Recv_0_3(void *buf, uint32_t size);

static inline void EMX_Send32F_0_3(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_0_3(float val) {
	EMX_Send32_0_3(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_0_3() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_0_3() {
	uint32_t r = EMX_Recv32_0_3();
	return *(float*)&r;
}

static inline void EMX_Send64F_0_3(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_0_3(double val) {
	EMX_Send64_0_3(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_0_3() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_0_3() {
	uint64_t r = EMX_Recv64_0_3();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_0_3() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_0_3() {
	return EMX_Recv8_0_3();
}

static inline void EMX_SendSync_0_3(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_0_3(uint8_t sync) {
	EMX_Send8_0_3(sync);
}

static inline void EMX_Wait_0_3() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_0_3() {
	EMX_Recv8_0_3();
}

static inline void EMX_Signal_0_3() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_0_3() {
	EMX_Send8_0_3(0);
}

void EMX_Send8_0_4(register uint8_t);
uint8_t EMX_Recv8_0_4();
void EMX_Send16_0_4(register uint16_t);
uint16_t EMX_Recv16_0_4();
void EMX_Send32_0_4(register uint32_t);
uint32_t EMX_Recv32_0_4();
void EMX_Send64_0_4(register uint64_t);
uint64_t EMX_Recv64_0_4();
void emx_send_array_0_4(register const void *buf, register uint32_t size);
void emx_recv_array_0_4(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_0_4();
static inline uint32_t emx_ringbuf_size_0_4() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_0_4);
	return wr + ((wr < *emx_loc_rd_pos_0_4) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_0_4;
}

static inline uint32_t emx_ringbuf_free_0_4();
static inline uint32_t emx_ringbuf_free_0_4() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_0_4);
	return rd + ((*emx_loc_wr_pos_0_4 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_0_4 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_0_4(const register void *buf, register uint32_t size);

static inline void emx_send_0_4(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_0_4(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_0_4() < size) emx_ringbuf_wait_0();

	emx_send_array_0_4(buf, size);
}

void EMX_Send_0_4(const void *buf, uint32_t size);

extern void emx_recv_array_0_4(register void *buf, register uint32_t size);

static inline void emx_recv_0_4(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_0_4(void *buf, uint32_t size) {
	while (emx_ringbuf_size_0_4() < size) emx_ringbuf_wait_4();

	emx_recv_array_0_4(buf, size);
}

void EMX_Recv_0_4(void *buf, uint32_t size);

static inline void EMX_Send32F_0_4(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_0_4(float val) {
	EMX_Send32_0_4(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_0_4() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_0_4() {
	uint32_t r = EMX_Recv32_0_4();
	return *(float*)&r;
}

static inline void EMX_Send64F_0_4(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_0_4(double val) {
	EMX_Send64_0_4(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_0_4() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_0_4() {
	uint64_t r = EMX_Recv64_0_4();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_0_4() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_0_4() {
	return EMX_Recv8_0_4();
}

static inline void EMX_SendSync_0_4(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_0_4(uint8_t sync) {
	EMX_Send8_0_4(sync);
}

static inline void EMX_Wait_0_4() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_0_4() {
	EMX_Recv8_0_4();
}

static inline void EMX_Signal_0_4() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_0_4() {
	EMX_Send8_0_4(0);
}

void EMX_Send8_0_5(register uint8_t);
uint8_t EMX_Recv8_0_5();
void EMX_Send16_0_5(register uint16_t);
uint16_t EMX_Recv16_0_5();
void EMX_Send32_0_5(register uint32_t);
uint32_t EMX_Recv32_0_5();
void EMX_Send64_0_5(register uint64_t);
uint64_t EMX_Recv64_0_5();
void emx_send_array_0_5(register const void *buf, register uint32_t size);
void emx_recv_array_0_5(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_0_5();
static inline uint32_t emx_ringbuf_size_0_5() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_0_5);
	return wr + ((wr < *emx_loc_rd_pos_0_5) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_0_5;
}

static inline uint32_t emx_ringbuf_free_0_5();
static inline uint32_t emx_ringbuf_free_0_5() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_0_5);
	return rd + ((*emx_loc_wr_pos_0_5 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_0_5 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_0_5(const register void *buf, register uint32_t size);

static inline void emx_send_0_5(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_0_5(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_0_5() < size) emx_ringbuf_wait_0();

	emx_send_array_0_5(buf, size);
}

void EMX_Send_0_5(const void *buf, uint32_t size);

extern void emx_recv_array_0_5(register void *buf, register uint32_t size);

static inline void emx_recv_0_5(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_0_5(void *buf, uint32_t size) {
	while (emx_ringbuf_size_0_5() < size) emx_ringbuf_wait_5();

	emx_recv_array_0_5(buf, size);
}

void EMX_Recv_0_5(void *buf, uint32_t size);

static inline void EMX_Send32F_0_5(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_0_5(float val) {
	EMX_Send32_0_5(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_0_5() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_0_5() {
	uint32_t r = EMX_Recv32_0_5();
	return *(float*)&r;
}

static inline void EMX_Send64F_0_5(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_0_5(double val) {
	EMX_Send64_0_5(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_0_5() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_0_5() {
	uint64_t r = EMX_Recv64_0_5();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_0_5() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_0_5() {
	return EMX_Recv8_0_5();
}

static inline void EMX_SendSync_0_5(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_0_5(uint8_t sync) {
	EMX_Send8_0_5(sync);
}

static inline void EMX_Wait_0_5() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_0_5() {
	EMX_Recv8_0_5();
}

static inline void EMX_Signal_0_5() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_0_5() {
	EMX_Send8_0_5(0);
}

void EMX_Send8_0_6(register uint8_t);
uint8_t EMX_Recv8_0_6();
void EMX_Send16_0_6(register uint16_t);
uint16_t EMX_Recv16_0_6();
void EMX_Send32_0_6(register uint32_t);
uint32_t EMX_Recv32_0_6();
void EMX_Send64_0_6(register uint64_t);
uint64_t EMX_Recv64_0_6();
void emx_send_array_0_6(register const void *buf, register uint32_t size);
void emx_recv_array_0_6(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_0_6();
static inline uint32_t emx_ringbuf_size_0_6() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_0_6);
	return wr + ((wr < *emx_loc_rd_pos_0_6) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_0_6;
}

static inline uint32_t emx_ringbuf_free_0_6();
static inline uint32_t emx_ringbuf_free_0_6() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_0_6);
	return rd + ((*emx_loc_wr_pos_0_6 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_0_6 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_0_6(const register void *buf, register uint32_t size);

static inline void emx_send_0_6(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_0_6(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_0_6() < size) emx_ringbuf_wait_0();

	emx_send_array_0_6(buf, size);
}

void EMX_Send_0_6(const void *buf, uint32_t size);

extern void emx_recv_array_0_6(register void *buf, register uint32_t size);

static inline void emx_recv_0_6(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_0_6(void *buf, uint32_t size) {
	while (emx_ringbuf_size_0_6() < size) emx_ringbuf_wait_6();

	emx_recv_array_0_6(buf, size);
}

void EMX_Recv_0_6(void *buf, uint32_t size);

static inline void EMX_Send32F_0_6(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_0_6(float val) {
	EMX_Send32_0_6(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_0_6() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_0_6() {
	uint32_t r = EMX_Recv32_0_6();
	return *(float*)&r;
}

static inline void EMX_Send64F_0_6(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_0_6(double val) {
	EMX_Send64_0_6(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_0_6() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_0_6() {
	uint64_t r = EMX_Recv64_0_6();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_0_6() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_0_6() {
	return EMX_Recv8_0_6();
}

static inline void EMX_SendSync_0_6(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_0_6(uint8_t sync) {
	EMX_Send8_0_6(sync);
}

static inline void EMX_Wait_0_6() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_0_6() {
	EMX_Recv8_0_6();
}

static inline void EMX_Signal_0_6() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_0_6() {
	EMX_Send8_0_6(0);
}

void EMX_Send8_0_7(register uint8_t);
uint8_t EMX_Recv8_0_7();
void EMX_Send16_0_7(register uint16_t);
uint16_t EMX_Recv16_0_7();
void EMX_Send32_0_7(register uint32_t);
uint32_t EMX_Recv32_0_7();
void EMX_Send64_0_7(register uint64_t);
uint64_t EMX_Recv64_0_7();
void emx_send_array_0_7(register const void *buf, register uint32_t size);
void emx_recv_array_0_7(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_0_7();
static inline uint32_t emx_ringbuf_size_0_7() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_0_7);
	return wr + ((wr < *emx_loc_rd_pos_0_7) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_0_7;
}

static inline uint32_t emx_ringbuf_free_0_7();
static inline uint32_t emx_ringbuf_free_0_7() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_0_7);
	return rd + ((*emx_loc_wr_pos_0_7 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_0_7 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_0_7(const register void *buf, register uint32_t size);

static inline void emx_send_0_7(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_0_7(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_0_7() < size) emx_ringbuf_wait_0();

	emx_send_array_0_7(buf, size);
}

void EMX_Send_0_7(const void *buf, uint32_t size);

extern void emx_recv_array_0_7(register void *buf, register uint32_t size);

static inline void emx_recv_0_7(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_0_7(void *buf, uint32_t size) {
	while (emx_ringbuf_size_0_7() < size) emx_ringbuf_wait_7();

	emx_recv_array_0_7(buf, size);
}

void EMX_Recv_0_7(void *buf, uint32_t size);

static inline void EMX_Send32F_0_7(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_0_7(float val) {
	EMX_Send32_0_7(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_0_7() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_0_7() {
	uint32_t r = EMX_Recv32_0_7();
	return *(float*)&r;
}

static inline void EMX_Send64F_0_7(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_0_7(double val) {
	EMX_Send64_0_7(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_0_7() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_0_7() {
	uint64_t r = EMX_Recv64_0_7();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_0_7() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_0_7() {
	return EMX_Recv8_0_7();
}

static inline void EMX_SendSync_0_7(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_0_7(uint8_t sync) {
	EMX_Send8_0_7(sync);
}

static inline void EMX_Wait_0_7() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_0_7() {
	EMX_Recv8_0_7();
}

static inline void EMX_Signal_0_7() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_0_7() {
	EMX_Send8_0_7(0);
}

void emx_ringbuf_wait_1();

void EMX_Send8_1_0(register uint8_t);
uint8_t EMX_Recv8_1_0();
void EMX_Send16_1_0(register uint16_t);
uint16_t EMX_Recv16_1_0();
void EMX_Send32_1_0(register uint32_t);
uint32_t EMX_Recv32_1_0();
void EMX_Send64_1_0(register uint64_t);
uint64_t EMX_Recv64_1_0();
void emx_send_array_1_0(register const void *buf, register uint32_t size);
void emx_recv_array_1_0(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_1_0();
static inline uint32_t emx_ringbuf_size_1_0() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_1_0);
	return wr + ((wr < *emx_loc_rd_pos_1_0) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_1_0;
}

static inline uint32_t emx_ringbuf_free_1_0();
static inline uint32_t emx_ringbuf_free_1_0() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_1_0);
	return rd + ((*emx_loc_wr_pos_1_0 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_1_0 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_1_0(const register void *buf, register uint32_t size);

static inline void emx_send_1_0(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_1_0(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_1_0() < size) emx_ringbuf_wait_1();

	emx_send_array_1_0(buf, size);
}

void EMX_Send_1_0(const void *buf, uint32_t size);

extern void emx_recv_array_1_0(register void *buf, register uint32_t size);

static inline void emx_recv_1_0(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_1_0(void *buf, uint32_t size) {
	while (emx_ringbuf_size_1_0() < size) emx_ringbuf_wait_0();

	emx_recv_array_1_0(buf, size);
}

void EMX_Recv_1_0(void *buf, uint32_t size);

static inline void EMX_Send32F_1_0(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_1_0(float val) {
	EMX_Send32_1_0(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_1_0() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_1_0() {
	uint32_t r = EMX_Recv32_1_0();
	return *(float*)&r;
}

static inline void EMX_Send64F_1_0(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_1_0(double val) {
	EMX_Send64_1_0(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_1_0() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_1_0() {
	uint64_t r = EMX_Recv64_1_0();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_1_0() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_1_0() {
	return EMX_Recv8_1_0();
}

static inline void EMX_SendSync_1_0(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_1_0(uint8_t sync) {
	EMX_Send8_1_0(sync);
}

static inline void EMX_Wait_1_0() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_1_0() {
	EMX_Recv8_1_0();
}

static inline void EMX_Signal_1_0() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_1_0() {
	EMX_Send8_1_0(0);
}

void EMX_Send8_1_2(register uint8_t);
uint8_t EMX_Recv8_1_2();
void EMX_Send16_1_2(register uint16_t);
uint16_t EMX_Recv16_1_2();
void EMX_Send32_1_2(register uint32_t);
uint32_t EMX_Recv32_1_2();
void EMX_Send64_1_2(register uint64_t);
uint64_t EMX_Recv64_1_2();
void emx_send_array_1_2(register const void *buf, register uint32_t size);
void emx_recv_array_1_2(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_1_2();
static inline uint32_t emx_ringbuf_size_1_2() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_1_2);
	return wr + ((wr < *emx_loc_rd_pos_1_2) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_1_2;
}

static inline uint32_t emx_ringbuf_free_1_2();
static inline uint32_t emx_ringbuf_free_1_2() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_1_2);
	return rd + ((*emx_loc_wr_pos_1_2 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_1_2 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_1_2(const register void *buf, register uint32_t size);

static inline void emx_send_1_2(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_1_2(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_1_2() < size) emx_ringbuf_wait_1();

	emx_send_array_1_2(buf, size);
}

void EMX_Send_1_2(const void *buf, uint32_t size);

extern void emx_recv_array_1_2(register void *buf, register uint32_t size);

static inline void emx_recv_1_2(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_1_2(void *buf, uint32_t size) {
	while (emx_ringbuf_size_1_2() < size) emx_ringbuf_wait_2();

	emx_recv_array_1_2(buf, size);
}

void EMX_Recv_1_2(void *buf, uint32_t size);

static inline void EMX_Send32F_1_2(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_1_2(float val) {
	EMX_Send32_1_2(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_1_2() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_1_2() {
	uint32_t r = EMX_Recv32_1_2();
	return *(float*)&r;
}

static inline void EMX_Send64F_1_2(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_1_2(double val) {
	EMX_Send64_1_2(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_1_2() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_1_2() {
	uint64_t r = EMX_Recv64_1_2();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_1_2() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_1_2() {
	return EMX_Recv8_1_2();
}

static inline void EMX_SendSync_1_2(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_1_2(uint8_t sync) {
	EMX_Send8_1_2(sync);
}

static inline void EMX_Wait_1_2() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_1_2() {
	EMX_Recv8_1_2();
}

static inline void EMX_Signal_1_2() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_1_2() {
	EMX_Send8_1_2(0);
}

void EMX_Send8_1_3(register uint8_t);
uint8_t EMX_Recv8_1_3();
void EMX_Send16_1_3(register uint16_t);
uint16_t EMX_Recv16_1_3();
void EMX_Send32_1_3(register uint32_t);
uint32_t EMX_Recv32_1_3();
void EMX_Send64_1_3(register uint64_t);
uint64_t EMX_Recv64_1_3();
void emx_send_array_1_3(register const void *buf, register uint32_t size);
void emx_recv_array_1_3(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_1_3();
static inline uint32_t emx_ringbuf_size_1_3() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_1_3);
	return wr + ((wr < *emx_loc_rd_pos_1_3) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_1_3;
}

static inline uint32_t emx_ringbuf_free_1_3();
static inline uint32_t emx_ringbuf_free_1_3() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_1_3);
	return rd + ((*emx_loc_wr_pos_1_3 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_1_3 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_1_3(const register void *buf, register uint32_t size);

static inline void emx_send_1_3(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_1_3(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_1_3() < size) emx_ringbuf_wait_1();

	emx_send_array_1_3(buf, size);
}

void EMX_Send_1_3(const void *buf, uint32_t size);

extern void emx_recv_array_1_3(register void *buf, register uint32_t size);

static inline void emx_recv_1_3(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_1_3(void *buf, uint32_t size) {
	while (emx_ringbuf_size_1_3() < size) emx_ringbuf_wait_3();

	emx_recv_array_1_3(buf, size);
}

void EMX_Recv_1_3(void *buf, uint32_t size);

static inline void EMX_Send32F_1_3(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_1_3(float val) {
	EMX_Send32_1_3(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_1_3() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_1_3() {
	uint32_t r = EMX_Recv32_1_3();
	return *(float*)&r;
}

static inline void EMX_Send64F_1_3(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_1_3(double val) {
	EMX_Send64_1_3(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_1_3() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_1_3() {
	uint64_t r = EMX_Recv64_1_3();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_1_3() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_1_3() {
	return EMX_Recv8_1_3();
}

static inline void EMX_SendSync_1_3(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_1_3(uint8_t sync) {
	EMX_Send8_1_3(sync);
}

static inline void EMX_Wait_1_3() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_1_3() {
	EMX_Recv8_1_3();
}

static inline void EMX_Signal_1_3() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_1_3() {
	EMX_Send8_1_3(0);
}

void EMX_Send8_1_4(register uint8_t);
uint8_t EMX_Recv8_1_4();
void EMX_Send16_1_4(register uint16_t);
uint16_t EMX_Recv16_1_4();
void EMX_Send32_1_4(register uint32_t);
uint32_t EMX_Recv32_1_4();
void EMX_Send64_1_4(register uint64_t);
uint64_t EMX_Recv64_1_4();
void emx_send_array_1_4(register const void *buf, register uint32_t size);
void emx_recv_array_1_4(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_1_4();
static inline uint32_t emx_ringbuf_size_1_4() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_1_4);
	return wr + ((wr < *emx_loc_rd_pos_1_4) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_1_4;
}

static inline uint32_t emx_ringbuf_free_1_4();
static inline uint32_t emx_ringbuf_free_1_4() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_1_4);
	return rd + ((*emx_loc_wr_pos_1_4 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_1_4 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_1_4(const register void *buf, register uint32_t size);

static inline void emx_send_1_4(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_1_4(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_1_4() < size) emx_ringbuf_wait_1();

	emx_send_array_1_4(buf, size);
}

void EMX_Send_1_4(const void *buf, uint32_t size);

extern void emx_recv_array_1_4(register void *buf, register uint32_t size);

static inline void emx_recv_1_4(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_1_4(void *buf, uint32_t size) {
	while (emx_ringbuf_size_1_4() < size) emx_ringbuf_wait_4();

	emx_recv_array_1_4(buf, size);
}

void EMX_Recv_1_4(void *buf, uint32_t size);

static inline void EMX_Send32F_1_4(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_1_4(float val) {
	EMX_Send32_1_4(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_1_4() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_1_4() {
	uint32_t r = EMX_Recv32_1_4();
	return *(float*)&r;
}

static inline void EMX_Send64F_1_4(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_1_4(double val) {
	EMX_Send64_1_4(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_1_4() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_1_4() {
	uint64_t r = EMX_Recv64_1_4();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_1_4() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_1_4() {
	return EMX_Recv8_1_4();
}

static inline void EMX_SendSync_1_4(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_1_4(uint8_t sync) {
	EMX_Send8_1_4(sync);
}

static inline void EMX_Wait_1_4() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_1_4() {
	EMX_Recv8_1_4();
}

static inline void EMX_Signal_1_4() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_1_4() {
	EMX_Send8_1_4(0);
}

void EMX_Send8_1_5(register uint8_t);
uint8_t EMX_Recv8_1_5();
void EMX_Send16_1_5(register uint16_t);
uint16_t EMX_Recv16_1_5();
void EMX_Send32_1_5(register uint32_t);
uint32_t EMX_Recv32_1_5();
void EMX_Send64_1_5(register uint64_t);
uint64_t EMX_Recv64_1_5();
void emx_send_array_1_5(register const void *buf, register uint32_t size);
void emx_recv_array_1_5(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_1_5();
static inline uint32_t emx_ringbuf_size_1_5() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_1_5);
	return wr + ((wr < *emx_loc_rd_pos_1_5) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_1_5;
}

static inline uint32_t emx_ringbuf_free_1_5();
static inline uint32_t emx_ringbuf_free_1_5() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_1_5);
	return rd + ((*emx_loc_wr_pos_1_5 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_1_5 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_1_5(const register void *buf, register uint32_t size);

static inline void emx_send_1_5(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_1_5(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_1_5() < size) emx_ringbuf_wait_1();

	emx_send_array_1_5(buf, size);
}

void EMX_Send_1_5(const void *buf, uint32_t size);

extern void emx_recv_array_1_5(register void *buf, register uint32_t size);

static inline void emx_recv_1_5(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_1_5(void *buf, uint32_t size) {
	while (emx_ringbuf_size_1_5() < size) emx_ringbuf_wait_5();

	emx_recv_array_1_5(buf, size);
}

void EMX_Recv_1_5(void *buf, uint32_t size);

static inline void EMX_Send32F_1_5(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_1_5(float val) {
	EMX_Send32_1_5(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_1_5() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_1_5() {
	uint32_t r = EMX_Recv32_1_5();
	return *(float*)&r;
}

static inline void EMX_Send64F_1_5(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_1_5(double val) {
	EMX_Send64_1_5(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_1_5() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_1_5() {
	uint64_t r = EMX_Recv64_1_5();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_1_5() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_1_5() {
	return EMX_Recv8_1_5();
}

static inline void EMX_SendSync_1_5(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_1_5(uint8_t sync) {
	EMX_Send8_1_5(sync);
}

static inline void EMX_Wait_1_5() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_1_5() {
	EMX_Recv8_1_5();
}

static inline void EMX_Signal_1_5() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_1_5() {
	EMX_Send8_1_5(0);
}

void EMX_Send8_1_6(register uint8_t);
uint8_t EMX_Recv8_1_6();
void EMX_Send16_1_6(register uint16_t);
uint16_t EMX_Recv16_1_6();
void EMX_Send32_1_6(register uint32_t);
uint32_t EMX_Recv32_1_6();
void EMX_Send64_1_6(register uint64_t);
uint64_t EMX_Recv64_1_6();
void emx_send_array_1_6(register const void *buf, register uint32_t size);
void emx_recv_array_1_6(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_1_6();
static inline uint32_t emx_ringbuf_size_1_6() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_1_6);
	return wr + ((wr < *emx_loc_rd_pos_1_6) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_1_6;
}

static inline uint32_t emx_ringbuf_free_1_6();
static inline uint32_t emx_ringbuf_free_1_6() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_1_6);
	return rd + ((*emx_loc_wr_pos_1_6 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_1_6 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_1_6(const register void *buf, register uint32_t size);

static inline void emx_send_1_6(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_1_6(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_1_6() < size) emx_ringbuf_wait_1();

	emx_send_array_1_6(buf, size);
}

void EMX_Send_1_6(const void *buf, uint32_t size);

extern void emx_recv_array_1_6(register void *buf, register uint32_t size);

static inline void emx_recv_1_6(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_1_6(void *buf, uint32_t size) {
	while (emx_ringbuf_size_1_6() < size) emx_ringbuf_wait_6();

	emx_recv_array_1_6(buf, size);
}

void EMX_Recv_1_6(void *buf, uint32_t size);

static inline void EMX_Send32F_1_6(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_1_6(float val) {
	EMX_Send32_1_6(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_1_6() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_1_6() {
	uint32_t r = EMX_Recv32_1_6();
	return *(float*)&r;
}

static inline void EMX_Send64F_1_6(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_1_6(double val) {
	EMX_Send64_1_6(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_1_6() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_1_6() {
	uint64_t r = EMX_Recv64_1_6();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_1_6() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_1_6() {
	return EMX_Recv8_1_6();
}

static inline void EMX_SendSync_1_6(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_1_6(uint8_t sync) {
	EMX_Send8_1_6(sync);
}

static inline void EMX_Wait_1_6() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_1_6() {
	EMX_Recv8_1_6();
}

static inline void EMX_Signal_1_6() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_1_6() {
	EMX_Send8_1_6(0);
}

void EMX_Send8_1_7(register uint8_t);
uint8_t EMX_Recv8_1_7();
void EMX_Send16_1_7(register uint16_t);
uint16_t EMX_Recv16_1_7();
void EMX_Send32_1_7(register uint32_t);
uint32_t EMX_Recv32_1_7();
void EMX_Send64_1_7(register uint64_t);
uint64_t EMX_Recv64_1_7();
void emx_send_array_1_7(register const void *buf, register uint32_t size);
void emx_recv_array_1_7(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_1_7();
static inline uint32_t emx_ringbuf_size_1_7() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_1_7);
	return wr + ((wr < *emx_loc_rd_pos_1_7) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_1_7;
}

static inline uint32_t emx_ringbuf_free_1_7();
static inline uint32_t emx_ringbuf_free_1_7() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_1_7);
	return rd + ((*emx_loc_wr_pos_1_7 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_1_7 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_1_7(const register void *buf, register uint32_t size);

static inline void emx_send_1_7(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_1_7(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_1_7() < size) emx_ringbuf_wait_1();

	emx_send_array_1_7(buf, size);
}

void EMX_Send_1_7(const void *buf, uint32_t size);

extern void emx_recv_array_1_7(register void *buf, register uint32_t size);

static inline void emx_recv_1_7(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_1_7(void *buf, uint32_t size) {
	while (emx_ringbuf_size_1_7() < size) emx_ringbuf_wait_7();

	emx_recv_array_1_7(buf, size);
}

void EMX_Recv_1_7(void *buf, uint32_t size);

static inline void EMX_Send32F_1_7(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_1_7(float val) {
	EMX_Send32_1_7(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_1_7() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_1_7() {
	uint32_t r = EMX_Recv32_1_7();
	return *(float*)&r;
}

static inline void EMX_Send64F_1_7(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_1_7(double val) {
	EMX_Send64_1_7(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_1_7() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_1_7() {
	uint64_t r = EMX_Recv64_1_7();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_1_7() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_1_7() {
	return EMX_Recv8_1_7();
}

static inline void EMX_SendSync_1_7(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_1_7(uint8_t sync) {
	EMX_Send8_1_7(sync);
}

static inline void EMX_Wait_1_7() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_1_7() {
	EMX_Recv8_1_7();
}

static inline void EMX_Signal_1_7() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_1_7() {
	EMX_Send8_1_7(0);
}

void emx_ringbuf_wait_2();

void EMX_Send8_2_0(register uint8_t);
uint8_t EMX_Recv8_2_0();
void EMX_Send16_2_0(register uint16_t);
uint16_t EMX_Recv16_2_0();
void EMX_Send32_2_0(register uint32_t);
uint32_t EMX_Recv32_2_0();
void EMX_Send64_2_0(register uint64_t);
uint64_t EMX_Recv64_2_0();
void emx_send_array_2_0(register const void *buf, register uint32_t size);
void emx_recv_array_2_0(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_2_0();
static inline uint32_t emx_ringbuf_size_2_0() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_2_0);
	return wr + ((wr < *emx_loc_rd_pos_2_0) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_2_0;
}

static inline uint32_t emx_ringbuf_free_2_0();
static inline uint32_t emx_ringbuf_free_2_0() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_2_0);
	return rd + ((*emx_loc_wr_pos_2_0 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_2_0 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_2_0(const register void *buf, register uint32_t size);

static inline void emx_send_2_0(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_2_0(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_2_0() < size) emx_ringbuf_wait_2();

	emx_send_array_2_0(buf, size);
}

void EMX_Send_2_0(const void *buf, uint32_t size);

extern void emx_recv_array_2_0(register void *buf, register uint32_t size);

static inline void emx_recv_2_0(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_2_0(void *buf, uint32_t size) {
	while (emx_ringbuf_size_2_0() < size) emx_ringbuf_wait_0();

	emx_recv_array_2_0(buf, size);
}

void EMX_Recv_2_0(void *buf, uint32_t size);

static inline void EMX_Send32F_2_0(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_2_0(float val) {
	EMX_Send32_2_0(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_2_0() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_2_0() {
	uint32_t r = EMX_Recv32_2_0();
	return *(float*)&r;
}

static inline void EMX_Send64F_2_0(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_2_0(double val) {
	EMX_Send64_2_0(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_2_0() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_2_0() {
	uint64_t r = EMX_Recv64_2_0();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_2_0() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_2_0() {
	return EMX_Recv8_2_0();
}

static inline void EMX_SendSync_2_0(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_2_0(uint8_t sync) {
	EMX_Send8_2_0(sync);
}

static inline void EMX_Wait_2_0() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_2_0() {
	EMX_Recv8_2_0();
}

static inline void EMX_Signal_2_0() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_2_0() {
	EMX_Send8_2_0(0);
}

void EMX_Send8_2_1(register uint8_t);
uint8_t EMX_Recv8_2_1();
void EMX_Send16_2_1(register uint16_t);
uint16_t EMX_Recv16_2_1();
void EMX_Send32_2_1(register uint32_t);
uint32_t EMX_Recv32_2_1();
void EMX_Send64_2_1(register uint64_t);
uint64_t EMX_Recv64_2_1();
void emx_send_array_2_1(register const void *buf, register uint32_t size);
void emx_recv_array_2_1(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_2_1();
static inline uint32_t emx_ringbuf_size_2_1() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_2_1);
	return wr + ((wr < *emx_loc_rd_pos_2_1) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_2_1;
}

static inline uint32_t emx_ringbuf_free_2_1();
static inline uint32_t emx_ringbuf_free_2_1() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_2_1);
	return rd + ((*emx_loc_wr_pos_2_1 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_2_1 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_2_1(const register void *buf, register uint32_t size);

static inline void emx_send_2_1(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_2_1(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_2_1() < size) emx_ringbuf_wait_2();

	emx_send_array_2_1(buf, size);
}

void EMX_Send_2_1(const void *buf, uint32_t size);

extern void emx_recv_array_2_1(register void *buf, register uint32_t size);

static inline void emx_recv_2_1(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_2_1(void *buf, uint32_t size) {
	while (emx_ringbuf_size_2_1() < size) emx_ringbuf_wait_1();

	emx_recv_array_2_1(buf, size);
}

void EMX_Recv_2_1(void *buf, uint32_t size);

static inline void EMX_Send32F_2_1(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_2_1(float val) {
	EMX_Send32_2_1(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_2_1() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_2_1() {
	uint32_t r = EMX_Recv32_2_1();
	return *(float*)&r;
}

static inline void EMX_Send64F_2_1(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_2_1(double val) {
	EMX_Send64_2_1(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_2_1() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_2_1() {
	uint64_t r = EMX_Recv64_2_1();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_2_1() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_2_1() {
	return EMX_Recv8_2_1();
}

static inline void EMX_SendSync_2_1(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_2_1(uint8_t sync) {
	EMX_Send8_2_1(sync);
}

static inline void EMX_Wait_2_1() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_2_1() {
	EMX_Recv8_2_1();
}

static inline void EMX_Signal_2_1() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_2_1() {
	EMX_Send8_2_1(0);
}

void EMX_Send8_2_3(register uint8_t);
uint8_t EMX_Recv8_2_3();
void EMX_Send16_2_3(register uint16_t);
uint16_t EMX_Recv16_2_3();
void EMX_Send32_2_3(register uint32_t);
uint32_t EMX_Recv32_2_3();
void EMX_Send64_2_3(register uint64_t);
uint64_t EMX_Recv64_2_3();
void emx_send_array_2_3(register const void *buf, register uint32_t size);
void emx_recv_array_2_3(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_2_3();
static inline uint32_t emx_ringbuf_size_2_3() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_2_3);
	return wr + ((wr < *emx_loc_rd_pos_2_3) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_2_3;
}

static inline uint32_t emx_ringbuf_free_2_3();
static inline uint32_t emx_ringbuf_free_2_3() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_2_3);
	return rd + ((*emx_loc_wr_pos_2_3 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_2_3 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_2_3(const register void *buf, register uint32_t size);

static inline void emx_send_2_3(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_2_3(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_2_3() < size) emx_ringbuf_wait_2();

	emx_send_array_2_3(buf, size);
}

void EMX_Send_2_3(const void *buf, uint32_t size);

extern void emx_recv_array_2_3(register void *buf, register uint32_t size);

static inline void emx_recv_2_3(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_2_3(void *buf, uint32_t size) {
	while (emx_ringbuf_size_2_3() < size) emx_ringbuf_wait_3();

	emx_recv_array_2_3(buf, size);
}

void EMX_Recv_2_3(void *buf, uint32_t size);

static inline void EMX_Send32F_2_3(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_2_3(float val) {
	EMX_Send32_2_3(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_2_3() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_2_3() {
	uint32_t r = EMX_Recv32_2_3();
	return *(float*)&r;
}

static inline void EMX_Send64F_2_3(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_2_3(double val) {
	EMX_Send64_2_3(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_2_3() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_2_3() {
	uint64_t r = EMX_Recv64_2_3();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_2_3() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_2_3() {
	return EMX_Recv8_2_3();
}

static inline void EMX_SendSync_2_3(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_2_3(uint8_t sync) {
	EMX_Send8_2_3(sync);
}

static inline void EMX_Wait_2_3() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_2_3() {
	EMX_Recv8_2_3();
}

static inline void EMX_Signal_2_3() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_2_3() {
	EMX_Send8_2_3(0);
}

void EMX_Send8_2_4(register uint8_t);
uint8_t EMX_Recv8_2_4();
void EMX_Send16_2_4(register uint16_t);
uint16_t EMX_Recv16_2_4();
void EMX_Send32_2_4(register uint32_t);
uint32_t EMX_Recv32_2_4();
void EMX_Send64_2_4(register uint64_t);
uint64_t EMX_Recv64_2_4();
void emx_send_array_2_4(register const void *buf, register uint32_t size);
void emx_recv_array_2_4(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_2_4();
static inline uint32_t emx_ringbuf_size_2_4() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_2_4);
	return wr + ((wr < *emx_loc_rd_pos_2_4) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_2_4;
}

static inline uint32_t emx_ringbuf_free_2_4();
static inline uint32_t emx_ringbuf_free_2_4() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_2_4);
	return rd + ((*emx_loc_wr_pos_2_4 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_2_4 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_2_4(const register void *buf, register uint32_t size);

static inline void emx_send_2_4(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_2_4(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_2_4() < size) emx_ringbuf_wait_2();

	emx_send_array_2_4(buf, size);
}

void EMX_Send_2_4(const void *buf, uint32_t size);

extern void emx_recv_array_2_4(register void *buf, register uint32_t size);

static inline void emx_recv_2_4(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_2_4(void *buf, uint32_t size) {
	while (emx_ringbuf_size_2_4() < size) emx_ringbuf_wait_4();

	emx_recv_array_2_4(buf, size);
}

void EMX_Recv_2_4(void *buf, uint32_t size);

static inline void EMX_Send32F_2_4(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_2_4(float val) {
	EMX_Send32_2_4(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_2_4() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_2_4() {
	uint32_t r = EMX_Recv32_2_4();
	return *(float*)&r;
}

static inline void EMX_Send64F_2_4(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_2_4(double val) {
	EMX_Send64_2_4(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_2_4() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_2_4() {
	uint64_t r = EMX_Recv64_2_4();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_2_4() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_2_4() {
	return EMX_Recv8_2_4();
}

static inline void EMX_SendSync_2_4(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_2_4(uint8_t sync) {
	EMX_Send8_2_4(sync);
}

static inline void EMX_Wait_2_4() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_2_4() {
	EMX_Recv8_2_4();
}

static inline void EMX_Signal_2_4() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_2_4() {
	EMX_Send8_2_4(0);
}

void EMX_Send8_2_5(register uint8_t);
uint8_t EMX_Recv8_2_5();
void EMX_Send16_2_5(register uint16_t);
uint16_t EMX_Recv16_2_5();
void EMX_Send32_2_5(register uint32_t);
uint32_t EMX_Recv32_2_5();
void EMX_Send64_2_5(register uint64_t);
uint64_t EMX_Recv64_2_5();
void emx_send_array_2_5(register const void *buf, register uint32_t size);
void emx_recv_array_2_5(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_2_5();
static inline uint32_t emx_ringbuf_size_2_5() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_2_5);
	return wr + ((wr < *emx_loc_rd_pos_2_5) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_2_5;
}

static inline uint32_t emx_ringbuf_free_2_5();
static inline uint32_t emx_ringbuf_free_2_5() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_2_5);
	return rd + ((*emx_loc_wr_pos_2_5 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_2_5 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_2_5(const register void *buf, register uint32_t size);

static inline void emx_send_2_5(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_2_5(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_2_5() < size) emx_ringbuf_wait_2();

	emx_send_array_2_5(buf, size);
}

void EMX_Send_2_5(const void *buf, uint32_t size);

extern void emx_recv_array_2_5(register void *buf, register uint32_t size);

static inline void emx_recv_2_5(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_2_5(void *buf, uint32_t size) {
	while (emx_ringbuf_size_2_5() < size) emx_ringbuf_wait_5();

	emx_recv_array_2_5(buf, size);
}

void EMX_Recv_2_5(void *buf, uint32_t size);

static inline void EMX_Send32F_2_5(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_2_5(float val) {
	EMX_Send32_2_5(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_2_5() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_2_5() {
	uint32_t r = EMX_Recv32_2_5();
	return *(float*)&r;
}

static inline void EMX_Send64F_2_5(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_2_5(double val) {
	EMX_Send64_2_5(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_2_5() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_2_5() {
	uint64_t r = EMX_Recv64_2_5();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_2_5() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_2_5() {
	return EMX_Recv8_2_5();
}

static inline void EMX_SendSync_2_5(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_2_5(uint8_t sync) {
	EMX_Send8_2_5(sync);
}

static inline void EMX_Wait_2_5() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_2_5() {
	EMX_Recv8_2_5();
}

static inline void EMX_Signal_2_5() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_2_5() {
	EMX_Send8_2_5(0);
}

void EMX_Send8_2_6(register uint8_t);
uint8_t EMX_Recv8_2_6();
void EMX_Send16_2_6(register uint16_t);
uint16_t EMX_Recv16_2_6();
void EMX_Send32_2_6(register uint32_t);
uint32_t EMX_Recv32_2_6();
void EMX_Send64_2_6(register uint64_t);
uint64_t EMX_Recv64_2_6();
void emx_send_array_2_6(register const void *buf, register uint32_t size);
void emx_recv_array_2_6(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_2_6();
static inline uint32_t emx_ringbuf_size_2_6() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_2_6);
	return wr + ((wr < *emx_loc_rd_pos_2_6) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_2_6;
}

static inline uint32_t emx_ringbuf_free_2_6();
static inline uint32_t emx_ringbuf_free_2_6() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_2_6);
	return rd + ((*emx_loc_wr_pos_2_6 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_2_6 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_2_6(const register void *buf, register uint32_t size);

static inline void emx_send_2_6(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_2_6(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_2_6() < size) emx_ringbuf_wait_2();

	emx_send_array_2_6(buf, size);
}

void EMX_Send_2_6(const void *buf, uint32_t size);

extern void emx_recv_array_2_6(register void *buf, register uint32_t size);

static inline void emx_recv_2_6(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_2_6(void *buf, uint32_t size) {
	while (emx_ringbuf_size_2_6() < size) emx_ringbuf_wait_6();

	emx_recv_array_2_6(buf, size);
}

void EMX_Recv_2_6(void *buf, uint32_t size);

static inline void EMX_Send32F_2_6(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_2_6(float val) {
	EMX_Send32_2_6(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_2_6() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_2_6() {
	uint32_t r = EMX_Recv32_2_6();
	return *(float*)&r;
}

static inline void EMX_Send64F_2_6(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_2_6(double val) {
	EMX_Send64_2_6(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_2_6() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_2_6() {
	uint64_t r = EMX_Recv64_2_6();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_2_6() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_2_6() {
	return EMX_Recv8_2_6();
}

static inline void EMX_SendSync_2_6(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_2_6(uint8_t sync) {
	EMX_Send8_2_6(sync);
}

static inline void EMX_Wait_2_6() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_2_6() {
	EMX_Recv8_2_6();
}

static inline void EMX_Signal_2_6() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_2_6() {
	EMX_Send8_2_6(0);
}

void EMX_Send8_2_7(register uint8_t);
uint8_t EMX_Recv8_2_7();
void EMX_Send16_2_7(register uint16_t);
uint16_t EMX_Recv16_2_7();
void EMX_Send32_2_7(register uint32_t);
uint32_t EMX_Recv32_2_7();
void EMX_Send64_2_7(register uint64_t);
uint64_t EMX_Recv64_2_7();
void emx_send_array_2_7(register const void *buf, register uint32_t size);
void emx_recv_array_2_7(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_2_7();
static inline uint32_t emx_ringbuf_size_2_7() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_2_7);
	return wr + ((wr < *emx_loc_rd_pos_2_7) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_2_7;
}

static inline uint32_t emx_ringbuf_free_2_7();
static inline uint32_t emx_ringbuf_free_2_7() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_2_7);
	return rd + ((*emx_loc_wr_pos_2_7 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_2_7 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_2_7(const register void *buf, register uint32_t size);

static inline void emx_send_2_7(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_2_7(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_2_7() < size) emx_ringbuf_wait_2();

	emx_send_array_2_7(buf, size);
}

void EMX_Send_2_7(const void *buf, uint32_t size);

extern void emx_recv_array_2_7(register void *buf, register uint32_t size);

static inline void emx_recv_2_7(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_2_7(void *buf, uint32_t size) {
	while (emx_ringbuf_size_2_7() < size) emx_ringbuf_wait_7();

	emx_recv_array_2_7(buf, size);
}

void EMX_Recv_2_7(void *buf, uint32_t size);

static inline void EMX_Send32F_2_7(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_2_7(float val) {
	EMX_Send32_2_7(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_2_7() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_2_7() {
	uint32_t r = EMX_Recv32_2_7();
	return *(float*)&r;
}

static inline void EMX_Send64F_2_7(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_2_7(double val) {
	EMX_Send64_2_7(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_2_7() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_2_7() {
	uint64_t r = EMX_Recv64_2_7();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_2_7() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_2_7() {
	return EMX_Recv8_2_7();
}

static inline void EMX_SendSync_2_7(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_2_7(uint8_t sync) {
	EMX_Send8_2_7(sync);
}

static inline void EMX_Wait_2_7() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_2_7() {
	EMX_Recv8_2_7();
}

static inline void EMX_Signal_2_7() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_2_7() {
	EMX_Send8_2_7(0);
}

void emx_ringbuf_wait_3();

void EMX_Send8_3_0(register uint8_t);
uint8_t EMX_Recv8_3_0();
void EMX_Send16_3_0(register uint16_t);
uint16_t EMX_Recv16_3_0();
void EMX_Send32_3_0(register uint32_t);
uint32_t EMX_Recv32_3_0();
void EMX_Send64_3_0(register uint64_t);
uint64_t EMX_Recv64_3_0();
void emx_send_array_3_0(register const void *buf, register uint32_t size);
void emx_recv_array_3_0(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_3_0();
static inline uint32_t emx_ringbuf_size_3_0() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_3_0);
	return wr + ((wr < *emx_loc_rd_pos_3_0) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_3_0;
}

static inline uint32_t emx_ringbuf_free_3_0();
static inline uint32_t emx_ringbuf_free_3_0() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_3_0);
	return rd + ((*emx_loc_wr_pos_3_0 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_3_0 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_3_0(const register void *buf, register uint32_t size);

static inline void emx_send_3_0(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_3_0(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_3_0() < size) emx_ringbuf_wait_3();

	emx_send_array_3_0(buf, size);
}

void EMX_Send_3_0(const void *buf, uint32_t size);

extern void emx_recv_array_3_0(register void *buf, register uint32_t size);

static inline void emx_recv_3_0(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_3_0(void *buf, uint32_t size) {
	while (emx_ringbuf_size_3_0() < size) emx_ringbuf_wait_0();

	emx_recv_array_3_0(buf, size);
}

void EMX_Recv_3_0(void *buf, uint32_t size);

static inline void EMX_Send32F_3_0(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_3_0(float val) {
	EMX_Send32_3_0(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_3_0() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_3_0() {
	uint32_t r = EMX_Recv32_3_0();
	return *(float*)&r;
}

static inline void EMX_Send64F_3_0(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_3_0(double val) {
	EMX_Send64_3_0(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_3_0() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_3_0() {
	uint64_t r = EMX_Recv64_3_0();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_3_0() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_3_0() {
	return EMX_Recv8_3_0();
}

static inline void EMX_SendSync_3_0(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_3_0(uint8_t sync) {
	EMX_Send8_3_0(sync);
}

static inline void EMX_Wait_3_0() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_3_0() {
	EMX_Recv8_3_0();
}

static inline void EMX_Signal_3_0() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_3_0() {
	EMX_Send8_3_0(0);
}

void EMX_Send8_3_1(register uint8_t);
uint8_t EMX_Recv8_3_1();
void EMX_Send16_3_1(register uint16_t);
uint16_t EMX_Recv16_3_1();
void EMX_Send32_3_1(register uint32_t);
uint32_t EMX_Recv32_3_1();
void EMX_Send64_3_1(register uint64_t);
uint64_t EMX_Recv64_3_1();
void emx_send_array_3_1(register const void *buf, register uint32_t size);
void emx_recv_array_3_1(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_3_1();
static inline uint32_t emx_ringbuf_size_3_1() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_3_1);
	return wr + ((wr < *emx_loc_rd_pos_3_1) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_3_1;
}

static inline uint32_t emx_ringbuf_free_3_1();
static inline uint32_t emx_ringbuf_free_3_1() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_3_1);
	return rd + ((*emx_loc_wr_pos_3_1 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_3_1 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_3_1(const register void *buf, register uint32_t size);

static inline void emx_send_3_1(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_3_1(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_3_1() < size) emx_ringbuf_wait_3();

	emx_send_array_3_1(buf, size);
}

void EMX_Send_3_1(const void *buf, uint32_t size);

extern void emx_recv_array_3_1(register void *buf, register uint32_t size);

static inline void emx_recv_3_1(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_3_1(void *buf, uint32_t size) {
	while (emx_ringbuf_size_3_1() < size) emx_ringbuf_wait_1();

	emx_recv_array_3_1(buf, size);
}

void EMX_Recv_3_1(void *buf, uint32_t size);

static inline void EMX_Send32F_3_1(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_3_1(float val) {
	EMX_Send32_3_1(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_3_1() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_3_1() {
	uint32_t r = EMX_Recv32_3_1();
	return *(float*)&r;
}

static inline void EMX_Send64F_3_1(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_3_1(double val) {
	EMX_Send64_3_1(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_3_1() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_3_1() {
	uint64_t r = EMX_Recv64_3_1();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_3_1() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_3_1() {
	return EMX_Recv8_3_1();
}

static inline void EMX_SendSync_3_1(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_3_1(uint8_t sync) {
	EMX_Send8_3_1(sync);
}

static inline void EMX_Wait_3_1() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_3_1() {
	EMX_Recv8_3_1();
}

static inline void EMX_Signal_3_1() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_3_1() {
	EMX_Send8_3_1(0);
}

void EMX_Send8_3_2(register uint8_t);
uint8_t EMX_Recv8_3_2();
void EMX_Send16_3_2(register uint16_t);
uint16_t EMX_Recv16_3_2();
void EMX_Send32_3_2(register uint32_t);
uint32_t EMX_Recv32_3_2();
void EMX_Send64_3_2(register uint64_t);
uint64_t EMX_Recv64_3_2();
void emx_send_array_3_2(register const void *buf, register uint32_t size);
void emx_recv_array_3_2(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_3_2();
static inline uint32_t emx_ringbuf_size_3_2() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_3_2);
	return wr + ((wr < *emx_loc_rd_pos_3_2) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_3_2;
}

static inline uint32_t emx_ringbuf_free_3_2();
static inline uint32_t emx_ringbuf_free_3_2() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_3_2);
	return rd + ((*emx_loc_wr_pos_3_2 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_3_2 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_3_2(const register void *buf, register uint32_t size);

static inline void emx_send_3_2(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_3_2(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_3_2() < size) emx_ringbuf_wait_3();

	emx_send_array_3_2(buf, size);
}

void EMX_Send_3_2(const void *buf, uint32_t size);

extern void emx_recv_array_3_2(register void *buf, register uint32_t size);

static inline void emx_recv_3_2(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_3_2(void *buf, uint32_t size) {
	while (emx_ringbuf_size_3_2() < size) emx_ringbuf_wait_2();

	emx_recv_array_3_2(buf, size);
}

void EMX_Recv_3_2(void *buf, uint32_t size);

static inline void EMX_Send32F_3_2(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_3_2(float val) {
	EMX_Send32_3_2(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_3_2() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_3_2() {
	uint32_t r = EMX_Recv32_3_2();
	return *(float*)&r;
}

static inline void EMX_Send64F_3_2(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_3_2(double val) {
	EMX_Send64_3_2(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_3_2() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_3_2() {
	uint64_t r = EMX_Recv64_3_2();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_3_2() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_3_2() {
	return EMX_Recv8_3_2();
}

static inline void EMX_SendSync_3_2(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_3_2(uint8_t sync) {
	EMX_Send8_3_2(sync);
}

static inline void EMX_Wait_3_2() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_3_2() {
	EMX_Recv8_3_2();
}

static inline void EMX_Signal_3_2() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_3_2() {
	EMX_Send8_3_2(0);
}

void EMX_Send8_3_4(register uint8_t);
uint8_t EMX_Recv8_3_4();
void EMX_Send16_3_4(register uint16_t);
uint16_t EMX_Recv16_3_4();
void EMX_Send32_3_4(register uint32_t);
uint32_t EMX_Recv32_3_4();
void EMX_Send64_3_4(register uint64_t);
uint64_t EMX_Recv64_3_4();
void emx_send_array_3_4(register const void *buf, register uint32_t size);
void emx_recv_array_3_4(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_3_4();
static inline uint32_t emx_ringbuf_size_3_4() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_3_4);
	return wr + ((wr < *emx_loc_rd_pos_3_4) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_3_4;
}

static inline uint32_t emx_ringbuf_free_3_4();
static inline uint32_t emx_ringbuf_free_3_4() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_3_4);
	return rd + ((*emx_loc_wr_pos_3_4 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_3_4 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_3_4(const register void *buf, register uint32_t size);

static inline void emx_send_3_4(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_3_4(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_3_4() < size) emx_ringbuf_wait_3();

	emx_send_array_3_4(buf, size);
}

void EMX_Send_3_4(const void *buf, uint32_t size);

extern void emx_recv_array_3_4(register void *buf, register uint32_t size);

static inline void emx_recv_3_4(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_3_4(void *buf, uint32_t size) {
	while (emx_ringbuf_size_3_4() < size) emx_ringbuf_wait_4();

	emx_recv_array_3_4(buf, size);
}

void EMX_Recv_3_4(void *buf, uint32_t size);

static inline void EMX_Send32F_3_4(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_3_4(float val) {
	EMX_Send32_3_4(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_3_4() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_3_4() {
	uint32_t r = EMX_Recv32_3_4();
	return *(float*)&r;
}

static inline void EMX_Send64F_3_4(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_3_4(double val) {
	EMX_Send64_3_4(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_3_4() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_3_4() {
	uint64_t r = EMX_Recv64_3_4();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_3_4() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_3_4() {
	return EMX_Recv8_3_4();
}

static inline void EMX_SendSync_3_4(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_3_4(uint8_t sync) {
	EMX_Send8_3_4(sync);
}

static inline void EMX_Wait_3_4() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_3_4() {
	EMX_Recv8_3_4();
}

static inline void EMX_Signal_3_4() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_3_4() {
	EMX_Send8_3_4(0);
}

void EMX_Send8_3_5(register uint8_t);
uint8_t EMX_Recv8_3_5();
void EMX_Send16_3_5(register uint16_t);
uint16_t EMX_Recv16_3_5();
void EMX_Send32_3_5(register uint32_t);
uint32_t EMX_Recv32_3_5();
void EMX_Send64_3_5(register uint64_t);
uint64_t EMX_Recv64_3_5();
void emx_send_array_3_5(register const void *buf, register uint32_t size);
void emx_recv_array_3_5(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_3_5();
static inline uint32_t emx_ringbuf_size_3_5() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_3_5);
	return wr + ((wr < *emx_loc_rd_pos_3_5) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_3_5;
}

static inline uint32_t emx_ringbuf_free_3_5();
static inline uint32_t emx_ringbuf_free_3_5() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_3_5);
	return rd + ((*emx_loc_wr_pos_3_5 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_3_5 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_3_5(const register void *buf, register uint32_t size);

static inline void emx_send_3_5(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_3_5(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_3_5() < size) emx_ringbuf_wait_3();

	emx_send_array_3_5(buf, size);
}

void EMX_Send_3_5(const void *buf, uint32_t size);

extern void emx_recv_array_3_5(register void *buf, register uint32_t size);

static inline void emx_recv_3_5(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_3_5(void *buf, uint32_t size) {
	while (emx_ringbuf_size_3_5() < size) emx_ringbuf_wait_5();

	emx_recv_array_3_5(buf, size);
}

void EMX_Recv_3_5(void *buf, uint32_t size);

static inline void EMX_Send32F_3_5(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_3_5(float val) {
	EMX_Send32_3_5(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_3_5() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_3_5() {
	uint32_t r = EMX_Recv32_3_5();
	return *(float*)&r;
}

static inline void EMX_Send64F_3_5(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_3_5(double val) {
	EMX_Send64_3_5(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_3_5() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_3_5() {
	uint64_t r = EMX_Recv64_3_5();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_3_5() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_3_5() {
	return EMX_Recv8_3_5();
}

static inline void EMX_SendSync_3_5(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_3_5(uint8_t sync) {
	EMX_Send8_3_5(sync);
}

static inline void EMX_Wait_3_5() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_3_5() {
	EMX_Recv8_3_5();
}

static inline void EMX_Signal_3_5() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_3_5() {
	EMX_Send8_3_5(0);
}

void EMX_Send8_3_6(register uint8_t);
uint8_t EMX_Recv8_3_6();
void EMX_Send16_3_6(register uint16_t);
uint16_t EMX_Recv16_3_6();
void EMX_Send32_3_6(register uint32_t);
uint32_t EMX_Recv32_3_6();
void EMX_Send64_3_6(register uint64_t);
uint64_t EMX_Recv64_3_6();
void emx_send_array_3_6(register const void *buf, register uint32_t size);
void emx_recv_array_3_6(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_3_6();
static inline uint32_t emx_ringbuf_size_3_6() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_3_6);
	return wr + ((wr < *emx_loc_rd_pos_3_6) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_3_6;
}

static inline uint32_t emx_ringbuf_free_3_6();
static inline uint32_t emx_ringbuf_free_3_6() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_3_6);
	return rd + ((*emx_loc_wr_pos_3_6 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_3_6 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_3_6(const register void *buf, register uint32_t size);

static inline void emx_send_3_6(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_3_6(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_3_6() < size) emx_ringbuf_wait_3();

	emx_send_array_3_6(buf, size);
}

void EMX_Send_3_6(const void *buf, uint32_t size);

extern void emx_recv_array_3_6(register void *buf, register uint32_t size);

static inline void emx_recv_3_6(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_3_6(void *buf, uint32_t size) {
	while (emx_ringbuf_size_3_6() < size) emx_ringbuf_wait_6();

	emx_recv_array_3_6(buf, size);
}

void EMX_Recv_3_6(void *buf, uint32_t size);

static inline void EMX_Send32F_3_6(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_3_6(float val) {
	EMX_Send32_3_6(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_3_6() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_3_6() {
	uint32_t r = EMX_Recv32_3_6();
	return *(float*)&r;
}

static inline void EMX_Send64F_3_6(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_3_6(double val) {
	EMX_Send64_3_6(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_3_6() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_3_6() {
	uint64_t r = EMX_Recv64_3_6();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_3_6() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_3_6() {
	return EMX_Recv8_3_6();
}

static inline void EMX_SendSync_3_6(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_3_6(uint8_t sync) {
	EMX_Send8_3_6(sync);
}

static inline void EMX_Wait_3_6() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_3_6() {
	EMX_Recv8_3_6();
}

static inline void EMX_Signal_3_6() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_3_6() {
	EMX_Send8_3_6(0);
}

void EMX_Send8_3_7(register uint8_t);
uint8_t EMX_Recv8_3_7();
void EMX_Send16_3_7(register uint16_t);
uint16_t EMX_Recv16_3_7();
void EMX_Send32_3_7(register uint32_t);
uint32_t EMX_Recv32_3_7();
void EMX_Send64_3_7(register uint64_t);
uint64_t EMX_Recv64_3_7();
void emx_send_array_3_7(register const void *buf, register uint32_t size);
void emx_recv_array_3_7(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_3_7();
static inline uint32_t emx_ringbuf_size_3_7() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_3_7);
	return wr + ((wr < *emx_loc_rd_pos_3_7) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_3_7;
}

static inline uint32_t emx_ringbuf_free_3_7();
static inline uint32_t emx_ringbuf_free_3_7() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_3_7);
	return rd + ((*emx_loc_wr_pos_3_7 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_3_7 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_3_7(const register void *buf, register uint32_t size);

static inline void emx_send_3_7(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_3_7(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_3_7() < size) emx_ringbuf_wait_3();

	emx_send_array_3_7(buf, size);
}

void EMX_Send_3_7(const void *buf, uint32_t size);

extern void emx_recv_array_3_7(register void *buf, register uint32_t size);

static inline void emx_recv_3_7(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_3_7(void *buf, uint32_t size) {
	while (emx_ringbuf_size_3_7() < size) emx_ringbuf_wait_7();

	emx_recv_array_3_7(buf, size);
}

void EMX_Recv_3_7(void *buf, uint32_t size);

static inline void EMX_Send32F_3_7(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_3_7(float val) {
	EMX_Send32_3_7(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_3_7() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_3_7() {
	uint32_t r = EMX_Recv32_3_7();
	return *(float*)&r;
}

static inline void EMX_Send64F_3_7(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_3_7(double val) {
	EMX_Send64_3_7(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_3_7() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_3_7() {
	uint64_t r = EMX_Recv64_3_7();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_3_7() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_3_7() {
	return EMX_Recv8_3_7();
}

static inline void EMX_SendSync_3_7(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_3_7(uint8_t sync) {
	EMX_Send8_3_7(sync);
}

static inline void EMX_Wait_3_7() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_3_7() {
	EMX_Recv8_3_7();
}

static inline void EMX_Signal_3_7() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_3_7() {
	EMX_Send8_3_7(0);
}

void emx_ringbuf_wait_4();

void EMX_Send8_4_0(register uint8_t);
uint8_t EMX_Recv8_4_0();
void EMX_Send16_4_0(register uint16_t);
uint16_t EMX_Recv16_4_0();
void EMX_Send32_4_0(register uint32_t);
uint32_t EMX_Recv32_4_0();
void EMX_Send64_4_0(register uint64_t);
uint64_t EMX_Recv64_4_0();
void emx_send_array_4_0(register const void *buf, register uint32_t size);
void emx_recv_array_4_0(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_4_0();
static inline uint32_t emx_ringbuf_size_4_0() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_4_0);
	return wr + ((wr < *emx_loc_rd_pos_4_0) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_4_0;
}

static inline uint32_t emx_ringbuf_free_4_0();
static inline uint32_t emx_ringbuf_free_4_0() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_4_0);
	return rd + ((*emx_loc_wr_pos_4_0 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_4_0 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_4_0(const register void *buf, register uint32_t size);

static inline void emx_send_4_0(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_4_0(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_4_0() < size) emx_ringbuf_wait_4();

	emx_send_array_4_0(buf, size);
}

void EMX_Send_4_0(const void *buf, uint32_t size);

extern void emx_recv_array_4_0(register void *buf, register uint32_t size);

static inline void emx_recv_4_0(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_4_0(void *buf, uint32_t size) {
	while (emx_ringbuf_size_4_0() < size) emx_ringbuf_wait_0();

	emx_recv_array_4_0(buf, size);
}

void EMX_Recv_4_0(void *buf, uint32_t size);

static inline void EMX_Send32F_4_0(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_4_0(float val) {
	EMX_Send32_4_0(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_4_0() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_4_0() {
	uint32_t r = EMX_Recv32_4_0();
	return *(float*)&r;
}

static inline void EMX_Send64F_4_0(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_4_0(double val) {
	EMX_Send64_4_0(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_4_0() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_4_0() {
	uint64_t r = EMX_Recv64_4_0();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_4_0() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_4_0() {
	return EMX_Recv8_4_0();
}

static inline void EMX_SendSync_4_0(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_4_0(uint8_t sync) {
	EMX_Send8_4_0(sync);
}

static inline void EMX_Wait_4_0() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_4_0() {
	EMX_Recv8_4_0();
}

static inline void EMX_Signal_4_0() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_4_0() {
	EMX_Send8_4_0(0);
}

void EMX_Send8_4_1(register uint8_t);
uint8_t EMX_Recv8_4_1();
void EMX_Send16_4_1(register uint16_t);
uint16_t EMX_Recv16_4_1();
void EMX_Send32_4_1(register uint32_t);
uint32_t EMX_Recv32_4_1();
void EMX_Send64_4_1(register uint64_t);
uint64_t EMX_Recv64_4_1();
void emx_send_array_4_1(register const void *buf, register uint32_t size);
void emx_recv_array_4_1(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_4_1();
static inline uint32_t emx_ringbuf_size_4_1() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_4_1);
	return wr + ((wr < *emx_loc_rd_pos_4_1) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_4_1;
}

static inline uint32_t emx_ringbuf_free_4_1();
static inline uint32_t emx_ringbuf_free_4_1() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_4_1);
	return rd + ((*emx_loc_wr_pos_4_1 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_4_1 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_4_1(const register void *buf, register uint32_t size);

static inline void emx_send_4_1(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_4_1(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_4_1() < size) emx_ringbuf_wait_4();

	emx_send_array_4_1(buf, size);
}

void EMX_Send_4_1(const void *buf, uint32_t size);

extern void emx_recv_array_4_1(register void *buf, register uint32_t size);

static inline void emx_recv_4_1(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_4_1(void *buf, uint32_t size) {
	while (emx_ringbuf_size_4_1() < size) emx_ringbuf_wait_1();

	emx_recv_array_4_1(buf, size);
}

void EMX_Recv_4_1(void *buf, uint32_t size);

static inline void EMX_Send32F_4_1(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_4_1(float val) {
	EMX_Send32_4_1(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_4_1() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_4_1() {
	uint32_t r = EMX_Recv32_4_1();
	return *(float*)&r;
}

static inline void EMX_Send64F_4_1(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_4_1(double val) {
	EMX_Send64_4_1(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_4_1() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_4_1() {
	uint64_t r = EMX_Recv64_4_1();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_4_1() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_4_1() {
	return EMX_Recv8_4_1();
}

static inline void EMX_SendSync_4_1(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_4_1(uint8_t sync) {
	EMX_Send8_4_1(sync);
}

static inline void EMX_Wait_4_1() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_4_1() {
	EMX_Recv8_4_1();
}

static inline void EMX_Signal_4_1() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_4_1() {
	EMX_Send8_4_1(0);
}

void EMX_Send8_4_2(register uint8_t);
uint8_t EMX_Recv8_4_2();
void EMX_Send16_4_2(register uint16_t);
uint16_t EMX_Recv16_4_2();
void EMX_Send32_4_2(register uint32_t);
uint32_t EMX_Recv32_4_2();
void EMX_Send64_4_2(register uint64_t);
uint64_t EMX_Recv64_4_2();
void emx_send_array_4_2(register const void *buf, register uint32_t size);
void emx_recv_array_4_2(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_4_2();
static inline uint32_t emx_ringbuf_size_4_2() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_4_2);
	return wr + ((wr < *emx_loc_rd_pos_4_2) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_4_2;
}

static inline uint32_t emx_ringbuf_free_4_2();
static inline uint32_t emx_ringbuf_free_4_2() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_4_2);
	return rd + ((*emx_loc_wr_pos_4_2 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_4_2 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_4_2(const register void *buf, register uint32_t size);

static inline void emx_send_4_2(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_4_2(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_4_2() < size) emx_ringbuf_wait_4();

	emx_send_array_4_2(buf, size);
}

void EMX_Send_4_2(const void *buf, uint32_t size);

extern void emx_recv_array_4_2(register void *buf, register uint32_t size);

static inline void emx_recv_4_2(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_4_2(void *buf, uint32_t size) {
	while (emx_ringbuf_size_4_2() < size) emx_ringbuf_wait_2();

	emx_recv_array_4_2(buf, size);
}

void EMX_Recv_4_2(void *buf, uint32_t size);

static inline void EMX_Send32F_4_2(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_4_2(float val) {
	EMX_Send32_4_2(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_4_2() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_4_2() {
	uint32_t r = EMX_Recv32_4_2();
	return *(float*)&r;
}

static inline void EMX_Send64F_4_2(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_4_2(double val) {
	EMX_Send64_4_2(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_4_2() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_4_2() {
	uint64_t r = EMX_Recv64_4_2();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_4_2() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_4_2() {
	return EMX_Recv8_4_2();
}

static inline void EMX_SendSync_4_2(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_4_2(uint8_t sync) {
	EMX_Send8_4_2(sync);
}

static inline void EMX_Wait_4_2() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_4_2() {
	EMX_Recv8_4_2();
}

static inline void EMX_Signal_4_2() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_4_2() {
	EMX_Send8_4_2(0);
}

void EMX_Send8_4_3(register uint8_t);
uint8_t EMX_Recv8_4_3();
void EMX_Send16_4_3(register uint16_t);
uint16_t EMX_Recv16_4_3();
void EMX_Send32_4_3(register uint32_t);
uint32_t EMX_Recv32_4_3();
void EMX_Send64_4_3(register uint64_t);
uint64_t EMX_Recv64_4_3();
void emx_send_array_4_3(register const void *buf, register uint32_t size);
void emx_recv_array_4_3(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_4_3();
static inline uint32_t emx_ringbuf_size_4_3() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_4_3);
	return wr + ((wr < *emx_loc_rd_pos_4_3) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_4_3;
}

static inline uint32_t emx_ringbuf_free_4_3();
static inline uint32_t emx_ringbuf_free_4_3() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_4_3);
	return rd + ((*emx_loc_wr_pos_4_3 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_4_3 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_4_3(const register void *buf, register uint32_t size);

static inline void emx_send_4_3(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_4_3(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_4_3() < size) emx_ringbuf_wait_4();

	emx_send_array_4_3(buf, size);
}

void EMX_Send_4_3(const void *buf, uint32_t size);

extern void emx_recv_array_4_3(register void *buf, register uint32_t size);

static inline void emx_recv_4_3(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_4_3(void *buf, uint32_t size) {
	while (emx_ringbuf_size_4_3() < size) emx_ringbuf_wait_3();

	emx_recv_array_4_3(buf, size);
}

void EMX_Recv_4_3(void *buf, uint32_t size);

static inline void EMX_Send32F_4_3(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_4_3(float val) {
	EMX_Send32_4_3(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_4_3() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_4_3() {
	uint32_t r = EMX_Recv32_4_3();
	return *(float*)&r;
}

static inline void EMX_Send64F_4_3(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_4_3(double val) {
	EMX_Send64_4_3(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_4_3() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_4_3() {
	uint64_t r = EMX_Recv64_4_3();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_4_3() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_4_3() {
	return EMX_Recv8_4_3();
}

static inline void EMX_SendSync_4_3(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_4_3(uint8_t sync) {
	EMX_Send8_4_3(sync);
}

static inline void EMX_Wait_4_3() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_4_3() {
	EMX_Recv8_4_3();
}

static inline void EMX_Signal_4_3() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_4_3() {
	EMX_Send8_4_3(0);
}

void EMX_Send8_4_5(register uint8_t);
uint8_t EMX_Recv8_4_5();
void EMX_Send16_4_5(register uint16_t);
uint16_t EMX_Recv16_4_5();
void EMX_Send32_4_5(register uint32_t);
uint32_t EMX_Recv32_4_5();
void EMX_Send64_4_5(register uint64_t);
uint64_t EMX_Recv64_4_5();
void emx_send_array_4_5(register const void *buf, register uint32_t size);
void emx_recv_array_4_5(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_4_5();
static inline uint32_t emx_ringbuf_size_4_5() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_4_5);
	return wr + ((wr < *emx_loc_rd_pos_4_5) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_4_5;
}

static inline uint32_t emx_ringbuf_free_4_5();
static inline uint32_t emx_ringbuf_free_4_5() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_4_5);
	return rd + ((*emx_loc_wr_pos_4_5 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_4_5 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_4_5(const register void *buf, register uint32_t size);

static inline void emx_send_4_5(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_4_5(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_4_5() < size) emx_ringbuf_wait_4();

	emx_send_array_4_5(buf, size);
}

void EMX_Send_4_5(const void *buf, uint32_t size);

extern void emx_recv_array_4_5(register void *buf, register uint32_t size);

static inline void emx_recv_4_5(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_4_5(void *buf, uint32_t size) {
	while (emx_ringbuf_size_4_5() < size) emx_ringbuf_wait_5();

	emx_recv_array_4_5(buf, size);
}

void EMX_Recv_4_5(void *buf, uint32_t size);

static inline void EMX_Send32F_4_5(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_4_5(float val) {
	EMX_Send32_4_5(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_4_5() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_4_5() {
	uint32_t r = EMX_Recv32_4_5();
	return *(float*)&r;
}

static inline void EMX_Send64F_4_5(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_4_5(double val) {
	EMX_Send64_4_5(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_4_5() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_4_5() {
	uint64_t r = EMX_Recv64_4_5();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_4_5() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_4_5() {
	return EMX_Recv8_4_5();
}

static inline void EMX_SendSync_4_5(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_4_5(uint8_t sync) {
	EMX_Send8_4_5(sync);
}

static inline void EMX_Wait_4_5() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_4_5() {
	EMX_Recv8_4_5();
}

static inline void EMX_Signal_4_5() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_4_5() {
	EMX_Send8_4_5(0);
}

void EMX_Send8_4_6(register uint8_t);
uint8_t EMX_Recv8_4_6();
void EMX_Send16_4_6(register uint16_t);
uint16_t EMX_Recv16_4_6();
void EMX_Send32_4_6(register uint32_t);
uint32_t EMX_Recv32_4_6();
void EMX_Send64_4_6(register uint64_t);
uint64_t EMX_Recv64_4_6();
void emx_send_array_4_6(register const void *buf, register uint32_t size);
void emx_recv_array_4_6(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_4_6();
static inline uint32_t emx_ringbuf_size_4_6() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_4_6);
	return wr + ((wr < *emx_loc_rd_pos_4_6) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_4_6;
}

static inline uint32_t emx_ringbuf_free_4_6();
static inline uint32_t emx_ringbuf_free_4_6() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_4_6);
	return rd + ((*emx_loc_wr_pos_4_6 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_4_6 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_4_6(const register void *buf, register uint32_t size);

static inline void emx_send_4_6(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_4_6(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_4_6() < size) emx_ringbuf_wait_4();

	emx_send_array_4_6(buf, size);
}

void EMX_Send_4_6(const void *buf, uint32_t size);

extern void emx_recv_array_4_6(register void *buf, register uint32_t size);

static inline void emx_recv_4_6(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_4_6(void *buf, uint32_t size) {
	while (emx_ringbuf_size_4_6() < size) emx_ringbuf_wait_6();

	emx_recv_array_4_6(buf, size);
}

void EMX_Recv_4_6(void *buf, uint32_t size);

static inline void EMX_Send32F_4_6(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_4_6(float val) {
	EMX_Send32_4_6(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_4_6() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_4_6() {
	uint32_t r = EMX_Recv32_4_6();
	return *(float*)&r;
}

static inline void EMX_Send64F_4_6(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_4_6(double val) {
	EMX_Send64_4_6(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_4_6() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_4_6() {
	uint64_t r = EMX_Recv64_4_6();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_4_6() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_4_6() {
	return EMX_Recv8_4_6();
}

static inline void EMX_SendSync_4_6(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_4_6(uint8_t sync) {
	EMX_Send8_4_6(sync);
}

static inline void EMX_Wait_4_6() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_4_6() {
	EMX_Recv8_4_6();
}

static inline void EMX_Signal_4_6() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_4_6() {
	EMX_Send8_4_6(0);
}

void EMX_Send8_4_7(register uint8_t);
uint8_t EMX_Recv8_4_7();
void EMX_Send16_4_7(register uint16_t);
uint16_t EMX_Recv16_4_7();
void EMX_Send32_4_7(register uint32_t);
uint32_t EMX_Recv32_4_7();
void EMX_Send64_4_7(register uint64_t);
uint64_t EMX_Recv64_4_7();
void emx_send_array_4_7(register const void *buf, register uint32_t size);
void emx_recv_array_4_7(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_4_7();
static inline uint32_t emx_ringbuf_size_4_7() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_4_7);
	return wr + ((wr < *emx_loc_rd_pos_4_7) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_4_7;
}

static inline uint32_t emx_ringbuf_free_4_7();
static inline uint32_t emx_ringbuf_free_4_7() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_4_7);
	return rd + ((*emx_loc_wr_pos_4_7 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_4_7 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_4_7(const register void *buf, register uint32_t size);

static inline void emx_send_4_7(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_4_7(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_4_7() < size) emx_ringbuf_wait_4();

	emx_send_array_4_7(buf, size);
}

void EMX_Send_4_7(const void *buf, uint32_t size);

extern void emx_recv_array_4_7(register void *buf, register uint32_t size);

static inline void emx_recv_4_7(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_4_7(void *buf, uint32_t size) {
	while (emx_ringbuf_size_4_7() < size) emx_ringbuf_wait_7();

	emx_recv_array_4_7(buf, size);
}

void EMX_Recv_4_7(void *buf, uint32_t size);

static inline void EMX_Send32F_4_7(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_4_7(float val) {
	EMX_Send32_4_7(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_4_7() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_4_7() {
	uint32_t r = EMX_Recv32_4_7();
	return *(float*)&r;
}

static inline void EMX_Send64F_4_7(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_4_7(double val) {
	EMX_Send64_4_7(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_4_7() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_4_7() {
	uint64_t r = EMX_Recv64_4_7();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_4_7() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_4_7() {
	return EMX_Recv8_4_7();
}

static inline void EMX_SendSync_4_7(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_4_7(uint8_t sync) {
	EMX_Send8_4_7(sync);
}

static inline void EMX_Wait_4_7() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_4_7() {
	EMX_Recv8_4_7();
}

static inline void EMX_Signal_4_7() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_4_7() {
	EMX_Send8_4_7(0);
}

void emx_ringbuf_wait_5();

void EMX_Send8_5_0(register uint8_t);
uint8_t EMX_Recv8_5_0();
void EMX_Send16_5_0(register uint16_t);
uint16_t EMX_Recv16_5_0();
void EMX_Send32_5_0(register uint32_t);
uint32_t EMX_Recv32_5_0();
void EMX_Send64_5_0(register uint64_t);
uint64_t EMX_Recv64_5_0();
void emx_send_array_5_0(register const void *buf, register uint32_t size);
void emx_recv_array_5_0(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_5_0();
static inline uint32_t emx_ringbuf_size_5_0() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_5_0);
	return wr + ((wr < *emx_loc_rd_pos_5_0) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_5_0;
}

static inline uint32_t emx_ringbuf_free_5_0();
static inline uint32_t emx_ringbuf_free_5_0() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_5_0);
	return rd + ((*emx_loc_wr_pos_5_0 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_5_0 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_5_0(const register void *buf, register uint32_t size);

static inline void emx_send_5_0(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_5_0(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_5_0() < size) emx_ringbuf_wait_5();

	emx_send_array_5_0(buf, size);
}

void EMX_Send_5_0(const void *buf, uint32_t size);

extern void emx_recv_array_5_0(register void *buf, register uint32_t size);

static inline void emx_recv_5_0(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_5_0(void *buf, uint32_t size) {
	while (emx_ringbuf_size_5_0() < size) emx_ringbuf_wait_0();

	emx_recv_array_5_0(buf, size);
}

void EMX_Recv_5_0(void *buf, uint32_t size);

static inline void EMX_Send32F_5_0(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_5_0(float val) {
	EMX_Send32_5_0(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_5_0() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_5_0() {
	uint32_t r = EMX_Recv32_5_0();
	return *(float*)&r;
}

static inline void EMX_Send64F_5_0(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_5_0(double val) {
	EMX_Send64_5_0(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_5_0() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_5_0() {
	uint64_t r = EMX_Recv64_5_0();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_5_0() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_5_0() {
	return EMX_Recv8_5_0();
}

static inline void EMX_SendSync_5_0(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_5_0(uint8_t sync) {
	EMX_Send8_5_0(sync);
}

static inline void EMX_Wait_5_0() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_5_0() {
	EMX_Recv8_5_0();
}

static inline void EMX_Signal_5_0() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_5_0() {
	EMX_Send8_5_0(0);
}

void EMX_Send8_5_1(register uint8_t);
uint8_t EMX_Recv8_5_1();
void EMX_Send16_5_1(register uint16_t);
uint16_t EMX_Recv16_5_1();
void EMX_Send32_5_1(register uint32_t);
uint32_t EMX_Recv32_5_1();
void EMX_Send64_5_1(register uint64_t);
uint64_t EMX_Recv64_5_1();
void emx_send_array_5_1(register const void *buf, register uint32_t size);
void emx_recv_array_5_1(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_5_1();
static inline uint32_t emx_ringbuf_size_5_1() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_5_1);
	return wr + ((wr < *emx_loc_rd_pos_5_1) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_5_1;
}

static inline uint32_t emx_ringbuf_free_5_1();
static inline uint32_t emx_ringbuf_free_5_1() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_5_1);
	return rd + ((*emx_loc_wr_pos_5_1 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_5_1 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_5_1(const register void *buf, register uint32_t size);

static inline void emx_send_5_1(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_5_1(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_5_1() < size) emx_ringbuf_wait_5();

	emx_send_array_5_1(buf, size);
}

void EMX_Send_5_1(const void *buf, uint32_t size);

extern void emx_recv_array_5_1(register void *buf, register uint32_t size);

static inline void emx_recv_5_1(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_5_1(void *buf, uint32_t size) {
	while (emx_ringbuf_size_5_1() < size) emx_ringbuf_wait_1();

	emx_recv_array_5_1(buf, size);
}

void EMX_Recv_5_1(void *buf, uint32_t size);

static inline void EMX_Send32F_5_1(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_5_1(float val) {
	EMX_Send32_5_1(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_5_1() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_5_1() {
	uint32_t r = EMX_Recv32_5_1();
	return *(float*)&r;
}

static inline void EMX_Send64F_5_1(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_5_1(double val) {
	EMX_Send64_5_1(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_5_1() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_5_1() {
	uint64_t r = EMX_Recv64_5_1();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_5_1() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_5_1() {
	return EMX_Recv8_5_1();
}

static inline void EMX_SendSync_5_1(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_5_1(uint8_t sync) {
	EMX_Send8_5_1(sync);
}

static inline void EMX_Wait_5_1() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_5_1() {
	EMX_Recv8_5_1();
}

static inline void EMX_Signal_5_1() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_5_1() {
	EMX_Send8_5_1(0);
}

void EMX_Send8_5_2(register uint8_t);
uint8_t EMX_Recv8_5_2();
void EMX_Send16_5_2(register uint16_t);
uint16_t EMX_Recv16_5_2();
void EMX_Send32_5_2(register uint32_t);
uint32_t EMX_Recv32_5_2();
void EMX_Send64_5_2(register uint64_t);
uint64_t EMX_Recv64_5_2();
void emx_send_array_5_2(register const void *buf, register uint32_t size);
void emx_recv_array_5_2(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_5_2();
static inline uint32_t emx_ringbuf_size_5_2() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_5_2);
	return wr + ((wr < *emx_loc_rd_pos_5_2) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_5_2;
}

static inline uint32_t emx_ringbuf_free_5_2();
static inline uint32_t emx_ringbuf_free_5_2() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_5_2);
	return rd + ((*emx_loc_wr_pos_5_2 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_5_2 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_5_2(const register void *buf, register uint32_t size);

static inline void emx_send_5_2(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_5_2(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_5_2() < size) emx_ringbuf_wait_5();

	emx_send_array_5_2(buf, size);
}

void EMX_Send_5_2(const void *buf, uint32_t size);

extern void emx_recv_array_5_2(register void *buf, register uint32_t size);

static inline void emx_recv_5_2(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_5_2(void *buf, uint32_t size) {
	while (emx_ringbuf_size_5_2() < size) emx_ringbuf_wait_2();

	emx_recv_array_5_2(buf, size);
}

void EMX_Recv_5_2(void *buf, uint32_t size);

static inline void EMX_Send32F_5_2(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_5_2(float val) {
	EMX_Send32_5_2(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_5_2() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_5_2() {
	uint32_t r = EMX_Recv32_5_2();
	return *(float*)&r;
}

static inline void EMX_Send64F_5_2(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_5_2(double val) {
	EMX_Send64_5_2(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_5_2() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_5_2() {
	uint64_t r = EMX_Recv64_5_2();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_5_2() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_5_2() {
	return EMX_Recv8_5_2();
}

static inline void EMX_SendSync_5_2(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_5_2(uint8_t sync) {
	EMX_Send8_5_2(sync);
}

static inline void EMX_Wait_5_2() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_5_2() {
	EMX_Recv8_5_2();
}

static inline void EMX_Signal_5_2() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_5_2() {
	EMX_Send8_5_2(0);
}

void EMX_Send8_5_3(register uint8_t);
uint8_t EMX_Recv8_5_3();
void EMX_Send16_5_3(register uint16_t);
uint16_t EMX_Recv16_5_3();
void EMX_Send32_5_3(register uint32_t);
uint32_t EMX_Recv32_5_3();
void EMX_Send64_5_3(register uint64_t);
uint64_t EMX_Recv64_5_3();
void emx_send_array_5_3(register const void *buf, register uint32_t size);
void emx_recv_array_5_3(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_5_3();
static inline uint32_t emx_ringbuf_size_5_3() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_5_3);
	return wr + ((wr < *emx_loc_rd_pos_5_3) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_5_3;
}

static inline uint32_t emx_ringbuf_free_5_3();
static inline uint32_t emx_ringbuf_free_5_3() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_5_3);
	return rd + ((*emx_loc_wr_pos_5_3 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_5_3 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_5_3(const register void *buf, register uint32_t size);

static inline void emx_send_5_3(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_5_3(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_5_3() < size) emx_ringbuf_wait_5();

	emx_send_array_5_3(buf, size);
}

void EMX_Send_5_3(const void *buf, uint32_t size);

extern void emx_recv_array_5_3(register void *buf, register uint32_t size);

static inline void emx_recv_5_3(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_5_3(void *buf, uint32_t size) {
	while (emx_ringbuf_size_5_3() < size) emx_ringbuf_wait_3();

	emx_recv_array_5_3(buf, size);
}

void EMX_Recv_5_3(void *buf, uint32_t size);

static inline void EMX_Send32F_5_3(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_5_3(float val) {
	EMX_Send32_5_3(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_5_3() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_5_3() {
	uint32_t r = EMX_Recv32_5_3();
	return *(float*)&r;
}

static inline void EMX_Send64F_5_3(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_5_3(double val) {
	EMX_Send64_5_3(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_5_3() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_5_3() {
	uint64_t r = EMX_Recv64_5_3();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_5_3() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_5_3() {
	return EMX_Recv8_5_3();
}

static inline void EMX_SendSync_5_3(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_5_3(uint8_t sync) {
	EMX_Send8_5_3(sync);
}

static inline void EMX_Wait_5_3() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_5_3() {
	EMX_Recv8_5_3();
}

static inline void EMX_Signal_5_3() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_5_3() {
	EMX_Send8_5_3(0);
}

void EMX_Send8_5_4(register uint8_t);
uint8_t EMX_Recv8_5_4();
void EMX_Send16_5_4(register uint16_t);
uint16_t EMX_Recv16_5_4();
void EMX_Send32_5_4(register uint32_t);
uint32_t EMX_Recv32_5_4();
void EMX_Send64_5_4(register uint64_t);
uint64_t EMX_Recv64_5_4();
void emx_send_array_5_4(register const void *buf, register uint32_t size);
void emx_recv_array_5_4(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_5_4();
static inline uint32_t emx_ringbuf_size_5_4() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_5_4);
	return wr + ((wr < *emx_loc_rd_pos_5_4) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_5_4;
}

static inline uint32_t emx_ringbuf_free_5_4();
static inline uint32_t emx_ringbuf_free_5_4() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_5_4);
	return rd + ((*emx_loc_wr_pos_5_4 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_5_4 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_5_4(const register void *buf, register uint32_t size);

static inline void emx_send_5_4(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_5_4(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_5_4() < size) emx_ringbuf_wait_5();

	emx_send_array_5_4(buf, size);
}

void EMX_Send_5_4(const void *buf, uint32_t size);

extern void emx_recv_array_5_4(register void *buf, register uint32_t size);

static inline void emx_recv_5_4(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_5_4(void *buf, uint32_t size) {
	while (emx_ringbuf_size_5_4() < size) emx_ringbuf_wait_4();

	emx_recv_array_5_4(buf, size);
}

void EMX_Recv_5_4(void *buf, uint32_t size);

static inline void EMX_Send32F_5_4(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_5_4(float val) {
	EMX_Send32_5_4(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_5_4() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_5_4() {
	uint32_t r = EMX_Recv32_5_4();
	return *(float*)&r;
}

static inline void EMX_Send64F_5_4(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_5_4(double val) {
	EMX_Send64_5_4(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_5_4() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_5_4() {
	uint64_t r = EMX_Recv64_5_4();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_5_4() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_5_4() {
	return EMX_Recv8_5_4();
}

static inline void EMX_SendSync_5_4(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_5_4(uint8_t sync) {
	EMX_Send8_5_4(sync);
}

static inline void EMX_Wait_5_4() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_5_4() {
	EMX_Recv8_5_4();
}

static inline void EMX_Signal_5_4() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_5_4() {
	EMX_Send8_5_4(0);
}

void EMX_Send8_5_6(register uint8_t);
uint8_t EMX_Recv8_5_6();
void EMX_Send16_5_6(register uint16_t);
uint16_t EMX_Recv16_5_6();
void EMX_Send32_5_6(register uint32_t);
uint32_t EMX_Recv32_5_6();
void EMX_Send64_5_6(register uint64_t);
uint64_t EMX_Recv64_5_6();
void emx_send_array_5_6(register const void *buf, register uint32_t size);
void emx_recv_array_5_6(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_5_6();
static inline uint32_t emx_ringbuf_size_5_6() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_5_6);
	return wr + ((wr < *emx_loc_rd_pos_5_6) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_5_6;
}

static inline uint32_t emx_ringbuf_free_5_6();
static inline uint32_t emx_ringbuf_free_5_6() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_5_6);
	return rd + ((*emx_loc_wr_pos_5_6 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_5_6 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_5_6(const register void *buf, register uint32_t size);

static inline void emx_send_5_6(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_5_6(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_5_6() < size) emx_ringbuf_wait_5();

	emx_send_array_5_6(buf, size);
}

void EMX_Send_5_6(const void *buf, uint32_t size);

extern void emx_recv_array_5_6(register void *buf, register uint32_t size);

static inline void emx_recv_5_6(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_5_6(void *buf, uint32_t size) {
	while (emx_ringbuf_size_5_6() < size) emx_ringbuf_wait_6();

	emx_recv_array_5_6(buf, size);
}

void EMX_Recv_5_6(void *buf, uint32_t size);

static inline void EMX_Send32F_5_6(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_5_6(float val) {
	EMX_Send32_5_6(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_5_6() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_5_6() {
	uint32_t r = EMX_Recv32_5_6();
	return *(float*)&r;
}

static inline void EMX_Send64F_5_6(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_5_6(double val) {
	EMX_Send64_5_6(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_5_6() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_5_6() {
	uint64_t r = EMX_Recv64_5_6();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_5_6() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_5_6() {
	return EMX_Recv8_5_6();
}

static inline void EMX_SendSync_5_6(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_5_6(uint8_t sync) {
	EMX_Send8_5_6(sync);
}

static inline void EMX_Wait_5_6() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_5_6() {
	EMX_Recv8_5_6();
}

static inline void EMX_Signal_5_6() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_5_6() {
	EMX_Send8_5_6(0);
}

void EMX_Send8_5_7(register uint8_t);
uint8_t EMX_Recv8_5_7();
void EMX_Send16_5_7(register uint16_t);
uint16_t EMX_Recv16_5_7();
void EMX_Send32_5_7(register uint32_t);
uint32_t EMX_Recv32_5_7();
void EMX_Send64_5_7(register uint64_t);
uint64_t EMX_Recv64_5_7();
void emx_send_array_5_7(register const void *buf, register uint32_t size);
void emx_recv_array_5_7(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_5_7();
static inline uint32_t emx_ringbuf_size_5_7() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_5_7);
	return wr + ((wr < *emx_loc_rd_pos_5_7) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_5_7;
}

static inline uint32_t emx_ringbuf_free_5_7();
static inline uint32_t emx_ringbuf_free_5_7() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_5_7);
	return rd + ((*emx_loc_wr_pos_5_7 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_5_7 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_5_7(const register void *buf, register uint32_t size);

static inline void emx_send_5_7(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_5_7(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_5_7() < size) emx_ringbuf_wait_5();

	emx_send_array_5_7(buf, size);
}

void EMX_Send_5_7(const void *buf, uint32_t size);

extern void emx_recv_array_5_7(register void *buf, register uint32_t size);

static inline void emx_recv_5_7(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_5_7(void *buf, uint32_t size) {
	while (emx_ringbuf_size_5_7() < size) emx_ringbuf_wait_7();

	emx_recv_array_5_7(buf, size);
}

void EMX_Recv_5_7(void *buf, uint32_t size);

static inline void EMX_Send32F_5_7(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_5_7(float val) {
	EMX_Send32_5_7(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_5_7() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_5_7() {
	uint32_t r = EMX_Recv32_5_7();
	return *(float*)&r;
}

static inline void EMX_Send64F_5_7(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_5_7(double val) {
	EMX_Send64_5_7(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_5_7() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_5_7() {
	uint64_t r = EMX_Recv64_5_7();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_5_7() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_5_7() {
	return EMX_Recv8_5_7();
}

static inline void EMX_SendSync_5_7(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_5_7(uint8_t sync) {
	EMX_Send8_5_7(sync);
}

static inline void EMX_Wait_5_7() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_5_7() {
	EMX_Recv8_5_7();
}

static inline void EMX_Signal_5_7() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_5_7() {
	EMX_Send8_5_7(0);
}

void emx_ringbuf_wait_6();

void EMX_Send8_6_0(register uint8_t);
uint8_t EMX_Recv8_6_0();
void EMX_Send16_6_0(register uint16_t);
uint16_t EMX_Recv16_6_0();
void EMX_Send32_6_0(register uint32_t);
uint32_t EMX_Recv32_6_0();
void EMX_Send64_6_0(register uint64_t);
uint64_t EMX_Recv64_6_0();
void emx_send_array_6_0(register const void *buf, register uint32_t size);
void emx_recv_array_6_0(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_6_0();
static inline uint32_t emx_ringbuf_size_6_0() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_6_0);
	return wr + ((wr < *emx_loc_rd_pos_6_0) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_6_0;
}

static inline uint32_t emx_ringbuf_free_6_0();
static inline uint32_t emx_ringbuf_free_6_0() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_6_0);
	return rd + ((*emx_loc_wr_pos_6_0 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_6_0 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_6_0(const register void *buf, register uint32_t size);

static inline void emx_send_6_0(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_6_0(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_6_0() < size) emx_ringbuf_wait_6();

	emx_send_array_6_0(buf, size);
}

void EMX_Send_6_0(const void *buf, uint32_t size);

extern void emx_recv_array_6_0(register void *buf, register uint32_t size);

static inline void emx_recv_6_0(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_6_0(void *buf, uint32_t size) {
	while (emx_ringbuf_size_6_0() < size) emx_ringbuf_wait_0();

	emx_recv_array_6_0(buf, size);
}

void EMX_Recv_6_0(void *buf, uint32_t size);

static inline void EMX_Send32F_6_0(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_6_0(float val) {
	EMX_Send32_6_0(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_6_0() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_6_0() {
	uint32_t r = EMX_Recv32_6_0();
	return *(float*)&r;
}

static inline void EMX_Send64F_6_0(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_6_0(double val) {
	EMX_Send64_6_0(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_6_0() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_6_0() {
	uint64_t r = EMX_Recv64_6_0();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_6_0() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_6_0() {
	return EMX_Recv8_6_0();
}

static inline void EMX_SendSync_6_0(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_6_0(uint8_t sync) {
	EMX_Send8_6_0(sync);
}

static inline void EMX_Wait_6_0() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_6_0() {
	EMX_Recv8_6_0();
}

static inline void EMX_Signal_6_0() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_6_0() {
	EMX_Send8_6_0(0);
}

void EMX_Send8_6_1(register uint8_t);
uint8_t EMX_Recv8_6_1();
void EMX_Send16_6_1(register uint16_t);
uint16_t EMX_Recv16_6_1();
void EMX_Send32_6_1(register uint32_t);
uint32_t EMX_Recv32_6_1();
void EMX_Send64_6_1(register uint64_t);
uint64_t EMX_Recv64_6_1();
void emx_send_array_6_1(register const void *buf, register uint32_t size);
void emx_recv_array_6_1(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_6_1();
static inline uint32_t emx_ringbuf_size_6_1() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_6_1);
	return wr + ((wr < *emx_loc_rd_pos_6_1) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_6_1;
}

static inline uint32_t emx_ringbuf_free_6_1();
static inline uint32_t emx_ringbuf_free_6_1() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_6_1);
	return rd + ((*emx_loc_wr_pos_6_1 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_6_1 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_6_1(const register void *buf, register uint32_t size);

static inline void emx_send_6_1(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_6_1(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_6_1() < size) emx_ringbuf_wait_6();

	emx_send_array_6_1(buf, size);
}

void EMX_Send_6_1(const void *buf, uint32_t size);

extern void emx_recv_array_6_1(register void *buf, register uint32_t size);

static inline void emx_recv_6_1(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_6_1(void *buf, uint32_t size) {
	while (emx_ringbuf_size_6_1() < size) emx_ringbuf_wait_1();

	emx_recv_array_6_1(buf, size);
}

void EMX_Recv_6_1(void *buf, uint32_t size);

static inline void EMX_Send32F_6_1(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_6_1(float val) {
	EMX_Send32_6_1(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_6_1() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_6_1() {
	uint32_t r = EMX_Recv32_6_1();
	return *(float*)&r;
}

static inline void EMX_Send64F_6_1(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_6_1(double val) {
	EMX_Send64_6_1(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_6_1() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_6_1() {
	uint64_t r = EMX_Recv64_6_1();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_6_1() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_6_1() {
	return EMX_Recv8_6_1();
}

static inline void EMX_SendSync_6_1(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_6_1(uint8_t sync) {
	EMX_Send8_6_1(sync);
}

static inline void EMX_Wait_6_1() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_6_1() {
	EMX_Recv8_6_1();
}

static inline void EMX_Signal_6_1() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_6_1() {
	EMX_Send8_6_1(0);
}

void EMX_Send8_6_2(register uint8_t);
uint8_t EMX_Recv8_6_2();
void EMX_Send16_6_2(register uint16_t);
uint16_t EMX_Recv16_6_2();
void EMX_Send32_6_2(register uint32_t);
uint32_t EMX_Recv32_6_2();
void EMX_Send64_6_2(register uint64_t);
uint64_t EMX_Recv64_6_2();
void emx_send_array_6_2(register const void *buf, register uint32_t size);
void emx_recv_array_6_2(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_6_2();
static inline uint32_t emx_ringbuf_size_6_2() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_6_2);
	return wr + ((wr < *emx_loc_rd_pos_6_2) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_6_2;
}

static inline uint32_t emx_ringbuf_free_6_2();
static inline uint32_t emx_ringbuf_free_6_2() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_6_2);
	return rd + ((*emx_loc_wr_pos_6_2 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_6_2 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_6_2(const register void *buf, register uint32_t size);

static inline void emx_send_6_2(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_6_2(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_6_2() < size) emx_ringbuf_wait_6();

	emx_send_array_6_2(buf, size);
}

void EMX_Send_6_2(const void *buf, uint32_t size);

extern void emx_recv_array_6_2(register void *buf, register uint32_t size);

static inline void emx_recv_6_2(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_6_2(void *buf, uint32_t size) {
	while (emx_ringbuf_size_6_2() < size) emx_ringbuf_wait_2();

	emx_recv_array_6_2(buf, size);
}

void EMX_Recv_6_2(void *buf, uint32_t size);

static inline void EMX_Send32F_6_2(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_6_2(float val) {
	EMX_Send32_6_2(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_6_2() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_6_2() {
	uint32_t r = EMX_Recv32_6_2();
	return *(float*)&r;
}

static inline void EMX_Send64F_6_2(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_6_2(double val) {
	EMX_Send64_6_2(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_6_2() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_6_2() {
	uint64_t r = EMX_Recv64_6_2();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_6_2() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_6_2() {
	return EMX_Recv8_6_2();
}

static inline void EMX_SendSync_6_2(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_6_2(uint8_t sync) {
	EMX_Send8_6_2(sync);
}

static inline void EMX_Wait_6_2() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_6_2() {
	EMX_Recv8_6_2();
}

static inline void EMX_Signal_6_2() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_6_2() {
	EMX_Send8_6_2(0);
}

void EMX_Send8_6_3(register uint8_t);
uint8_t EMX_Recv8_6_3();
void EMX_Send16_6_3(register uint16_t);
uint16_t EMX_Recv16_6_3();
void EMX_Send32_6_3(register uint32_t);
uint32_t EMX_Recv32_6_3();
void EMX_Send64_6_3(register uint64_t);
uint64_t EMX_Recv64_6_3();
void emx_send_array_6_3(register const void *buf, register uint32_t size);
void emx_recv_array_6_3(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_6_3();
static inline uint32_t emx_ringbuf_size_6_3() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_6_3);
	return wr + ((wr < *emx_loc_rd_pos_6_3) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_6_3;
}

static inline uint32_t emx_ringbuf_free_6_3();
static inline uint32_t emx_ringbuf_free_6_3() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_6_3);
	return rd + ((*emx_loc_wr_pos_6_3 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_6_3 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_6_3(const register void *buf, register uint32_t size);

static inline void emx_send_6_3(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_6_3(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_6_3() < size) emx_ringbuf_wait_6();

	emx_send_array_6_3(buf, size);
}

void EMX_Send_6_3(const void *buf, uint32_t size);

extern void emx_recv_array_6_3(register void *buf, register uint32_t size);

static inline void emx_recv_6_3(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_6_3(void *buf, uint32_t size) {
	while (emx_ringbuf_size_6_3() < size) emx_ringbuf_wait_3();

	emx_recv_array_6_3(buf, size);
}

void EMX_Recv_6_3(void *buf, uint32_t size);

static inline void EMX_Send32F_6_3(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_6_3(float val) {
	EMX_Send32_6_3(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_6_3() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_6_3() {
	uint32_t r = EMX_Recv32_6_3();
	return *(float*)&r;
}

static inline void EMX_Send64F_6_3(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_6_3(double val) {
	EMX_Send64_6_3(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_6_3() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_6_3() {
	uint64_t r = EMX_Recv64_6_3();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_6_3() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_6_3() {
	return EMX_Recv8_6_3();
}

static inline void EMX_SendSync_6_3(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_6_3(uint8_t sync) {
	EMX_Send8_6_3(sync);
}

static inline void EMX_Wait_6_3() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_6_3() {
	EMX_Recv8_6_3();
}

static inline void EMX_Signal_6_3() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_6_3() {
	EMX_Send8_6_3(0);
}

void EMX_Send8_6_4(register uint8_t);
uint8_t EMX_Recv8_6_4();
void EMX_Send16_6_4(register uint16_t);
uint16_t EMX_Recv16_6_4();
void EMX_Send32_6_4(register uint32_t);
uint32_t EMX_Recv32_6_4();
void EMX_Send64_6_4(register uint64_t);
uint64_t EMX_Recv64_6_4();
void emx_send_array_6_4(register const void *buf, register uint32_t size);
void emx_recv_array_6_4(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_6_4();
static inline uint32_t emx_ringbuf_size_6_4() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_6_4);
	return wr + ((wr < *emx_loc_rd_pos_6_4) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_6_4;
}

static inline uint32_t emx_ringbuf_free_6_4();
static inline uint32_t emx_ringbuf_free_6_4() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_6_4);
	return rd + ((*emx_loc_wr_pos_6_4 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_6_4 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_6_4(const register void *buf, register uint32_t size);

static inline void emx_send_6_4(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_6_4(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_6_4() < size) emx_ringbuf_wait_6();

	emx_send_array_6_4(buf, size);
}

void EMX_Send_6_4(const void *buf, uint32_t size);

extern void emx_recv_array_6_4(register void *buf, register uint32_t size);

static inline void emx_recv_6_4(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_6_4(void *buf, uint32_t size) {
	while (emx_ringbuf_size_6_4() < size) emx_ringbuf_wait_4();

	emx_recv_array_6_4(buf, size);
}

void EMX_Recv_6_4(void *buf, uint32_t size);

static inline void EMX_Send32F_6_4(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_6_4(float val) {
	EMX_Send32_6_4(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_6_4() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_6_4() {
	uint32_t r = EMX_Recv32_6_4();
	return *(float*)&r;
}

static inline void EMX_Send64F_6_4(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_6_4(double val) {
	EMX_Send64_6_4(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_6_4() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_6_4() {
	uint64_t r = EMX_Recv64_6_4();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_6_4() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_6_4() {
	return EMX_Recv8_6_4();
}

static inline void EMX_SendSync_6_4(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_6_4(uint8_t sync) {
	EMX_Send8_6_4(sync);
}

static inline void EMX_Wait_6_4() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_6_4() {
	EMX_Recv8_6_4();
}

static inline void EMX_Signal_6_4() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_6_4() {
	EMX_Send8_6_4(0);
}

void EMX_Send8_6_5(register uint8_t);
uint8_t EMX_Recv8_6_5();
void EMX_Send16_6_5(register uint16_t);
uint16_t EMX_Recv16_6_5();
void EMX_Send32_6_5(register uint32_t);
uint32_t EMX_Recv32_6_5();
void EMX_Send64_6_5(register uint64_t);
uint64_t EMX_Recv64_6_5();
void emx_send_array_6_5(register const void *buf, register uint32_t size);
void emx_recv_array_6_5(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_6_5();
static inline uint32_t emx_ringbuf_size_6_5() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_6_5);
	return wr + ((wr < *emx_loc_rd_pos_6_5) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_6_5;
}

static inline uint32_t emx_ringbuf_free_6_5();
static inline uint32_t emx_ringbuf_free_6_5() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_6_5);
	return rd + ((*emx_loc_wr_pos_6_5 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_6_5 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_6_5(const register void *buf, register uint32_t size);

static inline void emx_send_6_5(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_6_5(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_6_5() < size) emx_ringbuf_wait_6();

	emx_send_array_6_5(buf, size);
}

void EMX_Send_6_5(const void *buf, uint32_t size);

extern void emx_recv_array_6_5(register void *buf, register uint32_t size);

static inline void emx_recv_6_5(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_6_5(void *buf, uint32_t size) {
	while (emx_ringbuf_size_6_5() < size) emx_ringbuf_wait_5();

	emx_recv_array_6_5(buf, size);
}

void EMX_Recv_6_5(void *buf, uint32_t size);

static inline void EMX_Send32F_6_5(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_6_5(float val) {
	EMX_Send32_6_5(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_6_5() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_6_5() {
	uint32_t r = EMX_Recv32_6_5();
	return *(float*)&r;
}

static inline void EMX_Send64F_6_5(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_6_5(double val) {
	EMX_Send64_6_5(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_6_5() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_6_5() {
	uint64_t r = EMX_Recv64_6_5();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_6_5() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_6_5() {
	return EMX_Recv8_6_5();
}

static inline void EMX_SendSync_6_5(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_6_5(uint8_t sync) {
	EMX_Send8_6_5(sync);
}

static inline void EMX_Wait_6_5() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_6_5() {
	EMX_Recv8_6_5();
}

static inline void EMX_Signal_6_5() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_6_5() {
	EMX_Send8_6_5(0);
}

void EMX_Send8_6_7(register uint8_t);
uint8_t EMX_Recv8_6_7();
void EMX_Send16_6_7(register uint16_t);
uint16_t EMX_Recv16_6_7();
void EMX_Send32_6_7(register uint32_t);
uint32_t EMX_Recv32_6_7();
void EMX_Send64_6_7(register uint64_t);
uint64_t EMX_Recv64_6_7();
void emx_send_array_6_7(register const void *buf, register uint32_t size);
void emx_recv_array_6_7(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_6_7();
static inline uint32_t emx_ringbuf_size_6_7() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_6_7);
	return wr + ((wr < *emx_loc_rd_pos_6_7) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_6_7;
}

static inline uint32_t emx_ringbuf_free_6_7();
static inline uint32_t emx_ringbuf_free_6_7() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_6_7);
	return rd + ((*emx_loc_wr_pos_6_7 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_6_7 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_6_7(const register void *buf, register uint32_t size);

static inline void emx_send_6_7(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_6_7(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_6_7() < size) emx_ringbuf_wait_6();

	emx_send_array_6_7(buf, size);
}

void EMX_Send_6_7(const void *buf, uint32_t size);

extern void emx_recv_array_6_7(register void *buf, register uint32_t size);

static inline void emx_recv_6_7(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_6_7(void *buf, uint32_t size) {
	while (emx_ringbuf_size_6_7() < size) emx_ringbuf_wait_7();

	emx_recv_array_6_7(buf, size);
}

void EMX_Recv_6_7(void *buf, uint32_t size);

static inline void EMX_Send32F_6_7(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_6_7(float val) {
	EMX_Send32_6_7(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_6_7() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_6_7() {
	uint32_t r = EMX_Recv32_6_7();
	return *(float*)&r;
}

static inline void EMX_Send64F_6_7(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_6_7(double val) {
	EMX_Send64_6_7(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_6_7() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_6_7() {
	uint64_t r = EMX_Recv64_6_7();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_6_7() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_6_7() {
	return EMX_Recv8_6_7();
}

static inline void EMX_SendSync_6_7(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_6_7(uint8_t sync) {
	EMX_Send8_6_7(sync);
}

static inline void EMX_Wait_6_7() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_6_7() {
	EMX_Recv8_6_7();
}

static inline void EMX_Signal_6_7() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_6_7() {
	EMX_Send8_6_7(0);
}

void emx_ringbuf_wait_7();

void EMX_Send8_7_0(register uint8_t);
uint8_t EMX_Recv8_7_0();
void EMX_Send16_7_0(register uint16_t);
uint16_t EMX_Recv16_7_0();
void EMX_Send32_7_0(register uint32_t);
uint32_t EMX_Recv32_7_0();
void EMX_Send64_7_0(register uint64_t);
uint64_t EMX_Recv64_7_0();
void emx_send_array_7_0(register const void *buf, register uint32_t size);
void emx_recv_array_7_0(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_7_0();
static inline uint32_t emx_ringbuf_size_7_0() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_7_0);
	return wr + ((wr < *emx_loc_rd_pos_7_0) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_7_0;
}

static inline uint32_t emx_ringbuf_free_7_0();
static inline uint32_t emx_ringbuf_free_7_0() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_7_0);
	return rd + ((*emx_loc_wr_pos_7_0 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_7_0 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_7_0(const register void *buf, register uint32_t size);

static inline void emx_send_7_0(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_7_0(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_7_0() < size) emx_ringbuf_wait_7();

	emx_send_array_7_0(buf, size);
}

void EMX_Send_7_0(const void *buf, uint32_t size);

extern void emx_recv_array_7_0(register void *buf, register uint32_t size);

static inline void emx_recv_7_0(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_7_0(void *buf, uint32_t size) {
	while (emx_ringbuf_size_7_0() < size) emx_ringbuf_wait_0();

	emx_recv_array_7_0(buf, size);
}

void EMX_Recv_7_0(void *buf, uint32_t size);

static inline void EMX_Send32F_7_0(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_7_0(float val) {
	EMX_Send32_7_0(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_7_0() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_7_0() {
	uint32_t r = EMX_Recv32_7_0();
	return *(float*)&r;
}

static inline void EMX_Send64F_7_0(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_7_0(double val) {
	EMX_Send64_7_0(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_7_0() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_7_0() {
	uint64_t r = EMX_Recv64_7_0();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_7_0() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_7_0() {
	return EMX_Recv8_7_0();
}

static inline void EMX_SendSync_7_0(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_7_0(uint8_t sync) {
	EMX_Send8_7_0(sync);
}

static inline void EMX_Wait_7_0() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_7_0() {
	EMX_Recv8_7_0();
}

static inline void EMX_Signal_7_0() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_7_0() {
	EMX_Send8_7_0(0);
}

void EMX_Send8_7_1(register uint8_t);
uint8_t EMX_Recv8_7_1();
void EMX_Send16_7_1(register uint16_t);
uint16_t EMX_Recv16_7_1();
void EMX_Send32_7_1(register uint32_t);
uint32_t EMX_Recv32_7_1();
void EMX_Send64_7_1(register uint64_t);
uint64_t EMX_Recv64_7_1();
void emx_send_array_7_1(register const void *buf, register uint32_t size);
void emx_recv_array_7_1(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_7_1();
static inline uint32_t emx_ringbuf_size_7_1() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_7_1);
	return wr + ((wr < *emx_loc_rd_pos_7_1) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_7_1;
}

static inline uint32_t emx_ringbuf_free_7_1();
static inline uint32_t emx_ringbuf_free_7_1() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_7_1);
	return rd + ((*emx_loc_wr_pos_7_1 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_7_1 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_7_1(const register void *buf, register uint32_t size);

static inline void emx_send_7_1(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_7_1(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_7_1() < size) emx_ringbuf_wait_7();

	emx_send_array_7_1(buf, size);
}

void EMX_Send_7_1(const void *buf, uint32_t size);

extern void emx_recv_array_7_1(register void *buf, register uint32_t size);

static inline void emx_recv_7_1(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_7_1(void *buf, uint32_t size) {
	while (emx_ringbuf_size_7_1() < size) emx_ringbuf_wait_1();

	emx_recv_array_7_1(buf, size);
}

void EMX_Recv_7_1(void *buf, uint32_t size);

static inline void EMX_Send32F_7_1(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_7_1(float val) {
	EMX_Send32_7_1(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_7_1() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_7_1() {
	uint32_t r = EMX_Recv32_7_1();
	return *(float*)&r;
}

static inline void EMX_Send64F_7_1(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_7_1(double val) {
	EMX_Send64_7_1(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_7_1() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_7_1() {
	uint64_t r = EMX_Recv64_7_1();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_7_1() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_7_1() {
	return EMX_Recv8_7_1();
}

static inline void EMX_SendSync_7_1(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_7_1(uint8_t sync) {
	EMX_Send8_7_1(sync);
}

static inline void EMX_Wait_7_1() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_7_1() {
	EMX_Recv8_7_1();
}

static inline void EMX_Signal_7_1() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_7_1() {
	EMX_Send8_7_1(0);
}

void EMX_Send8_7_2(register uint8_t);
uint8_t EMX_Recv8_7_2();
void EMX_Send16_7_2(register uint16_t);
uint16_t EMX_Recv16_7_2();
void EMX_Send32_7_2(register uint32_t);
uint32_t EMX_Recv32_7_2();
void EMX_Send64_7_2(register uint64_t);
uint64_t EMX_Recv64_7_2();
void emx_send_array_7_2(register const void *buf, register uint32_t size);
void emx_recv_array_7_2(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_7_2();
static inline uint32_t emx_ringbuf_size_7_2() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_7_2);
	return wr + ((wr < *emx_loc_rd_pos_7_2) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_7_2;
}

static inline uint32_t emx_ringbuf_free_7_2();
static inline uint32_t emx_ringbuf_free_7_2() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_7_2);
	return rd + ((*emx_loc_wr_pos_7_2 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_7_2 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_7_2(const register void *buf, register uint32_t size);

static inline void emx_send_7_2(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_7_2(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_7_2() < size) emx_ringbuf_wait_7();

	emx_send_array_7_2(buf, size);
}

void EMX_Send_7_2(const void *buf, uint32_t size);

extern void emx_recv_array_7_2(register void *buf, register uint32_t size);

static inline void emx_recv_7_2(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_7_2(void *buf, uint32_t size) {
	while (emx_ringbuf_size_7_2() < size) emx_ringbuf_wait_2();

	emx_recv_array_7_2(buf, size);
}

void EMX_Recv_7_2(void *buf, uint32_t size);

static inline void EMX_Send32F_7_2(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_7_2(float val) {
	EMX_Send32_7_2(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_7_2() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_7_2() {
	uint32_t r = EMX_Recv32_7_2();
	return *(float*)&r;
}

static inline void EMX_Send64F_7_2(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_7_2(double val) {
	EMX_Send64_7_2(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_7_2() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_7_2() {
	uint64_t r = EMX_Recv64_7_2();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_7_2() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_7_2() {
	return EMX_Recv8_7_2();
}

static inline void EMX_SendSync_7_2(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_7_2(uint8_t sync) {
	EMX_Send8_7_2(sync);
}

static inline void EMX_Wait_7_2() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_7_2() {
	EMX_Recv8_7_2();
}

static inline void EMX_Signal_7_2() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_7_2() {
	EMX_Send8_7_2(0);
}

void EMX_Send8_7_3(register uint8_t);
uint8_t EMX_Recv8_7_3();
void EMX_Send16_7_3(register uint16_t);
uint16_t EMX_Recv16_7_3();
void EMX_Send32_7_3(register uint32_t);
uint32_t EMX_Recv32_7_3();
void EMX_Send64_7_3(register uint64_t);
uint64_t EMX_Recv64_7_3();
void emx_send_array_7_3(register const void *buf, register uint32_t size);
void emx_recv_array_7_3(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_7_3();
static inline uint32_t emx_ringbuf_size_7_3() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_7_3);
	return wr + ((wr < *emx_loc_rd_pos_7_3) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_7_3;
}

static inline uint32_t emx_ringbuf_free_7_3();
static inline uint32_t emx_ringbuf_free_7_3() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_7_3);
	return rd + ((*emx_loc_wr_pos_7_3 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_7_3 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_7_3(const register void *buf, register uint32_t size);

static inline void emx_send_7_3(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_7_3(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_7_3() < size) emx_ringbuf_wait_7();

	emx_send_array_7_3(buf, size);
}

void EMX_Send_7_3(const void *buf, uint32_t size);

extern void emx_recv_array_7_3(register void *buf, register uint32_t size);

static inline void emx_recv_7_3(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_7_3(void *buf, uint32_t size) {
	while (emx_ringbuf_size_7_3() < size) emx_ringbuf_wait_3();

	emx_recv_array_7_3(buf, size);
}

void EMX_Recv_7_3(void *buf, uint32_t size);

static inline void EMX_Send32F_7_3(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_7_3(float val) {
	EMX_Send32_7_3(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_7_3() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_7_3() {
	uint32_t r = EMX_Recv32_7_3();
	return *(float*)&r;
}

static inline void EMX_Send64F_7_3(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_7_3(double val) {
	EMX_Send64_7_3(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_7_3() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_7_3() {
	uint64_t r = EMX_Recv64_7_3();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_7_3() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_7_3() {
	return EMX_Recv8_7_3();
}

static inline void EMX_SendSync_7_3(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_7_3(uint8_t sync) {
	EMX_Send8_7_3(sync);
}

static inline void EMX_Wait_7_3() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_7_3() {
	EMX_Recv8_7_3();
}

static inline void EMX_Signal_7_3() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_7_3() {
	EMX_Send8_7_3(0);
}

void EMX_Send8_7_4(register uint8_t);
uint8_t EMX_Recv8_7_4();
void EMX_Send16_7_4(register uint16_t);
uint16_t EMX_Recv16_7_4();
void EMX_Send32_7_4(register uint32_t);
uint32_t EMX_Recv32_7_4();
void EMX_Send64_7_4(register uint64_t);
uint64_t EMX_Recv64_7_4();
void emx_send_array_7_4(register const void *buf, register uint32_t size);
void emx_recv_array_7_4(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_7_4();
static inline uint32_t emx_ringbuf_size_7_4() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_7_4);
	return wr + ((wr < *emx_loc_rd_pos_7_4) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_7_4;
}

static inline uint32_t emx_ringbuf_free_7_4();
static inline uint32_t emx_ringbuf_free_7_4() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_7_4);
	return rd + ((*emx_loc_wr_pos_7_4 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_7_4 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_7_4(const register void *buf, register uint32_t size);

static inline void emx_send_7_4(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_7_4(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_7_4() < size) emx_ringbuf_wait_7();

	emx_send_array_7_4(buf, size);
}

void EMX_Send_7_4(const void *buf, uint32_t size);

extern void emx_recv_array_7_4(register void *buf, register uint32_t size);

static inline void emx_recv_7_4(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_7_4(void *buf, uint32_t size) {
	while (emx_ringbuf_size_7_4() < size) emx_ringbuf_wait_4();

	emx_recv_array_7_4(buf, size);
}

void EMX_Recv_7_4(void *buf, uint32_t size);

static inline void EMX_Send32F_7_4(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_7_4(float val) {
	EMX_Send32_7_4(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_7_4() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_7_4() {
	uint32_t r = EMX_Recv32_7_4();
	return *(float*)&r;
}

static inline void EMX_Send64F_7_4(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_7_4(double val) {
	EMX_Send64_7_4(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_7_4() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_7_4() {
	uint64_t r = EMX_Recv64_7_4();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_7_4() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_7_4() {
	return EMX_Recv8_7_4();
}

static inline void EMX_SendSync_7_4(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_7_4(uint8_t sync) {
	EMX_Send8_7_4(sync);
}

static inline void EMX_Wait_7_4() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_7_4() {
	EMX_Recv8_7_4();
}

static inline void EMX_Signal_7_4() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_7_4() {
	EMX_Send8_7_4(0);
}

void EMX_Send8_7_5(register uint8_t);
uint8_t EMX_Recv8_7_5();
void EMX_Send16_7_5(register uint16_t);
uint16_t EMX_Recv16_7_5();
void EMX_Send32_7_5(register uint32_t);
uint32_t EMX_Recv32_7_5();
void EMX_Send64_7_5(register uint64_t);
uint64_t EMX_Recv64_7_5();
void emx_send_array_7_5(register const void *buf, register uint32_t size);
void emx_recv_array_7_5(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_7_5();
static inline uint32_t emx_ringbuf_size_7_5() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_7_5);
	return wr + ((wr < *emx_loc_rd_pos_7_5) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_7_5;
}

static inline uint32_t emx_ringbuf_free_7_5();
static inline uint32_t emx_ringbuf_free_7_5() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_7_5);
	return rd + ((*emx_loc_wr_pos_7_5 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_7_5 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_7_5(const register void *buf, register uint32_t size);

static inline void emx_send_7_5(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_7_5(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_7_5() < size) emx_ringbuf_wait_7();

	emx_send_array_7_5(buf, size);
}

void EMX_Send_7_5(const void *buf, uint32_t size);

extern void emx_recv_array_7_5(register void *buf, register uint32_t size);

static inline void emx_recv_7_5(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_7_5(void *buf, uint32_t size) {
	while (emx_ringbuf_size_7_5() < size) emx_ringbuf_wait_5();

	emx_recv_array_7_5(buf, size);
}

void EMX_Recv_7_5(void *buf, uint32_t size);

static inline void EMX_Send32F_7_5(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_7_5(float val) {
	EMX_Send32_7_5(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_7_5() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_7_5() {
	uint32_t r = EMX_Recv32_7_5();
	return *(float*)&r;
}

static inline void EMX_Send64F_7_5(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_7_5(double val) {
	EMX_Send64_7_5(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_7_5() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_7_5() {
	uint64_t r = EMX_Recv64_7_5();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_7_5() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_7_5() {
	return EMX_Recv8_7_5();
}

static inline void EMX_SendSync_7_5(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_7_5(uint8_t sync) {
	EMX_Send8_7_5(sync);
}

static inline void EMX_Wait_7_5() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_7_5() {
	EMX_Recv8_7_5();
}

static inline void EMX_Signal_7_5() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_7_5() {
	EMX_Send8_7_5(0);
}

void EMX_Send8_7_6(register uint8_t);
uint8_t EMX_Recv8_7_6();
void EMX_Send16_7_6(register uint16_t);
uint16_t EMX_Recv16_7_6();
void EMX_Send32_7_6(register uint32_t);
uint32_t EMX_Recv32_7_6();
void EMX_Send64_7_6(register uint64_t);
uint64_t EMX_Recv64_7_6();
void emx_send_array_7_6(register const void *buf, register uint32_t size);
void emx_recv_array_7_6(register void *buf, register uint32_t size);

static inline uint32_t emx_ringbuf_size_7_6();
static inline uint32_t emx_ringbuf_size_7_6() {
	uint32_t wr = EMX_ATOMICREAD(*emx_wr_pos_7_6);
	return wr + ((wr < *emx_loc_rd_pos_7_6) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_rd_pos_7_6;
}

static inline uint32_t emx_ringbuf_free_7_6();
static inline uint32_t emx_ringbuf_free_7_6() {
	uint32_t rd = EMX_ATOMICREAD(*emx_rd_pos_7_6);
	return rd + ((*emx_loc_wr_pos_7_6 >= rd) ? EMX_RINGBUF_SIZE : 0)
		- *emx_loc_wr_pos_7_6 - EMX_RINGBUF_ALIGN;
}

void emx_send_array_7_6(const register void *buf, register uint32_t size);

static inline void emx_send_7_6(const void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_send_7_6(const void *buf, uint32_t size) {
	while (emx_ringbuf_free_7_6() < size) emx_ringbuf_wait_7();

	emx_send_array_7_6(buf, size);
}

void EMX_Send_7_6(const void *buf, uint32_t size);

extern void emx_recv_array_7_6(register void *buf, register uint32_t size);

static inline void emx_recv_7_6(void *buf, uint32_t size) EMX_ALWAYS_INLINE;
static inline void emx_recv_7_6(void *buf, uint32_t size) {
	while (emx_ringbuf_size_7_6() < size) emx_ringbuf_wait_6();

	emx_recv_array_7_6(buf, size);
}

void EMX_Recv_7_6(void *buf, uint32_t size);

static inline void EMX_Send32F_7_6(float val) EMX_ALWAYS_INLINE;
static inline void EMX_Send32F_7_6(float val) {
	EMX_Send32_7_6(*(uint32_t*)&val);
}

static inline float EMX_Recv32F_7_6() EMX_ALWAYS_INLINE;
static inline float EMX_Recv32F_7_6() {
	uint32_t r = EMX_Recv32_7_6();
	return *(float*)&r;
}

static inline void EMX_Send64F_7_6(double val) EMX_ALWAYS_INLINE;
static inline void EMX_Send64F_7_6(double val) {
	EMX_Send64_7_6(*(uint64_t*)&val);
}

static inline double EMX_Recv64F_7_6() EMX_ALWAYS_INLINE;
static inline double EMX_Recv64F_7_6() {
	uint64_t r = EMX_Recv64_7_6();
	return *(double*)&r;
}

static inline uint8_t EMX_RecvSync_7_6() EMX_ALWAYS_INLINE;
static inline uint8_t EMX_RecvSync_7_6() {
	return EMX_Recv8_7_6();
}

static inline void EMX_SendSync_7_6(uint8_t sync) EMX_ALWAYS_INLINE;
static inline void EMX_SendSync_7_6(uint8_t sync) {
	EMX_Send8_7_6(sync);
}

static inline void EMX_Wait_7_6() EMX_ALWAYS_INLINE;
static inline void EMX_Wait_7_6() {
	EMX_Recv8_7_6();
}

static inline void EMX_Signal_7_6() EMX_ALWAYS_INLINE;
static inline void EMX_Signal_7_6() {
	EMX_Send8_7_6(0);
}

#endif
