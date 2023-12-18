# Компактный компилятор C (Tiny C Compiler)
https://bellard.org/tcc/  

## Установка
Скачать  
[архив tcc win32](https://web.archive.org/web/20200227013749/http://download-mirror.savannah.gnu.org/releases/tinycc/tcc-0.9.27-win32-bin.zip)  
[архив tcc win64](https://web.archive.org/web/20231122125001/http://download-mirror.savannah.gnu.org/releases/tinycc/tcc-0.9.27-win64-bin.zip)  
[перечень заголовков API Win2](https://web.archive.org/web/20231122124847/http://nongnu.askapache.com/tinycc/winapi-full-for-0.9.27.zip)  
Распаковать в папку, папку include API Win32 переместить в папку проекта tcc.

## Компиляция
Создать файл make.but для компиляции файла gui_app.c с помощью компилятора tcc
```
C:\tcc\tcc C:\tcc\dev\gui_app.c -Wall -O2 -s -lkernel32 -luser32 -lgdi32 -lcomctl32 -luxtheme -mwindows -municode
```
