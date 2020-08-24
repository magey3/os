#include <stddef.h>
#include <stdint.h>
#include "tss.h"

extern uint8_t _syscall_stack;

void get_tss(tss_t* tss){
	tss->rsp0 = (uint64_t)&_syscall_stack;
	tss->iopb = 104;
}
