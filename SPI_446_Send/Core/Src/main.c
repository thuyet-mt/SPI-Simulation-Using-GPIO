#include "main.h"
#include <stdlib.h>
#include <string.h>
#define HIGH 1
#define LOW 0
#define TFull 100
#define THalf TFull/2


#define MOSI_HIGH HAL_GPIO_WritePin(GPIOA, MOSI_Pin, HIGH)
#define MOSI_LOW  HAL_GPIO_WritePin(GPIOA, MOSI_Pin, LOW)

#define SS_HIGH HAL_GPIO_WritePin(GPIOA, SS_Pin, HIGH)
#define SS_LOW  HAL_GPIO_WritePin(GPIOA, SS_Pin, LOW)

#define SCK_HIGH HAL_GPIO_WritePin(GPIOA, SCK_Pin, HIGH)
#define SCK_LOW  HAL_GPIO_WritePin(GPIOA, SCK_Pin, LOW)

#define read_MISO ((HAL_GPIO_ReadPin(GPIOA, MISO_Pin))? HIGH:LOW)
TIM_HandleTypeDef htim1;
uint8_t rev;
char str[]="Hello World 2022";
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
void delay (uint16_t delay);
void SPI_setup(void);
void SPI_begin(void);
void SPI_end(void);
uint8_t SPI_transfer(uint8_t byte_out);
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM1_Init();
  HAL_TIM_Base_Start(&htim1);
    while (1)
  {
    	  for (int i=0; i<strlen(str);i++){
		  SPI_setup();
		  SPI_begin();
		  rev = SPI_transfer(str[i]);
				  SPI_end();
		  HAL_Delay(0.001);
	  }

  }
}
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}
static void MX_TIM1_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 1-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0xffff-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOA, LD2_Pin|SS_Pin|MOSI_Pin|SCK_Pin, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = LD2_Pin|SS_Pin|MOSI_Pin|SCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = MISO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MISO_GPIO_Port, &GPIO_InitStruct);

}
void delay (uint16_t delay){
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	while( __HAL_TIM_GET_COUNTER(&htim1) < delay );
}

void SPI_setup(void){
	SCK_LOW;
	SS_HIGH;
	HAL_Delay(1);
}

void SPI_begin(void){
	SS_LOW;
}

void SPI_end(void){
	SCK_LOW;
	SS_HIGH;
}
uint8_t SPI_transfer(uint8_t byte_out){
	uint8_t byte_in = 0;
	uint8_t ibit, res;
	for(ibit = 0x80;ibit>0;ibit = ibit>>1){
		res= byte_out & ibit;
		if(res){
			MOSI_HIGH;
		}
		else {
			MOSI_LOW;
		}
		delay(THalf);
		SCK_HIGH;

		if(read_MISO==HIGH){
			byte_in = byte_in | ibit;
		}
		delay(THalf);
		SCK_LOW;
	}
	return byte_in;
}
void Error_Handler(void)
{
    __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif 
