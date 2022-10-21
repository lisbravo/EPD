/**
  ******************************************************************************
  * @file           : EPD_2in13.h
  * @brief          : Header for the 2.13 driver
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
#ifndef __EPD_2IN13D_H_
#define __EPD_2IN13D_H_

#include "EPD_Comms.h"

// Display resolution
#define EPD_2IN13D_WIDTH   104
#define EPD_2IN13D_HEIGHT  212

#define UC8151D_PSR 0x00
#define UC8151D_PWR 0x01
#define UC8151D_POF 0x02
#define UC8151D_PFS 0x03
#define UC8151D_PON 0x04
#define UC8151D_PMEAS 0x05
#define UC8151D_BTST 0x06
#define UC8151D_DSLP 0x07
#define UC8151D_DTM1 0x10
#define UC8151D_DSP 0x11
#define UC8151D_DRF 0x12
#define UC8151D_DTM2 0x13


#define UC8151D_AUTO 0x17
#define UC8151D_LUTOPT 0x2A
#define UC8151D_PLL 0x30
#define UC8151D_TSC 0x40
#define UC8151D_TSE 0x41
#define UC8151D_TSW 0x42
#define UC8151D_TSR 0x43
#define UC8151D_PBC 0x44
#define UC8151D_CDI 0x50
#define UC8151D_LPD 0x51
#define UC8151D_TRES 0x61
#define UC8151D_GSST 0x70
#define UC8151D_REV 0x70
#define UC8151D_FLG 0x71
#define UC8151D_AMV 0x80
#define UC8151D_VV 0x81
#define UC8151D_VDCS 0x82
#define UC8151D_PTL 0x90
#define UC8151D_PTIN 0x91
#define UC8151D_PTOUT 0x92
#define UC8151D_PGM 0xA0
#define UC8151D_APG 0xA1
#define UC8151D_ROTP 0xA2
#define UC8151D_CCSET 0xE0
#define UC8151D_PWS 0xE3
#define UC8151D_LVSEL 0xE4
#define UC8151D_TSSET 0xE5

void UC8151D_Init(void);
void EPD_2IN13D_Clear(void);
void EPD_2IN13D_Display(UBYTE *Image);
void EPD_2IN13D_DisplayPart(UBYTE *Image);
void EPD_2IN13D_Sleep(void);

#endif
