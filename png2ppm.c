/* 
 * File:   main.c
 * Author: iwabuchik
 *
 * Created on May 12, 2014, 10:03 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#ifndef PNGLIB_H
#include "include/pnglib.h"
#include "include/pnginfo.h"
#endif

//#ifndef LIB_H

/*
 * 
 */
/*************************************
 
 * Prototypes
 
 **************************************/
char * _setup_FileName_Src(int, char **);
char * _setup_FileName_Dst(int, char **);

//void process_file(png_bytep *, int, int);


void _test_double_pointer(void);
void _test_malloc_in_function(void);

/*************************************
 
 * global vars
 
 **************************************/
extern png_bytep * row_pointers;


int main(int argc, char** argv) {

    int x, y;

    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
//    png_bytep * row_pointers;

    /*************************************
 
     * Setup: source file path
 
     **************************************/
    char *file_path_src = _setup_FileName_Src(argc, argv);
    
    consolColor_Change(GREEN);
    //log
    printf("[%s : %d] file_path_src = %s\n",
            base_name(__FILE__), __LINE__, file_path_src);

    consolColor_Reset();
    
    /*************************************
 
     * Get: png info
 
     **************************************/
    get_PngInfo
    (file_path_src, png_ptr, info_ptr,
        &width, &height, &number_of_passes,
        &color_type, &bit_depth);
    
    
//    //log
//    printf("[%s : %d] height => %d\n", base_name(__FILE__), __LINE__, height);
//
//    //log
//    printf("[%s : %d] info_ptr->height => %d\n",
//            base_name(__FILE__), __LINE__, info_ptr->height);
//    printf("[%s : %d] info_ptr.height => %d\n",
//            base_name(__FILE__), __LINE__, (*info_ptr).height);
////            base_name(__FILE__), __LINE__, (&info_ptr).height);
////            base_name(__FILE__), __LINE__, info_ptr.height);

    /*************************************
 
     * tests
 
     **************************************/
//    _test_double_pointer();
//    _test_malloc_in_function();
    
    /*************************************
 
     * setup: vars
 
     **************************************/
    // png_ptr
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
            abort_("[read_png_file] png_create_read_struct failed");
    
    consolColor_Change(LIGHT_YELLOW);

    //log
    printf("[%s : %d] png_create_read_struct() => done\n", base_name(__FILE__), __LINE__);

    consolColor_Reset();
    
    // info_ptr
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
            abort_("[read_png_file] png_create_info_struct failed");
    
    consolColor_Change(LIGHT_YELLOW);

    //log
    printf("[%s : %d] png_create_info_struct() => done\n", base_name(__FILE__), __LINE__);

    consolColor_Reset();
    
    /*************************************
 
     * read png
 
     **************************************/
    _test_ReadPng
    (file_path_src, png_ptr, info_ptr,
        &width, &height, &number_of_passes,
            &color_type, &bit_depth);

    /*************************************
 
     * process file
 
     **************************************/
//    //log
////    printf("[%s : %d] row_pointers[0][0] = %d\n", 
////            base_name(__FILE__), __LINE__, row_pointers[0][0]);
//    printf("[%s : %d] row_pointers[0] = %d\n", 
//            base_name(__FILE__), __LINE__, row_pointers[0]);
//
//    
//    
//     process_file(png_ptr, info_ptr, width, height);
////     process_file(width, height);
//     
//     //log
//    printf("[%s : %d] process => done\n", base_name(__FILE__), __LINE__);

    
    /*************************************
 
     * Conv: png to ppm
 
     **************************************/
    PPM *ppm = (PPM *) malloc(sizeof(PPM) * 1);
    
    conv_PNG_to_PPM(png_ptr, ppm);
//    PPM *ppm = conv_PNG_to_PPM(png_ptr);
    
    consolColor_Change(GREEN);
    
    //log
    printf("[%s : %d] ppm->file_name = %s\n",
            base_name(__FILE__), __LINE__, ppm->file_name);

    consolColor_Reset();
    
    //log
    printf("[%s : %d] ppm->format = %s\n", base_name(__FILE__), __LINE__, ppm->format);

    
    consolColor_Change(LIGHT_YELLOW);
    
    //log
    printf("[%s : %d] ppm->max_brightness = %d\n",
            base_name(__FILE__), __LINE__, ppm->max_brightness);
//    printf("[%s : %d] ppm->x = %d\n",
//            base_name(__FILE__), __LINE__, ppm->x);

    consolColor_Reset();
    
    
    //log
    printf("[%s : %d] row_pointers[0][0] => %d\n",
            base_name(__FILE__), __LINE__, row_pointers[0][0]);
    printf("[%s : %d] row_pointers[0][0] => %d\n",
            base_name(__FILE__), __LINE__, row_pointers[0][1]);
    printf("[%s : %d] row_pointers[0][0] => %d\n",
            base_name(__FILE__), __LINE__, row_pointers[0][2]);

    
    consolColor_Change(LIGHT_YELLOW);
    
    //log
    printf("[%s : %d] ppm->pixels[0].r = %d\n",
            base_name(__FILE__), __LINE__, ppm->pixels[0].r);
    printf("[%s : %d] ppm->pixels[0].g = %d\n",
            base_name(__FILE__), __LINE__, ppm->pixels[0].g);
    printf("[%s : %d] ppm->pixels[0].b = %d\n",
            base_name(__FILE__), __LINE__, ppm->pixels[0].b);

    consolColor_Reset();
    
    
    /*************************************
 
     * write: ppm
 
     **************************************/
    char *file_path_dst = _setup_FileName_Dst(argc, argv);
    
    consolColor_Change(GREEN);

    //log
    printf("[%s : %d] file_path_dst => %s\n", base_name(__FILE__), __LINE__, file_path_dst);

    consolColor_Reset();
    
    save_PPM(file_path_dst, ppm);
    
    consolColor_Change(LIGHT_YELLOW);

    //log
    printf("[%s : %d] save_PPM => done\n", base_name(__FILE__), __LINE__);

    consolColor_Reset();


    
    /*************************************
 
     * write png
 
     **************************************/
//    char *file_path_dst = _setup_FileName_Dst(argc, argv);
    
    
    
//    png_ptr->height = (png_ptr->height) / 2;
//    png_ptr->width = (png_ptr->width) / 2;
//    
//    info_ptr->height = (info_ptr->height) / 2;
//    info_ptr->width = (info_ptr->width) / 2;
//    
//    //logaa
//    printf("[%s : %d] png_ptr->height = %d\n", base_name(__FILE__), __LINE__, png_ptr->height);
//
//    width = width / 2;
//    height = height / 2;
//    
//    _test_WritePng
//    (file_path_dst, png_ptr, info_ptr,
//        &width, &height,
//        &color_type, &bit_depth);
    
//    write_png_file
//    (file_path_dst, png_ptr, info_ptr, row_pointers,
//        &width, &height, &color_type, &bit_depth);
    
//    //log
//    printf("[%s : %d] _test_WritePng() => done\n", base_name(__FILE__), __LINE__);
//    //log
//    printf("[%s : %d] write_png_file() => done\n", base_name(__FILE__), __LINE__);

    
    //log
    printf("[%s : %d] done\n", base_name(__FILE__), __LINE__);

    
    return (EXIT_SUCCESS);
}

