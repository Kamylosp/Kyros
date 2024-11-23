#include "main.h"
#include "config_gpio.h"

uint32_t cont_task_1 = 0;
uint32_t cont_task_2 = 0;
uint32_t cont_aperiodic_task_1 = 0;

#define ONE_SEC_IN_CONT 0x6CFFF
#define TWO_SEC_IN_CONT 0xD8FFE
#define THREE_SEC_IN_CONT 0x144FFD

struct_tasks struct_task1;
struct_tasks struct_task2;
struct_tasks struct_aperiodic_task1;
struct_tasks struct_aperiodic_task2;

OSThread_periodics_task_parameters parameters_periodic_task_1;
OSThread_periodics_task_parameters parameters_periodic_task_2;

semaphore_t critical_region_A;
semaphore_t critical_region_B;

uint32_t aux_tick = 0;

void task1(){
    while(1){
        cont_task_1 = 0;

        cont_task_1 = 0;
		while(cont_task_1 < THREE_SEC_IN_CONT)
			cont_task_1++;

        sem_down(&critical_region_A);

        cont_task_1 = 0;
        while(cont_task_1 < THREE_SEC_IN_CONT)
        	cont_task_1++;
        
        sem_down(&critical_region_B);

        cont_task_1 = 0;
        while(cont_task_1 < THREE_SEC_IN_CONT)
        	cont_task_1++;

        sem_up(&critical_region_B);

        cont_task_1 = 0;
        while(cont_task_1 < THREE_SEC_IN_CONT)
        	cont_task_1++;

        sem_up(&critical_region_A);

        OS_wait_next_period();
    }
}

void task2(){
    while(1){

        cont_task_2 = 0;
        while(cont_task_2 < THREE_SEC_IN_CONT)
        	cont_task_2++;
        
        sem_down(&critical_region_B);

        cont_task_2 = 0;
        while(cont_task_2 < THREE_SEC_IN_CONT)
        	cont_task_2++;

        sem_up(&critical_region_B);

        OS_wait_next_period();
    }
}

void aperiodic_task(void){
	cont_aperiodic_task_1 = 0;
	while(cont_aperiodic_task_1 < THREE_SEC_IN_CONT)
		cont_aperiodic_task_1++;

	sem_down(&critical_region_B);

	cont_aperiodic_task_1 = 0;
	while(cont_aperiodic_task_1 < 3*THREE_SEC_IN_CONT)
		cont_aperiodic_task_1++;

	sem_up(&critical_region_B);

	cont_aperiodic_task_1 = 0;
	while(cont_aperiodic_task_1 < THREE_SEC_IN_CONT)
		cont_aperiodic_task_1++;

	OS_finished_aperiodic_task();
}

int main() {
	uint32_t stack_idleThread[40];

    // start the OS
    OS_init(stack_idleThread, sizeof(stack_idleThread));

    parameters_periodic_task_1.deadline_absolute = 2700;
    parameters_periodic_task_1.deadline_dinamic = 2700;
    parameters_periodic_task_1.period_absolute = 2700;
    parameters_periodic_task_1.period_dinamic = 2700;

    parameters_periodic_task_2.deadline_absolute = 2700;
    parameters_periodic_task_2.deadline_dinamic = 2700;
    parameters_periodic_task_2.period_absolute = 2700;
    parameters_periodic_task_2.period_dinamic = 2700;

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

    OSAperiodic_task_start(&struct_aperiodic_task1.TCB_thread,
                            &aperiodic_task,
                            struct_aperiodic_task1.stack_thread,
                            sizeof(struct_aperiodic_task1.stack_thread));
    
    OSAperiodic_task_start(&struct_aperiodic_task2.TCB_thread,
                            &aperiodic_task,
							struct_aperiodic_task2.stack_thread,
                            sizeof(struct_aperiodic_task2.stack_thread));

    semaphore_init(&critical_region_A, 1, 1);
    semaphore_init(&critical_region_B, 1, 1);

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
