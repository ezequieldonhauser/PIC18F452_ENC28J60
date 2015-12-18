#ifndef __TICK_H
#define __TICK_H

#include "TCPIP Stack/TCPIP.h"

// All TICKS are stored as 32-bit unsigned integers.
typedef DWORD TICK;

// This value is used by TCP to implement timeout actions.
// For this definition, the Timer must be initialized to use 
// a 1:256 prescalar in Tick.c.  If using a 32kHz watch crystal 
// as the time base, modify the Tick.c file to use no prescalar.
#define TICKS_PER_SECOND		((GetPeripheralClock()+128ull)/256ull)	// Internal core clock drives timer
//#define TICKS_PER_SECOND		(32768ul)								// 32kHz crystal drives timer with no scalar

// Represents one second in Ticks
#define TICK_SECOND				((QWORD)TICKS_PER_SECOND)
// Represents one minute in Ticks
#define TICK_MINUTE				((QWORD)TICKS_PER_SECOND)*60ull)
// Represents one hour in Ticks
#define TICK_HOUR				((QWORD)TICKS_PER_SECOND*3600ull)

// Deprecated.  Do not use this function.
#define TickGetDiff(a, b)       ((a)-(b))

void TickInit(void);
DWORD TickGet(void);
DWORD TickGetDiv256(void);
DWORD TickGetDiv64K(void);
DWORD TickConvertToMilliseconds(DWORD dwTickValue);
void TickUpdate(void);

#endif
