#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char write_msg[] = "Hello from parent to child!";
    char read_msg[100];

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Fork to create a child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { // Child process
        close(pipefd[1]);  // Close write end of pipe
        read(pipefd[0], read_msg, sizeof(read_msg));
        printf("Child received message: %s\n", read_msg);
        close(pipefd[0]);
    } else { // Parent process
        close(pipefd[0]);  // Close read end of pipe
        write(pipefd[1], write_msg, sizeof(write_msg));
        close(pipefd[1]);
        wait(NULL);  // Wait for child process to finish
    }

    return 0;
}

