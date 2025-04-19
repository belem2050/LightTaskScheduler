# TaskScheduler

A lightweight cooperative task scheduler for Arduino. Schedule multiple functions to run periodically without blocking your `loop()`. Simple, safe, and flexible.

## Features

- Run multiple periodic tasks
- Supports `millis()` or `micros()` timing
- Pause / Resume tasks at runtime
- Task priorities — higher-priority tasks run first
- Clean and minimal memory usage (no dynamic allocation)

## Installation

1. Clone or download this repository as a `.zip`
2. In the Arduino IDE: **Sketch → Include Library → Add .ZIP Library...**
3. Select the downloaded `.zip`

## 🚀 Getting Started

### Basic Blink Example

```cpp
#include <TaskScheduler.h>

TaskScheduler scheduler;

void blink()
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

Task blinkTask(blink, 1000); // run every 1000 ms

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  scheduler.addTask(&blinkTask);
}

void loop()
{
  scheduler.run();
}
