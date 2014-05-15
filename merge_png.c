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
//char * _setup_FileName_Src(int, char **);
char * _setup_FileName_Dst(int, char **);

char ** _setup_FileName_Src(int, char **);

void show_help(void);

//void process_file(png_bytep *, int, int);


void _test_double_pointer(void);
void _test_malloc_in_function(void);

/*************************************
 
 * global vars
 
 **************************************/
extern png_bytep * row_pointers;
extern png_bytep * row_pointers_RGBA;

// merge_png.c
extern png_bytep * row_pointers_A;
extern png_bytep * row_pointers_B;
extern png_bytep * row_pointers_C;


int main(int argc, char** argv) {

    /*************************************
 
     * validate
 
     **************************************/
    if (argc < 4) {
        
        show_help();
        
        return 0;
    }
    
    /*************************************
 
     * vars
 
     **************************************/
    int x, y;

    // A
    int width_A, height_A; int number_of_passes_A;
    png_byte color_type_A, bit_depth_A;

    png_structp png_ptr_A; png_infop info_ptr_A;
    
    // B
    int width_B, height_B; int number_of_passes_B;
    png_byte color_type_B, bit_depth_B;

    png_structp png_ptr_B; png_infop info_ptr_B;
    
    // C
    int width_C, height_C; int number_of_passes_C;
    png_byte color_type_C, bit_depth_C;

    png_structp png_ptr_C; png_infop info_ptr_C;
    
    /*************************************
 
     * Setup: source file path
 
     **************************************/
    char **file_srcs = _setup_FileName_Src(argc, argv);
    
    consolColor_Change(GREEN);
    
    //log
    printf("[%s : %d] file_srcs[0] = %s\n",
            base_name(__FILE__), __LINE__, file_srcs[0]);
    printf("[%s : %d] file_srcs[1] = %s\n",
            base_name(__FILE__), __LINE__, file_srcs[1]);

    consolColor_Reset();
    
    /*************************************
 
     * Setup: dst file path
 
     **************************************/
    char *file_dst = _setup_FileName_Dst(argc, argv);
    
    consolColor_Change(GREEN);
    
    //log
    printf("[%s : %d] file_dst = %s\n",
            base_name(__FILE__), __LINE__, file_dst);

    consolColor_Reset();
    
    /*************************************
 
     * Get: png info
 
     **************************************/
    get_PngInfo
    (file_srcs[0], png_ptr_A, info_ptr_A,
        &width_A, &height_A, &number_of_passes_A,
        &color_type_A, &bit_depth_A);
    
    get_PngInfo
    (file_srcs[1], png_ptr_B, info_ptr_B,
        &width_B, &height_B, &number_of_passes_B,
        &color_type_B, &bit_depth_B);
    
//    get_PngInfo
//    (file_dst, png_ptr_C, info_ptr_C,
//        &width_C, &height_C, &number_of_passes_C,
//        &color_type_C, &bit_depth_C);
    
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
    // png_ptr_A
    png_ptr_A = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr_A)
            abort_("[read_png_file] png_create_read_struct failed");
    
    // info_ptr_A
    info_ptr_A = png_create_info_struct(png_ptr_A);
    if (!info_ptr_A)
            abort_("[read_png_file] png_create_info_struct failed");

    // png_ptr_B
    png_ptr_B = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr_B)
            abort_("[read_png_file] png_create_read_struct failed");
    
    // info_ptr_B
    info_ptr_B = png_create_info_struct(png_ptr_B);
    if (!info_ptr_B)
            abort_("[read_png_file] png_create_info_struct failed");

    // png_ptr_C
    png_ptr_C = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr_C)
            abort_("[read_png_file] png_create_read_struct failed");
    
    // info_ptr_C
    info_ptr_C = png_create_info_struct(png_ptr_C);
    if (!info_ptr_C)
            abort_("[read_png_file] png_create_info_struct failed");

            
    consolColor_Change(LIGHT_YELLOW);

    //log
    printf("[%s : %d] setup: vars => done\n", base_name(__FILE__), __LINE__);

    consolColor_Reset();
    
    /*************************************
 
     * read png
 
     **************************************/
    _test_ReadPng_Merge
    (file_srcs[0], png_ptr_A, info_ptr_A,
        &width_A, &height_A, &number_of_passes_A,
            &color_type_A, &bit_depth_A, 1);

    _test_ReadPng_Merge
    (file_srcs[1], png_ptr_B, info_ptr_B,
        &width_B, &height_B, &number_of_passes_B,
            &color_type_B, &bit_depth_B, 2);

    consolColor_Change(LIGHT_YELLOW);

    //log
    printf("[%s : %d] read png => done\n", base_name(__FILE__), __LINE__);

    
    consolColor_Reset();

    //log
    printf("[%s : %d] png_ptr_A->color_type, png_ptr_B->color_type => %d, %d\n", 
            base_name(__FILE__), __LINE__, png_ptr_A->color_type, png_ptr_B->color_type);

    
