#include "main.h"
#include "config_gpio.h"

uint32_t cont_task_1 = 0;
uint32_t cont_task_2 = 0;
uint32_t cont_task_3 = 0;
uint32_t cont_aperiodic_task_1 = 0;
uint32_t cont_aperiodic_task_2 = 0;

#define ONE_SEC_IN_CONT 0x6CFFF
#define TWO_SEC_IN_CONT 0xD8FFE
#define THREE_SEC_IN_CONT 0x144FFD

struct_periodic_task struct_task1;
struct_periodic_task struct_task2;

OSThread_periodics_task_parameters parameters_periodic_task_1;
OSThread_periodics_task_parameters parameters_periodic_task_2;

uint32_t aux_tick = 0;

void task1(){
    while(1){
        cont_task_1 = 0;

        while(cont_task_1 < ONE_SEC_IN_CONT)
        	cont_task_1++;
        

        //enter_critical_region();

        while(cont_task_1 < TWO_SEC_IN_CONT)
        	cont_task_1++;

        //out_critical_region();


        OS_wait_next_period();
    }
}

void task2(){
    while(1){

        cont_task_2 = 0;

        while(cont_task_2 < ONE_SEC_IN_CONT)
        	cont_task_2++;
        

        //enter_critical_region();

        while(cont_task_2 < THREE_SEC_IN_CONT)
        	cont_task_2++;

        //out_critical_region();

        OS_wait_next_period();
    }
}

int main() {
	uint32_t stack_idleThread[40];

    // start the OS
    OS_init(stack_idleThread, sizeof(stack_idleThread));

    parameters_periodic_task_1.deadline_absolute = 500;
    parameters_periodic_task_1.deadline_dinamic = 500;
    parameters_periodic_task_1.period_absolute = 500;
    parameters_periodic_task_1.period_dinamic = 500;

    parameters_periodic_task_2.deadline_absolute = 1000;
    parameters_periodic_task_2.deadline_dinamic = 1000;
    parameters_periodic_task_2.period_absolute = 1000;
    parameters_periodic_task_2.period_dinamic = 1000;

    struct_task1.TCB_thread.task_parameters = &parameters_periodic_task_1;
    struct_task2.TCB_thread.task_parameters = &parameters_periodic_task_2;

    OSPeriodic_task_start(&struct_task1.TCB_thread, 
                    &task1,
                    struct_task1.stack_thread,
                    sizeof(struct_task1.stack_thread));

    OSPeriodic_task_start(&struct_task2.TCB_thread, 
                    &task2,
                    struct_task2.stack_thread,
                    sizeof(struct_task2.stack_thread));

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
}
