#include <gmock/gmock.h>
#include <functional>

#include <unistd.h>
#include <sys/socket.h>

/*
ssize_t write(int fd, const void *buf, size_t count);
int close(int fd);
*/
static std::function<ssize_t(int fd, const void *buf, size_t count)> _write;
static std::function<int(int)> _close;

/*
int accept4(int sockfd, struct sockaddr *addr,
			socklen_t *addrlen, int flags);
*/
static std::function<int(int sockfd, struct sockaddr *addr,
			socklen_t *addrlen, int flags)> _accept4;


class SyscallIOMocker {
public:
	SyscallIOMocker() {
		_write = [this](int fd, const void *buf, size_t count) {
			return write(fd, buf, count);
		};
		_close = [this](int fd){
			return close(fd);
		};
		_accept4 
			= [this](int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flags) {
			return accept4(sockfd, addr, addrlen, flags);
		};
	}

	~SyscallIOMocker() {
		_write = {};
		_close = {};
		_accept4 = {};
	}

	MOCK_CONST_METHOD3(write, ssize_t(int fd, const void *buf, size_t count));
	MOCK_CONST_METHOD1(close, int(int));
	MOCK_CONST_METHOD4(accept4, int(int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flags));
};

class SyscallIOMockBase {
protected:
	SyscallIOMocker sysiom;
};

#ifdef __cplusplus
extern "C" {
#endif

ssize_t write(int fd, const void *buf, size_t count)
{
    return _write(fd, buf, count);
}

int close(int fd)
{
    return _close(fd);
}

int accept4(int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flags)
{
	return _accept4(sockfd, addr, addrlen, flags);
}
#ifdef __cplusplus
}
#endif
