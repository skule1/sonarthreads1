const int pwmFreq = 40000;  // PWM frequency
#if CONFIG_FREERTOS_UNICORE
#define TASK_RUNNING_CORE 0
#else
#define TASK_RUNNING_CORE 1
#endif

#define ANALOG_INPUT_PIN A0

#ifndef LED_BUILTIN
#define LED_BUILTIN 13  // Specify the on which is your LED
#endif


/* Porter:
 18, 19, 21, 22, 23, 25, 26, 27,};
// 21, 22, 23, 25, 26, 27,18,19};
*/
// Please read file README.md in the folder containing this example.


void TaskBlink1(void *pvParameters) {  // This is a task.
  uint32_t blink_delay = *((uint32_t *)pvParameters);

  /*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  If you want to know what pin the on-board LED is connected to on your ESP32 model, check
  the Technical Specs of your board.
*/

  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println('TaskBlink start');
  for (;;) {                          // A Task shall never return or exit.
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    // arduino-esp32 has FreeRTOS configured to have a tick-rate of 1000Hz and portTICK_PERIOD_MS
    // refers to how many milliseconds the period between each ticks is, ie. 1ms.
    delay(blink_delay);
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
    delay(blink_delay);
    Serial.println("TaskBlink");
  }
}


// 40kHz parameters
//const int pin = 18;
const uint16_t frequency = 40000;          // 40kHz
const uint16_t burstDurationMicros = 500;  // 0.5 ms burst (example)
unsigned long periodMicros = 1000000UL / frequency;
unsigned long halfPeriod = periodMicros / 2;
unsigned long elapsed = 0;
;

// Function to generate a 40kHz tone burst
void TaskBlink(uint8_t pin, uint16_t frequency, uint16_t durationMicros) {

  unsigned long elapsed = 0;
  const uint16_t duty = 50;
  while (elapsed < durationMicros) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(halfPeriod);
    // delayMicroseconds(periodMicros*duty/100);
    digitalWrite(pin, LOW);
    // delayMicroseconds(periodMicros*(100-duty)/100);
    delayMicroseconds(halfPeriod);
    elapsed += periodMicros;
  }
}






#if CONFIG_FREERTOS_UNICORE
#define TASK_RUNNING_CORE 0
#else
#define TASK_RUNNING_CORE 1
#endif

#define ANALOG_INPUT_PIN A0

#ifndef LED_BUILTIN
#define LED_BUILTIN 13  // Specify the on which is your LED
#endif

struct TaskParams1 {
  int port;
  // int frequence;
  // int burst;
};


struct TaskParams {
  int port;
  int offset;
  int fase;
  int apml;
  const char *navn;
};

static TaskParams params = { 42, 500, 50, 60, "Navn" };

TaskHandle_t TaskHandle1 = NULL;
TaskHandle_t TaskHandle2 = NULL;
TaskHandle_t TaskHandle3 = NULL;
TaskHandle_t TaskHandle4 = NULL;
TaskHandle_t TaskHandle5 = NULL;
TaskHandle_t TaskHandle6 = NULL;
TaskHandle_t TaskHandle7 = NULL;
TaskHandle_t TaskHandle8 = NULL;

int offset = 100;
TaskHandle_t bursthandle1 = nullptr;
TaskHandle_t bursthandle2 = nullptr;
TaskHandle_t bursthandle3 = nullptr;


// Define two tasks for Blink & AnalogRead.
//void TaskBlink(void *pvParameters);

TaskHandle_t analog_read_task_handle;  // You can (don't have to) use this to be able to manipulate a task from somewhere else.
TaskHandle_t taskhandle;               // You can (don't have to) use this to be able to manipulate a task from somewhere else.

