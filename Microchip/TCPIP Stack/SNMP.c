/*********************************************************************
 *
 *	Simple Network Management Protocol (SNMP) Version 1 Agent 
 *  Simple Network Management Protocol (SNMP) Version 2 community based Agent
 *  Module for Microchip TCP/IP Stack
 *	 -Provides SNMP API for doing stuff
 *	
 *	-Reference: RFC 1157 (for SNMP V1)
 *				RFC 3416 (for SNMPv2C)   	
 *********************************************************************
 * FileName:        SNMP.c
 * Dependencies:    UDP, ARP
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.30 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2009 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 * Author               Date    	Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Nilesh Rajbharti     1/9/03  	Original        (Rev 1.0)
 * Dan Cohen            12/11/03	Removed trap support by #define if not
 *                              	required to lower code space requirements
 * Amit Shirbhate 		09/24/08	SNMPv2c Support, comments and function
 *									headers added.	
 ********************************************************************/

#define __SNMP_C

#include "TCPIPConfig.h"

#if defined(STACK_USE_SNMP_SERVER)

#include "TCPIP Stack/TCPIP.h"

#if defined(STACK_USE_MPFS2)
/****************************************************************************
 *
 *	Begin SNMP for MPFS2.
 *
 ****************************************************************************/

/****************************************************************************
  Section:
	Macros and Definitions
  ***************************************************************************/

// Section:  SNMP agent version types
#define SNMP_V1                 (0)
#define SNMP_V2C				(1)

// Section:  SNMP specific variables
//#define STRUCTURE               (0x30)
//#define ASN_INT                 (0x02)
//#define OCTET_STRING            (0x04)
//#define ASN_NULL                (0x05)
//#define ASN_OID                 (0x06)
//#define SNMP_IP_ADDR            (0x40)
#define SNMP_COUNTER32          (0x41)
#define SNMP_GAUGE32            (0x42)
#define SNMP_TIME_TICKS         (0x43)
#define SNMP_OPAQUE             (0x44)
#define SNMP_NSAP_ADDR          (0x45)

// Section:  SNMP v1 and v2c pdu types
#define GET_REQUEST             (0xa0)
#define GET_NEXT_REQUEST        (0xa1)
#define GET_RESPONSE            (0xa2)
#define SET_REQUEST             (0xa3)
#define TRAP                    (0xa4)
#define GET_BULK_REQUEST        (0xa5)

// Section:  SNMP specific data validation
#define IS_STRUCTURE(a)         (a==STRUCTURE)
#define IS_ASN_INT(a)           (a==ASN_INT)
#define IS_OCTET_STRING(a)      (a==OCTET_STRING)
#define IS_OID(a)               (a==ASN_OID)
#define IS_ASN_NULL(a)          (a==ASN_NULL)
#define IS_GET_REQUEST(a)       (a==GET_REQUEST)
#define IS_GET_NEXT_REQUEST(a)  (a==GET_NEXT_REQUEST)
#define IS_GET_RESPONSE(a)      (a==GET_RESPONSE)
#define IS_SET_REQUEST(a)       (a==SET_REQUEST)
#define IS_TRAP(a)              (a==TRAP)
#define IS_AGENT_PDU(a)         (a==GET_REQUEST || \
                                 a==GET_NEXT_REQUEST || \
                                 a==SET_REQUEST || \
                                 a==SNMP_V2C_GET_BULK)
// Section:  SNMP Udp ports
#define SNMP_AGENT_PORT     (161)
#define SNMP_NMS_PORT       (162)
#define AGENT_NOTIFY_PORT   (0xfffe)

// Section:  SNMP Tx pdu offset settings
#define _SNMPSetTxOffset(o)     (SNMPTxOffset = o)
#define _SNMPGetTxOffset()      SNMPTxOffset


/****************************************************************************
  Section:
	Data Structures and Enumerations
  ***************************************************************************/

// Section:  SNMP specific errors
typedef enum 
{
    SNMP_NO_ERR = 0,			//Snmp no error
    SNMP_TOO_BIG,				//Value too big error
    SNMP_NO_SUCH_NAME,			//No such name in MIB error
    SNMP_BAD_VALUE,				//Not assignable value for the var error	
    SNMP_READ_ONLY,				//Read only variable, write not allowed err
    SNMP_GEN_ERR,				//Snmp gen error
    SNMP_NO_ACCESS,				//Access to modify or read not granted err 
    SNMP_WRONG_TYPE,			//Variable data type wrong error	
    SNMP_WRONG_LENGTH,			//Wrong data length error
    SNMP_WRONG_ENCODING,		//Wrong encoding error
    SNMP_WRONG_VALUE,			//Wrong value for the var type
    SNMP_NO_CREATION,			//No creationg error
    SNMP_INCONSISTENT_VAL,		//Inconsistent value error
    SNMP_RESOURCE_UNAVAILABE,	//Resource unavailbe error	
    SNMP_COMMIT_FAILED,			//Modification update failed error
    SNMP_UNDO_FAILED,			//Modification undo failed	
    SNMP_AUTH_ERROR,			//Authorization failed error
    SNMP_NOT_WRITABLE,			//Variable read only
    SNMP_INCONSISTENT_NAME,		//Inconsistent name
    SNMP_NO_SUCH_OBJ=128,		//No such object error	
    SNMP_NO_SUCH_INSTANCE=129,	//No such instance error
    SNMP_END_OF_MIB_VIEW=130	//Reached to end of mib error
} SNMP_ERR_STATUS;


// Section:  SNMP specific data tyes
typedef enum 
{
    INT8_VAL        = 0x00,		//8 bit integer value
    INT16_VAL       = 0x01,		//16 bit integer value
    INT32_VAL       = 0x02,		//32 bit integer value
    BYTE_ARRAY      = 0x03,		//Aray of bytes	
    ASCII_STRING    = 0x04,		//Ascii string type
    IP_ADDRESS      = 0x05,		//IP address variable
    COUNTER32       = 0x06,		//32 bit counter variable
    TIME_TICKS_VAL  = 0x07,		//Timer vakue counter variable	
    GAUGE32         = 0x08,		//32 bit guage variable
    OID_VAL         = 0x09,		//Object id value var
    DATA_TYPE_UNKNOWN			//Unknown data type
} DATA_TYPE;


// Section:  SNMP specific mib file access information
typedef union
{
    struct
    {
        unsigned int bIsFileOpen : 1;  //MIB file access int flag
    } Flags;						
    BYTE Val;						   //MIB file access byte flag
} SNMP_STATUS;


// Section:  SNMP OID index information
typedef union 
{
    struct
    {
        unsigned int bIsOID:1;	//value is OID/index int flag
    } Flags;
    BYTE Val;					//value is OID/index byte flag
} INDEX_INFO;


// Section:  SNMP object information
typedef union 
{
    struct
    {
        unsigned int bIsDistantSibling : 1; //Object have distant sibling node
        unsigned int bIsConstant : 1;		//Object is constant
        unsigned int bIsSequence : 1;		//Object is sequence
        unsigned int bIsSibling : 1;		//Sibling node flag

        unsigned int bIsParent : 1;			//Node is parent flag	
        unsigned int bIsEditable : 1;		//Node is editable flag
        unsigned int bIsAgentID : 1;		//Node have agent id flag
        unsigned int bIsIDPresent : 1;		//Id present flag
    } Flags;
	BYTE Val;								//MIB Obj info as byte value
} MIB_INFO;


// Section:  SNMP reuested variable list error status information.
//Max variable in a request supported 15
typedef struct 
{
WORD noSuchObjectErr;		//Var list no such obj errors flags
WORD noSuchNameErr;			//Var list no such name error 
WORD noSuchInstanceErr;		//Var list no such instance error
WORD endOfMibViewErr;		//Var list end of mib view error
}reqVarErrStatus;  


// Section:  ASN data type info
typedef struct 
{
    BYTE asnType;	//ASN data type
    BYTE asnLen;	//ASN data length
} DATA_TYPE_INFO;


// Section:  SNMP trap notification information for agent
typedef struct 
{
    char community[NOTIFY_COMMUNITY_LEN];	//Community name array
    BYTE communityLen;						//Community name length
    SNMP_ID agentIDVar;						//Agent id for trap identification
    BYTE notificationCode;					//Trap notification code
    UDP_SOCKET socket;						//Udp socket number	
    DWORD_VAL timestamp;					//Time stamp for trap
} SNMP_NOTIFY_INFO;


// Section:  SNMP MIB variable object information
typedef struct 
{
    DWORD           hNode;		//Node location in the mib		
    BYTE            oid;		//Object Id
    MIB_INFO        nodeInfo;	//Node info
    DATA_TYPE       dataType;	//Data type 
    SNMP_ID         id;			//Snmp Id	
    WORD_VAL        dataLen;	//Data length	
    DWORD           hData;		//Data
    DWORD           hSibling;	//Sibling info
    DWORD           hChild;		//Child info
    BYTE            index;		//Index of object
    BYTE            indexLen;	//Index length
} OID_INFO;


// Section:  SNMP pdu information database 
typedef struct 
{
   	DWORD_VAL		requestID;		//Snmp request id
	BYTE	        nonRepeators;	//# non repeaters in the request	
    BYTE			maxRepetitions;	//# max repeaters in the request 
	BYTE            pduType;		//Snmp pdu type
	BYTE            errorStatus;	//Pdu error status
    BYTE            erroIndex;		//Pdu error Index
	BYTE			snmpVersion;	//Snmp version
	WORD			pduLength;		//Pdu length
} PDU_INFO;


/****************************************************************************
  Section:
	Function Prototypes
  ***************************************************************************/

// Section: Process SNMP request pdus,form response pdus routines
static BYTE _SNMPGet(void);
static void _SNMPPut(BYTE v);
static BYTE FindOIDsInRequest(WORD pdulen);
static SNMP_ACTION ProcessHeader(PDU_INFO* pduDbPtr, char* community, BYTE* len);
static BOOL ProcessGetSetHeader(PDU_INFO* pduDbPtr);
static BOOL ProcessVariables(PDU_INFO* pduDbPtr,char* community, BYTE len);
static BYTE ProcessGetVar(OID_INFO* rec, BOOL bAsOID);
static BYTE ProcessGetNextVar(OID_INFO* rec);
static BYTE ProcessSetVar(PDU_INFO* pduDbPtr,OID_INFO* rec, SNMP_ERR_STATUS* errorStatus);
static BYTE ProcessGetBulkVar(OID_INFO* rec, BYTE* oidValuePtr, BYTE* oidLenPtr,BYTE* successor);

// Section: Routines to validate snmp request pdu elements for SNMP format
static BOOL IsValidOID(BYTE* oid, BYTE* len);
static BOOL IsValidCommunity(char* community, BYTE* len);
static BOOL IsValidInt(DWORD* val);
static BOOL IsValidPDU(SNMP_ACTION* pdu);
static BYTE IsValidLength(WORD* len);
static BYTE IsValidStructure(WORD* dataLen);
static BOOL IsASNNull(void);

// Section: Routines to read/search OIDs,objects from the SNMP MIB database
static BYTE OIDLookup(PDU_INFO* pduDbPtr,BYTE* oid, BYTE oidLen, OID_INFO* rec);
static BOOL GetNextLeaf(OID_INFO* rec);
static BOOL GetOIDStringByAddr(OID_INFO* rec, BYTE* oidString, BYTE* len);
static BOOL GetDataTypeInfo(DATA_TYPE dataType, DATA_TYPE_INFO* info);
static void ReadMIBRecord(DWORD h, OID_INFO* rec);

// Section: Global variables configuration for pdu processings
static void _SNMPDuplexInit(UDP_SOCKET socket);
static void SetErrorStatus(WORD errorStatusOffset,WORD errorIndexOffset,SNMP_ERR_STATUS errorStatus,BYTE errorIndex);

// Section: Routine to check if private mib object is requested by NMS.
static BOOL SNMPCheckIfPvtMibObjRequested(BYTE* OIDValuePtr);

// This function is used only when TRAP is enabled.
#if !defined(SNMP_TRAP_DISABLED)
static BOOL GetOIDStringByID(SNMP_ID id, OID_INFO* info, BYTE* oidString, BYTE* len);
#endif



/****************************************************************************
  Section:
	Global Variables
  ***************************************************************************/
static WORD SNMPTxOffset;	//Snmp udp buffer tx offset
static WORD SNMPRxOffset;	//Snmp udp buffer rx offset		
static SNMP_STATUS SNMPStatus;	//MIB file access status
static UDP_SOCKET SNMPAgentSocket = INVALID_UDP_SOCKET;	//Snmp udp socket
static MPFS_HANDLE hMPFS;	//MPFS file handler
extern TRAP_INFO trapInfo;	//trap information

static BYTE appendZeroToOID;//global flag to modify OID by appending zero 	
reqVarErrStatus snmpReqVarErrStatus; //vars	from req list processing err status	

// SNMPNotifyInfo is not required if TRAP is disabled
#if !defined(SNMP_TRAP_DISABLED)
static SNMP_NOTIFY_INFO SNMPNotifyInfo; //notify info for trap
#endif

//ASN format datatype for snmp v1 and v2c
static ROM DATA_TYPE_INFO dataTypeTable[] =
{
    { ASN_INT,           1       }, //INT8_VAL          
    { ASN_INT,           2       }, //INT16_VAL         
    { ASN_INT,           4       }, //INT32_VAL         
    { OCTET_STRING,      0xff    }, //BYTE_ARRAY        
    { OCTET_STRING,      0xff    }, //ASCII_ARRAY       
    { SNMP_IP_ADDR,      4       }, //IP_ADDRESS        
    { SNMP_COUNTER32,    4       }, //COUNTER32         
    { SNMP_TIME_TICKS,   4       }, //TIME_TICKS_VAL    
    { SNMP_GAUGE32,      4       }, //GAUTE32           
    { ASN_OID,           0xff    }  //OID_VAL           
};


/****************************************************************************
  ===========================================================================
  Section:
	SNMP v1 and v2c Agent Routines
  ===========================================================================
  ***************************************************************************/

/****************************************************************************
  Function:
    void SNMPInit(void)

  Summary:
    Initialize SNMP module internals.

  Description:
  	This function initializes the Snmp agent. One udp socket is intialized 
  	and opened at port 161. Agent will receive and transmit all the snmp 
  	pdus on this udp socket. 
  	
  Precondition:
	At least one UDP socket must be available. UDPInit() is already called.

  Parameters:
	None

  Returns:
	None
    
  Remarks:
	This function is called only once during lifetime of the application.
	One UDP socket will be used.
 ***************************************************************************/
void SNMPInit(void)
{
    // Start with no error or flag set.
    SNMPStatus.Val = 0;

    SNMPAgentSocket = UDPOpen(SNMP_AGENT_PORT, 0, INVALID_UDP_SOCKET);
    // SNMPAgentSocket must not be INVALID_UDP_SOCKET.
    // If it is, compile time value of UDP Socket numbers must be increased.

    return;
}


