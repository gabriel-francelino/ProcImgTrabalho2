/*---------------------------------------------------------
 * Image Processing
 *
 * Steganography - decode
 *---------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "imagelib.h"
#define DEBUG(x) x

void decode(image In)
{
    FILE *file;
    char name[100] = "";
    int fsize, sizeIn = In->nc * In->nr, sizeId = 0, contentId = 0, n = 2, j = 0;
    unsigned char byte = 0;
    unsigned int pixel, byteAux = 0;

    for (int i = 0; i < sizeIn; i++)
    {
        pixel = In->px[i];
        byteAux = (pixel >> (n * 8)) & 0xFF;
        int lsb = byteAux & 0x1;
        n <= 0 ? n = 2 : n--;
        // printf("[%d] => SizeIn: %d\t Pixel: %x\t RGB: %x\t lsb: %d\t n: %d\n", i, sizeIn, pixel, byteAux, lsb, n);
        byte = (byte << 1) | lsb;
        if (j >= 7)
        {
            char temp[2] = {(char)byte, '\0'};
            strcat(name, temp);
            // printf("\n\t[j=%d] => IndexName: %s | char: %c\t byte: %b\t hexa: %x\n", j, name, byte, byte, byte);
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
    uint32_t binSize = 0;
    for (int i = sizeId; i < sizeId + 32; i++)
    {
        pixel = In->px[i];

        if (n > 0)
        {
            byteAux = (pixel >> (n * 8)) & 0xFF;
        }
        else
        {
            byteAux = (pixel)&0xFF;
        }
        int lsb = byteAux & 0x1;
        n <= 0 ? n = 2 : n--;
        // printf("[%d] => SizeIn: %d\t Pixel: %x\t RGB: %x\t lsb: %d\t n: %d\n", i, sizeIn, pixel, byteAux, lsb, n);
        binSize = (binSize << 1) | lsb;
        if (j >= 7)
        {
            // printf("\n\t[j=%d] => IndexName: %s | char: %c\t byte: %b\t hexa: %x\n", j, name, byte, byte, byte);
            // byte = 0;
            j = 0;
        }
        else
        {
            j++;
        }
    }

    fsize = binSize;
    byte = 0;
    contentId = sizeId + 32; // Posição dos bytes de conteúdo: (sizeId + 32) + 1
    printf("ContentId: %d\n", contentId);
    printf("File size: %d bytes\n", fsize);

    // decode file
    file = fopen(name, "wb"); //0000 0000 0000 0010 = 2 ==> 4 2 
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
            //printf("ContentId: %d\n", contentId);
            contentId++;
            byteAux = (pixel >> (n * 8)) & 0xFF;
            int lsb = byteAux & 0x1;
            n <= 0 ? n = 2 : n--;
            byte = (byte << 1) | lsb;
        }

        //fprintf(file, "%b", byte);
        fwrite(&byte, sizeof(byte), 1, file);
        //printf("Byte: %c\n", byte);
        byte = 0;
        //contentId+=8;
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
