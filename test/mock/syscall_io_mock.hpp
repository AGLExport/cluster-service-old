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
int unlink(const char *pathname);
*/
static std::function<int(const char *)> _unlink;


/*
int socket(int socket_family, int socket_type, int protocol);
int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
int listen(int sockfd, int backlog);
int accept4(int sockfd, struct sockaddr *addr,
			socklen_t *addrlen, int flags);
*/
static std::function<int(int socket_family, int socket_type, int protocol)> _socket;
static std::function<int(int sockfd, const struct sockaddr *addr,socklen_t addrlen)> _bind;
static std::function<int(int sockfd, int backlog)> _listen;
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

		_unlink = [this](const char *pathname){
			return unlink(pathname);
		};

		_socket = [this](int socket_family, int socket_type, int protocol){
			return socket(socket_family, socket_type, protocol);
		};
		_bind = [this](int sockfd, const struct sockaddr *addr,socklen_t addrlen){
			return bind(sockfd, addr,addrlen);
		};
		_listen = [this](int sockfd, int backlog){
			return listen(sockfd, backlog);
		};
		_accept4 
			= [this](int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flags) {
			return accept4(sockfd, addr, addrlen, flags);
		};
	}

	~SyscallIOMocker() {
		_write = {};
		_close = {};

		_unlink = {};

		_socket = {};
		_bind = {};
		_listen = {};
		_accept4 = {};
	}

	MOCK_CONST_METHOD3(write, ssize_t(int fd, const void *buf, size_t count));
	MOCK_CONST_METHOD1(close, int(int));

	MOCK_CONST_METHOD1(unlink, int(const char *));
	
	MOCK_CONST_METHOD3(socket, int(int socket_family, int socket_type, int protocol));
	MOCK_CONST_METHOD3(bind, int(int sockfd, const struct sockaddr *addr,socklen_t addrlen));
	MOCK_CONST_METHOD2(listen, int(int sockfd, int backlog));
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

int unlink(const char *pathname)
{
	return _unlink(pathname);
}


int socket(int socket_family, int socket_type, int protocol)
{
	return _socket(socket_family, socket_type, protocol);
}

int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen)
{
	return _bind(sockfd, addr, addrlen);
}

int listen(int sockfd, int backlog)
{
	return _listen(sockfd, backlog);
}

int accept4(int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flags)
{
	return _accept4(sockfd, addr, addrlen, flags);
}

#ifdef __cplusplus
}
#endif
