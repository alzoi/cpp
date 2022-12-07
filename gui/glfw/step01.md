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

## Программа glfw_step01.cpp
```cpp
#include <GLFW/glfw3.h>

void render_openGL() {
  // Функция отрисовки сцены функциями OpenGL.
  
  // Цвет фона.
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  
  // Очистка буфера вывода установленным цветом.
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

  // Четыре координаты четырёхугольника (vertices to render)
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

int main(void) {
    
    if (!glfwInit()) return -1;

    GLFWwindow* lo_window;

    // Создать окно и связанный с ним контекст OpenGL.
    lo_window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!lo_window) {
        glfwTerminate();
        return -1;
    }

    // Установить контекст указанного окна lo_window текущим для вызывающего потока.
    glfwMakeContextCurrent(lo_window);

    // Цикл, пока пользователь не закроет окно
    while (!glfwWindowShouldClose(lo_window)) {
        
        render_openGL();

        // Поменять местами передний и задний буферы указанного окна.
        glfwSwapBuffers(lo_window);

        // Обработать события, которые находятся в очереди событий, затем вернуться в точку вызова.
        glfwPollEvents();
    }
    
    // Удалить все оставшиеся окна и курсоры.
    glfwTerminate();
    
    return 0;
}
```

## Компиляция программы
```
g++ glfw_step01.cpp -o glfw_step01 -std=c++17 -Wall -lGL -lglfw3 -lX11 -lXxf86vm -lXrandr \
-lpthread -lXi -ldl -lXinerama -lXcursor
```
Или более компактный вариант
```
g++ glfw_step01.cpp -o glfw_step01 -std=c++17 -Wall -lGL -lglfw3 -lpthread -ldl
```
