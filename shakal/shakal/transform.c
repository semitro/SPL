#include "transform.h"

struct image* apply_transform(struct image *img, transform **t, int originX, int originY){

    struct image* new_img = malloc(sizeof(struct image));

	new_img->height = img->height;
	new_img->width  = img->width;
    new_img->data = malloc(img->height*img->width*sizeof(struct pixel));

		printf("X width: %f\n", img->width*t[0][0]+1*t[0][1]);
		printf("Y width: %f\n", img->width*t[1][0]+1*t[1][1]);

		printf("X height: %f\n", 1*t[0][0]+img->height*t[0][1]);
		printf("Y height: %f\n", 1*t[1][0]+img->height*t[1][1]);


	for(int j = 0; j < img->height; j++)
		for(int i = 0; i < img->width; i++){
            new_img->data
					[(int)( img->width*( j*t[0][0] + i*t[1][0] + originY )
					+  i*t[1][0] + i*t[1][1] + originX)]
                    = img->data
					[           i    +  img->width*j];
        }

	return new_img;
}
