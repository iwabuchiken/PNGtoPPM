/* 
 * File:   pnglib.h
 * Author: iwabuchik
 *
 * Created on May 11, 2014, 12:42 AM
 */

#ifndef PNGLIB_H
#define	PNGLIB_H
//#endif

#ifndef LIB_H
#include "lib.h"
#endif

#ifndef IMG_LIB_H
#include "img_lib.h"
#endif

#include <zlib.h>

#include <stdarg.h>

//#include "pngstruct.h"

#include <png.h>

//#include <pngstruct.h>
#include "pngstruct.h"  // => needs to include AFTER png.h
#include "pnginfo.h"

#ifndef READPNG_H
typedef unsigned char   uch;  // readpng.h
typedef unsigned short  ush;  // readpng.h
typedef unsigned long   ulg;  // readpng.h
#endif


//typedef unsigned char png_byte;  // png.h
//typedef const png_byte        * png_const_bytep;  // png.h
//typedef size_t png_size_t;  // png.h

//#define PNG_LIBPNG_VER_STRING "1.6.10"  // png.h

#define PIXEL_GREEN     0, 100, 0
#define PIXEL_BLUE      0, 0, 100
#define PIXEL_RED       100, 0, 0
#define PIXEL_PURPLE    100, 0, 100

#ifdef	__cplusplus
extern "C" {
#endif

    png_bytep * row_pointers;
    png_bytep * row_pointers_RGBA;
    
    // merge_png.c
    png_bytep * row_pointers_A;
    png_bytep * row_pointers_B;
    png_bytep * row_pointers_C;
    
    typedef enum MergeFileType {
        
        SRC_A, SRC_B
                
    } MergeFileType;
    
//    png_bytep * row_pointers_rgba;
    
    void show_message_png(void);
    
    int lib_readpng_init(FILE *, ulg *, ulg *);
    
    int lib_png_sig_cmp
    (png_const_bytep, png_size_t, png_size_t);

    void abort_(const char *, ...);

    void read_png_file
    (char*,
        png_structp, png_infop, png_bytep *,
        int *, int *, int *, png_byte *, png_byte *);
    
    void write_png_file
    (char*, png_structp,
        png_infop, png_bytep *,
        int *, int *,
        png_byte *, png_byte *);

    void get_PngInfo
    (char*, png_structp, png_infop,
        int *, int *, int *,
        png_byte *, png_byte *);
    
    void _test_DoublePointer(char **);
    void _test_MallocInFunction(char *);
    
    void _test_ReadPng
    (char*, png_structp, png_infop, 
        int *, int *, int *,
        png_byte *, png_byte *);
    
    void _test_ReadPng_Rgba
    (char*, png_structp, png_infop, 
        int *, int *, int *,
        png_byte *, png_byte *);
    
    void _test_ReadPng_Merge
    (char*, png_structp, png_infop, 
        int *, int *, int *,
        png_byte *, png_byte *, int);
    
    void _test_WritePng
    (char*, png_structp, png_infop,
        int *, int *,
        png_byte *, png_byte *);
    
    void _test_WritePng_Merge
    (char*, png_structp, png_infop,
        int *, int *,
        png_byte *, png_byte *, int);
    
    void _test_WritePng_Rgba
    (char*, png_structp, png_infop,
        int *, int *,
        png_byte *, png_byte *);
    
    void process_file
    (png_structp, png_infop, int, int);
    
    void conv_PNG_to_PPM(png_structp, PPM *);
//    PPM* conv_PNG_to_PPM(png_structp);
    
    void conv_RGB_to_RGBA
    (char*, png_structp, png_structp,
            png_infop, int *, int *);
    
    void set_PixelVals(png_byte*, int, int, int);

    void merge_PngSrcs(
            int, int, 
            int, int, 
            int, int
        );
    
    void merge_PngSrcs_Hori_General
    (
        int, int, 
        int, int, 
        int, int
    );
    
    void _merge_PngSrcs_Hori_General_AlargerThanB
    (
        int, int, 
        int, int, 
        int, int
    );
    
    void _merge_PngSrcs_Hori_General_AsmallerThanB
    (
        int, int, 
        int, int, 
        int, int
    );
    
#ifdef	__cplusplus
}
#endif

#endif	/* PNGLIB_H */

