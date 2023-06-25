/*+=============================================================
2 | UNIFAL = Universidade Federal de Alfenas.
3 | BACHARELADO EM CIENCIA DA COMPUTACAO.
4 | Trabalho . . : Esteganografia
5 | Disciplina . : Processamento de Imagens
6 | Professor. . : Luiz Eduardo da Silva
7 | Aluno . . . .: Gabriel Francelino Nascimento
8 | Data . . . . : 24/06/2023
9 +=============================================================*/

#define CREATOR "# CREATOR: Image Processing using C-Ansi - ByDu\n"

typedef struct
{
    int *px;        // pixels vector
    int nr, nc, ml; // nr = n.rows, nc = n.columns, ml = max level
    int tp;         // tp = type
} * image;

#define ERROR(x, y) \
    if (x)          \
    y

enum
{
    BW = 1,
    GRAY,
    COLOR
};

#if defined(_WIN32) || defined(__WIN64__) || defined(__CYGWIN__)
#define VIEW "../utils/i_view32"
#elif defined(__linux__)
#define VIEW "eog"
#endif

void errormsg(char *, ...);
image img_create(int, int, int, int);
image img_clone(image);
int img_free(image);
void img_name(char *, char *, char *, int, int);
image img_get(char *, int);
void img_put(image, char *, int);
