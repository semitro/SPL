#include <stdio.h>
#include <stdint.h>
#include "image.h"
#include "image_loader.h"
#include "transform.h"
#include "main_window.h"

// load - OK
// init matrix
// apply rotate
// store

int main(int argc, char** argv)
{

	window_go();
//	if(argc != 2){
//		puts("Usage: filename");
//		exit(EXIT_SUCCESS);
//	}
//	FILE* file = fopen(argv[1],"rb");

//	if(!file){
//		puts("Error with opening the file");
//		exit(EXIT_FAILURE);
//	}

//	struct image img;
//	enum read_status read_stat = from_bmp(file, &img);
//	if(read_stat == READ_OK )
//		puts("The file has been loaded!");
//	else{
//		switch(read_stat){
//		case READ_INVALID_HEADER:{
//			puts("The file has invalid header");
//			break;
//		}
//		case READ_INVALID_SIGNATURE:{
//			puts("The file doesn't have bmp magic-number");
//			puts("Are you sure that this is the bmp-file?");
//			break;
//		}
//		case READ_INVALID_BITS:
//		default:
//			puts("Something is wrong with the file");

//		}
//		exit(0);
//	}


//	transform** t;
//	t    = malloc(sizeof(transform*)*2);
//	t[0] = malloc(sizeof(transform)*2);
//	t[1] = malloc(sizeof(transform)*2);

//		t[0][0] =  0.f;
//		t[1][0] =  1.f;
//		t[0][1] =  -1.f;
//		t[1][1] =  0.f;
//	//		t[0][0] =  1.f;
//	//		t[1][0] =  0.f;
//	//		t[0][1] =  0.f;
//	//		t[1][1] =  1.f;

//				t[0][0] =  0.f;
//				t[1][0] =  2.f;
//				t[0][1] =  -1.f;
//				t[1][1] =  0.f;
//		t[0][0] =  0.707106781;
//		t[1][0] =  0.707106781;
//		t[0][1] = -0.707106781;
//		t[1][1] =  0.707106781;
//        void *p = apply_transform(&img,t,0,0);
//        if( to_bmp(fopen("out.bmp", "wb"), p) == WRITE_OK)
//            puts("The file has been stored!");
//        else
//            puts ("Error with storing the file");

//        fclose(file);
        return 0;
}

