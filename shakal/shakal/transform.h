#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <stdlib.h>

#include "image.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef float transform;
struct image* apply_transform(struct image * img, transform **t, int originX, int originY);
#endif // TRANSFORM_H

