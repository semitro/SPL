#include "transform.h"

struct image* apply_transform(struct image *img, transform t[2][2], int originX, int originY){

	struct image* new_img = malloc(sizeof(struct image));

	// Применяем трансформацию для крайних правого и верхнего пикелей
	// Чтобы изменить размер получаемого изображения
	// (1, 0)
	int32_t right_x = img->width*t[0][0]+0*t[0][1];
	int32_t right_y = img->width*t[1][0]+0*t[1][1];
	// Все эти штуки - матричное умножение
	// (0, 1)
	int32_t top_x =  0*t[0][0]+img->height*t[0][1];
	int32_t top_y =  0*t[1][0]+img->height*t[1][1];

	// (1, 1)
	int32_t right_top_x = img->width*t[0][0] + img->height*t[0][1];
	int32_t right_top_y = img->width*t[1][0] + img->height*t[1][1];

	// Максимальная из разностей диагональных точек по x
	new_img->width   = MAX(abs(right_top_x),   abs(right_x - top_x));
	new_img->height  = MAX(abs(right_y-top_y), abs(right_top_y    ));

	new_img->data = malloc(new_img->height*new_img->width*sizeof(struct pixel));

//	printf("Width : %d\n", img->width );
//	printf("Height: %d\n", img->height );
//	printf("Width : %d\n", new_img->width );
//	printf("Height: %d\n", new_img->height );

	originX = MIN(right_top_x,MIN(top_x, right_x));
	if(originX > 0)
		originX = 0;

	originY = MIN(right_top_y,MIN(top_y, right_y));

	if(originY > 0)
		originY = 0;
//	printf("%d\n", originX);
//	printf("%d\n", originY);

	for(size_t j = 0; j < img->height; j++){
		for(size_t i = 0; i < img->width; i++){
			int new_pixel_x = i*t[0][0] + j*t[0][1] - originX;
			int new_pixel_y = i*t[1][0] + j*t[1][1] - originY;
			new_img->data[new_img->width*new_pixel_y + new_pixel_x] = img->data[img->width*j + i];
		}
	}

	return new_img;
}

inline double to_degrees(double radians) {
	return radians * (180.0 / M_PI);
}

struct image* rotate(struct image *img, float angle){

        transform t[2][2];
	t[0][0] =  cos(angle);
	t[1][0] =  sin(angle);
	t[0][1] = -sin(angle);
	t[1][1] =  cos(angle);

        return apply_transform(img, *t, 0, 0);
////		transform** t;
//		t    = malloc(sizeof(transform*)*2);
//		t[0] = malloc(sizeof(transform)*2);
//		t[1] = malloc(sizeof(transform)*2);

//
	//	//		t[0][0] =  1.f;
	//	//		t[1][0] =  0.f;
	//	//		t[0][1] =  0.f;
	//	//		t[1][1] =  1.f;

	//				t[0][0] =  0.f;
	//				t[1][0] =  2.f;
	//				t[0][1] =  -1.f;
	//				t[1][1] =  0.f;
			t[0][0] =  0.707106781;
			t[1][0] =  0.707106781;
			t[0][1] = -0.707106781;
			t[1][1] =  0.707106781;
			return apply_transform(img,t,0,0);
}
