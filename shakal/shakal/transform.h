#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#include "image.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
// "Насыщенна арифметика" - результаты больше 255 приравниваются к 255
#define SAT_ARIFM(a) (a <= 255 ? a : 255)

// Использовать ли SSE-инструкции?
#define USE_SSE
// #undef USE_SSE
typedef float transform;
// Применение трансформации непосредственно к расположению пикселей
// originX, originY зарезервированны для обозначения точки центра (например, вращения)
// в данной версии - игнорируются
struct image* apply_transform(struct image * img, transform t[2][2], int32_t originX, int32_t originY);
// Декорирует предыдущую функцию
struct image* rotate(struct image *img, float angle);

// Трансформация, применяющася к каждому пикселю, как трёхмерному вектору (b, g, r)
struct image* apply_pixel_transform(image *img ,transform t[3][4]);
// Трансформация с помощью Streamin SIMD extention-комад x86. Некроссплатформенно, но быстро. Надеюсь
//struct image* apply_pixel_transform_SIMD(image *img, transform t[3][3]);

struct image* sepia_filter(image* img);

#endif // TRANSFORM_H

