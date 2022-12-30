// g++ -Wall -W ex3.cpp -lX11

#include <iostream>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    
    // Подключаемся к первому локальному дисплею, X-серверу данной машины.
    const char *Disp0 = ":0";
    Display *display = XOpenDisplay(Disp0);
    int screen_num = DefaultScreen(display);
    Window root = RootWindow(display, screen_num);

    Window win = XCreateSimpleWindow(display, root, 0, 0, 512, 512, 2,
        WhitePixel(display, screen_num), BlackPixel(display, screen_num));

    XMapWindow(display, win);
    XSelectInput(display, win, ExposureMask | KeyPressMask);

    XGCValues gc_values;
    GC gc = XCreateGC(display, win, 0, &gc_values);

    const char *hello = "Hello! Nice to meet you!";

    // Красный цвет.
    XColor     red_col;
    Colormap   colormap;
    char red_bits[] = "#FF0000";
    colormap = DefaultColormap(display, 0);
    XParseColor(display, colormap, red_bits, &red_col); 
    XAllocColor(display, colormap, &red_col);

    // Цикл обработки событий.
    XEvent event;
    while(1) {
        XNextEvent(display, &event);
        switch(event.type) {
            case Expose: // Событие - Необходимо перерисовать окно.
                // Текст.
                XSetForeground(display, gc, WhitePixel(display, screen_num));
                XDrawString(display, win, gc, 10, 10, hello,strlen(hello));
                
                // Красная линия.
                XSetForeground(display, gc, red_col.pixel);
                XDrawLine(display, win, gc, 10, 70, 180, 30);
                //std::cout << "1" << std::flush;
                break;
            case KeyPress:
                if(event.xkey.keycode == XKeysymToKeycode(display, XK_Escape)) {
                    //exit(0);
                    return 0;
                }
                break;
        }
    }
    
    XCloseDisplay(display);
    return 0;
}
