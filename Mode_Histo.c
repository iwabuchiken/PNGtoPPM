//#include <stdio.h>
//#include <stdlib.h>
//#include <stdarg.h>
//#include <string.h>
//#include <unistd.h>
//
//#ifndef PNGLIB_H
////#define	PNGLIB_H
////#include "include/pnglib.h"
//#include "include/pnglib.h"
//#endif
//
//#ifndef PNGINFO_H
//
////#include "include/pnglib.h"
////#include "include/pnginfo.h"
//
//#include "include/pnginfo.h"
//
//#endif
//
//#ifndef METHODS_H
//#define	METHODS_H
//#include "include/methods.h"
//#endif

#ifndef MAIN_H
#include "include/main.h"
#endif



/////////////////////////////////////////

// prototypes

/////////////////////////////////////////
void _Mode_Histo__GetFileNames(int, char **);
void _Mode_Histo__DstPNG_Info(void);
void _Mode_Histo__Setup_Vars(int, char **);
void _Mode_Histo__Option_RGB(int, char **);
void _Mode_Histo__Write_ExecInfo(int, char **);
        
/////////////////////////////////////////

// Vars

/////////////////////////////////////////
//// Historgram: which color element to use for a histogram PNG
//char *Histo_RGB[] = {"R", "G", "B", "ALL"};
char *file_src;
char *file_dst;
char *opt_RGB;

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

