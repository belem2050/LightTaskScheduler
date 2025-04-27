#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <Arduino.h>

typedef void (*TaskCallback)();

/**
 * @brief A simple task class for scheduling functions.
 *
 * Task objects represent scheduled tasks running at given intervals.
 */
class Task 
{
  public:
    /// @brief 
    /// @param cb Callback function to execute
    /// @param interval Intervall in Milliseconds/MicroSeconds
    /// @param paused Whether the task is iniatially paused or not
    /// @param priority Task priority 0 is the lowest priority
    Task(TaskCallback cb = nullptr, unsigned long interval = 1000, bool paused = false, int priority = 0);

    /// @brief Resume a paused task
    void resume();

    /// @brief Pause a Task
    void pause();

    /// @brief Get whether a task is paused or not
    /// @return 
    bool isPaused() const;
    
    /// @brief  Check if task is ready to be run.
    /// @param now time in Milli/Micro Seconds
    /// @return True if ready
    bool isReady(unsigned long now);

    /// @brief Run a task
    /// @param now the current time
    void run(unsigned long now);

    /// @brief Set intervall 
    /// @param ms Intervall in either Milli or MicroSeconds
    void setInterval(unsigned long ms);

    /// @brief Set priority
    /// @param p Priority. 0 is the lowest
    void setPriority(int p);

    /// @brief Get the priority
    /// @return Priority
    int getPriority() const;

    /// @brief Reset a task 
    /// @param current current time 
    void reset(unsigned long current);

  private:
    TaskCallback callback;
    unsigned long interval;
    unsigned long lastRun;
    bool paused;
    int priority;
};

/**
 * @brief A simple task class for scheduling functions.
 *
 * Task objects represent scheduled tasks running at given intervals.
 */
class TaskScheduler
{
  public:

    /// @brief Task scheduler object
    /// @param useMicros 
    TaskScheduler(bool useMicros = false);

    /// @brief Add Task
    /// @param task Task
    /// @return True if sucess
    bool addTask(Task* task);

    /// @brief Remove Task
    /// @param task Task
    /// @return True if success
    bool removeTask(Task* task);

    /// @brief Run Task scheduler object
    void run();

    /// @brief Clear the tasks list
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
