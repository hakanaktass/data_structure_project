#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pgm.h"
#include "linkedlist.h"
#include "rle.h"


int 
main() 
{
    bool b_save_rle = true;         // SET THIS TRUE IF YOU WANT TO SAVE RLE FORMAT
    bool b_save_image = false;      // SET THIS IF YOU WANT TO SAVE NORMAL FORMAT
    LinkedList *list;

    PGMImage image;
    getPGMfile("color_pgm.pgm", &image);
        

    // OKUNAN PGM IMAGINI COMPRESS EDIP RLE ELDE ETME
    // BU AŞAMADA LİNKED LİST KULLANILMAKTA
    puts("compressing...");
    list = compress(&image);
    puts("compressing finished.");


    // OKUNAN P5 / P2 İMAGE'INI PGM OLARAK KAYDETME
    if (b_save_image)
        save(&image);
    else if (b_save_rle)
        save_rle(list);


    // RLE dosyası acip P2'ye cevirme
    // bu aşamaya 6. part da dahildir
    // Histogram verisi stdouta basili
    // Yeni yazılan dosyaya degerleri degistirme işlemi yapildiktan sonra yazılır.
    
    bool read_rle = true;  // rle dosyasi okumak için
    if (read_rle) {    
        xyz change_coordinate;
        change_coordinate.x = 0;
        change_coordinate.y = 0;
        change_coordinate.new_value = 3;
        open_rle("test_decoded.pgm", change_coordinate);
    }

    // destroy heap objects
    destroy_linked_list(list);
    free(list);
    // clearing data arrays inside image object
    for (int i = 0; i < image.width; ++i) {
        free (image.img_data[i]);
    }
    free (image.img_data);

    printf("Press Any Key To Exit!\n");
    getch();  
return 0;
}
