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
extern png_bytep * row_pointers_RGBA;


int main(int argc, char** argv) {

    /*************************************
 
     * vars
 
     **************************************/
    int x, y;

    // Source
    int width_Src, height_Src;
    png_byte color_type_Src, bit_depth_Src;

    png_structp png_ptr_Src;
    png_infop info_ptr_Src;
    
    int number_of_passes_Src;

    // Dst
    int width_Dst, height_Dst;
    png_byte color_type_Dst, bit_depth_Dst;

    png_structp png_ptr_Dst;
    png_infop info_ptr_Dst;

    int number_of_passes_Dst;
    
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
    (file_path_src, png_ptr_Src, info_ptr_Src,
        &width_Src, &height_Src, &number_of_passes_Src,
        &color_type_Src, &bit_depth_Src);
    
    get_PngInfo
    (file_path_src, png_ptr_Dst, info_ptr_Dst,
        &width_Dst, &height_Dst, &number_of_passes_Dst,
        &color_type_Dst, &bit_depth_Dst);
    
    /*************************************
 
     * tests
 
     **************************************/
//    if (row_pointers_rgba == NULL) {
//        
//        //log
//        printf("[%s : %d] row_pointers_rgba => NULL\n", base_name(__FILE__), __LINE__);
//
//        
//    } else {
//        
//        //log
//        printf("[%s : %d] row_pointers_rgba => not NULL\n", base_name(__FILE__), __LINE__);
//    }
//    
//    
//    
//    
//    if (row_pointers_rgba == NULL) {
//        
//        //log
//        printf("[%s : %d] row_pointers_rgba => NULL\n", base_name(__FILE__), __LINE__);
//
//        
//    } else {
//        
//        //log
//        printf("[%s : %d] row_pointers_rgba => not NULL\n", base_name(__FILE__), __LINE__);
//    }
//    _test_double_pointer();
//    _test_malloc_in_function();
    
    /*************************************
 
     * setup: vars
 
     **************************************/
    // png_ptr_Src
    png_ptr_Src = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr_Src)
            abort_("[read_png_file] png_create_read_struct failed");
    
    // info_ptr_Src
    info_ptr_Src = png_create_info_struct(png_ptr_Src);
    if (!info_ptr_Src)
            abort_("[read_png_file] png_create_info_struct failed");

    // png_ptr_Dst
    png_ptr_Dst = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr_Dst)
            abort_("[read_png_file] png_create_read_struct failed");
    
    // info_ptr_Dst
    info_ptr_Dst = png_create_info_struct(png_ptr_Dst);
    if (!info_ptr_Dst)
            abort_("[read_png_file] png_create_info_struct failed");


            
    consolColor_Change(LIGHT_YELLOW);

    //log
    printf("[%s : %d] setup: vars => done\n", base_name(__FILE__), __LINE__);

    consolColor_Reset();
    
    /*************************************
 
     * read png
 
     **************************************/
    _test_ReadPng
    (file_path_src, png_ptr_Src, info_ptr_Src,
        &width_Src, &height_Src, &number_of_passes_Src,
            &color_type_Src, &bit_depth_Src);

    _test_ReadPng_Rgba
    (file_path_src, png_ptr_Dst, info_ptr_Dst,
        &width_Dst, &height_Dst, &number_of_passes_Dst,
            &color_type_Dst, &bit_depth_Dst);

    /*************************************
 
     * process file
 
     **************************************/
//    //log
//    
//     process_file(png_ptr_Src, info_ptr, width, height);
////     process_file(width, height);
//     
//     //log
//    printf("[%s : %d] process => done\n", base_name(__FILE__), __LINE__);

    /*************************************
 
     * Conv: png_ptr_Dst, height_Dst
 
     **************************************/
    //log
    printf("[%s : %d] png_ptr_Src->rowbytes = %d\n",
            base_name(__FILE__), __LINE__, png_ptr_Src->rowbytes);
    int rowbytes_Src = png_ptr_Src->rowbytes;
    
    png_ptr_Dst->rowbytes = rowbytes_Src * 4 / 3;
    
//    png_ptr_Dst->color_type = PNG_COLOR_TYPE_RGBA;
    
//    //log
//    printf("[%s : %d] PNG_COLOR_TYPE_RGBA = %d\n",
//            base_name(__FILE__), __LINE__, PNG_COLOR_TYPE_RGBA);        // 6
//    printf("[%s : %d] PNG_COLOR_TYPE_RGB = %d\n",       
//            base_name(__FILE__), __LINE__, PNG_COLOR_TYPE_RGB);         // 2
//    printf("[%s : %d] png_ptr_Src->color_type = %d\n",
//            base_name(__FILE__), __LINE__, png_ptr_Src->color_type);
    printf("[%s : %d] png_ptr_Dst->color_type = %d\n",
            base_name(__FILE__), __LINE__, png_ptr_Dst->color_type);
    
    printf("[%s : %d] png_ptr_Dst->rowbytes = %d\n",
            base_name(__FILE__), __LINE__, png_ptr_Dst->rowbytes);

    printf("[%s : %d] png_ptr_Dst->width = %d\n",
            base_name(__FILE__), __LINE__, png_ptr_Dst->width);


    
    /*************************************
 
     * Conv: RGB => RGBA
 
     **************************************/
    char *file_path_dst = _setup_FileName_Dst(argc, argv);
    
    //log
    printf("[%s : %d] width_Dst, height_Dst => %d, %d\n", 
            base_name(__FILE__), __LINE__, width_Dst, height_Dst);

    
    conv_RGB_to_RGBA
    (file_path_dst,
            png_ptr_Src, png_ptr_Dst,
            info_ptr_Src, &width_Dst, &height_Dst);
    
//    row_pointers_RGBA[0][0] = row_pointers[0][0];
    //log
    printf("[%s : %d] row_pointers_RGBA[0][0] = %d\n",
            base_name(__FILE__), __LINE__, row_pointers_RGBA[0][0]);
    printf("[%s : %d] row_pointers[0][0] = %d\n",
            base_name(__FILE__), __LINE__, row_pointers[0][0]);

    /*************************************
 
     * write png
 
     **************************************/
//    _test_WritePng
//    (file_path_dst, png_ptr_Dst, info_ptr_Dst,
//        &width_Dst, &height_Dst,
//        &color_type_Dst, &bit_depth_Dst);
    _test_WritePng_Rgba
    (file_path_dst, png_ptr_Dst, info_ptr_Dst,
        &width_Dst, &height_Dst,
        &color_type_Dst, &bit_depth_Dst);
    
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

