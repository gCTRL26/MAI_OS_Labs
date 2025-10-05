#include "../include/os.hpp"
#include <cstdio>
#include <sys/wait.h>
#include <unistd.h>

namespace os {
    int Pipe(int pipefd[2]) {return pipe(pipefd);}

    pid_t Fork() {return fork();}

    int Dup2(int fd1, int fd2) {return dup2(fd1, fd2);}

    int Close(int fd) {return close(fd);}

    int Execl(const char *proc_path, const char *proc_name) {
        return execl(proc_path, proc_name, nullptr);
    }

    pid_t Wait(pid_t pid) {
        return waitpid(pid, nullptr, 0);
    }

    ssize_t Write(int fd, char* buf, size_t cnt) {
        return write(fd, buf, cnt);
    }

    void Perror(const char* s) {perror(s);}
}