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
    char name[100];
    int fsize=0, id=0;
    unsigned char byte;
    int sizePos = 0, j=1;
    unsigned int pixel = 0, byteAux = 0;
    
    for (int i = 0; i < In->nc*In->nr; i++)
    {
        // Transformando para hexadecimal
        pixel = In->px[i];
        printf("\nPixel: %x", pixel);

        // Separando os R, G, B
        int R, G, B;
        R = (pixel >> 16) & 0xFF;
        G = (pixel >> 8) & 0xFF;
        B = (pixel) & 0xFF;
        printf("\nHex R: %x, G: %x, B: %x", R, G, B);

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
            if (byteAux == 00000000)
            {
                sizePos = i + 1;
                i = (In->nc*In->nr) + 1;
            }
            
            name[id] = byteAux;
            byteAux = 0;
            id++;
            j=1;
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
