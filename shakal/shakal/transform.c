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
// Нарочито не соответсвует хедеру
struct image* apply_pixel_transform(image *img, const transform t[3][4]){
        image* new_img = malloc(sizeof (struct image) );
        new_img->data  = malloc(img->height*img->width*sizeof(struct pixel));
        new_img->height = img->height;
        new_img->width  = img->width ;
        pixel current_p;
        pixel new_p;

        #ifdef USE_SSE // This brhanch of code is included if we want to use simd-instruction of x86
        float xmm_color[4];
                __int128_t *p = (__int128_t*)&t[0][0];
		//// load the filter-matrix into
		asm("movups %0, %%xmm3\n" : :"m"(*p) );    //xmm3 - t[0][0], t[0][1], t[0][2], ...
		p++; // p = &t[1][0];                      // xmm3 - .., t[0][2], t[0][1], t[0][0]
		asm("movups %0, %%xmm4\n" : :"m"(*p) ); //xmm4 - t[1][0], t[1][1], t[1][2], ...
		p++; // p = &t[2][0];
		asm("movups %0, %%xmm5\n" : :"m"(*p) ); //xmm5 - t[2][0], t[2][1], t[2][2], ...
        #endif
        for(size_t j = 0; j < img->height; j++) // The width under the height - much better to cache-hit
            for(size_t i = 0; i < img->width; i++){
                current_p = img->data[img->width*j + i];
                #ifdef USE_SSE // see SIMD x86
				// epilog, preparing the xmm registers. xmm <- pixel
				xmm_color[0] = (float)current_p.b; // we can't just move current_p into xmm
				xmm_color[1] = (float)current_p.g; // because it keeps int8_t values
				xmm_color[2] = (float)current_p.r;

				asm("movups %0,      %%xmm0\n" : : "m"(*xmm_color)); // now the current_p
				asm("movaps %xmm0,   %xmm1\n");                    // in xmm0, xmm1 and xmm2
				asm("movaps %xmm0,   %xmm2\n");
                // the calculations
				asm(
				"mulps  %xmm3, %xmm0\n" // xmm0 *= xmm3; de facto, calculate b*t00, b*t01, b*t20
				"mulps  %xmm4, %xmm1\n" // xmm1 *= xmm4;
				"mulps  %xmm5, %xmm2\n" // xmm5 *= xmm2;

				"addps  %xmm1, %xmm0\n"
				"addps  %xmm2, %xmm0\n"

				); // Not xm00 contains new b-g-r pixel color. Every color is float
                // epilog, new pixel <- registers

				asm("movaps %%xmm0, %0" :"=m"(*xmm_color): );
				new_p.b = SAT_ARIFM(xmm_color[2]);
				new_p.g = SAT_ARIFM(xmm_color[1]);
				new_p.r = SAT_ARIFM(xmm_color[0]);

				#else // without USE_SSE
                // applying matrix multiplictaion
                new_p.r = SAT_ARIFM(current_p.b*t[0][0] + current_p.g*t[0][1] + current_p.r*t[0][2]);
                new_p.g = SAT_ARIFM(current_p.b*t[1][0] + current_p.g*t[1][1] + current_p.r*t[1][2]);
                new_p.b = SAT_ARIFM(current_p.b*t[2][0] + current_p.g*t[2][1] + current_p.r*t[2][2]);
                #endif // USE_SSE
                new_img->data[new_img->width*j + i] = new_p;
            }
        return new_img;
}

struct image* sepia_filter(image* img){
#ifdef USE_SSE
	// Поскольку мы знаем заранее, нужно ли использовать SSE, можем
	// подготовить удобное для последующих SIMD-команд представление данных

//	static const transform sepia[3][4] =  {
//		{ .272f, .349f, .393f, 0.f },
//		{ .543f, .686f, .769f, 0.f },
//		{ .131f, .168f, .189f, 0.f }
//	};
	static const transform sepia[3][4] =  {
		{ .393f, .769f, .189f, 0.f },
		{ .349f, .686f, .168f, 0.f },
		{ .272f, .543f, .131f, 0.f }
	};
//	static const transform sepia[3][4] =  {
//		{ .0f, .0f, .0f, .0f },
//		{ .0f, .0f, .0f, .0f },
//		{ .0f, .0f, .0f, .0f }
//	};
#else   // No using sse
		static const transform sepia[3][4] =  {
		 { .393f, .769f, .189f },
		 { .349f, .686f, .168f },
		 { .272f, .543f, .131f }
		};
#endif
		return apply_pixel_transform(img,sepia);
}

//struct image* apply_pixel_transform_SIMD(image *img, transform t[3][3]){
//	image* new_img = malloc(sizeof (struct image) );
//	new_img->data  = malloc(img->height*img->width*sizeof(struct pixel));
//	new_img->height = img->height;
//	new_img->width  = img->width ;
//	pixel current_p;
//	pixel new_p;

//}

