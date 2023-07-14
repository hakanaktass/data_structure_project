#include <stdio.h>    // IO operasyonları
#include <string.h>   // strcpy
#include <stdbool.h>  // bool, true, false
#include <stdlib.h>
#include "pgm.h"
#include <conio.h>    // Getch function
#include <ctype.h>    // is space function


/**
 * REFERENCE SITES: 
 * 1) http://netpbm.sourceforge.net/doc/pgm.html
 * 2) https://stackoverflow.com/a/58740911/12688015
 * 3) https://www.geeksforgeeks.org/how-to-read-a-pgmb-format-image-in-c/
 * 
 * Bu siteleri kullanarak PGM dosyaları ile nasıl çalışmam gerektiğini öğrendim.
*/

#include "pgm.h"


/*PGM dosyası okuma func'u*/
void getPGMfile (char filename[], PGMImage *img) 
{
    FILE *file;
    char type[3], ch;
    int row, col;
    int ch_int;
 
    file = fopen(filename, "r");
    
    if (file == NULL)
        puts("CAN'T OPEN FILE");

    /*determine pgm image type (only type three can be used)*/
    type[0] = getc(file);
    if(type[0] != 'P')
    {
        printf("ERROR1, Not valid PGM file type\n");
        exit(1);
    }
    type[1] = getc(file);
    type[2] = '\0';

    strcpy(img->type, type);

   // numbers stands for 5 and 2 in ASCII, checking for P5, P2
    if (type[1] == '2' || type[1] == '5')
        printf("Valid PGM file, %s\nType: P%d\n", filename, type[1] - 48);  
    else {
        printf("ERROR2, Not a valid PGM file type\n");
        exit(1);
    }
   
   // skipping comments and empty spaces to reach the data
    for (char skip; skip != '\n'; skip = getc(file));
    for (char skip; skip == '#'; skip = getc(file)) {
        for (char tmp; tmp != '\n'; tmp = getc(file));
    }

 
    fscanf(file, "%d", &(img->width));
    fscanf(file, "%d", &(img->height));
    fscanf(file, "%d", &(img->maxVal));
    
    printf("\nwidth  = %d", img->width);
    printf("\nheight = %d", img->height);
    printf("\nmaxVal = %d\n", img->maxVal);

    img->img_data = malloc(img->height * sizeof(unsigned char*));
    for (int i = 0; i < img->width; ++i)
        img->img_data[i] = malloc(img->height * sizeof(unsigned char));

    if(type[1] == '2') /* ASCII */ {
        /*boş satırları atlıyoruz*/
        for (char skip; skip != '\n'; skip = getc(file)); 
        /*boş satırları atlıyoruz*/

        for (row=img->height-1; row >=0; row--)
            for (col=0; col< img->width; col++) {
                fscanf(file,"%d", &ch_int);
                img->img_data[row][col] = (unsigned char) ch_int;
            }
    }
    
    /* BINARY */
    else if(type[1] == '5') {
        unsigned char buffer[1];
        /*boş satırları atlıyoruz*/
        for (char skip; skip != '\n'; skip = getc(file)); 
        /*boş satırları atlıyoruz*/

        for (row=img->height-1; row >=0; row--)
            for (col=0; col< img->width; col++)
            {
                fread(buffer, sizeof(buffer), 1, file);
                ch = buffer[0];
                img->img_data[row][col] = (unsigned char) ch;
            }
        
    }
  

  
    fclose(file);
    printf("\nDone reading file.\n");
}
  
  
void save(PGMImage *img)
{
    int data;
    FILE *iop;
    
    iop = fopen("test_decoded.pgm", "w");

    if (img->type[0] == 'P' && img->type[1] == '2') {
        fprintf(iop, "P2\n");
        fprintf(iop, "%d %d\n", img->width, img->height);
        fprintf(iop, "255\n");
        
        for(int i = img->height - 1; i  >= 0; i--) {
            for(int j = 0; j < img->width; j++) {
                data = img->img_data[i][j];
                fprintf(iop, "%-3d ", (int) data);
            }
            fprintf(iop, "\n");
        }
    }

    else if (img->type[0] == 'P' && img->type[1] == '5') {
        fprintf(iop, "P5\n");
        fprintf(iop, "%d %d\n", img->width, img->height);
        fprintf(iop, "255\n");
        
        for(int i = img->height - 1; i  >= 0; i--)
            for(int j = 0; j < img->width; j++) {
                data = img->img_data[i][j];
                putc(data, iop);
            }
    }


/* Fonksiyonun sonuna kadar hatasız geldiysek file pointer'ını yok edip bir üst aşamaya dönüyoruz.*/
fprintf(iop, "\n");
fclose(iop);
return;
}