// The setup function runs once when you press reset or power on the board.
void setup() {

  //pinMode(18, OUTPUT);
  //  pinMode(16, OUTPUT);
  //  pinMode(12, OUTPUT);
  //  pinMode(23, OUTPUT);
  //  pinMode(19, OUTPUT);
  //  pinMode(25, OUTPUT);
  //  pinMode(26, OUTPUT);
  //  pinMode(27, OUTPUT);
  // pinMode(21, OUTPUT);
  // pinMode(17, OUTPUT);
  // pinMode(22, OUTPUT);
  // pinMode(35, OUTPUT);
  // pinMode(33, OUTPUT);
  // pinMode(34, OUTPUT);





  // Initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  // pinMode(18, OUTPUT);
  Serial.print("halfPeriod  ");
  Serial.println(halfPeriod);
  // Set up two tasks to run independently.
  //uint32_t blink_delay = 1000;  // Delay between changing state on LED pin

  //18, 19, 21, 22, 23, 25, 26, 27,};

  static TaskParams params1 = { 18, offset, 0, 50, "task1" };
  xTaskCreate(Task, "Task1", 2048, &params1, 2, &TaskHandle1);

  static TaskParams params2 = { 19, offset, 10, 50, "task2" };
  xTaskCreate(Task, "Task2", 2048, &params2, 2, &TaskHandle2);

  static TaskParams params3 = { 21, offset, -10, 50, "task3" };
  xTaskCreate(Task, "Task3", 2048, &params3, 2, &TaskHandle3);

  static TaskParams params4 = { 22, offset, 0, 50, "task4" };
  xTaskCreate(Task, "Task4", 2048, &params4, 2, &TaskHandle4);

  // static TaskParams params5 = { 23, offset, 0, 50, "task5" };
  // xTaskCreate(Task, "Task5", 2048, &params5, 2, &TaskHandle5);

  // static TaskParams params6 = { 25, offset, 0, 50, "task6" };
  // xTaskCreate(Task, "Task6", 2048, &params6, 2, &TaskHandle6);

  // static TaskParams params7 = { 26, offset, 0, 50, "task7" };
  // xTaskCreate(Task, "Task7", 2048, &params7, 2, &TaskHandle7);

  // static TaskParams params8 = { 27, offset, 0, 50, "task8" };
  // xTaskCreate(Task, "Task8", 2048, &params8, 2, &TaskHandle8);

  // static TaskParams params1 = { 18, offset, 0, 50, "task1" };
  // xTaskCreate(childTask, "Task1", 2048, &params1, 2, &TaskHandle1);

  // static TaskParams params2 = { 19, offset, 0, 50, "task2" };
  // xTaskCreate(childTask, "Task2", 2048, &params2, 2, &TaskHandle2);



  // static TaskParams param1 = { 18, offset, 0, 50, "task1" };
  // xTaskCreate(childTask, "childTask", 2048, &param1, 2, &bursthandle1);

  // static TaskParams param2 = { 19, offset, 0, 50, "task2" };
  // xTaskCreate(childTask, "childTask", 2048, &param2, 2, &bursthandle2);


  // Serial.println("Basic Multi Threading Arduino Example\n");
  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.



  //   xTaskNotifyGive(TaskHandle1);  // Trigger Task B
  // xTaskNotifyGive(TaskHandle2);  // Trigger Task B
  // xTaskNotifyGive(TaskHandle3);  // Trigger Task B
  // xTaskNotifyGive(TaskHandle4);  // Trigger Task B
  // xTaskNotifyGive(TaskHandle5);  // Trigger Task B
  // xTaskNotifyGive(TaskHandle6);  // Trigger Task B
  // xTaskNotifyGive(TaskHandle7);  // Trigger Task B
  // xTaskNotifyGive(TaskHandle8);  // Trigger Task B
  delay(50);

  //   xTaskCreate(
  //   TaskBlink2, "Task Blink"  // A name just for humans
  //   ,
  //   2048  // The stack size can be checked by calling `uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);`
  //   ,
  //  NULL  // Task parameter which can modify the task behavior. This must be passed as pointer to void.
  //   ,
  //   2  // Priority
  //   ,
  //  NULL  // Task handle is not used here - simply pass NULL
  // );
}

