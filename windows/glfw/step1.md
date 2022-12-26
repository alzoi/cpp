# Пример GLFW + GLAD + OpenGL

## Ссылка
https://www.youtube.com/watch?v=hRInLNR9iRg  
https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/1.2.hello_window_clear/hello_window_clear.cpp  
[Настройка потока для GLFW](https://stackoverflow.com/questions/31328280/thread-setup-for-glfw/31621053#31621053)  

## Установка GLFW
Скачиваем [Windows pre-compiled binaries](https://github.com/glfw/glfw/releases/download/3.3.8/glfw-3.3.8.bin.WIN64.zip)  
Из директории библиотеки /glfw-3.3.8.bin.WIN64/ копируе следующие папки
```
include
lib-mingw-w64
```
вставляем их в директорию собственного проекта /my_prj/, папку /lib-mingw-w64/ переименовываем в /lib/.  
В папку проекта /bin/ необходимо поместить библиотечный файл /lib/glfw3.dll. 

## Установка GLAD
На сайте https://glad.dav1d.de/ генерируем загрузчик OpenGL, указываем версию, в Profile указываем Core.  
Нажимаем ADD ALL, чтобы добавить все Extensions.  
Нажимаем GENERATE.  
Скачиваем файл glad.zip.  
Из данного архива копируем папки include и src в директорию своего проекта. 

## Пример файл step1.cpp
```cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
//#include <windows.h> // Для работы с функцией GetTickCount

static void error_callback(int error, const char* description) {
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void do_render(GLFWwindow* window) {
    float ratio;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);

    ratio = width / (float) height;
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glRotatef((float)glfwGetTime()*50.f, 0.f, 0.f, 1.f);

    glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
    glEnd();

    glfwSwapBuffers(window);
}

int main(void) {
    
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    
    if (!glfwInit()) exit(EXIT_FAILURE);
    
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    //char newTitle[128];
    
    glfwSwapInterval(1);
    
    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff = 0.0;
    unsigned int counter = 0;
        
    glfwSetKeyCallback(window, key_callback);

    glfwSetTime(0.0); // Сброс счётчика времени.

    while (!glfwWindowShouldClose(window)) {
        
        glfwPollEvents();
        //glfwWaitEvents();
        
	do_render(window);

        // Счётчик кадров.
	    counter++;

        // Получаем число секунд, которые прошли с момента сброса счётчика времени.
        // Результат получаем в секундах, например: 0,000.295.800 cекунд = 296 микросекунд = 295 800 наносекунд).
        crntTime = glfwGetTime();

        // Считаем интервал времени на отрисовку одного кадра.
        timeDiff = crntTime - prevTime;
        
        // Обновляем заголовок через одну секунду.
        if (timeDiff >= 1.0 ) {

            std::string FPS = std::to_string(counter);
            std::string msF = std::to_string(timeDiff * 1000 / counter );

            std::string newTitle = "OpenGL: " + FPS + " FPS (" + msF + " мс на кадр)";
            glfwSetWindowTitle(window, newTitle.c_str());

            prevTime = crntTime;
            counter  = 0;
        }

        // В заголовок окна выводим количество миллисекунд с момента включения ПК.
        //snprintf(newTitle, sizeof(newTitle), "%lu", GetTickCount());
        //glfwSetWindowTitle(window, newTitle);
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
```

## Makefile
```
./bin/st1.exe: ./src/step1.cpp
	g++ ./src/step1.cpp ./src/glad.c -o ./bin/st1.exe --std=c++17 -I./include -L./lib -lglfw3dll
```

## Компиляция
```
mingw32-make
```
