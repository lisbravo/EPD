/**
  ******************************************************************************
  * @file           : EPD_2in13.h
  * @brief          : 2.13 EPD driver
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
#include "../Inc/EPD_2in13d.h"
#include "Debug.h"
#include <stdbool.h>
/**
 * full screen update LUT
**/
static const unsigned char EPD_2IN13D_lut_vcomDC[] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x02,
    0x60, 0x28, 0x28, 0x00, 0x00, 0x01,
    0x00, 0x14, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x12, 0x12, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
};
static const unsigned char EPD_2IN13D_lut_ww[] = {
    0x40, 0x08, 0x00, 0x00, 0x00, 0x02,
    0x90, 0x28, 0x28, 0x00, 0x00, 0x01,
    0x40, 0x14, 0x00, 0x00, 0x00, 0x01,
    0xA0, 0x12, 0x12, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const unsigned char EPD_2IN13D_lut_bw[] = {
    0x40, 0x17, 0x00, 0x00, 0x00, 0x02,
    0x90, 0x0F, 0x0F, 0x00, 0x00, 0x03,
    0x40, 0x0A, 0x01, 0x00, 0x00, 0x01,
    0xA0, 0x0E, 0x0E, 0x00, 0x00, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const unsigned char EPD_2IN13D_lut_wb[] = {
    0x80, 0x08, 0x00, 0x00, 0x00, 0x02,
    0x90, 0x28, 0x28, 0x00, 0x00, 0x01,
    0x80, 0x14, 0x00, 0x00, 0x00, 0x01,
    0x50, 0x12, 0x12, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const unsigned char EPD_2IN13D_lut_bb[] = {
    0x80, 0x08, 0x00, 0x00, 0x00, 0x02,
    0x90, 0x28, 0x28, 0x00, 0x00, 0x01,
    0x80, 0x14, 0x00, 0x00, 0x00, 0x01,
    0x50, 0x12, 0x12, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

/**
 * partial screen update LUT
**/
#define Tx19 0x19 // original value is 25 (phase length)
//#define Tx19 0x20   // new value for test is 32 (phase length)
static const unsigned char EPD_2IN13D_lut_vcom1[] = {
    0x00, Tx19, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    ,0x00, 0x00,
};
static const unsigned char EPD_2IN13D_lut_ww1[] = {
    0x00, Tx19, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const unsigned char EPD_2IN13D_lut_bw1[] = {
    0x80, Tx19, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const unsigned char EPD_2IN13D_lut_wb1[] = {
    0x40, Tx19, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const unsigned char EPD_2IN13D_lut_bb1[] = {
    0x00, Tx19, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

bool _power_is_on, _using_partial_mode, _hibernating;

/******************************************************************************
function :	Software reset
parameter:
******************************************************************************/
static void EPD_2IN13D_Reset(void)
{
    EPD_Digital_Write(EPD_RST_PIN, 1);
    EPD_Delay_ms(10);
    EPD_Digital_Write(EPD_RST_PIN, 0);
    EPD_Delay_ms(10);
    EPD_Digital_Write(EPD_RST_PIN, 1);
    EPD_Delay_ms(10);
}

/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
static void UC8151D_SendCommand(uint8_t Reg)
{
	EPD_Digital_Write(EPD_CS_PIN, 1);
	EPD_Digital_Write(EPD_DC_PIN, 0);
    EPD_Digital_Write(EPD_CS_PIN, 0);
    EPD_SPI_WriteByte(Reg);
    EPD_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void UC8151D_SendData(uint8_t Data)
{
    EPD_Digital_Write(EPD_DC_PIN, 1);
    EPD_Digital_Write(EPD_CS_PIN, 0);
    EPD_SPI_WriteByte(Data);
    EPD_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :	Wait until the busy_pin goes LOW
parameter:
******************************************************************************/
static void UC8151D_BusyWait(void)
{
    Debug("e-Paper busy check\r\n");
    uint8_t busy;
    do {
        UC8151D_SendCommand(0x71);
        busy = EPD_Digital_Read(EPD_BUSY_PIN);
        busy =!(busy & 0x01);
    } while(busy);
    EPD_Delay_ms(200);
    Debug("e-Paper busy release\r\n");
}

/******************************************************************************
function :	Full LUT download
parameter:
******************************************************************************/
static void UC8151D_SendFullLUT(void)
{
    unsigned int count;

    UC8151D_SendCommand(UC8151D_CDI);			//VCOM AND DATA INTERVAL SETTING
    UC8151D_SendData(0xB7);		//WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7

    UC8151D_SendCommand(0x20);
    for(count=0; count<44; count++) {
        UC8151D_SendData(EPD_2IN13D_lut_vcomDC[count]);
    }

    UC8151D_SendCommand(0x21);
    for(count=0; count<42; count++) {
        UC8151D_SendData(EPD_2IN13D_lut_ww[count]);
    }

    UC8151D_SendCommand(0x22);
    for(count=0; count<42; count++) {
        UC8151D_SendData(EPD_2IN13D_lut_bw[count]);
    }

    UC8151D_SendCommand(0x23);
    for(count=0; count<42; count++) {
        UC8151D_SendData(EPD_2IN13D_lut_wb[count]);
    }

    UC8151D_SendCommand(0x24);
    for(count=0; count<42; count++) {
        UC8151D_SendData(EPD_2IN13D_lut_bb[count]);
    }
}

/******************************************************************************
function :	Partial LUT download
parameter:
******************************************************************************/
static void UC8151D_SendPartialLUT(void)
{
    unsigned int count;
    UC8151D_SendCommand(0x20);
    for(count=0; count<44; count++) {
        UC8151D_SendData(EPD_2IN13D_lut_vcom1[count]);
    }

    UC8151D_SendCommand(0x21);
    for(count=0; count<42; count++) {
        UC8151D_SendData(EPD_2IN13D_lut_ww1[count]);
    }

    UC8151D_SendCommand(0x22);
    for(count=0; count<42; count++) {
        UC8151D_SendData(EPD_2IN13D_lut_bw1[count]);
    }

    UC8151D_SendCommand(0x23);
    for(count=0; count<42; count++) {
        UC8151D_SendData(EPD_2IN13D_lut_wb1[count]);
    }

    UC8151D_SendCommand(0x24);
    for(count=0; count<42; count++) {
        UC8151D_SendData(EPD_2IN13D_lut_bb1[count]);
    }
}

/******************************************************************************
function :	Turn On Display
parameter:
******************************************************************************/
static void UC8151D_DisplayRefresh(void)
{
    UC8151D_SendCommand(UC8151D_DRF);		 //DISPLAY REFRESH
    EPD_Delay_ms(5);     //!!!The delay here is necessary, 200uS at least!!!

    UC8151D_BusyWait();
}

/******************************************************************************
function :	Initialize the e-Paper register
parameter:
******************************************************************************/
void UC8151D_PowerOn()
{
  if (!_power_is_on)
  {
	UC8151D_SendCommand(UC8151D_PON);
    EPD_Delay_ms(10);
    UC8151D_BusyWait();
  }
  _power_is_on = true;
}
void UC8151D_Init_Full()
{
	//Reset 3 times
	//TODO: Implement if (_hibernating) _reset();
	for (uint8_t var = 0; var < 3; ++var) {
		EPD_2IN13D_Reset();
		EPD_Delay_ms(10);
	}
	UC8151D_Init();
	UC8151D_PowerOn();

}
void UC8151D_Init()
{
	EPD_Module_Init();
//
    UC8151D_SendCommand(UC8151D_PLL);	//PLL setting
    UC8151D_SendData(0x3C);     // 3a 100HZ   29 150Hz 39 200HZ	31 171HZ

    UC8151D_PowerOn();
    UC8151D_SendCommand(UC8151D_PSR);
    UC8151D_SendData(0xBF);

 	UC8151D_SendCommand(UC8151D_CDI);
 	UC8151D_SendData(0xB7);

    UC8151D_SendCommand(UC8151D_TRES);	//resolution setting
    UC8151D_SendData(EPD_2IN13D_WIDTH);
    UC8151D_SendData((EPD_2IN13D_HEIGHT >> 8) & 0xff);
    UC8151D_SendData(EPD_2IN13D_HEIGHT& 0xff);

    EPD_2IN13D_Clear();

    _using_partial_mode = false;
}

/******************************************************************************
function :	Initialize the e-Paper register in Partial mode
parameter:
******************************************************************************/
void UC8151D_InitPart()
{
	//UC8151D_Init();
	UC8151D_SendCommand(UC8151D_PSR); //panel setting
	UC8151D_SendData(hasFastPartialUpdate ? 0xbf : 0x1f); // for test with OTP LUT
	UC8151D_SendCommand(UC8151D_VDCS); //vcom_DC setting
	UC8151D_SendData (0x08);
	UC8151D_SendCommand(UC8151D_CDI);
	UC8151D_SendData(0x17);    //WBmode:VBDF 17|D7 VBDW 97 VBDB 57   WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7

	UC8151D_SendPartialLUT();
	//UC8151D_PowerOn();
	_using_partial_mode = true;
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void EPD_2IN13D_Clear(void)
{
    uint16_t Width, Height;
    Width = (EPD_2IN13D_WIDTH % 8 == 0)? (EPD_2IN13D_WIDTH / 8 ): (EPD_2IN13D_WIDTH / 8 + 1);
    Height = EPD_2IN13D_HEIGHT;

    UC8151D_SendCommand(UC8151D_DTM1);
    for (uint16_t j = 0; j < Height; j++) {
        for (uint16_t i = 0; i < Width; i++) {
            UC8151D_SendData(0x00);
        }
    }

    UC8151D_SendCommand(UC8151D_DTM2);
    for (uint16_t j = 0; j < Height; j++) {
        for (uint16_t i = 0; i < Width; i++) {
            UC8151D_SendData(0xFF);
        }
    }

    //EPD_2IN13D_SetFullReg();
    UC8151D_DisplayRefresh();
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void EPD_2IN13D_Display(uint8_t *Image)
{
    uint16_t Width, Height;
    Width = (EPD_2IN13D_WIDTH % 8 == 0)? (EPD_2IN13D_WIDTH / 8 ): (EPD_2IN13D_WIDTH / 8 + 1);
    Height = EPD_2IN13D_HEIGHT;

    if (_using_partial_mode) UC8151D_Init();

    for (uint16_t j = 0; j < Height; j++) {
        for (uint16_t i = 0; i < Width; i++) {
            UC8151D_SendData(0x00);
        }
    }

    UC8151D_SendCommand(UC8151D_DTM2);
    for (uint16_t j = 0; j < Height; j++) {
        for (uint16_t i = 0; i < Width; i++) {
            UC8151D_SendData(Image[i + j * Width]);
        }
    }

    UC8151D_SendFullLUT();
	//EPD_2IN13D_SetFullReg();
    UC8151D_DisplayRefresh();
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void UC8151D_DisplayPart(uint8_t *Image, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	if (!_using_partial_mode) UC8151D_InitPart();

	/* Set partial Windows */
    UC8151D_SendCommand(UC8151D_PTIN);		//This command makes the display enter partial mode
    UC8151D_setPartialRamArea(y, x, h, w);

    uint16_t bytes_per_column = (EPD_2IN13D_WIDTH % 8 == 0)? (EPD_2IN13D_WIDTH / 8 ): (EPD_2IN13D_WIDTH / 8 + 1);

    //Bytes to draw in direction X
    h += y % 8;
    h = (h % 8 == 0)? (h / 8 ): (h / 8 + 1);

    Image = Image + (bytes_per_column * x) + (y/8);

    /* send data */
    UC8151D_SendCommand(0x10);
	for (uint16_t j = 0; j < w; j++) {
		for (uint16_t i = 0; i < h; i++) {
			uint16_t address = i + (j * bytes_per_column);
			UC8151D_SendData(~Image[address]);
			//UC8151D_DisplayRefresh();
			//UC8151D_SendData(0x20);
		}
	}

	UC8151D_SendCommand(0x13);
	for (uint16_t j = 0; j < w; j++) {
		for (uint16_t i = 0; i < h; i++) {
			UC8151D_SendData(Image[i + (j * bytes_per_column)]);
			//UC8151D_SendData(~0x20);
		}
	}

    UC8151D_DisplayRefresh();
    UC8151D_SendCommand(0x92); // partial out
    EPD_Delay_ms(1); // yield() to avoid WDT on ESP8266 and ESP32

}

void UC8151D_setPartialRamArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //w = ((w + 7) / 8) * 8;
  uint16_t xe = ((x + w) -1 ) | 0x0007; // byte boundary inclusive (last byte)
  uint16_t ye = y + h - 1;
  x &= 0xFFF8; // byte boundary
  //x -= (x % 8);
  UC8151D_SendCommand(UC8151D_PTL); // partial window
  UC8151D_SendData(x % 256);
  UC8151D_SendData(xe % 256);
  UC8151D_SendData(y / 256);
  UC8151D_SendData(y % 256);
  UC8151D_SendData(ye / 256);
  UC8151D_SendData(ye % 256);
  UC8151D_SendData(0x01); // don't see any difference
  //UC8151D_SendData(0x00); // don't see any difference
}

/******************************************************************************
function :	Enter sleep mode
parameter:
******************************************************************************/
void EPD_2IN13D_Sleep(void)
{
    UC8151D_SendCommand(UC8151D_CDI);
    UC8151D_SendData(0xf7);

    UC8151D_SendCommand(UC8151D_POF);  	//power off
    UC8151D_BusyWait();

    UC8151D_SendCommand(UC8151D_DSLP);  	//deep sleep
    UC8151D_SendData(0xA5);
}
