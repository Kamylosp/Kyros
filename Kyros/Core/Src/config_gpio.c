#include "config_gpio.h"
<<<<<<< HEAD:str-miros-stm32f103-master/Src/config_gpio.c
#include "stm32f1xx_hal.h"

/* Conections:

button: B0

PWM : A0

Sensor de distância:
    SCL: B6
    SDA: B7 */
=======
>>>>>>> main:Kyros/Core/Src/config_gpio.c

void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
<<<<<<< HEAD:str-miros-stm32f103-master/Src/config_gpio.c
  __HAL_RCC_GPIOA_CLK_ENABLE();
=======
>>>>>>> main:Kyros/Core/Src/config_gpio.c

  GPIO_InitStruct.Pin = Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Button_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 1U, 1U);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
<<<<<<< HEAD:str-miros-stm32f103-master/Src/config_gpio.c

=======
>>>>>>> main:Kyros/Core/Src/config_gpio.c
