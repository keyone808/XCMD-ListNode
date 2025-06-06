#include "xcmd.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t xcmdTaskHandle;
TaskHandle_t mainfunc_taskHandle;
int arry[5] = {1, 2, 3, 4, 5};


//list--------------
typedef struct ListNode {
  int number;
  struct ListNode* next;
} ListNode;

//----------------
ListNode* head = (ListNode*)malloc(sizeof(ListNode));

//2025-5-12
//xmcd_test
//tym
///-------------------------------transplant------------------
int param_check(int expected, int argc, char* argv[]) {
  if (argc <= expected) {
    printf("param error!\r\n");
    return 0;
  }
  return 1;
}

int cmd_get_char(uint8_t* ch) {
  if (Serial.available()) {
    *ch = Serial.read();
    return 1;
  } else {
    return 0;
  }
}

int cmd_put_char(uint8_t ch) {
  Serial.write(ch);
  return 1;
}


//--------------------------------------------------------------
///DIY_cmd
static int cmd_echo(int argc, char* argv[]) {
  if (param_check(1, argc, argv)) {//check for input parameter
    printf("%s\r\n", argv[1]);
  }
  return 0;
}

static int cmd_show(int argc, char* argv[]) {
  if (param_check(0, argc, argv)) {
    UBaseType_t stackRemaining_1 = uxTaskGetStackHighWaterMark(xcmdTaskHandle);
    UBaseType_t stackRemaining_2 = uxTaskGetStackHighWaterMark(mainfunc_taskHandle);
    Serial.print("xcmdTask stack remaining: ");
    Serial.println(stackRemaining_1);
    Serial.print("mainfunc_task stack remaining: ");
    Serial.println(stackRemaining_2);
  }
  return 0;
}
//traverse all list
static int cmd_show_list(int argc, char* argv[]) {
  if (param_check(0, argc, argv)) {
    for (ListNode* p = head; p != NULL; p = p->next) {
      Serial.printf("%d\n", p->number);
    }
  }
  return 0;
}


static xcmd_t cmds[] = {
  { "echo", cmd_echo, "print anything", NULL },
  {"show", cmd_show, "show each task stack reamining ", NULL },
  {"show_list", cmd_show_list, "show all list ", NULL },
};

void test_cmd_init(void) {
  xcmd_cmd_register(cmds, sizeof(cmds) / sizeof(xcmd_t));
}

//--------------------------------------------------------------
//create a list to test
//int arry[5] = {1, 2, 3, 4, 5};
//ListNode* head = (ListNode*)malloc(sizeof(ListNode));
ListNode* create_list(void) {
  //List_head
  //ListNode* head = (ListNode*)malloc(sizeof(ListNode));
  head->number = arry[0];
  head->next = NULL;
  ListNode* cur = head;
  for (int i = 1; i < 5; i++) {
    cur->next = (ListNode*)malloc(sizeof(ListNode));
    cur = cur->next;
    cur->number = arry[i];
    cur->next = NULL;
  }
  return head;
}


//-------------------------------------------------------------
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  xcmd_init(cmd_get_char, cmd_put_char);
  test_cmd_init();
  xTaskCreatePinnedToCore(xcmdTask, "xcmdTask", 4096, NULL, 1, &xcmdTaskHandle, 0);
  // 创建传感器任务，分配给核心 1
  xTaskCreatePinnedToCore(mainfunc_task, "mainfunc_task", 2048, NULL, 1, &mainfunc_taskHandle, 1);
}


// /xcmd任务
void xcmdTask(void* pvParameters) {

  while (1) {
    xcmd_task();
    vTaskDelay(pdMS_TO_TICKS(100));  // 适当的间隔避免占满 CPU
  }
}


void mainfunc_task(void* pvParameters) {
  while (1) {
    create_list();
    //主程序
    vTaskDelay(pdMS_TO_TICKS(1000));  // 适当的间隔避免占满 CPU
  }
}



void loop() {
  // put your main code here, to run repeatedly:
  //xcmd_task();
}
