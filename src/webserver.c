#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
#include "request.h"

#define PORT 8080
#define MAX_THREADS 4
#define BUFFER_SIZE 10

char *root_dir = "www";
int request_buffer[BUFFER_SIZE];
int buffer_count = 0, buffer_in = 0, buffer_out = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER;

void *worker_thread(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        while (buffer_count == 0)
            pthread_cond_wait(&buffer_not_empty, &mutex);

        int conn_fd = request_buffer[buffer_out];
        buffer_out = (buffer_out + 1) % BUFFER_SIZE;
        buffer_count--;

        pthread_cond_signal(&buffer_not_full);
        pthread_mutex_unlock(&mutex);

        handle_request(conn_fd, root_dir);
        close(conn_fd);
    }
    return NULL;
}

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create server socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    printf("Server running on port %d...\n", PORT);

    // Create worker threads
    pthread_t threads[MAX_THREADS];
    for (int i = 0; i < MAX_THREADS; i++)
        pthread_create(&threads[i], NULL, worker_thread, NULL);

    while (1)
    {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

        pthread_mutex_lock(&mutex);
        while (buffer_count == BUFFER_SIZE)
            pthread_cond_wait(&buffer_not_full, &mutex);

        request_buffer[buffer_in] = client_fd;
        buffer_in = (buffer_in + 1) % BUFFER_SIZE;
        buffer_count++;

        pthread_cond_signal(&buffer_not_empty);
        pthread_mutex_unlock(&mutex);
    }

    return 0;
}