/****************************************************************************
  Function:
	BOOL SNMPTask(void)

  Summary:
	Polls for every snmp pdu received.

  Description:
	Handle incoming SNMP requests as well as any outgoing SNMP 
	responses and timeout conditions.
	
  Precondition:
	SNMPInit() is already called.

  Parameters:
	None

  Return Values:
	TRUE	-	If SNMP module has finished with a state
	FALSE	-	If a state has not been finished.
	
  Remarks:
	None
 ***************************************************************************/
BOOL SNMPTask(void)
{
    char community[SNMP_COMMUNITY_MAX_LEN];
    BYTE communityLen;
  	PDU_INFO pduInfoDB; //received pdu information database
    BOOL lbReturn;

	if(SNMPAgentSocket == INVALID_UDP_SOCKET)
		return TRUE;

    // Check to see if there is any packet on SNMP Agent socket.
    if ( !UDPIsGetReady(SNMPAgentSocket) )
        return TRUE;

    // As we process SNMP variables, we will prepare response on-the-fly
    // creating full duplex transfer.
    // Current MAC layer does not support full duplex transfer, so
    // SNMP needs to manage its own full duplex connection.
    // Prepare for full duplex transfer.
    _SNMPDuplexInit(SNMPAgentSocket);

	communityLen = 0;	// Suppress C30 warning: 'communityLen' may be used uninitialized in this function
    pduInfoDB.pduType = ProcessHeader(&pduInfoDB,community, &communityLen);

    if ( pduInfoDB.pduType == SNMP_ACTION_UNKNOWN )
        goto _SNMPDiscard;

   if ( !ProcessGetSetHeader(&pduInfoDB))	
        goto _SNMPDiscard;

    // Open MIB file.
    SNMPStatus.Flags.bIsFileOpen = FALSE;

		
	
    hMPFS = MPFSOpenROM((ROM BYTE*)SNMP_BIB_FILE_NAME);

	
	if(hMPFS != MPFS_INVALID_HANDLE)
    {
       SNMPStatus.Flags.bIsFileOpen = TRUE;
    }

    lbReturn = ProcessVariables(&pduInfoDB,community, communityLen);
    if ( SNMPStatus.Flags.bIsFileOpen )
    {
       MPFSClose(hMPFS);
    }

    if ( lbReturn == FALSE )
        goto _SNMPDiscard;

	if(gSendTrapFlag==FALSE)	
   		UDPFlush();

    return TRUE;

_SNMPDiscard:
    UDPDiscard();

    return TRUE;
}


#if !defined(SNMP_TRAP_DISABLED)
/****************************************************************************
  Function:
	void SNMPNotifyPrepare(IP_ADDR* remoteHost,
                           char* community,
                           BYTE communityLen,
                           SNMP_ID agentIDVar,
                           BYTE notificationCode,
                           DWORD timestamp)

  Summary:
	Collects trap notification info and send ARP to remote host.

  Description:
	This function prepares SNMP module to send SNMP trap notification
	to remote host. It sends ARP request to remote host to learn remote
	host MAC address.
	
  Precondition:
	SNMPInit() is already called.

  Parameters:
	remoteHost  - pointer to remote Host IP address
	community   - Community string to use to notify
	communityLen- Community string length
	agentIDVar  - System ID to use identify this agent
	notificaitonCode - Notification Code to use
	timestamp   - Notification timestamp in 100th of second.

  Returns:
	None
		
  Remarks:
	This is first of series of functions to complete SNMP notification.
 ***************************************************************************/
void SNMPNotifyPrepare(IP_ADDR* remoteHost,
                        char* community,
                        BYTE communityLen,
                        SNMP_ID agentIDVar,
                        BYTE notificationCode,
                        DWORD timestamp )
{
	IP_ADDR* remHostIpAddrPtr;
	remHostIpAddrPtr = remoteHost;
							
    strcpy(SNMPNotifyInfo.community, community);
    SNMPNotifyInfo.communityLen = communityLen;

    SNMPNotifyInfo.agentIDVar = agentIDVar;
    SNMPNotifyInfo.notificationCode = notificationCode;

    SNMPNotifyInfo.timestamp.Val = timestamp;

    ARPResolve(remHostIpAddrPtr);
}


/****************************************************************************
  Function:
	BOOL SNMPIsNotifyReady(IP_ADDR* remoteHost)

  Summary:
	Resolves given remoteHost IP address into MAC address.
	
  Description:
  	This function resolves given remoteHost IP address into MAC address using 
  	ARP module. If remoteHost is not aviailable, this function would never 
  	return TRUE. Application must implement timeout logic to handle 
  	"remoteHost not avialable" situation.
	
  Precondition:
	SNMPNotifyPrepare() is already called.

  Parameters:
	remoteHost  - Pointer to remote Host IP address
      
  Return Values:
	TRUE	-	If remoteHost IP address is resolved and 
				SNMPNotify may be called.
    FALSE	-	If remoteHost IP address is not resolved.
    
  Remarks:
	This would fail if there were not UDP socket to open.
 ***************************************************************************/
BOOL SNMPIsNotifyReady(IP_ADDR* remoteHost)
{
    NODE_INFO remoteNode;

	IP_ADDR * remHostIpAddrPtr;
	remHostIpAddrPtr = remoteHost;

    if ( ARPIsResolved(remHostIpAddrPtr, &remoteNode.MACAddr) )
    {
        remoteNode.IPAddr.Val = remHostIpAddrPtr->Val;

        SNMPNotifyInfo.socket = UDPOpen(AGENT_NOTIFY_PORT, &remoteNode, SNMP_NMS_PORT);

        return (SNMPNotifyInfo.socket != INVALID_UDP_SOCKET);
    }
    return FALSE;
}


/****************************************************************************
  Function:
	BOOL SNMPNotify(SNMP_ID var,SNMP_VAL val,SNMP_INDEX index)

  Summary:
  	Creates and Sends TRAP pdu.
	
  Description:
	This function creates SNMP trap PDU and sends it to previously specified
	remoteHost.
	
  Precondition:
	SNMPIsNotifyReady() is already called and returned TRUE.

  Parameters:
	var     - SNMP var ID that is to be used in notification
	val     - Value of var. Only value of BYTE, WORD or DWORD can be sent.
	index   - Index of var. If this var is a single,index would be 0, or else 
			  if this var Is a sequence, index could be any value 
			  from 0 to 127
	  
  Return Values:
	TRUE	-	if SNMP notification was successful sent.
	   			This does not guarantee that remoteHost recieved it.
	FALSE	-	Notification sent failed.
  			    This would fail under following contions:
  			    1) Given SNMP_BIB_FILE does not exist in MPFS
  			    2) Given var does not exist.
  			    3) Previously given agentID does not exist
  			    4) Data type of given var is unknown - only
  			       possible if MPFS itself was corrupted.

  Remarks:
	This would fail if there were not UDP socket to open.
 ***************************************************************************/
BOOL SNMPNotify(SNMP_ID var, SNMP_VAL val, SNMP_INDEX index)
{
	char* pCommunity;
    BYTE len;
    BYTE OIDValue[OID_MAX_LEN];
    BYTE OIDLen;
    BYTE agentIDLen;
    BYTE* pOIDValue;
    WORD packetStructLenOffset;
    WORD pduStructLenOffset;
    WORD varBindStructLenOffset;
    WORD varPairStructLenOffset;
    WORD prevOffset;
    OID_INFO rec;
	DATA_TYPE_INFO dataTypeInfo;

    hMPFS = MPFSOpenROM((ROM BYTE*)SNMP_BIB_FILE_NAME);
    if ( hMPFS == MPFS_INVALID_HANDLE )
    {
        UDPClose(SNMPNotifyInfo.socket);
        return FALSE;
    }

    _SNMPDuplexInit(SNMPNotifyInfo.socket);

    len = SNMPNotifyInfo.communityLen;
    pCommunity = SNMPNotifyInfo.community;

    _SNMPPut(STRUCTURE);            // First item is packet structure
    packetStructLenOffset = SNMPTxOffset;
    _SNMPPut(0);

    // Put SNMP version info.
    _SNMPPut(ASN_INT);              // Int type.
    _SNMPPut(1);                    // One byte long value.

	//Application has to decide which snmp version has to be 
	//updated to the notification pdu.
    //_SNMPPut(SNMP_V1);              // v1.
    _SNMPPut(SNMP_V2C);           // v2

    //len = strlen(community);  // Save community length for later use.
    _SNMPPut(OCTET_STRING);         // Octet string type.
    _SNMPPut(len);                  // community string length
    while( len-- )                  // Copy entire string.
        _SNMPPut(*(pCommunity++));

    // Put PDU type.  SNMP agent's response is always GET RESPONSE
    _SNMPPut(TRAP);
    pduStructLenOffset = SNMPTxOffset;
    _SNMPPut(0);

    // Get complete OID string from MPFS.
    if ( !GetOIDStringByID(SNMPNotifyInfo.agentIDVar,
                           &rec, OIDValue, &agentIDLen) )
    {
        MPFSClose(hMPFS);
        UDPClose(SNMPNotifyInfo.socket);
        return FALSE;
    }

    if ( !rec.nodeInfo.Flags.bIsAgentID )
    {
        MPFSClose(hMPFS);
        UDPClose(SNMPNotifyInfo.socket);
        return FALSE;
    }

    MPFSSeek(hMPFS, rec.hData, MPFS_SEEK_START);

    _SNMPPut(ASN_OID);
    MPFSGet(hMPFS, &len);
    agentIDLen = len;
    _SNMPPut(len);
    while( len-- )
    {
	    BYTE c;
	    MPFSGet(hMPFS, &c);
        _SNMPPut(c);
    }

    // This agent's IP address.
    _SNMPPut(SNMP_IP_ADDR);
    _SNMPPut(4);
    _SNMPPut(AppConfig.MyIPAddr.v[0]);
    _SNMPPut(AppConfig.MyIPAddr.v[1]);
    _SNMPPut(AppConfig.MyIPAddr.v[2]);
    _SNMPPut(AppConfig.MyIPAddr.v[3]);

	// Geberic Trap code
	 _SNMPPut(ASN_INT);
	 _SNMPPut(1);
	 _SNMPPut(gGenericTrapNotification); 
  //_SNMPPut(6);            // Enterprise specific trap code
//    _SNMPPut(4);            // Enterprise specific trap code

	// Specific Trap code
    _SNMPPut(ASN_INT);
    _SNMPPut(1);
    _SNMPPut(SNMPNotifyInfo.notificationCode);

    // Time stamp
    _SNMPPut(SNMP_TIME_TICKS);
    _SNMPPut(4);
    _SNMPPut(SNMPNotifyInfo.timestamp.v[3]);
    _SNMPPut(SNMPNotifyInfo.timestamp.v[2]);
    _SNMPPut(SNMPNotifyInfo.timestamp.v[1]);
    _SNMPPut(SNMPNotifyInfo.timestamp.v[0]);

    // Variable binding structure header
    _SNMPPut(0x30);
    varBindStructLenOffset = SNMPTxOffset;
    _SNMPPut(0);

    // Create variable name-pair structure
    _SNMPPut(0x30);
    varPairStructLenOffset = SNMPTxOffset;
	 _SNMPPut(0);
	 
    // Get complete notification variable OID string.
    if ( !GetOIDStringByID(var, &rec, OIDValue, &OIDLen) )
    {
        MPFSClose(hMPFS);
        UDPClose(SNMPNotifyInfo.socket);
        return FALSE;
    }

    // Copy OID string into packet.
    _SNMPPut(ASN_OID);
    _SNMPPut((BYTE)(OIDLen+1));
    len = OIDLen;
    pOIDValue = OIDValue;
    while( len-- )
        _SNMPPut(*pOIDValue++);
    _SNMPPut(index);

    // Encode and Copy actual data bytes
    if ( !GetDataTypeInfo(rec.dataType, &dataTypeInfo) )
    {
        MPFSClose(hMPFS);
        UDPClose(SNMPNotifyInfo.socket);
        return FALSE;
    }

    _SNMPPut(dataTypeInfo.asnType);

	#if 0  //Amit 
    // In this version, only data type of 4 bytes or less long can be
    // notification variable.
    if ( dataTypeInfo.asnLen == 0xff )
    {
        MPFSClose(hMPFS);
        UDPClose(SNMPNotifyInfo.socket);
        return FALSE;
    }
	#endif

	#if 1 

	//Modified to Send trap even for  dataTypeInfo.asnType= ASCII_STRING, 
	//where dataTypeInfo.asnLen=0xff

	if ( dataTypeInfo.asnLen == 0xff )
	{
		dataTypeInfo.asnLen=0x4;
		val.dword=0;
	}
	#endif

    len = dataTypeInfo.asnLen;
    _SNMPPut(len);
    while( len-- )
        _SNMPPut(val.v[len]);

    len = dataTypeInfo.asnLen           // data bytes count
         + 1                            // Length byte
         + 1                            // Data type byte
         + OIDLen                       // OID bytes
         + 2                            // OID header bytes
         + 1;                           // index byte

    prevOffset = _SNMPGetTxOffset();
    _SNMPSetTxOffset(varPairStructLenOffset);
    _SNMPPut(len);

    len += 2;                           // Variable Binding structure header
    _SNMPSetTxOffset(varBindStructLenOffset);
    _SNMPPut(len);

    len = len
        + 2                             // Var bind struct header
        + 6                             // 6 bytes of timestamp
        + 3                             // 3 bytes of trap code
        + 3                             // 3 bytes of notification code
        + 6                             // 6 bytes of agnent IP address
        + agentIDLen                    // Agent ID bytes
        + 2;                                // Agent ID header bytes
    _SNMPSetTxOffset(pduStructLenOffset);
    _SNMPPut(len);

    len = len                           // PDU struct length
        + 2                             // PDU header
        + SNMPNotifyInfo.communityLen            // Community string bytes
        + 2                             // Community header bytes
        + 3;                            // SNMP version bytes
    _SNMPSetTxOffset(packetStructLenOffset);
    _SNMPPut(len);

    _SNMPSetTxOffset(prevOffset);

    MPFSClose(hMPFS);
    UDPFlush();
    UDPClose(SNMPNotifyInfo.socket);

    return TRUE;
}
#endif // Code removed when SNMP_TRAP_DISABLED


