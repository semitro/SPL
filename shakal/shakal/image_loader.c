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
	img->data = malloc(img->width*img->height*sizeof(struct pixel));

	// for padding, skipping
	char empty[3];
	for(int i = 0; i < header.biHeight;i++){
                if(1 != fread(img->data + img->width*i, img->width*sizeof(struct pixel), 1, in) ){
			return READ_INVALID_BITS;
		}
		// Учитывая выравнивние
		fread(empty,header.biWidth%BMP_PADDING,1,in);
	}

		return READ_OK;
}
struct bmp_header generate_header(const struct image * img){
        header_prototype.biSizeImage = img->height * img->width * sizeof(struct pixel)
                + (img->width%BMP_PADDING)*img->height;

	header_prototype.bfileSize   = sizeof(header_prototype)
			+ header_prototype.biSizeImage;
	header_prototype.biWidth  = img->width;
	header_prototype.biHeight = img->height;
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


	if( 1 != fwrite(&header,sizeof(header),1,out)){
		return WRITE_ERROR;
	}

	for(int i = 0; i < header.biHeight;i++){
		if(1 != fwrite(img->data + i*header.biWidth, header.biWidth*sizeof(struct pixel), 1, out))
			return WRITE_ERROR;

		// Учитывая выравнивние. Записываем какой угодно остаток байт
                fwrite(img->data,header.biWidth%BMP_PADDING,1,out);
	}

	return WRITE_OK;
}
