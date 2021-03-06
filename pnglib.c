#ifndef PNGLIB_H
//#define	PNGLIB_H
#include "include/pnglib.h"
#include "include/pnginfo.h"
#endif

//char *bg_colors_2[6] = {
char *bg_colors_2[] = {
    
    "red", "blue", "green", "purple",
    "white", "black", "gray"

};

int histo_png_size[2] = {255, 255};     // width, height

// Historgram: which color element to use for a histogram PNG
char *Histo_RGB[] = {"R", "G", "B", "ALL"};
int Histo_RGB_len = 4;

void show_message_png()
{
    
    //log
    printf("[%s : %d] pnglib\n", base_name(__FILE__), __LINE__);

    
}

int lib_readpng_init(FILE *infile, ulg *pWidth, ulg *pHeight)
{

    uch sig[8];


    /* first do a quick check that the file really is a PNG image; could
     * have used slightly more general png_sig_cmp() function instead */

    fread(sig, 1, 8, infile);
    
    //log
    printf("[%s : %d] sig => %s\n", base_name(__FILE__), __LINE__, sig);

    int res_i = png_sig_cmp(sig, 0, 8);
    
    //log
    printf("[%s : %d] png_sig_cmp => %d\n", base_name(__FILE__), __LINE__, res_i);

    
    if (res_i)
//    if (png_sig_cmp(sig, 0, 8))
        return 1;   /* bad signature */

    
    
    return 0;
    
}

int lib_png_sig_cmp
(png_const_bytep sig, png_size_t start, png_size_t num_to_check)
{
   png_byte png_signature[8] = {137, 80, 78, 71, 13, 10, 26, 10};

   if (num_to_check > 8)
      num_to_check = 8;

   else if (num_to_check < 1)
      return (-1);

   if (start > 7)
      return (-1);

   if (start + num_to_check > 8)
      num_to_check = 8 - start;

//   //test
//   int i;
//   
//   for (i = 0; i < num_to_check; i++) {
//
//       //log
//        printf("[%s : %d] sig[%d] => %d (%%c=%c) / png_signature[%d] => %d\n", 
//                base_name(__FILE__), __LINE__, i, sig[i], sig[i], i, png_signature[i]);
//
//    }

   
   return ((int)(memcmp(&sig[start], &png_signature[start], num_to_check)));
}
//
/*************************************
void abort_(const char * s, ...)
 *  
 * message
 * REF http://zarb.org/~gc/html/libpng.html
 
 **************************************/
void abort_(const char * s, ...)
{
    //log
    printf("[%s : %d] aborting...\n", base_name(__FILE__), __LINE__);

    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
    
}
//
///*************************************
// * void read_png_file(char* file_name)
// *  
// * REF http://zarb.org/~gc/html/libpng.html
// 
// **************************************/
//void read_png_file
//(char* file_name, png_structp png_ptr,
//        png_infop info_ptr, png_bytep * row_pointers,
//        int *number_of_passes, int *width, int *height,
//        png_byte *color_type, png_byte *bit_depth)
//{
//        char header[8];    // 8 is the maximum size that can be checked
//
//        int x, y;
//        
//        /* open file and test for it being a png */
//        FILE *fp = fopen(file_name, "rb");
//        if (!fp)
//                abort_("[read_png_file] File %s could not be opened for reading", file_name);
//        fread(header, 1, 8, fp);
//        if (png_sig_cmp(header, 0, 8))
//                abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);
//
//
//        /* initialize stuff */
//        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//
//        if (!png_ptr)
//                abort_("[read_png_file] png_create_read_struct failed");
//
//        info_ptr = png_create_info_struct(png_ptr);
//        if (!info_ptr)
//                abort_("[read_png_file] png_create_info_struct failed");
//
//        if (setjmp(png_jmpbuf(png_ptr)))
//                abort_("[read_png_file] Error during init_io");
//
//        png_init_io(png_ptr, fp);
//        png_set_sig_bytes(png_ptr, 8);
//
//        png_read_info(png_ptr, info_ptr);
//
//        *width = png_get_image_width(png_ptr, info_ptr);
//        *height = png_get_image_height(png_ptr, info_ptr);
//        *color_type = png_get_color_type(png_ptr, info_ptr);
//        *bit_depth = png_get_bit_depth(png_ptr, info_ptr);
////        width = png_get_image_width(png_ptr, info_ptr);
////        height = png_get_image_height(png_ptr, info_ptr);
////        color_type = png_get_color_type(png_ptr, info_ptr);
////        bit_depth = png_get_bit_depth(png_ptr, info_ptr);
//
//        *number_of_passes = png_set_interlace_handling(png_ptr);
////        number_of_passes = png_set_interlace_handling(png_ptr);
//        png_read_update_info(png_ptr, info_ptr);
//
//
//        /* read file */
//        if (setjmp(png_jmpbuf(png_ptr)))
//                abort_("[read_png_file] Error during read_image");
//
//        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * (*height));
////        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
//        for (y=0; y < *height; y++)
////        for (y=0; y<height; y++)
//                row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
//
//        png_read_image(png_ptr, row_pointers);
//
//        fclose(fp);
//}
//
/*************************************
 *  void write_png_file()
 * 
 * char* file_name      => dst fine name
 * png_structp png_ptr  => empty pnt pointer
 * png_infop info_ptr   => empty info pointer
 * png_bytep * row_pointers     => value-carrying row pointers
 * int *height          => height of the png image
 
 **************************************/

