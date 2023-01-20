# GUI

## Ссылки
[WinAPI приложение для Windows](https://www.youtube.com/watch?v=TzuYeY_K02c)  
[Windows Graphics Architecture](https://learn.microsoft.com/en-us/windows/win32/learnwin32/overview-of-the-windows-graphics-architecture)  
[Создание простого приложения Windows Direct2D](https://learn.microsoft.com/ru-ru/windows/win32/direct2d/direct2d-quickstart?source=recommendations)  
[Учебник по Windows GDI](https://zetcode.com/gui/winapi/gdi/)  
[Учебник по Windows GDI+](https://learn.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-drawing-a-line-use)  
[GUI приложение на C++ с использованием библиотеки wxWidgets](https://www.youtube.com/watch?v=BjQhp0eHmJw&list=PLFk1_lkqT8MbVOcwEppCPfjGOGhLvcf9G)  
[Implement GUI in C++ Step by Step in VS 2017](https://www.youtube.com/watch?v=SC6VfQbrjtY&list=PLmeQIS8S5cYPFkpAk6x-aF0KEB0rfJb-K&index=3)  
[Create Your First C++ Windows Form](https://www.youtube.com/watch?v=zv8DkkhBNR0)  
[C++ for Linux, Windows and MacOS - building with wxWidgets and CMake](https://www.youtube.com/watch?v=MfuBS9n5_aY&list=PL0qQTroQZs5vVmTuBew-nTx9DIu6rRl2c)  
[Уроки по WinAPI](https://www.youtube.com/watch?v=UluSI1P4Ijg&list=PLBOPkQsFLCR2H7_0Ss0W6y703J_ySRGi_)  
[Wine - программное обеспечение, позволяющее запускать Windows приложения в Linux ОС](https://www.winehq.org/)  
[Разработка UI системы](https://habr.com/ru/post/521306/)  
[CS332. Компьютерная графика](https://edu.mmcs.sfedu.ru/course/view.php?id=188)  
[Курс Компьютерная графика 2018 | Виталий Галинский ](https://www.youtube.com/watch?v=J6uINtQW7Ho&list=PL-_cKNuVAYAVK2E--20nqggd57jcipCk6)  
[Лекции к курсу Компьютерная графика 2018](https://www.school30.spb.ru/cgsg/cgc2018/)  

Запуск Windows приложения в Linux
```cmd
wine win_app.exe
```
## GUI в операционной системе Windows
[WinUI 3 - Новая эра разработки под Windows](https://habr.com/ru/post/546576/)  

## Графический стек Linux
[Обзор современного графического стека Linux](https://bootlin.com/doc/training/graphics/graphics-slides.pdf)  
[Xlib/XCB/GLX/OpenGL](https://stackoverflow.com/questions/40543176/does-opengl-use-xlib-to-draw-windows-and-render-things-or-is-it-the-other-way-a)  
[Рисование с помощью библиотеки Xlib](https://linuxgazette.net/issue78/tougher.html), [второй пример](https://halverscience.net/c_programming/c_graphics_xwindows/c_graphics_xwindows.html)  
[Примеры Xlib](https://github.com/QMonkey/Xlib-demo/tree/master/src)  
[Basic Graphics Programming With The Xlib Library - by Guy Keren](http://web.archive.org/web/20071018025425/http://users.actcom.co.il/~choo/lupg/tutorials/xlib-programming/xlib-programming.html)  
[Графический стек Linux](https://www.baeldung.com/linux/gui)  

Когда мы запускаем графическое приложение, оно загружает драйвер OpenGL — например, [Mesa](https://docs.mesa3d.org/). Драйвер, в свою очередь, загружает libdrm , что позволяет напрямую обращаться к ядру через ioctl.

[X Window System](https://linux.die.net/man/7/x) — это оконная система с открытым исходным кодом, которая используется в большинстве дистрибутивов на основе Linux. Он основан на архитектуре клиент-сервер, которая обеспечивает прозрачный для сети способ взаимодействия с окнами, который также можно использовать в удаленных средах.  

[X.Org](https://en.wikipedia.org/wiki/X.Org_Server) — это серверная реализация системы X Window System. Это наиболее часто используемый сервер отображения в Unix-подобных системах. Сервер X.Org обычно запускается диспетчером отображения или вручную с виртуального терминала.  

Библиотека **X**, или [Xlib](https://tronche.com/gui/x/xlib/), является реализацией на стороне клиента. Эта библиотека, в свою очередь, используется графическими наборами инструментов, такими как GTK+ и QT , для создания графического интерфейса для программного приложения.  

[Blender](https://github.com/blender/blender/) - кроссплатформенный инструмент для 3D-моделирования и анимации. Blender не полагается на стороние [библиотеки GUI](https://philippegroarke.com/posts/2018/c++_ui_solutions/) элементов (Qt, GTK+ и т. д.) и низкоуровневые клиентские библиотеки, но имеет собственную библиотеку виджетов, полностью основанную на OpenGL.

## Графические библиотеки для работы с оконной подсистемой ОС
[opengl.org/resources/libraries/](https://www.opengl.org/resources/libraries/)  
[GLUT/freeglut](https://www.opengl.org/resources/libraries/glut/) история, [пример](http://www.codebind.com/linux-tutorials/install-opengl-ubuntu-linux/)  
[SDL](https://www.libsdl.org/)  
[SFML](https://www.sfml-dev.org/) стабильная  
[GLFW](https://www.glfw.org/) наиболее проработанная, [пример](https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.1.hello_triangle/hello_triangle.cpp)  

## OpenGL
[https://paroj.github.io/gltut/](https://www.opengl.org/resources/libraries/)   
[learnopengl.com](https://learnopengl.com/Getting-started/Hello-Window)  
[opengl-tutorial.org](http://www.opengl-tutorial.org/ru/beginners-tutorials/tutorial-2-the-first-triangle/)  
[Separate thread for rendering OpenGL](http://www.songho.ca/opengl/gl_mvc.html)  

## Игровой цикл (цикл обработки сообщений)
https://dewitters.com/dewitters-gameloop/  
https://gafferongames.com/post/fix_your_timestep/  
[codeproject.com/Articles/27219/TetroGL](https://www.codeproject.com/Articles/27219/TetroGL-An-OpenGL-Game-Tutorial-in-C-for-Win32-Pla)  
## Установка драйверов
https://wiki.debian.org/ATIProprietary  

## Средство просмотра аппаратных возможностей OpenGL
https://www.saschawillems.de/creations/opengl-hardware-capability-viewer/ 

## Библиотека GUI конмпонентов GTK
https://gitlab.com/lockie/otus-gtk  
https://www.youtube.com/watch?v=CNEJofOOPSY&t=894s  

## Библиотека GUI конмпонентов wxWidgets
[wxWidgets на Just Dev Tutorials](https://www.youtube.com/watch?v=MfuBS9n5_aY&list=PL0qQTroQZs5vVmTuBew-nTx9DIu6rRl2c)  

