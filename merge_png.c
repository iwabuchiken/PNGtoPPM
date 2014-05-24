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
//#include "include/pnglib.h"
#include "include/pnglib.h"
//#include "include/pnglib.h"
#include "include/pnginfo.h"
#endif

/**************************
 * Global vars
 **************************/
int Opt_Merge_Direction = 0;    // 0: vertical, 1: horizontal
char *opt_bg_color; // background color
char *opt_bg_color_Default = "blue"; // background color

//const char *bg_colors = {
char *bg_colors[] = {
    
    "red", "blue", "green", "purple",
    "white", "black"
    
};

const int bg_colors_len = 4;    // length of bg_colors

char *direc[] = {
  
    "verti", "hori"
    
};

int opt_merge_direc = 0;        // option: merge direction
                                // 0: vertical, 1: horizontal
                                // default => 0


char *file_dst;

int RGB[3];

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

void set_Options(char **);
void set_Options_BgColor(char **);
void set_Options_MergeDirec(char **);

int _Is_ProcessMode(int, char **);
void process_Mode(int, char **);
void set_Options_Process(char **);
int set_Options_Process_RGB(char **);
char * _setup_FileName_Src__Process(int, char **);
char * _setup_FileName_Dst__Process(int, char **);

/*************************************
 
 * global vars
 
 **************************************/
extern png_bytep * row_pointers;
extern png_bytep * row_pointers_RGBA;

// merge_png.c
extern png_bytep * row_pointers_A;
extern png_bytep * row_pointers_B;
extern png_bytep * row_pointers_C;

/**************************
 * main()
 * 
 * exit -3      => unknown opt_merge_direc value
 * exit -1      => values not given for \"-rgb\" option
 * 
 **************************/

