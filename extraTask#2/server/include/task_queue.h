#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <stddef.h>
#include "list_keeper.h"

// Добавить задание для выполнения
void add_task(void* function,size_t from,size_t to);
// Запустить демон для выполнения заданий. Вызывается лишь раз сервером
void start_execution_pipe();
#endif // TASK_QUEUE_H

