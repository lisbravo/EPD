/**
  ******************************************************************************
  * @file           : EPD_Comms.c
  * @brief          : EPaper Communications driver
  * @date			: 21/10/22
  ******************************************************************************
  * @attention
  *
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
**/
#include "spi.h"
#include "../Inc/EPD_Comms.h"

extern SPI_HandleTypeDef hspi1;
void EPD_SPI_WriteByte(UBYTE value)
{
    HAL_SPI_Transmit(&hspi1, &value, 1, 1000);
}

int EPD_Module_Init(void)
{
    EPD_Digital_Write(EPD_DC_PIN, 0);
    EPD_Digital_Write(EPD_CS_PIN, 0);
    EPD_Digital_Write(EPD_RST_PIN, 1);
	return 0;
}

void EPD_Module_Exit(void)
{
    EPD_Digital_Write(EPD_DC_PIN, 0);
    EPD_Digital_Write(EPD_CS_PIN, 0);

    //close 5V
    EPD_Digital_Write(EPD_RST_PIN, 0);
}