void Mode_Histo(int argc, char **argv)
{
    /**************************
     * Get: file names
     **************************/
    _Mode_Histo__GetFileNames(argc, argv);
    
//    /**************************
//     * Get: Source PNG file
//     **************************/
//    file_src = (char *) _setup_FileName_Src__Process(argc, argv);
////    char *file_src = (char *) _setup_FileName_Src__Process(argc, argv);
//    
//    consolColor_Change(GREEN);
//
//    //log
//    printf("[%s : %d] file_src => %s\n", base_name(__FILE__), __LINE__, file_src);
//
//    consolColor_Reset();
//    
//    
//    /**************************
//     * Get: dst PNG file
//     **************************/
//    file_dst = (char *) _setup_FileName_Dst__Histo(argc, argv);
////    char *file_dst = (char *) _setup_FileName_Dst__Histo(argc, argv);
//    
//    consolColor_Change(GREEN);
//
//    //log
//    printf("[%s : %d] file_dst => %s\n", base_name(__FILE__), __LINE__, file_dst);
//
//    consolColor_Reset();
//    
    /*************************************
 
     * option: "-rgb"
 
     **************************************/
    _Mode_Histo__Option_RGB(argc, argv);
    
//    const char *opt_label_RGB = "-rgb";
//    
//    opt_RGB = get_Opt_Value(argv, opt_label_RGB);
////    char *opt_RGB = get_Opt_Value(argv, opt_label_RGB);
////    char *opt_RGB = get_Opt_Value(argv, "-rgb");
//
//    consolColor_Change(LIGHT_YELLOW);
//
//    //log
//    printf("[%s : %d] rgb option => %s\n",
//            base_name(__FILE__), __LINE__, opt_RGB);
//
//    consolColor_Reset();
//    //log
//    printf("[%s : %d] debug\n", base_name(__FILE__), __LINE__);
//
//    exit(-1);
    
    /*************************************
 
     * Modify: dst file name => add RGB info
 
     **************************************/
    file_dst = modify_DstFileName_Histo_RGB(file_dst, opt_RGB);
    
    //log
    printf("[%s : %d] file_dst => modified: %s\n", 
            base_name(__FILE__), __LINE__, file_dst);

    
    /*************************************
 
     * vars
 
     **************************************/
//    int x, y;
//
//    // A
//    int width_A, height_A; int number_of_passes_A;
//    png_byte color_type_A, bit_depth_A;
//
//    png_structp png_ptr_A; png_infop info_ptr_A;
//    
//    // B
//    int width_B, height_B; int number_of_passes_B;
//    png_byte color_type_B, bit_depth_B;
//
//    png_structp png_ptr_B; png_infop info_ptr_B;
//    
//    // C
//    int width_C, height_C; int number_of_passes_C;
//    png_byte color_type_C, bit_depth_C;
//
//    png_structp png_ptr_C; png_infop info_ptr_C;
    
    /*************************************
 
     * setup: vars
 
     **************************************/
    _Mode_Histo__Setup_Vars(argc, argv);
    
//    // png_ptr_A
//    png_ptr_A = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//
//    if (!png_ptr_A)
//            abort_("[read_png_file] png_create_read_struct failed");
//    
//    // info_ptr_A
//    info_ptr_A = png_create_info_struct(png_ptr_A);
//    if (!info_ptr_A)
//            abort_("[read_png_file] png_create_info_struct failed");
//
//    // png_ptr_B
//    png_ptr_B = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//
//    if (!png_ptr_B)
//            abort_("[read_png_file] png_create_read_struct failed");
//    
//    // info_ptr_B
//    info_ptr_B = png_create_info_struct(png_ptr_B);
//    if (!info_ptr_B)
//            abort_("[read_png_file] png_create_info_struct failed");
//
//    // png_ptr_C
//    png_ptr_C = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//
//    if (!png_ptr_C)
//            abort_("[read_png_file] png_create_read_struct failed");
//    
//    // info_ptr_C
//    info_ptr_C = png_create_info_struct(png_ptr_C);
//    if (!info_ptr_C)
//            abort_("[read_png_file] png_create_info_struct failed");
//
//    consolColor_Change(LIGHT_YELLOW);
//
//    //log
//    printf("[%s : %d] setup: vars => done\n", base_name(__FILE__), __LINE__);
//
//    consolColor_Reset();    

    /*************************************
 
     * Get: png info
 
     **************************************/
    get_PngInfo
    (file_src, png_ptr_A, info_ptr_A,
        &width_A, &height_A, &number_of_passes_A,
        &color_type_A, &bit_depth_A);
    
    
    //log
    printf("[%s : %d] info_ptr_A->width => %d\n", 
            base_name(__FILE__), __LINE__, info_ptr_A->width);

    /*************************************
 
     * read png
 
     **************************************/
    _test_ReadPng__Process
    (file_src, png_ptr_A, info_ptr_A,
        &width_A, &height_A, &number_of_passes_A,
            &color_type_A, &bit_depth_A);

    consolColor_Change(LIGHT_YELLOW);

//    //log
//    printf("[%s : %d] read png => done\n", base_name(__FILE__), __LINE__);

    consolColor_Reset();
    
    //log
    printf("[%s : %d] png_ptr_A->width => %d\n", 
            base_name(__FILE__), __LINE__, png_ptr_A->width);
    printf("[%s : %d] width_A => %d\n", 
            base_name(__FILE__), __LINE__, width_A);

    /**************************
     * Get: histo data
     **************************/
    gen_HistoData_RGB(width_A, height_A, opt_RGB);
//    gen_HistoData(width_A, height_A);
    
    consolColor_Change(LIGHT_YELLOW);

    //log
    printf("[%s : %d] gen_HistoData => done\n",
            base_name(__FILE__), __LINE__);

    consolColor_Reset();
    
    //log
    printf("[%s : %d] histo_range[0], histo_range[1] => %d, %d\n", 
            base_name(__FILE__), __LINE__, histo_range[0], histo_range[1]);

    /*************************************
 
     * Build: dst png: info
     * 
     * 1. color type => use that of file A
     * 2. depth => same as 1
 
     **************************************/
    _Mode_Histo__DstPNG_Info();
    
//    if(opt_merge_direc == 1) {          // 1: horizontal
        
//    // png_ptr_B
//    width_B = histo_png_size[0];
//    height_B = histo_png_size[1];
////    width_B = width_A;
////    height_B = height_A;
////    height_C = height_A + height_B;
//
//    color_type_B = color_type_A;
//    bit_depth_B = bit_depth_A;
//
//    png_ptr_B->width = width_B;
//    png_ptr_B->height = height_B;
//    png_ptr_B->color_type = color_type_B;
//    
////    info_ptr_B->rowbytes = info_ptr_A->rowbytes;
//    info_ptr_B->rowbytes = width_B * 3;
//    png_ptr_B->rowbytes = info_ptr_B->rowbytes;
//    
//    // png_ptr_C
//    width_C = histo_png_size[0];
//    height_C = histo_png_size[1];
////    width_C = width_A;
////    height_C = height_A;
////    height_C = height_A + height_C;
//
//    color_type_C = color_type_A;
//    bit_depth_C = bit_depth_A;
//
//    png_ptr_C->width = width_C;
//    png_ptr_C->height = height_C;
//    png_ptr_C->color_type = color_type_C;
//    
////    info_ptr_C->rowbytes = info_ptr_A->rowbytes;
//    info_ptr_C->rowbytes = width_C * 3;
//    png_ptr_C->rowbytes = info_ptr_C->rowbytes;
//    
//    //log
//    printf("[%s : %d] info_ptr_B->rowbytes => %d\n", 
//            base_name(__FILE__), __LINE__, info_ptr_B->rowbytes);
//
//
//    // png_ptr_A
//    png_ptr_A->width = width_A;
//    png_ptr_A->height = height_A;
//    png_ptr_A->color_type = color_type_A;
    
//    //log
//    printf("[%s : %d] png_ptr_A: width, height => %d, %d\n", 
//            base_name(__FILE__), __LINE__, png_ptr_A->width, png_ptr_A->height);
//    printf("[%s : %d] width_A => %d\n", 
//            base_name(__FILE__), __LINE__, width_A);
//    
//    printf("[%s : %d] png_ptr_B: width, height => %d, %d\n", 
//            base_name(__FILE__), __LINE__, png_ptr_B->width, png_ptr_B->height);
//    printf("[%s : %d] width_B => %d\n", 
//            base_name(__FILE__), __LINE__, width_B);
    
    /**************************
     * Build: dst png: pixels
     * 
     * 
     **************************/
    char *bg_color_name = "gray";
//    char *bg_color_name = "white";
    
    init_Row_Pointers_B__Histo(png_ptr_B, info_ptr_B, bg_color_name);

    //log
    printf("[%s : %d] png_ptr_B->rowbytes => %d\n", 
            base_name(__FILE__), __LINE__, png_ptr_B->rowbytes);
    printf("[%s : %d] info_ptr_B->rowbytes => %d\n", 
            base_name(__FILE__), __LINE__, info_ptr_B->rowbytes);

    
    /**************************
     * Get: Histo pixels
     **************************/
    gen_HistoPixels_RGB(opt_RGB);
//    gen_HistoPixels();
            
    consolColor_Change(LIGHT_YELLOW);

    //log
    printf("[%s : %d] gen_HistoPixels() => done\n",
            base_name(__FILE__), __LINE__);

    consolColor_Reset();

    
    
    /*************************************
 
     * write png
 
     **************************************/
//    writePNG_Histo
//    (file_dst, png_ptr_B, info_ptr_B,
//        &width_B, &height_B,
//        &color_type_B, &bit_depth_B, opt_RGB);
    _test_WritePng__Process
    (file_dst, png_ptr_B, info_ptr_B,
        &width_B, &height_B,
        &color_type_B, &bit_depth_B);
    
    
    
//    _test_WritePng_Rgba
//    (file_path_dst, png_ptr_Dst, info_ptr_Dst,
//        &width_Dst, &height_Dst,
//        &color_type_Dst, &bit_depth_Dst);

    consolColor_Change(LIGHT_YELLOW);

    //log
    printf("[%s : %d] _test_WritePng() => done\n", base_name(__FILE__), __LINE__);
    

    consolColor_Reset();
    
    /**************************
     * Write: Execution info
     **************************/
    _Mode_Histo__Write_ExecInfo(argc, argv);

    /**************************
     * Last message
     **************************/
    //log
    printf("[%s : %d] done => Mode_Histo\n", base_name(__FILE__), __LINE__);
    
//    char *label_1 = "<Dst file name>";
//    char *label_2 = "<Src file name>";
//    
//    int len_1 = strlen(label_1) + strlen(file_dst);
//    int len_2 = strlen(label_2) + strlen(file_src);
//    
//    char *message_1 = (char *) malloc(sizeof(char) * (len_1 + 2));
//    char *message_2 = (char *) malloc(sizeof(char) * (len_2 + 2));
//    
//    sprintf(message_1, "%s %s\n", label_1, file_dst);
//    sprintf(message_2, "%s %s\n", label_2, file_src);
//    
////    char *message = concat("<Dst file name> ", file_dst);
//    
//    
//    char *message = concat(message_1, message_2);
//    
//    // write_log => methods.c
//    write_Log(__FILE__, __LINE__, message);

    
}//void Mode_Histo(int argc, char **argv)

