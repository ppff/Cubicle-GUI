#ifndef CUB_PARSER_H
#define CUB_PARSER_H

#define MAX_SUPPORTED_VERSION 1

#ifdef CUBICLE_SOFTWARE

#define LIST_TYPE ;
#define FOPEN(FILENAME) ;
#define LIST_ADD(X, Y, Z) ;
#define FCLOSE ;
#else

#include <stdlib.h>
#include <stdio.h>
#include "applications/crystal_structure/CUB_LED_list.h"
/*#include "fatfs.h"

#define LIST_TYPE CUB_LED_list_t *l
#define FOPEN(FILENAME) FIL *file = NULL;\
f_open(file, FILENAME, FA_READ)
#define READ_LINE(BUFF) f_gets(BUFF, 64, file)
#define LIST_ADD(X, Y, Z) CUB_LED_t led = {(X), (Y), (Z), NULL};\
CUB_LED_list_add(l, &led)
#define FCLOSE f_close(file)
#endif

int CUB_parse_file(char *filename, LIST_TYPE);
#endif
*/
