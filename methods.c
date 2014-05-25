#ifndef METHODS_H
#include "include/methods.h"
#endif

#ifndef PNGLIB_H
//#include "include/pnglib.h"
#include "include/pnglib.h"
//#include "include/pnglib.h"
#include "include/pnginfo.h"
#endif

void show_help(void)
{
    char *msg = "<Usage>\n"
    "\tpngtoppm src1 src2 dst\n"
    "\n"
    "<Options>\n"
    "\t-bg\t background color\n"
    "\t\tred, green, blue, purple, white, black"
    "\t-direc\n"
    "\t\tverti, hori\n"
    
    "\t-proc\n"
    "\t\tProcess png pixels\n"
    
    "\t-rgb\n"
    "\t\tRGB values for \"-proc\" mode\n"
    "\t\te.g. 100,20,50 (R,G,B)\n"
    "\t\te.g. ./dist/Debug/GNU-Linux-x86/pngtoppm\n"
    "\t\t\t-src images/XXX -dst images/YYY -proc -rgb 100,20,20\n"
    ;


    consolColor_Change(LIGHT_BLUE);
    
    //log
    printf("[%s : %d]\n%s\n", base_name(__FILE__), __LINE__, msg);

    consolColor_Reset();
    
}

