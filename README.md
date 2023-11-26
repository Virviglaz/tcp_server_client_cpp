# TCP Server and Client implementation for C++
## Server usage:
### Callbacks
~~~cpp
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
	std::cout << "We have " << s << " bytes of data." << std::endl;
	c.Send(b, s); /* Send data back (loop) */
	return 0;
}

static void on_error (const TCP::Server::Client& c, int err)
{
	std::cout << "Error " << err << std::endl;
}
~~~
### Start server:
~~~cpp
TCP::Server server(port, 12, "test server", on_connect, on_disconnect, on_receive, on_error);
server.Start();
~~~
### Stop server:
~~~cpp
server.WaitForStop();
~~~
## Client usage:
~~~cpp
TCP::Client client(ip, port);
client.Connect();
client.Send("Hello world", 12);
~~~
## How to test:
~~~cpp
$ make test
~~~
