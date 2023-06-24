// #include <stdio.h>

// int main(int argc, char const *argv[])
// {
//     unsigned int px = 0xAABBCC, byteAux = 0;
//     int R, G, B, R1, G1, B1;
//     R = (px >> 16) & 0xFF; // 1010 1010
//     byteAux = (byteAux << 1) | (R & 0x1);
//     G = (px >> 8) & 0xFF; // 1011 1011
//     byteAux = (byteAux << 1) | (G & 0x1);
//     B = (px) & 0xFF; // 1100 1100
//     byteAux = (byteAux << 1) | (B & 0x1);
//     printf("%x, %x, %x, %x\n", R, G, B, byteAux);

//     // R1 = R & 0xFE;
//     // printf("%x\n", R1);
//     // G1 = G | 0x01;
//     // printf("%x\n", G1);
//     // B1 = B & 0xFE;
//     // printf("%x\n", B1);
//     // R1 = R & 0xFE;;
//     // printf("%x\n", R1);
//     // G1 = G & 0xFE;
//     // printf("%x\n", G1);
//     // B1 = B & 0xFE;
//     // printf("%x\n", B1);
//     // R1 = R & 0xFE;
//     // printf("%x\n", R1);
//     // G1 = G | 0x01;
//     // printf("%x\n", G1);



//     // int v[24];
//     // unsigned int pixel = 0;
//     // int i;

//     // int b = 1;
//     // for (i = 0; i < 24; i++)
//     // {
//     //     v[i] = b;
//     //     //(b == 1) ? b-- : b++;
//     // }

//     // for (i = 0; i < 24; i++)
//     // {
//     //     // Desloca o valor existente para a esquerda e adiciona o novo bit
//     //     pixel = (pixel << 1) | v[i];
//     // }

//     // printf("O valor hexadecimal do pixel é: %06X\n", pixel);
//     return 0;
// }
