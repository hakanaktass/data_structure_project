

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "pgm.h"
#include <conio.h>    // Getch function
#include <ctype.h>    // is space function
#include "linkedlist.h"

LinkedList* compress(PGMImage *img) 
{   
    LinkedList *ll = malloc(sizeof(LinkedList));
    init_linked_list(ll);

    unsigned char *array = malloc(img->width * img->height * sizeof(unsigned char));
    int index = 0;


    for(int i = img->height - 1; i  >= 0; i--) {
        for(int j = 0; j < img->width; j++) {
            array[index++] = img->img_data[i][j];
        }
    }

    long k = 0;
    long index2 = 1;
    while (k < (img->width * img->height)) {
        unsigned char current = array[k];
        long counter = 1;
        while (array[index2] == current) {
            counter++;
            index2++;
        }
        Node *new_node = malloc(sizeof(Node));
        new_node->run_length = counter;
        new_node->data       = current;
        append_node(new_node, ll);

        // create node (counter, current)
        k += counter;
        index2 = k + 1;
        //printf("%d\n",index2);
    }


    ll->head->run_length = img->width;    // WİDTH // HEAD'İ VERİ SAKLAMAK İÇİN KULLANIYORUZ
    ll->head->data       = img->height;     // HEİGHT

    free(array);
    return ll;
}

