/*****************************************************************************
 *   i2c.h:  Header file for Philips LPC214x Family Microprocessors
 *
 *   Copyright(C) 2006, Philips Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2005.10.01  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/

#ifndef __I2C_H 
#define __I2C_H

#define BUFSIZE_I2C			0x20
#define MAX_TIMEOUT			0x00AFFF 

#define I2CMASTER			0x01
#define I2CSLAVE			0x02

/* For more info, read PCF8594C-2 datasheet */
#define PCF_ADDR			64 //0x28 //0xA0
#define PCF_WORD			0x00
#define RD_BIT				0x01

#define GET_DATA			0x01

#define I2C_IDLE			0
#define I2C_STARTED			1
#define I2C_RESTARTED		2
#define I2C_REPEATED_START	3
#define DATA_ACK			4
#define DATA_NACK			5

#define I2CONSET_I2EN		0x00000040  /* I2C Control Set Register */
#define I2CONSET_AA			0x00000004
#define I2CONSET_SI			0x00000008
#define I2CONSET_STO		0x00000010
#define I2CONSET_STA		0x00000020

#define I2CONCLR_AAC		0x00000004  /* I2C Control clear Register */
#define I2CONCLR_SIC		0x00000008
#define I2CONCLR_STAC		0x00000020
#define I2CONCLR_I2ENC		0x00000040

#define I2DAT_I2C			0x00000000  /* I2C Data Reg */
#define I2ADR_I2C			0x00000000  /* I2C Slave Address Reg */
#define I2SCLH_SCLH			0x0000012c  /* I2C SCL Duty Cycle High Reg */	//I2C buss is too fast for current config
#define I2SCLL_SCLL			0x0000012c  /* I2C SCL Duty Cycle Low Reg */	//Need to slow it down due to E2PROM //was 0x80
//#define I2SCLH_SCLH			1000  /* I2C SCL Duty Cycle High Reg */	//I2C buss is too fast for current config
//#define I2SCLL_SCLL			1000  /* I2C SCL Duty Cycle Low Reg */	//Need to slow it down due to E2PROM //was 0x80


#define I2CSLAVEADDR         0x55           // 7-bit slave address 
#define bq27500CMD_CNTL_LSB  0x00
#define bq27500CMD_CNTL_MSB  0x01
#define bq27500CMD_AR_LSB    0x02
#define bq27500CMD_AR_MSB    0x03
#define bq27500CMD_ARTTE_LSB 0x04
#define bq27500CMD_ARTTE_MSB 0x05
#define bq27500CMD_TEMP_LSB  0x06
#define bq27500CMD_TEMP_MSB  0x07
#define bq27500CMD_VOLT_LSB  0x08
#define bq27500CMD_VOLT_MSB  0x09
#define bq27500CMD_FLAGS_LSB 0x0A
#define bq27500CMD_FLAGS_MSB 0x0B
#define bq27500CMD_NAC_LSB   0x0C
#define bq27500CMD_NAC_MSB   0x0D
#define bq27500CMD_FAC_LSB   0x0E
#define bq27500CMD_FAC_MSB   0x0F
#define bq27500CMD_RM_LSB    0x10
#define bq27500CMD_RM_MSB    0x11
#define bq27500CMD_FCC_LSB   0x12
#define bq27500CMD_FCC_MSB   0x13
#define bq27500CMD_AI_LSB    0x14
#define bq27500CMD_AI_MSB    0x15
#define bq27500CMD_TTE_LSB   0x16
#define bq27500CMD_TTE_MSB   0x17
#define bq27500CMD_TTF_LSB   0x18
#define bq27500CMD_TTF_MSB   0x19
#define bq27500CMD_SI_LSB    0x1A
#define bq27500CMD_SI_MSB    0x1B
#define bq27500CMD_STTE_LSB  0x1C
#define bq27500CMD_STTE_MSB  0x1D
#define bq27500CMD_MLI_LSB   0x1E
#define bq27500CMD_MLI_MSB   0x1F
#define bq27500CMD_MLTTE_LSB 0x20
#define bq27500CMD_MLTTE_MSB 0x21
#define bq27500CMD_AE_LSB    0x22
#define bq27500CMD_AE_MSB    0x23
#define bq27500CMD_AP_LSB    0x24
#define bq27500CMD_AP_MSB    0x25
#define bq27500CMD_TTECP_LSB 0x26
#define bq27500CMD_TTECP_MSB 0x27
#define bq27500CMD_RSVD_LSB  0x28
#define bq27500CMD_RSVD_MSB  0x29
#define bq27500CMD_CC_LSB    0x2A
#define bq27500CMD_CC_MSB    0x2B
#define bq27500CMD_SOC_LSB   0x2C
#define bq27500CMD_SOC_MSB   0x2D
#define bq27500CMD_DCAP_LSB  0x3C
#define bq27500CMD_DCAP_MSB  0x3D
#define bq27500CMD_DFCLS     0x3E
#define bq27500CMD_DFBLK     0x3F
#define bq27500CMD_ADF       0x40
#define bq27500CMD_ACKSDFD   0x54
#define bq27500CMD_DFDCKS    0x60
#define bq27500CMD_DFDCNTL   0x61
#define bq27500CMD_DNAMELEN  0x62
#define bq27500CMD_DNAME     0x63
#define bq27500CMD_APPSTAT   0x6A

unsigned char   bq27500_read (unsigned char cmd, char Size);
int StartI2Master (void) ;
extern void I2C0MasterHandler( void ) __irq;
extern DWORD I2CInit( DWORD I2cMode );
extern DWORD I2CStart( void );
extern DWORD I2CStop( void );
extern DWORD I2CEngine( void );

#endif /* end __I2C_H */
/****************************************************************************
**                            End Of File
*****************************************************************************/
