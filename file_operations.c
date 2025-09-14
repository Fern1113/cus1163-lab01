#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "file_operations.h"

int create_and_write_file(const char *filename, const char *content) {
    int fd;                   // file descriptor
    ssize_t bytes_written;    // number of bytes written

    printf("Creating file: %s\n", filename);
    printf("Content to write: %s\n", content);

    // Open or create the file
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    printf("File descriptor: %d\n", fd);

    // Write to the file
    bytes_written = write(fd, content, strlen(content));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return -1;
    }

    printf("Successfully wrote %zd bytes to '%s'\n", bytes_written, filename);

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        return -1;
    }

    printf("File closed successfully\n");
    return 0;
}

int read_file_contents(const char *filename) {
    int fd;                   // file descriptor
    char buffer[1024];        // buffer for reading
    ssize_t bytes_read;       // number of bytes read

    printf("Reading file: %s\n", filename);

    // Open the file for reading
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    printf("File descriptor: %d\n", fd);
    printf("\n--- Contents of '%s' ---\n", filename);

    // Read file contents in a loop
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';  // null-terminate
        printf("%s", buffer);
    }

    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return -1;
    }

    printf("\n--- End of file ---\n");

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        return -1;
    }

    printf("File closed successfully\n");
    return 0;
}