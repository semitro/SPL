#include "image_loader.h"

struct bmp_header header_prototype;

// malloc on the img->img
enum read_status from_bmp(FILE *in, struct image* img){
	struct stat f_param;
	fstat(fileno(in),&f_param);

	struct bmp_header header;
	fread(&header,sizeof(struct bmp_header),1,in);

	if(header.bfType != BMP_SIGNATURE){
		return READ_INVALID_SIGNATURE;
	}

	if(header.bfileSize != f_param.st_size){
		return READ_INVALID_HEADER;
	}

	header_prototype = header;

	img->height = header.biHeight;
	img->width  = header.biWidth ;
	img->data = malloc(header.biSizeImage);
	if(1 != fread(img->data, header.biSizeImage, 1, in) ){
		return READ_INVALID_BITS;
	}
	else
		return READ_OK;
}
struct bmp_header generate_header(const struct image * img){
	header_prototype.biSizeImage = img->height * img->width * sizeof(struct pixel);
	header_prototype.bfileSize   = sizeof(header_prototype)
			+ header_prototype.biSizeImage;
	return header_prototype;
	//	struct bmp_header header;
	//	header.biHeight    = img->height;
	//	header.biWidth     = img->width;
	//	header.bfType      = BMP_SIGNATURE;
	//	header.biSizeImage = img->height * img->width * sizeof(struct pixel);
	//	header.bfileSize   = sizeof(header) + header.biSizeImage;
	//	header.bOffBits    = sizeof header;
	//	return header;
}

enum write_status to_bmp(FILE *out, const struct image *img){
	struct bmp_header header = generate_header(img);

	header.biWidth  = img->width ;
	header.biHeight = img->height;

	if( 1 != fwrite(&header,sizeof(header),1,out)){
		return WRITE_ERROR;
	}

	if( 1 != fwrite(img->data, header.biSizeImage, 1, out)){
		return WRITE_ERROR;
	}
	return WRITE_OK;
}