void loop() {
  //   digitalWrite(18, HIGH);
  // delay(50);
  // digitalWrite(18, LOW);
  // delay(50);
  //     digitalWrite(18, HIGH);  // turn the LED on (HIGH is the voltage level)
  //   vTaskDelay(10);
  //   digitalWrite(18, LOW);  // turn the LED off by making the voltage LOW
  //  vTaskDelay(10);
  // xTaskNotifyGive(bursthandle1);  // Trigger Task B
  // xTaskNotifyGive(bursthandle2);  // Trigger Task B
  xTaskNotifyGive(TaskHandle1);  // Trigger Task B
  xTaskNotifyGive(TaskHandle2);  // Trigger Task B
  xTaskNotifyGive(TaskHandle3);  // Trigger Task B
  xTaskNotifyGive(TaskHandle4);  // Trigger Task B
                                 // xTaskNotifyGive(TaskHandle5);  // Trigger Task B
                                 // xTaskNotifyGive(TaskHandle6);  // Trigger Task B
                                 // xTaskNotifyGive(TaskHandle7);  // Trigger Task B
                                 // xTaskNotifyGive(TaskHandle8);  // Trigger Task B
  delay(300);
  //   digitalWrite(pin, HIGH);
  //   // delayMicroseconds(halfPeriod);
  //  delay(100);
  //   digitalWrite(pin, LOW);
  //   delayMicroseconds(halfPeriod);

  // generateToneBurst(18, frequency, burstDurationMicros);
  //   vTaskDelay(pdMS_TO_TICKS(100));  // Wait 100ms before next burst
  // // if (analog_read_task_handle != NULL) {  // Make sure that the task actually exists
  //   delay(500);
  //   vTaskDelete(analog_read_task_handle);  // Delete task
  //   analog_read_task_handle = NULL;        // prevent calling vTaskDelete on non-existing task
  // }
}



//   TaskParams *data = (TaskParams *)pvParameters;  //
// int port=data->port;
//  TaskParams1* params20 = new  TaskParams1{ data->port};
//   Serial.println(data->port);
//   if (data->port == 18) {
//     xTaskCreatePinnedToCore(
//       childTask,     // Task function
//       "ChildTask",   // Name
//       2048,          // Stack size
//       (void*)params20,     // Params
//       1,             // Priority
//       bursthandle1,  // Handle
//       0              // Core 0
//     );
//   }

// Child task
void Task(void *pvParameters) {

  TaskParams *data = (TaskParams *)pvParameters;  //
  Serial.print(data->navn);
  Serial.print(" : ");
  Serial.print(data->port);
  Serial.print(" : ");
    Serial.print("  data->fase");
    Serial.print("  :  ");
    Serial.print(data->fase);
    Serial.print("  data->offset + data->fase");
    Serial.print("  :  ");
    Serial.print(data->offset + data->fase);
    // Serial.print("  halfPeriod");
    // Serial.print("  :  ");
    // Serial.print(halfPeriod);
    Serial.print(" 100-(data->offset + data->fase)");
    Serial.print("  :  ");
    Serial.println(100 - (data->offset + data->fase));

  //  Serial.println(data1->burst);

  const uint16_t duty = 50;
  pinMode(data->port, OUTPUT);
  digitalWrite(data->port, LOW);
  while (true) {

    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    // Serial.print("childTask");
    // Serial.print("  :  ");
    // Serial.print(data->port);
    // Serial.print("  data->fase");
    // Serial.print("  :  ");
    // Serial.print(data->fase);
    // Serial.print("  data->offset + data->fase");
    // Serial.print("  :  ");
    // Serial.print(data->offset + data->fase);
    // // Serial.print("  halfPeriod");
    // // Serial.print("  :  ");
    // // Serial.print(halfPeriod);
    // Serial.print(" 100-(data->offset + data->fase)");
    // Serial.print("  :  ");
    // Serial.println(100 - (data->offset + data->fase));
       digitalWrite(data->port, HIGH);
    delay(1);
     digitalWrite(data->port, LOW);
   //if (data->port!=18) 
   vTaskDelay(data->offset + data->fase);

    analogWrite(data->port, 128);
  //  digitalWrite(data->port, HIGH);
    delay(5);
    analogWrite(data->port, 0);
    // digitalWrite(data->port, LOW);
   //   if (data->port!=18)  vTaskDelay(100 - (data->offset + data->fase));
    // delay(1);
    // unsigned long elapsed = 0;

    // while (elapsed < burstDurationMicros) {
    //   digitalWrite(data->port, HIGH);
    //   delayMicroseconds(halfPeriod);
    //   // delayMicroseconds(periodMicros*duty/100);
    //   digitalWrite(data->port, LOW);
    //   // delayMicroseconds(periodMicros*(100-duty)/100);
    //   delayMicroseconds(halfPeriod);
    //   elapsed += periodMicros;
    // }
    // vTaskDelay(100-(data->offset + data->fase));
  }
}



