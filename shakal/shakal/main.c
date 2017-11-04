#include <stdio.h>
#include <stdint.h>
#include "image.h"
#include "image_loader.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "image.h"
// load
// init matrix
// apply rotate
// store
#define BMP_SIGNATURE 0x4D42
// malloc on the img->img
enum read_status from_bmp(FILE *in,struct image * img){
	struct stat f_param;
	fstat(fileno(in),&f_param);

	struct bmp_header header;
	fread(&header,sizeof(struct bmp_header),1,in);

	if(header.bfType != BMP_SIGNATURE){
		return READ_INVALID_SIGNATURE;
	}

	if(header.bfileSize != f_param.st_size){
		return READ_INVALID_HEADER;
	}

	img->height = header.biHeight;
	img->width  = header.biWidth ;
        img->data = malloc(header.biSizeImage);
        if(1 != fread(img->data, header.biSizeImage, 1, in) ){
            return READ_INVALID_BITS;
        }
        else
            return READ_OK;
}

int main(int argc, char** argv)
{
	if(argc != 2){
		puts("Usage: filename");
		exit(EXIT_SUCCESS);
	}
	FILE* file = fopen(argv[1],"rb");

	if(!file){
		puts("Error with opening the file");
		exit(EXIT_FAILURE);
	}

        struct image img;
        if( from_bmp(file, &img) == READ_OK){
		puts("The file has been loaded!");
	}

	fclose(file);
	return 0;
}

