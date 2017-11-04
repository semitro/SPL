#include "transform.h"

struct image* apply_transform(struct image *img, transform **t, int originX, int originY){

	struct image* new_img = malloc(sizeof(struct image));

	// Применяем трансформацию для крайних правого и верхнего пикелей
	// Чтобы изменить размер получаемого изображения
	int right_x = img->width*t[0][0]+0*t[0][1];
	int right_y = img->width*t[1][0]+0*t[1][1];

	int top_x =  0*t[0][0]+img->height*t[0][1];
	int top_y =  0*t[1][0]+img->height*t[1][1];

	new_img->width   = abs(right_x) + abs(top_x);
	new_img->height  = abs(right_y) + abs(top_y);

	new_img->data = malloc(new_img->height*new_img->width*sizeof(struct pixel));

	printf("Width : %d\n", abs(right_x) + abs(top_x) );
	printf("Height: %d\n", abs(right_y) + abs(top_y) );


	originX = MIN(top_x,right_x);
	originY = MIN(top_y, right_y);
	printf("%d\n", originX);
	printf("%d\n", originY);

	for(int j = 0; j < img->height; j++)
		for(int i = 0; i < img->width; i++){
			new_img->data
					[(int)( img->width*(  i*t[1][0] + j*t[1][1]- originY )
					+  i*t[0][0] + j*t[0][1]- originX)]
					= img->data
					[           i    +  img->width*j];
		}

	return new_img;
}
