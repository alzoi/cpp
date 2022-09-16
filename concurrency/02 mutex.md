# Взаимное исключение (mutex)

## Ссылки
[Лекция](https://youtu.be/fmcBo4E7qr0)  
[Семинар](https://youtu.be/QMM4GDSQya4)  
[Задача mutex](https://gitlab.com/Lipovsky/concurrency-course/-/tree/master/tasks/mutex/mutex)  
[Задача SpinLock](https://gitlab.com/Lipovsky/concurrency-course/-/tree/master/tasks/mutex/spinlock)  

## Теория

**atomic** создан из [spinlock](https://github.com/alzoi/C/blob/master/spinlock.md) - цикла в пространстве пользователя, который постоянно проверяет установку определённого значения в ячейке памяти. spinlock нагружает CPU.  

**mutex** создан из futex - очередь остановленных (не выполняющихся) потоков в ядре ОС.  mutex использует [системный вызов](https://man7.org/linux/man-pages/man2/futex.2.html) к ядру ОС, обращение занимает время, но остановленный поток не нагружает CPU. Подробнее в [видео](https://youtu.be/xKqO04SN6C0?list=PLEJxKK7AcSEGPOCFtQTJhOElU44J_JAun&t=161).

## Примеры
Системный вызов futex, зависит от CPU
```cpp
  uint32_t addr;
  int val_expected = 0;
  int foo = syscall( SYS_futex, &addr, FUTEX_WAIT_PRIVATE, val_expected, nullptr, nullptr, 0);
```
