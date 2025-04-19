#include <TaskScheduler.h>

TaskScheduler scheduler;

// Task: blink the built-in LED every 500 ms
void blinkLED() 
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

// Task: print a message every second
void printMessage()
{
  Serial.println("Hello from TaskScheduler!");
}

Task blinkTask(blinkLED, 500);
Task printTask(printMessage, 1000);

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  delay(1000);

  scheduler.addTask(&blinkTask);
  scheduler.addTask(&printTask);
}

void loop() 
{
  scheduler.run();

  // Pause LED blinking after 5 seconds
  if (millis() > 5000 && !blinkTask.isPaused()) 
  {
    blinkTask.pause();
    Serial.println("LED blinking paused.");
  }

  // Resume blinking after 10 seconds
  if (millis() > 10000 && blinkTask.isPaused())
  {
    blinkTask.resume();
    Serial.println("LED blinking resumed.");
  }
}
