#include "../include/sys_calls.hpp"
#include <sched.h>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

namespace sys_call {
    SysCall::SysCall(): pipe_rd_(-1), pipe_wr_(-1), child_pid_(-1) {}

    void SysCall::CreatePipe() {
        int pipe_fd[2];
        if (pipe(pipe_fd) == -1) {
            perror("pipe");
        }
        pipe_rd_ = pipe_fd[0];
        pipe_wr_ = pipe_fd[1];
    }

    void SysCall::CreateChild() {
        child_pid_ = fork();
        if (child_pid_ == -1) {
            perror("fork");
        }
    }

    void SysCall::SetChildProc(const std::string& filename) {
        close(pipe_rd_);
        dup2(pipe_wr_, STDOUT_FILENO);
        close(pipe_wr_);

        int file_fd = open(filename.c_str(), O_RDONLY);
        if (file_fd == -1) {
            perror("open");
        }
        dup2(file_fd, STDIN_FILENO);
        close(file_fd);

        execl("./child", "./child", nullptr);
        perror("exec");
    }

    void SysCall::SetParentProc() {
        close(pipe_wr_);
        
        char buffer[256];
        ssize_t cnt;
        while ((cnt = read(pipe_rd_, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, cnt);
        }
        close(pipe_rd_);
        waitpid(child_pid_, nullptr, 0);
    }

    void SysCall::Clean() {
        if (pipe_rd_ != -1) {
            close(pipe_rd_);
            pipe_rd_ = -1;
        }
        if (pipe_wr_ != -1) {
            close(pipe_wr_);
            pipe_wr_ = -1;
        }
    }

    void SysCall::StartProcesses(const std::string& filename) {
        CreatePipe();
        CreateChild();
        if (child_pid_ == 0) {
            SetChildProc(filename);
        } else {
            SetParentProc();
        }
    }

    SysCall::~SysCall() {
        Clean();
    }

}