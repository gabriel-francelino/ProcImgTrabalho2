/*+=============================================================
2 | UNIFAL = Universidade Federal de Alfenas.
3 | BACHARELADO EM CIENCIA DA COMPUTACAO.
4 | Trabalho . . : Esteganografia
5 | Disciplina . : Processamento de Imagens
6 | Professor. . : Luiz Eduardo da Silva
7 | Aluno . . . .: Gabriel Francelino Nascimento
8 | Data . . . . : 24/06/2023
9 +=============================================================*/

/*---------------------------------------------------------
 * Image Processing
 *
 * Steganography - decode
 *---------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "imagelib.h"
#define DEBUG(x) x

void decode(image In)
{
    FILE *file;
    char name[100] = ""; //new file name
    int fsize;  // new file's content size
    int sizeIn = In->nc * In->nr; // input file size
    int sizeId = 0, contentId = 0; // index of size and content 
    int n = 2, j = 0; // iterator
    unsigned char byte = 0; // content
    unsigned int pixel, byteAux = 0, binSize = 0;

    // decode file name
    for (int i = 0; i < sizeIn; i++)
    {
        pixel = In->px[i];
        byteAux = (pixel >> (n * 8)) & 0xFF; // isolated bytes of R, G or B colors
        int lsb = byteAux & 0x1; // Least Significant Bits
        n <= 0 ? n = 2 : n--; // iterators used to isolate R, G and B
        byte = (byte << 1) | lsb; // include the rightmost bit of the byte
        if (j >= 7)
        {
            char temp[2] = {(char)byte, '\0'}; // convert from unsigned char to string
            strcat(name, temp);  // append the characters of the name
            if (byte == 0)
            {
                sizeId = i + 1;
                i = sizeIn + 1;
            }
            byte = 0;
            j = 0;
        }
        else
        {
            j++;
        }
    }

    printf("File name: %s\n", name);

    // decode file size
    for (int i = sizeId; i < sizeId + 32; i++)
    {
        pixel = In->px[i];
        byteAux = (pixel >> (n * 8)) & 0xFF;
        int lsb = byteAux & 0x1;
        n <= 0 ? n = 2 : n--;
        binSize = (binSize << 1) | lsb; // add the 32 bits in the variable
        j >= 7 ? j=0 : j++; // iterator used to define the number of bits 
    }

    fsize = binSize;
    byte = 0;
    contentId = sizeId + 32; // index of first content pixel
    printf("File size: %d bytes\n", fsize);

    // decode file
    file = fopen(name, "wb"); 
    if (!file)
    {
        printf("Cannot create file %s\n", name);
        exit(10);
    }
    while (fsize)
    {
        // decode the bytes of the file
        for (int i = 0; i < 8; i++)
        {
            pixel = In->px[contentId];
            contentId++;
            byteAux = (pixel >> (n * 8)) & 0xFF;
            int lsb = byteAux & 0x1;
            n <= 0 ? n = 2 : n--;
            byte = (byte << 1) | lsb;
        }

        fwrite(&byte, sizeof(byte), 1, file);
        byte = 0;
        fsize--;
    }
    fclose(file);
}

void msg(char *s)
{
    printf("\nSteganography - decode");
    printf("\n-------------------------------");
    printf("\nUSE.:  %s  <IMG.PPM>", s);
    printf("\nWhere:\n");
    printf("    <IMG.PPM>  Image file in PPM ASCII format\n\n");
    exit(20);
}

/*-----------------------------------------
  Main program
------------------------------------------*/
int main(int argc, char *argv[])
{
    char name[100];
    image In;
    char *p;
    if (argc < 2)
        msg(argv[0]);
    strcpy(name, argv[1]);
    p = strstr(name, ".ppm");
    if (p)
        *p = 0;
    strcat(name, ".ppm");
    In = img_get(name, COLOR);
    decode(In);
    img_free(In);
    return 0;
}