void write_png_file
(char* file_name, png_structp png_ptr,
    png_infop info_ptr, png_bytep * row_pointers,
    int *width, int *height,
    png_byte *color_type, png_byte *bit_depth)
{
    int y;
    
    //log
    printf("[%s : %d] row_pointers[0][0] => %d\n",
            base_name(__FILE__), __LINE__, row_pointers[0][0]);

    
    /* create file */
    FILE *fp = fopen(file_name, "wb");
    if (!fp)
            abort_("[write_png_file] File %s could not be opened for writing", file_name);

    //log
    printf("[%s : %d] file => opened: %s\n", base_name(__FILE__), __LINE__, file_name);


    /* initialize stuff */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
            abort_("[write_png_file] png_create_write_struct failed");

    //log
    printf("[%s : %d] png_ptr => created\n", base_name(__FILE__), __LINE__);

    
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
            abort_("[write_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during init_io");

    //log
    printf("[%s : %d] png_create_info_struct => done\n", base_name(__FILE__), __LINE__);

    
    png_init_io(png_ptr, fp);

    //log
    printf("[%s : %d] png_init_io => done\n", base_name(__FILE__), __LINE__);


    /* write header */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during writing header");

    png_set_IHDR(png_ptr, info_ptr, *width, *height,
                 *bit_depth, *color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    //log
    printf("[%s : %d] png_ptr->height => %d\n",
            base_name(__FILE__), __LINE__, png_ptr->height);
    
    printf("[%s : %d] info_ptr->height => %d\n",
            base_name(__FILE__), __LINE__, info_ptr->height);

    
    //log
    printf("[%s : %d] png_set_IHDR => done\n", base_name(__FILE__), __LINE__);

    
    png_write_info(png_ptr, info_ptr);

    //log
    printf("[%s : %d] png_write_info => done\n", base_name(__FILE__), __LINE__);
//
    //log
    printf("[%s : %d] png_ptr->height => %d\n",
            base_name(__FILE__), __LINE__, png_ptr->height);
    printf("[%s : %d] png_ptr->width => %d\n",
            base_name(__FILE__), __LINE__, png_ptr->width);

    /* write bytes */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during writing bytes");

    png_write_image(png_ptr, row_pointers);

    //log
    printf("[%s : %d] png_write_image => done\n", base_name(__FILE__), __LINE__);


    /* end write */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during end of write");

    png_write_end(png_ptr, NULL);

    /* cleanup heap allocation */
    for (y=0; y < *height; y++)
//    for (y=0; y<height; y++)
            free(row_pointers[y]);
    free(row_pointers);

    fclose(fp);
}//void write_png_file()

void _test_WritePng
(char* file_name, png_structp png_ptr,
    png_infop info_ptr,
    int *width, int *height,
    png_byte *color_type, png_byte *bit_depth)
{
    int y;
    
    //log
    printf("[%s : %d] row_pointers[0][0] => %d\n",
            base_name(__FILE__), __LINE__, row_pointers[0][0]);

    
    /* create file */
    FILE *fp = fopen(file_name, "wb");
    if (!fp)
            abort_("[write_png_file] File %s could not be opened for writing", file_name);

    //log
    printf("[%s : %d] file => opened: %s\n", base_name(__FILE__), __LINE__, file_name);


    /* initialize stuff */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
            abort_("[write_png_file] png_create_write_struct failed");

    //log
    printf("[%s : %d] png_ptr => created\n", base_name(__FILE__), __LINE__);

    
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
            abort_("[write_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during init_io");

    //log
    printf("[%s : %d] png_create_info_struct => done\n", base_name(__FILE__), __LINE__);

    
    png_init_io(png_ptr, fp);

    //log
    printf("[%s : %d] png_init_io => done\n", base_name(__FILE__), __LINE__);


    /* write header */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during writing header");

    png_set_IHDR(png_ptr, info_ptr, *width, *height,
                 *bit_depth, *color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    //log
    printf("[%s : %d] png_ptr->height => %d\n",
            base_name(__FILE__), __LINE__, png_ptr->height);
    
    printf("[%s : %d] info_ptr->height => %d\n",
            base_name(__FILE__), __LINE__, info_ptr->height);

    
    //log
    printf("[%s : %d] png_set_IHDR => done\n", base_name(__FILE__), __LINE__);

    
    png_write_info(png_ptr, info_ptr);

    //log
    printf("[%s : %d] png_write_info => done\n", base_name(__FILE__), __LINE__);
//
    //log
    printf("[%s : %d] png_ptr->height => %d\n",
            base_name(__FILE__), __LINE__, png_ptr->height);
    printf("[%s : %d] png_ptr->width => %d\n",
            base_name(__FILE__), __LINE__, png_ptr->width);

    /* write bytes */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during writing bytes");

    png_write_image(png_ptr, row_pointers);

    //log
    printf("[%s : %d] png_write_image => done\n", base_name(__FILE__), __LINE__);


    /* end write */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during end of write");

    png_write_end(png_ptr, NULL);

    /* cleanup heap allocation */
    for (y=0; y < *height; y++)
//    for (y=0; y<height; y++)
            free(row_pointers[y]);
    free(row_pointers);

    fclose(fp);
}//void write_png_file()

void _test_WritePng__Process
(char* file_name, png_structp png_ptr,
    png_infop info_ptr,
    int *width, int *height,
    png_byte *color_type, png_byte *bit_depth)
{
    int y;
    
    /* create file */
    FILE *fp = fopen(file_name, "wb");
    if (!fp)
            abort_("[write_png_file] File %s could not be opened for writing", file_name);

    //log
    printf("[%s : %d] file => opened: %s\n", base_name(__FILE__), __LINE__, file_name);


    /* initialize stuff */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
            abort_("[write_png_file] png_create_write_struct failed");

//    //log
//    printf("[%s : %d] png_ptr => created\n", base_name(__FILE__), __LINE__);

    
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
            abort_("[write_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during init_io");

//    //log
//    printf("[%s : %d] png_create_info_struct => done\n", base_name(__FILE__), __LINE__);

    
    png_init_io(png_ptr, fp);

    //log
    printf("[%s : %d] png_init_io => done\n", base_name(__FILE__), __LINE__);


    /* write header */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during writing header");

    png_set_IHDR(png_ptr, info_ptr, *width, *height,
                 *bit_depth, *color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

//    //log
//    printf("[%s : %d] png_ptr->height => %d\n",
//            base_name(__FILE__), __LINE__, png_ptr->height);
//    
//    printf("[%s : %d] info_ptr->height => %d\n",
//            base_name(__FILE__), __LINE__, info_ptr->height);

    
//    //log
//    printf("[%s : %d] png_set_IHDR => done\n", base_name(__FILE__), __LINE__);

    
    png_write_info(png_ptr, info_ptr);

//    //log
//    printf("[%s : %d] png_write_info => done\n", base_name(__FILE__), __LINE__);
//
//    //log
//    printf("[%s : %d] png_ptr->height => %d\n",
//            base_name(__FILE__), __LINE__, png_ptr->height);
//    printf("[%s : %d] png_ptr->width => %d\n",
//            base_name(__FILE__), __LINE__, png_ptr->width);

    /* write bytes */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during writing bytes");

    png_write_image(png_ptr, row_pointers_B);

//    //log
//    printf("[%s : %d] png_write_image => done\n", base_name(__FILE__), __LINE__);


    /* end write */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during end of write");

    png_write_end(png_ptr, NULL);

    /* cleanup heap allocation */
    for (y=0; y < *height; y++)
//    for (y=0; y<height; y++)
            free(row_pointers_B[y]);
    free(row_pointers_B);

    fclose(fp);
}//void write_png_file()

void writePNG_Histo
(char* file_name, png_structp png_ptr,
    png_infop info_ptr,
    int *width, int *height,
    png_byte *color_type, png_byte *bit_depth, char rgb_opt)
//(char*, png_structp, png_infop,
//int *, int *, png_byte *, png_byte *, char rgb_opt)
{
    int y;
    
    /* create file */
    FILE *fp = fopen(file_name, "wb");
    if (!fp)
            abort_("[write_png_file] File %s could not be opened for writing", file_name);

    //log
    printf("[%s : %d] file => opened: %s\n", base_name(__FILE__), __LINE__, file_name);


    /* initialize stuff */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
            abort_("[write_png_file] png_create_write_struct failed");

//    //log
//    printf("[%s : %d] png_ptr => created\n", base_name(__FILE__), __LINE__);

    
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
            abort_("[write_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during init_io");

//    //log
//    printf("[%s : %d] png_create_info_struct => done\n", base_name(__FILE__), __LINE__);

    
    png_init_io(png_ptr, fp);

    //log
    printf("[%s : %d] png_init_io => done\n", base_name(__FILE__), __LINE__);


    /* write header */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during writing header");

    png_set_IHDR(png_ptr, info_ptr, *width, *height,
                 *bit_depth, *color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

//    //log
//    printf("[%s : %d] png_ptr->height => %d\n",
//            base_name(__FILE__), __LINE__, png_ptr->height);
//    
//    printf("[%s : %d] info_ptr->height => %d\n",
//            base_name(__FILE__), __LINE__, info_ptr->height);

    
//    //log
//    printf("[%s : %d] png_set_IHDR => done\n", base_name(__FILE__), __LINE__);

    
    png_write_info(png_ptr, info_ptr);

//    //log
//    printf("[%s : %d] png_write_info => done\n", base_name(__FILE__), __LINE__);
//
//    //log
//    printf("[%s : %d] png_ptr->height => %d\n",
//            base_name(__FILE__), __LINE__, png_ptr->height);
//    printf("[%s : %d] png_ptr->width => %d\n",
//            base_name(__FILE__), __LINE__, png_ptr->width);

    /* write bytes */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during writing bytes");

    png_write_image(png_ptr, row_pointers_B);

//    //log
//    printf("[%s : %d] png_write_image => done\n", base_name(__FILE__), __LINE__);


    /* end write */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during end of write");

    png_write_end(png_ptr, NULL);

    /* cleanup heap allocation */
    for (y=0; y < *height; y++)
//    for (y=0; y<height; y++)
            free(row_pointers_B[y]);
    free(row_pointers_B);

    fclose(fp);
}//void write_png_file()

/*************************************
 * _test_WritePng_Merge
 * 
 * @param type 1        => src 1
 *              2       => src 2
 *              3       => dst
 **************************************/
void _test_WritePng_Merge
(char* file_name, png_structp png_ptr,
    png_infop info_ptr,
    int *width, int *height,
    png_byte *color_type, png_byte *bit_depth, int type)
{
    
    //log
    printf("[%s : %d] Starts => _test_WritePng_Merge\n", base_name(__FILE__), __LINE__);

    int x, y;
//    int y;
    
    /* create file */
    FILE *fp = fopen(file_name, "wb");
    
    //log
    printf("[%s : %d] fopen() => done\n", base_name(__FILE__), __LINE__);

    
    if (!fp)
            abort_("[write_png_file] File %s could not be opened for writing", file_name);

    //log
    printf("[%s : %d] file => opened: %s\n", base_name(__FILE__), __LINE__, file_name);


    /* initialize stuff */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
            abort_("[write_png_file] png_create_write_struct failed");

    //log
    printf("[%s : %d] png_ptr => created\n", base_name(__FILE__), __LINE__);

    
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
            abort_("[write_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during init_io");

    //log
    printf("[%s : %d] png_create_info_struct => done\n", base_name(__FILE__), __LINE__);

    
    png_init_io(png_ptr, fp);

    //log
    printf("[%s : %d] png_init_io => done\n", base_name(__FILE__), __LINE__);


    /* write header */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during writing header");

    png_set_IHDR(png_ptr, info_ptr, *width, *height,
                 *bit_depth, *color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    
    //log
    printf("[%s : %d] png_set_IHDR => done\n", base_name(__FILE__), __LINE__);

    
    png_write_info(png_ptr, info_ptr);

    //log
    printf("[%s : %d] png_write_info => done\n", base_name(__FILE__), __LINE__);

    /* write bytes */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during writing bytes");


    /*************************************
 
     * write: row pointers
 
     **************************************/
    if (type == 1) {
        
        png_write_image(png_ptr, row_pointers_A);
        
    } else if (type == 2) {
        
        png_write_image(png_ptr, row_pointers_B);
        
    } else if (type == 3) {
        
//        /*************************************
// 
//        * init: row_pointers_C
//
//        **************************************/
//   //    int x, y;   // iterator
//
//       int width = png_ptr->width;
//       int height = png_ptr->height;
//
//       row_pointers_C = (png_bytep*) malloc(sizeof(png_bytep) * (height));
//
//       //log
//       printf("[%s : %d] malloc done for row_pointers_C\n", 
//               base_name(__FILE__), __LINE__);
//
//
//       for (y=0; y < height; y++)
//               row_pointers_C[y] = 
//                       (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
//
//       //log
//       printf("[%s : %d] malloc done for => row_pointers_C[y]\n", base_name(__FILE__), __LINE__);
//
//
//       for (y = 0; y < height; y++) {
//
//           png_byte* row = row_pointers_C[y];
//   //
//           for (x=0; x<width; x++) {
//
//               png_byte* ptr = &(row[x*3]);
//
//           //log
//               ptr[0] = 0; ptr[1] = 0; ptr[2] = 0;
//   //                  ptr[1] = 0; ptr[2] = 0;
//
//           }
//       }//for (y=0; y<height; y++)    
//
//       //log
//       printf("[%s : %d] init_Row_Pointers_C() => done\n", base_name(__FILE__), __LINE__);

        png_write_image(png_ptr, row_pointers_C);
        
    } else {
        
        consolColor_Change(RED);

        //log
        printf("[%s : %d] unknown file type => %d\n", 
                base_name(__FILE__), __LINE__, type);

        consolColor_Reset();
        
        fclose(fp);
        
        exit(0);

    }

    //log
    printf("[%s : %d] png_write_image => done\n", base_name(__FILE__), __LINE__);

    /* end write */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during end of write");

    png_write_end(png_ptr, NULL);

    /* cleanup heap allocation */
//    for (y=0; y < *height; y++)
//    for (y=0; y<height; y++)
    if (type == 1) {
        
        for (y=0; y < *height; y++)
            free(row_pointers_A[y]);
        
        free(row_pointers_A);

    } else if (type == 2) {
        
        for (y=0; y < *height; y++)
            free(row_pointers_B[y]);
        
        free(row_pointers_B);

    } else if (type == 3) {

        for (y=0; y < *height; y++)
            free(row_pointers_C[y]);
        
        free(row_pointers_C);

    }
    
//    free(row_pointers);

    fclose(fp);
}//void write_png_file()

void _test_WritePng_Rgba
(char* file_name, png_structp png_ptr,
    png_infop info_ptr,
    int *width, int *height,
    png_byte *color_type, png_byte *bit_depth)
{
    int y;
    
//    //log
//    printf("[%s : %d] row_pointers[0][0] => %d\n",
//            base_name(__FILE__), __LINE__, row_pointers[0][0]);

    
    /* create file */
    FILE *fp = fopen(file_name, "wb");
    if (!fp)
            abort_("[write_png_file] File %s could not be opened for writing", file_name);

    //log
    printf("[%s : %d] file => opened: %s\n", base_name(__FILE__), __LINE__, file_name);


    /* initialize stuff */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
            abort_("[write_png_file] png_create_write_struct failed");

//    //log
//    printf("[%s : %d] png_ptr => created\n", base_name(__FILE__), __LINE__);

    
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
            abort_("[write_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during init_io");

//    //log
//    printf("[%s : %d] png_create_info_struct => done\n", base_name(__FILE__), __LINE__);

    
    png_init_io(png_ptr, fp);

//    //log
//    printf("[%s : %d] png_init_io => done\n", base_name(__FILE__), __LINE__);


    /* write header */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during writing header");

    png_set_IHDR(png_ptr, info_ptr, *width, *height,
                 *bit_depth, *color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    //log
    printf("[%s : %d] png_ptr->height => %d\n",
            base_name(__FILE__), __LINE__, png_ptr->height);
    
    printf("[%s : %d] info_ptr->height => %d\n",
            base_name(__FILE__), __LINE__, info_ptr->height);

    
    //log
    printf("[%s : %d] png_set_IHDR => done\n", base_name(__FILE__), __LINE__);

    
    png_write_info(png_ptr, info_ptr);

    //log
    printf("[%s : %d] png_write_info => done\n", base_name(__FILE__), __LINE__);
//
    //log
    printf("[%s : %d] png_ptr->height => %d\n",
            base_name(__FILE__), __LINE__, png_ptr->height);
    printf("[%s : %d] png_ptr->width => %d\n",
            base_name(__FILE__), __LINE__, png_ptr->width);

    /* write bytes */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during writing bytes");

    png_write_image(png_ptr, row_pointers_RGBA);
//    png_write_image(png_ptr, row_pointers);

    //log
    printf("[%s : %d] png_write_image => done\n", base_name(__FILE__), __LINE__);


    /* end write */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[write_png_file] Error during end of write");

    png_write_end(png_ptr, NULL);

    /* cleanup heap allocation */
    for (y=0; y < *height; y++)
//    for (y=0; y<height; y++)
            free(row_pointers_RGBA[y]);
//            free(row_pointers[y]);
    free(row_pointers_RGBA);
//    free(row_pointers);

    fclose(fp);
}//void write_png_file()

void read_png_file
(char* file_name,
        png_structp png_ptr, png_infop info_ptr,
        png_bytep * row_pointers,
        
        int *width, int *height, int *number_of_passes,
        png_byte *color_type, png_byte *bit_depth)
{
        char header[8];    // 8 is the maximum size that can be checked

        int y;  // for-loop counter
        
        /* open file and test for it being a png */
        FILE *fp = fopen(file_name, "rb");
        if (!fp)
                abort_("[read_png_file] File %s could not be opened for reading", file_name);
        fread(header, 1, 8, fp);
        if (png_sig_cmp(header, 0, 8))
                abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);
        

        /* initialize stuff */
//        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//
//        if (!png_ptr)
//                abort_("[read_png_file] png_create_read_struct failed");

//        info_ptr = png_create_info_struct(png_ptr);
//        if (!info_ptr)
//                abort_("[read_png_file] png_create_info_struct failed");

        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during init_io");

        //log
        printf("[%s : %d] info_ptr->height => %d\n", 
            base_name(__FILE__), __LINE__, info_ptr->height);

        
        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);

        png_read_info(png_ptr, info_ptr);

        *width = png_get_image_width(png_ptr, info_ptr);
        *height = png_get_image_height(png_ptr, info_ptr);
        *color_type = png_get_color_type(png_ptr, info_ptr);
        *bit_depth = png_get_bit_depth(png_ptr, info_ptr);

        *number_of_passes = png_set_interlace_handling(png_ptr);
        png_read_update_info(png_ptr, info_ptr);


        /* read file */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during read_image");

        //log
    printf("[%s : %d] *height => %d\n", base_name(__FILE__), __LINE__, *height);
    printf("[%s : %d] info_ptr->height => %d\n", 
            base_name(__FILE__), __LINE__, info_ptr->height);

        
//        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * (*height));
//        
//        for (y=0; y< *height; y++)
//                row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

        png_read_image(png_ptr, row_pointers);

        //log
    printf("[%s : %d] png_read_image() => done\n", base_name(__FILE__), __LINE__);

        
        fclose(fp);
        
        //log
//    printf("[%s : %d] row_pointers[0][0] => %d\n", base_name(__FILE__), __LINE__, row_pointers[0][0]);

        
        //log
    printf("[%s : %d] read_png_file() => done\n", base_name(__FILE__), __LINE__);

        
}

void get_PngInfo
(char* file_name,
        png_structp png_ptr, png_infop info_ptr,
                
        int *width, int *height, int *number_of_passes,
        png_byte *color_type, png_byte *bit_depth)
{
        char header[8];    // 8 is the maximum size that can be checked

        int y;  // for-loop counter
        
        /* open file and test for it being a png */
        FILE *fp = fopen(file_name, "rb");
        if (!fp)
                abort_("[read_png_file] File %s could not be opened for reading", file_name);
        fread(header, 1, 8, fp);
        if (png_sig_cmp(header, 0, 8))
                abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);
        

        /* initialize stuff */
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!png_ptr)
                abort_("[read_png_file] png_create_read_struct failed");

        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
                abort_("[read_png_file] png_create_info_struct failed");

        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during init_io");

//        //log
//        printf("[%s : %d] info_ptr->height => %d\n", 
//            base_name(__FILE__), __LINE__, info_ptr->height);

        
        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);

        png_read_info(png_ptr, info_ptr);

        *width = png_get_image_width(png_ptr, info_ptr);
        *height = png_get_image_height(png_ptr, info_ptr);
        *color_type = png_get_color_type(png_ptr, info_ptr);
        *bit_depth = png_get_bit_depth(png_ptr, info_ptr);

        *number_of_passes = png_set_interlace_handling(png_ptr);
        png_read_update_info(png_ptr, info_ptr);


        /* read file */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during read_image");

//        //log
//    printf("[%s : %d] *height => %d\n", base_name(__FILE__), __LINE__, *height);

        
//        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * (*height));
//        
//        for (y=0; y< *height; y++)
//                row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
//
//        png_read_image(png_ptr, row_pointers);

        fclose(fp);
        
//        //log
//    printf("[%s : %d] info_ptr->height => %d\n",
//            base_name(__FILE__), __LINE__, info_ptr->height);
    
        
        
//        //log
//    printf("[%s : %d] row_pointers[0][0] => %d\n", base_name(__FILE__), __LINE__, row_pointers[0][0]);

        //log
    printf("[%s : %d] info_ptr->width => %d\n", 
            base_name(__FILE__), __LINE__, info_ptr->width);

        //log
    printf("[%s : %d] get_PngInfo() => done\n", base_name(__FILE__), __LINE__);

        
}//void get_PngInfo

void _test_DoublePointer(char **memos)
{
//    memos = (char **) malloc(sizeof(char*) * 4);
    
    char *memo_1 = "abcdef\n";
    
    memos[0] = memo_1;
    
    //log
    printf("[%s : %d] _test_DoublePointer() => ends\n", base_name(__FILE__), __LINE__);

    
    
}

void _test_MallocInFunction(char *msg)
{
    msg = malloc(sizeof(char) * 20);
    
    char *s = "xxxvvvddd\n";
    
    strcpy(msg, s);
    
    msg[strlen(s)] = '\0';
    
    //log
    printf("[%s : %d] msg => %s\n", base_name(__FILE__), __LINE__, msg);
    
    //log
    printf("[%s : %d] _test_MallocInFunction() => done\n", base_name(__FILE__), __LINE__);

    
}


void _test_ReadPng
(char* file_name,
        png_structp png_ptr, png_infop info_ptr,
        
        int *width, int *height, int *number_of_passes,
        png_byte *color_type, png_byte *bit_depth)
{
        char header[8];    // 8 is the maximum size that can be checked

        int y;  // for-loop counter
        
        /* open file and test for it being a png */
        FILE *fp = fopen(file_name, "rb");
        if (!fp)
                abort_("[read_png_file] File %s could not be opened for reading", file_name);
        fread(header, 1, 8, fp);
        if (png_sig_cmp(header, 0, 8))
                abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);
        

        /* initialize stuff */
//        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//
//        if (!png_ptr)
//                abort_("[read_png_file] png_create_read_struct failed");

//        info_ptr = png_create_info_struct(png_ptr);
//        if (!info_ptr)
//                abort_("[read_png_file] png_create_info_struct failed");

        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during init_io");

//        //log
//        printf("[%s : %d] info_ptr->height => %d\n", 
//            base_name(__FILE__), __LINE__, info_ptr->height);

        
        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);

        png_read_info(png_ptr, info_ptr);

        *width = png_get_image_width(png_ptr, info_ptr);
        *height = png_get_image_height(png_ptr, info_ptr);
        *color_type = png_get_color_type(png_ptr, info_ptr);
        *bit_depth = png_get_bit_depth(png_ptr, info_ptr);

        *number_of_passes = png_set_interlace_handling(png_ptr);
        png_read_update_info(png_ptr, info_ptr);


        /* read file */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during read_image");

