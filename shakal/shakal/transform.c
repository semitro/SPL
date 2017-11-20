#include "transform.h"

struct image* apply_transform(struct image *img, transform t[2][2], int32_t originX, int32_t originY){

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

//	originX = fmin(fmin(top_x, right_x),  right_top_x);
	originX = MIN(MIN(top_x, right_x), right_top_x);
	if(originX > 0)
		originX = 0;

	originY = MIN(right_top_y,MIN(top_y,right_y));

	if(originY > 0)
		originY = 0;


	for(size_t j = 0; j < img->height; j++)
		for(size_t i = 0; i < img->width; i++){
			int new_pixel_x = i*t[0][0] + j*t[0][1] - originX;
			int new_pixel_y = i*t[1][0] + j*t[1][1] - originY;
			new_img->data[new_img->width*new_pixel_y + new_pixel_x] = img->data[img->width*j + i];
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

}

struct image* apply_pixel_transform(image *img, transform t[3][3]){
	image* new_img = malloc(sizeof (struct image) );
	new_img->data  = malloc(img->height*img->width*sizeof(struct pixel));
	new_img->height = img->height;
	new_img->width  = img->width ;
	pixel current_p;
	pixel new_p;

	for(size_t j = 0; j < img->height; j++) // Ширина под высотой увеличивает частоту попадаия в кэш
		for(size_t i = 0; i < img->width; i++){
			current_p = img->data[img->width*j + i];
//			 applying matrix multiplictaion
			new_p.r = SAT_ARIFM(current_p.b*t[0][0] + current_p.g*t[0][1] + current_p.r*t[0][2]);
			new_p.g = SAT_ARIFM(current_p.b*t[1][0] + current_p.g*t[1][1] + current_p.r*t[1][2]);
			new_p.b = SAT_ARIFM(current_p.b*t[2][0] + current_p.g*t[2][1] + current_p.r*t[2][2]);
			new_img->data[new_img->width*j + i] = new_p;
		}
	return new_img;
}


struct image* sepia_filter(image* img){
	static const transform sepia[3][3] =  {
	 { .393f, .769f, .189f },
	 { .349f, .686f, .168f },
	 { .272f, .543f, .131f }
	};
	return apply_pixel_transform(img,sepia);
}
