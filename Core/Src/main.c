/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

DMA_HandleTypeDef hdma_memtomem_dma1_stream0;
DMA_HandleTypeDef hdma_memtomem_dma1_stream1;
DMA_HandleTypeDef hdma_memtomem_dma1_stream2;
DMA_HandleTypeDef hdma_memtomem_dma1_stream3;
DMA_HandleTypeDef hdma_memtomem_dma1_stream4;
DMA_HandleTypeDef hdma_memtomem_dma1_stream5;
DMA_HandleTypeDef hdma_memtomem_dma1_stream6;
DMA_HandleTypeDef hdma_memtomem_dma1_stream7;
MDMA_HandleTypeDef hmdma_mdma_channel0_dma1_stream0_tc_0;
/* USER CODE BEGIN PV */
volatile uint32_t time1;
volatile uint32_t time2;
volatile uint32_t diff;

#define  ARRAYLEN 0x3400 //53248B 13312W
uint32_t i; 
uint32_t a[ARRAYLEN]__attribute__((aligned(8)));
uint32_t b[ARRAYLEN]__attribute__((aligned(8)));
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_DMA_Init(void);
static void MX_MDMA_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
 __attribute__((optimize("no-tree-loop-distribute-patterns")))
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  HAL_SuspendTick();
  DWT->CTRL|=DWT_CTRL_CYCCNTENA_Msk;
  time1=DWT->CYCCNT;
