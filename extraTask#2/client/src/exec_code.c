#include "exec_code.h"
#include <stdio.h>
size_t load_from_file(char* f_name,void* buffer){
   FILE *fd = fopen(f_name,"r");
   size_t b_read;
   if(!fd)
    return NULL;

    b_read = fread(buffer,MAX_BUFFER_LOAD,1,fd);

   fclose(fd);
   return b_read;
}
