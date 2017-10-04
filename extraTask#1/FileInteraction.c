#include "FileInteraction.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING 100
void apply_for_each_stroke_show_int(int(*function)(char*), char* filename){
    FILE *file = fopen(filename,"r");

    char* str = malloc(MAX_STRING);
    unsigned int str_index = 0;
    char c;
    if (file) {
        while (1){
            c = getc(file);

            if(EOF == c)
                return;

            str[str_index++] = c;

            if('\n' == c){
                str[str_index-1]='\0';
                str_index=0;
                printf("The function, applying to '%s' in %s says: %d\n",str,filename,function(str));

            }

        }
    }
    fclose(file);
    free(str);
}
