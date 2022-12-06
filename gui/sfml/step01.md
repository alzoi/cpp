# Пример использования OpenGL в библиотеке SFML
Ссылки:  
https://www.sfml-dev.org/tutorials/2.5/window-opengl.php  

Установка:
```
sudo apt-get install libsfml-dev
```
Компиляция:
```
g++ opengl.cpp -o sfml_app -lsfml-graphics -lsfml-window -lsfml-system -lGL
```

```с++
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

// vertices to render
GLfloat Vertices[4][3] = {
    {-0.5f, 0.5f, 0.0f},  // top left
    {0.5f, 0.5f, 0.0f},   // top right
    {0.5f, -0.5f, 0.0f},  // bottom right
    {-0.5f, -0.5f, 0.0f}, // bottom left
};

// render routine
void do_render() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_QUADS);
  glColor3f(1.0, 1.0, 1.0);
  for (auto Coord : Vertices)
    glVertex3fv(Coord);
  glEnd();
}

int main()
{
    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
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