//  for (i=0; i<ARRAYLEN; i++) {
//    b[i] = a[i];
//  }
  memcpy(b,a,ARRAYLEN*4);
  time2=DWT->CYCCNT;
  diff=time2-time1;



  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_DMA_Init();
  MX_MDMA_Init();
  /* USER CODE BEGIN 2 */
   HAL_DMA_Start(&hdma_memtomem_dma1_stream0,a,b,ARRAYLEN);
   HAL_DMA_Start(&hdma_memtomem_dma1_stream1,a,b,ARRAYLEN);
   HAL_DMA_Start(&hdma_memtomem_dma1_stream2,a,b,ARRAYLEN);
   HAL_DMA_Start(&hdma_memtomem_dma1_stream3,a,b,ARRAYLEN);
   HAL_DMA_Start(&hdma_memtomem_dma1_stream4,a,b,ARRAYLEN);
   HAL_DMA_Start(&hdma_memtomem_dma1_stream5,a,b,ARRAYLEN);
   HAL_DMA_Start(&hdma_memtomem_dma1_stream6,a,b,ARRAYLEN);
   HAL_DMA_Start(&hdma_memtomem_dma1_stream7,a,b,ARRAYLEN);

  DWT->CTRL|=DWT_CTRL_CYCCNTENA_Msk;
  time1=DWT->CYCCNT;
   __HAL_DMA_ENABLE(&hdma_memtomem_dma1_stream0);
  __HAL_DMA_ENABLE(&hdma_memtomem_dma1_stream1);
   __HAL_DMA_ENABLE(&hdma_memtomem_dma1_stream2);
   __HAL_DMA_ENABLE(&hdma_memtomem_dma1_stream3);
   __HAL_DMA_ENABLE(&hdma_memtomem_dma1_stream4);
   __HAL_DMA_ENABLE(&hdma_memtomem_dma1_stream5);
   __HAL_DMA_ENABLE(&hdma_memtomem_dma1_stream6);
   __HAL_DMA_ENABLE(&hdma_memtomem_dma1_stream7);
  HAL_DMA_PollForTransfer(&hdma_memtomem_dma1_stream7, HAL_DMA_FULL_TRANSFER, 0xFFFFFFFF);
  time2=DWT->CYCCNT;
  diff=time2-time1;

  HAL_MDMA_Start(&hmdma_mdma_channel0_dma1_stream0_tc_0, a, b, ARRAYLEN*4, 0);
  DWT->CTRL|=DWT_CTRL_CYCCNTENA_Msk;
  time1=DWT->CYCCNT;

  /* activate If SW request mode*/
  __HAL_MDMA_ENABLE(&hmdma_mdma_channel0_dma1_stream0_tc_0);
  hmdma_mdma_channel0_dma1_stream0_tc_0.Instance->CCR |=  MDMA_CCR_SWRQ;
  HAL_MDMA_PollForTransfer(&hmdma_mdma_channel0_dma1_stream0_tc_0, HAL_MDMA_FULL_TRANSFER, 0xFFFFFFFF);
  time2=DWT->CYCCNT;
  diff=time2-time1;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * Enable DMA controller clock
  * Configure DMA for memory to memory transfers
  *   hdma_memtomem_dma1_stream0
  *   hdma_memtomem_dma1_stream1
  *   hdma_memtomem_dma1_stream2
  *   hdma_memtomem_dma1_stream3
  *   hdma_memtomem_dma1_stream4
  *   hdma_memtomem_dma1_stream5
  *   hdma_memtomem_dma1_stream6
  *   hdma_memtomem_dma1_stream7
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* Configure DMA request hdma_memtomem_dma1_stream0 on DMA1_Stream0 */
  hdma_memtomem_dma1_stream0.Instance = DMA1_Stream0;
  hdma_memtomem_dma1_stream0.Init.Request = DMA_REQUEST_MEM2MEM;
  hdma_memtomem_dma1_stream0.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma1_stream0.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma1_stream0.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma1_stream0.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_memtomem_dma1_stream0.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_memtomem_dma1_stream0.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma1_stream0.Init.Priority = DMA_PRIORITY_LOW;
  hdma_memtomem_dma1_stream0.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  hdma_memtomem_dma1_stream0.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  hdma_memtomem_dma1_stream0.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_memtomem_dma1_stream0.Init.PeriphBurst = DMA_PBURST_SINGLE;
  if (HAL_DMA_Init(&hdma_memtomem_dma1_stream0) != HAL_OK)
  {
    Error_Handler( );
  }

  /* Configure DMA request hdma_memtomem_dma1_stream1 on DMA1_Stream1 */
  hdma_memtomem_dma1_stream1.Instance = DMA1_Stream1;
  hdma_memtomem_dma1_stream1.Init.Request = DMA_REQUEST_MEM2MEM;
  hdma_memtomem_dma1_stream1.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma1_stream1.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma1_stream1.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma1_stream1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_memtomem_dma1_stream1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_memtomem_dma1_stream1.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma1_stream1.Init.Priority = DMA_PRIORITY_LOW;
  hdma_memtomem_dma1_stream1.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  hdma_memtomem_dma1_stream1.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  hdma_memtomem_dma1_stream1.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_memtomem_dma1_stream1.Init.PeriphBurst = DMA_PBURST_SINGLE;
  if (HAL_DMA_Init(&hdma_memtomem_dma1_stream1) != HAL_OK)
  {
    Error_Handler( );
  }

  /* Configure DMA request hdma_memtomem_dma1_stream2 on DMA1_Stream2 */
  hdma_memtomem_dma1_stream2.Instance = DMA1_Stream2;
  hdma_memtomem_dma1_stream2.Init.Request = DMA_REQUEST_MEM2MEM;
  hdma_memtomem_dma1_stream2.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma1_stream2.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma1_stream2.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma1_stream2.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_memtomem_dma1_stream2.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_memtomem_dma1_stream2.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma1_stream2.Init.Priority = DMA_PRIORITY_LOW;
  hdma_memtomem_dma1_stream2.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  hdma_memtomem_dma1_stream2.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  hdma_memtomem_dma1_stream2.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_memtomem_dma1_stream2.Init.PeriphBurst = DMA_PBURST_SINGLE;
  if (HAL_DMA_Init(&hdma_memtomem_dma1_stream2) != HAL_OK)
  {
    Error_Handler( );
  }

  /* Configure DMA request hdma_memtomem_dma1_stream3 on DMA1_Stream3 */
  hdma_memtomem_dma1_stream3.Instance = DMA1_Stream3;
  hdma_memtomem_dma1_stream3.Init.Request = DMA_REQUEST_MEM2MEM;
  hdma_memtomem_dma1_stream3.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma1_stream3.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma1_stream3.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma1_stream3.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_memtomem_dma1_stream3.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_memtomem_dma1_stream3.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma1_stream3.Init.Priority = DMA_PRIORITY_LOW;
  hdma_memtomem_dma1_stream3.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  hdma_memtomem_dma1_stream3.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  hdma_memtomem_dma1_stream3.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_memtomem_dma1_stream3.Init.PeriphBurst = DMA_PBURST_SINGLE;
  if (HAL_DMA_Init(&hdma_memtomem_dma1_stream3) != HAL_OK)
  {
    Error_Handler( );
  }

  /* Configure DMA request hdma_memtomem_dma1_stream4 on DMA1_Stream4 */
  hdma_memtomem_dma1_stream4.Instance = DMA1_Stream4;
  hdma_memtomem_dma1_stream4.Init.Request = DMA_REQUEST_MEM2MEM;
  hdma_memtomem_dma1_stream4.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma1_stream4.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma1_stream4.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma1_stream4.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_memtomem_dma1_stream4.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_memtomem_dma1_stream4.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma1_stream4.Init.Priority = DMA_PRIORITY_LOW;
  hdma_memtomem_dma1_stream4.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  hdma_memtomem_dma1_stream4.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  hdma_memtomem_dma1_stream4.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_memtomem_dma1_stream4.Init.PeriphBurst = DMA_PBURST_SINGLE;
  if (HAL_DMA_Init(&hdma_memtomem_dma1_stream4) != HAL_OK)
  {
    Error_Handler( );
  }

  /* Configure DMA request hdma_memtomem_dma1_stream5 on DMA1_Stream5 */
  hdma_memtomem_dma1_stream5.Instance = DMA1_Stream5;
  hdma_memtomem_dma1_stream5.Init.Request = DMA_REQUEST_MEM2MEM;
  hdma_memtomem_dma1_stream5.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma1_stream5.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma1_stream5.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma1_stream5.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_memtomem_dma1_stream5.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_memtomem_dma1_stream5.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma1_stream5.Init.Priority = DMA_PRIORITY_LOW;
  hdma_memtomem_dma1_stream5.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  hdma_memtomem_dma1_stream5.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  hdma_memtomem_dma1_stream5.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_memtomem_dma1_stream5.Init.PeriphBurst = DMA_PBURST_SINGLE;
  if (HAL_DMA_Init(&hdma_memtomem_dma1_stream5) != HAL_OK)
  {
    Error_Handler( );
  }

  /* Configure DMA request hdma_memtomem_dma1_stream6 on DMA1_Stream6 */
  hdma_memtomem_dma1_stream6.Instance = DMA1_Stream6;
  hdma_memtomem_dma1_stream6.Init.Request = DMA_REQUEST_MEM2MEM;
  hdma_memtomem_dma1_stream6.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma1_stream6.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma1_stream6.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma1_stream6.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_memtomem_dma1_stream6.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_memtomem_dma1_stream6.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma1_stream6.Init.Priority = DMA_PRIORITY_LOW;
  hdma_memtomem_dma1_stream6.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  hdma_memtomem_dma1_stream6.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  hdma_memtomem_dma1_stream6.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_memtomem_dma1_stream6.Init.PeriphBurst = DMA_PBURST_SINGLE;
  if (HAL_DMA_Init(&hdma_memtomem_dma1_stream6) != HAL_OK)
  {
    Error_Handler( );
  }

  /* Configure DMA request hdma_memtomem_dma1_stream7 on DMA1_Stream7 */
  hdma_memtomem_dma1_stream7.Instance = DMA1_Stream7;
  hdma_memtomem_dma1_stream7.Init.Request = DMA_REQUEST_MEM2MEM;
  hdma_memtomem_dma1_stream7.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma1_stream7.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma1_stream7.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma1_stream7.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_memtomem_dma1_stream7.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_memtomem_dma1_stream7.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma1_stream7.Init.Priority = DMA_PRIORITY_LOW;
  hdma_memtomem_dma1_stream7.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  hdma_memtomem_dma1_stream7.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  hdma_memtomem_dma1_stream7.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_memtomem_dma1_stream7.Init.PeriphBurst = DMA_PBURST_SINGLE;
  if (HAL_DMA_Init(&hdma_memtomem_dma1_stream7) != HAL_OK)
  {
    Error_Handler( );
  }

}

