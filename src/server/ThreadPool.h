//
// Created by h on 12/01/18.
//

#ifndef EX5_THREADPOOL_H
#define EX5_THREADPOOL_H

#include "Task.h"
#include <queue>
#include <pthread.h>
using namespace std;

class ThreadPool {
private:
  queue<Task *> tasksQueue;
  pthread_t* threads;
  void executeTasks();
  bool stopped;
  pthread_mutex_t lock;
  static void *execute(void *arg);

public:
  explicit ThreadPool(int threadsNum);
  void addTask(Task *task);
  void terminate();
  virtual ~ThreadPool();
};


#endif //EX5_THREADPOOL_H
