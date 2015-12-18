#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-Default.mk)" "nbproject/Makefile-local-Default.mk"
include nbproject/Makefile-local-Default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/tcpip.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/tcpip.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED="../../Microchip/TCPIP Stack/TFTPc.c" "../../Microchip/TCPIP Stack/Announce.c" "../../Microchip/TCPIP Stack/ARP.c" "../../Microchip/TCPIP Stack/Delay.c" "../../Microchip/TCPIP Stack/DHCP.c" "../../Microchip/TCPIP Stack/DHCPs.c" "../../Microchip/TCPIP Stack/DNS.c" "../../Microchip/TCPIP Stack/DynDNS.c" "../../Microchip/TCPIP Stack/ENC28J60.c" "../../Microchip/TCPIP Stack/ETH97J60.c" "../../Microchip/TCPIP Stack/Hashes.c" "../../Microchip/TCPIP Stack/Helpers.c" "../../Microchip/TCPIP Stack/HTTP2.c" "../../Microchip/TCPIP Stack/ICMP.c" "../../Microchip/TCPIP Stack/IP.c" "../../Microchip/TCPIP Stack/MPFS2.c" "../../Microchip/TCPIP Stack/NBNS.c" "../../Microchip/TCPIP Stack/Reboot.c" "../../Microchip/TCPIP Stack/SMTP.c" "../../Microchip/TCPIP Stack/SNTP.c" "../../Microchip/TCPIP Stack/SPIEEPROM.c" "../../Microchip/TCPIP Stack/SPIFlash.c" "../../Microchip/TCPIP Stack/SPIRAM.c" "../../Microchip/TCPIP Stack/StackTsk.c" "../../Microchip/TCPIP Stack/TCP.c" "../../Microchip/TCPIP Stack/Telnet.c" "../../Microchip/TCPIP Stack/Tick.c" "../../Microchip/TCPIP Stack/UART2TCPBridge.c" "../../Microchip/TCPIP Stack/UART.c" "../../Microchip/TCPIP Stack/UDP.c" "../../Microchip/TCPIP Stack/BerkeleyAPI.c" "../../Microchip/TCPIP Stack/ENCX24J600.c" "../../Microchip/TCPIP Stack/FTP.c" "../../Microchip/TCPIP Stack/HTTP.c" "../../Microchip/TCPIP Stack/Random.c" "../../Microchip/TCPIP Stack/RSA.c" "../../Microchip/TCPIP Stack/SSL.c" "../../Microchip/TCPIP Stack/SNMP.c" ../MainDemo.c ../CustomHTTPApp.c ../LCDBlocking.c ../ClientSocket.c ../ServerSocket.c ../MPFSImg2.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1295770447/TFTPc.o ${OBJECTDIR}/_ext/1295770447/Announce.o ${OBJECTDIR}/_ext/1295770447/ARP.o ${OBJECTDIR}/_ext/1295770447/Delay.o ${OBJECTDIR}/_ext/1295770447/DHCP.o ${OBJECTDIR}/_ext/1295770447/DHCPs.o ${OBJECTDIR}/_ext/1295770447/DNS.o ${OBJECTDIR}/_ext/1295770447/DynDNS.o ${OBJECTDIR}/_ext/1295770447/ENC28J60.o ${OBJECTDIR}/_ext/1295770447/ETH97J60.o ${OBJECTDIR}/_ext/1295770447/Hashes.o ${OBJECTDIR}/_ext/1295770447/Helpers.o ${OBJECTDIR}/_ext/1295770447/HTTP2.o ${OBJECTDIR}/_ext/1295770447/ICMP.o ${OBJECTDIR}/_ext/1295770447/IP.o ${OBJECTDIR}/_ext/1295770447/MPFS2.o ${OBJECTDIR}/_ext/1295770447/NBNS.o ${OBJECTDIR}/_ext/1295770447/Reboot.o ${OBJECTDIR}/_ext/1295770447/SMTP.o ${OBJECTDIR}/_ext/1295770447/SNTP.o ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o ${OBJECTDIR}/_ext/1295770447/SPIFlash.o ${OBJECTDIR}/_ext/1295770447/SPIRAM.o ${OBJECTDIR}/_ext/1295770447/StackTsk.o ${OBJECTDIR}/_ext/1295770447/TCP.o ${OBJECTDIR}/_ext/1295770447/Telnet.o ${OBJECTDIR}/_ext/1295770447/Tick.o ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.o ${OBJECTDIR}/_ext/1295770447/UART.o ${OBJECTDIR}/_ext/1295770447/UDP.o ${OBJECTDIR}/_ext/1295770447/BerkeleyAPI.o ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o ${OBJECTDIR}/_ext/1295770447/FTP.o ${OBJECTDIR}/_ext/1295770447/HTTP.o ${OBJECTDIR}/_ext/1295770447/Random.o ${OBJECTDIR}/_ext/1295770447/RSA.o ${OBJECTDIR}/_ext/1295770447/SSL.o ${OBJECTDIR}/_ext/1295770447/SNMP.o ${OBJECTDIR}/_ext/1472/MainDemo.o ${OBJECTDIR}/_ext/1472/CustomHTTPApp.o ${OBJECTDIR}/_ext/1472/LCDBlocking.o ${OBJECTDIR}/_ext/1472/ClientSocket.o ${OBJECTDIR}/_ext/1472/ServerSocket.o ${OBJECTDIR}/_ext/1472/MPFSImg2.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1295770447/TFTPc.o.d ${OBJECTDIR}/_ext/1295770447/Announce.o.d ${OBJECTDIR}/_ext/1295770447/ARP.o.d ${OBJECTDIR}/_ext/1295770447/Delay.o.d ${OBJECTDIR}/_ext/1295770447/DHCP.o.d ${OBJECTDIR}/_ext/1295770447/DHCPs.o.d ${OBJECTDIR}/_ext/1295770447/DNS.o.d ${OBJECTDIR}/_ext/1295770447/DynDNS.o.d ${OBJECTDIR}/_ext/1295770447/ENC28J60.o.d ${OBJECTDIR}/_ext/1295770447/ETH97J60.o.d ${OBJECTDIR}/_ext/1295770447/Hashes.o.d ${OBJECTDIR}/_ext/1295770447/Helpers.o.d ${OBJECTDIR}/_ext/1295770447/HTTP2.o.d ${OBJECTDIR}/_ext/1295770447/ICMP.o.d ${OBJECTDIR}/_ext/1295770447/IP.o.d ${OBJECTDIR}/_ext/1295770447/MPFS2.o.d ${OBJECTDIR}/_ext/1295770447/NBNS.o.d ${OBJECTDIR}/_ext/1295770447/Reboot.o.d ${OBJECTDIR}/_ext/1295770447/SMTP.o.d ${OBJECTDIR}/_ext/1295770447/SNTP.o.d ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o.d ${OBJECTDIR}/_ext/1295770447/SPIFlash.o.d ${OBJECTDIR}/_ext/1295770447/SPIRAM.o.d ${OBJECTDIR}/_ext/1295770447/StackTsk.o.d ${OBJECTDIR}/_ext/1295770447/TCP.o.d ${OBJECTDIR}/_ext/1295770447/Telnet.o.d ${OBJECTDIR}/_ext/1295770447/Tick.o.d ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.o.d ${OBJECTDIR}/_ext/1295770447/UART.o.d ${OBJECTDIR}/_ext/1295770447/UDP.o.d ${OBJECTDIR}/_ext/1295770447/BerkeleyAPI.o.d ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o.d ${OBJECTDIR}/_ext/1295770447/FTP.o.d ${OBJECTDIR}/_ext/1295770447/HTTP.o.d ${OBJECTDIR}/_ext/1295770447/Random.o.d ${OBJECTDIR}/_ext/1295770447/RSA.o.d ${OBJECTDIR}/_ext/1295770447/SSL.o.d ${OBJECTDIR}/_ext/1295770447/SNMP.o.d ${OBJECTDIR}/_ext/1472/MainDemo.o.d ${OBJECTDIR}/_ext/1472/CustomHTTPApp.o.d ${OBJECTDIR}/_ext/1472/LCDBlocking.o.d ${OBJECTDIR}/_ext/1472/ClientSocket.o.d ${OBJECTDIR}/_ext/1472/ServerSocket.o.d ${OBJECTDIR}/_ext/1472/MPFSImg2.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1295770447/TFTPc.o ${OBJECTDIR}/_ext/1295770447/Announce.o ${OBJECTDIR}/_ext/1295770447/ARP.o ${OBJECTDIR}/_ext/1295770447/Delay.o ${OBJECTDIR}/_ext/1295770447/DHCP.o ${OBJECTDIR}/_ext/1295770447/DHCPs.o ${OBJECTDIR}/_ext/1295770447/DNS.o ${OBJECTDIR}/_ext/1295770447/DynDNS.o ${OBJECTDIR}/_ext/1295770447/ENC28J60.o ${OBJECTDIR}/_ext/1295770447/ETH97J60.o ${OBJECTDIR}/_ext/1295770447/Hashes.o ${OBJECTDIR}/_ext/1295770447/Helpers.o ${OBJECTDIR}/_ext/1295770447/HTTP2.o ${OBJECTDIR}/_ext/1295770447/ICMP.o ${OBJECTDIR}/_ext/1295770447/IP.o ${OBJECTDIR}/_ext/1295770447/MPFS2.o ${OBJECTDIR}/_ext/1295770447/NBNS.o ${OBJECTDIR}/_ext/1295770447/Reboot.o ${OBJECTDIR}/_ext/1295770447/SMTP.o ${OBJECTDIR}/_ext/1295770447/SNTP.o ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o ${OBJECTDIR}/_ext/1295770447/SPIFlash.o ${OBJECTDIR}/_ext/1295770447/SPIRAM.o ${OBJECTDIR}/_ext/1295770447/StackTsk.o ${OBJECTDIR}/_ext/1295770447/TCP.o ${OBJECTDIR}/_ext/1295770447/Telnet.o ${OBJECTDIR}/_ext/1295770447/Tick.o ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.o ${OBJECTDIR}/_ext/1295770447/UART.o ${OBJECTDIR}/_ext/1295770447/UDP.o ${OBJECTDIR}/_ext/1295770447/BerkeleyAPI.o ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o ${OBJECTDIR}/_ext/1295770447/FTP.o ${OBJECTDIR}/_ext/1295770447/HTTP.o ${OBJECTDIR}/_ext/1295770447/Random.o ${OBJECTDIR}/_ext/1295770447/RSA.o ${OBJECTDIR}/_ext/1295770447/SSL.o ${OBJECTDIR}/_ext/1295770447/SNMP.o ${OBJECTDIR}/_ext/1472/MainDemo.o ${OBJECTDIR}/_ext/1472/CustomHTTPApp.o ${OBJECTDIR}/_ext/1472/LCDBlocking.o ${OBJECTDIR}/_ext/1472/ClientSocket.o ${OBJECTDIR}/_ext/1472/ServerSocket.o ${OBJECTDIR}/_ext/1472/MPFSImg2.o

