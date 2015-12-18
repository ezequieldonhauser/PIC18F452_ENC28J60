#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H

#include "GenericTypeDefs.h"
#include "Compiler.h"

//algumas definiçoes usadas para TICK, UAT, e SPI
#define GetSystemClock()		(40000000ul) // Hz
#define GetInstructionClock()	(GetSystemClock()/4)
#define GetPeripheralClock()	GetInstructionClock()

//LEDs (saidas)
#define LED0_TRIS		(TRISDbits.TRISD7)
#define LED0_IO			(LATDbits.LATD7)
#define LED1_TRIS		(TRISDbits.TRISD6)
#define LED1_IO			(LATDbits.LATD6)

//BOTOES (entrada) 0 = precionado
//#define BUTTON0_TRIS	(TRISBbits.TRISB2) //key1
//#define	BUTTON0_IO		(PORTBbits.RB2)
//#define BUTTON1_TRIS	(TRISBbits.TRISB1) //key2
//#define	BUTTON1_IO		(PORTBbits.RB1)

//LCD (4bits)
//#define LCD_DATA_TRIS		(TRISE)
//#define LCD_DATA_IO		(LATE)
//#define LCD_RD_WR_TRIS	(TRISDbits.TRISD1)
//#define LCD_RD_WR_IO		(LATDbits.LATD1)
//#define LCD_RS_TRIS		(TRISDbits.TRISD0)
//#define LCD_RS_IO		(LATDbits.LATD0)
//#define LCD_E_TRIS		(TRISDbits.TRISD2)
//#define LCD_E_IO		(LATDbits.LATD2)

//ENC28J60 I/O pins
#define ENC_RST_TRIS	(TRISCbits.TRISC0)
#define ENC_RST_IO		(LATCbits.LATC0)
#define ENC_CS_TRIS		(TRISCbits.TRISC1)//descomente para usar o ENC28J60
#define ENC_CS_IO		(LATCbits.LATC1)
#define ENC_SCK_TRIS	(TRISCbits.TRISC3)
#define ENC_SDI_TRIS	(TRISCbits.TRISC4)
#define ENC_SDO_TRIS	(TRISCbits.TRISC5)
#define ENC_SPI_IF		(PIR1bits.SSPIF)
#define ENC_SSPBUF		(SSPBUF)
#define ENC_SPISTAT		(SSPSTAT)
#define ENC_SPISTATbits	(SSPSTATbits)
#define ENC_SPICON1		(SSPCON1)
#define ENC_SPICON1bits	(SSPCON1bits)
#define ENC_SPICON2		(SSPCON2)

//25LC1024 EEPROM
//#define EEPROM_CS_TRIS	(TRISDbits.TRISD7)
//#define EEPROM_CS_IO		(LATDbits.LATD7)
//#define EEPROM_SCK_TRIS	(TRISCbits.TRISC3)
//#define EEPROM_SDI_TRIS	(TRISCbits.TRISC4)
//#define EEPROM_SDO_TRIS	(TRISCbits.TRISC5)
//#define EEPROM_SPI_IF		(PIR1bits.SSP1IF)
//#define EEPROM_SSPBUF		(SSP1BUF)
//#define EEPROM_SPICON1	(SSP1CON1)
//#define EEPROM_SPICON1bits	(SSP1CON1bits)
//#define EEPROM_SPICON2	(SSP1CON2)
//#define EEPROM_SPISTAT	(SSP1STAT)
//#define EEPROM_SPISTATbits	(SSP1STATbits)

//RS232 (UAT)
#define BusyUART()		BusyUSART()
#define CloseUART()		CloseUSART()
#define ConfigIntUART(a)	ConfigIntUSART(a)
#define DataRdyUART()		DataRdyUSART()
#define OpenUART(a,b,c)		OpenUSART(a,b,c)
#define ReadUART()		ReadUSART()
#define WriteUART(a)		WriteUSART(a)
#define getsUART(a,b,c)		getsUSART(b,a)
#define putsUART(a)		putsUSART(a)
#define getcUART()		ReadUSART()
#define putcUART(a)		WriteUSART(a)
#define putrsUART(a)		putrsUSART((far rom char*)a)

#endif
