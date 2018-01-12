//
// Created by h on 12/01/18.
//

#include "ThreadPool.h"
#include <unistd.h>


ThreadPool::ThreadPool(int threadsNum) :
        stopped(false) {
  threads = new pthread_t[threadsNum];
  for (int i = 0; i < threadsNum; i++) {
    pthread_create(threads + i, NULL, execute,
                   this);
  }
  pthread_mutex_init(&lock, NULL);
}
void* ThreadPool::execute(void *arg) {
  ThreadPool *pool = (ThreadPool *)arg;
  pool->executeTasks();
}
void ThreadPool::addTask(Task *task) {
  tasksQueue.push(task);
}

void ThreadPool::executeTasks() {
  while (!stopped) {
    pthread_mutex_lock(&lock);
    if (!tasksQueue.empty()) {
      Task* task = tasksQueue.front();
      tasksQueue.pop();
      pthread_mutex_unlock(&lock);
      task->execute();
    }
    else {
      pthread_mutex_unlock(&lock);
      sleep(1);
    }
  }
}
void ThreadPool::terminate() {
  pthread_mutex_destroy(&lock);
  stopped = true;
}
ThreadPool::~ThreadPool() {
  delete[] threads;
}