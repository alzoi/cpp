# Пример использования OpenGL в библиотеке SFML
Ссылки:  
https://www.sfml-dev.org/tutorials/2.5/window-opengl.php  
[youtube.com/OnigiriScience](https://www.youtube.com/watch?v=TTqLX0OHZzI&list=PLyc_E1fmJGpLjpv4tQ6s67m-zx5sxZkbM&index=1)  

Установка:
```
sudo apt-get install libsfml-dev
```
Компиляция:
```
g++ sfml_step01.cpp -o sfml_step01 -lsfml-graphics -lsfml-window -lsfml-system -lGL
```

Пример sfml_step01.cpp
```cpp
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

// render routine
void do_render() {

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  
  // Очистка кадра.
  glClear(GL_COLOR_BUFFER_BIT);

  // Точка
  glBegin(GL_POINTS);
  glColor3d(0, 1, 0);
  glVertex2d(0.9, 0.1);
  glEnd();

  // Красный отрезок.
  glBegin(GL_LINES);
  glColor3d(1, 0, 0);
  glVertex2d(0.2, 0.1);
  glVertex2d(0.8, 0.5);
  glEnd();

  // Координаты четырёхугольника (vertices to render)
  GLfloat Vertices[4][3] = {
    {-0.1f,  0.1f, 0.0f}, // top left
    { 0.1f,  0.1f, 0.0f}, // top right
    { 0.1f, -0.1f, 0.0f}, // bottom right
    {-0.1f, -0.1f, 0.0f}, // bottom left
  };

  // Задание на отрисовку четырёхугольника.
  glBegin(GL_QUADS);  
  glColor3f(1.0, 1.0, 1.0);
  for (auto Coord : Vertices) {
    glVertex3fv(Coord);
  }        
  glEnd();
  
  // Ждём завершения отрисовки кадра.
  glFinish();

}

int main()
{
    sf::ContextSettings ls_settings;

    ls_settings.depthBits         = 24;
    ls_settings.stencilBits       = 8;
    ls_settings.antialiasingLevel = 4;
    ls_settings.majorVersion      = 3;
    ls_settings.minorVersion      = 1;
    
    // create the window
    sf::Window window(
        sf::VideoMode(800, 600),
        "OpenGL",
        sf::Style::Default,
        ls_settings
    );
    
    window.setVerticalSyncEnabled(true);

    // activate the window
    window.setActive(true);

    // load resources, initialize the OpenGL states, ...

    // run the main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...
        do_render();

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}
```
