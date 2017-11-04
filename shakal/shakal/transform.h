#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <stdlib.h>

#include "image.h"

struct image* apply_transform(struct image * img, int **t);
#endif // TRANSFORM_H

