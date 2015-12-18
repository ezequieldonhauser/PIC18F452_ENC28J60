#ifndef __TCPIPCONFIG_H
#define __TCPIPCONFIG_H

#include "GenericTypeDefs.h"
#include "Compiler.h"
#define GENERATED_BY_TCPIPCONFIG "Version 1.0.3398.23884"

// =============================================================================
//   Application Options
// =============================================================================
//#define STACK_USE_UART                        // Application demo using UART for IP address display and stack configuration
//#define STACK_USE_UART2TCP_BRIDGE		// UART to TCP Bridge application example
#define STACK_USE_ICMP_SERVER			// Ping query and response capability
#define STACK_USE_ICMP_CLIENT			// Ping transmission capability
//#define STACK_USE_HTTP_SERVER			// Old HTTP server
//#define STACK_USE_HTTP2_SERVER        // New HTTP server with POST, Cookies, Authentication, etc.
//#define STACK_USE_SSL_SERVER			// NAO USAR ------------------------
//#define STACK_USE_SSL_CLIENT			// NAO USAR ------------------------
//#define STACK_USE_DHCP_CLIENT			// Dynamic Host Configuration Protocol client for obtaining IP address and other parameters
//#define STACK_USE_DHCP_SERVER			// Single host DHCP server
//#define STACK_USE_FTP_SERVER			// File Transfer Protocol (old)
//#define STACK_USE_SMTP_CLIENT			// Simple Mail Transfer Protocol for sending email
//#define STACK_USE_TFTP_CLIENT			// Trivial File Transfer Protocol client
//#define STACK_USE_TCP_CLIENT                	// Exemplo de socket TCP ClientSocket.c
#define STACK_USE_TCP_SERVER                    // Exemplo de socket TCP ServerSocket.c
//#define STACK_USE_TELNET_SERVER                 // Telnet server
//#define STACK_USE_ANNOUNCE			// Microchip Embedded Ethernet Device Discoverer server/client
//#define STACK_USE_DNS				// Domain Name Service Client for resolving hostname strings to IP addresses
//#define STACK_USE_NBNS				// NetBIOS Name Service Server for repsonding to NBNS hostname broadcast queries
//#define STACK_USE_REBOOT_SERVER		  // Module for resetting this PIC remotely.  Primarily useful for a Bootloader.
//#define STACK_USE_SNTP_CLIENT			  // Simple Network Time Protocol for obtaining current date/time from Internet
//#define STACK_USE_DYNAMICDNS_CLIENT		  // Dynamic DNS client updater module
//#define STACK_USE_BERKELEY_API                  // Berekely Sockets APIs are available
//#define STACK_USE_SNMP_SERVER			// Simple Network Management Protocol v2C Community Agent

// =======================================================================
//   Data Storage Options
// =======================================================================
//defição do gerenciador de UPLOAD de paginas
//#define STACK_USE_MPFS
//#define STACK_USE_MPFS2

//onde a pagina web será salva (senao selecionar nenhum fica na eeprom interna)
//#define MPFS_USE_EEPROM
//#define MPFS_USE_SPI_FLASH
//#define USE_EEPROM_25LC1024

//area reservada na eeprom
#define MPFS_RESERVE_BLOCK              (256ul)

//maximas conexeçoes abertas
#define MAX_MPFS_HANDLES		(9ul)

// =============================================================================
//   endereços da rede (Network Adress) IP, MASK, GATEWAY, DNS
// =============================================================================
#define MY_DEFAULT_HOST_NAME		"PICTCPIP"

#define MY_DEFAULT_MAC_BYTE1            (0x00)	// Use the default of
#define MY_DEFAULT_MAC_BYTE2            (0x04)	// 00-04-A3-00-00-00 if using
#define MY_DEFAULT_MAC_BYTE3            (0xA3)	// an ENCX24J600 or ZeroG ZG2100 
#define MY_DEFAULT_MAC_BYTE4            (0x00)	// and wish to use the internal 
#define MY_DEFAULT_MAC_BYTE5            (0x00)	// factory programmed MAC 
#define MY_DEFAULT_MAC_BYTE6            (0x00)	// address instead.

#define MY_DEFAULT_IP_ADDR_BYTE1        (192ul)
#define MY_DEFAULT_IP_ADDR_BYTE2        (168ul)
#define MY_DEFAULT_IP_ADDR_BYTE3        (0ul)
#define MY_DEFAULT_IP_ADDR_BYTE4        (240ul)

