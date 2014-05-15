#ifndef PNGLIB_H
#include "include/pnglib.h"
#include "include/pnginfo.h"
#endif

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
(png_structp png_ptr, png_infop info_ptr)
{
    
    int x, y;   // iterator
    
    int width = png_ptr->width;
    int height = png_ptr->height;
    
    row_pointers_C = (png_bytep*) malloc(sizeof(png_bytep) * (height));

    //log
    printf("[%s : %d] malloc done for row_pointers_C\n", 
            base_name(__FILE__), __LINE__);

    
    for (y=0; y < height; y++)
            row_pointers_C[y] = 
                    (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
    
    //log
    printf("[%s : %d] malloc done for => row_pointers_C[y]\n", base_name(__FILE__), __LINE__);

    
    for (y = 0; y < height; y++) {

        png_byte* row = row_pointers_C[y];
//
        for (x=0; x<width; x++) {

            png_byte* ptr = &(row[x*3]);

        //log
            ptr[0] = 0; ptr[1] = 0; ptr[2] = 200;
//                  ptr[1] = 0; ptr[2] = 0;

        }
    }//for (y=0; y<height; y++)    
    
    //log
    printf("[%s : %d] init_Row_Pointers_C() => done\n", base_name(__FILE__), __LINE__);

    
}//init_Row_Pointers_C
