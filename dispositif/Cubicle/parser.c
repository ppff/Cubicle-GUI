#include "parser.h"

int* parser_file(const char* name ){

char chaine[LG_MAX] ;
char version[12];
int* tab;
int j;
    FILE *fichier = fopen (name, "r");
	int i=0;
  	
    if(fichier!=NULL){
	fgets(version, LG_MAX, fichier);
	printf ("version lue : %s", version);

     tab=malloc(LG_MAX*sizeof(int));
         while(fgets(chaine, LG_MAX, fichier) != NULL){
            for(j=0;j<3;j++){
			
                tab[i]=(int)chaine[j];
                i++;
            }
         	printf ("chaine lue : %s", chaine);
        }

    }
 fclose (fichier);
return tab;
}
/*
main(){
	int* tab;
	tab=parser_file("parser.txt");

}
 
*/