#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
int main() {
char buf[100];
struct sockaddr_in server, client;
int s_check, c_check;
s_check = socket(AF_INET, SOCK_STREAM, 0);
server.sin_family = AF_INET;
server.sin_addr.s_addr = inet_addr("127.0.0.1");
server.sin_port = htons(9995);
bind(s_check, (struct sockaddr*)&server, sizeof(server));
listen(s_check, 1);
int size = sizeof(client);
c_check = accept(s_check, (struct sockaddr*)&client, &size);
do
{
memset(buf,'\0',100);
printf("Enter the string:");
fflush(stdin);
scanf("%s",buf);
send(c_check, buf, 100, 0);
printf("\nClient IP address is: %s\n", inet_ntoa(client.sin_addr));
recv(c_check, buf, 100, 0);
printf("\nRecieved data is : %s\n", buf);
}while(strcmp(buf,"bye")!=0);
close(c_check);
close(s_check);
return(0);
}
