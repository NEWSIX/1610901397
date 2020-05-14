#include <Arduino_FreeRTOS.h> 

/*---------------------DEFINE---------------------*/

void taskT1( void *pvParameters );
void taskT2( void *pvParameters );
void setup() {
  Serial.begin(9600);
  xTaskCreate(
    taskT1
    ,  "task1"   
    ,  128  
    ,  NULL
    ,  3  
    ,  NULL );
  xTaskCreate(
    taskT2
    ,  "task2"
    ,  128  
    ,  NULL
    ,  2  
    ,  NULL );
vTaskStartScheduler();
}
void loop()
{
}
/*---------------------RTOS---------------------*/
void taskT1(void *pvParameters)  {
  (void) pvParameters;
  for (;;)
    {

    }
}
void taskT2(void *pvParameters)  {
  (void) pvParameters;
  for (;;)
    {

    }
}
/*---------------------OTHER FUNCTION---------------------*/