#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int sd,cd;
	struct sockaddr_in sa,ca;
	char data[100],divisor[10],data1[100];
	int dl,divl,i,j;
	sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	sa.sin_family=AF_INET;
	sa.sin_port=htons(9995);
	sa.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(sd,(struct sockaddr *)&sa,sizeof(sa));

	printf("\nEnter the dataword: ");
	gets(data);
	printf("\nEnter coefficients of generator polynomial: ");
	gets(divisor);
	dl=strlen(data);
	divl=strlen(divisor);
	for(i=0;i<divl-1;i++) 
		data[dl+i]='0';
	data[dl+i]='\0';
	printf("\nUpdated divident: %s",data);
	strcpy(data1,data);
	for(i=0;i<dl;i++)
	{
		if(data1[i]=='1')
		{
			for(j=0;j<divl;j++)
			{
				if(data1[i+j]==divisor[j])
					data1[i+j]='0';
				else
					data1[i+j]='1';
			}
		}
		}
		data1[i+j]='1';
		for(i=dl;i<dl+(divl-1);i++)
			data[i]=data1[i];
		printf("\nThe codeword is: %s",data);

	send(sd,data,sizeof(data),0);
	close(sd); 
	return 0;
}
