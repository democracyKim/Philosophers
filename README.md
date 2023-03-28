# Eat, Sleep and Think: Philosophers with Threads and Mutexes

<details>
<summary>External functions</summary>
<div markdown="1">

- usleep(): This function is used to pause the execution of a thread for a specified number of microseconds. It takes a single argument, which is the number of microseconds to sleep. 
```c
usleep(1000000); // sleep for 1 second
```
This code pauses the execution of the current thread for 1 second.

- gettimeofday(): This function is used to get the current time as a struct timeval, which contains the number of seconds and microseconds since the Unix epoch (January 1, 1970). It takes two arguments: a pointer to a struct timeval to be filled in with the current time, and a struct timezone pointer that can be set to NULL.
```c
struct timeval tv;
gettimeofday(&tv, NULL);
printf("The current time is %ld seconds and %ld microseconds\n", tv.tv_sec, tv.tv_usec);
```
This code gets the current time and prints it to the console.

- pthread_create(): This function is used to create a new thread of execution. It takes four arguments: a pointer to a pthread_t variable that will be filled in with the ID of the new thread, a pthread_attr_t pointer that can be set to NULL, a function pointer that takes a single void* argument and returns a void*, and a void* argument to be passed to the function.
```c
#include <pthread.h>
#include <stdio.h>

void *thread_func(void *arg) {
    printf("Hello, world!\n");
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);
    pthread_join(tid, NULL);
    return 0;
}
```
This code creates a new thread that calls thread_func(), which prints "Hello, world!" to the console.

- pthread_detach(): This function is used to detach a thread, which allows the system to reclaim its resources when the thread terminates. It takes a single argument, which is the pthread_t ID of the thread to detach.
```c
pthread_t tid;
pthread_create(&tid, NULL, thread_func, NULL);
pthread_detach(tid);
```
This code creates a new thread and detaches it from the main thread.

- pthread_join(): This function is used to wait for a thread to terminate and retrieve its exit status. It takes two arguments: the pthread_t ID of the thread to join, and a pointer to a void* variable that will be filled in with the thread's exit status.
```c
pthread_t tid;
pthread_create(&tid, NULL, thread_func, NULL);
void *status;
pthread_join(tid, &status);
```
This code creates a new thread and waits for it to terminate, storing its exit status in the status variable.

- pthread_mutex_init(): This function is used to initialize a mutex lock. It takes two arguments: a pointer to the mutex lock to be initialized, and a pthread_mutexattr_t pointer that can be set to NULL.
```c
pthread_mutex_t mutex;
pthread_mutex_init(&mutex, NULL);
```

- pthread_mutex_destroy(): This function is used to destroy a mutex lock that was previously initialized with pthread_mutex_init(). It takes a single argument, which is a pointer to the mutex lock to be destroyed. 
```c
pthread_mutex_t mutex;
pthread_mutex_init(&mutex, NULL);
// use the mutex lock...
pthread_mutex_destroy(&mutex);
```
This code initializes a new mutex lock, uses it, and then destroys it.

- pthread_mutex_lock(): This function is used to lock a mutex lock. If the mutex lock is already locked by another thread, the calling thread will block until the lock becomes available. It takes a single argument, which is a pointer to the mutex lock to be locked.
```c
pthread_mutex_t mutex;
pthread_mutex_init(&mutex, NULL);
pthread_mutex_lock(&mutex);
// critical section...
pthread_mutex_unlock(&mutex);
pthread_mutex_destroy(&mutex);
```
This code initializes a new mutex lock, locks it, enters a critical section, unlocks it, and then destroys it.

- pthread_mutex_unlock(): This function is used to unlock a mutex lock that was previously locked with pthread_mutex_lock(). It takes a single argument, which is a pointer to the mutex lock to be unlocked.
```c
pthread_mutex_t mutex;
pthread_mutex_init(&mutex, NULL);
pthread_mutex_lock(&mutex);
// critical section...
pthread_mutex_unlock(&mutex);
pthread_mutex_destroy(&mutex);
```
This code initializes a new mutex lock, locks it, enters a critical section, unlocks it, and then destroys it.

</div>
</details>