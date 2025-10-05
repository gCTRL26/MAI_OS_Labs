#include <cstddef>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>

namespace os {
    int Pipe(int pipefd[2]);
    pid_t Fork();
    int Dup2(int fd1, int fd2);
    int Close(int fd);
    int Execl(const char* proc_path, const char* proc_name);
    pid_t Wait(pid_t pid);
    ssize_t Write(int fd, char* buf, size_t cnt);
    void Perror(const char* s);
}