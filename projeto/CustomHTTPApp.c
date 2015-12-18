#define __CUSTOMHTTPAPP_C

#include "TCPIPConfig.h"

#if defined(STACK_USE_HTTP2_SERVER)

#include "TCPIP Stack/TCPIP.h"
#include "TCPIP Stack/MPFS2.h"
#include <adc.h>

extern HTTP_CONN curHTTP;
extern HTTP_STUB httpStubs[MAX_HTTP_CONNECTIONS];
extern BYTE curHTTPID;

/*****************************************************************************
  Function:
	BYTE HTTPNeedsAuth(BYTE* cFile)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)
BYTE HTTPNeedsAuth(BYTE* cFile)
{
	// If the filename begins with the folder "index", then require auth
    if(memcmppgm2ram(cFile, (ROM void*)"index.htm", 9) == 0)
            return 0x00;		// Authentication will be needed later
	
	return 0x80;
}
#endif

/*****************************************************************************
  Function:
	BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)
BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass)
{
    if(strcmppgm2ram((char *)cUser,(ROM char *)"admin") == 0
       && strcmppgm2ram((char *)cPass, (ROM char *)"admin") == 0)
	return 0x80;		// We accept this combination
    
    return 0x00;
}
#endif

/*********************************************************************
 * Function:        HTTP_IO_RESULT HTTPExecuteGet(void)
 *
 * PreCondition:    curHTTP is loaded
 *
 * Input:           None
 *
 * Output:          HTTP_IO_DONE on success
 *					HTTP_IO_WAITING if waiting for asynchronous process
 *
 * Side Effects:    None
 *
 * Overview:        This function is called if data was read from the
 *					HTTP request from either the GET arguments, or
 *					any cookies sent.  curHTTP.data contains
 *					sequential pairs of strings representing the
 *					data received.  Any required authentication has 
 *					already been validated.
 *
 * Note:            Custom implementation for WebVend Application
 ********************************************************************/
HTTP_IO_RESULT HTTPExecuteGet(void)
{
	// No GET functionality is defined

	return HTTP_IO_DONE;
}

#if defined(HTTP_USE_POST)

/*********************************************************************
 * Function:        HTTP_IO_RESULT HTTPExecutePost(void)
 *
 * PreCondition:    curHTTP is loaded
 *
 * Input:           None
 *
 * Output:          HTTP_IO_DONE on success
 *					HTTP_IO_NEED_DATA if more data is requested
 *					HTTP_IO_WAITING if waiting for asynchronous process
 *
 * Side Effects:    None
 *
 * Overview:        This function is called if the request method was
 *					POST.  It is called after HTTPExecuteGet and 
 *					after any required authentication has been validated.
 *
 * Note:            Custom implementation for WebVend Application
 ********************************************************************/
HTTP_IO_RESULT HTTPExecutePost(void)
{
	// No POST functionality is defined
	
	return HTTP_IO_DONE;
}

#endif //(use_post)

void HTTPPrint_btn(WORD num)
{
    // Determine which button
    switch(num)
    {
//        case 0:
//            num = BUTTON0_IO;
//            break;
//        case 1:
//            num = BUTTON1_IO;
//            break;
        default:
            num = 0;
    }

    // Print the output
    if(num)
        TCPPutROMString(sktHTTP, (ROM BYTE*)"up");
    else
        TCPPutROMString(sktHTTP, (ROM BYTE*)"down");

    return;
}


void HTTPPrint_pot(void)
{
    BYTE AN0String[8];
    WORD ADval;

    // Wait until A/D conversion is done
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);

    // Convert 10-bit value into ASCII string
    ADval = (WORD)ADRES;
    //ADval *= (WORD)10;
    //ADval /= (WORD)102;
    uitoa(ADval, AN0String);

    TCPPutString(sktHTTP, AN0String);
}

#endif
