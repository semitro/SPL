#include "transform.h"

struct image* apply_transform(struct image *img, int **t){

	struct image* new_img = malloc(sizeof(struct image));
	new_img->height = img->height;
	new_img->width  = img->width;
	new_img->data = malloc(img->height*img->width*sizeof(struct pixel));

	for(int j = 0; j < img->height; j++)
		for(int i = 0; i < img->width; i++){
			new_img->data[ img->width*(j*t[0][0] + j*t[0][1] )
							   +  i*t[1][0] + i*t[1][1] ]
					= img->data[           i    +  img->width*j];
		}

//    for(int i = 0; i < img->height; i++){
//        for(int j = 0; j < img->width; j++){
//            new_img->data[ j*t[0][0] + j*t[0][1] +  new_img->width*(i*t[1][0] + i*t[1][1]) ]
//                    = img->data [           i    +  img->width*j];
//            //			new_img->data[ j*t[0][0] + j*t[0][1] ][ i*t[1][0] + i*t[1][1] ]
//            //					= img->data [           i           ][           j           ];
//        }
//    }
    return new_img;
}