//        //log
//    printf("[%s : %d] *height => %d\n", base_name(__FILE__), __LINE__, *height);
//    printf("[%s : %d] info_ptr->height => %d\n", 
//            base_name(__FILE__), __LINE__, info_ptr->height);

        
        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * (*height));
        
        for (y=0; y< *height; y++)
                row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

        png_read_image(png_ptr, row_pointers);

//        //log
//        printf("[%s : %d] png_get_rowbytes(png_ptr,info_ptr) = %d\n", 
//            base_name(__FILE__), __LINE__, png_get_rowbytes(png_ptr,info_ptr));

//        //test
//        int tmp_i = png_ptr->rowbytes;
//        
////        png_ptr->row_buf = tmp_i * 4 / 3;
//        
//        //log
//        printf("[%s : %d] tmp_i * 4 / 3 ==> %d\n", 
//                base_name(__FILE__), __LINE__, (tmp_i * 4 / 3));

        
        /*************************************
 
        * init: row_pointers_rgba

        **************************************/

//        row_pointers_rgba = (png_bytep*) malloc(sizeof(png_bytep) * (*height));
//        
//        for (y=0; y< *height; y++)
//                row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
        
//        consolColor_Change(LIGHT_YELLOW);
//
//        //log
//        printf("[%s : %d] png_read_image() => done\n", base_name(__FILE__), __LINE__);
//
//        consolColor_Reset();
        
        fclose(fp);
        
        //log
//    printf("[%s : %d] row_pointers[0][0] => %d\n", base_name(__FILE__), __LINE__, row_pointers[0][0]);

        consolColor_Change(LIGHT_YELLOW);

        //log
        printf("[%s : %d] _test_ReadPng() => done\n", base_name(__FILE__), __LINE__);

        consolColor_Reset();

        
}//void _test_ReadPng

/**************************
 * void _test_ReadPng__Process()
 * 
 * 1. Read pixels into => row_pointers_A
 **************************/

void _test_ReadPng__Process
(char* file_name,
        png_structp png_ptr, png_infop info_ptr,
        
        int *width, int *height, int *number_of_passes,
        png_byte *color_type, png_byte *bit_depth)
{
        char header[8];    // 8 is the maximum size that can be checked

        int y;  // for-loop counter
        
        /* open file and test for it being a png */
        FILE *fp = fopen(file_name, "rb");
        if (!fp)
                abort_("[read_png_file] File %s could not be opened for reading", file_name);
        fread(header, 1, 8, fp);
        if (png_sig_cmp(header, 0, 8))
                abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);

        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during init_io");
        
        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);

        png_read_info(png_ptr, info_ptr);

        *width = png_get_image_width(png_ptr, info_ptr);
        *height = png_get_image_height(png_ptr, info_ptr);
        *color_type = png_get_color_type(png_ptr, info_ptr);
        *bit_depth = png_get_bit_depth(png_ptr, info_ptr);

        *number_of_passes = png_set_interlace_handling(png_ptr);
        png_read_update_info(png_ptr, info_ptr);

        /* read file */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during read_image");

        row_pointers_A = (png_bytep*) malloc(sizeof(png_bytep) * (*height));
        
        for (y=0; y< *height; y++)
                row_pointers_A[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

        png_read_image(png_ptr, row_pointers_A);
        
        fclose(fp);
        
        //log
//    printf("[%s : %d] row_pointers[0][0] => %d\n", base_name(__FILE__), __LINE__, row_pointers[0][0]);

        consolColor_Change(LIGHT_YELLOW);

        //log
        printf("[%s : %d] _test_ReadPng__Process() => done\n", 
                base_name(__FILE__), __LINE__);

        consolColor_Reset();

        
}//void _test_ReadPng__Process

/*************************************
 * _test_ReadPng_Merge
 * 
 * @param type 1        => src 1
 *              2       => src 2
 **************************************/
void _test_ReadPng_Merge
(char* file_name,
        png_structp png_ptr, png_infop info_ptr,
        int *width, int *height, int *number_of_passes,
        png_byte *color_type, png_byte *bit_depth, int type)
{
    char header[8];    // 8 is the maximum size that can be checked

    int y;  // for-loop counter

    /* open file and test for it being a png */
    FILE *fp = fopen(file_name, "rb");
    if (!fp)
            abort_("[read_png_file] File %s could not be opened for reading", file_name);
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8))
            abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);