char * _setup_FileName_Src(int argc, char **argv)
{
    char *src = "/home/iwabuchik/WORKS/WS/WS_Prog/PNGtoPPM/images/download-jpg.png";
    
    if(argc < 2)
        return src;
    
    int len = strlen(argv[1]);  // Get argv[1]
    
    src = (char *) malloc(sizeof(char) * (len + 1));
    
    strcpy(src, argv[1]);
    
    *(src + len) = '\0';        // null char
    
    return src;
    
}

char * _setup_FileName_Dst(int argc, char **argv)
{
    char *dst = "/home/iwabuchik/WORKS/WS/WS_Prog/PNGtoPPM/images/copy.png";
    
    if(argc < 3)
        return dst;
    
    int len = strlen(argv[2]);  // Get argv[2]
    
    dst = (char *) malloc(sizeof(char) * (len + 1));
    
    strcpy(dst, argv[2]);
    
    *(dst + len) = '\0';        // null char
    
    return dst;
    
}

//void process_file
//(png_bytep * row_pointers, int width, int height)
////void process_file(void)
//{
////        if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
////                abort_("[process_file] input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA "
////                       "(lacks the alpha channel)");
////
////        if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGBA)
////                abort_("[process_file] color_type of input file must be PNG_COLOR_TYPE_RGBA (%d) (is %d)",
////                       PNG_COLOR_TYPE_RGBA, png_get_color_type(png_ptr, info_ptr));
//        
//    int x, y;
//    
//        for (y=0; y<height; y++) {
//            
//            //log
//        printf("[%s : %d] y = %d\n", base_name(__FILE__), __LINE__, y);
//
//                png_byte* row = row_pointers[y];
//                
//                //log
//        printf("[%s : %d] png_byte* row\n", base_name(__FILE__), __LINE__);
//
//                
//                for (x=0; x<width; x++) {
//                    
//                    //log
//            printf("[%s : %d] x = %d\n", base_name(__FILE__), __LINE__, x);
//
//                        png_byte* ptr = &(row[x*3]);
//                        
//                        //log
//            printf("[%s : %d] png_byte* ptr\n", base_name(__FILE__), __LINE__);
//
////                        printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d\n",
////                               x, y, ptr[0], ptr[1], ptr[2]);
////                        png_byte* ptr = &(row[x*4]);
////                        printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
////                               x, y, ptr[0], ptr[1], ptr[2], ptr[3]);
//
//                        /* set red value to 0 and green value to the blue one */
////                        ptr[0] = 0;
////                        ptr[1] = ptr[2];
//            //log
//            printf("[%s : %d] start => ptr[0] = 0\n", base_name(__FILE__), __LINE__);
//
//                        ptr[0] = 0;
//                        
//                        //log
//            printf("[%s : %d] ptr[0]\n", base_name(__FILE__), __LINE__);
//
//                        
//                        ptr[1] = 0;
//                        
//            printf("[%s : %d] ptr[1]\n", base_name(__FILE__), __LINE__);
//            
//                        ptr[2] = 255 - ptr[2];
//            
//            printf("[%s : %d] ptr[2]\n", base_name(__FILE__), __LINE__);
//                        
//                        //log
//            printf("[%s : %d] ptr[] => done\n", base_name(__FILE__), __LINE__);
//
////                        ptr[1] = 255 - ptr[0];
////                        ptr[2] = 255 - ptr[0];
////                        ptr[1] = ptr[2];
//                }
//        }//for (y=0; y<height; y++)
//        
//        //log
//    printf("[%s : %d] processing => done\n", base_name(__FILE__), __LINE__);
//
//}

void _test_double_pointer()
{
    char ** memos;
    
    memos = (char **) malloc(sizeof(char*) * 4);
    
    //log
    printf("[%s : %d] malloc => done for memos\n", base_name(__FILE__), __LINE__);

    
    _test_DoublePointer(memos);
    
    //log
    printf("[%s : %d] memos[0] => %s\n", base_name(__FILE__), __LINE__, memos[0]);

    
}

void _test_malloc_in_function()
{
    char *msg;
    
    _test_MallocInFunction(msg);
    
    //log
    printf("[%s : %d] msg => %s\n", base_name(__FILE__), __LINE__, msg);

    
}

