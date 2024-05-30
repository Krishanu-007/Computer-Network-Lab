#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	int sd,cd;
	struct sockaddr_in sa,ca;
	char str[200],ch;
	sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	sa.sin_family=AF_INET;
	sa.sin_port=htons(9995);
	sa.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(sd,(struct sockaddr *)&sa,sizeof(sa));
	int c = 0, count=0;
	printf("Enter a dataword:");
	gets(str);
	while (str[c] != '\0') 
	{
		if ((str[c] == '1')) 
		{
			count++;
		}
		c++;
	}
	printf("Total no of 1s: %d",count);
	printf("\nEnter the mode of parity:'e' for Even and 'o' for Odd: ");
	scanf("%c",&ch);
	switch(ch)
	{
		case 'e':
		if(count%2==0)
		{
			strcat(str,"0");
		}
		else
		{
			strcat(str,"1");
		}
		break;
		case 'o':
		if(count%2==0)
		{
			strcat(str,"1");
		}
		else
		{
			strcat(str,"0");
		}
		break;
	}
	printf("Codeword created is: ");
	puts(str);
	send(sd,str,sizeof(str),0);
	close(sd); 
	return 0;
}