#define MY_DEFAULT_MASK_BYTE1           (255ul)
#define MY_DEFAULT_MASK_BYTE2           (255ul)
#define MY_DEFAULT_MASK_BYTE3           (255ul)
#define MY_DEFAULT_MASK_BYTE4           (0ul)

#define MY_DEFAULT_GATE_BYTE1           (192ul)
#define MY_DEFAULT_GATE_BYTE2           (168ul)
#define MY_DEFAULT_GATE_BYTE3           (0ul)
#define MY_DEFAULT_GATE_BYTE4           (254ul)

#define MY_DEFAULT_PRIMARY_DNS_BYTE1	(192ul)
#define MY_DEFAULT_PRIMARY_DNS_BYTE2	(168ul)
#define MY_DEFAULT_PRIMARY_DNS_BYTE3	(0ul)
#define MY_DEFAULT_PRIMARY_DNS_BYTE4	(254ul)

#define MY_DEFAULT_SECONDARY_DNS_BYTE1	(8ul)
#define MY_DEFAULT_SECONDARY_DNS_BYTE2	(8ul)
#define MY_DEFAULT_SECONDARY_DNS_BYTE3	(8ul)
#define MY_DEFAULT_SECONDARY_DNS_BYTE4	(8ul)

// =============================================================================
//   Cliente e Servidor Socket (GENERIC_TCP_CLIENT) e (GENERIC_TCP_SERVER)
// =============================================================================
//NOME ou IP do servidor onde o pic se conectará
//static BYTE ServerName[] = "192.168.25.239";

//PORTA do servidor onde o pic se conectará
static WORD ServerPort = 2000;

//PORTA do pic onde um cliente se conectará
#define SERVER_PORT     3000

// =============================================================================
//   Transport Layer Options
// =============================================================================

//configuração do modo de transporte dos dados (layer)
#define STACK_USE_TCP
//#define STACK_USE_UDP

//definção do tipo de operação (cliente ou servidor)
//comente essa linha para modo servidor
//#define STACK_CLIENT_MODE

//definiçoes de alocação de memoria RAM para cada Socket
// for use by your TCP TCBs, RX FIFOs, and TX FIFOs.
#define TCP_ETH_RAM_SIZE			(2253ul)
#define TCP_PIC_RAM_SIZE			(0ul)
#define TCP_SPI_RAM_SIZE			(0ul)
#define TCP_SPI_RAM_BASE_ADDRESS		(0x00)

//definição de nomes para os tipos de Socket
#define TCP_SOCKET_TYPES
    #define TCP_PURPOSE_GENERIC_TCP_CLIENT          0
    #define TCP_PURPOSE_GENERIC_TCP_SERVER          1
    #define TCP_PURPOSE_TELNET                      2
    #define TCP_PURPOSE_FTP_COMMAND                 3
    #define TCP_PURPOSE_FTP_DATA                    4
    #define TCP_PURPOSE_TCP_PERFORMANCE_TX          5
    #define TCP_PURPOSE_TCP_PERFORMANCE_RX          6
    #define TCP_PURPOSE_UART_2_TCP_BRIDGE           7
    #define TCP_PURPOSE_HTTP_SERVER                 8
    #define TCP_PURPOSE_DEFAULT                     9
    #define TCP_PURPOSE_BERKELEY_SERVER             10
    #define TCP_PURPOSE_BERKELEY_CLIENT             11
#define END_OF_TCP_SOCKET_TYPES