//    //log
//    printf("[%s : %d] file name => %s\n", base_name(__FILE__), __LINE__, file_name);


    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[read_png_file] Error during init_io");

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    *width = png_get_image_width(png_ptr, info_ptr);
    *height = png_get_image_height(png_ptr, info_ptr);
    *color_type = png_get_color_type(png_ptr, info_ptr);
    *bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    *number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);


    /* read file */
    if (setjmp(png_jmpbuf(png_ptr)))
            abort_("[read_png_file] Error during read_image");

    /*************************************
 
     * row pointers
 
     **************************************/
    // src 1
    if (type == 1) {

        row_pointers_A = (png_bytep*) malloc(sizeof(png_bytep) * (*height));

        for (y=0; y< *height; y++)
                row_pointers_A[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

        png_read_image(png_ptr, row_pointers_A);

    } else if (type == 2) {
        // src 2
        
        row_pointers_B = (png_bytep*) malloc(sizeof(png_bytep) * (*height));

        for (y=0; y< *height; y++)
                row_pointers_B[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

        png_read_image(png_ptr, row_pointers_B);

    } else {
        
        consolColor_Change(RED);

        //log
        printf("[%s : %d] unknown file type => %d\n", base_name(__FILE__), __LINE__, type);

        consolColor_Reset();

        fclose(fp);
        
        exit(0);
        
    }
       
        
    fclose(fp);
    
    consolColor_Change(LIGHT_YELLOW);

    //log
    printf("[%s : %d] _test_ReadPng() => done\n", base_name(__FILE__), __LINE__);

    consolColor_Reset();

        
}//void _test_ReadPng

void _test_ReadPng_Rgba
(char* file_name,
        png_structp png_ptr, png_infop info_ptr,
        
        
        int *width, int *height, int *number_of_passes,
        png_byte *color_type, png_byte *bit_depth)
{
        char header[8];    // 8 is the maximum size that can be checked

        int y;  // for-loop counter
        
        /* open file and test for it being a png */
        FILE *fp = fopen(file_name, "rb");
        if (!fp)
                abort_("[read_png_file] File %s could not be opened for reading", file_name);
        fread(header, 1, 8, fp);
        if (png_sig_cmp(header, 0, 8))
                abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);
        
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during init_io");

//        //log
//        printf("[%s : %d] info_ptr->height => %d\n", 
//            base_name(__FILE__), __LINE__, info_ptr->height);

        
        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);

        png_read_info(png_ptr, info_ptr);

        *width = png_get_image_width(png_ptr, info_ptr);
        *height = png_get_image_height(png_ptr, info_ptr);
        *color_type = png_get_color_type(png_ptr, info_ptr);
        *bit_depth = png_get_bit_depth(png_ptr, info_ptr);

        *number_of_passes = png_set_interlace_handling(png_ptr);
        png_read_update_info(png_ptr, info_ptr);


        /* read file */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during read_image");

//        //log
//    printf("[%s : %d] *height => %d\n", base_name(__FILE__), __LINE__, *height);
//    printf("[%s : %d] info_ptr->height => %d\n", 
//            base_name(__FILE__), __LINE__, info_ptr->height);

        
        row_pointers_RGBA = (png_bytep*) malloc(sizeof(png_bytep) * (*height));
        
        for (y=0; y< *height; y++)
                row_pointers_RGBA[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

        png_read_image(png_ptr, row_pointers_RGBA);

//        //log
//        printf("[%s : %d] png_get_rowbytes(png_ptr,info_ptr) = %d\n", 
//            base_name(__FILE__), __LINE__, png_get_rowbytes(png_ptr,info_ptr));

//        //test
//        int tmp_i = png_ptr->rowbytes;
//        
////        png_ptr->row_buf = tmp_i * 4 / 3;
//        
//        //log
//        printf("[%s : %d] tmp_i * 4 / 3 ==> %d\n", 
//                base_name(__FILE__), __LINE__, (tmp_i * 4 / 3));

        
        /*************************************
 
        * init: row_pointers_rgba

        **************************************/

//        row_pointers_rgba = (png_bytep*) malloc(sizeof(png_bytep) * (*height));
//        
//        for (y=0; y< *height; y++)
//                row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
        
//        consolColor_Change(LIGHT_YELLOW);
//
//        //log
//        printf("[%s : %d] png_read_image() => done\n", base_name(__FILE__), __LINE__);
//
//        consolColor_Reset();
        
        fclose(fp);
        
        //log
//    printf("[%s : %d] row_pointers[0][0] => %d\n", base_name(__FILE__), __LINE__, row_pointers[0][0]);

        consolColor_Change(LIGHT_YELLOW);

        //log
        printf("[%s : %d] _test_ReadPng_Rgba() => done\n", base_name(__FILE__), __LINE__);

        consolColor_Reset();

        
}//void _test_ReadPng_rgba

void process_file
(png_structp png_ptr, png_infop info_ptr,
int width, int height)
//void process_file(void)
{
    if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGB
            && png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGBA)
            abort_(
                "[process_file] input file is neither PNG_COLOR_TYPE_RGB "
                "or PNG_COLOR_TYPE_RGBA. ");

//    if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGBA)
//            abort_("[process_file] color_type of input file must be PNG_COLOR_TYPE_RGBA (%d) (is %d)",
//                   PNG_COLOR_TYPE_RGBA, png_get_color_type(png_ptr, info_ptr));
        
    int x, y;
    
    for (y=0; y<height; y++) {

            png_byte* row = row_pointers[y];
//
            for (x=0; x<width; x++) {

                png_byte* ptr = &(row[x*3]);

            //log
                  ptr[0] = 0; ptr[1] = 0;
//                  ptr[1] = 0; ptr[2] = 0;
                  
            }
    }//for (y=0; y<height; y++)
        
        //log
    printf("[%s : %d] processing => done\n", base_name(__FILE__), __LINE__);

}

void conv_PNG_to_PPM(png_structp png_ptr, PPM *ppm)
//PPM* conv_PNG_to_PPM(png_structp png_ptr)
{
//    PPM *ppm = (PPM *) malloc(sizeof(PPM) * 1);
    
    ppm->file_name = (char *) malloc(sizeof(char) * 20);
    
    char *fname = "qwertyuiop";
    
    strcpy(ppm->file_name, fname);
    
    ppm->file_name[strlen(fname)] = '\0';
    
    //log
    printf("[%s : %d] png_ptr->width = %d\n", base_name(__FILE__), __LINE__, png_ptr->width);

    ppm->x = png_ptr->width;
    ppm->y = png_ptr->height;
//    ppm->x = (gray) *(png_ptr->width);
//    ppm->x = (gray) png_ptr->width;
    
//    ppm->x = 100;
    
    strcpy(ppm->format, "P6");
    
    ppm->format[2] = '\0';
    
//    ppm->max_brightness = png_ptr->
    /*************************************
 
     * Conv: pixels
 
     **************************************/
    int num_of_pixels;
    
    int max_brightness = 0;
    int tmp;
    
    num_of_pixels = png_ptr->width * png_ptr->height;
    
    ppm->pixels = (pixel *) malloc (sizeof(pixel) * num_of_pixels);
    
    int x, y;
    int counter = 0;    // counter for ppm->pixels
    
    for (y=0; y< png_ptr->height; y++) {

//        //log
//    printf("[%s : %d] y = %d\n", base_name(__FILE__), __LINE__, y);
//
            png_byte* row = row_pointers[y];
//
//            //log
//    printf("[%s : %d] png_byte* row\n", base_name(__FILE__), __LINE__);


            for (x=0; x< png_ptr->width; x++) {

                png_byte* ptr = &(row[x*3]);
                
                ppm->pixels[counter].r = ptr[0];
                
                tmp = ptr[0];
                if(tmp > max_brightness)
                    max_brightness = tmp;
                
                ppm->pixels[counter].g = ptr[1];
                ppm->pixels[counter].b = ptr[2];
                
//                (ppm->pixels + counter)). = ptr[0];
//                (ppm->pixels + counter)[1] = ptr[1];
//                (ppm->pixels + counter)[2] = ptr[2];
                
                counter ++;
                
//                ptr[0] = 255 - ptr[0]; ptr[1] = 0; ptr[2] = 0;
//                ptr[0] = 0; ptr[1] = 255 - ptr[1]; ptr[2] = 0;
//                ptr[0] = 0; ptr[1] = 0; ptr[2] = 255 - ptr[2];

            }
    }//for (y=0; y<height; y++)
    
    ppm->max_brightness = max_brightness;
    
    //log
//    printf("[%s : %d] ppm->x = %d\n", base_name(__FILE__), __LINE__, ppm->x);

    
//    return ppm;
    
}

void conv_RGB_to_RGBA
(char* file_name,
        png_structp png_ptr_Src, png_structp png_ptr_Dst,
        png_infop info_ptr_Src, int *width_Dst, int *height_Dst)
        
//        int *width, int *height, int *number_of_passes,
//        png_byte *color_type, png_byte *bit_depth)
{
    
    int x, y;   // counter
    int i, j;   // counter: i for row_pointers, j for row_pointers_rgba
    int count;  // counter for conversion process
        
    row_pointers_RGBA = (png_bytep*) malloc(sizeof(png_bytep) * (*height_Dst));

    int num_of_rowbytes = png_get_rowbytes(png_ptr_Src,info_ptr_Src);
    
    for (y=0; y< *height_Dst; y++)
//            row_pointers_RGBA[y] = (png_byte*) malloc((num_of_rowbytes * 3 / 3));
                        /*
                         * pngtoppm: malloc.c:2451: sYSMALLOc: Assertion `(old_top == (((mbinptr) (((char *) &((av)->bins[((1) - 1) * 2])) - __builtin_offsetof (struct malloc_chunk, fd)))) && old_size == 0) || ((unsigned long) (old_size) >= (unsigned long)((((__builtin_offsetof (struct malloc_chunk, fd_nextsize))+((2 * (sizeof(size_t))) - 1)) & ~((2 * (sizeof(size_t))) - 1))) && ((old_top)->size & 0x1) && ((unsigned long)old_end & pagemask) == 0)' failed.
                                Aborted (core dumped)

                         */
            row_pointers_RGBA[y] = (png_byte*) malloc((num_of_rowbytes * 4 / 3));
//            row_pointers_rgba[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

//    png_read_image(png_ptr, row_pointers);

//    //log
//    printf("[%s : %d] row_pointers_RGBA[0][0] = %d\n", 
//            base_name(__FILE__), __LINE__, row_pointers_RGBA[0][0]); // => 0

    
    /*************************************

    * conv

    **************************************/
    count = i = j = 0;  // init counters
    
//    row_pointers_RGBA[0][0] = row_pointers[0][0];
    
    for (y=0; y < *height_Dst; y++) {

        png_byte* row = row_pointers_RGBA[y];
        
        count = 0;

        for (x=0; x < *width_Dst; x++) {

            png_byte* ptr = &(row[x*3]);

            ptr[0] = *(row_pointers[y] + count);

            count ++;

            ptr[1] = 0;
//            ptr[1] = *(row_pointers[y] + count);

            count ++;

            ptr[2] = *(row_pointers[y] + count);

            count ++;
            
            ptr[3] = 0x01;
//            ptr[3] = 0xff;

        //log
//                  ptr[0] = 0; ptr[1] = 0;
//                  ptr[1] = 0; ptr[2] = 0;
//                ptr[0] = 255 - ptr[0]; ptr[1] = 0; ptr[2] = 0;
//                ptr[0] = 0; ptr[1] = 255 - ptr[1]; ptr[2] = 0;
//                ptr[0] = 0; ptr[1] = 0; ptr[2] = 255 - ptr[2];

        }//for (x=0; x < *width_Dst; x++)
        
    }//for (y=0; y<height; y++)
//    count ++;   // count => 1
    
//    for (y = 0; y < *height_Src; y++) {
//        
////        for (x = 0; )
//        
//        
//    }
    
    
    /*************************************

    * init: row_pointers_rgba

    **************************************/

    consolColor_Change(LIGHT_YELLOW);

    //log
    printf("[%s : %d] conv_RGB_to_RGBA() => done\n", base_name(__FILE__), __LINE__);

    consolColor_Reset();

        
}//void _test_ReadPng

