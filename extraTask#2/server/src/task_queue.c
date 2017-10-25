#include "task_queue.h"
#include <sys/queue.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>

TAILQ_HEAD(tailhead, entry) queue_head;
struct tailhead *headp;
struct entry{
	TAILQ_ENTRY(entry) entries;
	void* function; // Функция (задание), применяемая к списку от from до to
	size_t from;
	size_t to;
};
static void walking_deamon();
pthread_mutex_t mutex; // Позволяет одновременно выполняться ЛИБО add_task,
					   //  ЛИБО проходу walking_deamon'а
void add_task(void* function,size_t from,size_t to){
	pthread_mutex_lock(&mutex);
		printf("Добавляю задание %p  для (%d,%d)\n",function,from,to);
        struct entry* new_task = malloc( sizeof(struct entry) );
        new_task->from = from;
        new_task->to = to;
        new_task->function = function;
        TAILQ_INSERT_TAIL(&queue_head,new_task,entries);
	pthread_mutex_unlock(&mutex);
}

// Демон, смотрящий, можно ли выполнить это задание, и выполняющий
static void walking_deamon(){
    struct entry* i_entry;
    while(1){
        sleep(1);
        puts("Я проснулся!");

        pthread_mutex_lock(&mutex);

        for(i_entry = queue_head.tqh_first;i_entry != NULL;
			i_entry = i_entry->entries.tqe_next){
            puts("Мы внутри листа!");
			do_this_with_list(i_entry->function,i_entry->from,i_entry->to);
			struct entry *to_free = i_entry;

                        TAILQ_REMOVE(&queue_head,i_entry,entries);
			free(to_free);
		}

        pthread_mutex_unlock(&mutex);
    }
}

void start_execution_pipe(){
    if(pthread_mutex_init(&mutex,NULL) != 0)
        perror("Error with the mutex init");
    else
        puts("The mutex has just been initialized");
    TAILQ_INIT(&queue_head);
    pthread_t new_thread;
    pthread_create(&new_thread,NULL,(void*(*)(void*))walking_deamon,NULL);
}