void _Mode_Histo__GetFileNames(int argc, char **argv)
{
    /**************************
     * Get: Source PNG file
     **************************/
    file_src = (char *) _setup_FileName_Src__Process(argc, argv);
//    char *file_src = (char *) _setup_FileName_Src__Process(argc, argv);
    
    consolColor_Change(GREEN);

    //log
    printf("[%s : %d] file_src => %s\n", base_name(__FILE__), __LINE__, file_src);

    consolColor_Reset();
    
    
    /**************************
     * Get: dst PNG file
     **************************/
    file_dst = (char *) _setup_FileName_Dst__Histo(argc, argv);
//    char *file_dst = (char *) _setup_FileName_Dst__Histo(argc, argv);
    
    consolColor_Change(GREEN);

    //log
    printf("[%s : %d] file_dst => %s\n", base_name(__FILE__), __LINE__, file_dst);

    consolColor_Reset();
        
}

void _Mode_Histo__DstPNG_Info(void)
{
    // png_ptr_B
    width_B = histo_png_size[0];
    height_B = histo_png_size[1];
//    width_B = width_A;
//    height_B = height_A;
//    height_C = height_A + height_B;

    color_type_B = color_type_A;
    bit_depth_B = bit_depth_A;

    png_ptr_B->width = width_B;
    png_ptr_B->height = height_B;
    png_ptr_B->color_type = color_type_B;
    
//    info_ptr_B->rowbytes = info_ptr_A->rowbytes;
    info_ptr_B->rowbytes = width_B * 3;
    png_ptr_B->rowbytes = info_ptr_B->rowbytes;
    
    // png_ptr_C
    width_C = histo_png_size[0];
    height_C = histo_png_size[1];
//    width_C = width_A;
//    height_C = height_A;
//    height_C = height_A + height_C;

    color_type_C = color_type_A;
    bit_depth_C = bit_depth_A;

    png_ptr_C->width = width_C;
    png_ptr_C->height = height_C;
    png_ptr_C->color_type = color_type_C;
    
//    info_ptr_C->rowbytes = info_ptr_A->rowbytes;
    info_ptr_C->rowbytes = width_C * 3;
    png_ptr_C->rowbytes = info_ptr_C->rowbytes;
    
    //log
    printf("[%s : %d] info_ptr_B->rowbytes => %d\n", 
            base_name(__FILE__), __LINE__, info_ptr_B->rowbytes);


    // png_ptr_A
    png_ptr_A->width = width_A;
    png_ptr_A->height = height_A;
    png_ptr_A->color_type = color_type_A;    
}//void _Mode_Histo__DstPNG_Info(void)
    