# Source Files
SOURCEFILES=../../Microchip/TCPIP Stack/TFTPc.c ../../Microchip/TCPIP Stack/Announce.c ../../Microchip/TCPIP Stack/ARP.c ../../Microchip/TCPIP Stack/Delay.c ../../Microchip/TCPIP Stack/DHCP.c ../../Microchip/TCPIP Stack/DHCPs.c ../../Microchip/TCPIP Stack/DNS.c ../../Microchip/TCPIP Stack/DynDNS.c ../../Microchip/TCPIP Stack/ENC28J60.c ../../Microchip/TCPIP Stack/ETH97J60.c ../../Microchip/TCPIP Stack/Hashes.c ../../Microchip/TCPIP Stack/Helpers.c ../../Microchip/TCPIP Stack/HTTP2.c ../../Microchip/TCPIP Stack/ICMP.c ../../Microchip/TCPIP Stack/IP.c ../../Microchip/TCPIP Stack/MPFS2.c ../../Microchip/TCPIP Stack/NBNS.c ../../Microchip/TCPIP Stack/Reboot.c ../../Microchip/TCPIP Stack/SMTP.c ../../Microchip/TCPIP Stack/SNTP.c ../../Microchip/TCPIP Stack/SPIEEPROM.c ../../Microchip/TCPIP Stack/SPIFlash.c ../../Microchip/TCPIP Stack/SPIRAM.c ../../Microchip/TCPIP Stack/StackTsk.c ../../Microchip/TCPIP Stack/TCP.c ../../Microchip/TCPIP Stack/Telnet.c ../../Microchip/TCPIP Stack/Tick.c ../../Microchip/TCPIP Stack/UART2TCPBridge.c ../../Microchip/TCPIP Stack/UART.c ../../Microchip/TCPIP Stack/UDP.c ../../Microchip/TCPIP Stack/BerkeleyAPI.c ../../Microchip/TCPIP Stack/ENCX24J600.c ../../Microchip/TCPIP Stack/FTP.c ../../Microchip/TCPIP Stack/HTTP.c ../../Microchip/TCPIP Stack/Random.c ../../Microchip/TCPIP Stack/RSA.c ../../Microchip/TCPIP Stack/SSL.c ../../Microchip/TCPIP Stack/SNMP.c ../MainDemo.c ../CustomHTTPApp.c ../LCDBlocking.c ../ClientSocket.c ../ServerSocket.c ../MPFSImg2.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-Default.mk dist/${CND_CONF}/${IMAGE_TYPE}/tcpip.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F452
MP_PROCESSOR_OPTION_LD=18f452
MP_LINKER_DEBUG_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1295770447/TFTPc.o: ../../Microchip/TCPIP\ Stack/TFTPc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TFTPc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TFTPc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/TFTPc.o   "../../Microchip/TCPIP Stack/TFTPc.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/TFTPc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/TFTPc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/Announce.o: ../../Microchip/TCPIP\ Stack/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Announce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/Announce.o   "../../Microchip/TCPIP Stack/Announce.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/Announce.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/ARP.o: ../../Microchip/TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ARP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ARP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/ARP.o   "../../Microchip/TCPIP Stack/ARP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/ARP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/Delay.o: ../../Microchip/TCPIP\ Stack/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/Delay.o   "../../Microchip/TCPIP Stack/Delay.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/Delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/DHCP.o: ../../Microchip/TCPIP\ Stack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/DHCP.o   "../../Microchip/TCPIP Stack/DHCP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/DHCP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DHCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/DHCPs.o: ../../Microchip/TCPIP\ Stack/DHCPs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCPs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCPs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/DHCPs.o   "../../Microchip/TCPIP Stack/DHCPs.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/DHCPs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DHCPs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/DNS.o: ../../Microchip/TCPIP\ Stack/DNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DNS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/DNS.o   "../../Microchip/TCPIP Stack/DNS.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/DNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/DynDNS.o: ../../Microchip/TCPIP\ Stack/DynDNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DynDNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DynDNS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/DynDNS.o   "../../Microchip/TCPIP Stack/DynDNS.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/DynDNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DynDNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/ENC28J60.o: ../../Microchip/TCPIP\ Stack/ENC28J60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ENC28J60.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ENC28J60.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/ENC28J60.o   "../../Microchip/TCPIP Stack/ENC28J60.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/ENC28J60.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ENC28J60.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/ETH97J60.o: ../../Microchip/TCPIP\ Stack/ETH97J60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETH97J60.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETH97J60.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/ETH97J60.o   "../../Microchip/TCPIP Stack/ETH97J60.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/ETH97J60.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ETH97J60.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/Hashes.o: ../../Microchip/TCPIP\ Stack/Hashes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Hashes.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Hashes.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/Hashes.o   "../../Microchip/TCPIP Stack/Hashes.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/Hashes.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Hashes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/Helpers.o: ../../Microchip/TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Helpers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/Helpers.o   "../../Microchip/TCPIP Stack/Helpers.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/Helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/HTTP2.o: ../../Microchip/TCPIP\ Stack/HTTP2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/HTTP2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/HTTP2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/HTTP2.o   "../../Microchip/TCPIP Stack/HTTP2.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/HTTP2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/HTTP2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/ICMP.o: ../../Microchip/TCPIP\ Stack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ICMP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ICMP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/ICMP.o   "../../Microchip/TCPIP Stack/ICMP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/ICMP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ICMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/IP.o: ../../Microchip/TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/IP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/IP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/IP.o   "../../Microchip/TCPIP Stack/IP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/IP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/MPFS2.o: ../../Microchip/TCPIP\ Stack/MPFS2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/MPFS2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/MPFS2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/MPFS2.o   "../../Microchip/TCPIP Stack/MPFS2.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/MPFS2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/MPFS2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/NBNS.o: ../../Microchip/TCPIP\ Stack/NBNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/NBNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/NBNS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/NBNS.o   "../../Microchip/TCPIP Stack/NBNS.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/NBNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/NBNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/Reboot.o: ../../Microchip/TCPIP\ Stack/Reboot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Reboot.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Reboot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/Reboot.o   "../../Microchip/TCPIP Stack/Reboot.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/Reboot.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Reboot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/SMTP.o: ../../Microchip/TCPIP\ Stack/SMTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SMTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SMTP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/SMTP.o   "../../Microchip/TCPIP Stack/SMTP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/SMTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SMTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/SNTP.o: ../../Microchip/TCPIP\ Stack/SNTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNTP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/SNTP.o   "../../Microchip/TCPIP Stack/SNTP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/SNTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SNTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o: ../../Microchip/TCPIP\ Stack/SPIEEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o   "../../Microchip/TCPIP Stack/SPIEEPROM.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/SPIFlash.o: ../../Microchip/TCPIP\ Stack/SPIFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIFlash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIFlash.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/SPIFlash.o   "../../Microchip/TCPIP Stack/SPIFlash.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/SPIFlash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SPIFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/SPIRAM.o: ../../Microchip/TCPIP\ Stack/SPIRAM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIRAM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIRAM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/SPIRAM.o   "../../Microchip/TCPIP Stack/SPIRAM.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/SPIRAM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SPIRAM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/StackTsk.o: ../../Microchip/TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/StackTsk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/StackTsk.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/StackTsk.o   "../../Microchip/TCPIP Stack/StackTsk.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/StackTsk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/StackTsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/TCP.o: ../../Microchip/TCPIP\ Stack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TCP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/TCP.o   "../../Microchip/TCPIP Stack/TCP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/TCP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/TCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/Telnet.o: ../../Microchip/TCPIP\ Stack/Telnet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Telnet.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Telnet.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/Telnet.o   "../../Microchip/TCPIP Stack/Telnet.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/Telnet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Telnet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/Tick.o: ../../Microchip/TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Tick.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/Tick.o   "../../Microchip/TCPIP Stack/Tick.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.o: ../../Microchip/TCPIP\ Stack/UART2TCPBridge.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.o   "../../Microchip/TCPIP Stack/UART2TCPBridge.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/UART.o: ../../Microchip/TCPIP\ Stack/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/UART.o   "../../Microchip/TCPIP Stack/UART.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/UART.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/UDP.o: ../../Microchip/TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UDP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UDP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/UDP.o   "../../Microchip/TCPIP Stack/UDP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/UDP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/BerkeleyAPI.o: ../../Microchip/TCPIP\ Stack/BerkeleyAPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/BerkeleyAPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/BerkeleyAPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/BerkeleyAPI.o   "../../Microchip/TCPIP Stack/BerkeleyAPI.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/BerkeleyAPI.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/BerkeleyAPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/ENCX24J600.o: ../../Microchip/TCPIP\ Stack/ENCX24J600.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o   "../../Microchip/TCPIP Stack/ENCX24J600.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ENCX24J600.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/FTP.o: ../../Microchip/TCPIP\ Stack/FTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/FTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/FTP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/FTP.o   "../../Microchip/TCPIP Stack/FTP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/FTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/FTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/HTTP.o: ../../Microchip/TCPIP\ Stack/HTTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/HTTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/HTTP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/HTTP.o   "../../Microchip/TCPIP Stack/HTTP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/HTTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/HTTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/Random.o: ../../Microchip/TCPIP\ Stack/Random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Random.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Random.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/Random.o   "../../Microchip/TCPIP Stack/Random.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/Random.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/RSA.o: ../../Microchip/TCPIP\ Stack/RSA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/RSA.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/RSA.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/RSA.o   "../../Microchip/TCPIP Stack/RSA.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/RSA.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/RSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/SSL.o: ../../Microchip/TCPIP\ Stack/SSL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SSL.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SSL.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/SSL.o   "../../Microchip/TCPIP Stack/SSL.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/SSL.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SSL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/SNMP.o: ../../Microchip/TCPIP\ Stack/SNMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNMP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNMP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/SNMP.o   "../../Microchip/TCPIP Stack/SNMP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/SNMP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SNMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/MainDemo.o: ../MainDemo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MainDemo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MainDemo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/MainDemo.o   ../MainDemo.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/MainDemo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MainDemo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/CustomHTTPApp.o: ../CustomHTTPApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CustomHTTPApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CustomHTTPApp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/CustomHTTPApp.o   ../CustomHTTPApp.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/CustomHTTPApp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/CustomHTTPApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/LCDBlocking.o: ../LCDBlocking.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/LCDBlocking.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/LCDBlocking.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/LCDBlocking.o   ../LCDBlocking.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/LCDBlocking.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/LCDBlocking.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/ClientSocket.o: ../ClientSocket.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ClientSocket.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ClientSocket.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/ClientSocket.o   ../ClientSocket.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/ClientSocket.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/ClientSocket.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/ServerSocket.o: ../ServerSocket.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ServerSocket.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ServerSocket.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/ServerSocket.o   ../ServerSocket.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/ServerSocket.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/ServerSocket.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/MPFSImg2.o: ../MPFSImg2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MPFSImg2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MPFSImg2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/MPFSImg2.o   ../MPFSImg2.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/MPFSImg2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MPFSImg2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/_ext/1295770447/TFTPc.o: ../../Microchip/TCPIP\ Stack/TFTPc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TFTPc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TFTPc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/TFTPc.o   "../../Microchip/TCPIP Stack/TFTPc.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/TFTPc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/TFTPc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/Announce.o: ../../Microchip/TCPIP\ Stack/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Announce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/Announce.o   "../../Microchip/TCPIP Stack/Announce.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/Announce.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/ARP.o: ../../Microchip/TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ARP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ARP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/ARP.o   "../../Microchip/TCPIP Stack/ARP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/ARP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/Delay.o: ../../Microchip/TCPIP\ Stack/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/Delay.o   "../../Microchip/TCPIP Stack/Delay.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/Delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/DHCP.o: ../../Microchip/TCPIP\ Stack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/DHCP.o   "../../Microchip/TCPIP Stack/DHCP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/DHCP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DHCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/DHCPs.o: ../../Microchip/TCPIP\ Stack/DHCPs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCPs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCPs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/DHCPs.o   "../../Microchip/TCPIP Stack/DHCPs.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/DHCPs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DHCPs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/DNS.o: ../../Microchip/TCPIP\ Stack/DNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DNS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/DNS.o   "../../Microchip/TCPIP Stack/DNS.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/DNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/DynDNS.o: ../../Microchip/TCPIP\ Stack/DynDNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DynDNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DynDNS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/DynDNS.o   "../../Microchip/TCPIP Stack/DynDNS.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/DynDNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DynDNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/ENC28J60.o: ../../Microchip/TCPIP\ Stack/ENC28J60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ENC28J60.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ENC28J60.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/ENC28J60.o   "../../Microchip/TCPIP Stack/ENC28J60.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/ENC28J60.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ENC28J60.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/ETH97J60.o: ../../Microchip/TCPIP\ Stack/ETH97J60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETH97J60.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETH97J60.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/ETH97J60.o   "../../Microchip/TCPIP Stack/ETH97J60.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/ETH97J60.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ETH97J60.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/Hashes.o: ../../Microchip/TCPIP\ Stack/Hashes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Hashes.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Hashes.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/Hashes.o   "../../Microchip/TCPIP Stack/Hashes.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/Hashes.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Hashes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/Helpers.o: ../../Microchip/TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Helpers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/Helpers.o   "../../Microchip/TCPIP Stack/Helpers.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/Helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/HTTP2.o: ../../Microchip/TCPIP\ Stack/HTTP2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/HTTP2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/HTTP2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/HTTP2.o   "../../Microchip/TCPIP Stack/HTTP2.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/HTTP2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/HTTP2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/ICMP.o: ../../Microchip/TCPIP\ Stack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ICMP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ICMP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/ICMP.o   "../../Microchip/TCPIP Stack/ICMP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/ICMP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ICMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/IP.o: ../../Microchip/TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/IP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/IP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/IP.o   "../../Microchip/TCPIP Stack/IP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/IP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/MPFS2.o: ../../Microchip/TCPIP\ Stack/MPFS2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/MPFS2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/MPFS2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/MPFS2.o   "../../Microchip/TCPIP Stack/MPFS2.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/MPFS2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/MPFS2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/NBNS.o: ../../Microchip/TCPIP\ Stack/NBNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/NBNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/NBNS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/NBNS.o   "../../Microchip/TCPIP Stack/NBNS.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/NBNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/NBNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/Reboot.o: ../../Microchip/TCPIP\ Stack/Reboot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Reboot.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Reboot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/Reboot.o   "../../Microchip/TCPIP Stack/Reboot.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/Reboot.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Reboot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/SMTP.o: ../../Microchip/TCPIP\ Stack/SMTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SMTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SMTP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/SMTP.o   "../../Microchip/TCPIP Stack/SMTP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/SMTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SMTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/SNTP.o: ../../Microchip/TCPIP\ Stack/SNTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNTP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/SNTP.o   "../../Microchip/TCPIP Stack/SNTP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/SNTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SNTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o: ../../Microchip/TCPIP\ Stack/SPIEEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o   "../../Microchip/TCPIP Stack/SPIEEPROM.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/SPIFlash.o: ../../Microchip/TCPIP\ Stack/SPIFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIFlash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIFlash.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/SPIFlash.o   "../../Microchip/TCPIP Stack/SPIFlash.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/SPIFlash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SPIFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/SPIRAM.o: ../../Microchip/TCPIP\ Stack/SPIRAM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIRAM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIRAM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/SPIRAM.o   "../../Microchip/TCPIP Stack/SPIRAM.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/SPIRAM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SPIRAM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/StackTsk.o: ../../Microchip/TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/StackTsk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/StackTsk.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/StackTsk.o   "../../Microchip/TCPIP Stack/StackTsk.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/StackTsk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/StackTsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/TCP.o: ../../Microchip/TCPIP\ Stack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TCP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/TCP.o   "../../Microchip/TCPIP Stack/TCP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/TCP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/TCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/Telnet.o: ../../Microchip/TCPIP\ Stack/Telnet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Telnet.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Telnet.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/Telnet.o   "../../Microchip/TCPIP Stack/Telnet.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/Telnet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Telnet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/Tick.o: ../../Microchip/TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Tick.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/Tick.o   "../../Microchip/TCPIP Stack/Tick.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.o: ../../Microchip/TCPIP\ Stack/UART2TCPBridge.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.o   "../../Microchip/TCPIP Stack/UART2TCPBridge.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/UART.o: ../../Microchip/TCPIP\ Stack/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/UART.o   "../../Microchip/TCPIP Stack/UART.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/UART.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/UDP.o: ../../Microchip/TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UDP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UDP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/UDP.o   "../../Microchip/TCPIP Stack/UDP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/UDP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/BerkeleyAPI.o: ../../Microchip/TCPIP\ Stack/BerkeleyAPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/BerkeleyAPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/BerkeleyAPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/BerkeleyAPI.o   "../../Microchip/TCPIP Stack/BerkeleyAPI.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/BerkeleyAPI.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/BerkeleyAPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/ENCX24J600.o: ../../Microchip/TCPIP\ Stack/ENCX24J600.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o   "../../Microchip/TCPIP Stack/ENCX24J600.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ENCX24J600.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/FTP.o: ../../Microchip/TCPIP\ Stack/FTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/FTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/FTP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/FTP.o   "../../Microchip/TCPIP Stack/FTP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/FTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/FTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/HTTP.o: ../../Microchip/TCPIP\ Stack/HTTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/HTTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/HTTP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/HTTP.o   "../../Microchip/TCPIP Stack/HTTP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/HTTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/HTTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/Random.o: ../../Microchip/TCPIP\ Stack/Random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Random.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Random.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/Random.o   "../../Microchip/TCPIP Stack/Random.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/Random.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/RSA.o: ../../Microchip/TCPIP\ Stack/RSA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/RSA.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/RSA.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/RSA.o   "../../Microchip/TCPIP Stack/RSA.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/RSA.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/RSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/SSL.o: ../../Microchip/TCPIP\ Stack/SSL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SSL.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SSL.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/SSL.o   "../../Microchip/TCPIP Stack/SSL.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/SSL.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SSL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1295770447/SNMP.o: ../../Microchip/TCPIP\ Stack/SNMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNMP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNMP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1295770447/SNMP.o   "../../Microchip/TCPIP Stack/SNMP.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1295770447/SNMP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SNMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/MainDemo.o: ../MainDemo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MainDemo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MainDemo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/MainDemo.o   ../MainDemo.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/MainDemo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MainDemo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/CustomHTTPApp.o: ../CustomHTTPApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CustomHTTPApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CustomHTTPApp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/CustomHTTPApp.o   ../CustomHTTPApp.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/CustomHTTPApp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/CustomHTTPApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/LCDBlocking.o: ../LCDBlocking.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/LCDBlocking.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/LCDBlocking.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/LCDBlocking.o   ../LCDBlocking.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/LCDBlocking.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/LCDBlocking.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/ClientSocket.o: ../ClientSocket.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ClientSocket.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ClientSocket.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/ClientSocket.o   ../ClientSocket.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/ClientSocket.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/ClientSocket.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/ServerSocket.o: ../ServerSocket.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ServerSocket.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ServerSocket.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/ServerSocket.o   ../ServerSocket.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/ServerSocket.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/ServerSocket.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/MPFSImg2.o: ../MPFSImg2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MPFSImg2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MPFSImg2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -I".." -I"../Microchip/Include" -I"../../Microchip/Include" -ml -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/MPFSImg2.o   ../MPFSImg2.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/MPFSImg2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MPFSImg2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/tcpip.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG   -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_SIMULATOR=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/tcpip.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/tcpip.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w    -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/tcpip.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Default
	${RM} -r dist/Default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
