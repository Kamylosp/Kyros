#include <stdint.h>
#include "miros.h"


uint32_t conta0=0, conta1=0, conta2=0;

uint32_t stack_blinky1[40];
OSThread blinky1;
void main_blinky1() {
    while (1) {
    	conta0++;
        OS_delay(TICKS_PER_SEC * 3U / 4U);
    }
}

uint32_t stack_blinky2[40];
OSThread blinky2;

void main_blinky2() {
    while (1) {
    	conta1++;
        OS_delay(TICKS_PER_SEC / 3U);
    }
}

uint32_t stack_blinky3[40];
OSThread blinky3;
void main_blinky3() {
    while (1) {
    	conta2++;
        OS_delay(TICKS_PER_SEC * 3U / 5U);
    }
}

uint32_t stack_idleThread[40];

int main() {
    OS_init(stack_idleThread, sizeof(stack_idleThread));

    /* start blinky1 thread */
    OSThread_start(&blinky1,
                   5U, /* priority */
                   &main_blinky1,
                   stack_blinky1, sizeof(stack_blinky1));

    /* start blinky2 thread */
    OSThread_start(&blinky2,
                   2U, /* priority */
                   &main_blinky2,
                   stack_blinky2, sizeof(stack_blinky2));

    /* start blinky3 thread */
    OSThread_start(&blinky3,
                   1U, /* priority */
                   &main_blinky3,
                   stack_blinky3, sizeof(stack_blinky3));

    /* transfer control to the RTOS to run the threads */
    OS_run();

    //return 0;
}
