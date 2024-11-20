#include "main.h"
#include "config_gpio.h"

uint32_t cont_task_1 = 0;
uint32_t cont_task_2 = 0;
uint32_t cont_task_3 = 0;
uint32_t cont_aperiodic_task_1 = 0;
uint8_t actual_task = 0;

uint32_t ky = 0;

uint8_t qtd_aperiodic_tasks=0;

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

void aperiodic_task_1(){
    while(1){
        actual_task = 11;

        cont_aperiodic_task_1 = 0;
        while(cont_aperiodic_task_1 < 0xFFFFF)
                	cont_aperiodic_task_1++;

        OS();
    }
}

struct_periodic_task struct_task1;
struct_periodic_task struct_task2;
struct_periodic_task struct_task3;

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

    MX_GPIO_Init();

    OS_run();
}


uint32_t previousMillis = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  /* Prevent unused argument(s) compilation warning */
  //UNUSED(GPIO_Pin);

	uint32_t currentMillis = HAL_GetTick();

	if (GPIO_Pin == GPIO_PIN_0 && (currentMillis - previousMillis) > 1){
		ky++;
		previousMillis = currentMillis;
	}


  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
}
