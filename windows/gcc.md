# Установка компилятора на Windows

## msys2.org
Скачиваем компилятор
https://github.com/msys2/msys2-installer/releases/download/2022-06-03/msys2-x86_64-20220603.exe
После установки, в окне msys2 даём команды для установки библиотек и инструментов:
```
pacman -Syu
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
```
В переменные окружения добавляем:
```
C:\msys64\mingw64\bin
C:\msys64\usr\bin
```

## MingW-W64-builds
Идём на сайт https://gcc.gnu.org/install/binaries.html  
Открываем ссылку [mingw-w64](https://www.mingw-w64.org/downloads/)  
Открываем ссылку [MingW-W64-builds](https://github.com/niXman/mingw-builds-binaries/releases)  
Для 64-битной версии ОС выбираем [x86_64-12.2.0-release-win32-seh-ucrt-rt_v10-rev2.7z](https://github.com/niXman/mingw-builds-binaries/releases/download/12.2.0-rt_v10-rev2/x86_64-12.2.0-release-win32-seh-ucrt-rt_v10-rev2.7z)  
Это компилятор без поддержки устаревших функций многопоточности С++11, обработкой исключений [seh](https://learn.microsoft.com/en-us/cpp/cpp/structured-exception-handling-c-cpp?view=msvc-170) (Structured Exception Handling, используется в Windows) и универсальной средой выполнения кода C [ucrt](https://support.microsoft.com/en-us/topic/update-for-universal-c-runtime-in-windows-c0514201-7fe6-95a3-b0a5-287930f3560c).
