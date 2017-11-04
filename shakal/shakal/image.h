#ifndef IMAGE
#define IMAGE

#include <stdint.h>

struct pixel { uint8_t b,g,r; };
struct image {
	uint64_t width, height;
	struct pixel_t* data;
};


#endif // IMAGE

