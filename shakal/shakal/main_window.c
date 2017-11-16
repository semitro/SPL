#include "main_window.h"

static Colormap _colormap;
static pthread_t _draw_thread;
static pthread_mutex_t _draw_again;
static image* _img;

static void draw_thread(image *img);
static void redraw();

static u_int32_t _slider_point;

static void draw_slider(){
	XWindowAttributes attr;
	XGetWindowAttributes(dis, win, &attr);
	XSetForeground(dis,gc,WhitePixel(dis,screen));
	XDrawLine(dis ,win, gc, 0, attr.height - BOTTOM_SLIDER_ALIGN, attr.width, attr.height - BOTTOM_SLIDER_ALIGN);
	XDrawArc(dis, win, gc, _slider_point,  attr.height - BOTTOM_SLIDER_ALIGN - SLIDER_POINT_WIDE/2, SLIDER_POINT_WIDE,
			 SLIDER_POINT_WIDE, 0, 360*64 );

	XFlush(dis);
}
static void set_slider_point(u_int32_t x){
	//XDraw
	_slider_point = x;
}

void main_loop(){

    XEvent e;

	draw_slider();
	//redraw();
    for(;;) {
		//

        // Ужасно, один процессор загружается на полную,
		// но иначе XNextEvent блкирует dis, и я не могу рисовать
		while(XPending(dis)){
            XNextEvent(dis, &e);
			switch (e.type) {
			case Expose:
				draw_slider();
				redraw();
				break;
			default:
				break;
			}
		}
    }
}

void start_GUI(){
	XInitThreads();
	dis = XOpenDisplay((char*)0);

	screen = DefaultScreen(dis);
	unsigned long black=BlackPixel(dis,screen);	  /* get color black */
	unsigned long white=WhitePixel(dis, screen);  /* get color white */
	win = XCreateSimpleWindow(dis,DefaultRootWindow(dis), 0, 0, 200, 300, 5, black,black );

	/* here is where some properties of the window can be set.
			   The third and fourth items indicate the name which appears
			   at the top of the window and the name of the minimized window
			   respectively.
			*/
	XSetStandardProperties(dis,win,"My Window","HI!",None,NULL,0,NULL);

	/* this routine determines which types of input are allowed in
	   the input.  see the appropriate section for details...
	*/
	XSelectInput(dis, win, StructureNotifyMask | ExposureMask|ButtonPressMask|KeyPressMask);

	/* create the Graphics Context */
	gc=XCreateGC(dis, win, 0,0);

	/* here is another routine to set the foreground and background
	   colors _currently_ in use in the window.
	*/
	XSetBackground(dis,gc,black);
	XSetForeground(dis,gc,white);

	// max - from zero to max
	_colormap = XDefaultColormap(dis,screen);
	//XStandardColormap color_map = *XAllocStandardColormap();

	XMapWindow(dis, win);
	XFlush(dis);
	// Подготовка потока перерисовки img
	pthread_mutex_init(&_draw_again, NULL);
	pthread_mutex_lock(&_draw_again);
	pthread_create(&_draw_thread, NULL, &draw_thread, _img);
	main_loop();
}

XColor my_pixel_to_x(struct pixel my_color){
        XColor color;
        color.red   = MAX_X_COLOR_NUMBER*my_color.r/MAX_IMG_PIXEL_COLOR_NUMBER;
        color.green = MAX_X_COLOR_NUMBER*my_color.g/MAX_IMG_PIXEL_COLOR_NUMBER;
        color.blue  = MAX_X_COLOR_NUMBER*my_color.b/MAX_IMG_PIXEL_COLOR_NUMBER;
        return color;
}

static void draw_thread(struct image *img){
    XColor color;

    struct pixel my_pixel;
    color.flags = DoBlue | DoRed | DoGreen;


    while(1){
        pthread_mutex_lock(&_draw_again);

        for(u_int i = 0; i < img->height; i++)
            for(u_int j = 0; j < img->width; j++){
                my_pixel = img->data[img->width*i + j];

                color = my_pixel_to_x(my_pixel);

                //XQueryColor(dis, colormap, &color);
                XAllocColor(dis, _colormap, &color);

                XSetForeground(dis, gc, color.pixel);
				XDrawPoint(dis, win, gc, j, img->height - i);

            }

    }

}
static void redraw(){
	// Разрешить циклу потока перерисовки сделать ещё одну итерацию
	pthread_mutex_unlock(&_draw_again);
}

void set_img(struct image *img){
	//draw_thread(img);
	_img = img;
}


