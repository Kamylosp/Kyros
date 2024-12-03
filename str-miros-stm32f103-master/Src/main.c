#include <stdint.h>
#include <stdlib.h>
#include "miros.h"
#include "pid.h"
#include "VL53L0X.h"
#include "config_gpio.h"

struct_tasks struct_distance_sensor_task;
struct_tasks struct_pwm_actuator_task;
struct_tasks struct_aperiodic_task;

OSThread_periodics_task_parameters parameters_distance_sensor_task;
OSThread_periodics_task_parameters parameters_pwm_actuator_task;

PIDController pidController;
semaphore_t mutex;

struct VL53L0X distanceSensor;

static struct VL53L0X myTOFsensor = {.io_2v8 = true, .address = 0b0101001, .io_timeout = 500, .did_timeout = false};

/*
Na biblioteca do VL53L0X, tem duas funções que a gente pode usar. Como a gente deve criar a task periodica pelo miros, 
parece que tem q chamar essa função do startContinuous passando 0 como periodo no parâmetro, e dai a task q chama essa função
precisa ter um periodo de 50ms. A outra alternativa seria passar 50ms direto no parametro dessa função, mas acho q quem define 
o periodo é o miros, dai me parece que a primeira opcao seria a mais certa. Só precisa verificar se, quando o periodo é 0, ele 
n fica num loop infinito lendo as temperaturas..

// Start continuous ranging measurements. If period_ms (optional) is 0 or not
// given, continuous back-to-back mode is used (the sensor takes measurements as
// often as possible); otherwise, continuous timed mode is used, with the given
// inter-measurement period in milliseconds determining how often the sensor
// takes a measurement.
// based on VL53L0X_StartMeasurement()
void VL53L0X_startContinuous(struct VL53L0X* dev, uint32_t period_ms)

// Performs a single-shot range measurement and returns the reading in
// millimeters
// based on VL53L0X_PerformSingleRangingMeasurement()
uint16_t VL53L0X_readRangeSingleMillimeters(struct VL53L0X* dev)
*/
void read_distance_sensor();
void pwm_actuator();
void distance_sensor_init();
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);


int main() {
	uint32_t stack_idleThread[40];

    OS_init(stack_idleThread, sizeof(stack_idleThread));

    MX_GPIO_Init();
    semaphore_init(&mutex, 1, 1);
    PID_setup(&pidController, -0.0001, -0.00001, -0.00001, 0.02, 0.3, -0.3);
    distance_sensor_init();

    parameters_distance_sensor_task.deadline_absolute = 5;
    parameters_distance_sensor_task.deadline_dinamic = 5;
    parameters_distance_sensor_task.period_absolute = 5;
    parameters_distance_sensor_task.period_dinamic = 5;

    parameters_pwm_actuator_task.deadline_absolute = 5;
    parameters_pwm_actuator_task.deadline_dinamic = 5;
    parameters_pwm_actuator_task.period_absolute = 5;
    parameters_pwm_actuator_task.period_dinamic = 5;

    struct_distance_sensor_task.TCB_thread.task_parameters = &parameters_distance_sensor_task;
    struct_pwm_actuator_task.TCB_thread.task_parameters = &parameters_pwm_actuator_task;

    OSPeriodic_task_start(&struct_distance_sensor_task.TCB_thread, 
                            &read_distance_sensor,
                            struct_distance_sensor_task.stack_thread,
                            sizeof(struct_distance_sensor_task.stack_thread));

    OSPeriodic_task_start(&struct_pwm_actuator_task.TCB_thread, 
                            &pwm_actuator,
                            struct_pwm_actuator_task.stack_thread,
                            sizeof(struct_pwm_actuator_task.stack_thread));

    OS_run();
}

void read_distance_sensor(){
    while(1){
        float currentDistance = VL53L0X_readRangeSingleMillimeters(&distanceSensor);
        PID_setInput(&pidController, currentDistance, &mutex);
        OS_wait_next_period();
    }
}

void pwm_actuator(){
    while(1){
        float pwmVal = PID_action(&pidController, &mutex);
        // Comandar PWM;
        OS_wait_next_period();
    }
}


void aperiodic_task(){
    sem_down(&mutex);

    if (pidController.setpoint == 0.02)
        pidController.setpoint = 0.04;
    else 
        pidController.setpoint = 0.02;
    
    sem_up(&mutex);
    
    OS_finished_aperiodic_task();
}

void distance_sensor_init() {

    VL53L0X_init(&myTOFsensor);
	VL53L0X_setMeasurementTimingBudget(&myTOFsensor, 20e3); // 20 ms
	VL53L0X_startContinuous(&myTOFsensor, 0);
    
    return;
}


uint32_t previousTick = 0;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	uint32_t currentTick = HAL_GetTick();

	if (GPIO_Pin == GPIO_PIN_0 && (currentTick - previousTick) > 10){
		    OSAperiodic_task_start(&struct_aperiodic_task.TCB_thread,
                                    &aperiodic_task,
                                    struct_aperiodic_task.stack_thread,
                                    sizeof(struct_aperiodic_task.stack_thread));
	}
}