// =============================================================================
//   Configuraçoes de transporte TCP
// =============================================================================
#if defined(__TCP_C)
    // Define what types of sockets are needed, how many of
    // each to include, where their TCB, TX FIFO, and RX FIFO
    // should be stored, and how big the RX and TX FIFOs should
    // be.  Making this initializer bigger or smaller defines
    // how many total TCP sockets are available.
    //
    // Each socket requires up to 48 bytes of PIC RAM and
    // 40+(TX FIFO size)+(RX FIFO size) bytes bytes of
    // TCP_*_RAM each.
    // Note: The RX FIFO must be at least 1 byte in order to
    // receive SYN and FIN messages required by TCP.  The TX
    // FIFO can be zero if desired.
    #define TCP_CONFIGURATION
        ROM struct
        {
            BYTE vSocketPurpose;
            BYTE vMemoryMedium;
            WORD wTXBufferSize;
            WORD wRXBufferSize;
        } TCPSocketInitializer[] =
        {   //inicialização das variaveis dos tipos de sockets
            //{TCP_PURPOSE_GENERIC_TCP_CLIENT, TCP_ETH_RAM, 30, 30},
            {TCP_PURPOSE_GENERIC_TCP_SERVER, TCP_ETH_RAM, 150, 150},
            {TCP_PURPOSE_GENERIC_TCP_SERVER, TCP_ETH_RAM, 150, 150},
            {TCP_PURPOSE_GENERIC_TCP_SERVER, TCP_ETH_RAM, 150, 150},
            {TCP_PURPOSE_GENERIC_TCP_SERVER, TCP_ETH_RAM, 150, 150},
            //{TCP_PURPOSE_TELNET, TCP_ETH_RAM, 150, 20},
            //{TCP_PURPOSE_FTP_COMMAND, TCP_ETH_RAM, 100, 40},
            //{TCP_PURPOSE_FTP_DATA, TCP_ETH_RAM, 0, 128},
            //{TCP_PURPOSE_TCP_PERFORMANCE_TX, TCP_ETH_RAM, 256, 1},
            //{TCP_PURPOSE_TCP_PERFORMANCE_RX, TCP_ETH_RAM, 40, 1500},
            //{TCP_PURPOSE_UART_2_TCP_BRIDGE, TCP_ETH_RAM, 256, 256},
            //{TCP_PURPOSE_HTTP_SERVER, TCP_ETH_RAM, 100, 100},
            //{TCP_PURPOSE_HTTP_SERVER, TCP_ETH_RAM, 200, 200},
            {TCP_PURPOSE_DEFAULT, TCP_ETH_RAM, 200, 200},
            //{TCP_PURPOSE_BERKELEY_SERVER, TCP_ETH_RAM, 25, 20},
            //{TCP_PURPOSE_BERKELEY_CLIENT, TCP_ETH_RAM, 125, 100},
        };
    #define END_OF_TCP_CONFIGURATION
#endif

// =======================================================================
//   Configuraçoes de transporte UDP
// =======================================================================
#define MAX_UDP_SOCKETS                 (9u)
#define UDP_USE_TX_CHECKSUM

/* Berkeley API Sockets Configuration
 *   Note that each Berkeley socket internally uses one TCP or UDP socket
 *   defined by MAX_UDP_SOCKETS and the TCPSocketInitializer[] array.
 *   Therefore, this number MUST be less than or equal to MAX_UDP_SOCKETS + the
 *   number of TCP sockets defined by the TCPSocketInitializer[] array
 *   (i.e. sizeof(TCPSocketInitializer)/sizeof(TCPSocketInitializer[0])).
 *   This define has no effect if STACK_USE_BERKELEY_API is not defined and
 *   Berkeley Sockets are disabled.  Set this value as low as your application
 *   requires to avoid waisting RAM.
 */
#define BSD_SOCKET_COUNT                (5u)

