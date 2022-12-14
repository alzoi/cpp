// Рисуем сцену, не каждый такт обновления развёртки монитора,
// а только если область рисования требует обновления.
// g++ step02.cpp -o step02 -std=c++17 -Wall -lGL -lGLEW -lglfw3 -lpthread -ldl

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>

class InvokeOnDestroy {
// Класс для выполнения завершающей функции.
  std::function<void()> f;
public:
  InvokeOnDestroy(std::function<void()> &&fn) : f(fn) {}
  ~InvokeOnDestroy() { f(); }
};

void myGlfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  // Окну отправляем команду "Закрыть" по нажатию клавиши Escape.
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void render(GLFWwindow *wnd) {
  
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);  

  glBegin(GL_LINES);
    glColor3d(1, 0, 0);
    glVertex2d(0.2, 0.1);
    glVertex2d(0.8, 0.5);
  glEnd();

  glfwSwapBuffers(wnd);
}

void wnd_refresh_callback(GLFWwindow *wnd) {
// Рисуем сцену при поступлении события "Обновить окно".  
  
  render(wnd);
  std::cout << "1" << std::flush;

}

int main() {
  
  if (!glfwInit()) return 1;

  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  glfwWindowHint(GLFW_STENCIL_BITS, 8);
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

  InvokeOnDestroy _glfwTerminate(glfwTerminate);

  GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Tutorial", nullptr, nullptr);
  
  glfwSetKeyCallback(window, myGlfwKeyCallback);
  glfwSetWindowRefreshCallback(window, wnd_refresh_callback);

  // Активируем окно для потока вывода OpenGl.
  glfwMakeContextCurrent(window);
  if (glewInit() != GLEW_OK) return 1;
  
  // Ждём указанное число обновлений развёртки экрана перед обновлением видимого буфера.
  glfwSwapInterval(0);
  
  render(window);
  
  while (!glfwWindowShouldClose(window)) {
    
    glfwPollEvents();
  
  }

  std::cout << std::endl << std::flush;

  return 0;
}
