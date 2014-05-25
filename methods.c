#ifndef METHODS_H
//#define	METHODS_H
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

void log_Command_Input(int argc, char **argv)
{

    char *time_label = get_TimeLabel_Now(STANDARD);
    
//    //log
//    printf("[%s : %d] time_label => %s\n", 
//            base_name(__FILE__), __LINE__, time_label);
//
//    
//    //log
//    printf("[%s : %d] argc => %d\n", base_name(__FILE__), __LINE__, argc);

    char joint = ' ';
    
    char *argv_str = join(joint, argv, argc);
//    char *argv_str = join(" ", argv, argc);
    
//    //log
//    printf("[%s : %d] argv_str => %s\n", base_name(__FILE__), __LINE__, argv_str);

//    char *log_file_path = "./log/exec_log.txt";
    
    FILE *fp;
    
    if((fp = fopen(LOG_FILE_PATH, "a")) == NULL) {
        
        //log
        printf("[%s : %d] Can't open the log file: %s\n", 
                base_name(__FILE__), __LINE__, LOG_FILE_PATH);
        
        exit(-1);

    }
    
    //REF fprintf http://www.tutorialspoint.com/c_standard_library/c_function_fprintf.htm
    fprintf(fp, "[%s]\n", time_label);
//    fprintf(fp, "%s %s %s %d", "We", "are", "in", 2012);
    
    fprintf(fp, "%s\n", "<argv>");
    
    // argc
    fprintf(fp, "argc=%d: ", argc);
    
    fprintf(fp, "%s\n", argv_str);
    
//    char *CR = "\n";
//    
//    fwrite(CR, 1, sizeof(CR), fp);
//    fwrite('\n', 1, sizeof(char), fp);
    
    //REF fputc http://www.cplusplus.com/reference/cstdio/fputc/
    fputc('\n', fp);
    
    fclose(fp);
    
    //log
    printf("[%s : %d] file => closed: %s\n", 
            base_name(__FILE__), __LINE__, LOG_FILE_PATH);

}
