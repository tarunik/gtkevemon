#ifndef THREAD_HEADER
#define THREAD_HEADER

#include <pthread.h>
#include <semaphore.h>

class Thread
{
  private:
    pthread_t handle;

    static void* stub (void* arg)
      { return ((Thread*)arg)->run(); }

  protected:
    virtual void* run (void) = 0;

  public:
    virtual ~Thread (void) { }

    void create (const pthread_attr_t* p = 0)
      { pthread_create(&handle, p, Thread::stub, (void*)this); }
    void cancel (void)
      { pthread_cancel(handle); }
    void join (void)
      { pthread_join(handle, 0); }
};

/* ---------------------------------------------------------------- */

class Semaphore
{
  private:
    sem_t sem;

  public:
    /* Defaults to mutex. */
    Semaphore (unsigned int value = 1)
      { sem_init(&sem, 0, value); }
    Semaphore (unsigned int value, int pshared)
      { sem_init(&sem, pshared, value); }

    /* DOWN the semaphore. */
    int wait (void)
      { return sem_wait(&sem); }
    /* UP the semaphore. */
    int post (void)
      { return sem_post(&sem); }
    /* Returns the current value. */
    int get_value (void)
      {
        int value;
        sem_getvalue(&sem, &value);
        return value;
      }
};

#endif /* THREAD_HEADER */