int main(int argc, char** argv) {

    /*************************************
 
     * validate
 
     **************************************/
    if (argc < 4) {
        
        show_help();
        
        return 0;
    }
    
    /**************************
     * Processing mode?
     **************************/
    int res_i = _Is_ProcessMode(argc, argv);
    
    if(res_i == true) {
        
        process_Mode(argc, argv);
        
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
    
    /**************************
     * Options
     **************************/
    set_Options(argv);
    
//    exit(1);
    
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
    file_dst = _setup_FileName_Dst(argc, argv);
//    char *file_dst = _setup_FileName_Dst(argc, argv);
    
    consolColor_Change(GREEN);
    
    //log
    printf("[%s : %d] file_dst = %s\n",
            base_name(__FILE__), __LINE__, file_dst);

    consolColor_Reset();
    
//    //test
//    exit(-1);
    
//    //test
////    char joint = '.';
//    char *tmp = join_simple(bg_colors, (sizeof(bg_colors) / sizeof(char *)));
////    char *tmp = join(joint, bg_colors, (sizeof(bg_colors) / sizeof(char *)));
////    char *tmp = join(joint, direc, (sizeof(direc) / sizeof(char *)));
//    
//    //log
//    printf("[%s : %d] join(bg_colors) => %s\n", base_name(__FILE__), __LINE__, tmp);
////    printf("[%s : %d] join(direc) => %s\n", base_name(__FILE__), __LINE__, tmp);
//
//    
//    exit(0);
    
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
    
    /*************************************
 
     * tests
 
     **************************************/
    
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

    /*************************************
 
     * Build: dst png info
     * 
     * 1. color type => use that of file A
     * 2. depth => same as 1
 
     **************************************/
    if(opt_merge_direc == 1) {          // 1: horizontal
        
        width_C = width_A + width_B;
        height_C = larger(height_A, height_B);
    //    height_C = height_A + height_B;

        color_type_C = color_type_A;
        bit_depth_C = bit_depth_A;

        png_ptr_C->width = width_C;
        png_ptr_C->height = height_C;

        png_ptr_C->color_type = png_ptr_A->color_type;
        png_ptr_C->bit_depth = png_ptr_A->bit_depth;

        png_ptr_C->rowbytes = png_ptr_A->rowbytes + png_ptr_B->rowbytes;
        info_ptr_C->rowbytes = info_ptr_A->rowbytes + info_ptr_B->rowbytes;
        
    } else if(opt_merge_direc == 0) {   // 0: vertical
        
        width_C = larger(width_A, width_B);
        height_C = height_A + height_B;
    //    height_C = height_A + height_B;

        color_type_C = color_type_A;
        bit_depth_C = bit_depth_A;

        png_ptr_C->width = width_C;
        png_ptr_C->height = height_C;

        png_ptr_C->color_type = png_ptr_A->color_type;
        png_ptr_C->bit_depth = png_ptr_A->bit_depth;

        png_ptr_C->rowbytes = png_ptr_A->rowbytes + png_ptr_B->rowbytes;
        info_ptr_C->rowbytes = info_ptr_A->rowbytes + info_ptr_B->rowbytes;
    }
//    width_C = width_A + width_B;
//    height_C = larger(height_A, height_B);
////    height_C = height_A + height_B;
//    
//    color_type_C = color_type_A;
//    bit_depth_C = bit_depth_A;
//    
//    png_ptr_C->width = width_C;
//    png_ptr_C->height = height_C;
//    
//    png_ptr_C->color_type = png_ptr_A->color_type;
//    png_ptr_C->bit_depth = png_ptr_A->bit_depth;
//    
//    png_ptr_C->rowbytes = png_ptr_A->rowbytes + png_ptr_B->rowbytes;
//    info_ptr_C->rowbytes = info_ptr_A->rowbytes + info_ptr_B->rowbytes;
    
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
     * 
     * file: pnglib.c
 
     **************************************/
    init_Row_Pointers_C(png_ptr_C, info_ptr_C, opt_bg_color);
//    init_Row_Pointers_C(png_ptr_C, info_ptr_C);

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
 
     * copy: png A to png C
 
     **************************************/
//    merge_PngSrcs(
    // 1: hori, 0: verti
    if(opt_merge_direc == 1) {          // 1: horizontal
        
        merge_PngSrcs_Hori_General(
                width_A, height_A,
                width_B, height_B,
                width_C, height_C
                );
        
    } else if(opt_merge_direc == 0) {   // 0: vertical
        
        merge_PngSrcs_Verti_General(
                width_A, height_A,
                width_B, height_B,
                width_C, height_C
                );
        
    } else {
        
        //log
        printf("[%s : %d] Unknown direction value => %d\n", 
                base_name(__FILE__), __LINE__, opt_merge_direc);

        exit(-3);
        
    }
    
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

/**************************
 * _setup_FileName_Dst()
 * 
 * @return 1. option-info-appended string
 *        2. argv[3] => if tokenizing failed
 **************************/
char * _setup_FileName_Dst(int argc, char **argv)
{
    
    char *dst = (char *) malloc(sizeof(char) * (strlen(argv[3]) + 1));
    
    strcpy(dst, argv[3]);
    dst[strlen(argv[3])] = '\0';
    
    /**************************
     * Add info: bg_color
     **************************/
    char delim = '.';
    int *num_of_tokens;
    int position = 1;
    
    char **tokens = str_split_r_2
                (dst, delim, position, num_of_tokens);
    
//    free(dst);
    
    if (tokens != NULL) {

        //log
        printf("[%s : %d] tokens[0] = %s / tokens[1] = %s\n", 
                base_name(__FILE__), __LINE__, tokens[0], tokens[1]);
        
        free(dst);
        
        char *label = "_bg=";
        char *bg_info = concat(label, opt_bg_color);
        
        // direction
        label = "_direc=";
        char *direc_info = concat(label, direc[opt_merge_direc]);
        
        //log
        printf("[%s : %d] bg_info => %s\n", base_name(__FILE__), __LINE__, bg_info);

        int size = 5;
        
        char **tmp = (char **) malloc(sizeof(char *) * size);
//        char **tmp = (char **) malloc(sizeof(char *) * 4);
        
        char *joint_str = ".";
        
        tmp[0] = tokens[0];
        tmp[1] = bg_info;
        tmp[2] = direc_info;
        tmp[3] = joint_str;
        tmp[4] = tokens[1];

//        //log
//        printf("[%s : %d] tmp[1] => %s\n", base_name(__FILE__), __LINE__, tmp[1]);
//        
//        int size = sizeof(char *);
////        int size = sizeof(tmp);
////        int size = (sizeof(tmp) / sizeof(char *));
//        
//        //log
//        printf("[%s : %d] size => %d\n", base_name(__FILE__), __LINE__, size);

        
        char *tmp_str = join_simple(tmp, size);
//        char *tmp_str = join_simple(tmp, 4);
//        char *tmp_str = join_simple(tmp, (sizeof(tmp) / sizeof(char *)));
        
        //log
        printf("[%s : %d] tmp_str => %s\n", base_name(__FILE__), __LINE__, tmp_str);
        
        dst = tmp_str;
        
//        return dst;
//        return tmp_str;

        
    } else {
        
        //log
        printf("[%s : %d] tokens => NULL\n", base_name(__FILE__), __LINE__);
        
        dst = argv[3];
        
//        return dst;
//        return argv[3];

    }
    
    /**************************
     * Add info: direction
     **************************/
    
    
    return dst;
    
//    return dst;
    
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

char * _setup_FileName_Src__Process(int argc, char **argv)
{
    char *file_src;
    
    int i = 0;
    int flag = false;   // true if "-rgb" values given
    
    while(*(argv + i) != NULL) {
        
        if(!strcmp(*(argv + i), "-src")) {
            
            i ++;
            
            if(*(argv + i) != NULL) {
                
                int len = strlen(*(argv + i));
                
                file_src = (char *) malloc(sizeof(char) * (len + 1));
                
                strcpy(file_src, *(argv + i));
                
                file_src[len] = '\0';
                
                flag = true;
                
                break;
                
            } else {
                
                //log
                printf("[%s : %d] value not given for \"-src\"\n", 
                        base_name(__FILE__), __LINE__);

                exit(-1);
                
            }
            
        }
        
        i ++;
        
    }//while(*(argv + i) != NULL)

    if(flag == false) {
        
        //log
        printf("[%s : %d] \"-src\" option not given\n", base_name(__FILE__), __LINE__);
        
        exit(-1);

    }
    
    // return
    return file_src;
    
}

char * _setup_FileName_Dst__Process(int argc, char **argv)
{
    char *file_dst;
    
    int i = 0;
    int flag = false;   // true if "-rgb" values given
    
    while(*(argv + i) != NULL) {
        
        if(!strcmp(*(argv + i), "-dst")) {
            
            i ++;
            
            if(*(argv + i) != NULL) {
                
                int len = strlen(*(argv + i));
                
                file_dst = (char *) malloc(sizeof(char) * (len + 1));
                
                strcpy(file_dst, *(argv + i));
                
                file_dst[len] = '\0';
                
                flag = true;
                
                break;
                
            } else {
                
                //log
                printf("[%s : %d] value not given for \"-src\"\n", 
                        base_name(__FILE__), __LINE__);

                exit(-1);
                
            }
            
        }
        
        i ++;
        
    }//while(*(argv + i) != NULL)

    if(flag == false) {
        
        //log
        printf("[%s : %d] \"-dst\" option not given\n", base_name(__FILE__), __LINE__);
        
        exit(-1);

    }
    
    /**************************
     * Add info: RGB
     **************************/
    char delim = '.';
    int *num_of_tokens;
    int position = 1;
    
    char **tokens = str_split_r_2
                (file_dst, delim, position, num_of_tokens);
    
    if (tokens != NULL) {

        //log
        printf("[%s : %d] tokens[0] = %s / tokens[1] = %s\n", 
                base_name(__FILE__), __LINE__, tokens[0], tokens[1]);
        
        free(file_dst);
        
        char *label = "_rgb=";
        
        char *rgb_info = (char *) malloc(sizeof(char) * (11 + 1));
        
        sprintf(rgb_info, "%d,%d,%d", RGB[0], RGB[1], RGB[2]);
        
        rgb_info = concat(label, rgb_info);
//        char *bg_info = concat(label, opt_bg_color);
        
//        // direction
//        label = "_direc=";
//        char *direc_info = concat(label, direc[opt_merge_direc]);
//        
//        //log
//        printf("[%s : %d] bg_info => %s\n", base_name(__FILE__), __LINE__, bg_info);

        int size = 4;
        
        char **tmp = (char **) malloc(sizeof(char *) * size);
//        char **tmp = (char **) malloc(sizeof(char *) * 4);
        
        char *joint_str = ".";
        
        tmp[0] = tokens[0];
        tmp[1] = rgb_info;
        tmp[2] = joint_str;
        tmp[3] = tokens[1];
        
        char *tmp_str = join_simple(tmp, size);
//        char *tmp_str = join_simple(tmp, 4);
//        char *tmp_str = join_simple(tmp, (sizeof(tmp) / sizeof(char *)));
        
        //log
        printf("[%s : %d] tmp_str => %s\n", base_name(__FILE__), __LINE__, tmp_str);
        
        file_dst = tmp_str;
        
//        return dst;
//        return tmp_str;

        
    } else {
        
        consolColor_Change(RED);

        //log
        printf("[%s : %d] tokens => NULL\n",
                base_name(__FILE__), __LINE__);

        consolColor_Reset();
        
        exit(-1);
        
//        return dst;
//        return argv[3];

    }
    
    // return
    return file_dst;
    
}

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
    
    ;


    consolColor_Change(LIGHT_BLUE);
    
    //log
    printf("[%s : %d]\n%s\n", base_name(__FILE__), __LINE__, msg);

    consolColor_Reset();
    
}

void set_Options(char **argv)
{
    while(*argv != NULL) {
        
        if (!strcmp(*argv, "-bg")) {
            
            set_Options_BgColor(argv);
            
            
        } else if (!strcmp(*argv, "-direc")) {
            
            set_Options_MergeDirec(argv);
            
        }//if (!strcmp(*argv, "-bg"))

        argv++;
    }
    
    /**************************
     * Default: opt_bg_color
     **************************/
    if (opt_bg_color == NULL) {

        int len = strlen(opt_bg_color_Default);
        
        opt_bg_color = (char *) malloc(sizeof(char) * (len + 1));
        
        strcpy(opt_bg_color, opt_bg_color_Default);
        
        opt_bg_color[len] = '\0';
        
    }
    
}

void set_Options_BgColor(char **argv)
{
    argv++;

    /**************************
     * Validate: Value for '-bg' option
     **************************/
    if(*argv == NULL) {
        //log
        printf("[%s : %d] no value set for option '-bg'\n", 
                base_name(__FILE__), __LINE__);

        exit(-1);
    }
    
    /**************************
     * Validate: The value is in the bg_colors?
     **************************/
    int res_i = is_InArray(*argv, bg_colors, sizeof(bg_colors) / sizeof(char *));
//    int res_i = is_InArray(*argv, bg_colors, 3);
    
    if(res_i == false) {
        
        //log
        printf("[%s : %d] Unknown color name => %s\n", base_name(__FILE__), __LINE__, *argv);
        
        exit(-1);

    } else {
        
        //log
        printf("[%s : %d] res_i => %d\n", base_name(__FILE__), __LINE__, res_i);
        
    }
    
    int len = strlen(*argv);

    opt_bg_color = (char *) malloc(sizeof(char) * (len + 1));

    strcpy(opt_bg_color, *argv);
    opt_bg_color[len] = '\0';

    //log
    printf("[%s : %d] opt_bg_color => %s\n", base_name(__FILE__), __LINE__, opt_bg_color);
            
}//void set_Options_BgColor(char **argv)

void set_Options_MergeDirec(char **argv)
{
    argv++;

    /**************************
     * Validate: Value for '-bg' option
     **************************/
    if(*argv == NULL) {
        //log
        printf("[%s : %d] no value set for option '-direc'\n", 
                base_name(__FILE__), __LINE__);

        exit(-1);
    }
    
    /**************************
     * Validate: The value is in the bg_colors?
     **************************/
    int res_i = is_InArray(*argv, direc, sizeof(direc) / sizeof(char *));
//    int res_i = is_InArray(*argv, bg_colors, 3);
    
    if(res_i == false) {
        
        //log
        printf("[%s : %d] Unknown direction name => %s\n",
                base_name(__FILE__), __LINE__, *argv);
        
        exit(-1);

    } else {
        
        //log
        printf("[%s : %d] res_i => %d\n", base_name(__FILE__), __LINE__, res_i);
        
    }
    
    if(!strcmp(*argv, direc[0])) {      // vertical
        
        opt_merge_direc = 0;
        
    } else if(!strcmp(*argv, direc[1])) {       // horizontal
        
        opt_merge_direc = 1;
        
    }

    //log
    printf("[%s : %d] opt_merge_direc => %d\n", 
            base_name(__FILE__), __LINE__, opt_merge_direc);
    
}//void set_Options_MergeDirec(char

/**************************
 * _Is_ProcessMode(int argc, char **argv)
 * 
 * @return true => option "-proc" present
 *         false => not
 **************************/
int _Is_ProcessMode(int argc, char **argv)
{
    int i;
    
//    argv ++;
    
    for (i = 0; i < argc; i++) {

        if(!strcmp(*(argv + i), "-proc")) {
            
            return true;
            
        };

    }
    
    return false;

}//int _Is_ProcessMode(int argc, char **argv)

void process_Mode(int argc, char **argv)
{

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
    
    
    /**************************
     * Options
     **************************/
    set_Options_Process(argv);
    
    consolColor_Change(GREEN);
    
    //log
    printf("[%s : %d] RGB => set (%d,%d,%d)\n",
            base_name(__FILE__), __LINE__, RGB[0], RGB[1], RGB[2]);
    
    consolColor_Reset();
    
    /*************************************aaaaaa
 
     * Setup: source file path
 
     **************************************/
    char *file_src = _setup_FileName_Src__Process(argc, argv);
    
    consolColor_Change(GREEN);
    
    //log
    printf("[%s : %d] file_src = %s\n",
            base_name(__FILE__), __LINE__, file_src);
    
    consolColor_Reset();
    
    /*************************************
 
     * Setup: dst file path
 
     **************************************/
    file_dst = _setup_FileName_Dst__Process(argc, argv);
//    char *file_dst = _setup_FileName_Dst(argc, argv);
    
    consolColor_Change(GREEN);
    
    //log
    printf("[%s : %d] file_dst = %s\n",
            base_name(__FILE__), __LINE__, file_dst);

    consolColor_Reset();
    
//    /*************************************
// 
//     * Get: png info
// 
//     **************************************/
//    get_PngInfo
//    (file_src, png_ptr_A, info_ptr_A,
//        &width_A, &height_A, &number_of_passes_A,
//        &color_type_A, &bit_depth_A);
//    
//    
//    //log
//    printf("[%s : %d] info_ptr_A->width => %d\n", 
//            base_name(__FILE__), __LINE__, info_ptr_A->width);

    
//    get_PngInfo
//    (file_srcs[1], png_ptr_B, info_ptr_B,
//        &width_B, &height_B, &number_of_passes_B,
//        &color_type_B, &bit_depth_B);
    
//    /*************************************
// 
//     * tests
// 
//     **************************************/
//    
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

            
    consolColor_Change(LIGHT_YELLOW);

    //log
    printf("[%s : %d] setup: vars => done\n", base_name(__FILE__), __LINE__);

    consolColor_Reset();
//   
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

    //log
    printf("[%s : %d] png_ptr_A->width => %d\n", 
            base_name(__FILE__), __LINE__, png_ptr_A->width);
    printf("[%s : %d] width_A => %d\n", 
            base_name(__FILE__), __LINE__, width_A);

    
    consolColor_Reset();

    /*************************************
 
     * Build: dst png info
     * 
     * 1. color type => use that of file A
     * 2. depth => same as 1
 
     **************************************/
//    if(opt_merge_direc == 1) {          // 1: horizontal
        
    // png_ptr_B
    width_B = width_A;
    height_B = height_A;
//    height_C = height_A + height_B;

    color_type_B = color_type_A;
    bit_depth_B = bit_depth_A;

    png_ptr_B->width = width_B;
    png_ptr_B->height = height_B;
    png_ptr_B->color_type = color_type_B;
    
    info_ptr_B->rowbytes = info_ptr_A->rowbytes;

    // png_ptr_A
    png_ptr_A->width = width_A;
    png_ptr_A->height = height_A;
    png_ptr_A->color_type = color_type_A;
    
//    info_ptr_B->rowbytes = info_ptr_A->rowbytes;

//    png_ptr_C->color_type = png_ptr_A->color_type;
//    png_ptr_C->bit_depth = png_ptr_A->bit_depth;
//
//    png_ptr_C->rowbytes = png_ptr_A->rowbytes + png_ptr_B->rowbytes;
        
    
//    //log
//    printf("[%s : %d] png_ptr_A->width, png_ptr_A->height => %d, %d\n", 
//            base_name(__FILE__), __LINE__, png_ptr_A->width, png_ptr_A->height);
//    printf("[%s : %d] png_ptr_B->width, png_ptr_B->height => %d, %d\n", 
//            base_name(__FILE__), __LINE__, png_ptr_B->width, png_ptr_B->height);
//    printf("[%s : %d] info_ptr_B->rowbytes => %d\n", 
//            base_name(__FILE__), __LINE__, info_ptr_B->rowbytes);
//    
//    printf("[%s : %d] png_ptr_B->color_type => %d\n", 
//            base_name(__FILE__), __LINE__, png_ptr_B->color_type);
//    printf("[%s : %d] color_type_B => %d\n", 
//            base_name(__FILE__), __LINE__, color_type_B);
    
    
    init_Row_Pointers_B(png_ptr_B, info_ptr_B);
    
    
//    } else if(opt_merge_direc == 0) {   // 0: vertical
//        
//        width_C = larger(width_A, width_B);
//        height_C = height_A + height_B;
//    //    height_C = height_A + height_B;
//
//        color_type_C = color_type_A;
//        bit_depth_C = bit_depth_A;
//
//        png_ptr_C->width = width_C;
//        png_ptr_C->height = height_C;
//
//        png_ptr_C->color_type = png_ptr_A->color_type;
//        png_ptr_C->bit_depth = png_ptr_A->bit_depth;
//
//        png_ptr_C->rowbytes = png_ptr_A->rowbytes + png_ptr_B->rowbytes;
//        info_ptr_C->rowbytes = info_ptr_A->rowbytes + info_ptr_B->rowbytes;
//    }

    /*************************************
 
     * process file
 
     **************************************/
    //log
    ProcMode process_mode = rgb;
    
    process_file__RGB(png_ptr_A, png_ptr_B, RGB, process_mode);
//     process_file(width, height);
    
    consolColor_Change(LIGHT_YELLOW);

    //log
    printf("[%s : %d] process => done\n",
            base_name(__FILE__), __LINE__);

    consolColor_Reset();
    
    
    
//     //log
//    printf("[%s : %d] process => done\n", base_name(__FILE__), __LINE__);

//    /*************************************
// 
//     * init: row_pointers_C (dst png)
//     * 
//     * file: pnglib.c
// 
//     **************************************/
//    init_Row_Pointers_C(png_ptr_C, info_ptr_C, opt_bg_color);
////    init_Row_Pointers_C(png_ptr_C, info_ptr_C);
//
//    //log
//    printf("[%s : %d] png_ptr_C->width, png_ptr_C->height => %d, %d\n",
//            base_name(__FILE__), __LINE__, png_ptr_C->width, png_ptr_C->height);
//    printf("[%s : %d] png_ptr_C->rowbytes => %d\n",
//            base_name(__FILE__), __LINE__, png_ptr_C->rowbytes);
//    printf("[%s : %d] png_ptr_A->rowbytes, png_ptr_B->rowbytes => %d, %d\n",
//            base_name(__FILE__), __LINE__,
//            png_ptr_A->rowbytes,
//            png_ptr_B->rowbytes
//            );
//
//    
//    //log
//    printf("[%s : %d] Back from => init_Row_Pointers_C()\n", base_name(__FILE__), __LINE__);
//
//    /*************************************
// 
//     * copy: png A to png C
// 
//     **************************************/
////    merge_PngSrcs(
//    // 1: hori, 0: verti
//    if(opt_merge_direc == 1) {          // 1: horizontal
//        
//        merge_PngSrcs_Hori_General(
//                width_A, height_A,
//                width_B, height_B,
//                width_C, height_C
//                );
//        
//    } else if(opt_merge_direc == 0) {   // 0: vertical
//        
//        merge_PngSrcs_Verti_General(
//                width_A, height_A,
//                width_B, height_B,
//                width_C, height_C
//                );
//        
//    } else {
//        
//        //log
//        printf("[%s : %d] Unknown direction value => %d\n", 
//                base_name(__FILE__), __LINE__, opt_merge_direc);
//
//        exit(-3);
//        
//    }
//    
    /*************************************
 
     * write png
 
     **************************************/
    _test_WritePng__Process
    (file_dst, png_ptr_B, info_ptr_B,
        &width_B, &height_B,
        &color_type_B, &bit_depth_B);
    
//    _test_WritePng_Rgba
//    (file_path_dst, png_ptr_Dst, info_ptr_Dst,
//        &width_Dst, &height_Dst,
//        &color_type_Dst, &bit_depth_Dst);
    
    //log
    printf("[%s : %d] _test_WritePng() => done\n", base_name(__FILE__), __LINE__);

    
    //log
    printf("[%s : %d] done\n", base_name(__FILE__), __LINE__);

    
//    return (EXIT_SUCCESS);    
}//void process_Mode(int argc, char **argv)

void set_Options_Process(char **argv)
{
    /**************************
     * vars
     **************************/
    int i = 0;    
    int flag_RGB = false;   // true if the rgb option is set
    
    while(*(argv + i) != NULL) {
        
        if (!strcmp(*(argv + i), "-rgb")) {
            
            int res = set_Options_Process_RGB(argv);
            
        }

        argv++;
    
    }
    
    
    
}

/**************************
 * set_Options_Process_RGB(char **argv)
 * 
 * @process
 *      1. If "-rgb" option     => set RGB vars with the arguement values
 *      2. If not               => set to the default: 100,100,100
 **************************/

int set_Options_Process_RGB(char **argv)
{
    int i = 0;
    int flag = false;   // true if "-rgb" values given
    
    while(*(argv + i) != NULL) {
        
        if(!strcmp(*(argv + i), "-rgb")) {
            
            i ++;       // next arguement to "-rgb" option
            
            if(*(argv + i) == NULL) {
                
                //log
                printf("[%s : %d] values not given for \"-rgb\" option\n", 
                        base_name(__FILE__), __LINE__);
                
                exit(-1);

            }
            
            flag = true;
            
            char delim = ',';
//            char delim = ",";
//            const char delim = ",";
            
            int num;
            
//            //log
//            printf("[%s : %d] *(argv + i) => %s\n", 
//                    base_name(__FILE__), __LINE__, *(argv + i));

            char **tokens = str_split_3(*(argv + i), delim, &num);
//            char *tokens = str_split_3(*(argv + i), delim, &num);
            
//            //log
//            printf("[%s : %d] back from => str_split_3()\n", 
//                    base_name(__FILE__), __LINE__);
            
            if(tokens == NULL) {
                
                //log
                printf("[%s : %d] split result => less than 1. Tokenize failed\n", 
                        base_name(__FILE__), __LINE__);

                exit(-1);
                
            } else if(num != 3) {//if(tokens == NULL)
                
                //log
                printf("[%s : %d] Irregular number of tokens => %d (arg = %s)\n", 
                        base_name(__FILE__), __LINE__, num, *(argv + i));
                
                exit(-1);
                
            }//if(tokens == NULL)
            
//            //log
//            printf("[%s : %d] num => %d\n", base_name(__FILE__), __LINE__, num);

            /**************************
             * Set: RGB values
             **************************/
            RGB[0] = atoi(tokens[0]);
            RGB[1] = atoi(tokens[1]);
            RGB[2] = atoi(tokens[2]);
            
            flag = true;
            
            break;
            
//            //log
//            printf("[%s : %d] tokens[0] => %s\n", 
//                    base_name(__FILE__), __LINE__, tokens[0]);
////                    base_name(__FILE__), __LINE__, tokens[0]);

        }//if(!strcmp(*(argv + i), "-rgb"))
        
        i ++;   // next arguement
        
    }//while(*(argv + i) != NULL)
    
    /**************************
     * Set: default
     **************************/
    if(flag == false) {
        
        RGB[0] = 100;
        RGB[1] = 100;
        RGB[2] = 100;
        
    }
    
    return flag;
//    return false;
    
}//void set_Options_Process_RGB(char **argv)
