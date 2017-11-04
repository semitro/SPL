#include <stdio.h>
// load
// init matrix
// apply rotate
// store

struct pixel { uint8_t b,g,r; };

struct __attribute__((packed))
	bmp_header {
		uint16_t bfType;
		uint32_t  bfileSize;
		uint32_t bfReserved;
		uint32_t bOffBits;
		uint32_t biSize;
		uint32_t biWidth;
		uint32_t  biHeight;
		uint16_t  biPlanes;
		uint16_t biBitCount;
		uint32_t biCompression;
		uint32_t biSizeImage;
		uint32_t biXPelsPerMeter;
		uint32_t biYPelsPerMeter;
		uint32_t biClrUsed;
		uint32_t  biClrImportant;
};

int main(void)
{
	printf("Hello World!\n");
	return 0;
}

