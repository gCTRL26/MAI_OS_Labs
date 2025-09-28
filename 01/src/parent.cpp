#include <iostream>
#include <sched.h>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


int main() {
    int pipe_fd[2];
    pid_t pid;
    std::string filename;

    std::cout << "Enter filename with numbers" << std::endl;
    std::cin >> filename;

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);

        int file_fd = open(filename.c_str(), O_RDONLY);
        if (file_fd == -1) {
            perror("open");
            return 1;
        }
        dup2(file_fd, STDIN_FILENO);
        close(file_fd);

        execl("./child", "./child", nullptr);
        perror("exec");
        return 1;
    } else if (pid > 0) {
        close(pipe_fd[1]);
        
        char* buffer[256];
        ssize_t cnt;
        while ((cnt = read(pipe_fd[0], buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, cnt);
        }
        close(pipe_fd[0]);
        waitpid(pid, nullptr, 0);
    }

    return 0;
}