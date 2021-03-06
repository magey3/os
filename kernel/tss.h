#ifndef TSS_H
#define TSS_H

typedef struct {
	uint32_t res0;
	uint64_t rsp0;
	uint64_t rsp1;
	uint64_t rsp2;
	uint64_t res1;
	uint64_t ist1;
	uint64_t ist2;
	uint64_t ist3;
	uint64_t ist4;
	uint64_t ist5;
	uint64_t ist6;
	uint64_t ist7;
	uint64_t res2;
	uint16_t res3;
	uint16_t iopb;
} __attribute__((packed)) tss_t;

void get_tss(tss_t* tss);

#endif
