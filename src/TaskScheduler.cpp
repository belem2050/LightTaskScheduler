#include "TaskScheduler.h"

Task::Task(TaskCallback cb, unsigned long interval, bool paused, int priority)
    : callback(cb), interval(interval), lastRun(0), paused(paused), priority(priority) {}

void Task::pause() 
{ 
    paused = true; 
}
void Task::resume() 
{ 
    paused = false; 
}

bool Task::isPaused() const 
{ 
    return paused;
}

bool Task::isReady(unsigned long current)
{
    return !paused && (current - lastRun >= interval);
}

void Task::run(unsigned long current)
{
    if (callback) 
    {
        callback();
        lastRun = current;
    }
}

void Task::setInterval(unsigned long ms) 
{
  interval = ms;
}

void Task::setPriority(int p)
{
  priority = p;
}

int Task::getPriority() const 
{
  return priority;
}

void Task::reset() 
{
  lastRun = useMicros ? micros() : millis();
}

TaskScheduler::TaskScheduler(bool useMicros) : taskCount(0), useMicros(useMicros) {}

unsigned long TaskScheduler::now()
{
  return useMicros ? micros() : millis();
}

bool TaskScheduler::addTask(Task* task)
{
  if (taskCount < MAX_TASKS) 
  {
    tasks[taskCount++] = task;
    sortTasks();
    return true;
  }
  return false;
}

bool TaskScheduler::removeTask(Task* task) 
{
  for (int i = 0; i < taskCount; ++i)
  {
    if (tasks[i] == task)
    {
      for (int j = i; j < taskCount - 1; ++j) 
      {
        tasks[j] = tasks[j + 1];
      }
      --taskCount;
      return true;
    }
  }
  return false;
}

void TaskScheduler::clearAll() 
{
  taskCount = 0;
}

void TaskScheduler::sortTasks()
{
  for (int i = 0; i < taskCount - 1; ++i) 
  {
    for (int j = i + 1; j < taskCount; ++j) 
    {
      if (tasks[j]->getPriority() > tasks[i]->getPriority()) 
      {
        Task* temp = tasks[i];
        tasks[i] = tasks[j];
        tasks[j] = temp;
      }
    }
  }
}

void TaskScheduler::run()
{
  unsigned long current = now();
  for (int i = 0; i < taskCount; ++i) 
  {
    if (tasks[i]->isReady(current))
    {
      tasks[i]->run(current);
    }
  }
}
