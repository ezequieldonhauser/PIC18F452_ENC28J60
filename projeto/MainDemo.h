#ifndef _MAINDEMO_H
#define _MAINDEMO_H

#define BAUD_RATE       (9600)	// bps
//#define USE_LCD

#include "TCPIP Stack/HTTP2.h"

#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
	void SaveAppConfig(void);
#else
	#define SaveAppConfig()
#endif

typedef union
{
    struct
    {
        struct
        {
            unsigned char id[4];
        }id;
        struct
        {
            unsigned char user[15];
        }user;
        struct
        {
            unsigned char senha[4];
        }senha;
    }members;
    unsigned char all[24];
}OPERADOR_STRUCT;

//OPERADOR_STRUCT operador;

//estrutura de variaveis usadas na aplicação
APP_CONFIG  AppConfig;
BYTE        myDHCPBindCount = 0xFF;

//-----------------------------------------------------------------------------

static void InitAppConfig(void);
static void InitializeBoard(void);

#endif // _MAINDEMO_H
