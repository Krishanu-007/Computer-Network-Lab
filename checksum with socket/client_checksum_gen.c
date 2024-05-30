#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <math.h>
int main()
{
	int sd,cadl;
	struct sockaddr_in sad,cad;
	char str[100],str1[100];
	int t,c,k,dl,sl,i,j=0,sum[100];
	sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	sad.sin_family=AF_INET;
	sad.sin_port=htons(9995);	
	sad.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(sd, (struct sockaddr *)&sad, sizeof(sad));
	printf("Enter a dataword : ");
	gets(str);
	dl=strlen(str);
	while(1)
	{
		printf("\nenter the segment length: ");
		scanf("%d",&sl);
		for(i=1;i<=sl/2;i++)
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
	if((dl%sl)!=0)
	{
		i=sl-(dl%sl);
		for(j=0;j<i;j++)
			str1[j]='0';
		strcat(str1,str);
		strcpy(str,str1);
		dl=dl+i;
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
	printf("\nChecksum = ");
	for(i=0;i<sl;i++)
	{
		if(sum[i]==0)
			sum[i]=1;
		else
			sum[i]=0;
		printf("%d",sum[i]);
		str[dl+i]=sum[i]+48;
	}
	str[dl+i]='\0';
	printf("\nCode word is:");
	puts(str);
	send(sd, str, sizeof(str),0);
	close(sd);
}
