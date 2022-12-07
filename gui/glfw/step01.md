# Библиотека GLFW и OpenGL

## Установка библиотеки
https://www.glfw.org/docs/latest/compile_guide.html  
```
sudo apt install xorg-dev
cd ~
git clone https://github.com/glfw/glfw.git
cd glfw
cmake -S . -B build
cd build
make
make install
```

## Программа glfw_main.cpp
```cpp
#include <GLFW/glfw3.h>

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

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        do_render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
```

## Компиляция программы
```
g++ glfw_main.cpp -o glfw_main -std=c++17 -Wall -lGL -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
```
