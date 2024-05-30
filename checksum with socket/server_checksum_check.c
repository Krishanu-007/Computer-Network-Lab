#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <math.h>
int main()
{
	int sd,cd,cadl;
	struct sockaddr_in sad,cad;
	char str[100];
	int dl,j,k,c,sum[100],t,sl,i;
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
	dl=strlen(str);
	while(1)
	{
		printf("\n enter the segment length \n");
		scanf("%d",&sl);
		for(i=1;i<=sl;i++)
		{
			if(pow(2,i)==sl)
			{
				j=1;
				break;
			}
		}
		if(j==1)
			break;
		else
			printf("\nsegment length must in pow of 2\n");
	}
	for(i=0;i<sl;i++)
		sum[i]=0;

	for(i=dl;i>0;i=i-sl)
	{

		c=0;
		k=sl-1;
		for(j=i-1;j>=i-sl;j--)
		{
			t=(sum[k]+(str[j]-48)+c);
			sum[k]=t%2;
			c=t/2;
			k--;
		}
		if(c==1)
		{
			for(j=sl-1;j>=0;j--)
			{
				t=sum[j]+c;
				sum[j]=t%2;
				c=t/2;
			}

		}
	}
	j=0;
	for(i=0;i<sl;i++)
	{
		if(sum[i]!=1)
		{
			j++;
			break;
		}
	}
	if(j==0)
	{
		printf("\n data recv ok \n");
		printf("\n ACTUAL data IS: \n");
		for(i=0;i<dl-sl;i++)
			printf("%c ",str[i]);
	}
	else
	{
		printf("\n data recv wrong \n");
	}

	close(cd);
	close(sd);
}
