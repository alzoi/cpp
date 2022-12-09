# Библиотека GLFW и OpenGL

## Установка библиотеки
https://www.glfw.org/docs/latest/compile_guide.html  
Библиотека [GLEW](https://github.com/nigels-com/glew) для определения и загрузки расширений OpenGL для целевой платформы.
```
sudo apt-get update
sudo apt install xorg-dev
cd ~
git clone https://github.com/glfw/glfw.git
cd glfw
cmake -S . -B build
cd build
make
sudo make install
make clean
```
Проверка версии OpenGL
```
sudo apt-get install mesa-utils
glxinfo | grep "OpenGL version"
```
Возможно потребуются версии
```
sudo apt-get install cmake pkg-config
sudo apt-get install mesa-utils libglu1-mesa-dev freeglut3-dev mesa-common-dev
sudo apt-get install libglew-dev libglfw3-dev libglm-dev
sudo apt-get install libao-dev libmpg123-dev
```

## Компиляция программы
```
g++ glfw_step01.cpp -o glfw_step01 -std=c++17 -Wall -lGL -lglfw3 -lX11 -lXxf86vm -lXrandr \
-lpthread -lXi -ldl -lXinerama -lXcursor -lGLEW
```
Или более компактный вариант
```
g++ glfw_step01.cpp -o glfw_step01 -std=c++17 -Wall -lGL -lglfw3 -lpthread -ldl
```

## Программа glfw_step01.cpp
```cpp
#include <stdexcept>
#include <iostream>

#include <GLFW/glfw3.h>

void render_openGL() {
// Функция отрисовки сцены функциями OpenGL, сцена создаётся во внеэкранном буфере (невидимый задний буфер).
  
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

struct glfw_error : public std::runtime_error {
// Класс для обработки ошибок.
  glfw_error(const char *s) : std::runtime_error(s) {}
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
// Область просмотра подстраивать под размеры окна.
  glViewport(0, 0, width, height);
}

void error_callback(int, const char *err_str) {
// Выбросить ошибку.
  throw glfw_error(err_str);
}

int main(void) try {

  glfwSetErrorCallback(error_callback);
  
  glfwInit();
  // if (!glfwInit()) return -1;
  
  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  glfwWindowHint(GLFW_STENCIL_BITS, 8);
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Профиль для OpenGL >=3.2 

  // Создать окно и связанный с ним контекст OpenGL.
  GLFWwindow* lo_window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
  if (!lo_window) {
      glfwTerminate();
      return -1;
  }

  // Установить контекст указанного окна lo_window текущим для вызывающего потока.
  glfwMakeContextCurrent(lo_window);
  glfwSetFramebufferSizeCallback(lo_window, framebuffer_size_callback);

  // Определяем доступную версию OpenGL. 
  GLint vers1, vers2;
  glGetIntegerv(GL_MAJOR_VERSION, &vers1);
  glGetIntegerv(GL_MINOR_VERSION, &vers2);
  std::cout << "Данная видеокарта поддерживает версию OpenGL: " << vers1 << "." << vers2 << std::endl;
  
  // Цикл, пока пользователь не закроет окно
  while (!glfwWindowShouldClose(lo_window)) {
      
      render_openGL();

      // Скопировать данные заднего буфера на экранный буфер (видимый пользователю передний буфер).
      glfwSwapBuffers(lo_window);

      // Обработать события, которые находятся в очереди событий, затем вернуться в точку вызова.
      glfwPollEvents();
  }
  
  // Удалить все оставшиеся окна и курсоры.
  glfwTerminate();
  
  return 0;

} catch (glfw_error &E) {
  std::cout << "GLFW error: " << E.what() << std::endl;
} catch (std::exception &E) {
  std::cout << "Standard error: " << E.what() << std::endl;
} catch (...) {
  std::cout << "Unknown error\n";
}
```
