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
![image](https://user-images.githubusercontent.com/20499566/191022425-daecacc9-779b-4245-abc6-11bd73d6f722.png)  
Важно учитывать, что обычная операция проверки условия выполняется не атомарно
```cpp
if (count == 0) {
}
```
указанная операция в машинных кодах разбивается на следующие инструкции CPU:
```asm
# 1) Извлекаем из памяти по адресу count значение в регистр процессора rax
move count(%rip), %rax
# 2) Сравниваем значение регистра rax с нулём.
cmp $0, %rax
# 3) Если значение в регистре rax равно нулю, то переходим на метку по адресу .L1
je .L2
```
Наш поток считывает ноль из памяти по адресу count.  
Планировщик ОС переключается на выполнение другого потока.  
Новый поток увеличивает значение общей переменной count на единицу.  
Далее планировщик ОС возвращается к выполнению инструкции № 2 нашего потока и сравнивает значения регистра rax с нулём, но, так как другой поток уже изменил значение count, то при сравнении будет сделан ошибочный вывод.  
Мы выполним ветку для **count == 0**.  

Инструкция [xchg %rax, (lock_addr)](https://github.com/alzoi/C/blob/master/spinlock.md) атомарно выполняет обмен значений между регистром и ячейкой памяти (второй операнд).  

Инструкция [lock cmpxchg %rcx, (lock_addr)](https://www.felixcloutier.com/x86/cmpxchg) атомарно сравнивает значение в регистре rax со вторым операндом (ячейкой памяти), если значения равны, то первый операнд загружается во второй операнд.  
В противном случае второй операнд загружается в регистр rax.  
Флаг ZF = 1, если при сравнении инструкция cmpxchg определила, что значение второго операнда равно значению регистра rax, в противном случае ZF = 0.  
Явный префикс lock разрешает атомарное выполнение инструкции **cmpxchg**.
```asm
.section .data

# Общая ячейка памяти со значением 1.
lock_addr:
  .quad 1 

.section .text

.global _start

_start:    
  # Передаём в регистр rcx единицу, это значение для установки в ячейку lock_addr
  mov $0x1, %rcx
  # Передаём в регистре rax значение ноль, с этим значением будем сравнивать ячейку lock_addr.
  xor %rax, %rax 

  # Проверяем, что значение в ячейке памяти lock_addr равно значению в регистре rax,
  # если значения равны, то в ячейку памяти (lock_addr) записываем значение из rcx.  
  lock cmpxchg %rcx, (lock_addr)

  # Переход к метке .L2_no_locked, если флаг ZF=0, то есть значение в rax было не равно значению в ячейке (lock_addr)
  jne .L2_no_locked            

# Если получилось установить блокировку.
.L1_locked:
  mov $60, %rax   # 60 - это номер системного вызова для функции ядра exit.
  mov $77, %rdi
  syscall

# Если не получилось установить блокировку.
.L2_no_locked:
  # в этой точке в rax уже будет установлено значение из ячейки lock_addr,
  # так как при выполнении инстркции cmpxchg эти значения были не равны. 
  mov $60, %rax
  mov $88, %rdi
  syscall

# Освободить блокировку
.L3_unlock:
  movq $0, (lock_addr)
  ret
  
# Вывод данной программы:
#   код 88 - выполнился код в метке L2_no_locked,
#            блокировку захватить не удалось, так как критическая секция блокирована другим потоком.
```

## Примеры FUTEX
Системный вызов [futex](https://man7.org/linux/man-pages/man2/futex.2.html).
```cpp
long syscall(SYS_futex,
  uint32_t*               uaddr,
  int                     futex_op,
  uint32_t                val,
  const struct timespec*  timeout,
  uint32_t*               uaddr2,
  uint32_t                val3
);
```
Операция futex_op = **FUTEX_WAIT_PRIVATE** приватно для одного процесса проверяет, что значение в слове фьютекса (указанном с помощью адреса uaddr) всё ещё содержит ожидаемое значение val, и если да, то ОС останавливает поток и помещает его в очередь приостановленных потоков. Потоки или поток возобновят свою работу после выполнения системного вызова SYS_futex с операцией **FUTEX_WAKE_PRIVATE** над словом фьютекса.
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