void save_rle(LinkedList *ll)
{
    FILE *iop;
    
    int width  = ll->head->run_length;
    int height = ll->head->data;
    

    iop = fopen("test_decoded.pgm", "w");

    Node *start = ll->head->next;

    fprintf(iop, "%d %d ", height, width);
    while (start) {
        if (start != ll->tail)
            fprintf(iop, "%d %d  ", start->run_length, start->data);

        start = start->next;
    }


/* Fonksiyonun sonuna kadar hatasız geldiysek file pointer'ını yok edip bir üst aşamaya dönüyoruz.*/
fprintf(iop, "\n");
fclose(iop);
return;
}



void open_rle(const char *rle_filename, xyz change) {
    FILE *read_file, *write_file, *txt;
    int width, height;


    int rle;
    int data;
    int check = 0;

    int prev = -999;

    read_file  = fopen(rle_filename, "r");
    write_file = fopen("rle_new_file.pgm", "w");

    if (read_file == NULL)
        puts("CAN'T OPEN THE RLE FILE");

    fscanf(read_file, "%d", &height);
    fscanf(read_file, "%d", &width);

    int *array = malloc(height * width * sizeof(int));
    int *histogram = calloc(256, sizeof(int));

    for (int i = 0; i < height*width; ++i) {
        int c = fscanf(read_file, "%d", &rle);
        int d = fscanf(read_file, "%d", &data);
        
        

        if (!(c == EOF || d == EOF)){
            check += (rle);
            if (data > 255) {
                puts("PIXEL VALUE ERROR, OVER THAN 255, ERROR! CALCELING THE FILE OPERATIONS!");
                return;
            }

            for (int j = 0; j < rle; j++)
                array[i+j] = data;


            if (data == prev) {
                puts("ERROR, Repeating sequence!!!");
                puts("File operation cancelled");
                exit(1);
            }

            prev = data;        
        }
    }
    // check pixels
    if (! (height*width == check)) {
        puts("INVALID WIDTH / HEIGHT, PIXEL NUBMER ERROR!"); return;
    }


    fprintf(write_file, "P2\n"); 
    fprintf(write_file, "%d %d\n", height, width);    
    fprintf(write_file, "255\n");    

    for(int i = height - 1; i  >= 0; i--) {
        for(int j = 0; j < width; j++) {
            data = array[i*width + j];
            if (change.x == i && change.y == j)
                fprintf(write_file, "%-3d ", change.new_value);
            else
                fprintf(write_file, "%-3d ", data);
        }
        fprintf(write_file, "\n");
    }

    for (int i = 0; i < height * width; ++i)
    {
        data = array[i];
        histogram[data]++;
    }

    txt = fopen("test_encoded.txt", "w");

    printf("\n\nHISTOGRAM INFO\n");
    for (int i = 0; i < 255; ++i) {
        if (histogram[i]) {
            printf("Data: %d, Occurances: %d\n", i, histogram[i]);
            fprintf(txt, "Data: %d, Occurances: %d\n", i, histogram[i]);
        }
    }
    printf("\n\nEND OF HISTOGRAM INFO\n");

    free(array); free(histogram);

    fclose(write_file);


    fclose(read_file);
    printf("Converted RLE file %s to PGM file rle_new.pgm. Type: P2\n", rle_filename);  
}