//    int tmp;
//    for(tmp = 0; tmp < 10; tmp++) {
//        
//        //log
//        printf("[%s : %d] row_poniters_A[%d] = %d / row_poniters_B[%d] = %d\n",
//                base_name(__FILE__), __LINE__, 
//                tmp, row_pointers_A[0][tmp], tmp, row_pointers_B[0][tmp]);
//
//    }

    /*************************************
 
     * Build: dst png info
     * 
     * 1. color type => use that of file A
     * 2. depth => same as 1
 
     **************************************/
//    //log
//    printf("[%s : %d] width_A, width_B => %d, %d\n",
//            base_name(__FILE__), __LINE__, width_A, width_B);
    
    width_C = width_A + width_B;
    height_C = height_A + height_B;

    color_type_C = color_type_A;
    bit_depth_C = bit_depth_A;
    
    png_ptr_C->width = width_C;
    png_ptr_C->height = height_C;
    
    png_ptr_C->color_type = png_ptr_A->color_type;
    png_ptr_C->bit_depth = png_ptr_A->bit_depth;
    
    png_ptr_C->rowbytes = png_ptr_A->rowbytes + png_ptr_B->rowbytes;
    info_ptr_C->rowbytes = info_ptr_A->rowbytes + info_ptr_B->rowbytes;
    
    
    //log
    printf("[%s : %d] info_ptr_C->rowbytes => %d\n", 
            base_name(__FILE__), __LINE__, info_ptr_C->rowbytes);

    
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
 
     * init: row_pointers_C (dst png)
 
     **************************************/
    init_Row_Pointers_C(png_ptr_C, info_ptr_C);

    //log
    printf("[%s : %d] png_ptr_C->width, png_ptr_C->height => %d, %d\n",
            base_name(__FILE__), __LINE__, png_ptr_C->width, png_ptr_C->height);
    printf("[%s : %d] png_ptr_C->rowbytes => %d\n",
            base_name(__FILE__), __LINE__, png_ptr_C->rowbytes);
    printf("[%s : %d] png_ptr_A->rowbytes, png_ptr_B->rowbytes => %d, %d\n",
            base_name(__FILE__), __LINE__,
            png_ptr_A->rowbytes,
            png_ptr_B->rowbytes
            );

    
    //log
    printf("[%s : %d] Back from => init_Row_Pointers_C()\n", base_name(__FILE__), __LINE__);

    /*************************************
 
     * write png
 
     **************************************/
    //log
    printf("[%s : %d] png_get_rowbytes(png_ptr_C,info_ptr_C) => %d\n",
            base_name(__FILE__), __LINE__, png_get_rowbytes(png_ptr_C,info_ptr_C));

    
    
    //log
    printf("[%s : %d] png_ptr_C->color_type = %d\n", 
            base_name(__FILE__), __LINE__, png_ptr_C->color_type);

    
    
    _test_WritePng_Merge
    (file_dst, png_ptr_C, info_ptr_C,
        &width_C, &height_C,
        &color_type_C, &bit_depth_C, 3);
    
//    _test_WritePng_Rgba
//    (file_path_dst, png_ptr_Dst, info_ptr_Dst,
//        &width_Dst, &height_Dst,
//        &color_type_Dst, &bit_depth_Dst);
    
    //log
    printf("[%s : %d] _test_WritePng() => done\n", base_name(__FILE__), __LINE__);

    
    //log
    printf("[%s : %d] done\n", base_name(__FILE__), __LINE__);

    
    return (EXIT_SUCCESS);
}

//char * _setup_FileName_Src(int argc, char **argv)
//{
//    char *src = "/home/iwabuchik/WORKS/WS/WS_Prog/PNGtoPPM/images/download-jpg.png";
//    
//    if(argc < 2)
//        return src;
//    
//    int len = strlen(argv[1]);  // Get argv[1]
//    
//    src = (char *) malloc(sizeof(char) * (len + 1));
//    
//    strcpy(src, argv[1]);
//    
//    *(src + len) = '\0';        // null char
//    
//    return src;
//    
//}

char * _setup_FileName_Dst(int argc, char **argv)
{
    char *dst = (char *) malloc(sizeof(char) * (strlen(argv[3]) + 1));
    
    strcpy(dst, argv[3]);
    dst[strlen(argv[3])] = '\0';
    
    return dst;
    
}//char * _setup_FileName_Dst(int argc, char **argv)

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

char ** _setup_FileName_Src(int argc, char **argv)
{
    if (argc < 4) {
        
        //log
        printf("[%s : %d] argc => < 4\n", base_name(__FILE__), __LINE__);

        return NULL;
        
    }
    
    char **names = (char **) malloc(sizeof(char *) * 2);
    
    char *name_1 = (char *) malloc(sizeof(char) * (strlen(argv[1]) + 1));
    char *name_2 = (char *) malloc(sizeof(char) * (strlen(argv[2]) + 1));
    
    // name_1
    strcpy(name_1, argv[1]);
    name_1[strlen(argv[1])] = '\0';
    
    names[0] = name_1;
    
    // name_2
    strcpy(name_2, argv[2]);
    name_2[strlen(argv[2])] = '\0';
    
    names[1] = name_2;
    
    // return
    return names;
    
}

void show_help(void)
{
    char *msg = "<Usage>\n"
                "\tpngtoppm src1 src2 dst\n"
    ;
    
    //log
    printf("[%s : %d]\n%s\n", base_name(__FILE__), __LINE__, msg);

    
}