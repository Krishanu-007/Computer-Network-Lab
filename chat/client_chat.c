#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<stdlib.h>
#include <string.h>
int main() {
struct sockaddr_in client;
int c_check;
char buf[100];
c_check = socket(AF_INET, SOCK_STREAM, 0);
client.sin_family = AF_INET;
client.sin_addr.s_addr = inet_addr("127.0.0.1");
client.sin_port = htons(9995);
connect(c_check, (struct sockaddr*)&client, sizeof(client));
do{
recv(c_check, buf, 100, 0);
printf("\n codeword recv from sender is %s \n",buf);
printf("Enter the string :");
fflush(stdin);
scanf("%s",buf);
send(c_check, buf, 100, 0);
}while(strcmp(buf,"bye")!=0);
close(c_check);
return(0);
}