/****************************************************************************
  Function:
	SNMP_ACTION ProcessHeader(PDU_INFO* pduDbPtr,
							  char* community, BYTE* len)

  Summary:
  	Validates the received udp packet Snmp header. 
	
  Description:
  	Collects PDU_INFO (SNMP pdu information database),community name,
  	community length and length of data payload. 
	This function validates the received udp packet for these different 
	variables of snmp pdu. The sequence in which these elements
	are received is important. The validation is done for the agent
	processing capabilities and the max UDP packet length as UDP packets
	can not be fragmented.
		
  Precondition:
	UDPIsGetReady(SNMPAgentSocket) is called in SNMPTask(),
	it check if there is any packet on SNMP Agent socket,
    should return TRUE.
    
  Parameters:
  	 pduDbPtr  - Pointer to received pdu information database
	 community - Pointer to var storing, community string in rxed pdu
	 len	   - Pointer to var storing, community string length rxed in pdu	
	 
  Return Values:
	SNMP_ACTION - Snmp request pdu type.
	
  Remarks:
	The received pdu will be processed only if this routine returns the
	pdu type else the pdu is discarded as not Snmp pdu.
 ***************************************************************************/
static SNMP_ACTION ProcessHeader(PDU_INFO* pduDbPtr, char* community, BYTE* len)
{
    DWORD_VAL tempLen;
    SNMP_ACTION pdu;
	
    // Very first item must be a structure
    if ( !IsValidStructure((WORD*)&tempLen) )
        return SNMP_ACTION_UNKNOWN;

    if ( !IsValidInt(&tempLen.Val) )
        return SNMP_ACTION_UNKNOWN;

	pduDbPtr->snmpVersion= tempLen.v[0];
    if ( (tempLen.v[0] != SNMP_V1) && ( tempLen.v[0] != SNMP_V2C ))
        return SNMP_ACTION_UNKNOWN;

    // This function populates response as it processes community string.
    if ( !IsValidCommunity(community, len) )
        return SNMP_ACTION_UNKNOWN;

    // Fetch and validate pdu type.  
    if ( !IsValidPDU(&pdu) )
        return SNMP_ACTION_UNKNOWN;

	//Get_Bulk_Request is not defined in SNMP V1, hence discard udp request packet	
	if(pduDbPtr->snmpVersion==SNMP_V1 && pduDbPtr->pduType == GET_BULK_REQUEST)
		return SNMP_ACTION_UNKNOWN;
	

    // Ask main application to verify community name against requested pdu type.
    if(SNMPValidateCommunity((BYTE *)community)==INVALID_COMMUNITY)
        return SNMP_ACTION_UNKNOWN;

    return pdu;
}

/****************************************************************************
  Function:
	BOOL ProcessGetSetHeader(PDU_INFO* pduDbPtr)
	
  Summary:
  	Validates the received udp packet Get/Set request header. 
	
  Description:
	All the variables of snmp pdu request header are validated for their
	data types. Collects request_id for the snmp request pdu. Fetch,validates
	error status,error index and discard as they are need not to be processed
	as received in request pdu. Collects non repeaters and max repeaters
	values in case of Get_Bulk request.  
  	
  Precondition:
	ProcessHeader() is called and returns pdu type and do not returns 
	SNMP_ACTION_UNKNOWN
    
  Parameters:
  	pduDbPtr  - Pointer to received pdu information database.
  	
  Return Values:
	TRUE  - If the received request header is validated and passed.
	FALSE - If rxed request header is not valid.
	
  Remarks:
	The request pdu will be processed only if this routine returns TRUE
 ***************************************************************************/
static BOOL ProcessGetSetHeader(PDU_INFO* pduDbPtr)
{
    DWORD_VAL tempData;

    // Fetch and save request ID.
    if ( IsValidInt(&tempData.Val) )
         pduDbPtr->requestID.Val = tempData.Val;
    else
        return FALSE;

	if((pduDbPtr->snmpVersion == SNMP_V1 || pduDbPtr->snmpVersion == SNMP_V2C) &&(pduDbPtr->pduType != GET_BULK_REQUEST))
	{
	    // Fetch and discard error status
	    if ( !IsValidInt(&tempData.Val) )
	        return FALSE;

	    // Fetch and disacard error index
	    return IsValidInt(&tempData.Val);
	}
	else if( pduDbPtr->snmpVersion == SNMP_V2C && pduDbPtr->pduType == GET_BULK_REQUEST )
	{
		// Fetch non-repeaters value
		if ( IsValidInt(&tempData.Val) )
			 pduDbPtr->nonRepeators=tempData.v[0];
		else
			return FALSE;
			
		// Fetch Max-repetitions value
		if(IsValidInt(&tempData.Val))
			 pduDbPtr->maxRepetitions=(BYTE)tempData.v[0];
		else
			return FALSE;
	}
	else 
		return FALSE;
	
	return TRUE;
}


/****************************************************************************
  Function:
	BOOL ProcessVariables(PDU_INFO* pduDbPtr,BYTE* community, BYTE len)
	
  Summary:
  	This routine processes the snmp request and parallely creates the 
  	response pdu.
	
  Description:
  	Once the received pdu is validated as Snmp pdu, it is forwarded for 
  	processing to this routine. This rotuine handles Get, Get_Next, Get_Bulk,
  	Set request and creates appropriate response as Get_Response. 
  	This routine will decide on whether the request pdu should be processed
  	or be discarded.
	
  Precondition:
	The received udp packet is varified as SNMP request.
	ProcessHeader() and ProcessGetSetHeader() returns but FALSE.
	
  Parameters:
  	pduDbPtr  - Pointer to received pdu information database
    community - Pointer to var, storing community string in rxed pdu
	len	   	  - Pointer to var, storing community string length rxed in pdu
	
  Return Values:
	TRUE 	- If the snmp request processing is successful.
	FALSE	- If the processing failed else the processing is not completed.
	
  Remarks:
  	This routine will hog the cpu till the snmp pdu processing is completed
  	irrespetcive of the size of the pdu and the number of variables requested.
	The local variables are defined as non static. 
	If application need this routine to be executed in co-operative manner,
	uncomment the "return" in Switch case and change all the local varaibles
	to Static variables. This will increase the response time to snmp request,
	will eat up memory in static variable allocation.
	Also the application should take care that the next snmp PDU is not read 
	untill the current pdu processing is completed. This control can be 
	achieved using a gloabl flag and polled for in SNMPTask().
 ***************************************************************************/
