#include <stdio.h>
#include <stdint.h>
#include "image.h"
#include "image_loader.h"
#include "transform.h"
#include "main_window.h"
#include <time.h>
#include <sys/resource.h>
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
	enum read_status read_stat = from_bmp(file, &img);

	if(read_stat == READ_OK )
		puts("The file has been loaded!");
	else{
		switch(read_stat){
		case READ_INVALID_HEADER:{
			puts("The file has invalid header");
			break;
		}
		case READ_INVALID_SIGNATURE:{
			puts("The file doesn't have bmp magic-number");
			puts("Are you sure that this is the bmp-file?");
			break;
		}
		case READ_INVALID_BITS:
		default:
			puts("Something is wrong with the file");

		}
		exit(0);
	}

/*        struct rusage r;
		   struct timeval start;
		   struct timeval end;
		   getrusage(RUSAGE_SELF, &r );
		   start = r.ru_utime;
		   sepia_filter(&img);

		   getrusage(RUSAGE_SELF, &r );
		   end = r.ru_utime;
		   long res = ((end.tv_sec - start.tv_sec) * 1000000L) +
			   end.tv_usec - start.tv_usec;

	printf( "Time elapsed in microseconds: %ld\n", res );
	printf("%d\n", img.data[2]);
*/
	set_img(&img);
	//rotate(&imt)
        start_GUI();
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
		//void *p = apply_pixel_transform(&img, t);
//		void *p = rotate(&img,M_PI/2.);
//		if( to_bmp(fopen("out.bmp", "wb"), p) == WRITE_OK)
//			puts("The file has been stored!");
//		else
//			puts ("Error with storing the file");

//        fclose(file);
        return 0;
}

