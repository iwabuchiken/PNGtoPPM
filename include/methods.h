/* 
 * File:   methods.h
 * Author: buchi
 *
 * Created on 2014/05/25, 11:45
 */



#ifndef METHODS_H
#define	METHODS_H

#ifdef	__cplusplus
extern "C" {
#endif

/**************************
 * Variables
 **************************/
const char *LOG_FILE_PATH = "./log/exec_log.txt";


/**************************
 * Prototypes
 **************************/
void log_Command_Input(int, char **);


#ifdef	__cplusplus
}
#endif

#endif	/* METHODS_H */