static BOOL ProcessVariables(PDU_INFO* pduDbPtr,char* community, BYTE len)
{
    BYTE temp;
    BYTE OIDValue[OID_MAX_LEN];
    BYTE OIDLen;
   	BYTE varIndex;
	BYTE errorIndex;
	BYTE communityLen,commRetVal;
	BYTE noOfOIDsInReq,tempNonRepeators,noOfVarToBeInResponse;
	BYTE repeatCntr,varBindCntr;
	BYTE Getbulk_N,Getbulk_M,Getbulk_R;/*Refer RFC 3416 Section "4.2.3" GetBulkRequest-PDU*/
	BYTE oidLookUpRet;
	BYTE templen;
	BYTE successor=0;// 'I'th lexicographic successor 
	 
	BYTE *ptemp;
	BYTE *ptroid;
	BYTE *rxedCommunityName;
   
    WORD oidOffset;
    WORD prevOffset;
	WORD packetStructLenOffset;
    WORD pduLenOffset;
    WORD errorStatusOffset;
    WORD errorIndexOffset;
    WORD varBindStructOffset;
    WORD varStructLenOffset;	
	WORD prevSnmpRxOffset;	
	
    WORD_VAL varBindingLen;
    WORD_VAL tempLen;
    WORD_VAL varPairLen;
    WORD_VAL varBindLen;

	OID_INFO OIDInfo;    
    SNMP_ERR_STATUS errorStatus;
	
	static enum 
	{
		SM_PKT_STRUCT_LEN_OFFSET=0u,
		SM_RESPONSE_PDU_LEN_OFFSET,
		SM_ERROR_STATUS_OFFSET,
		SM_ERROR_INDEX_OFFSET,
		SM_FIND_NO_OF_REQUESTED_VARBINDS,
		SM_FIND_NO_OF_RESPONSE_VARBINDS,
		SM_VARBIND_STRUCT_OFFSET,
		SM_VARSTRUCT_LEN_OFFSET,
		SM_POPULATE_REQ_OID,
		SM_FIND_OID_IN_MIB,
		SM_NON_REPETITIONS,
		SM_MAX_REPETITIONS
	}smSnmp=SM_PKT_STRUCT_LEN_OFFSET;

	snmpReqVarErrStatus.noSuchInstanceErr=0x0000;
	snmpReqVarErrStatus.noSuchNameErr=0x0000;
	snmpReqVarErrStatus.noSuchObjectErr=0x0000;
	snmpReqVarErrStatus.endOfMibViewErr=0x0000;

	rxedCommunityName=(BYTE *)community;

	while(1)
	{
		switch(smSnmp)
		{

		// Before each variables are processed, prepare necessary header.

		case SM_PKT_STRUCT_LEN_OFFSET:

			varPairLen.Val=0x0000;

			_SNMPPut(STRUCTURE); // First item is packet structure

			// Since we do not know length of structure at this point, use
			// placeholder bytes that will be replaced with actual value.
			_SNMPPut(0x82);
			packetStructLenOffset = SNMPTxOffset;
			_SNMPPut(0);
			_SNMPPut(0);

			// Put SNMP version info - only v1.0 is supported.
			_SNMPPut(ASN_INT);              // Int type.
			_SNMPPut(1);                    // One byte long value.
			_SNMPPut(pduDbPtr->snmpVersion);              // v1.0.

			// Put community string
			communityLen = len;             // Save community length for later use.
			_SNMPPut(OCTET_STRING);         // Octet string type.
			_SNMPPut(len);                  // community string length
			while( len-- )                  // Copy entire string.
			_SNMPPut(*community++);

			smSnmp++;

			//return FALSE;
		case SM_RESPONSE_PDU_LEN_OFFSET:

			// Put PDU type.  SNMP agent's response is always GET RESPONSE
			_SNMPPut(GET_RESPONSE);
			
			// Since we don't know length of this response, use placeholders until
			// we know for sure...
			_SNMPPut(0x82);                    
			pduLenOffset = SNMPTxOffset;
			_SNMPPut(0); // Be prepared for 2 byte-long length
			_SNMPPut(0);

			// Put original request back.
			_SNMPPut(ASN_INT);	// Int type.
			_SNMPPut(4);		// To simplify logic, always use 4 byte long requestID
			_SNMPPut(pduDbPtr->requestID.v[3]); // Start MSB
			_SNMPPut(pduDbPtr->requestID.v[2]);
			_SNMPPut(pduDbPtr->requestID.v[1]);
			_SNMPPut(pduDbPtr->requestID.v[0]);

			smSnmp++;

			//return FALSE;
			
		case SM_ERROR_STATUS_OFFSET :

			// Put error status.
			// Since we do not know error status, put place holder until we know it...
			_SNMPPut(ASN_INT);              // Int type
			_SNMPPut(1);                    // One byte long.
			errorStatusOffset = SNMPTxOffset;
			_SNMPPut(0);                    // Placeholder.
			smSnmp++;

		case SM_ERROR_INDEX_OFFSET :

			// Similarly put error index.
			_SNMPPut(ASN_INT);              // Int type
			_SNMPPut(1);                    // One byte long
			errorIndexOffset = SNMPTxOffset;
			_SNMPPut(0);                    // Placeholder.

			varIndex    = 0;
			errorIndex  = 0;
			errorStatus = SNMP_NO_ERR;

			smSnmp++;

		case SM_FIND_NO_OF_REQUESTED_VARBINDS:

			// Decode variable binding structure
			if ( !IsValidStructure(&varBindingLen.Val) )
			return FALSE;

			//Find number of OIDs/varbinds's data requested in received PDU.
			noOfOIDsInReq=FindOIDsInRequest(varBindingLen.Val);
			
			smSnmp++;	

			//return FALSE;

		case SM_FIND_NO_OF_RESPONSE_VARBINDS:

			//Calulate number of variables to be responded for the received request
			Getbulk_N = noOfOIDsInReq; Getbulk_M=0; Getbulk_R=0;
			if((pduDbPtr->snmpVersion == SNMP_V2C) && (pduDbPtr->pduType == GET_BULK_REQUEST))
			{
				if((pduDbPtr->nonRepeators) <= noOfOIDsInReq)
				{
					Getbulk_N = pduDbPtr->nonRepeators;
				}

				Getbulk_M = pduDbPtr->maxRepetitions;

				if((noOfOIDsInReq - Getbulk_N)>=0)
					Getbulk_R = noOfOIDsInReq-Getbulk_N;
			}

			tempNonRepeators = Getbulk_N;

			noOfVarToBeInResponse = Getbulk_N + (Getbulk_M * Getbulk_R);//Refer RFC 3416 

			smSnmp++;

			//return FALSE;

		case SM_VARBIND_STRUCT_OFFSET:
	
			// Put variable binding response structure
			_SNMPPut(STRUCTURE);
			_SNMPPut(0x82);

			// Since we do not know data payload length, put place holder until we know it...
			varBindStructOffset = SNMPTxOffset;
			_SNMPPut(0);
			_SNMPPut(0);

			varBindLen.Val = 0;

			smSnmp++;

			//return FALSE;
			
		case SM_VARSTRUCT_LEN_OFFSET:

			/*	If the getbulk request is received with zero non-repeaters, process
				variable State Machine jumps to SM_MAX_REPETITIONS. Modify the Rx
				and Tx offset accordigly. */
			if(Getbulk_N==0)
			{
				prevSnmpRxOffset=SNMPRxOffset;
				smSnmp=SM_MAX_REPETITIONS;
				varStructLenOffset = SNMPTxOffset;
				SNMPTxOffset=SNMPTxOffset+4;
				break;
			}
			
			/*
				Need to know what variable we are processing, so that in case
				if there is problem for that varaible, we can put it in
				errorIndex location of SNMP packet.
			*/
			varIndex++;

			// Decode variable length structure
			temp = IsValidStructure(&tempLen.Val);
			if ( !temp )
			return FALSE;

			varBindingLen.Val -= tempLen.Val;
			varBindingLen.Val -= temp;

			varStructLenOffset = SNMPTxOffset;

			if(pduDbPtr->pduType == GET_BULK_REQUEST )
			{
				SNMPTxOffset=SNMPTxOffset+4;
			}
			smSnmp++;

			//return FALSE;

		case SM_POPULATE_REQ_OID:
			
			/* 	Populate received pdu for the requested OIDs and also create the 
				response pdu on the go.*/
			
			// Decode next object
			if ( !IsValidOID(OIDValue, &OIDLen) )
			return FALSE;

			// For Get & Get-Next, value must be NULL.
			if ( pduDbPtr->pduType != (BYTE)SET_REQUEST )
			{
				if ( !IsASNNull() )
				return FALSE;
			}

			if(pduDbPtr->pduType != GET_BULK_REQUEST )
			{
				// Prepare response - original variable
				_SNMPPut(ASN_OID);
				oidOffset = SNMPTxOffset;
				_SNMPPut(OIDLen);
				ptemp = OIDValue;
				temp = OIDLen;
				while( temp-- )
				_SNMPPut(*ptemp++);
			}


			/* 
			   Match "rxedCommunityName" to "readCommunity" to authorize access
			   to private MIB objects.
			   As we start supporting the secured encrypted community transaction, 
			   rxed community string can be an encrypted string which the agent
			   need to decrypt and validate to autohrize access.
			   The agent should respond with encrypted community name.
			*/

			commRetVal=SNMPValidateCommunity(rxedCommunityName);
				
			smSnmp=SM_PKT_STRUCT_LEN_OFFSET;	// Start out assuming commRetVal == INVALID_COMMUNITY
			if(pduDbPtr->pduType == (BYTE)SET_REQUEST)
			{	
				if(commRetVal==WRITE_COMMUNITY)//If SET request, then "community==WRITE_COMMUNITY" is must.
					smSnmp=SM_FIND_OID_IN_MIB;
			}
			else 
			{	
				if(commRetVal!=INVALID_COMMUNITY)//If any GET request, then "community!=INVALID_COMMUNITY" is must (community is WRITE_COMMUNITY or READ_COMMUNITY).
					smSnmp=SM_FIND_OID_IN_MIB;
			}

			//Verify if trying to access the private object
			//Application has to decide on what community name should allowed to
			//read write the private mib objects.

			if(SNMPCheckIfPvtMibObjRequested(OIDValue) && (smSnmp==SM_PKT_STRUCT_LEN_OFFSET) )
			{
				//If private mib object is requested and community do not match, 
				//generate authentication failure TRAP

				Getbulk_N=0;
				noOfVarToBeInResponse=0;
				smSnmp=SM_PKT_STRUCT_LEN_OFFSET;	

				//Searching the requested OID in the MIB database 
				oidLookUpRet = OIDLookup(pduDbPtr,OIDValue, OIDLen, &OIDInfo);	
				gOIDCorrespondingSnmpMibID=OIDInfo.id;

				_SNMPSetTxOffset(packetStructLenOffset-2);
				gSpecificTrapNotification=VENDOR_TRAP_DEFAULT;
				gGenericTrapNotification=AUTH_FAILURE;
				gSendTrapFlag=TRUE;	

			}
			/*else 
				smSnmp++;*/

			if(smSnmp==SM_PKT_STRUCT_LEN_OFFSET || smSnmp==SM_VARSTRUCT_LEN_OFFSET)
				break;	
				
			//return FALSE;
			
		case SM_FIND_OID_IN_MIB:

			/* Search for the requested OID in the MIB database with the agent.*/
			
			if(Getbulk_N!= 0)
				Getbulk_N--;
			
			if(Getbulk_N==0)
				prevSnmpRxOffset=SNMPRxOffset;

			noOfVarToBeInResponse--;

			//Searching the requested OID in the MIB database 
			oidLookUpRet = OIDLookup(pduDbPtr,OIDValue, OIDLen, &OIDInfo);	

			if(oidLookUpRet != TRUE && pduDbPtr->pduType != GET_NEXT_REQUEST)
			{
				_SNMPSetTxOffset(varStructLenOffset);

				// Put corresponding variable response structure
				_SNMPPut(STRUCTURE);
				_SNMPPut(0x82);
				
				varStructLenOffset=_SNMPGetTxOffset();
				_SNMPPut(0x00);//Place holder
				_SNMPPut(0x00);

				// ASN OID data type
				templen=OIDLen;
				ptroid=OIDValue;	
				_SNMPPut(ASN_OID);

				if(appendZeroToOID)
					_SNMPPut(OIDLen+1);//for appending "0"
				else 
					_SNMPPut(OIDLen);//do not append "0"		

				//Put OID
				while( templen-- )
				_SNMPPut(*ptroid++);

				if(appendZeroToOID)
				{
					_SNMPPut(0x00);//Appending '0' to OID in response
					varPairLen.Val += OIDLen+1+2; //Modify the response length
				}
				else 
					varPairLen.Val += OIDLen+2;
			
				//update and send the error status and the error index.
				if(pduDbPtr->snmpVersion == SNMP_V1)
				{
					errorStatus = SNMP_NO_SUCH_NAME;
					SetErrorStatus(errorStatusOffset,errorIndexOffset,SNMP_NO_SUCH_NAME,varIndex);

					_SNMPPut(ASN_NULL);
					_SNMPPut(0);	
				}
				else if( pduDbPtr->snmpVersion == SNMP_V2C && pduDbPtr->pduType != SET_REQUEST)
				{
					if(pduDbPtr->pduType == SNMP_GET)
					{
						_SNMPPut(oidLookUpRet);
						_SNMPPut(0x00);
						if(oidLookUpRet == SNMP_NO_SUCH_OBJ)
						{
							snmpReqVarErrStatus.noSuchObjectErr|=(0x0001 << varIndex);
						}
						else if(oidLookUpRet == SNMP_NO_SUCH_INSTANCE)
						{
							snmpReqVarErrStatus.noSuchInstanceErr|=(0x0001 << varIndex);
						}
					}
					else if(pduDbPtr->pduType == GET_BULK_REQUEST )
					{
						_SNMPPut(SNMP_END_OF_MIB_VIEW);
						_SNMPPut(0x00);
						snmpReqVarErrStatus.endOfMibViewErr|=(0x0001 << varIndex);
					}
				}

				varPairLen.Val +=2 ;

				varBindLen.Val += 4	// Variable Pair STRUCTURE byte + 1 length byte.
				+ varPairLen.Val;

				//Now update the place holder for var pair length
				prevOffset = _SNMPGetTxOffset();
				_SNMPSetTxOffset(varStructLenOffset);

				_SNMPPut(varPairLen.v[1]);
				_SNMPPut(varPairLen.v[0]);

				_SNMPSetTxOffset(prevOffset);

				varPairLen.Val=0x00;

				//Reset to state machine to access the next oid in request
				smSnmp=SM_VARSTRUCT_LEN_OFFSET;
				break;	
			}
			smSnmp++;

			//return FALSE;

		case SM_NON_REPETITIONS:

			/* 	Variables in get,get_next,set and get_bulk ( non repetition variables)
				of snmp request are processed in this part of the state machine.*/
			
			//Save SnmpTxOffsetfor future uses.
			prevOffset = _SNMPGetTxOffset();
			_SNMPSetTxOffset(varStructLenOffset);

			//Start response variable binding with ASN STRUCTURE type.	
			_SNMPPut(STRUCTURE);
			_SNMPPut(0x82);

			varStructLenOffset=_SNMPGetTxOffset();
			_SNMPPut(0x00); //place holder
			_SNMPPut(0x00);

			_SNMPPut(ASN_OID); 

			if(pduDbPtr->pduType == SNMP_SET)
            {
            	templen=OIDLen;
				ptroid=OIDValue;	

				if(appendZeroToOID)
					_SNMPPut(OIDLen+1);//for appending "0"
				else 
					_SNMPPut(OIDLen);//do not append "0"		

				//Put OID
				while( templen-- )
				_SNMPPut(*ptroid++);

				if(appendZeroToOID)
					_SNMPPut(0x00);//Appending '0' to OID in response

				//Now process the SET command
                temp = ProcessSetVar(pduDbPtr,&OIDInfo, &errorStatus);

				if ( errorStatus != SNMP_NO_ERR )
                {
	                //SET var command failed. Update the error status.
                    SetErrorStatus(errorStatusOffset,
                                   errorIndexOffset,
                                   errorStatus,
                                   varIndex);

                }

				if(appendZeroToOID)
					varPairLen.Val = OIDLen+1 +2   // OID name + header bytes
                                + temp;            // value bytes as put by SetVar
				else
					varPairLen.Val = OIDLen+2+temp;
				
			}
			else if(pduDbPtr->pduType == SNMP_GET || pduDbPtr->pduType == SNMP_V2C_GET_BULK)
			{	 
				templen=OIDLen;
				ptroid=OIDValue;	
				
				if(appendZeroToOID)
					_SNMPPut(OIDLen+1);//for appending "0"
				else 
					_SNMPPut(OIDLen);//do not append "0"

				//Put OID
				while( templen-- )
					_SNMPPut(*ptroid++);
				
				if(appendZeroToOID)
				{
					_SNMPPut(0x00);//Appending '0' to OID in response
					varPairLen.Val = OIDLen + 2+1;
				}
				else 
					varPairLen.Val = OIDLen +2;

				//Now process the GET command
				temp=ProcessGetVar(&OIDInfo,FALSE);

			}	
			else if(pduDbPtr->pduType == SNMP_GET_NEXT)
			{			
				temp=ProcessGetNextVar(&OIDInfo);

				//If Get Next command failed
				if(temp==0)
				{
					templen=OIDLen;
					ptroid=OIDValue;
					
					if(appendZeroToOID)
						_SNMPPut(OIDLen+1);//for appending "0"
					else 
						_SNMPPut(OIDLen);//do not append "0"

					//Put OID
					while( templen-- )
						_SNMPPut(*ptroid++);
					
					if(appendZeroToOID)
						_SNMPPut(0x00);//Appending '0' to OID in response
				}
			}


			/*  If the request command processing is failed, update
				the error status, index accordingly and response pdu.*/ 
			if(temp == 0 &&(pduDbPtr->pduType != SNMP_SET))
			{
				if(pduDbPtr->snmpVersion == SNMP_V1)
				{
					errorStatus = SNMP_NO_SUCH_NAME;
					SetErrorStatus(errorStatusOffset,errorIndexOffset,SNMP_NO_SUCH_NAME,
								   varIndex);
				}

				_SNMPPut(ASN_NULL);
				_SNMPPut(0);

				if((pduDbPtr->pduType == SNMP_GET_NEXT|| pduDbPtr->pduType == SNMP_V2C_GET_BULK)&&pduDbPtr->snmpVersion == SNMP_V2C)
				{
					SNMPTxOffset=SNMPTxOffset-2;
					_SNMPPut(SNMP_END_OF_MIB_VIEW);
					_SNMPPut(0);
				
				}

				if(pduDbPtr->pduType == SNMP_GET || pduDbPtr->pduType == SNMP_V2C_GET_BULK)
				{
					temp = 2;
				}
				else if(pduDbPtr->pduType == SNMP_GET_NEXT)	{
				     varPairLen.Val = OIDLen+1          // as put by GetNextVar()
                                     + 2                // OID header
                                     + 2;               // END_OF_MIB_VIEW bytes
				}


				/* 	Applications can make use of the below information 
					to find the error status for the given variable and to 
					build the logic arround. */
				snmpReqVarErrStatus.noSuchNameErr	 |=(0x0001 << varIndex);
				snmpReqVarErrStatus.noSuchObjectErr	 |=(0x0001 << varIndex);
				snmpReqVarErrStatus.noSuchInstanceErr|=(0x0001 << varIndex);
				snmpReqVarErrStatus.endOfMibViewErr	 |=(0x0001 << varIndex);
				
			}
			else if(pduDbPtr->pduType == SNMP_GET_NEXT)
			{
				//varPairLen.Val = (temp + 2+OIDLen+1+1);
				varPairLen.Val = (temp + 2);
			}
	
			if(pduDbPtr->pduType == SNMP_GET || pduDbPtr->pduType == SNMP_V2C_GET_BULK)
				varPairLen.Val += temp;   

			varBindLen.Val += 4	// Variable Pair STRUCTURE byte + 1 length byte.
			+ varPairLen.Val;

			//Update place holder
			prevOffset = _SNMPGetTxOffset();
			_SNMPSetTxOffset(varStructLenOffset);
			_SNMPPut(varPairLen.v[1]);
			_SNMPPut(varPairLen.v[0]);

			_SNMPSetTxOffset(prevOffset);
			varStructLenOffset = _SNMPGetTxOffset();

			varPairLen.Val=0x00;

			/* 	Decide on the number of Non repetition variables remained to 
				be processed, decide the course of state machine.*/
				
			if((pduDbPtr->pduType==GET_BULK_REQUEST) &&
			   (pduDbPtr->snmpVersion == SNMP_V2C) &&( Getbulk_N == 0))
				smSnmp=SM_MAX_REPETITIONS;
			else
				smSnmp=SM_VARSTRUCT_LEN_OFFSET;
			break;	

			//return FALSE;

		case SM_MAX_REPETITIONS:

			/*Process each variable in request as Get_Next for 
			  Getbulk_M (Max_repetition) times */
			for(repeatCntr=0;repeatCntr<Getbulk_M;repeatCntr++)
			{
				SNMPRxOffset=prevSnmpRxOffset;
				
				//Process every veriable in the request.
				for(varBindCntr=0;varBindCntr<Getbulk_R;varBindCntr++)
				{

					if(varBindCntr==0)
						varIndex=(noOfOIDsInReq-Getbulk_R);

					varIndex++;

					if((snmpReqVarErrStatus.endOfMibViewErr >> (tempNonRepeators+varBindCntr+1))&0x0001)
 					{
						noOfVarToBeInResponse--;
 						temp = IsValidStructure(&tempLen.Val);

						if(varBindCntr!=Getbulk_R)
						{
							SNMPRxOffset=SNMPRxOffset+tempLen.Val;//2+OIDLen+2;
						}
						continue;
					}

					noOfVarToBeInResponse--;
					prevOffset = _SNMPGetTxOffset();
					_SNMPSetTxOffset(varStructLenOffset);

					_SNMPPut(STRUCTURE);
					_SNMPPut(0x82);
					varStructLenOffset=_SNMPGetTxOffset();
					_SNMPPut(0x00);
					_SNMPPut(0x00);

					successor=repeatCntr;

					// Decode variable length structure
					temp = IsValidStructure(&tempLen.Val);
					if ( !temp )
						break;

					// Decode next object
					if ( !IsValidOID(OIDValue, &OIDLen) )
						return FALSE;

					templen=OIDLen;
					ptroid=OIDValue;
					
					// For Get & Get-Next, value must be NULL.
					if ( pduDbPtr->pduType != (BYTE)SET_REQUEST )
						if ( !IsASNNull() )
							break;

					if(!OIDLookup(pduDbPtr,OIDValue, OIDLen, &OIDInfo))
					{
						templen=OIDLen;
						ptroid=OIDValue;	
						_SNMPPut(ASN_OID);

						if(appendZeroToOID)
							_SNMPPut(OIDLen+1);//for appending "0"
						else 
							_SNMPPut(OIDLen);//for appending "0"

						//Put OID
						while( templen-- )
							_SNMPPut(*ptroid++);
						
						if(appendZeroToOID)
							_SNMPPut(0x00);//Appending '0' to OID in response

						_SNMPPut(SNMP_END_OF_MIB_VIEW);
						_SNMPPut(0x00);

						//Start counting total number of bytes in this structure.
						varPairLen.Val = OIDLen+1 // as put by GetNextVar()
						 +2       // OID header
						 +2;      // endOfMibView bytes

						snmpReqVarErrStatus.endOfMibViewErr	 |=(0x0001 << varIndex);
					}
					else
					{
						temp = ProcessGetBulkVar(&OIDInfo, &OIDValue[0],&OIDLen,&successor);
						if ( temp == 0 )
						{
							templen=OIDLen;
							ptroid=OIDValue;	
							_SNMPPut(ASN_OID);
							_SNMPPut(OIDLen);

							//Put OID
							while( templen-- )
							_SNMPPut(*ptroid++);

							/*Do send back the Same OID if get_next is EndOfMibView. Do not
							  append zero to this OID*/
							
							_SNMPPut(SNMP_END_OF_MIB_VIEW);
							_SNMPPut(0x00);

							snmpReqVarErrStatus.endOfMibViewErr	 |=(0x0001 << varIndex);
							                    
							//Start counting total number of bytes in this structure.
							varPairLen.Val = OIDLen  // as put by GetNextVar()
							     + 2     // OID header
							     + 2;    // endOfMibView byte.
						}
						else 
							varPairLen.Val = (temp + 2);        // + OID headerbytes
					}
				
					varBindLen.Val += 4	// Variable Pair STRUCTURE byte + 1 length byte.
					+ varPairLen.Val;

					prevOffset = _SNMPGetTxOffset();
					_SNMPSetTxOffset(varStructLenOffset);

					_SNMPPut(varPairLen.v[1]);
					_SNMPPut(varPairLen.v[0]);

					_SNMPSetTxOffset(prevOffset);
					varStructLenOffset = _SNMPGetTxOffset();
						 
				}//for(varBindCntr=0;varBindCntr<Getbulk_R;varBindCntr++)
				
			}//for(repeatCntr=0;repeatCntr<Getbulk_M;repeatCntr++)
			
			break;
		}//end of switch(smSnmp)

		/*If all the variables are processed and the repsonse pdu is updated with 
		  the number of variable responses ought to be in the response; you are done
		  with the request pdu processing. Else continue to processing.*/
		if(Getbulk_N==0 && noOfVarToBeInResponse==0)
		{	
 			smSnmp=SM_PKT_STRUCT_LEN_OFFSET;
			break;
		}

	}//end of while(1)		


	// Update the place holders with respective values.
		
	prevOffset = _SNMPGetTxOffset();

    _SNMPSetTxOffset(varBindStructOffset);
    _SNMPPut(varBindLen.v[1]);
    _SNMPPut(varBindLen.v[0]);

    // varBindLen is reused as "pduLen"
    varBindLen.Val = varBindLen.Val+4       // Variable Binding Strucure length
                + 6                         // Request ID bytes (4+2)
                + 3                         // Error status		(2+1)
                + 3;                        // Error index		(2+1)	

    _SNMPSetTxOffset(pduLenOffset);
    _SNMPPut(varBindLen.v[1]);
    _SNMPPut(varBindLen.v[0]);

    // varBindLen is reused as "packetLen".
    varBindLen.Val = 3                      // SNMP Version bytes
                    + 2 + communityLen      // community string bytes
                    + 4                     // PDU structure header bytes.
                    + varBindLen.Val;

    _SNMPSetTxOffset(packetStructLenOffset);
    _SNMPPut(varBindLen.v[1]);
    _SNMPPut(varBindLen.v[0]);

	_SNMPSetTxOffset(prevOffset);

     return TRUE;
	
}


