/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "servo_cfg.h"
#include "usart.h"
#include "queue.h"
#include "Segment_cfg.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

extern uint8_t ir_sensor_1 ;
extern uint8_t ir_sensor_2 ;
extern uint8_t traffic_1_counter ;

extern uint8_t blurtooth_send[5] ;
extern uint8_t reciever  ;
extern uint8_t traffic_send ;
extern uint8_t data ;
extern uint8_t data2 ;
extern uint8_t stop_data ;

extern uint8_t previous_state;
extern uint8_t previous_state_urduino;

extern uint8_t flag ;

uint8_t segment_counter;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal2,
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for myTask03 */
osThreadId_t myTask03Handle;
const osThreadAttr_t myTask03_attributes = {
  .name = "myTask03",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow3,
};
/* Definitions for myTask04 */
osThreadId_t myTask04Handle;
const osThreadAttr_t myTask04_attributes = {
  .name = "myTask04",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal4,
};
/* Definitions for myTask05 */
osThreadId_t myTask05Handle;
const osThreadAttr_t myTask05_attributes = {
  .name = "myTask05",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for myQueuereceive */
osMessageQueueId_t myQueuereceiveHandle;
const osMessageQueueAttr_t myQueuereceive_attributes = {
  .name = "myQueuereceive"
};
/* Definitions for myBinaryTraffic */
osSemaphoreId_t myBinaryTrafficHandle;
const osSemaphoreAttr_t myBinaryTraffic_attributes = {
  .name = "myBinaryTraffic"
};
/* Definitions for segmentSem02 */
osSemaphoreId_t segmentSem02Handle;
const osSemaphoreAttr_t segmentSem02_attributes = {
  .name = "segmentSem02"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void traffic_light(void *argument);
void servo_control(void *argument);
void StartTrans(void *argument);
void display(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of myBinaryTraffic */
  myBinaryTrafficHandle = osSemaphoreNew(1, 1, &myBinaryTraffic_attributes);

  /* creation of segmentSem02 */
  segmentSem02Handle = osSemaphoreNew(1, 1, &segmentSem02_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of myQueuereceive */
  myQueuereceiveHandle = osMessageQueueNew (10, sizeof(uint8_t), &myQueuereceive_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(traffic_light, NULL, &myTask02_attributes);

  /* creation of myTask03 */
  myTask03Handle = osThreadNew(servo_control, NULL, &myTask03_attributes);

  /* creation of myTask04 */
  myTask04Handle = osThreadNew(StartTrans, NULL, &myTask04_attributes);

  /* creation of myTask05 */
  myTask05Handle = osThreadNew(display, NULL, &myTask05_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	  traffic_1_counter++;
	  segment_counter++;
	  		if(traffic_1_counter <= 20){
	  			HAL_GPIO_WritePin(GPIOB, traffic1_green_Pin,  GPIO_PIN_RESET);
	  			HAL_GPIO_WritePin(GPIOB, traffic1_yellow_Pin, GPIO_PIN_RESET);
	  			HAL_GPIO_WritePin(GPIOB, traffic1_red_Pin,    GPIO_PIN_SET);
	  			HAL_GPIO_WritePin(GPIOB, traffic3_green_Pin,  GPIO_PIN_RESET);
	  			HAL_GPIO_WritePin(GPIOB, traffic3_yellow_Pin, GPIO_PIN_RESET);
	  			HAL_GPIO_WritePin(GPIOB, traffic3_red_Pin,    GPIO_PIN_SET);
	  			osSemaphoreAcquire(myBinaryTrafficHandle, 100);
	  			traffic_send = 'Z';
	  			if(traffic_1_counter == 20){
	  				osSemaphoreAcquire(segmentSem02Handle, 100);
	  				segment_counter =0 ;
	  				osSemaphoreRelease(segmentSem02Handle);
	  			}
	  			osSemaphoreRelease(myBinaryTrafficHandle);
	  		}else if((traffic_1_counter > 20) && (traffic_1_counter <= 80)){
	  			HAL_GPIO_WritePin(GPIOB, traffic1_green_Pin,  GPIO_PIN_SET);
	  			HAL_GPIO_WritePin(GPIOB, traffic1_yellow_Pin, GPIO_PIN_RESET);
	  			HAL_GPIO_WritePin(GPIOB, traffic1_red_Pin,    GPIO_PIN_RESET);
	  			HAL_GPIO_WritePin(GPIOB, traffic3_green_Pin,  GPIO_PIN_SET);
	  			HAL_GPIO_WritePin(GPIOB, traffic3_yellow_Pin, GPIO_PIN_RESET);
	  			HAL_GPIO_WritePin(GPIOB, traffic3_red_Pin,    GPIO_PIN_RESET);
	  			osSemaphoreAcquire(myBinaryTrafficHandle, 100);
	  			traffic_send = 'X';
	  			if(traffic_1_counter == 0){
	  				osSemaphoreAcquire(segmentSem02Handle, 100);
	  				segment_counter =0 ;
	  				osSemaphoreRelease(segmentSem02Handle);
	  			}
	  			osSemaphoreRelease(myBinaryTrafficHandle);
	  		}else if((traffic_1_counter > 80) && (traffic_1_counter <= 85)){
	  			HAL_GPIO_WritePin(GPIOB, traffic1_green_Pin,  GPIO_PIN_RESET);
	  			HAL_GPIO_WritePin(GPIOB, traffic1_yellow_Pin, GPIO_PIN_SET);
	  			HAL_GPIO_WritePin(GPIOB, traffic1_red_Pin,    GPIO_PIN_RESET);
	  			HAL_GPIO_WritePin(GPIOB, traffic3_green_Pin,  GPIO_PIN_RESET);
	  			HAL_GPIO_WritePin(GPIOB, traffic3_yellow_Pin, GPIO_PIN_SET);
	  			HAL_GPIO_WritePin(GPIOB, traffic3_red_Pin,    GPIO_PIN_RESET);
	  			osSemaphoreAcquire(myBinaryTrafficHandle, 100);
	  			traffic_send = 'Y';
	  			if(traffic_1_counter == 85) {
	  				traffic_1_counter = 0;
	  				osSemaphoreAcquire(segmentSem02Handle, 100);
	  				segment_counter =0 ;
	  				osSemaphoreRelease(segmentSem02Handle);
	  			}
	  			osSemaphoreRelease(myBinaryTrafficHandle);
	  		}
	  	  if(previous_state != data2){
	  		  previous_state = data2;
	  		  HAL_UART_Transmit(&huart1, &data2, 1, HAL_MAX_DELAY);
	  	  }
    osDelay(1000);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_traffic_light */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_traffic_light */
void traffic_light(void *argument)
{
  /* USER CODE BEGIN traffic_light */
  /* Infinite loop */
  for(;;)
  {
	      ir_sensor_1 = HAL_GPIO_ReadPin(GPIOA, ir_1_Pin);
	  	  ir_sensor_2 = HAL_GPIO_ReadPin(GPIOA, ir_2_Pin);

	  	  if((ir_sensor_1 == GPIO_PIN_RESET) || (ir_sensor_2 == GPIO_PIN_RESET)){
	  		  servo_Motor_Start_angle_90(&servo);
	  	  }else{
	  		  servo_Motor_Start_angle_N90(&servo);
	  	  }
    osDelay(10);
  }
  /* USER CODE END traffic_light */
}

/* USER CODE BEGIN Header_servo_control */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_servo_control */
void servo_control(void *argument)
{
  /* USER CODE BEGIN servo_control */
  /* Infinite loop */
  for(;;)
  {
	  xQueueReceive(myQueuereceiveHandle,&data,100);
	  //data = reciever;
	  if (osSemaphoreAcquire(myBinaryTrafficHandle, 100) == osOK) {
	  data2 = traffic_send;
	  if ((traffic_send == 'Z') && (flag == 0)) {
	      HAL_UART_Transmit(&huart2, &stop_data, 1, HAL_MAX_DELAY);
	      flag = 1;  // Set flag to avoid repeated transmissions
	  } else if (traffic_send != 'Z') {
	      if (previous_state_urduino != data) {
	          previous_state_urduino = data;
	          HAL_UART_Transmit(&huart2, &data, 1, HAL_MAX_DELAY);
	      }
	      flag = 0;  // Reset flag when traffic is not 'Z'
	  }
	  if(previous_state != data2){
	  		  previous_state = data2;
	  		  HAL_UART_Transmit(&huart1, &data2, 1, HAL_MAX_DELAY);
	  	  }
	    osSemaphoreRelease(myBinaryTrafficHandle);
	}
    osDelay(50);
  }
  /* USER CODE END servo_control */
}

/* USER CODE BEGIN Header_StartTrans */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTrans */
void StartTrans(void *argument)
{
  /* USER CODE BEGIN StartTrans */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTrans */
}

/* USER CODE BEGIN Header_display */
/**
* @brief Function implementing the myTask05 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_display */
void display(void *argument)
{
  /* USER CODE BEGIN display */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	  osSemaphoreAcquire(segmentSem02Handle, 100);
	  segment_wright_logic(&segment,segment_counter/10);
	  osSemaphoreRelease(segmentSem02Handle);
	  osDelay(10);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
	  osSemaphoreAcquire(segmentSem02Handle, 100);
	  segment_wright_logic(&segment,segment_counter%10);
	  osSemaphoreRelease(segmentSem02Handle);
	  osDelay(10);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
  }
  /* USER CODE END display */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {

    	HAL_UART_Receive_IT(&huart1, &reciever, 1);
    	xQueueSendToBackFromISR(myQueuereceiveHandle,(void *)&reciever,NULL);
    }
}
/* USER CODE END Application */