void init_Row_Pointers_C
(png_structp png_ptr, png_infop info_ptr, char *bg_name)
{
    
    int x, y;   // iterator
    
    int width = png_ptr->width;
    int height = png_ptr->height;
    
    row_pointers_C = (png_bytep*) malloc(sizeof(png_bytep) * (height));

//    //log
//    printf("[%s : %d] malloc done for row_pointers_C\n", 
//            base_name(__FILE__), __LINE__);

    
    for (y=0; y < height; y++)
            row_pointers_C[y] = 
                    (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
    
//    //log
//    printf("[%s : %d] malloc done for => row_pointers_C[y]\n", base_name(__FILE__), __LINE__);

    
    for (y = 0; y < height; y++) {

        png_byte* row = row_pointers_C[y];
//
        for (x=0; x<width; x++) {

            png_byte* ptr = &(row[x*3]);
            
            if (!strcmp(bg_name, "green")) {
                
                set_PixelVals(ptr, PIXEL_GREEN);

            } else if (!strcmp(bg_name, "red")) {
                
                set_PixelVals(ptr, PIXEL_RED);
                
            } else if (!strcmp(bg_name, "blue")) {
                
                set_PixelVals(ptr, PIXEL_BLUE);
                
            } else if (!strcmp(bg_name, "purple")) {
                
                set_PixelVals(ptr, PIXEL_PURPLE);
                
            } else if (!strcmp(bg_name, "white")) {
                
                set_PixelVals(ptr, PIXEL_WHITE);
                
            } else if (!strcmp(bg_name, "black")) {
                
                set_PixelVals(ptr, PIXEL_BLACK);
                
            }

//            set_PixelVals(ptr, PIXEL_GREEN);
//            set_PixelVals(ptr, 0, 100, 0);
        //log
//            ptr[0] = 0; ptr[1] = 0; ptr[2] = 200;
//                  ptr[1] = 0; ptr[2] = 0;

        }
    }//for (y=0; y<height; y++)    
    
    //log
    printf("[%s : %d] init_Row_Pointers_C() => done\n", base_name(__FILE__), __LINE__);

    
}//init_Row_Pointers_C

void init_Row_Pointers_B
(png_structp png_ptr, png_infop info_ptr)
{
    
    int x, y;   // iterator
    
    int width = png_ptr->width;
    int height = png_ptr->height;
    
    row_pointers_B = (png_bytep*) malloc(sizeof(png_bytep) * (height));

//    //log
//    printf("[%s : %d] malloc done for row_pointers_B\n", 
//            base_name(__FILE__), __LINE__);

    
    for (y=0; y < height; y++)
            row_pointers_B[y] = 
                    (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
    
    consolColor_Change(LIGHT_YELLOW);

    //log
    printf("[%s : %d] init_Row_Pointers_B() => done\n",
            base_name(__FILE__), __LINE__);

    consolColor_Reset();
//    //log
//    printf("[%s : %d] init_Row_Pointers_B() => done\n", base_name(__FILE__), __LINE__);
    
}//init_Row_Pointers_B

void init_Row_Pointers_B__Histo
(png_structp png_ptr, png_infop info_ptr, char *bg_color_name)
{
    
    int x, y;   // iterator
    
    int width = png_ptr->width;
    int height = png_ptr->height;
    
    //log
    printf("[%s : %d] width, height => %d, %d\n", 
            base_name(__FILE__), __LINE__, width, height);

    //log
    printf("[%s : %d] png_get_rowbytes(png_ptr,info_ptr) => %d\n", 
            base_name(__FILE__), __LINE__, png_get_rowbytes(png_ptr,info_ptr));

    
    /**************************
     * Malloc
     **************************/
    row_pointers_B = (png_bytep*) malloc(sizeof(png_bytep) * (height));

    for (y=0; y < height; y++)
            row_pointers_B[y] = 
                    (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

    // C
    row_pointers_C = (png_bytep*) malloc(sizeof(png_bytep) * (height));

    for (y=0; y < height; y++)
            row_pointers_C[y] = 
                    (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

    /**************************
     * Bg color
     **************************/
    for (y = 0; y < height; y++) {

        png_byte* row = row_pointers_B[y];
        png_byte* row_C = row_pointers_C[y];
//
        for (x=0; x<width; x++) {

            png_byte* ptr = &(row[x*3]);
            png_byte* ptr_C = &(row_C[x*3]);
            
            if (!strcmp(bg_color_name, "green")) {
                
                set_PixelVals(ptr, PIXEL_GREEN);
                set_PixelVals(ptr_C, PIXEL_GREEN);

            } else if (!strcmp(bg_color_name, "red")) {
                
                set_PixelVals(ptr, PIXEL_RED);
                set_PixelVals(ptr_C, PIXEL_RED);
                
            } else if (!strcmp(bg_color_name, "blue")) {
                
                set_PixelVals(ptr, PIXEL_BLUE);
                set_PixelVals(ptr_C, PIXEL_BLUE);
                
            } else if (!strcmp(bg_color_name, "purple")) {
                
                set_PixelVals(ptr, PIXEL_PURPLE);
                set_PixelVals(ptr_C, PIXEL_PURPLE);
                
            } else if (!strcmp(bg_color_name, "white")) {
                
                set_PixelVals(ptr, PIXEL_WHITE);
                set_PixelVals(ptr_C, PIXEL_WHITE);
                
            } else if (!strcmp(bg_color_name, "black")) {
                
                set_PixelVals(ptr, PIXEL_BLACK);
                set_PixelVals(ptr_C, PIXEL_BLACK);
                
            } else if (!strcmp(bg_color_name, "gray")) {
                
                set_PixelVals(ptr, PIXEL_GRAY);
                set_PixelVals(ptr_C, PIXEL_GRAY);
                
            } else {
                
                consolColor_Change(RED);

                //log
                printf("[%s : %d] Unknown color name => %s\n",
                        base_name(__FILE__), __LINE__, bg_color_name);

                consolColor_Reset();
                
                exit(-1);
                
            }

        }
        
    }//for (y=0; y<height; y++)    
    
    consolColor_Change(LIGHT_YELLOW);

    //log
    printf("[%s : %d] init_Row_Pointers_B_Histo() => done\n",
            base_name(__FILE__), __LINE__);

    consolColor_Reset();
//    //log
//    printf("[%s : %d] init_Row_Pointers_B() => done\n", base_name(__FILE__), __LINE__);
    
}//void init_Row_Pointers_B__Histo

void set_PixelVals(png_byte* ptr, int r, int g, int b)
{
    ptr[0] = 255 * r / 100;
    ptr[1] = 255 * g / 100;
    ptr[2] = 255 * b / 100;
//    ptr[1] = g; ptr[2] = b;
//    ptr[0] = r; ptr[1] = g; ptr[2] = b;
}

void set_PixelVals_2(png_byte* ptr, int colors[3])
{
    ptr[0] = 255 * colors[0] / 100;
    ptr[1] = 255 * colors[1] / 100;
    ptr[2] = 255 * colors[2] / 100;
//    ptr[1] = g; ptr[2] = b;
//    ptr[0] = r; ptr[1] = g; ptr[2] = b;
}

void merge_PngSrcs
(
    int width_A, int height_A, 
    int width_B, int height_B, 
    int width_C, int height_C
)
{
    //log
    printf("[%s : %d] width_A, height_A => %d, %d\nwidth_B, height_B => %d, %d\nwidth_C, height_C => %d, %d", base_name(__FILE__), __LINE__,
            width_A, height_A,
            width_B, height_B,
            width_C, height_C
            );

    int x, x2, y;
    
    for(y = 0; y < height_B; y++) {
//    for(y = 0; y < height_A; y++) {
        
        png_byte *row_A = row_pointers_A[y];
        png_byte *row_B = row_pointers_B[y];
        png_byte *row_C = row_pointers_C[y];
        
        for(x = 0; x < width_A; x++) {
            
            png_byte *ptr_A = &(row_A[x * 3]);
            png_byte *ptr_C = &(row_C[x * 3]);
            
            ptr_C[0] = ptr_A[0];
            ptr_C[1] = ptr_A[1];
            ptr_C[2] = ptr_A[2];
            
            
        }//for(x = 0; x < width_A; x++)
    
        for(x2 = 0; x2 < width_B; x++, x2++) {
            
            png_byte *ptr_B = &(row_B[x2 * 3]);
            png_byte *ptr_C = &(row_C[x * 3]);
            
            ptr_C[0] = ptr_B[0];
            ptr_C[1] = ptr_B[1];
            ptr_C[2] = ptr_B[2];
            
            
        }//for(x = 0; x < width_A; x++)
    
    }//for(y = 0; y < height_B; y++)
    
    // chunk 2
    for(y = height_B; y < height_C; y++) {

        png_byte *row_A = row_pointers_A[y];
        png_byte *row_C = row_pointers_C[y];
        
        for(x = 0; x < width_A; x++) {
            
            png_byte *ptr_A = &(row_A[x * 3]);
            png_byte *ptr_C = &(row_C[x * 3]);
            
            ptr_C[0] = ptr_A[0];
            ptr_C[1] = ptr_A[1];
            ptr_C[2] = ptr_A[2];
            
            
        }//for(x = 0; x < width_A; x++)
        
    }
//<<<<<<< HEAD
//=======
    
    
}//void merge_PngSrcs

void merge_PngSrcs_Hori_General
(
    int width_A, int height_A, 
    int width_B, int height_B, 
    int width_C, int height_C
)
{
    //log
    printf("[%s : %d] width_A, height_A => %d, %d\n"
            "width_B, height_B => %d, %d\n"
            "width_C, height_C => %d, %d\n", base_name(__FILE__), __LINE__,
            width_A, height_A,
            width_B, height_B,
            width_C, height_C
            );

    if(height_A >= height_B) {
        
        _merge_PngSrcs_Hori_General_AlargerThanB
                (width_A, height_A,
                    width_B, height_B,
                    width_C, height_C);
        
    } else {
        
        _merge_PngSrcs_Hori_General_AsmallerThanB
                (width_A, height_A,
                    width_B, height_B,
                    width_C, height_C);
        
    }
    
//    int x, x2, y;
//    
//    for(y = 0; y < height_B; y++) {
////    for(y = 0; y < height_A; y++) {
//        
//        png_byte *row_A = row_pointers_A[y];
//        png_byte *row_B = row_pointers_B[y];
//        png_byte *row_C = row_pointers_C[y];
//        
//        for(x = 0; x < width_A; x++) {
//            
//            png_byte *ptr_A = &(row_A[x * 3]);
//            png_byte *ptr_C = &(row_C[x * 3]);
//            
//            ptr_C[0] = ptr_A[0];
//            ptr_C[1] = ptr_A[1];
//            ptr_C[2] = ptr_A[2];
//            
//            
//        }//for(x = 0; x < width_A; x++)
//    
//        for(x2 = 0; x2 < width_B; x++, x2++) {
//            
//            png_byte *ptr_B = &(row_B[x2 * 3]);
//            png_byte *ptr_C = &(row_C[x * 3]);
//            
//            ptr_C[0] = ptr_B[0];
//            ptr_C[1] = ptr_B[1];
//            ptr_C[2] = ptr_B[2];
//            
//            
//        }//for(x = 0; x < width_A; x++)
//    
//    }//for(y = 0; y < height_B; y++)
//    
//    // chunk 2
//    for(y = height_B; y < height_C; y++) {
//
//        png_byte *row_A = row_pointers_A[y];
//        png_byte *row_C = row_pointers_C[y];
//        
//        for(x = 0; x < width_A; x++) {
//            
//            png_byte *ptr_A = &(row_A[x * 3]);
//            png_byte *ptr_C = &(row_C[x * 3]);
//            
//            ptr_C[0] = ptr_A[0];
//            ptr_C[1] = ptr_A[1];
//            ptr_C[2] = ptr_A[2];
//            
//            
//        }//for(x = 0; x < width_A; x++)
//        
//    }//for(y = height_B; y < height_C; y++)
    
    
}//void merge_PngSrcs_Hori_General

void merge_PngSrcs_Verti_General
(
    int width_A, int height_A, 
    int width_B, int height_B, 
    int width_C, int height_C
)
{
    //log
    printf("[%s : %d] width_A, height_A => %d, %d\n"
            "width_B, height_B => %d, %d\n"
            "width_C, height_C => %d, %d\n", base_name(__FILE__), __LINE__,
            width_A, height_A,
            width_B, height_B,
            width_C, height_C
            );

    int x, y2, y;
    
    for(y = 0; y < height_A; y++) {
        
        png_byte *row_A = row_pointers_A[y];
//        png_byte *row_B = row_pointers_B[y];
        png_byte *row_C = row_pointers_C[y];
        
        for(x = 0; x < width_A; x++) {
            
            png_byte *ptr_A = &(row_A[x * 3]);
            png_byte *ptr_C = &(row_C[x * 3]);
            
            ptr_C[0] = ptr_A[0];
            ptr_C[1] = ptr_A[1];
            ptr_C[2] = ptr_A[2];
            
            
        }//for(x = 0; x < width_A; x++)
    
    }//for(y = 0; y < height_B; y++)
    
    for(y2 = 0; y < height_C; y++, y2++) {
//    for(y2 = 0; y < height_B; y++, y2++) {
        
//        png_byte *row_A = row_pointers_A[y];
        png_byte *row_B = row_pointers_B[y2];
        png_byte *row_C = row_pointers_C[y];
        
        for(x = 0; x < width_B; x++) {
            
            png_byte *ptr_B = &(row_B[x * 3]);
            png_byte *ptr_C = &(row_C[x * 3]);
            
            ptr_C[0] = ptr_B[0];
            ptr_C[1] = ptr_B[1];
            ptr_C[2] = ptr_B[2];
            
            
        }//for(x = 0; x < width_A; x++)
    
    }//for(y = 0; y < height_B; y++)
//    if(height_A >= height_B) {
//        
//        _merge_PngSrcs_Hori_General_AlargerThanB
//                (width_A, height_A,
//                    width_B, height_B,
//                    width_C, height_C);
//        
//    } else {
//        
//        _merge_PngSrcs_Hori_General_AsmallerThanB
//                (width_A, height_A,
//                    width_B, height_B,
//                    width_C, height_C);
//        
//    }
//>>>>>>> 0f4f09c7514cac2c887fbc3903bf226d583ffd04
    
}//void merge_PngSrcs_Verti_General

void _merge_PngSrcs_Hori_General_AlargerThanB
(
        int width_A, int height_A,
        int width_B, int height_B,
        int width_C, int height_C)
{
    //log
    printf("[%s : %d] _merge_PngSrcs_Hori_General_AlargerThanB()\n",
            base_name(__FILE__), __LINE__);
    
}//void merge_PngSrcs

void merge_PngSrcs_Hori_General
(
    int width_A, int height_A, 
    int width_B, int height_B, 
    int width_C, int height_C
)
{
    //log
    printf("[%s : %d] width_A, height_A => %d, %d\n"
            "width_B, height_B => %d, %d\n"
            "width_C, height_C => %d, %d\n", base_name(__FILE__), __LINE__,
            width_A, height_A,
            width_B, height_B,
            width_C, height_C
            );

    if(height_A >= height_B) {
        
        _merge_PngSrcs_Hori_General_AlargerThanB
                (width_A, height_A,
                    width_B, height_B,
                    width_C, height_C);
        
    } else {
        
        _merge_PngSrcs_Hori_General_AsmallerThanB
                (width_A, height_A,
                    width_B, height_B,
                    width_C, height_C);
        
    }
    
//    int x, x2, y;
//    
//    for(y = 0; y < height_B; y++) {
////    for(y = 0; y < height_A; y++) {
//        
//        png_byte *row_A = row_pointers_A[y];
//        png_byte *row_B = row_pointers_B[y];
//        png_byte *row_C = row_pointers_C[y];
//        
//        for(x = 0; x < width_A; x++) {
//            
//            png_byte *ptr_A = &(row_A[x * 3]);
//            png_byte *ptr_C = &(row_C[x * 3]);
//            
//            ptr_C[0] = ptr_A[0];
//            ptr_C[1] = ptr_A[1];
//            ptr_C[2] = ptr_A[2];
//            
//            
//        }//for(x = 0; x < width_A; x++)
//    
//        for(x2 = 0; x2 < width_B; x++, x2++) {
//            
//            png_byte *ptr_B = &(row_B[x2 * 3]);
//            png_byte *ptr_C = &(row_C[x * 3]);
//            
//            ptr_C[0] = ptr_B[0];
//            ptr_C[1] = ptr_B[1];
//            ptr_C[2] = ptr_B[2];
//            
//            
//        }//for(x = 0; x < width_A; x++)
//    
//    }//for(y = 0; y < height_B; y++)
//    
//    // chunk 2
//    for(y = height_B; y < height_C; y++) {
//
//        png_byte *row_A = row_pointers_A[y];
//        png_byte *row_C = row_pointers_C[y];
//        
//        for(x = 0; x < width_A; x++) {
//            
//            png_byte *ptr_A = &(row_A[x * 3]);
//            png_byte *ptr_C = &(row_C[x * 3]);
//            
//            ptr_C[0] = ptr_A[0];
//            ptr_C[1] = ptr_A[1];
//            ptr_C[2] = ptr_A[2];
//            
//            
//        }//for(x = 0; x < width_A; x++)
//        
//    }//for(y = height_B; y < height_C; y++)
    
    
}//void merge_PngSrcs_Hori_General

void _merge_PngSrcs_Hori_General_AlargerThanB
(
        int width_A, int height_A,
        int width_B, int height_B,
        int width_C, int height_C)
{
    //log
    printf("[%s : %d] _merge_PngSrcs_Hori_General_AlargerThanB()\n",
            base_name(__FILE__), __LINE__);
    
    int x, x2, y;
    
    for(y = 0; y < height_B; y++) {
//    for(y = 0; y < height_A; y++) {
        
        png_byte *row_A = row_pointers_A[y];
        png_byte *row_B = row_pointers_B[y];
        png_byte *row_C = row_pointers_C[y];
        
        for(x = 0; x < width_A; x++) {
            
            png_byte *ptr_A = &(row_A[x * 3]);
            png_byte *ptr_C = &(row_C[x * 3]);
            
            ptr_C[0] = ptr_A[0];
            ptr_C[1] = ptr_A[1];
            ptr_C[2] = ptr_A[2];
            
            
        }//for(x = 0; x < width_A; x++)
    
        for(x2 = 0; x2 < width_B; x++, x2++) {
            
            png_byte *ptr_B = &(row_B[x2 * 3]);
            png_byte *ptr_C = &(row_C[x * 3]);
            
            ptr_C[0] = ptr_B[0];
            ptr_C[1] = ptr_B[1];
            ptr_C[2] = ptr_B[2];
            
            
        }//for(x = 0; x < width_A; x++)
    
    }//for(y = 0; y < height_B; y++)
    
    // chunk 2
    for(y = height_B; y < height_C; y++) {

        png_byte *row_A = row_pointers_A[y];
        png_byte *row_C = row_pointers_C[y];
        
        for(x = 0; x < width_A; x++) {
            
            png_byte *ptr_A = &(row_A[x * 3]);
            png_byte *ptr_C = &(row_C[x * 3]);
            
            ptr_C[0] = ptr_A[0];
            ptr_C[1] = ptr_A[1];
            ptr_C[2] = ptr_A[2];
            
            
        }//for(x = 0; x < width_A; x++)
        
    }//for(y = height_B; y < height_C; y++)
    
}//void _merge_PngSrcs_Hori_General_AlargerThanB

void _merge_PngSrcs_Hori_General_AsmallerThanB
(
        int width_A, int height_A,
        int width_B, int height_B,
        int width_C, int height_C)
{
    //log
    printf("[%s : %d] _merge_PngSrcs_Hori_General_AsmallerThanB()\n",
            base_name(__FILE__), __LINE__);

    int x, x2, y;
    
    for(y = 0; y < height_A; y++) {
        
        png_byte *row_A = row_pointers_A[y];
        png_byte *row_B = row_pointers_B[y];
        png_byte *row_C = row_pointers_C[y];
        
        for(x = 0; x < width_A; x++) {
            
            png_byte *ptr_A = &(row_A[x * 3]);
            png_byte *ptr_C = &(row_C[x * 3]);
            
            ptr_C[0] = ptr_A[0];
            ptr_C[1] = ptr_A[1];
            ptr_C[2] = ptr_A[2];
            
            
        }//for(x = 0; x < width_A; x++)
    
        for(x2 = 0; x2 < width_B; x++, x2++) {
            
            png_byte *ptr_B = &(row_B[x2 * 3]);
            png_byte *ptr_C = &(row_C[x * 3]);
            
            ptr_C[0] = ptr_B[0];
            ptr_C[1] = ptr_B[1];
            ptr_C[2] = ptr_B[2];
            
            
        }//for(x = 0; x < width_A; x++)
    
    }//for(y = 0; y < height_B; y++)
    
    // chunk 2
    for(y = height_A; y < height_C; y++) {

        png_byte *row_B = row_pointers_B[y];
        png_byte *row_C = row_pointers_C[y];
        
        for(x = width_A, x2 = 0; x2 < width_B; x++, x2++) {
            
            png_byte *ptr_B = &(row_B[x2 * 3]);
            png_byte *ptr_C = &(row_C[x * 3]);
            
            ptr_C[0] = ptr_B[0];
            ptr_C[1] = ptr_B[1];
            ptr_C[2] = ptr_B[2];
            
            
        }//for(x = 0; x < width_A; x++)
        
    }//for(y = height_B; y < height_C; y++)
    
}//void _merge_PngSrcs_Hori_General_AsmallerThanB
//<<<<<<< HEAD
//=======

void process_file__RGB
(png_structp png_ptr_A, png_structp png_ptr_B,
        int **rgb_vals, ProcMode process_mode)
//        int *rgb_vals[3], ProcMode process_mode)
{
    int width = png_ptr_A->width;
    int height = png_ptr_A->height;
    
    int x, y;
    
    //log
    printf("[%s : %d] process_mode => %d\n", 
            base_name(__FILE__), __LINE__, process_mode);
    printf("[%s : %d] rgb => %d\n", 
            base_name(__FILE__), __LINE__, rgb);

    
    //log
    printf("[%s : %d] rgb_vals[0] => %d\n", base_name(__FILE__), __LINE__, (int) rgb_vals[0]);
//    printf("[%s : %d] (*rgb_vals[0]) => %d\n", base_name(__FILE__), __LINE__, (*rgb_vals[0]));

    
    for(y = 0; y < height; y++) {
        
        png_byte *row_A = row_pointers_A[y];
        png_byte *row_B = row_pointers_B[y];
//        png_byte *row_C = row_pointers_C[y];
        
        for(x = 0; x < width; x++) {
            
            png_byte *ptr_A = &(row_A[x * 3]);
            png_byte *ptr_B = &(row_B[x * 3]);
//            png_byte *ptr_B = &(row_B[x * 3]);
            
            if (process_mode == rgb) {

                int r = (int) rgb_vals[0];
                int g = (int) rgb_vals[1];
                int b = (int) rgb_vals[2];

                ptr_B[0] = ptr_A[0] * r / 100;
                ptr_B[1] = ptr_A[1] * g / 100;
                ptr_B[2] = ptr_A[2] * b / 100;
            
            } else {
                
                int i;
                
                int max_bright = 100;
                int minimum_bright = 50;
                
                
                
                for (i = 0; i < 3; i++) {

                    if (ptr_A[i] > max_bright) {

                        ptr_B[i] = 255;
//                        ptr_B[i] = max_bright;

                    } else if (ptr_A[i] < minimum_bright) {

                        ptr_B[i] = 0;

                    } else {
                        
                        ptr_B[i] = ptr_A[i];
                        
                    }
                    
                }

            }
//            ptr_B[0] = ptr_A[0] * (*rgb_vals[0]) / 100;
//            ptr_B[1] = ptr_A[1] * (*rgb_vals[1]) / 100;
//            ptr_B[2] = ptr_A[2] * (*rgb_vals[2]) / 100;
//            ptr_B[2] = ptr_A[2] * rgb_vals[2] / 100;
//            ptr_B[1] = ptr_A[1];
//            ptr_B[2] = ptr_A[2];
            
            
        }//for(x = 0; x < width_A; x++)
    
    }//for(y = 0; y < height_B; y++)   
    
    //log
    printf("[%s : %d] row_pointers_B[0][0] => %d\n", 
            base_name(__FILE__), __LINE__, row_pointers_B[0][0]);
    printf("[%s : %d] row_pointers_B[0][10] => %d\n", 
            base_name(__FILE__), __LINE__, row_pointers_B[0][10]);
    printf("[%s : %d] row_pointers_B[0][20] => %d\n", 
            base_name(__FILE__), __LINE__, row_pointers_B[0][20]);

    
}

void gen_HistoData(int width_A, int height_A)
{
    int x, y;
    
    for (y = 0; y < height_A; y++) {

        png_byte *row_A = row_pointers_A[y];
        
        for (x = 0; x < width_A; x++) {

            png_byte *ptr_A = &(row_A[x * 3]);
            
            histo[ptr_A[1]] ++;
//            histo[ptr_A[2]] ++;
//            histo[ptr_A[0]] ++;

        }

    }//for (y = 0; y < height_A; y++)

    /**************************
     * Get: range
     **************************/
    // max
    int tmp = histo[0];
    int i;      // iterator
    
    for (i = 0; i < MAX_BRIGHTNESS; i++) {

        if(histo[i] > tmp)
            tmp = histo[i];

    }
    
    histo_range[0] = tmp;
    
    // minimum
    tmp = histo[0];
    
    for (i = 0; i < MAX_BRIGHTNESS; i++) {

        if(histo[i] < tmp)
            tmp = histo[i];

    }
    
    histo_range[1] = tmp;
    
    /**************************
     * Histo data => Convert to the range
     **************************/
    //test
    //log
    printf("[%s : %d] max in histo[] => %d\n", 
            base_name(__FILE__), __LINE__, get_max_element(histo, MAX_BRIGHTNESS));

    
    for (i = 0; i < MAX_BRIGHTNESS; i++) {

        histo[i] = MAX_BRIGHTNESS * histo[i] / histo_range[0];

    }

    //log
    printf("[%s : %d] max in histo[] => %d\n", 
            base_name(__FILE__), __LINE__, get_max_element(histo, MAX_BRIGHTNESS));


}//void gen_HistoData(int width_A, int height_A)

//void gen_HistoData_RGB(int, int, char *)
void gen_HistoData_RGB
(int width_A, int height_A, char *rgb_opt)
{
    int x, y;
    
    for (y = 0; y < height_A; y++) {

        png_byte *row_A = row_pointers_A[y];
        
        for (x = 0; x < width_A; x++) {

            png_byte *ptr_A = &(row_A[x * 3]);
            
            if (!strcmp(rgb_opt, Histo_RGB[0])) { // R
                
                histo_R[ptr_A[0]] ++;

            } else if (!strcmp(rgb_opt, Histo_RGB[1])) { // G
                
                histo_G[ptr_A[1]] ++;
                
            } else if (!strcmp(rgb_opt, Histo_RGB[2])) { // B
                
                histo_B[ptr_A[2]] ++;
                
            } else if (!strcmp(rgb_opt, Histo_RGB[3])) { // ALL
                
                consolColor_Change(RED);

                //log
                printf("[%s : %d] Sorry. Under construction for rgb option => %s\n",
                        base_name(__FILE__), __LINE__, rgb_opt);

                consolColor_Reset();
                
                exit(-1);
                
            }
            
//            histo[ptr_A[1]] ++;
//            histo[ptr_A[2]] ++;
//            histo[ptr_A[0]] ++;

        }

    }//for (y = 0; y < height_A; y++)

    /**************************
     * Get: range
     **************************/
    // max
    int *histo_tmp;
//    int histo_tmp[MAX_BRIGHTNESS];
    
    if (!strcmp(rgb_opt, Histo_RGB[0])) // R
                
                histo_tmp = histo_R;

    else if (!strcmp(rgb_opt, Histo_RGB[1])) // G
                
                histo_tmp = histo_G;
                
    else if (!strcmp(rgb_opt, Histo_RGB[2])) // B
                
                histo_tmp = histo_B;
                
    else if (!strcmp(rgb_opt, Histo_RGB[3])) { // ALL
                
                consolColor_Change(RED);

                //log
                printf("[%s : %d] Sorry. Under construction for rgb option => %s\n",
                        base_name(__FILE__), __LINE__, rgb_opt);

                consolColor_Reset();
                
                exit(-1);
                
    }
    
    /**************************
     * Set: histo_range
     **************************/
    int tmp = histo_tmp[0];
    int i;      // iterator
    
    for (i = 0; i < MAX_BRIGHTNESS; i++) {

        if(histo_tmp[i] > tmp)
            tmp = histo_tmp[i];

    }
    
    histo_range[0] = tmp;
    
    // minimum
    tmp = histo_tmp[0];
    
    for (i = 0; i < MAX_BRIGHTNESS; i++) {

        if(histo_tmp[i] < tmp)
            tmp = histo_tmp[i];

    }
    
    histo_range[1] = tmp;
    
    /**************************
     * Histo data => Convert to the range
     **************************/
    //test
    //log
    printf("[%s : %d] max in histo_tmp[] => %d\n", 
            base_name(__FILE__), __LINE__, get_max_element(histo, MAX_BRIGHTNESS));

    
    for (i = 0; i < MAX_BRIGHTNESS; i++) {

        histo_tmp[i] = MAX_BRIGHTNESS * histo_tmp[i] / histo_range[0];

    }

    //log
    printf("[%s : %d] max in histo_tmp[] => %d\n", 
            base_name(__FILE__), __LINE__, get_max_element(histo, MAX_BRIGHTNESS));


}//void gen_HistoData(int width_A, int height_A)

void gen_HistoPixels()
{
    int width = histo_png_size[0];
    int height = histo_png_size[1];
    
    int x, y;
    
    //log
    printf("[%s : %d] Start => for loop\n", base_name(__FILE__), __LINE__);

    
    for (y = 0; y < height; y++) {

        png_byte *row_B = row_pointers_B[y];
        
//        //log
//        printf("[%s : %d] y => %d\n", base_name(__FILE__), __LINE__, y);

        
        for (x = 0; x < histo[y]; x++) {
            
//            //log
//            printf("[%s : %d] histo[y] => %d\n", 
//                    base_name(__FILE__), __LINE__, histo[y]);


            png_byte *ptr_B = &(row_B[x * 3]);
            
            int colors[3] = {PIXEL_GREEN};
//            colors[] = {PIXEL_GREEN};
            
            set_PixelVals_2(ptr_B, colors);
//            set_PixelVals(ptr_B, PIXEL_GREEN);
//            set_PixelVals(ptr_B, PIXEL_BLUE);
//            ptr_B[0] = 255;
//            ptr_B[1] = 0;
//            ptr_B[2] = 0;

        }

    }//for (y = 0; y < height_A; y++)

    /**************************
     * Rotate pixels
     **************************/
    for (y = 0; y < height; y++) {

//        png_byte *row_B = row_pointers_B[0];
        png_byte *row_B = row_pointers_B[y];
        
//        //log
//        printf("[%s : %d] y => %d\n", base_name(__FILE__), __LINE__, y);

        
        for (x = 0; x < width; x++) {
            
            png_byte *ptr_B = &(row_B[x * 3]);
            
//            //log
//            printf("[%s : %d] (width - 1) - x = %d\n", 
//                base_name(__FILE__), __LINE__, ((width - 1) - x));

            
            row_pointers_C[(width - 1) - x][y * 3 + 0] = ptr_B[0];
            row_pointers_C[(width - 1) - x][y * 3 + 1] = ptr_B[1];
            row_pointers_C[(width - 1) - x][y * 3 + 2] = ptr_B[2];
//            row_pointers_C[(width - 1) - x][0] = ptr_B[0];
//            row_pointers_C[(width - 1) - x][1] = ptr_B[1];
//            row_pointers_C[(width - 1) - x][2] = ptr_B[2];
//            row_pointers_C[0][(width - 1) - x] = ptr_B[0];
//            row_pointers_C[1][(width - 1) - x] = ptr_B[1];
//            row_pointers_C[2][(width - 1) - x] = ptr_B[2];
//            row_pointers_C[x][y] = row_pointers_B[y][(width - 1) - x];
//            row_pointers_C[x][y] = row_pointers_B[y][width - 1];
//        for (x = 0; x < histo[y]; x++) {
            
//            //log
//            printf("[%s : %d] histo[y] => %d\n", 
//                    base_name(__FILE__), __LINE__, histo[y]);


//            png_byte *ptr_B = &(row_B[x * 3]);
//            
//            int colors[3] = {PIXEL_GREEN};
////            colors[] = {PIXEL_GREEN};
//            
//            set_PixelVals_2(ptr_B, colors);
//            set_PixelVals(ptr_B, PIXEL_GREEN);
//            set_PixelVals(ptr_B, PIXEL_BLUE);
//            ptr_B[0] = 255;
//            ptr_B[1] = 0;
//            ptr_B[2] = 0;

        }

    }//for (y = 0; y < height_A; y++)
    
////    for (y = 0; y < height; y++) {
//
//        png_byte *row_B = row_pointers_B[0];
////        png_byte *row_B = row_pointers_B[y];
//        
////        //log
////        printf("[%s : %d] y => %d\n", base_name(__FILE__), __LINE__, y);
//
//        
//        for (x = 0; x < width; x++) {
//            
//            png_byte *ptr_B = &(row_B[x * 3]);
//            
//            //log
//            printf("[%s : %d] (width - 1) - x = %d\n", 
//                base_name(__FILE__), __LINE__, ((width - 1) - x));
//
//            
//            row_pointers_C[(width - 1) - x][0] = ptr_B[0];
//            row_pointers_C[(width - 1) - x][1] = ptr_B[1];
//            row_pointers_C[(width - 1) - x][2] = ptr_B[2];
////            row_pointers_C[0][(width - 1) - x] = ptr_B[0];
////            row_pointers_C[1][(width - 1) - x] = ptr_B[1];
////            row_pointers_C[2][(width - 1) - x] = ptr_B[2];
////            row_pointers_C[x][y] = row_pointers_B[y][(width - 1) - x];
////            row_pointers_C[x][y] = row_pointers_B[y][width - 1];
////        for (x = 0; x < histo[y]; x++) {
//            
////            //log
////            printf("[%s : %d] histo[y] => %d\n", 
////                    base_name(__FILE__), __LINE__, histo[y]);
//
//
////            png_byte *ptr_B = &(row_B[x * 3]);
////            
////            int colors[3] = {PIXEL_GREEN};
//////            colors[] = {PIXEL_GREEN};
////            
////            set_PixelVals_2(ptr_B, colors);
////            set_PixelVals(ptr_B, PIXEL_GREEN);
////            set_PixelVals(ptr_B, PIXEL_BLUE);
////            ptr_B[0] = 255;
////            ptr_B[1] = 0;
////            ptr_B[2] = 0;
//
//        }
//
////    }//for (y = 0; y < height_A; y++)
//    
    row_pointers_B = row_pointers_C;
    
}//void gen_HistoPixels()

void gen_HistoPixels_RGB(char *rgb_opt)
{
    int width = histo_png_size[0];
    int height = histo_png_size[1];
    
    int x, y;
    
    //log
    printf("[%s : %d] Start => for loop\n", base_name(__FILE__), __LINE__);

    
    for (y = 0; y < height; y++) {

        png_byte *row_B = row_pointers_B[y];
        
//        //log
//        printf("[%s : %d] y => %d\n", base_name(__FILE__), __LINE__, y);
        int width_max;
        
        if (!strcmp(rgb_opt, Histo_RGB[0])) { // R

            width_max = histo_R[y];

        } else if (!strcmp(rgb_opt, Histo_RGB[1])) { // G

            width_max = histo_G[y];

        } else if (!strcmp(rgb_opt, Histo_RGB[2])) { // B

            width_max = histo_B[y];

        } else if (!strcmp(rgb_opt, Histo_RGB[3])) { // ALL

            consolColor_Change(RED);

            //log
            printf("[%s : %d] Sorry. Under construction for rgb option => %s\n",
                    base_name(__FILE__), __LINE__, rgb_opt);

            consolColor_Reset();

            exit(-1);

        }
        
        
        for (x = 0; x < width_max; x++) {
//        for (x = 0; x < histo[y]; x++) {
            
//            //log
//            printf("[%s : %d] histo[y] => %d\n", 
//                    base_name(__FILE__), __LINE__, histo[y]);


            png_byte *ptr_B = &(row_B[x * 3]);
            
            if (!strcmp(rgb_opt, Histo_RGB[0])) { // R
                
                int colors[3] = {PIXEL_RED};

                set_PixelVals_2(ptr_B, colors);

            } else if (!strcmp(rgb_opt, Histo_RGB[1])) { // G
                
                int colors[3] = {PIXEL_GREEN};

                set_PixelVals_2(ptr_B, colors);
                
            } else if (!strcmp(rgb_opt, Histo_RGB[2])) { // B
                
                int colors[3] = {PIXEL_BLUE};

                set_PixelVals_2(ptr_B, colors);
                
            } else if (!strcmp(rgb_opt, Histo_RGB[3])) { // ALL
                
                consolColor_Change(RED);

                //log
                printf("[%s : %d] Sorry. Under construction for rgb option => %s\n",
                        base_name(__FILE__), __LINE__, rgb_opt);

                consolColor_Reset();
                
                exit(-1);
                
            }
            
//            int colors[3] = {PIXEL_GREEN};
////            colors[] = {PIXEL_GREEN};
//            
//            set_PixelVals_2(ptr_B, colors);
//            set_PixelVals(ptr_B, PIXEL_GREEN);
//            set_PixelVals(ptr_B, PIXEL_BLUE);
//            ptr_B[0] = 255;
//            ptr_B[1] = 0;
//            ptr_B[2] = 0;

        }

    }//for (y = 0; y < height_A; y++)

    /**************************
     * Rotate pixels
     **************************/
    for (y = 0; y < height; y++) {

//        png_byte *row_B = row_pointers_B[0];
        png_byte *row_B = row_pointers_B[y];
        
//        //log
//        printf("[%s : %d] y => %d\n", base_name(__FILE__), __LINE__, y);

        
        for (x = 0; x < width; x++) {
            
            png_byte *ptr_B = &(row_B[x * 3]);
            
//            //log
//            printf("[%s : %d] (width - 1) - x = %d\n", 
//                base_name(__FILE__), __LINE__, ((width - 1) - x));

            
            row_pointers_C[(width - 1) - x][y * 3 + 0] = ptr_B[0];
            row_pointers_C[(width - 1) - x][y * 3 + 1] = ptr_B[1];
            row_pointers_C[(width - 1) - x][y * 3 + 2] = ptr_B[2];
//            row_pointers_C[(width - 1) - x][0] = ptr_B[0];
//            row_pointers_C[(width - 1) - x][1] = ptr_B[1];
//            row_pointers_C[(width - 1) - x][2] = ptr_B[2];
//            row_pointers_C[0][(width - 1) - x] = ptr_B[0];
//            row_pointers_C[1][(width - 1) - x] = ptr_B[1];
//            row_pointers_C[2][(width - 1) - x] = ptr_B[2];
//            row_pointers_C[x][y] = row_pointers_B[y][(width - 1) - x];
//            row_pointers_C[x][y] = row_pointers_B[y][width - 1];
//        for (x = 0; x < histo[y]; x++) {
            
//            //log
//            printf("[%s : %d] histo[y] => %d\n", 
//                    base_name(__FILE__), __LINE__, histo[y]);


//            png_byte *ptr_B = &(row_B[x * 3]);
//            
//            int colors[3] = {PIXEL_GREEN};
////            colors[] = {PIXEL_GREEN};
//            
//            set_PixelVals_2(ptr_B, colors);
//            set_PixelVals(ptr_B, PIXEL_GREEN);
//            set_PixelVals(ptr_B, PIXEL_BLUE);
//            ptr_B[0] = 255;
//            ptr_B[1] = 0;
//            ptr_B[2] = 0;

        }

    }//for (y = 0; y < height_A; y++)
    
////    for (y = 0; y < height; y++) {
//
//        png_byte *row_B = row_pointers_B[0];
////        png_byte *row_B = row_pointers_B[y];
//        
////        //log
////        printf("[%s : %d] y => %d\n", base_name(__FILE__), __LINE__, y);
//
//        
//        for (x = 0; x < width; x++) {
//            
//            png_byte *ptr_B = &(row_B[x * 3]);
//            
//            //log
//            printf("[%s : %d] (width - 1) - x = %d\n", 
//                base_name(__FILE__), __LINE__, ((width - 1) - x));
//
//            
//            row_pointers_C[(width - 1) - x][0] = ptr_B[0];
//            row_pointers_C[(width - 1) - x][1] = ptr_B[1];
//            row_pointers_C[(width - 1) - x][2] = ptr_B[2];
////            row_pointers_C[0][(width - 1) - x] = ptr_B[0];
////            row_pointers_C[1][(width - 1) - x] = ptr_B[1];
////            row_pointers_C[2][(width - 1) - x] = ptr_B[2];
////            row_pointers_C[x][y] = row_pointers_B[y][(width - 1) - x];
////            row_pointers_C[x][y] = row_pointers_B[y][width - 1];
////        for (x = 0; x < histo[y]; x++) {
//            
////            //log
////            printf("[%s : %d] histo[y] => %d\n", 
////                    base_name(__FILE__), __LINE__, histo[y]);
//
//
////            png_byte *ptr_B = &(row_B[x * 3]);
////            
////            int colors[3] = {PIXEL_GREEN};
//////            colors[] = {PIXEL_GREEN};
////            
////            set_PixelVals_2(ptr_B, colors);
////            set_PixelVals(ptr_B, PIXEL_GREEN);
////            set_PixelVals(ptr_B, PIXEL_BLUE);
////            ptr_B[0] = 255;
////            ptr_B[1] = 0;
////            ptr_B[2] = 0;
//
//        }
//
////    }//for (y = 0; y < height_A; y++)
//    
    row_pointers_B = row_pointers_C;
    
}//void gen_HistoPixels()

char *get_Opt_Value(char **argv, const char *opt)
{
    char *opt_val;
    
    int i = 0;
    int flag = false;   // true if "-rgb" values given
    
    while(*(argv + i) != NULL) {
        
        if(!strcmp(*(argv + i), opt)) {
//        if(!strcmp(*(argv + i), "-dst")) {
            
            i ++;
            
            if(*(argv + i) != NULL) {
                
                int len = strlen(*(argv + i));
                
                opt_val = (char *) malloc(sizeof(char) * (len + 1));
                
                strcpy(opt_val, *(argv + i));
                
                opt_val[len] = '\0';
                
                flag = true;
                
                break;
                
            } else {

                consolColor_Change(RED);

                //log
                printf("[%s : %d] value not given for \"%s\"\n", 
                        base_name(__FILE__), __LINE__, opt);

                consolColor_Reset();

                exit(-1);
                
            }
            
        }
        
        i ++;
        
    }//while(*(argv + i) != NULL)

    if(flag == false) {
        
        //log
        printf("[%s : %d] \"%s\" option => not given\n", 
                base_name(__FILE__), __LINE__, opt);
//        printf("option => not given\n");
        
        exit(-1);

    }

    /**************************
     * Validate: opt value => in the array?
     **************************/
    int res_i =  is_InArray(opt_val, Histo_RGB, Histo_RGB_len);
    
    if(res_i != true) {
        
        consolColor_Change(RED);

        //log
        printf("[%s : %d] Unknown option value for '%s' => %s\n",
                base_name(__FILE__), __LINE__, opt, opt_val);
        
        //log
        char *msg = join(',', Histo_RGB, Histo_RGB_len);
        
        printf("[%s : %d] Available values =L> %s (%d items)\n", 
                base_name(__FILE__), __LINE__, msg, Histo_RGB_len);


        consolColor_Reset();
        
        exit(-1);
        
    }
    
    return opt_val;   
    
}

char *modify_DstFileName_Histo_RGB
(char *file_dst, char *opt_RGB)
{
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
        
//        free(file_dst);
        
        char *label = "_rgb=";
        
//        char *rgb_info = (char *) malloc(sizeof(char) * (11 + 1));
//        
//        sprintf(rgb_info, "%d,%d,%d", RGB[0], RGB[1], RGB[2]);
        
        char *rgb_info = concat(label, opt_RGB);
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

        
    } else {//if (tokens != NULL)
        
        consolColor_Change(RED);

        //log
        printf("[%s : %d] tokens => NULL\n",
                base_name(__FILE__), __LINE__);

        consolColor_Reset();
        
        exit(-1);
        
//        return dst;
//        return argv[3];

    }//if (tokens != NULL)
    
}//char *modify_DstFileName_Histo_RGB
//>>>>>>> 0f4f09c7514cac2c887fbc3903bf226d583ffd04
