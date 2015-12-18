#include <p18F452.h>

// CONFIG1H
#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator with PLL enabled/Clock frequency = (4 x FOSC))
#pragma config OSCS = OFF       // Oscillator System Clock Switch Enable bit (Oscillator system clock switch option is disabled (main oscillator is source))

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = ON         // Brown-out Reset Enable bit (Brown-out Reset enabled)
#pragma config BORV = 20        // Brown-out Reset Voltage bits (VBOR set to 2.0V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 128      // Watchdog Timer Postscale Select bits (1:128)

// CONFIG3H
#pragma config CCP2MUX = ON     // CCP2 Mux bit (CCP2 input/output is multiplexed with RC1)

// CONFIG4L
#pragma config STVR = ON        // Stack Full/Underflow Reset Enable bit (Stack Full/Underflow will cause RESET)
#pragma config LVP = OFF        // Low Voltage ICSP Enable bit (Low Voltage ICSP disabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-001FFFh) not code protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-001FFFh) not write protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-001FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from Table Reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from Table Reads executed in other blocks)

#include <stdlib.h>
//#include <p18f66j60.h>
#include "TCPIP Stack/TCPIP.h"
#include "MainDemo.h"
#include "LCDBlocking.h"
#include "TCPIPConfig.h"
#include "ClientSocket.h"
#include "ServerSocket.h"

//------------------------------interrupção-------------------------------------
#pragma interruptlow LowISR
void LowISR(void)
{
    TickUpdate();
}
#pragma interruptlow HighISR
void HighISR(void)
{
    #if defined(STACK_USE_UART2TCP_BRIDGE)
                UART2TCPBridgeISR();
    #endif
}
#pragma code lowVector=0x18
void LowVector(void){_asm goto LowISR _endasm}
#pragma code highVector=0x8
void HighVector(void){_asm goto HighISR _endasm}
#pragma code // Return to default code section
//------------------------------------------------------------------------------

//static void ProcessIO(void);
unsigned char AN0String[10];

//função principal
void main(void)
{
    static TICK t = 0;

    //inicializa todas as configuraçoes de hardware
    InitializeBoard();

    #if defined(USE_LCD)
    //inicializa configs do LCD se acaso estiver habilitado
    LCDInit();
    DelayMs(100);
    strcpypgm2ram((char*)LCDText, "APP TCPIP");
    LCDUpdate();
    #endif

    //inicializa um tick de tempo usado para TICK,SPI,UAT
    TickInit();

    //inicializa MPSF para upload de paginas web se acaso estiver habilitado
    #if defined(STACK_USE_MPFS) || defined(STACK_USE_MPFS2)
    MPFSInit();
    #endif

    //inicializa variaveis da aplicação AppConfig (IP, MASCARA, GATWAY, ETC)
    InitAppConfig();

    //inicializa a layer da pilha TCPIP (MAC, ARP, TCP, UDP)
    //e tambem as aplicaçoes habilitadas (HTTP, SNMP, SOCKET, ETC)
    StackInit();

    //inicializa UART 2 TCP Bridge
    #if defined(STACK_USE_UART2TCP_BRIDGE)
    UART2TCPBridgeInit();
    #endif

    //laço principal (nunca use delays, apenas maquinas de estado)
    //todos os processos devem estar executando paralelamente
    while(1)
    {
        //pisca o led para informar a pilha rodando
        if(TickGet() - t >= TICK_SECOND/2ul)
        {
            t = TickGet();
            LED0_IO ^= 1;
        }

        //processa coisas relacionadas ao hardware, leitura de pinos,etc.
        //ProcessIO();

        //chama tarefas da pilha TCPIP
        StackTask();

        //chama tarefas das aplicaçoes habilitadas
        StackApplications();

        //exemplo de aplicação Cliente Socket
        #if defined(STACK_USE_TCP_CLIENT)
        ClientSocketTCP();
        #endif

        //exemplo de aplicação Servidor Socket
        #if defined(STACK_USE_TCP_SERVER)
        ServerSocketTCP();
        #endif

        #if defined(STACK_USE_SNMP_SERVER) && !defined(SNMP_TRAP_DISABLED)
        //User should use one of the following SNMP demo
        // This routine demonstrates V1 or V2 trap formats with one variable binding.
        SNMPTrapDemo();

        #if defined(SNMP_STACK_USE_V2_TRAP) || defined(SNMP_V1_V2_TRAP_WITH_SNMPV3)
        //This routine provides V2 format notifications with multiple (3) variable bindings
        //User should modify this routine to send v2 trap format notifications with the required varbinds.
        //SNMPV2TrapDemo();
        #endif
        if(gSendTrapFlag)
            SNMPSendTrap();
        #endif

    }
}

// Processes A/D data from the potentiometer
//static void ProcessIO(void)
//{
//    BYTE temp;
//    // AN0 should already be set up as an analog input
//    ADCON0bits.GO = 1;
//
//    // Wait until A/D conversion is done
//    while(ADCON0bits.GO);
//
//    temp = ADCON2;
//    ADCON2 |= 0x7;    // Select Frc mode by setting ADCS0/ADCS1/ADCS2
//    ADCON2 = temp;
//
//    // Convert 10-bit value into ASCII string
//    uitoa(*((WORD*)(&ADRESL)), AN0String);
//}

