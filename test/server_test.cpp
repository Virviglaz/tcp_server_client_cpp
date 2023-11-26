#include "tcp_server.hpp"
#include <iostream>
#include <unistd.h>
#include <atomic>
#include <string.h>
using namespace std;

static atomic<int> cnt { 0 };
static int on_connect(const TCP::Server::Client& c)
{
	std::cout << "Connected!" << std::endl;
	std::cout << "Server IP: " << c.GetSelfIP() << std::endl;
	std::cout << "Client IP: " << c.GetClientIP() << ":" << c.GetClientPort() << std::endl;
	return 0;
}

static int on_disconnect(const TCP::Server::Client& c)
{
	std::cout << "Disconnected!" << std::endl;
	return 0;
}

static int on_receive(const TCP::Server::Client& c, void *b, ssize_t s)
{
	std::cout << "We have " << s << " bytes of data: " << cnt << std::endl;
	cnt++;
	c.Send(b, s);
	return 0;
}

static void on_error (const TCP::Server::Client& c, int err)
{
	std::cout << "Error " << err << std::endl;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s port\n", argv[0]);
		return EINVAL;
	}

	uint16_t port = atoi(argv[1]);
	printf("Receiving data at port %u\n", port);

	int res;

	TCP::Server server(port, 12, "test server", on_connect, on_disconnect, on_receive, on_error);
	res = server.Start();
	if (res) {
		std::cout << "Server start error " << res << std::endl;
		return res;
	}

	while (cnt < 10) {
		usleep(1000);
	}

	server.WaitForStop();
	std::cout << "Server stopped " << std::endl;

	return 0;
}
