# Взаимное исключение (mutex)

## Ссылки
[Лекция](https://youtu.be/fmcBo4E7qr0)  
[Семинар](https://youtu.be/QMM4GDSQya4)  
[Задача mutex](https://gitlab.com/Lipovsky/concurrency-course/-/tree/master/tasks/mutex/mutex)  
[Задача SpinLock](https://gitlab.com/Lipovsky/concurrency-course/-/tree/master/tasks/mutex/spinlock)  

## Теория

**atomic** создан из [spinlock](https://github.com/alzoi/C/blob/master/spinlock.md) - цикла в пространстве пользователя, который постоянно проверяет установку определённого значения в ячейке памяти. spinlock нагружает CPU.  

**mutex** создан из futex - очередь остановленных (не выполняющихся) потоков в ядре ОС.  mutex использует [системный вызов](https://man7.org/linux/man-pages/man2/futex.2.html) к ядру ОС, обращение занимает время, но остановленный поток не нагружает CPU, помещённые в очередь ожидания потоки не получают процессорного времени. Подробнее в [видео](https://youtu.be/xKqO04SN6C0?list=PLEJxKK7AcSEGPOCFtQTJhOElU44J_JAun&t=161).  
Реализацию функции пробуждения **wakeup** спящего в очереди потока можно посмотреть в книге [xv6 строка 2964](https://pdos.csail.mit.edu/6.828/2018/xv6/xv6-rev11.pdf)
Реализацию функции засыпания **sleep** - помещения потока в очередь ожидания можно посмотреть в книге [xv6 строка 2874](https://pdos.csail.mit.edu/6.828/2018/xv6/xv6-rev11.pdf).
## Пример MUTEX
![image](https://user-images.githubusercontent.com/20499566/191020945-7bbc5eeb-ea10-418d-854a-133d8aa412b0.png)

## Примеры FUTEX
Системный вызов [futex](https://man7.org/linux/man-pages/man2/futex.2.html), с операцией FUTEX_WAIT_PRIVATE. 
Операция **FUTEX_WAIT_PRIVATE** приватно для одного процесса проверяет, что значение в слове фьютекса (указанном с помощью адреса uaddr) всё ещё содержит ожидаемое значение val, и если да, то ОС останавливает поток и помещает его в очередь приостановленных потоков. Потоки или поток возобновят свою работу после выполнения системного вызова SYS_futex с операцией **FUTEX_WAKE_PRIVATE** над словом фьютекса.
Вызов работает в ОС Linux:  
```cpp
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/futex.h>
#include <cstdint>
#include <climits>
//#include <limits.h>

// Общий адрес фьютекса (слово фьютекса).
uint32_t addr;  

// Поток № 01.
void thread_t01() {  
  
  int val_expected = 0;
  
  // Приостанавливаем текущий поток до получения события от других потоков.
  long foo = syscall( SYS_futex, &addr, FUTEX_WAIT_PRIVATE, val_expected, nullptr, nullptr, 0);
}

// Поток № 02.
void thread_t02() {  
  
  uint32_t val_count = 1;
  
  // Просим ядро ОС разбудить первый поток в очереди, ожидающих на адресе addr.
  long foo = syscall( SYS_futex, &addr, FUTEX_WAKE_PRIVATE, val_count, nullptr, nullptr, 0);
}

// Поток № 03.
void thread_t03() {  
  
  uint32_t val_count = INT_MAX;
  
  // Просим ядро ОС разбудить все потоки, ожидающие на адресе addr.
  long foo = syscall( SYS_futex, &addr, FUTEX_WAKE_PRIVATE, val_count, nullptr, nullptr, 0);
}

```
