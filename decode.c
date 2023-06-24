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
    char name[100] = "";
    int fsize, sizeIn = In->nc*In->nr, n=2, j=0;
    unsigned char byte = 0;
    unsigned int pixel, byteAux = 0;

    for (int i = 0; i < sizeIn; i++)
    {
        pixel = In->px[i];
        //byteAux = (pixel >> (n*8)) & 0xFF;
        if (n>0)
        {
            byteAux = (pixel >> (n*8)) & 0xFF;
        }else
        {
            byteAux = (pixel) & 0xFF;
        }
        int lsb = byteAux & 0x1;
        n <= 0 ? n=2 : n--;
        printf("[%d] => SizeIn: %d\t Pixel: %x\t RGB: %x\t lsb: %d\t n: %d\n", i, sizeIn, pixel, byteAux, lsb, n);
        byte = (byte << 1) | lsb;
        if (j>=7)
        {
            char temp[2] = {(char)byte, '\0'};
            strcat(name, temp);
            printf("\n\t[j=%d] => IndexName: %s | char: %c\t byte: %b\t hexa: %x\n", j, name, byte, byte, byte);
            if (byte == 0)
            {
                i = sizeIn+1;
            }  
            byte = 0;
            j=0;
        } else
        {
            j++;
        }   
    }
        
    printf("File name: %s\n", name);
    
    // decode file size
    byteAux = 0;
    for (int i = sizePos; i <= sizePos + 32; i++)
    {
        pixel = In->px[i];
        printf("\nPixel: %x", pixel);

        int R, G, B;
        R = (pixel >> 16) & 0xFF;
        G = (pixel >> 8) & 0xFF;
        B = (pixel) & 0xFF;

        if (j==1)
        {
            //R = R & 0xFE;
            byteAux = (byteAux << 1) | (R & 0x1);
        } else if (j==2)
        {
            //G = G | 0x01;
            byteAux = (byteAux << 1) | (G & 0x1);
        } else if (j==3)
        {
            //B = B & 0xFE;
            byteAux = (byteAux << 1) | (B & 0x1);
        } else if (j==4)
        {
            //R = R & 0xFE;
            byteAux = (byteAux << 1) | (R & 0x1);
        } else if (j==5)
        {
            //G = G & 0xFE;
            byteAux = (byteAux << 1) | (G & 0x1);
        } else if (j==6)
        {
            //B = B & 0xFE;
            byteAux = (byteAux << 1) | (B & 0x1);
        } else if (j==7)
        {
            //R = R & 0xFE;
            byteAux = (byteAux << 1) | (R & 0x1);
        }else if (j==8)
        {
            //G = G | 0x01;
            byteAux = (byteAux << 1) | (G & 0x1);
        }

        j++;  

        if (j>8)
        {
            printf("\nBin [%d]: %x\n", j-1, byteAux);            
            fsize = (fsize << 8) | byteAux;
            byteAux = 0;
            j=1;
        }
    }
    
    
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
