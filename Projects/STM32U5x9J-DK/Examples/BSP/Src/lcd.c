/**
  ******************************************************************************
  * @file    Examples/BSP/Src/lcd.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the LCD feature in the
  *          STM32U599J_DK discovery driver
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stlogo.h"
#include "rect_buff.h"
#include "stm32_lcd.h"
/** @addtogroup STM32L5xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO TS_State_t TS_State;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void Lcd_SetHint(void);

/**
  * @brief  LCD demo
  * @param  None
  * @retval 0 if ok, else value < 0.
  */
int32_t Lcd_demo(uint32_t argbColor, uint32_t xPos, uint32_t yPos)
{
  int32_t   result = 0;
  uint32_t  Brightness;
  uint32_t  Format;
  uint32_t  Xsize = LCD_WIDTH, Ysize = LCD_HEIGHT;

  /* Set the brightness */
  if (BSP_LCD_SetBrightness(0, 100) != BSP_ERROR_FEATURE_NOT_SUPPORTED) result--;

  /* Get the brightness */
  if (BSP_LCD_GetBrightness(0, &Brightness) != BSP_ERROR_FEATURE_NOT_SUPPORTED) result--;

  /* Get the format */
  if (BSP_LCD_GetFormat(0, &Format) != BSP_ERROR_NONE) result--;
  if (Format != LCD_PIXEL_FORMAT_ARGB8888) result--;

  /* Get the display Xsize */
  if (BSP_LCD_GetXSize(0, &Xsize) != BSP_ERROR_NONE) result--;
  if (Xsize != LCD_WIDTH) result--;

  /* Get the display Ysize */
  if (BSP_LCD_GetYSize(0, &Ysize) != BSP_ERROR_NONE) result--;
  if (Ysize != LCD_HEIGHT) result--;

  /* Set active layer */
  if (BSP_LCD_SetActiveLayer(0, 0) != BSP_ERROR_NONE) result--;

  /* Clean display */
  uint32_t i;
  uint32_t j;

  for (i = 0; i < Xsize; i++)
  {
    for (j = 0; j < Ysize; j++)
    {
      if (BSP_LCD_WritePixel(0, i, j, argbColor) != BSP_ERROR_NONE) result--;
    }
  }

  Lcd_SetHint();

  /* Set the display on */
  if (BSP_LCD_DisplayOn(0) != BSP_ERROR_NONE) result--;

  /* Display a bitmap */
  if (BSP_LCD_DrawBitmap(0, xPos, yPos, (uint8_t *)stlogo) != BSP_ERROR_NONE) result--;

  return result;
}

/**
  * @brief  Display lcd demo hint
  * @param  None
  * @retval None
  */
static void Lcd_SetHint(void)
{
  /* Clear the LCD */
  //BSP_LCD_FillRect(0, 0, 0, 480, 480, LCD_COLOR_BLACK);

  /* Display text */
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_LIGHTBLUE);
  //UTIL_LCD_DisplayStringAt(0, 170, (uint8_t *)"Test of LCD", CENTER_MODE);
}

/**
  * @}
  */

/**
  * @}
  */



