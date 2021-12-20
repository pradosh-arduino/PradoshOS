#include "../BasicRenderer.h"
#include "../scheduling/pit/pit.h"

class Syscalls{
    public:
    void Debug(const char* str);
    void Done(const char* str);
    void Failed(const char* str);
    void Warn(const char* str);
    void LoadingAnim();
    void Time(const char* msg);
};
