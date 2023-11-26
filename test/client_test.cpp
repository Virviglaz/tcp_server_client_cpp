#include "tcp_server.hpp"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s ip:port\n", argv[0]);
		return EINVAL;
	}

	char s[100];
	strncpy(s, argv[1], sizeof(s));
	char *p = strchr(s, ':');
	if (!p) {
		printf("Format error!\n");
		return EINVAL;
	}
	*p = 0;
	char ip[16];
	strncpy(ip, s, sizeof(ip));
	uint16_t port = atoi(++p);


	printf("Sending data to %s:%u\n", ip, port);

	TCP::Client client(ip, port);

	int res = client.Connect();
	if (res)
		return res;

	for (int i = 0; i != 10; i++) {
		if (client.Send("Hello world", 12))
				break;
		char buf[16];
		if (client.Read(buf, 12) == 12)
			printf("%s\n", buf);
	}

	return 0;
}