/****************************************************************************
  Function:
	BYTE ProcessGetNextVar(OID_INFO* rec)
	
  Summary:
  	Retrieves next node from the MIB database.  
  	
  Description:
  	This routine reads into the MIB stored with the agent in MPFS2 format.
  	It will search for the first lexicographic successor of the variable 
  	binding's name in the incoming GetNextRequest-PDU. If found, the 
  	corresponding variable binding's name and value fields in the Response 
  	pdu are set to the name and value of the located variable. If the 
  	lexicographic succesor is not found, the vlaue filed is set to
  	"endofMibView" and name field is retained as in request.
	  	
  Precondition:
	ProcessVariables() is called.
	
  Parameters:
  	rec - Pointer to SNMP MIB object information for which next node 
  		  to be found
  	
  Return Values:
	temp.V[0]- Total number of bytes copied to response packet if succesful.	
	FALSE	 - If End of MIB is reached or processing is failure.
	
  Remarks:
	None.
 ***************************************************************************/
static BYTE ProcessGetNextVar(OID_INFO* rec)
{
    WORD_VAL temp;
    BYTE putBytes;
    OID_INFO indexRec;
    BYTE *pOIDValue;
    BYTE OIDValue[OID_MAX_LEN];
    BYTE OIDLen;
    INDEX_INFO indexInfo;
    MIB_INFO varNodeInfo;
    SNMP_ID varID;
    WORD OIDValOffset;
    WORD prevOffset;
    BOOL lbNextLeaf;
    BYTE ref;
    static SNMP_VAL v;
    static BYTE varDataType;
    static BYTE indexBytes;
 
    lbNextLeaf = FALSE;
    temp.v[0] = 0;

    // Get next leaf only if this OID is a parent or a simple leaf node.
    if ( rec->nodeInfo.Flags.bIsParent ||
       (!rec->nodeInfo.Flags.bIsParent && !rec->nodeInfo.Flags.bIsSequence) )
    {	
		_GetNextLeaf:
		lbNextLeaf = TRUE;
        if ( !GetNextLeaf(rec))
			return FALSE;
	}

    // Get complete OID string from oid record.
    if ( !GetOIDStringByAddr(rec, OIDValue, &OIDLen))
	{	
        return FALSE;
	}

    // Copy complete OID string to create response packet.
    pOIDValue = OIDValue;
    OIDValOffset = _SNMPGetTxOffset();
    temp.v[0] = OIDLen;
    _SNMPSetTxOffset(OIDValOffset+1);

	//Put OID
	while( temp.v[0]-- )
    _SNMPPut(*pOIDValue++);

    // Start counting number of bytes put - OIDLen is already counted.
    temp.v[0] = OIDLen;

    varDataType = rec->dataType;
    varID = rec->id;

    // If this is a simple OID, handle it as a GetVar command.
    if(!rec->nodeInfo.Flags.bIsSequence)
    {
		// This is an addition to previously copied OID string.
        // This is index value of '0'.
        _SNMPPut(0);
        temp.v[0]++;

        // Since we added one more byte to previously copied OID
        // string, we need to update OIDLen value.
        prevOffset = _SNMPGetTxOffset();
        _SNMPSetTxOffset(OIDValOffset);
        _SNMPPut(++OIDLen);
        _SNMPSetTxOffset(prevOffset);

        // Now do Get on this simple variable.
        prevOffset = _SNMPGetTxOffset();
        putBytes = ProcessGetVar(rec, FALSE);
        if ( putBytes == 0 )
        {
            _SNMPSetTxOffset(prevOffset);
            _SNMPPut(ASN_NULL);
            _SNMPPut(0);
            putBytes = 2;
        }

        temp.v[0] += putBytes; // ProcessGetVar(rec, FALSE);

         // Return with total number of bytes copied to response packet.
        return temp.v[0];
    }

    // This is a sequence variable.
    // First of all make sure that there is a next index after this
    // index.  We also need to make sure that we do not do this foerever.
    // So make sure that this is not a repeat test.
    ref = 0;
    if ( lbNextLeaf == TRUE )
    {
         // Let application tell us whether this is a valid index or not.
        if ( !SNMPGetVar(rec->id, rec->index, &ref, &v) )
        {
             // If not, then we need to get next leaf in line.
            // Remember that we have already did this once, so that we do not
            // do this forever.
            //lbNextSequence = TRUE;

            // Reset the response packet pointer to begining of OID.
            _SNMPSetTxOffset(OIDValOffset);

            // Jump to this label within this function - Not a good SW engineering
            // practice, but this will reuse code at much lower expense.
            goto _GetNextLeaf;
        }
    }

    // Need to fetch index information from MIB and prepare complete OID+
    // index response.
     varNodeInfo.Val = rec->nodeInfo.Val;

    // In this version, only 7-bit index is supported.
    MPFSGet(hMPFS, NULL);

    indexBytes = 0;

    MPFSGet(hMPFS, &indexInfo.Val);

    // Fetch index ID.
    MPFSGet(hMPFS, &indexRec.id);

	// Fetch index data type.
    indexRec.dataType = 0;
    MPFSGet(hMPFS, (BYTE*)&indexRec.dataType);

    indexRec.index = rec->index;

    // Check with application to see if there exists next index
    // for this index id.
    if ( !lbNextLeaf && !SNMPGetNextIndex(indexRec.id, &indexRec.index) )
    {
        //lbNextSeqeuence = TRUE;
         // Reset the response packet pointer to begining of OID.
        _SNMPSetTxOffset(OIDValOffset);

        // Jump to this label.  Not a good practice, but once-in-a-while
        // it should be acceptable !
        goto _GetNextLeaf;
    }

    // Index is assumed to be dynamic, and leaf node.
    // mib2bib has already ensured that this was the case.
    indexRec.nodeInfo.Flags.bIsConstant = 0;
    indexRec.nodeInfo.Flags.bIsParent = 0;
    indexRec.nodeInfo.Flags.bIsSequence = 1;

    // Now handle this as simple GetVar.
    // Keep track of number of bytes added to OID.
    indexBytes += ProcessGetVar(&indexRec, TRUE);

    rec->index = indexRec.index;

    // These are the total number of bytes put so far as a result of this function.
    temp.v[0] += indexBytes;

    // These are the total number of bytes in OID string including index bytes.
    OIDLen += indexBytes;

    // Since we added index bytes to previously copied OID
    // string, we need to update OIDLen value.
    prevOffset = _SNMPGetTxOffset();
    _SNMPSetTxOffset(OIDValOffset);
    _SNMPPut(OIDLen);
    _SNMPSetTxOffset(prevOffset);


    // Fetch actual value itself.
    // Need to restore original OID value.
    rec->nodeInfo.Val = varNodeInfo.Val;
    rec->id = varID;
    rec->dataType = varDataType;

    temp.v[0] += ProcessGetVar(rec, FALSE);
     return temp.v[0];
}


/****************************************************************************
  Function:
	BYTE ProcessGetBulkVar(OID_INFO* rec, BYTE* oidValuePtr, 
						   BYTE* oidLenPtr,BYTE* successor)	

  Summary:
  	This routine process the SNMPv2c Get Bulk Request.
  	
  Description:
	ProcessVariables() processes the received snmp request pdu for each of
	the variable binding in the variable binding list to produce a response 
	pdu. Depending on the number of the Max_repetitions for every variable
	in the list for which Bulk information is expected, ProcessGetBulkVar()
	is executed. It searches for the next lexicographically ordered 
	successor for of the OID received in the request. For each of the 
	iterations upto max-repetitions, the next leaf node is searched in the
	MIB to that of the leaf node found in the last iteration, for the 
	corresponding variable binding.
 		  	
  Precondition:
	ProcessVariables() is called.
	
  Parameters:
  	rec 		- Pointer to SNMP MIB variable object information OID 
  	oidValuePtr	- Pointer to new node OID found in MIB 
  	oidLenPtr	- Oid length
  	successor	- 'I'th lexicographic successor to be found value
  	  	
  Return Values:
	FALSE 	  - If no lexicographic successor found
	temp.v[0] - Total number of bytes copied to response packet
	
  Remarks:
	None.
***************************************************************************/
static BYTE ProcessGetBulkVar(OID_INFO* rec, BYTE* oidValuePtr, BYTE* oidLenPtr,BYTE* successor)
{
    
    BYTE ref,putBytes,cntr;
    BYTE OIDLen;
	static BYTE varDataType;
    static BYTE indexBytes;
	SNMP_ID varID;
	BOOL lbNextLeaf;
	INDEX_INFO indexInfo;
    MIB_INFO varNodeInfo;
 	WORD OIDValOffset;
    WORD prevOffset;	
	WORD_VAL temp;
	OID_INFO indexRec;
	static SNMP_VAL v;
 
    lbNextLeaf = FALSE;
    temp.v[0] = 0;

	//Reach to the node for the expected iteration
	for(cntr=1;cntr<=*successor;cntr++)
	{
    	// Get next leaf only if this OID is a parent or a simple leaf node.
    	if((rec->nodeInfo.Flags.bIsParent)||(rec->nodeInfo.Flags.bIsSequence)||
        (!rec->nodeInfo.Flags.bIsParent && !rec->nodeInfo.Flags.bIsSequence))
        {	
		   	_GetNextLeaf:
	        lbNextLeaf = TRUE;
	        if(!GetNextLeaf(rec))
				return FALSE;
		}
	}

    // Get complete OID string from oid record.
    if(!GetOIDStringByAddr(rec, oidValuePtr, &OIDLen))
        return FALSE;

    _SNMPPut(ASN_OID);

	OIDValOffset = _SNMPGetTxOffset();
	temp.v[0] =*oidLenPtr= OIDLen;
    _SNMPSetTxOffset(OIDValOffset+1);

	//Put OID
	while( temp.v[0]-- )
	{
		_SNMPPut(*oidValuePtr);
		oidValuePtr++;
	}

	// Start counting number of bytes put - OIDLen is already counted.
	temp.v[0] =*oidLenPtr= OIDLen;

    varDataType = rec->dataType;
    varID = rec->id;

    // If this is a simple OID, handle it as a GetVar command.
    if ( !rec->nodeInfo.Flags.bIsSequence )
    {
    	
         // This is an addition to previously copied OID string.
        // This is index value of '0'.
        _SNMPPut(0);
        temp.v[0]++;

        // Since we added one more byte to previously copied OID
        // string, we need to update OIDLen value.
        prevOffset = _SNMPGetTxOffset();
        _SNMPSetTxOffset(OIDValOffset);
        _SNMPPut(++OIDLen);
        _SNMPSetTxOffset(prevOffset);

        // Now do Get on this simple variable.
        prevOffset = _SNMPGetTxOffset();
        putBytes = ProcessGetVar(rec, FALSE);
     
        temp.v[0] += putBytes; // ProcessGetVar(rec, FALSE);
   
	    // Return with total number of bytes copied to response packet.
        return temp.v[0];
    }
	
    ref = 0;
    if ( lbNextLeaf == TRUE )
    {
    	// Let application tell us whether this is a valid index or not.
        if ( !SNMPGetVar(rec->id, rec->index, &ref, &v) )
        {
             // Reset the response packet pointer to begining of OID.
            _SNMPSetTxOffset(OIDValOffset);

            // Jump to this label within this function - Not a good SW engineering
            // practice, but this will reuse code at much lower expense.
             goto _GetNextLeaf;
        }
    }

	// Need to fetch index information from MIB and prepare complete OID+
    // index response.
    varNodeInfo.Val = rec->nodeInfo.Val;

    // In this version, only 7-bit index is supported.
    MPFSGet(hMPFS, NULL);

    indexBytes = 0;

    MPFSGet(hMPFS, &indexInfo.Val);

    // Fetch index ID.
    MPFSGet(hMPFS, &indexRec.id);
    // Fetch index data type.
    indexRec.dataType = 0;
    MPFSGet(hMPFS, (BYTE*)&indexRec.dataType);

    indexRec.index = rec->index;

    // Check with application to see if there exists next index
    // for this index id.
    if ( !lbNextLeaf && !SNMPGetNextIndex(indexRec.id, &indexRec.index) )
    {	
    	 //lbNextSeqeuence = TRUE;

        // Reset the response packet pointer to begining of OID.
        _SNMPSetTxOffset(OIDValOffset);

        // Jump to this label.  Not a good practice, but once-in-a-while
        // it should be acceptable !
        
        goto _GetNextLeaf;
    }

    // Index is assumed to be dynamic, and leaf node.
    // mib2bib has already ensured that this was the case.
    indexRec.nodeInfo.Flags.bIsConstant = 0;
    indexRec.nodeInfo.Flags.bIsParent = 0;
    indexRec.nodeInfo.Flags.bIsSequence = 1;

    // Now handle this as simple GetVar.
    // Keep track of number of bytes added to OID.
    indexBytes += ProcessGetVar(&indexRec, TRUE);

    rec->index = indexRec.index;

    // These are the total number of bytes put so far as a result of this function.
    temp.v[0] += indexBytes;

    // These are the total number of bytes in OID string including index bytes.
    OIDLen += indexBytes;

    // Since we added index bytes to previously copied OID
    // string, we need to update OIDLen value.
    prevOffset = _SNMPGetTxOffset();
    _SNMPSetTxOffset(OIDValOffset);
    _SNMPPut(OIDLen);
    _SNMPSetTxOffset(prevOffset);


    // Fetch actual value itself.
    // Need to restore original OID value.
    rec->nodeInfo.Val = varNodeInfo.Val;
    rec->id = varID;
    rec->dataType = varDataType;

    temp.v[0] += ProcessGetVar(rec, FALSE);
	
	return temp.v[0];
}