// void Task1(void *pvParameters) {
//   TaskParams *data = (TaskParams *)pvParameters;  //
// int port=data->port;
//  TaskParams1* params20 = new  TaskParams1{ data->port};
//   Serial.println(data->port);
//   if (data->port == 18) {
//     xTaskCreatePinnedToCore(
//       childTask,     // Task function
//       "ChildTask",   // Name
//       2048,          // Stack size
//       (void*)params20,     // Params
//       1,             // Priority
//       bursthandle1,  // Handle
//       0              // Core 0
//     );
//   }
//   if (data->port == 19) {
//     xTaskCreatePinnedToCore(
//       childTask,     // Task function
//       "ChildTask",   // Name
//       2048,          // Stack size
//       (void*)params20,     // Params
//       1,             // Priority
//       bursthandle2,  // Handle
//       0              // Core 0
//     );
//   };



//  uint32_t blink_delay = 1000;                    // Delay between changing state on LED pin
// TaskHandle_t TaskHandle_puls = NULL;
// xTaskCreate(
//   TaskBlink2, "Task Blink"  // A name just for humans
//   ,
//   2048  // The stack size can be checked by calling `uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);`
//   ,
//  NULL  // Task parameter which can modify the task behavior. This must be passed as pointer to void.
//   ,
//   2  // Priority
//   ,
//  NULL  // Task handle is not used here - simply pass NULL
// );
// Serial.println("task start...");
// Serial.println(data->port);
// Serial.println(data->offset);
// Serial.println(data->fase);
// Serial.println(data->apml);
// Serial.println(data->navn);
// pinMode(data->port, OUTPUT);
// digitalWrite(data->port, LOW);
// for (;;) {
//ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
// digitalWrite(data->port, HIGH);  // turn the LED on (HIGH is the voltage level)
// vTaskDelay(2);
// digitalWrite(data->port, LOW);  // turn the LED off by making the voltage LOW
// vTaskDelay(1);
//vTaskDelay(80-(data->offset + data->fase));
// Serial.print("task start...");
// Serial.print(data->port);
// Serial.print(" : ");
// Serial.print(data->fase);
// Serial.print(" : ");
// Serial.print(data->apml);
// Serial.print(" : ");
//   Serial.print(data->navn);
//   Serial.print(" : ");
//   Serial.print(data->offset + data->fase);
//  Serial.print(" : ");
//  Serial.println(80-(data->offset + data->fase));
// pinMode(data->port, OUTPUT);
// digitalWrite(data->port, LOW);
// for (;;) {
//   vTaskDelay(data->offset + data->fase);

//   static TaskParams1 params20 = { data->port };
//childTask(&params20);
//   childTask( 18, frequency,burstDurationMicros);
//  static TaskParams1 params20 = {data->port, frequency,burstDurationMicros };
//   childTask(void *params20);
//xTaskNotifyGive(TaskHandle_puls);  // Trigger Task B



//  unsigned long elapsed = 0;
//   const uint16_t duty = 50;
//   while (elapsed < burstDurationMicros) {
//    digitalWrite(data->port, HIGH);
//     delayMicroseconds(halfPeriod);
//     // delayMicroseconds(periodMicros*duty/100);
//    digitalWrite(data->port, LOW);
//     // delayMicroseconds(periodMicros*(100-duty)/100);
//     delayMicroseconds(halfPeriod);
//     elapsed += periodMicros;
//   }








// generateToneBurst(data->port, frequency, burstDurationMicros);

// vTaskDelay(20);

// vTaskDelay(pdMS_TO_TICKS(100));  // Wait 100ms before next burst
//       digitalWrite(data->port, HIGH);  // turn the LED on (HIGH is the voltage level)
//       vTaskDelay(10);
//       digitalWrite(data->port, LOW);  // turn the LED off by making the voltage LOW
//       vTaskDelay(10);

//       vTaskDelay(80 - (data->offset + data->fase));
//     }
//   }
// }
