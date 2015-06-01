#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LG_MAX 200

struct vecteur
{   int x;
    int y;
    int z;
}; 

typedef struct liste_vect liste_vect;
struct liste_vect
{
    struct vecteur noeud;
    struct liste_vect *suivant;
};


extern int* parser_file(const char* name);

#endif