void _Mode_Histo__Setup_Vars(int argc, char **argv)
{
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
    
}//void _Mode_Histo__Setup_Vars(int argc, char **argv)

void _Mode_Histo__Option_RGB(int argc, char **argv)
{
    const char *opt_label_RGB = "-rgb";
    
    opt_RGB = get_Opt_Value(argv, opt_label_RGB);
//    char *opt_RGB = get_Opt_Value(argv, opt_label_RGB);
//    char *opt_RGB = get_Opt_Value(argv, "-rgb");

    consolColor_Change(LIGHT_YELLOW);

    //log
    printf("[%s : %d] rgb option => %s\n",
            base_name(__FILE__), __LINE__, opt_RGB);

    consolColor_Reset();    
}

void _Mode_Histo__Write_ExecInfo
(int argc, char **argv)
{
    char *label_1 = "<Dst file name>";
    char *label_2 = "<Src file name>";
    
    int len_1 = strlen(label_1) + strlen(file_dst);
    int len_2 = strlen(label_2) + strlen(file_src);
    
    char *message_1 = (char *) malloc(sizeof(char) * (len_1 + 2));
    char *message_2 = (char *) malloc(sizeof(char) * (len_2 + 2));
    
    sprintf(message_1, "%s %s\n", label_1, file_dst);
    sprintf(message_2, "%s %s\n", label_2, file_src);
    
//    char *message = concat("<Dst file name> ", file_dst);
    
    
    char *message = concat(message_1, message_2);
    
    // write_log => methods.c
    write_Log(__FILE__, __LINE__, message);
    
}
