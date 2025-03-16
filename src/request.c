#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "request.h"

void handle_request(int fd, char *root_dir)
{
    char buffer[1024], method[10], path[100];
    read(fd, buffer, sizeof(buffer));

    sscanf(buffer, "%s %s", method, path);
    if (strcmp(method, "GET") != 0)
    {
        write(fd, "HTTP/1.1 405 Method Not Allowed\r\n\r\n", 35);
        return;
    }

    char full_path[200];
    snprintf(full_path, sizeof(full_path), "%s%s", root_dir, strcmp(path, "/") == 0 ? "/index.html" : path);

    int file_fd = open(full_path, O_RDONLY);
    if (file_fd < 0)
    {
        write(fd, "HTTP/1.1 404 Not Found\r\n\r\n", 26);
        return;
    }

    write(fd, "HTTP/1.1 200 OK\r\n\r\n", 19);
    char file_buffer[512];
    int bytes_read;
    while ((bytes_read = read(file_fd, file_buffer, sizeof(file_buffer))) > 0)
        write(fd, file_buffer, bytes_read);

    close(file_fd);
}
