/* 
 * File:   main.h
 * Author: buchi
 *
 * Created on 2014/05/26, 13:29
 */

#ifndef MAIN_H
#define	MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#ifndef PNGLIB_H
//#define	PNGLIB_H
//#include "include/pnglib.h"
#include "pnglib.h"
//#include "include/pnglib.h"
#endif

#ifndef PNGINFO_H

//#include "include/pnglib.h"
//#include "include/pnginfo.h"

#include "include/pnginfo.h"

#endif

#ifndef METHODS_H
#define	METHODS_H
#include "methods.h"
#endif

///////////////////////////////////////////
//
//// Vars
//
///////////////////////////////////////////
//char *Histo_RGB[];

#ifdef	__cplusplus
extern "C" {
#endif

void Mode_Histo(int, char **);    



#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

