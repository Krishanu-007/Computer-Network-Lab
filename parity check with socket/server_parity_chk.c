#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
int main()
{
	int sd,cd,cadl;
	struct sockaddr_in sad,cad;
	char str[100],ch;
	int c = 0, count=0;
	sd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sad.sin_family=AF_INET;
	sad.sin_port=htons(9995);
	sad.sin_addr.s_addr=inet_addr("127.0.0.1");
	bind(sd, (struct sockaddr *)&sad, sizeof(sad));
	listen(sd,10);
	cadl=sizeof(cad);
	cd=accept(sd, (struct sockaddr *)&cad, &cadl);
	recv(cd,str,sizeof(str),0);
	printf("Client Says: %s\n",str);
	while (str[c] != '\0') 
	{
		if ((str[c] == '1')) 
		{
			count++;
		}
		c++;
	}

	printf("Total no of 1s: %d",count);
	printf("\n Enter the mode of parity:'e' for Even and 'o' for Odd ");
	scanf("%c",&ch);
	switch(ch)
	{
		case 'e':
		if(count%2==0)
		{
			printf("No error");
		}
		else
		{
			printf("Error");
		}
		break;
		case 'o':
		if(count%2==0)
		{
			printf("Error");
		}
		else
		{
			printf("No Error");
		}

		break;
	}
	close(cd);
	close(sd);
}