/****************************************************************************
  Function:
	BYTE OIDLookup(PDU_INFO* pduDbPtr,BYTE* oid, BYTE oidLen, OID_INFO* rec)
	
  Summary:
  	To search and validate whether the requested OID is in the MIB database.
  	
  Description:
	The MIB database is stored with the agent in binary mib format.
  	This is the binary mib format:
  	<oid, nodeInfo, [id], [SiblingOffset], [DistantSibling], [dataType],
  	[dataLen], [data], [{IndexCount, <IndexType>, <Index>, ...>]}, ChildNode
	variable bind name is a dotted string of oid. Every oid is a node in the
	MIB tree and have varied information. This routine on reception of the 
	snmp request, will search for every oid in the var name. This routine 
	will return information whether the requested var name is part of the 
	MIB tree data structre of this agent or not.
	 		  	
  Precondition:
	Valid snmp request with valid OID format is received.
	
  Parameters:
  	pduDbPtr	- Pointer to received snmp  pdu elements information 
  	oid			- Pointer to the string of OID to be searched
  	oidLen		- Oid length
  	rec			- Pointer to SNMP MIB variable object information  
  	  	
  Return Values:
	TRUE	-	If the complete OID string is found in the mib
	FALSE	-   If complete OID do not match. 
				Also different erros returned are
				SNMP_END_OF_MIB_VIEW
				SNMP_NO_SUCH_NAME
				SNMP_NO_SUCH_OBJ
				SNMP_NO_SUCH_INSTANCE
  Remarks:
	This routine works for the MPFS2 mib storage format. It uses the MPFS2
	APIs to read,search and collect information from the mib database. 
***************************************************************************/
static BYTE OIDLookup(PDU_INFO* pduDbPtr,BYTE* oid, BYTE oidLen, OID_INFO* rec)
{
	
	BYTE savedOID,tempSavedOID;
	BYTE matchedCount;
	BYTE snmpVer;
	BYTE snmpReqType;
	BYTE tempLen;
	BYTE* reqOidPtr;
	BYTE comapreOidWithSibling=FALSE;

	WORD_VAL tempData;
    DWORD hNode,tempHNode;//    MPFS hNode;

	appendZeroToOID=TRUE;

	snmpVer=pduDbPtr->snmpVersion;
	snmpReqType=pduDbPtr->pduType;

    if(!SNMPStatus.Flags.bIsFileOpen )
	   return FALSE;
	
	hNode = 0;
    matchedCount = oidLen;

	tempLen=oidLen;
	reqOidPtr=oid;

    while( 1 )
    {
    
		MPFSSeek(hMPFS, hNode, MPFS_SEEK_START);

        // Remember offset of this node so that we can find its sibling
        // and child data.
        rec->hNode = MPFSTell(hMPFS); // hNode;

        // Read OID byte.
        MPFSGet(hMPFS, &savedOID);

		if(comapreOidWithSibling==FALSE)
		{
		   	tempSavedOID=savedOID;
			tempHNode=hNode;
		}

        // Read Node Info
        MPFSGet(hMPFS, &rec->nodeInfo.Val);

	    // Next byte will be node id, if this is a leaf node with variable data.
        if(rec->nodeInfo.Flags.bIsIDPresent)
	        MPFSGet(hMPFS, &rec->id);
	
        // Read sibling offset, if there is any.
        if(rec->nodeInfo.Flags.bIsSibling)
        {
            MPFSGet(hMPFS, &tempData.v[0]);
            MPFSGet(hMPFS, &tempData.v[1]);
            rec->hSibling = tempData.Val;
        }

        if ( savedOID != *reqOidPtr )
        {
        	/*if very first OID byte does not match, it may be because it is
              0, 1 or 2.  In that case declare that there is a match.
              The command processor would detect OID type and continue or reject
              this OID as a valid argument.*/
            if(matchedCount == oidLen)
				goto FoundIt;
			
			if(comapreOidWithSibling==TRUE && !rec->nodeInfo.Flags.bIsSibling)
				goto DidNotFindIt;

			if ( rec->nodeInfo.Flags.bIsSibling )
            {
 	            hNode = MPFSSeek(hMPFS, tempData.Val, MPFS_SEEK_START);
	            hNode = MPFSTell(hMPFS);
				comapreOidWithSibling=TRUE;
            }
            else
	            goto DidNotFindIt;
        }
        else
        {
	        // One more oid byte matched.
            matchedCount--;
            reqOidPtr++;

            // A node is said to be matched if last matched node is a leaf node
            // or all but last OID string is matched and last byte of OID is '0'.
            // i.e. single index.
            if ( !rec->nodeInfo.Flags.bIsParent )
            {
            	// Read and discard Distant Sibling info if there is any.
                if ( rec->nodeInfo.Flags.bIsDistantSibling )
                {	
                   	MPFSGet(hMPFS, &tempData.v[0]);
                    MPFSGet(hMPFS, &tempData.v[1]);
                    rec->hSibling = tempData.Val;
                }

		        rec->dataType = 0;
                MPFSGet(hMPFS, (BYTE*)&rec->dataType);
                rec->hData = MPFSTell(hMPFS);

				if(snmpReqType==SNMP_GET && matchedCount == 0)
				{
					appendZeroToOID=FALSE;
					goto DidNotFindIt;
                 }
				else if(snmpReqType==SNMP_GET && matchedCount == 1 && *reqOidPtr == 0x00)
				{
					appendZeroToOID=FALSE;
                 }
				else if(snmpReqType==SNMP_GET_NEXT && matchedCount == 0)
				{
					appendZeroToOID=TRUE;
					snmpReqType=pduDbPtr->pduType=SNMP_GET;
				}

                goto FoundIt;
            }
			else if(matchedCount >1 && *reqOidPtr == 0x00)
            {
             	 appendZeroToOID=FALSE;
				 goto DidNotFindIt;
			}
            else if(matchedCount == 1 && *reqOidPtr == 0x00)
	        {
	            appendZeroToOID=FALSE;

				if(rec->nodeInfo.Flags.bIsParent)
				{	
					goto DidNotFindIt;
	            }

			}
            else if(matchedCount == 0)
            {
	           	if(rec->nodeInfo.Flags.bIsParent || snmpReqType==SNMP_GET)
    			{
					appendZeroToOID=FALSE;
					
					goto DidNotFindIt;
                 }
				 else 
				 	goto FoundIt;
			}
            else
            {	
	            hNode = MPFSTell(hMPFS);
                // Try to match following child node.
                continue;
            }
        }
    }

FoundIt:

	// Convert index info from OID to regular value format.
    rec->index = savedOID;

	
	/*To Reach To The Next leaf Node */
    savedOID = *reqOidPtr;

	rec->indexLen = 1;

	// In this version, we only support 7-bit index.
	// if(((matchedCount <=1)&&( *reqOidPtr == 0x00)))
    if(((matchedCount ==1)&&( *reqOidPtr == 0x00)))
    	rec->index = 0;
	else if(matchedCount == 0)
		rec->index = 0;
	else if ( matchedCount > 1 || savedOID & 0x80 )
    {	
    	// Current instnace spans across more than 7-bit.
        rec->indexLen = 0xff;

		if(snmpReqType==SNMP_GET && snmpVer==SNMP_V1)
		{
			return SNMP_NO_SUCH_NAME;
		}
		else if(snmpReqType==SNMP_GET && snmpVer==SNMP_V2C)
		{
			if(matchedCount== oidLen) //No OBJECT IDNETIFIER Prefix match
				return SNMP_NO_SUCH_INSTANCE;
			else
				return SNMP_NO_SUCH_OBJ;
		}

		return FALSE;
    }

	return TRUE;

DidNotFindIt:

	if(snmpReqType==SNMP_GET)
	{
		if(snmpVer==SNMP_V1)
			return SNMP_NO_SUCH_NAME;

		else if(snmpVer==SNMP_V2C)
		{	
			if(matchedCount== oidLen) //No OBJECT IDNETIFIER Prefix match
				return SNMP_NO_SUCH_INSTANCE;
			else
				return SNMP_NO_SUCH_OBJ;
		}
	}
/*Amit*/	else if((snmpReqType==SNMP_GET_NEXT||snmpReqType==SNMP_V2C_GET_BULK) && snmpVer==SNMP_V2C)
//	else if(snmpReqType==SNMP_GET_NEXT&& snmpVer==SNMP_V2C)
	{
		return SNMP_END_OF_MIB_VIEW;
	}
	
	return FALSE;
}	


/****************************************************************************
  Function:
	BOOL GetNextLeaf(OID_INFO* rec)
	
  Summary:
  	Searches for the next leaf node in the MIP tree.  	

  Description:
  	This routine searches for the next leaf node from the current node.
  	The input to this function is the node from where next leaf node
  	is to be located. The next leaf node will be a silbing else distant 
  	sibling or leaf node of next branch, if any present. The input parameter
  	var pointer will be updated with the newly found leaf node OID info.
 		 		  	
  Precondition:
	ProcessGetBulkVar() else ProcessGetNextVar() is called. 
	
  Parameters:
  	rec		- Pointer to SNMP MIB variable object information  

  Return Values:
	TRUE	- If next leaf node is found.
	FALSE	- There is no next leaf node.
	
  Remarks:
	None.
***************************************************************************/
static BOOL GetNextLeaf(OID_INFO* rec)
{
    WORD_VAL temp;

    // If current node is leaf, its next sibling (near or distant) is the next leaf.
    if ( !rec->nodeInfo.Flags.bIsParent )
    {
        // Since this is a leaf node, it must have at least one distant or near
        // sibling to get next sibling.
        if(rec->nodeInfo.Flags.bIsSibling ||
           rec->nodeInfo.Flags.bIsDistantSibling )
        {
            // Reposition at sibling.
            MPFSSeek(hMPFS, rec->hSibling, MPFS_SEEK_START);

            // Fetch node related information
        }
        // There is no sibling to this leaf.  This must be the very last node on the tree.
        else
        {
			//--MPFSClose();
            return FALSE;
        }
    }

    while( 1 )
    {
        // Remember current MPFS position for this node.
       rec->hNode = MPFSTell(hMPFS);

        // Read OID byte.
        MPFSGet(hMPFS, &rec->oid);

        // Read Node Info
        MPFSGet(hMPFS, &rec->nodeInfo.Val);

        // Next byte will be node id, if this is a leaf node with variable data.
        if ( rec->nodeInfo.Flags.bIsIDPresent )
            MPFSGet(hMPFS, &rec->id);

        // Fetch sibling offset, if there is any.
        if ( rec->nodeInfo.Flags.bIsSibling ||
             rec->nodeInfo.Flags.bIsDistantSibling )
        {
            MPFSGet(hMPFS, &temp.v[0]);
            MPFSGet(hMPFS, &temp.v[1]);
            rec->hSibling = temp.Val;
        }

        // If we have not reached a leaf yet, continue fetching next child in line.
        if ( rec->nodeInfo.Flags.bIsParent )
        {
            continue;
        }

        // Fetch data type.
        rec->dataType = 0;
        MPFSGet(hMPFS, (BYTE*)&rec->dataType);

        rec->hData = MPFSTell(hMPFS);

        // Since we just found next leaf in line, it will always have zero index
        // to it.
        rec->indexLen = 1;
        rec->index = 0;

        return TRUE;
    }
    return FALSE;
}


/****************************************************************************
  Function:
	BOOL IsValidCommunity(char* community, BYTE* len)
	
  Summary:
  	Verifies for the community string datatype and the max 
  	community name and length, this agent can process.

  Description:
  	This routine populates and validates the community datatype, community
  	name and length from the received snmp request pdu. Community name is
  	used for accessing public and private memebrs of the mib.
  	 		 		  	
  Precondition:
	ProcessHeader() is called. 
	
  Parameters:
  	community -	Pointer to memory where community string will be stored.
  	len		  - Pointer to memory where comunity length gets stored.

  Return Values:
	TRUE	- If valid community received.
	FALSE	- If community is not valid.
	
  Remarks:
	None.
***************************************************************************/
static BOOL IsValidCommunity(char* community, BYTE* len)
{
    BYTE tempData;
    BYTE tempLen;

    tempData = _SNMPGet();
    if ( !IS_OCTET_STRING(tempData) )
        return FALSE;

    tempLen = _SNMPGet();
    *len    = tempLen;
    if ( tempLen > SNMP_COMMUNITY_MAX_LEN )
        return FALSE;

    while( tempLen-- )
    {
        tempData = _SNMPGet();
        *community++ = tempData;
    }
    *community = '\0';
	 return TRUE;
}


