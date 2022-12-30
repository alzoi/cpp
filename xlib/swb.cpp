// g++ -Wall -W swb.cpp -lX11 -lXext
// Доп. библиотеки: lXdamage -lXfixes -lXtst

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/Xdbe.h>

#define MAX_X (3 * M_PI)
#define MAX_Y 2

long double f(long double x) {
    return sin(x);
}


int x_prev_position = -1;
int y_prev_position = -1;

void draw (Display *display, Drawable win, int shift_x, int shift_y, int resized) {
    static Window rootReturn;
    static int xReturn;
    static int yReturn;
    static unsigned int widthReturn;
    static unsigned int heightReturn;
    static unsigned int borderWidthReturn;
    static unsigned int depthReturn;
    GC gc;
    XGCValues gcv;

    int blackpixel = BlackPixel(display, DefaultScreen(display));
    int whitepixel = WhitePixel(display, DefaultScreen(display));

    static long double total_shift_x = 0;
    static long double total_shift_y = 0;

    gcv.background = whitepixel;
    gcv.foreground = blackpixel;
    gc = XCreateGC(display, DefaultRootWindow(display), GCForeground | GCBackground, &gcv);

    if (resized) {
        XGetGeometry(display, win, &rootReturn, &xReturn, &yReturn, &widthReturn, &heightReturn, &borderWidthReturn, &depthReturn);
    }

    if (shift_x >= 0) {
        if (x_prev_position >= 0) {
            total_shift_x += (x_prev_position - shift_x) * 0.01;
            total_shift_y += (y_prev_position - shift_y) * 0.01;
        }

        x_prev_position = shift_x;
        y_prev_position = shift_y;
    }

    XDrawLine(display, win, gc, 0, heightReturn / 2, widthReturn, heightReturn / 2);

    XDrawLine(display, win, gc, widthReturn / 2, 0, widthReturn / 2, heightReturn);

    unsigned npoints = (widthReturn/5)+1;
    XPoint *points = (XPoint*)malloc(sizeof(XPoint) * npoints );

    for (unsigned i = 0; i < npoints; ++i) {
        unsigned w1 = i*5;
        double x = (w1*2.0/widthReturn - 1.0)*MAX_X + total_shift_x;
        double y = f(x) + total_shift_y;
        points[i].x = w1;
        points[i].y = (1.0 - (y/MAX_Y))*heightReturn / 2.0;
    }

    XDrawLines(display, win, gc, points, npoints, CoordModeOrigin);
    free (points);
}

int main() {
    Display *dpy;
    int screen;
    Window win;
    Window rootWin;
    XEvent event;
    Status rc;
    int major, minor;

    unsigned int depth;
    XSetWindowAttributes attrs;

    dpy = XOpenDisplay(NULL);

    if (dpy == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    screen = DefaultScreen(dpy);
    depth = DefaultDepth(dpy, screen);
    rootWin = RootWindow(dpy, screen);

    attrs.border_pixel = BlackPixel(dpy, screen);
    attrs.background_pixel = WhitePixel(dpy, screen);
    attrs.override_redirect = True;
    attrs.colormap = CopyFromParent;
    attrs.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | Button1MotionMask | ButtonReleaseMask;

    win = XCreateWindow(dpy, rootWin, 700, 700, 500, 300, 0, depth, InputOutput, CopyFromParent, CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &attrs);

    XMapWindow(dpy, win);

    rc = XdbeQueryExtension(dpy, &major, &minor);
    assert (rc);

    XdbeBackBuffer bbuf = XdbeAllocateBackBufferName(dpy, win, XdbeBackground);
    XdbeSwapInfo swapInfo = { .swap_window = win, .swap_action = XdbeBackground};

    for (;;) {
        XNextEvent(dpy, &event);
        switch(event.type) {
        case Expose:
            draw(dpy, bbuf, -1, -1, 1);
            XdbeSwapBuffers (dpy, &swapInfo, 1);
            break;

        case ButtonRelease:
            switch (event.xbutton.button) {
            case Button1:
                x_prev_position = -1;
                y_prev_position = -1;

                break;
            }
            break;
        case MotionNotify:
            draw(dpy, bbuf, event.xmotion.x, event.xmotion.y, 0);
            XdbeSwapBuffers (dpy, &swapInfo, 1);
            break;

        case KeyPress:
            if (XLookupKeysym(&event.xkey, 0) == XK_q) {
                XdbeDeallocateBackBufferName(dpy, bbuf);
                XDestroyWindow(dpy, win);
                XCloseDisplay(dpy);
                exit(0);
            }
        }
    }

    return 1;
}
