#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <Arduino.h>

typedef void (*TaskCallback)();

class Task 
{
  public:
    Task(TaskCallback cb = nullptr, unsigned long interval = 1000, bool paused = true, int priority = 0);
    void resume();
    void pause();
    bool isPaused() const;
    
    bool isReady(unsigned long now, bool useMicros = false);
    void run(unsigned long now);
    void setInterval(unsigned long ms);
    void setPriority(int p);
    int getPriority() const;
    void reset();

  private:
    TaskCallback callback;
    unsigned long interval;
    unsigned long lastRun;
    bool paused;
    int priority;
};

class TaskScheduler
{
  public:
    TaskScheduler(bool useMicros = false);

    bool addTask(Task* task);
    bool removeTask(Task* task);
    void run();
    void clearAll();

  private:
    static const int MAX_TASKS = 20;
    Task* tasks[MAX_TASKS];
    int taskCount;
    bool useMicros;

    unsigned long now();
    void sortTasks();
};

#endif
