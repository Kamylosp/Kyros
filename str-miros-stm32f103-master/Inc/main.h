#ifndef __MAIN_H
#define __MAIN_H

#include <stdint.h>
#include <stdlib.h>
#include "miros.h"
#include "stm32f1xx_hal.h"

#define Button_Pin GPIO_PIN_0
#define Button_GPIO_Port GPIOB
#define Button_EXTI_IRQn EXTI0_IRQn

void task1();
void task2();
void task3();

void aperiodic_task_1();
void aperiodic_task_2();
#endif
