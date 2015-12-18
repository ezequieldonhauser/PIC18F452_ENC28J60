#ifndef __COMPILER_H
#define __COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PTR_BASE            WORD
#define ROM_PTR_BASE        unsigned short long
#define	__attribute__(a)
#define FAR                 far
#define ROM                 rom
#define strcpypgm2ram(a, b) strcpypgm2ram(a,(far rom char*)b)

#endif
