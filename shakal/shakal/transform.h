#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <stdlib.h>
#include <math.h>

#include "image.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef float transform;
struct image* apply_transform(struct image * img, transform t[2][2], int originX, int originY);

struct image* rotate(struct image *img, float angle);

#endif // TRANSFORM_H

