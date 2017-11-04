#ifndef IMAGE_LOADER
#define IMAGE_LOADER

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


enum read_status  {
	READ_OK = 0,
	READ_INVALID_SIGNATURE,
	READ_INVALID_BITS,
	READ_INVALID_HEADER
		/* more codes  */
};
enum read_status from_bmp( FILE* in, struct image*);


#endif // IMAGE_LOADER

