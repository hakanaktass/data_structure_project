#ifndef RLE_H
#define RLE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "pgm.h"
#include <conio.h>    // Getch function
#include <ctype.h>    // is space function
#include "linkedlist.h"

LinkedList* compress(PGMImage *img);


#endif