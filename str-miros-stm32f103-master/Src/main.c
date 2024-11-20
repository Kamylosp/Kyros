#include "main.h"
#include "config_gpio.h"

uint32_t cont_task_1 = 0;
uint32_t cont_task_2 = 0;
uint32_t cont_task_3 = 0;
uint32_t cont_aperiodic_task_1 = 0;
uint32_t cont_aperiodic_task_2 = 0;

struct_periodic_task struct_task1;
struct_periodic_task struct_task2;
struct_periodic_task struct_task3;

struct_periodic_task struct_aperiodic_task_1;
struct_periodic_task struct_aperiodic_task_2;

OSThread_periodics_task_parameters parameters_periodic_task_1;
OSThread_periodics_task_parameters parameters_periodic_task_2;
OSThread_periodics_task_parameters parameters_periodic_task_3;

uint32_t aux_tick = 0;

void task1(){
    while(1){

        uint32_t start_tick = HAL_GetTick();

        cont_task_1 = 0;
        while(cont_task_1 < 0x5FFFF)
        	cont_task_1++;

        aux_tick = HAL_GetTick() - start_tick;

        OS_wait_next_period();
    }
}

void task2(){
    while(1){

        cont_task_2 = 0;
        while(cont_task_2 < 0x1FFFF)
        	cont_task_2++;

        OS_wait_next_period();
    }
}

void task3(){
    while(1){

        cont_task_3 = 0;
        while(cont_task_3 < 0x3FFFF){
                	cont_task_3++;
        }

        OS_wait_next_period();
    }
}

void aperiodic_task_1(){

	cont_aperiodic_task_1 = 0;
	while(cont_aperiodic_task_1 < 0x3FFFF)
				cont_aperiodic_task_1++;

	OSAperiodic_task_start(&struct_aperiodic_task_2.TCB_thread,
							&aperiodic_task_2,
							struct_aperiodic_task_2.stack_thread,
							sizeof(struct_aperiodic_task_2.stack_thread));

	while(cont_aperiodic_task_1 < 0x6FFFF)
					cont_aperiodic_task_1++;

	OS_finished_aperiodic_task();
}

void aperiodic_task_2(){

	cont_aperiodic_task_2 = 0;
	while(cont_aperiodic_task_2 < 0x5FFFF)
		cont_aperiodic_task_2++;

	OS_finished_aperiodic_task();
}


int main() {
	uint32_t stack_idleThread[40];

    // start the OS
    OS_init(stack_idleThread, sizeof(stack_idleThread));


    parameters_periodic_task_1.deadline_absolute = 500;
    parameters_periodic_task_1.deadline_dinamic = 500;
    parameters_periodic_task_1.period_absolute = 500;
    parameters_periodic_task_1.period_dinamic = 500;

    parameters_periodic_task_2.deadline_absolute = 100;
    parameters_periodic_task_2.deadline_dinamic = 100;
    parameters_periodic_task_2.period_absolute = 100;
    parameters_periodic_task_2.period_dinamic = 100;

    parameters_periodic_task_3.deadline_absolute = 200;
    parameters_periodic_task_3.deadline_dinamic = 200;
    parameters_periodic_task_3.period_absolute = 200;
    parameters_periodic_task_3.period_dinamic = 200;

    struct_task1.TCB_thread.task_parameters = &parameters_periodic_task_1;
    struct_task2.TCB_thread.task_parameters = &parameters_periodic_task_2;
    struct_task3.TCB_thread.task_parameters = &parameters_periodic_task_3;

    OSPeriodic_task_start(&struct_task1.TCB_thread, 
                    &task1,
                    struct_task1.stack_thread,
                    sizeof(struct_task1.stack_thread));
    
    OSPeriodic_task_start(&struct_task2.TCB_thread, 
                    &task2,
                    struct_task2.stack_thread,
                    sizeof(struct_task2.stack_thread));

    OSPeriodic_task_start(&struct_task3.TCB_thread, 
                    &task3,
                    struct_task3.stack_thread,
                    sizeof(struct_task3.stack_thread));

    OSAperiodic_task_start(&struct_aperiodic_task_1.TCB_thread,
    						&aperiodic_task_1,
							struct_aperiodic_task_1.stack_thread,
							sizeof(struct_aperiodic_task_1.stack_thread));
    //MX_GPIO_Init();

    OS_run();
}


uint32_t previousMillis = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  /* Prevent unused argument(s) compilation warning */
  //UNUSED(GPIO_Pin);

	uint32_t currentMillis = HAL_GetTick();

	if (GPIO_Pin == GPIO_PIN_0 && (currentMillis - previousMillis) > 1){
		//ky++;
		previousMillis = currentMillis;
	}


  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
}