// =======================================================================
//  Opçoes de configuraçoes para as Aplicaçoes (HTTP, TELNET, FTP, ETC)
// =======================================================================

    // -- HTTP2 Server options -----------------------------------------------

    // Maximum numbers of simultaneous HTTP connections allowed.
    // Each connection consumes 2 bytes of RAM and a TCP socket
    #define MAX_HTTP_CONNECTIONS	(4u)

    //Aqui define qal o arquivo web que ira ser chamdo primeiro
    #define HTTP_DEFAULT_FILE		"index.htm"
    #define HTTPS_DEFAULT_FILE		"index.htm"
    #define HTTP_DEFAULT_LEN		(10u)//tamanho dessa strig
                                                                                       
    // Configure MPFS over HTTP updating
    // Comment this line to disable updating via HTTP
    #define HTTP_MPFS_UPLOAD		"upload"
    #define HTTP_MPFS_UPLOAD_REQUIRES_AUTH	// Require password for MPFS uploads
        // Certain firewall and router combinations cause the MPFS2 Utility to fail
        // when uploading.  If this happens, comment out this definition.

    // Define which HTTP modules to use
    // If not using a specific module, comment it to save resources
    #define HTTP_USE_POST					// Enable POST support
    //#define HTTP_USE_COOKIES				// Enable cookie support
    //#define HTTP_USE_AUTHENTICATION			// Enable basic authentication support

    //#define HTTP_NO_AUTH_WITHOUT_SSL		// Uncomment to require SSL before requesting a password
    #define HTTP_SSL_ONLY_CHAR		0xFF	// Files beginning with this character will only be served over HTTPS
                                                                                // Set to 0x00 to require for all files
                                                                                // Set to 0xff to require for no files

    //#define STACK_USE_HTTP_APP_RECONFIG		// Use the AppConfig web page in the Demo App (~2.5kb ROM, ~0b RAM)
    //#define STACK_USE_HTTP_MD5_DEMO			// Use the MD5 Demo web page (~5kb ROM, ~160b RAM)
    //#define STACK_USE_HTTP_EMAIL_DEMO		// Use the e-mail demo web page

    // -- SSL Options --------------------------------------------------------

    #define MAX_SSL_CONNECTIONS		(2ul)	// Maximum connections via SSL
    #define MAX_SSL_SESSIONS		(2ul)	// Max # of cached SSL sessions
    #define MAX_SSL_BUFFERS		(4ul)	// Max # of SSL buffers (2 per socket)
    #define MAX_SSL_HASHES		(5ul)	// Max # of SSL hashes  (2 per, plus 1 to avoid deadlock)

    // Bits in SSL RSA key.  This parameter is used for SSL sever
    // connections only.  The only valid value is 512 bits (768 and 1024
    // bits do not work at this time).  Note, however, that SSL client
    // operations do currently work up to 1024 bit RSA key length.
    #define SSL_RSA_KEY_SIZE		(512ul)


    // -- Telnet Options -----------------------------------------------------

    // Number of simultaneously allowed Telnet sessions.  Note that you
    // must have an equal number of TCP_PURPOSE_TELNET type TCP sockets
    // declared in the TCPSocketInitializer[] array above for multiple
    // connections to work.  If fewer sockets are available than this
    // definition, then the the lesser of the two quantities will be the
    // actual limit.
    #define MAX_TELNET_CONNECTIONS	(1u)

    // Default local listening port for the Telnet server.  Port 23 is the
    // protocol default.
    #define TELNET_PORT			(23u)

    // Default username and password required to login to the Telnet server.
    #define TELNET_USERNAME			"admin"
    #define TELNET_PASSWORD			"Pa$$w0rd"


    // -- SNMP Options -------------------------------------------------------

    // Comment following line if SNMP TRAP support is needed
    //#define SNMP_TRAP_DISABLED

    // Comment following line if SNMP TRAP DEMO not required
    #define SNMP_TRAP_DEMO_ENABLED

    // This is the maximum length for community string.
    // Application must ensure that this length is observed.
    // SNMP module adds one byte extra after SNMP_COMMUNITY_MAX_LEN
    // for adding '\0' NULL character.
    #define SNMP_COMMUNITY_MAX_LEN  	(8u)
    #define SNMP_MAX_COMMUNITY_SUPPORT	(3u)
    #define NOTIFY_COMMUNITY_LEN		(SNMP_COMMUNITY_MAX_LEN)

    // Default SNMPv2C community names.  These can be overridden at run time if
    // alternate strings are present in external EEPROM or Flash (actual
    // strings are stored in AppConfig.readCommunity[] and
    // AppConfig.writeCommunity[] arrays).  These strings are case sensitive.
    // An empty string means disabled (not matchable).
    // For application security, these default community names should not be
    // used, but should all be disabled to force the end user to select unique
    // community names.  These defaults are provided only to make it easier to
    // start development.  Specifying more strings than
    // SNMP_MAX_COMMUNITY_SUPPORT will result in the later strings being
    // ignored (but still wasting program memory).  Specifying fewer strings is
    // legal, as long as at least one is present.  A string larger than
    // SNMP_COMMUNITY_MAX_LEN bytes will be ignored.
    #define SNMP_READ_COMMUNITIES        {"public", "read", ""}
    #define END_OF_SNMP_READ_COMMUNITIES
    #define SNMP_WRITE_COMMUNITIES        {"private", "write", "public"}
    #define END_OF_SNMP_WRITE_COMMUNITIES

#endif