/****************************************************************************
  Function:
	BOOL IsValidInt(DWORD* val)
	
  Summary:
  	Verifies variable datatype as INT and retrieves its value.

  Description:
  	This routine populates and validates the received variable for the
  	data type as "ASN_INT" and the data length for max 4 bytes.
  	 		 		  	
  Precondition:
	ProcessHeader() or ProcessGetSetHeader() is called. 
	
  Parameters:
  	val - Pointer to memory where int var value will be stored.
 
  ReturnValues:
	TRUE	- If valid integer type and value is received.
	FALSE	- Other than integer data type and value received .
	
  Remarks:
	None.
***************************************************************************/
static BOOL IsValidInt(DWORD* val)
{
    DWORD_VAL tempData;
    DWORD_VAL tempLen;

    tempLen.Val = 0;

    // Get variable type
    if ( !IS_ASN_INT(_SNMPGet()) )
        return FALSE;

    if ( !IsValidLength(&tempLen.w[0]) )
        return FALSE;

    // Integer length of more than 32-bit is not supported.
    if ( tempLen.Val > 4 )
        return FALSE;

    tempData.Val = 0;
    while( tempLen.v[0]-- )
        tempData.v[tempLen.v[0]] = _SNMPGet();

    *val = tempData.Val;

    return TRUE;
}


/****************************************************************************
  Function:
	BOOL IsValidPDU(SNMP_ACTION* pdu)
	
  Summary:
  	Verifies for the snmp request type.

  Description:
  	This routine populates and verifies for the received snmp request 
  	pdu type. 
  	 		 		  	
  Precondition:
	ProcessHeader() is called. 
	
  Parameters:
  	val - Pointer to memory where received snmp request type is stored.
 
  Return Values:
	TRUE	- If this snmp request can be processed by the agent. 
	FALSE	- If the request can not be processed.
	
  Remarks:
	None.
***************************************************************************/
static BOOL IsValidPDU(SNMP_ACTION* pdu)
{
    BYTE tempData;
    WORD tempLen;


    // Fetch pdu data type
    tempData = _SNMPGet();
    if ( !IS_AGENT_PDU(tempData) )
        return FALSE;

    *pdu = tempData;


	/* Now fetch pdu length.  We don't need to remember pdu length.
	   Do this to proceed to next pdu element of interest*/	
    return IsValidLength(&tempLen);
}




/****************************************************************************
  Function:
	BYTE IsValidLength(WORD* len)
	
  Summary:
  	Retrieves the packet length and actual pdu length.

  Description:
	Checks current packet and returns total length value as well as 
	actual length bytes.We do not support any length byte count of more 
	than 2 i.e. total length value must not be more than 16-bit.
  	 		 		  	
  Precondition:
	None 
	
  Parameters:
  	len - Pointer to memory where actual length is stored.
 
  Return Values:
	lengthBytes	- Total length bytes are 0x80 itself plus tempData.
		
  Remarks:
	None.
***************************************************************************/
static BYTE IsValidLength(WORD *len)
{
    BYTE tempData;
    WORD_VAL tempLen;
    BYTE lengthBytes;

    // Initialize length value.
    tempLen.Val = 0;
    lengthBytes = 0;

    tempData = _SNMPGet();
    tempLen.v[0] = tempData;
    if ( tempData & 0x80 )
    {
        tempData &= 0x7F;

        // We do not support any length byte count of more than 2
        // i.e. total length value must not be more than 16-bit.
        if ( tempData > 2 )
            return FALSE;

        // Total length bytes are 0x80 itself plus tempData.
        lengthBytes = tempData + 1;

        // Get upto 2 bytes of length value.
        while( tempData-- )
            tempLen.v[tempData] = _SNMPGet();
    }
    else
        lengthBytes = 1;

    *len = tempLen.Val;

    return lengthBytes;
}


/****************************************************************************
  Function:
	BOOL IsASNNull(void)

	
  Summary:
  	Verifies the value type as ASN_NULL.

  Description:
  	For Get,Get_Next,Get_Bulk snmp reuest, the var bind the value data type 
  	should be ASN_NULL and value field must be NULL and . This routine
  	verifies the data type and value fields in the received requests.
  	The SET request, the value data type can not be ASN_NULL,
  	otherwise the snmp request is not processed.

  Precondition:
	None
	
  Parameters:
  	None
 
  Returns Values
	TRUE	- If value type is ASN_NULL and value is NULL. 
	FALSE	- If data type and value is other than ASN_NULL and NULL resp.
	
  Remarks:
	None.
***************************************************************************/
static BOOL IsASNNull(void)
{
	BYTE a;

		
    // Fetch and verify that this is NULL data type.
    /*if ( !IS_ASN_NULL(_SNMPGet()) )
        return FALSE;*/

	a=_SNMPGet();

	if (!IS_ASN_NULL(a))
			return FALSE;

    // Fetch and verify that length value is zero.
    return (_SNMPGet() == 0 );
}


/****************************************************************************
  Function:
	BOOL IsValidOID(BYTE* oid, BYTE* len)
	
  Summary:
  	Populates OID type, length and oid string from the received pdu.

  Description:
	In this routine, OID data type "ASN_OID" is verified in the received pdu.
	If the data type is matched, then only var bind is processed. OID length
	and OID is populated. The max OID length can be 15. 
  	
  Precondition:
	ProcessVariabels() is called.
	
  Parameters:
  	oid - Pointer to memory to store the received OID string
  	len	- Pointer to memory to store OID length
 
  Return Values:
	TRUE	- If value type is ASN_OID and oid length not more than 15. 
	FALSE	- Otherwise.
	
  Remarks:
	None.
***************************************************************************/
static BOOL IsValidOID(BYTE* oid, BYTE* len)
{
    DWORD_VAL tempLen;

    // Fetch and verify that this is OID.
    if ( !IS_OID(_SNMPGet()) )
        return FALSE;

    // Retrieve OID length
    if ( !IsValidLength(&tempLen.w[0]) )
        return FALSE;

    // Make sure that OID length is within our capability.
    if ( tempLen.w[0] > OID_MAX_LEN )
        return FALSE;

    *len = tempLen.v[0];

	while( tempLen.v[0]-- )
	{
       *oid++ = _SNMPGet();
	}
	*oid=0xff;
    return TRUE;
}

/****************************************************************************
  Function:
	BYTE IsValidStructure(WORD* dataLen)
	
  Summary:
  	Decode variable length structure.

  Description:
	This routine is used  to verify whether the received varbind is of type
	STRUCTURE and to find out the variable binding structure length.
  	
  Precondition:
	ProcessHeader() is called.	
	
  Parameters:
  	datalen	- Pointer to memory to store OID structure length.
 
  Return Values:
	headrbytes	- Variable binding length.
	FALSE		- If variable data structure is not type STRUCTURE. 	

  Remarks:
	None.
***************************************************************************/
static BYTE IsValidStructure(WORD* dataLen)
{
    DWORD_VAL tempLen;
    BYTE headerBytes;

    if ( !IS_STRUCTURE(_SNMPGet()) )
        return FALSE;

    // Retrieve structure length
    headerBytes = IsValidLength(&tempLen.w[0]);
    if ( !headerBytes )
        return FALSE;

    headerBytes++;

    // Since we are using UDP as our transport and UDP are not fragmented,
    // this structure length cannot be more than 1500 bytes.
    // As a result, we will only use lower WORD of length value.
    *dataLen = tempLen.w[0];

    return headerBytes;
}

/****************************************************************************
  Function:
	void _SNMPDuplexInit(UDP_SOCKET socket)
	
  Summary:
  	Prepare for full duplex transfer.

  Description:
	As we process SNMP variables, we will prepare response on-the-fly
    creating full duplex transfer. Current MAC layer does not support 
    full duplex transfer, so SNMP needs to manage its own full duplex
    connection. Prepare for full duplex transfer. Set the Tx and Rx 
    offset to start of the buffer.
  	
  Precondition:
	SNMPTask() is called.	
	
  Parameters:
	socket - An active udp socket for which tx and rx offset to be set.
 
  Returns:
	None.

  Remarks:
  	 This routine should be called for every new snmp packet received.
***************************************************************************/
static void _SNMPDuplexInit(UDP_SOCKET socket)
{
    // In full duplex transfer, transport protocol must be ready to
    // accept new transmit packet.
    while( !UDPIsPutReady(socket) ) ;

    // Initialize buffer offsets.
    SNMPRxOffset = 0;
    SNMPTxOffset = 0;
}


/****************************************************************************
  Function:
	void _SNMPPut(BYTE v)
	
  Summary:
  	Copy byte to tx buffer.

  Description:
	This function writes a single byte to the currently active UDP socket, 
	transmit buffer, while incrementing the buffer offset for the next write 
	operation.

  Precondition:
	SNMPTask() is called.	
	A active udp socket is availabe to tx from.
	
  Parameters:
	None.
 
  Returns:
	None.

  Remarks:
  	None.
***************************************************************************/
static void _SNMPPut(BYTE v)
{
    UDPSetTxBuffer(SNMPTxOffset);

    UDPPut(v);

    SNMPTxOffset++;
}

/****************************************************************************
  Function:
	BYTE _SNMPGet(void)
	
  Summary:
  	Read byte from snmp udp socket rx buffer.

  Description:
	This function reads a single byte from the currently active UDP socket, 
	receive buffer, while incrementing the buffer offset from where the next 
	byte will be read.
	
  Precondition:
	SNMPTask() is called.
	A active udp socket is available to read from.
	
  Parameters:
	None
 
  Returns:
	None.

  Remarks:
  	None.
***************************************************************************/
static BYTE _SNMPGet(void)
{
    BYTE v;

    UDPSetRxBuffer(SNMPRxOffset++);
    UDPGet(&v);
    return v;
}

#if !defined(SNMP_TRAP_DISABLED)
/****************************************************************************
  Function:
	BOOL GetOIDStringByID(SNMP_ID id, OID_INFO* info, 
						  BYTE* oidString, BYTE* len)
	
  Summary:
  	Get complete notification variable OID string from MPFS using var id.
  	
  Description:
  	This routine is called when a OID string is required to be searched
  	from MPFS using agent id. The string is saved with agent.  
  	TRAP pdu is send with this OID corresponding to the SNMP_ID used 
  	by the agent application to send the pdu.
	
  Precondition:
	SNMPNotify() is called.	
	
  Parameters:
	id			-	System ID to use identify this agent.
	info		-	Pointer to SNMP MIB variable object information
	oidString	-	Pointer to store the string of OID serached
	len			-	Oid length
 
  Return Values:
	TRUE	-	If oid string is found for the variable id in MPFS.
	FLASE	-	Otherwise.

  Remarks:
  	This function is used only when TRAP is enabled.
***************************************************************************/
static BOOL GetOIDStringByID(SNMP_ID id, OID_INFO* info, BYTE* oidString, BYTE* len)
{
    DWORD hCurrent;

    hCurrent = 0;

    while (1)
    {
    	//Read in the Mib record for the oid info
        ReadMIBRecord(hCurrent, info);

        if ( !info->nodeInfo.Flags.bIsParent )
        {
            if ( info->nodeInfo.Flags.bIsIDPresent )
            {
                if ( info->id == id )
                    return GetOIDStringByAddr(info, oidString, len);
            }

            if ( info->nodeInfo.Flags.bIsSibling ||
                 info->nodeInfo.Flags.bIsDistantSibling )
                MPFSSeek(hMPFS, info->hSibling, MPFS_SEEK_START);

            else
                break;

        }
        hCurrent = MPFSTell(hMPFS);
    }
    return FALSE;
}
#endif


/****************************************************************************
  Function:
	BOOL GetOIDStringByAddr(OID_INFO* rec, BYTE* oidString, BYTE* len)
	
  Summary:
  	Get OID string from MPFS using the node address.
  	
  Description:
  	This routine is called when a OID string is required to be searched
  	from MPFS using node address.
  	
  Precondition:
	None.
	
  Parameters:
	rec			-	Pointer to SNMP MIB variable object information
	oidString	-	Pointer to store the string of OID serached
	len			-	Oid length
 
  Return Values:
	TRUE	-	If oid string is found.
	FLASE	-	Otherwise.

  Remarks:
  	None.
***************************************************************************/
static BOOL GetOIDStringByAddr(OID_INFO* rec, BYTE* oidString, BYTE* len)
{
    DWORD hTarget;
    DWORD hCurrent;
    DWORD hNext;
    OID_INFO currentMIB;
    BYTE index;
    enum { SM_PROBE_SIBLING, SM_PROBE_CHILD } state;

    hCurrent = 0;


    hTarget = rec->hNode;//node address
    state = SM_PROBE_SIBLING;
    index = 0;

    while( 1 )
    {
        ReadMIBRecord(hCurrent, &currentMIB);

        oidString[index] = currentMIB.oid;

        if ( hTarget == hCurrent )
        {
            *len = ++index;
            return TRUE;
        }

        switch(state)
        {
        case SM_PROBE_SIBLING:
            if ( !currentMIB.nodeInfo.Flags.bIsSibling )
                state = SM_PROBE_CHILD;

            else
            {
                hNext = currentMIB.hSibling;
                MPFSSeek(hMPFS, hNext, MPFS_SEEK_START);
                hNext = MPFSTell(hMPFS);
                if ( hTarget >= hNext )
                {
                    hCurrent = hNext;
                    break;
                }
                else
                    state = SM_PROBE_CHILD;
            }

        case SM_PROBE_CHILD:
            if ( !currentMIB.nodeInfo.Flags.bIsParent )
                return FALSE;

            index++;

            hCurrent = currentMIB.hChild;
            state = SM_PROBE_SIBLING;
            break;
        }
    }
    return FALSE;
}


/****************************************************************************
  Function:
	void ReadMIBRecord(DWORD h, OID_INFO* rec)
	
  Summary:
  	Get OID string from MPFS using the node address.
  	
  Description:
  	This routine is called when a OID string is required to be searched
  	from MPFS using node address.
  	
  Precondition:
	GetOIDStringByID() or GetOIDStringByAddr() is called.
	
  Parameters:
	h		-	Node adderess whose oid is to be read.
	rec		-	Pointer to store SNMP MIB variable object information
  
  Returns:
	None.
	
  Remarks:
  	None.
***************************************************************************/
static void ReadMIBRecord(DWORD h, OID_INFO* rec)
{
    MIB_INFO nodeInfo;
    WORD_VAL tempVal;

    MPFSSeek(hMPFS, h, MPFS_SEEK_START);

    // Remember location of this record.
    rec->hNode = h;

    // Read OID
    MPFSGet(hMPFS, &rec->oid);

    // Read nodeInfo
    MPFSGet(hMPFS, &rec->nodeInfo.Val);
    nodeInfo = rec->nodeInfo;

    // Read id, if there is any: Only leaf node with dynamic data will have id.
    if ( nodeInfo.Flags.bIsIDPresent )
        MPFSGet(hMPFS, &rec->id);

    // Read Sibling offset if there is any - any node may have sibling
    if ( nodeInfo.Flags.bIsSibling )
    {
        MPFSGet(hMPFS, &tempVal.v[0]);
        MPFSGet(hMPFS, &tempVal.v[1]);
        rec->hSibling = tempVal.Val;
    }

    // All rest of the parameters are applicable to leaf node only.
    if ( nodeInfo.Flags.bIsParent )
        rec->hChild = MPFSTell(hMPFS);
    else
    {
        if ( nodeInfo.Flags.bIsDistantSibling )
        {
            // Read Distant Sibling if there is any - only leaf node will have distant sibling
            MPFSGet(hMPFS, &tempVal.v[0]);
            MPFSGet(hMPFS, &tempVal.v[1]);
            rec->hSibling = tempVal.Val;
        }

        // Save data type for this node.
        rec->dataType = 0;
        MPFSGet(hMPFS, (BYTE*)&rec->dataType);

        rec->hData = MPFSTell(hMPFS);

    }

}

