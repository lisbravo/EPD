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
static const unsigned char EPD_2IN13D_lut_vcom1[] = {
    0x00, 0x19, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    ,0x00, 0x00,
};
static const unsigned char EPD_2IN13D_lut_ww1[] = {
    0x00, 0x19, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const unsigned char EPD_2IN13D_lut_bw1[] = {
    0x80, 0x19, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const unsigned char EPD_2IN13D_lut_wb1[] = {
    0x40, 0x19, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const unsigned char EPD_2IN13D_lut_bb1[] = {
    0x00, 0x19, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


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
static void EPD_2IN13D_SendCommand(UBYTE Reg)
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
static void EPD_2IN13D_SendData(UBYTE Data)
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
    UBYTE busy;
    do {
        EPD_2IN13D_SendCommand(0x71);
        busy = EPD_Digital_Read(EPD_BUSY_PIN);
        busy =!(busy & 0x01);
    } while(busy);
    EPD_Delay_ms(200);
    Debug("e-Paper busy release\r\n");
}

/******************************************************************************
function :	LUT download
parameter:
******************************************************************************/
static void EPD_2IN13D_SetFullReg(void)
{
    EPD_2IN13D_SendCommand(0X50);			//VCOM AND DATA INTERVAL SETTING
    EPD_2IN13D_SendData(0xB7);		//WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7

//    unsigned int count;
//    EPD_2IN13D_SendCommand(0x20);
//    for(count=0; count<44; count++) {
//        EPD_2IN13D_SendData(EPD_2IN13D_lut_vcomDC[count]);
//    }
//
//    EPD_2IN13D_SendCommand(0x21);
//    for(count=0; count<42; count++) {
//        EPD_2IN13D_SendData(EPD_2IN13D_lut_ww[count]);
//    }
//
//    EPD_2IN13D_SendCommand(0x22);
//    for(count=0; count<42; count++) {
//        EPD_2IN13D_SendData(EPD_2IN13D_lut_bw[count]);
//    }
//
//    EPD_2IN13D_SendCommand(0x23);
//    for(count=0; count<42; count++) {
//        EPD_2IN13D_SendData(EPD_2IN13D_lut_wb[count]);
//    }
//
//    EPD_2IN13D_SendCommand(0x24);
//    for(count=0; count<42; count++) {
//        EPD_2IN13D_SendData(EPD_2IN13D_lut_bb[count]);
//    }
}

/******************************************************************************
function :	LUT download
parameter:
******************************************************************************/
static void EPD_2IN13D_SetPartReg(void)
{
    EPD_2IN13D_SendCommand(0x82);			//vcom_DC setting
    EPD_2IN13D_SendData(0x00);
    EPD_2IN13D_SendCommand(0X50);
    EPD_2IN13D_SendData(0xb7);
	
    unsigned int count;
    EPD_2IN13D_SendCommand(0x20);
    for(count=0; count<44; count++) {
        EPD_2IN13D_SendData(EPD_2IN13D_lut_vcom1[count]);
    }

    EPD_2IN13D_SendCommand(0x21);
    for(count=0; count<42; count++) {
        EPD_2IN13D_SendData(EPD_2IN13D_lut_ww1[count]);
    }

    EPD_2IN13D_SendCommand(0x22);
    for(count=0; count<42; count++) {
        EPD_2IN13D_SendData(EPD_2IN13D_lut_bw1[count]);
    }

    EPD_2IN13D_SendCommand(0x23);
    for(count=0; count<42; count++) {
        EPD_2IN13D_SendData(EPD_2IN13D_lut_wb1[count]);
    }

    EPD_2IN13D_SendCommand(0x24);
    for(count=0; count<42; count++) {
        EPD_2IN13D_SendData(EPD_2IN13D_lut_bb1[count]);
    }
}

/******************************************************************************
function :	Turn On Display
parameter:
******************************************************************************/
static void UC8151D_DisplayRefresh(void)
{
    EPD_2IN13D_SendCommand(UC8151D_DRF);		 //DISPLAY REFRESH
    EPD_Delay_ms(5);     //!!!The delay here is necessary, 200uS at least!!!

    UC8151D_BusyWait();
}

/******************************************************************************
function :	Initialize the e-Paper register
parameter:
******************************************************************************/
void UC8151D_Init()
{
	EPD_Module_Init();

	//Reset 3 times
	for (uint8_t var = 0; var < 3; ++var) {
		EPD_2IN13D_Reset();
		EPD_Delay_ms(10);
	}

//    EPD_2IN13D_SendCommand(0x01);	//POWER SETTING
//    EPD_2IN13D_SendData(0x03);
//    EPD_2IN13D_SendData(0x00);
//    EPD_2IN13D_SendData(0x2b);
//    EPD_2IN13D_SendData(0x2b);
//    EPD_2IN13D_SendData(0x03);
//
//    EPD_2IN13D_SendCommand(0x06);	//boost soft start
//    EPD_2IN13D_SendData(0x17);     //A
//    EPD_2IN13D_SendData(0x17);     //B
//    EPD_2IN13D_SendData(0x17);     //C
//
//    EPD_2IN13D_SendCommand(0x04);
//    EPD_2IN13D_ReadBusy();
//
//    EPD_2IN13D_SendCommand(0x00);	//panel setting
//    EPD_2IN13D_SendData(0xbf);     //LUT from OTP，128x296
//    EPD_2IN13D_SendData(0x0e);     //VCOM to 0V fast
//
    EPD_2IN13D_SendCommand(UC8151D_PLL);	//PLL setting
    EPD_2IN13D_SendData(0x3C);     // 3a 100HZ   29 150Hz 39 200HZ	31 171HZ

    EPD_2IN13D_SendCommand(UC8151D_PON);
    EPD_Delay_ms(10);
    UC8151D_BusyWait();
    EPD_2IN13D_SendCommand(UC8151D_PSR);
    EPD_2IN13D_SendData(0x1F);
 	EPD_2IN13D_SendCommand(UC8151D_CDI);
 	EPD_2IN13D_SendData(0x97);

    EPD_2IN13D_SendCommand(UC8151D_TRES);	//resolution setting
    EPD_2IN13D_SendData(EPD_2IN13D_WIDTH);
    EPD_2IN13D_SendData((EPD_2IN13D_HEIGHT >> 8) & 0xff);
    EPD_2IN13D_SendData(EPD_2IN13D_HEIGHT& 0xff);

//    EPD_2IN13D_SendCommand(0x82);	//vcom_DC setting
//    EPD_2IN13D_SendData(0x28);
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void EPD_2IN13D_Clear(void)
{
    UWORD Width, Height;
    Width = (EPD_2IN13D_WIDTH % 8 == 0)? (EPD_2IN13D_WIDTH / 8 ): (EPD_2IN13D_WIDTH / 8 + 1);
    Height = EPD_2IN13D_HEIGHT;

    EPD_2IN13D_SendCommand(UC8151D_DTM1);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_2IN13D_SendData(0x00);
        }
    }

    EPD_2IN13D_SendCommand(UC8151D_DTM2);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_2IN13D_SendData(0xFF);
        }
    }

    //EPD_2IN13D_SetFullReg();
    UC8151D_DisplayRefresh();
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void EPD_2IN13D_Display(UBYTE *Image)
{
    UWORD Width, Height;
    Width = (EPD_2IN13D_WIDTH % 8 == 0)? (EPD_2IN13D_WIDTH / 8 ): (EPD_2IN13D_WIDTH / 8 + 1);
    Height = EPD_2IN13D_HEIGHT;

    EPD_2IN13D_SendCommand(0x10);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_2IN13D_SendData(0x00);
        }
    }
    // Dev_Delay_ms(10);

    EPD_2IN13D_SendCommand(0x13);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_2IN13D_SendData(Image[i + j * Width]);
        }
    }
    // Dev_Delay_ms(10);

	//EPD_2IN13D_SetFullReg();
    UC8151D_DisplayRefresh();
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void EPD_2IN13D_DisplayPart(UBYTE *Image)
{
	UC8151D_Init();
    /* Set partial Windows */
    EPD_2IN13D_SetPartReg();
    EPD_2IN13D_SendCommand(0x91);		//This command makes the display enter partial mode
    EPD_2IN13D_SendCommand(0x90);		//resolution setting
    EPD_2IN13D_SendData(0);           //x-start
    EPD_2IN13D_SendData(EPD_2IN13D_WIDTH - 1);       //x-end

    EPD_2IN13D_SendData(0);
    EPD_2IN13D_SendData(0);     //y-start
    EPD_2IN13D_SendData(EPD_2IN13D_HEIGHT / 256);
    EPD_2IN13D_SendData(EPD_2IN13D_HEIGHT % 256 - 1);  //y-end
    EPD_2IN13D_SendData(0x28);

    UWORD Width;
    Width = (EPD_2IN13D_WIDTH % 8 == 0)? (EPD_2IN13D_WIDTH / 8 ): (EPD_2IN13D_WIDTH / 8 + 1);
    
    /* send data */
    EPD_2IN13D_SendCommand(0x10);
    for (UWORD j = 0; j < EPD_2IN13D_HEIGHT; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_2IN13D_SendData(~Image[i + j * Width]);
        }
    }

    EPD_2IN13D_SendCommand(0x13);
    for (UWORD j = 0; j < EPD_2IN13D_HEIGHT; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_2IN13D_SendData(Image[i + j * Width]);
        }
    }

    /* Set partial refresh */    
    UC8151D_DisplayRefresh();
}


/******************************************************************************
function :	Enter sleep mode
parameter:
******************************************************************************/
void EPD_2IN13D_Sleep(void)
{
    EPD_2IN13D_SendCommand(UC8151D_CDI);
    EPD_2IN13D_SendData(0xf7);

    EPD_2IN13D_SendCommand(UC8151D_POF);  	//power off
    UC8151D_BusyWait();

    EPD_2IN13D_SendCommand(UC8151D_DSLP);  	//deep sleep
    EPD_2IN13D_SendData(0xA5);
}
