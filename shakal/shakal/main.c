#include <stdio.h>
#include <stdint.h>
#include "image.h"
#include "image_loader.h"
#include "transform.h"

// load - OK
// init matrix
// apply rotate
// store

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

	transform** t;
	t    = malloc(sizeof(transform*)*2);
	t[0] = malloc(sizeof(transform)*2);
	t[1] = malloc(sizeof(transform)*2);

	t[0][0] =  0.f;
	t[1][0] =  1.f;
	t[0][1] = -1.f;
	t[1][1] =  0.f;

        if( to_bmp(fopen("out.bmp", "wb"), apply_transform(&img,t,0,0)) == WRITE_OK){
		puts("The file has been stored!");
	}


	fclose(file);
	return 0;
}

