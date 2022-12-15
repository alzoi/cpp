# Установка GLFW
Скачиваем [Windows pre-compiled binaries](https://github.com/glfw/glfw/releases/download/3.3.8/glfw-3.3.8.bin.WIN64.zip)  
Из директории библиотеки /glfw-3.3.8.bin.WIN64/ копируе следующие папки
```
include
lib-mingw-w64
```
вставляем их в директорию собственного проекта /my_prj/, папку /lib-mingw-w64/ переименовываем в /lib/.

# Установка GLAD
На сайте https://glad.dav1d.de/ генерируем загрузчик OpenGL, указываем версию, в Profile указываем Core.  
Нажимаем ADD ALL, чтобы добавить все Extensions.  
Нажимаем GENERATE.  
Скачиваем файл glad.zip.  
Из данного архива копируем папки include и src в директорию своего проекта. 

# У
https://www.youtube.com/watch?v=hRInLNR9iRg

# Пример
https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/1.2.hello_window_clear/hello_window_clear.cpp  
