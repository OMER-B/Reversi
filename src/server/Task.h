//
// Created by h on 12/01/18.
//

#ifndef EX5_TASK_H
#define EX5_TASK_H


class Task {
private:
  void * (*func)(void *arg);
  void *arg;

public:
  Task(void * (*func)(void *arg), void* arg) :
          func(func), arg(arg) {}
  void execute() {
    func(arg);
  }
  virtual ~Task() {}

};


#endif //EX5_TASK_H
