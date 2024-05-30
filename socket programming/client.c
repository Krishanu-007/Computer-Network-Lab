#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int sd,cd;
	struct sockaddr_in sa,ca;
	char str[200];
	sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	sa.sin_family=AF_INET;
	sa.sin_port=htons(9995);
	sa.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(sd,(struct sockaddr *)&sa,sizeof(sa));
	printf("Enter your message: ");
	gets(str);
	send(sd,str,sizeof(str),0);
	close(sd); 
	return 0;
}