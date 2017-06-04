#ifndef SOCKET_H
#define SOCKET_H


#pragma comment(lib,"ws2_32.lib") //加载了连接库文件，实现通信程序的管理
#include <WinSock2.h>
#include <string>


enum TypeSocket {BlockingSocket, NonBlockingSocket};

class Socket 
{
public:

	virtual ~Socket();
	Socket(const Socket&);
	Socket& operator=(Socket&);

	std::string ReceiveLine();
	std::string ReceiveBytes();

	void   Close();

	// The parameter of SendLine is not a const reference
	void   SendLine (std::string);

	// The parameter of SendBytes is a const reference
	void   SendBytes(const std::string&);

	void   SendBytes(const char * buf);

protected:
	friend class SocketServer;
	friend class SocketSelect;

	Socket(SOCKET s);
	Socket();


	SOCKET s_;

	int* refCounter_;

private: 
	static void Start();
	static void End();
	static int  nofSockets_;     //套接字数量
};



class SocketClient : public Socket 
{
public:
	SocketClient(const std::string& host, int port);
};



class SocketServer : public Socket 
{
public:
	SocketServer(int port, int connections, TypeSocket type=BlockingSocket);

	Socket* Accept();
};


class SocketSelect 
{
public:
	SocketSelect(Socket const * const s1, Socket const * const s2=NULL, TypeSocket type=BlockingSocket);

	bool Readable(Socket const * const s);

private:
	fd_set fds_;
}; 



#endif
