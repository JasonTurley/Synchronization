# Synchronization
A simplified implementation of a mutex object and counting semaphore. The lock utilizes [GNU atomic builtins](https://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Atomic-Builtins.html)
(i.e. test-and-set). The mutex may be one of four types: normal, errorcheck, or recursive. 

**Normal** mutexes favor speed over correctness. No error checking or deadlock detection occurs. 
Meaning any thread may release the mutex via ```mutex_unlock()``` (_not good!_).

**Errorcheck** types ensure the correct thread is locking and unlocking the mutex. 

**Recursive** mutexes perform the same operations as errorcheck, but add relock ability. Hence, the same thread may lock the same mutex multiple times.
When releasing, the thread _must_ call ```mutex_unlock``` for each ```mutex_lock```.

# Motivation
* To become a better systems programmer.
* To learn more about synchronization primitives.
* Appreciate the complexity of OS kernels.

# Credits
This project is inspired by [SystemsProgrammingProjects]9https://github.com/angrave/SystemProgrammingProjects/wiki) by University of Illinois Computer Science professor, Lawrence Angrave.
