#include <string>


namespace sys_call {
    class SysCall {
      private:
        int pipe_rd_;
        int pipe_wr_;
        int child_pid_;

        void CreatePipe();
        void CreateChild();
        void SetChildProc(const std::string& filename);
        void SetParentProc();
        void Clean();
      
      public:
        SysCall();
        void StartProcesses(const std::string& filename);
        ~SysCall() = default;
    };
}