static BOOL GetDataTypeInfo(DATA_TYPE dataType, DATA_TYPE_INFO *info )
{
    if ( dataType >= DATA_TYPE_UNKNOWN )
        return FALSE;

    info->asnType   = dataTypeTable[dataType].asnType;
    info->asnLen    = dataTypeTable[dataType].asnLen;

    return TRUE;
}


/****************************************************************************
  Function:
	BYTE ProcessSetVar(PDU_INFO* pduDbPtr,OID_INFO* rec, 
					   SNMP_ERR_STATUS* errorStatus)
	
  Summary:
  	Processes snmp Set request pdu.
  	
  Description:
  	This routine processes the received snmp set request pdu for the 
  	variable binding in the request and also creates the response pdu.
  	
  Precondition:
	ProcessVariables() is called.
	
  Parameters:
    pduDbPtr	-   Received pdu information database pointer
    rec		  	-   Pointer to SNMP MIB variable object information
    errorStatus -   Pointer to update error status info

  Return Values:
	copiedBytes	- Number of bytes copied by this routine to the 
				  snmp pdu tx buffer.

  Remarks:
  	None.
***************************************************************************/
static BYTE ProcessSetVar(PDU_INFO* pduDbPtr,OID_INFO* rec, SNMP_ERR_STATUS* errorStatus)
{
	BYTE ref;
	BYTE temp;
	BYTE dataType;
	BYTE dataLen;
	BYTE copiedBytes;
    SNMP_ERR_STATUS errorCode;
    DATA_TYPE_INFO actualDataTypeInfo;
    SNMP_VAL dataValue;
    
    // Start with no error.
    errorCode = SNMP_NO_ERR;
    copiedBytes = 0;

    // Non-leaf, Constant and ReadOnly node cannot be modified
    if(rec->nodeInfo.Flags.bIsParent   ||
       rec->nodeInfo.Flags.bIsConstant ||
       !rec->nodeInfo.Flags.bIsEditable )
    {	
        if(pduDbPtr->snmpVersion == SNMP_V1)
       		errorCode = SNMP_NO_SUCH_NAME;
		else if (pduDbPtr->snmpVersion == SNMP_V2C)
			errorCode = SNMP_NOT_WRITABLE;
	}

    dataType = _SNMPGet();
    _SNMPPut(dataType);
    copiedBytes++;

    // Get data type for this node.
    //actualDataType = MPFSGet();
    if ( !GetDataTypeInfo(rec->dataType, &actualDataTypeInfo) )
	{
		if(pduDbPtr->snmpVersion == SNMP_V1)
        	errorCode = SNMP_BAD_VALUE;
		else if (pduDbPtr->snmpVersion == SNMP_V2C)
			errorCode = SNMP_WRONG_TYPE;
	}

    // Make sure that received data type is same as what is declared
    // for this node.
    if ( dataType != actualDataTypeInfo.asnType )
	{	
        if(pduDbPtr->snmpVersion == SNMP_V1)
        	errorCode = SNMP_BAD_VALUE;
		else if (pduDbPtr->snmpVersion == SNMP_V2C)
			errorCode = SNMP_WRONG_TYPE;
	}

    // Make sure that received data length is within our capability.
    dataLen = _SNMPGet();
    _SNMPPut(dataLen);
    copiedBytes++;

    // Only max data length of 127 is supported.
    if ( dataLen > 0x7f )
	{
		if(pduDbPtr->snmpVersion == SNMP_V1)
        	errorCode = SNMP_BAD_VALUE;
		else if (pduDbPtr->snmpVersion == SNMP_V2C)
			errorCode = SNMP_WRONG_LENGTH;
	}

	
    // If this is a Simple variable and given index is other than '0',
    // it is considered bad value
    if ( !rec->nodeInfo.Flags.bIsSequence && rec->index != 0x00 ){
        errorCode = SNMP_NO_SUCH_NAME;}

    dataValue.dword = 0;
    ref = 0;

    // If data length is within 4 bytes, fetch all at once and pass it
    // to application.
    if ( actualDataTypeInfo.asnLen != 0xff )
    {
        // According to mib def., this data length for this data type/
        // must be less or equal to 4, if not, we don't know what this
        // is.
        if ( dataLen <= 4 )
        {
            // Now that we have verified data length, fetch them all
            // at once and save it in correct place.
            //dataLen--;

            while( dataLen-- )
            {
                temp = _SNMPGet();
                dataValue.v[dataLen] = temp;

                // Copy same byte back to create response...
                _SNMPPut(temp);
                copiedBytes++;
            }


            // Pass it to application.
            if ( errorCode == SNMP_NO_ERR )
            {
                if(!SNMPSetVar(rec->id, rec->index, ref, dataValue))
				{
                   	if(pduDbPtr->snmpVersion == SNMP_V1)
        				errorCode = SNMP_BAD_VALUE;
					else if (pduDbPtr->snmpVersion == SNMP_V2C)
						errorCode = SNMP_WRONG_VALUE;
				}
            }
        }
        else
		{
            if(pduDbPtr->snmpVersion == SNMP_V1)
        		errorCode = SNMP_BAD_VALUE;
			else if (pduDbPtr->snmpVersion == SNMP_V2C)
			{	if( rec->nodeInfo.Flags.bIsConstant)
					errorCode = SNMP_NOT_WRITABLE;
				else
					errorCode = SNMP_WRONG_LENGTH;
			}
		}	
    }
    else
    {
        // This is a multi-byte Set operation.
        // Check with application to see if this many bytes can be
        // written to current variable.
        if ( !SNMPIsValidSetLen(rec->id, dataLen) )
		{
            if(pduDbPtr->snmpVersion == SNMP_V1)
        		errorCode = SNMP_BAD_VALUE;
			else if (pduDbPtr->snmpVersion == SNMP_V2C)
			{
				if( rec->nodeInfo.Flags.bIsConstant)
					errorCode = SNMP_NOT_WRITABLE;
				else
					errorCode = SNMP_WRONG_LENGTH;
			}
		}
        // Even though there may have been error processing this
        // variable, we still need to reply with original data
        // so at least copy those bytes.
        while( dataLen-- )
        {
            dataValue.byte = _SNMPGet();

            _SNMPPut(dataValue.byte);
            copiedBytes++;

            // Ask applicaton to set this variable only if there was
            // no previous error.
            if ( errorCode == SNMP_NO_ERR )
            {
                if ( !SNMPSetVar(rec->id, rec->index, ref++, dataValue) )
				{
                    errorCode = SNMP_BAD_VALUE;
				}
            }
        }
        // Let application know about end of data transfer
        if ( errorCode == SNMP_NO_ERR )
		{
            SNMPSetVar(rec->id, rec->index, (WORD)SNMP_END_OF_VAR, dataValue);
		}
    }
    *errorStatus = errorCode;

    return copiedBytes;
}


/****************************************************************************
  Function:
	BYTE ProcessGetVar(OID_INFO* rec, BOOL bAsOID)
	
  Summary:
  	Processes snmp Get request pdu.
  	
  Description:
  	This routine processes the received snmp Get request pdu for the 
  	variable binding in the request and also creates the response pdu.
  	
  Precondition:
	ProcessVariables() is called.
	
  Parameters:
    rec		 -   Pointer to SNMP MIB variable object information
    bAsOID	 -   Oid flag.

  Return Values:
	varLen	- Number of bytes put in response tx pdu		
	FALSE	- If any of the elements of the request pdu validation fails.
	
  Remarks:
  	None.
***************************************************************************/
static BYTE ProcessGetVar(OID_INFO* rec, BOOL bAsOID)
{
    BYTE ref;
    BYTE temp;
    BYTE varLen;
    BYTE dataType;
    WORD offset;
    WORD prevOffset;
    SNMP_VAL v;
    DATA_TYPE_INFO dataTypeInfo;

	offset = 0;	// Suppress C30 warning: 'offset' may be used uninitialized in this function
    v.dword   = 0;

    // Non-leaf node does not contain any data.
    if ( rec->nodeInfo.Flags.bIsParent )
        return FALSE;

    // If current OID is Simple variable and index is other than .0
    // we don't Get this variable.
    if ( !rec->nodeInfo.Flags.bIsSequence )
    {
        // index of other than '0' is not invalid.
        if ( rec->index > 0 )
            return FALSE;
    }

    dataType = rec->dataType;
    if ( !GetDataTypeInfo(dataType, &dataTypeInfo) )
        return FALSE;

    if ( !bAsOID )
    {
        _SNMPPut(dataTypeInfo.asnType);

        offset = SNMPTxOffset;
        _SNMPPut(dataTypeInfo.asnLen);
    }

    if ( rec->nodeInfo.Flags.bIsConstant )
    {
        BYTE c;
        MPFSSeek(hMPFS, rec->hData, MPFS_SEEK_START);

        MPFSGet(hMPFS, &varLen);
        temp = varLen;
        while( temp-- )
	    {
	        MPFSGet(hMPFS, &c);
            _SNMPPut(c);
        }
    }
    else
    {
        ref = SNMP_START_OF_VAR;
        v.dword = 0;
        varLen = 0;

        do
        {
            if ( SNMPGetVar(rec->id, rec->index, &ref, &v) )
            {
                if ( dataTypeInfo.asnLen != 0xff )
                {
                    varLen = dataTypeInfo.asnLen;

                    while( dataTypeInfo.asnLen )
                        _SNMPPut(v.v[--dataTypeInfo.asnLen]);

                    break;
                }
                else
                {
                    varLen++;
                    _SNMPPut(v.v[0]);
                }
            }
            else
                return FALSE;

        } while( ref != SNMP_END_OF_VAR );
    }

    if ( !bAsOID )
    {
         prevOffset = _SNMPGetTxOffset();

        _SNMPSetTxOffset(offset);
        _SNMPPut(varLen);

        _SNMPSetTxOffset(prevOffset);

        varLen++;
        varLen++;
    }

    return varLen;
}


/****************************************************************************
  Function:
	void SetErrorStatus(WORD errorStatusOffset,
                           WORD errorIndexOffset,
                           SNMP_ERR_STATUS errorStatus,
                           BYTE errorIndex)
  Summary:
  	Set snmp error status in the response pdu. 
  	
  Description:
  	This routine processes the received snmp Get request pdu for the 
  	variable binding in the request and also creates the response pdu.
  	
  Precondition:
	ProcessVariables() is called.	
	
  Parameters:
    errorStatusOffset - Offset to update error status in Response Tx pdu 	
    errorIndexOffset  - Offset to update error index
    errorStatus		  - Snmp process error to be updated in response.	
    errorIndex		  - Index of the request varbind in the var bind list 
    					for which error status is to be updated. 					
    
  Returns:
	None.
	
  Remarks:
  	None.
***************************************************************************/
static void SetErrorStatus(WORD errorStatusOffset,
                           WORD errorIndexOffset,
                           SNMP_ERR_STATUS errorStatus,
                           BYTE errorIndex)
{
    WORD prevOffset;

    prevOffset = _SNMPGetTxOffset();

    _SNMPSetTxOffset(errorStatusOffset);
    _SNMPPut((BYTE)errorStatus);

    _SNMPSetTxOffset(errorIndexOffset);
    _SNMPPut(errorIndex);

    _SNMPSetTxOffset(prevOffset);
}


/****************************************************************************
  Function:
	BYTE FindOIDsInRequest(WORD pdulen)
	
  Summary:
  	Finds number of varbinds in the varbind list received in a pdu.
  	
  Description:
  	This routine is used to find the number of OIDs requested in the received
  	snmp pdu.   	
  	
  Precondition	:
	ProcessVariables() is called.	
		
  Parameters:
	pdulen		-	Length of snmp pdu request received. 
    
  Return Values:
	varCount	-	Number of OIDs found in a pdu request. 
	
  Remarks:
  	None.
***************************************************************************/
static BYTE FindOIDsInRequest(WORD pdulen)
{
BYTE varCount=0;
WORD prevUDPRxOffset;
WORD varBindLen;
WORD snmpPduLen;
 	
	snmpPduLen=pdulen;

	prevUDPRxOffset=SNMPRxOffset;

	while(snmpPduLen)
	{
		
		if(!IsValidStructure(&varBindLen))
			return FALSE;

		SNMPRxOffset=SNMPRxOffset+varBindLen;
		varCount++;
		snmpPduLen=snmpPduLen
					-1 //1 byte for STRUCTURE identifier
					-1//1 byte for varbind length 
					-varBindLen;
	}

	SNMPRxOffset=prevUDPRxOffset;

	return varCount;
}

/****************************************************************************
  Function:
	BOOL SNMPCheckIfPvtMibObjRequested(BYTE* OIDValuePtr)
	
  Summary:
  	To find whether requested OID is only for private access.
  	
  Description:
  	This routine is used to find whether requested object belongs
  	to the private object group of the mib of agent. If yes, then
  	that mib object can be accessed only with private community 
  	(supported in SNMPv2c). 
  	
  Precondition	:
	ProcessVariables() is called.	
		
  Parameters:
	OIDValuePtr	-	Pointer to memory stored with received OID.
    
  Return Values:
	TRUE	-	If the requested object is of private branch of the mib.
	FLASE	-	If the requested object is publically accessible.
	
  Remarks:
  	None.
***************************************************************************/
static BOOL SNMPCheckIfPvtMibObjRequested(BYTE* OIDValuePtr)
{
	BYTE cnt=0;
	BYTE pvtObjIdentifier[4]={0x2b,0x06/*dod*/,0x01/*internet*/,0x04/*private*/};

	while(cnt<4)
	{
		//check whether requested oid is for pvt obj
		if(pvtObjIdentifier[cnt]== OIDValuePtr[cnt])
		{
			cnt++;
		}
		else
		{
			cnt=0;
			return FALSE;
		}
		if(cnt == 0x04)
			return TRUE;
	}
	return FALSE;

}


#endif

#endif //#if defined(STACK_USE_SNMP_SERVER)
