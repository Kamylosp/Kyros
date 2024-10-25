#include <stdint.h>
#include <stdlib.h>
#include "miros.h"

struct struct_threads {
    OSThread TCB_thread;
    uint32_t stack_thread[40];
};


uint8_t actual_task = 0;

void task1(){
    while(1){
        actual_task = 1;
    }
}

void task2(){
    while(1){
        actual_task = 2;
    }
}

void task3(){
    while(1){
        actual_task = 3;
    }
}


struct struct_threads struct_task1;
struct struct_threads struct_task2;
struct struct_threads struct_task3;


int main() {
	uint32_t stack_idleThread[40];

    // start the OS
    OS_init(stack_idleThread, sizeof(stack_idleThread));


    struct_task1.TCB_thread.task_parameters.cost_absolute = 50;
    struct_task1.TCB_thread.task_parameters.cost_dinamic = 50;
    struct_task1.TCB_thread.task_parameters.deadline_absolute = 100;
    struct_task1.TCB_thread.task_parameters.deadline_dinamic = 100;
    struct_task1.TCB_thread.task_parameters.period_absolute = 150;
    struct_task1.TCB_thread.task_parameters.period_dinamic = 150;

    struct_task2.TCB_thread.task_parameters.cost_absolute = 50;
    struct_task2.TCB_thread.task_parameters.cost_dinamic = 50;
    struct_task2.TCB_thread.task_parameters.deadline_absolute = 150;
    struct_task2.TCB_thread.task_parameters.deadline_dinamic = 150;
    struct_task2.TCB_thread.task_parameters.period_absolute = 200;
    struct_task2.TCB_thread.task_parameters.period_dinamic = 200;

    struct_task3.TCB_thread.task_parameters.cost_absolute = 50;
    struct_task3.TCB_thread.task_parameters.cost_dinamic = 50;
    struct_task3.TCB_thread.task_parameters.deadline_absolute = 250;
    struct_task3.TCB_thread.task_parameters.deadline_dinamic = 250;
    struct_task3.TCB_thread.task_parameters.period_absolute = 300;
    struct_task3.TCB_thread.task_parameters.period_dinamic = 300;


    OSThread_start(&struct_task1.TCB_thread, 
                    1,
                    &task1,
                    struct_task1.stack_thread,
                    sizeof(struct_task1.stack_thread));

    OSThread_start(&struct_task2.TCB_thread, 
                    2,
                    &task2,
                    struct_task2.stack_thread,
                    sizeof(struct_task2.stack_thread));

    OSThread_start(&struct_task3.TCB_thread, 
                    3,
                    &task3,
                    struct_task3.stack_thread,
                    sizeof(struct_task3.stack_thread));            


    /* transfer control to the RTOS to run the threads */
    OS_run();
}