/**
  * Enable MDMA controller clock
  * Configure MDMA for global transfers
  *   hmdma_mdma_channel0_dma1_stream0_tc_0
  */
static void MX_MDMA_Init(void)
{

  /* MDMA controller clock enable */
  __HAL_RCC_MDMA_CLK_ENABLE();
  /* Local variables */

  /* Configure MDMA channel MDMA_Channel0 */
  /* Configure MDMA request hmdma_mdma_channel0_dma1_stream0_tc_0 on MDMA_Channel0 */
  hmdma_mdma_channel0_dma1_stream0_tc_0.Instance = MDMA_Channel0;
  hmdma_mdma_channel0_dma1_stream0_tc_0.Init.Request = MDMA_REQUEST_DMA1_Stream0_TC;
  hmdma_mdma_channel0_dma1_stream0_tc_0.Init.TransferTriggerMode = MDMA_BUFFER_TRANSFER;
  hmdma_mdma_channel0_dma1_stream0_tc_0.Init.Priority = MDMA_PRIORITY_LOW;
  hmdma_mdma_channel0_dma1_stream0_tc_0.Init.Endianness = MDMA_LITTLE_ENDIANNESS_PRESERVE;
  hmdma_mdma_channel0_dma1_stream0_tc_0.Init.SourceInc = MDMA_SRC_INC_DOUBLEWORD;
  hmdma_mdma_channel0_dma1_stream0_tc_0.Init.DestinationInc = MDMA_DEST_INC_DOUBLEWORD;
  hmdma_mdma_channel0_dma1_stream0_tc_0.Init.SourceDataSize = MDMA_SRC_DATASIZE_DOUBLEWORD;
  hmdma_mdma_channel0_dma1_stream0_tc_0.Init.DestDataSize = MDMA_DEST_DATASIZE_DOUBLEWORD;
  hmdma_mdma_channel0_dma1_stream0_tc_0.Init.DataAlignment = MDMA_DATAALIGN_PACKENABLE;
  hmdma_mdma_channel0_dma1_stream0_tc_0.Init.BufferTransferLength = ARRAYLEN*4;
  hmdma_mdma_channel0_dma1_stream0_tc_0.Init.SourceBurst = MDMA_SOURCE_BURST_SINGLE;
  hmdma_mdma_channel0_dma1_stream0_tc_0.Init.DestBurst = MDMA_DEST_BURST_SINGLE;
  hmdma_mdma_channel0_dma1_stream0_tc_0.Init.SourceBlockAddressOffset = 0;
  hmdma_mdma_channel0_dma1_stream0_tc_0.Init.DestBlockAddressOffset = 0;
  if (HAL_MDMA_Init(&hmdma_mdma_channel0_dma1_stream0_tc_0) != HAL_OK)
  {
    Error_Handler();
  }

  /* Configure post request address and data masks */
  if (HAL_MDMA_ConfigPostRequestMask(&hmdma_mdma_channel0_dma1_stream0_tc_0, 0, 0) != HAL_OK)
  {
    Error_Handler();
  }

  /* MDMA interrupt initialization */
  /* MDMA_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(MDMA_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(MDMA_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
