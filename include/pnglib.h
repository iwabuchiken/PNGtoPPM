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
#define PIXEL_WHITE     100, 100, 100
#define PIXEL_BLACK     0, 0, 0
#define PIXEL_GRAY      50, 50, 50

#define MAX_BRIGHTNESS 255

/////////////////////////////////////////

// enums

/////////////////////////////////////////
typedef enum {
    
    rgb, threshold
    
} ProcMode;

/////////////////////////////////////////

// Vars

/////////////////////////////////////////
//char *bg_colors_2[] = {
//    
//    "red", "blue", "green", "purple",
//    "white", "black"
//    
//};

//int pnglib;
//char *bg_colors_2;
//char *bg_colors_3 = "abcdef";


#ifdef	__cplusplus
extern "C" {
#endif

    // Background colors used in the histogram PNG file
    char *bg_colors_2[];
    
    // Image size of the histogram PNG file
    int histo_png_size[2];
    
    // Array of histogram values
    int histo[MAX_BRIGHTNESS];
    
    // 1. max and minimum of the brightness value of a given PNG file
    // 2. used in the function: gen_HistoData(int width_A, int height_A)
    // 3. histo_range[max, minimum]
    int histo_range[2];     
    
//    char *bg_colors_2[6];
//    char *bg_colors_2[6] = {
//    
//        "red",  "blue", "green",        "purple",
//        "white",        "black"
//
//    };

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
    
    void _test_WritePng__Process
    (char*, png_structp, png_infop,
        int *, int *, png_byte *, png_byte *);
    
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
    void set_PixelVals_2(png_byte*, int[3]);

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
    
    void merge_PngSrcs_Verti_General
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

    void init_Row_Pointers_C
    (png_structp, png_infop, char *);
    
    void init_Row_Pointers_B
    (png_structp, png_infop);
    
    void _test_ReadPng__Process
    (char*, png_structp, png_infop,
    int *, int *, int *, png_byte *, png_byte *);
  
    void process_file__RGB
//    (png_structp, png_structp, int *[3], ProcMode);
    (png_structp, png_structp, int **, ProcMode);
    
    void init_Row_Pointers_B__Histo(png_structp, png_infop, char *);

    void gen_HistoData(int, int);
    
    void gen_HistoPixels(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* PNGLIB_H */

