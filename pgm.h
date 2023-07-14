/**
 *   -- FROM GIVEN LINKS --
 * 
 *   There is exactly one image in a file.
 *   The magic number is P2 instead of P5.
 *   Each pixel in the raster is represented as an 
 *   ASCII decimal number (of arbitrary size).
 *   Each pixel in the raster has white space before and after it. 
 *   There must be at least 
 *   one character of white space between any two pixels, 
 *   but there is no maximum.
 *   No line should be longer than 70 characters. 
 *
*/


#ifndef PGM_H
#define PGM_H

/*max size of an image*/
#include "linkedlist.h"
typedef struct {
    int x;
    int y;
    int new_value;
} xyz;

typedef struct PGMstructure 
{
  int maxVal;
  int width;
  int height;
  unsigned char **img_data;
  char type[3];
} PGMImage;

void getPGMfile (char filename[], PGMImage *img);
void save(PGMImage *img);
void save_rle(LinkedList *ll);
void open_rle(const char *rle_filename, xyz);
#endif