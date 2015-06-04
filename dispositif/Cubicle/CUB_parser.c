/*#include "CUB_parser.h"

int CUB_parse_file(char *filename, LIST_TYPE)
{
	FOPEN(filename);
	char buff[64];

    // Version
	READ_LINE(buff);
	uint32_t version = strtol(buff, NULL, 10);
	if (version > MAX_SUPPORTED_VERSION)
	return 1;

    // Vectors
	while ((READ_LINE(buff)) != NULL) {
		char *p1 = buff;
		char *p2 = NULL;
		uint32_t x = strtol(p1, &p2, 10);
		uint32_t y = strtol(p2, &p1, 10);
		uint32_t z = strtol(p1, &p2, 10);
		LIST_ADD(x, y, z);
}
FCLOSE;
return 0;
}
*/
    
