#include <gmock/gmock.h>
#include <functional>

#include <signal.h>


/*
int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset);
*/
static std::function<int(int how, const sigset_t *set, sigset_t *oldset)> _pthread_sigmask;

class LibpthreadMocker {
public:
    LibpthreadMocker() {
        _pthread_sigmask 
    		= [this](int how, const sigset_t *set, sigset_t *oldset)
		{
			return pthread_sigmask(how, set, oldset);
		};
    }

    ~LibpthreadMocker() {
        _pthread_sigmask = {};

    }

    MOCK_CONST_METHOD3(pthread_sigmask, int(int how, const sigset_t *set, sigset_t *oldset));
};

class LibpthreadMockBase {
protected:
   LibpthreadMocker lpm;
};

#ifdef __cplusplus
extern "C" {
#endif

int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset)
{
    return _pthread_sigmask(how, set, oldset);
}
#ifdef __cplusplus
}
#endif
