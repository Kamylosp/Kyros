#include <stdint.h>
#include <stdlib.h>
#include "miros.h"
#include "stm32f1xx_hal.h"


struct struct_threads {
    OSThread TCB_thread;
    uint32_t stack_thread[40];
};

uint32_t cont_task_1 = 0;
uint32_t cont_task_2 = 0;
uint32_t cont_task_3 = 0;
uint8_t actual_task = 0;


void task1(){
    while(1){
        actual_task = 1;

        cont_task_1 = 0;
        while(cont_task_1 < 0x8FFF)
        	cont_task_1++;

        OS_wait_next_period();
    }
}

void task2(){
    while(1){
        actual_task = 2;

        cont_task_2 = 0;
        while(cont_task_2 < 0xFFFF)
        	cont_task_2++;

        OS_wait_next_period();
    }
}

void task3(){
    while(1){
        actual_task = 3;

        cont_task_3 = 0;
        while(cont_task_3 < 0x1FFFF)
                	cont_task_3++;

        OS_wait_next_period();
    }
}

struct struct_threads struct_task1;
struct struct_threads struct_task2;
struct struct_threads struct_task3;

int main() {
	uint32_t stack_idleThread[40];

    // start the OS
    OS_init(stack_idleThread, sizeof(stack_idleThread));

    struct_task1.TCB_thread.task_parameters.deadline_absolute = 100;
    struct_task1.TCB_thread.task_parameters.deadline_dinamic = 100;
    struct_task1.TCB_thread.task_parameters.period_absolute = 100;
    struct_task1.TCB_thread.task_parameters.period_dinamic = 100;

    struct_task2.TCB_thread.task_parameters.deadline_absolute = 80;
    struct_task2.TCB_thread.task_parameters.deadline_dinamic = 80;
    struct_task2.TCB_thread.task_parameters.period_absolute = 80;
    struct_task2.TCB_thread.task_parameters.period_dinamic = 80;

    struct_task3.TCB_thread.task_parameters.deadline_absolute = 150;
    struct_task3.TCB_thread.task_parameters.deadline_dinamic = 150;
    struct_task3.TCB_thread.task_parameters.period_absolute = 150;
    struct_task3.TCB_thread.task_parameters.period_dinamic = 150;

    OSThread_start(&struct_task1.TCB_thread, 
                    &task1,
                    struct_task1.stack_thread,
                    sizeof(struct_task1.stack_thread));
    

    OSThread_start(&struct_task2.TCB_thread, 
                    &task2,
                    struct_task2.stack_thread,
                    sizeof(struct_task2.stack_thread));


    OSThread_start(&struct_task3.TCB_thread, 
                    &task3,
                    struct_task3.stack_thread,
                    sizeof(struct_task3.stack_thread));            


    /* transfer control to the RTOS to run the threads */
    OS_run();
}
