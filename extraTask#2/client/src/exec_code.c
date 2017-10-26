#include "exec_code.h"
#include <stdio.h>
size_t load_from_file(char* f_name,void* buffer){
   FILE *fd = fopen(f_name,"r");
   size_t b_read;
   if(!fd)
    return 0;

    b_read = fread(buffer,1,MAX_BUFFER_LOAD,fd);
   fclose(fd);
   return b_read;
}
