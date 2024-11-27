#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    char buffer[100];
    ssize_t bytesRead, bytesWritten;

    // Open the file for reading and writing
    int fd = open("luffy.txt", O_RDWR | O_CREAT );
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    // Read from the file
    bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("Failed to read file");
        close(fd);
        return 1;
    }
    buffer[bytesRead] = '\0';  // Null-terminate the string
    printf("Read from file: %s\n", buffer);

    // Write to the file
    const char *text = "This is some new text!";
    bytesWritten = write(fd, text, strlen(text));
    if (bytesWritten == -1) {
        perror("Failed to write to file");
        close(fd);
        return 1;
    }

    // Close the file
    close(fd);
    return 0;
}