//inicializa todas as configuraçoes de hardware
static void InitializeBoard(void)
{	
    DelayMs(100);
    
    // LEDs
    LED0_IO   = 1;
    LED1_IO   = 1;
    LED0_TRIS = 0;
    LED1_TRIS = 0;
    
    //botoes
    //BUTTON0_TRIS = 1;
    //BUTTON1_TRIS = 1;

    // Enable 4x/5x/96MHz PLL on PIC18F87J10, PIC18F97J60, PIC18F87J50, etc.
    //OSCTUNE = 0x40;

    // Set up analog features of PORTA
//    ADCON0 = 0b00001001;	//ADON, Channel 2 (AN2)
//    ADCON1 = 0b00001100;	//VSS0 VDD0, AN0,AN1,AN2 is analog
//    ADCON2 = 0xBE;		//Right justify, 20TAD ACQ time, Fosc/64 (~21.0kHz)

    // Disable internal PORTB pull-ups
    INTCON2bits.RBPU = 1;

    // Configure USART
    //TXSTA = 0x20;
    //RCSTA = 0x90;

    // See if we can use the high baud rate setting
//    #if ((GetPeripheralClock()+2*BAUD_RATE)/BAUD_RATE/4 - 1) <= 255
//    SPBRG = (GetPeripheralClock()+2*BAUD_RATE)/BAUD_RATE/4 - 1;
//    TXSTAbits.BRGH = 1;
//    #else	// Use the low baud rate setting
//    //SPBRG = (GetPeripheralClock()+8*BAUD_RATE)/BAUD_RATE/16 - 1;
//    #endif

    //PIE1bits.RCIE = 1;
    // Enable Interrupts
    RCONbits.IPEN = 1;		// Enable interrupt priorities
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;

    // Do a calibration A/D conversion
//    ADCON0bits.ADCAL = 1;
//    ADCON0bits.GO = 1;
//    while(ADCON0bits.GO);
//    ADCON0bits.ADCAL = 0;

    #if defined(SPIRAM_CS_TRIS)
            SPIRAMInit();
    #endif
    #if defined(EEPROM_CS_TRIS)
            XEEInit();
    #endif
    #if defined(SPIFLASH_CS_TRIS)
            SPIFlashInit();
    #endif
}

//inicialização geral das variaveis da aplicação
static ROM BYTE SerializedMACAddress[6]=
{ MY_DEFAULT_MAC_BYTE1, MY_DEFAULT_MAC_BYTE2, MY_DEFAULT_MAC_BYTE3,
  MY_DEFAULT_MAC_BYTE4, MY_DEFAULT_MAC_BYTE5, MY_DEFAULT_MAC_BYTE6};
static void InitAppConfig(void)
{
    AppConfig.Flags.bIsDHCPEnabled = TRUE;
    AppConfig.Flags.bInConfigMode = TRUE;
    memcpypgm2ram((void*)&AppConfig.MyMACAddr, (ROM void*)SerializedMACAddress, sizeof(AppConfig.MyMACAddr));
    memcpypgm2ram(AppConfig.NetBIOSName, (ROM void*)MY_DEFAULT_HOST_NAME, 16);
    FormatNetBIOSName(AppConfig.NetBIOSName);
    AppConfig.MyIPAddr.Val = MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2<<8ul | MY_DEFAULT_IP_ADDR_BYTE3<<16ul | MY_DEFAULT_IP_ADDR_BYTE4<<24ul;
    AppConfig.DefaultIPAddr.Val = AppConfig.MyIPAddr.Val;
    AppConfig.MyMask.Val = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2<<8ul | MY_DEFAULT_MASK_BYTE3<<16ul | MY_DEFAULT_MASK_BYTE4<<24ul;
    AppConfig.DefaultMask.Val = AppConfig.MyMask.Val;
    AppConfig.MyGateway.Val = MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2<<8ul | MY_DEFAULT_GATE_BYTE3<<16ul | MY_DEFAULT_GATE_BYTE4<<24ul;
    AppConfig.PrimaryDNSServer.Val = MY_DEFAULT_PRIMARY_DNS_BYTE1 | MY_DEFAULT_PRIMARY_DNS_BYTE2<<8ul  | MY_DEFAULT_PRIMARY_DNS_BYTE3<<16ul  | MY_DEFAULT_PRIMARY_DNS_BYTE4<<24ul;
    AppConfig.SecondaryDNSServer.Val = MY_DEFAULT_SECONDARY_DNS_BYTE1 | MY_DEFAULT_SECONDARY_DNS_BYTE2<<8ul  | MY_DEFAULT_SECONDARY_DNS_BYTE3<<16ul  | MY_DEFAULT_SECONDARY_DNS_BYTE4<<24ul;

    #if defined(EEPROM_CS_TRIS)
    {
        BYTE c;

        // When a record is saved, first byte is written as 0x60 to indicate
        // that a valid record was saved.  Note that older stack versions
        // used 0x57.  This change has been made to so old EEPROM contents
        // will get overwritten.  The AppConfig() structure has been changed,
        // resulting in parameter misalignment if still using old EEPROM
        // contents.
        XEEReadArray(0x0000, &c, 1);
        if(c == 0x42u)
        {
            XEEReadArray(0x0001, (BYTE*)&AppConfig, sizeof(AppConfig));
        }
    else
        SaveAppConfig();
    }
    #elif defined(SPIFLASH_CS_TRIS)
    {
        BYTE c;

        SPIFlashReadArray(0x0000, &c, 1);
        if(c == 0x42u)
        {
            SPIFlashReadArray(0x0001, (BYTE*)&AppConfig, sizeof(AppConfig));
        }
        else
            SaveAppConfig();
    }
    #endif
}


