# Установка компилятора на Windows

## msys2.org
Скачиваем компилятор
https://github.com/msys2/msys2-installer/releases/download/2022-06-03/msys2-x86_64-20220603.exe
После установки, в окне msys2 даём команды для установки библиотек и инструментов:
```
pacman -Syu
pacman -Su
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
```
В переменные окружения добавляем:
```
C:\msys64\mingw64\bin
C:\msys64\usr\bin
```
