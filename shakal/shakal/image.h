#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

typedef struct pixel { uint8_t b,g,r; }pixel;

typedef struct image {
	uint64_t width, height;
	struct pixel* data;
}image;


#endif // IMAGE

