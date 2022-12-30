// Рисуем в окне красную линию с помощью библиотеки Xlib.

// g++ -Wall -W ex3.cpp -lX11

#include <X11/Xlib.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#define NIL (0)

int main() {
  
  // Graphics context.
  GC       gc;
  XColor   red_col;
  Colormap colormap;

  // Дисплей.
  Display *dpy = XOpenDisplay(NIL);
  assert(dpy);

  // Цвет для фона.
  //int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));
  int blackColor = BlackPixel(dpy, DefaultScreen(dpy));

  // Красный цвет.
  char red_bits[] = "#FF0000";
  colormap = DefaultColormap(dpy, 0);
  XParseColor(dpy, colormap, red_bits, &red_col); 
  XAllocColor(dpy, colormap, &red_col);
  
  // Создаём окно.
  Window w = XCreateSimpleWindow(dpy,
    DefaultRootWindow(dpy), 0, 0, 200, 100, 0, blackColor, blackColor);
  
  XSelectInput(dpy, w, StructureNotifyMask);
  XMapWindow(dpy, w);
  
  // Ожидание подключения к серверу.
  while(1) {
    XEvent e; XNextEvent(dpy,&e);
    if(e.type == MapNotify) break;
  }
  
  // Контекст.
  gc = XCreateGC(dpy, w, 0, NIL);

  // Линия.
  XSetForeground(dpy, gc, red_col.pixel);
  XDrawLine(dpy, w, gc, 10, 70, 180, 30);

  XFlush(dpy);
  sleep(1);
  
  char str[2];
  fgets(str, 2, stdin); 
  
  return(0);

}
