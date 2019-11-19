#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<pthread.h>
void* Send(void *cli_socket_ptr)
{
	char buff[256];
	int *cli_socket_ptr_Temp = (int *)cli_socket_ptr;
	int cli_socket = *cli_socket_ptr_Temp;

	while(1)
	{
		bzero(buff,256);
		printf("Enter MSG : ");
		gets(buff);
		int msg_len = 0,nBytes = 0,i = 0;
		while(buff[i++] != NULL)
		{
			msg_len++;
			//i++;
		}
		buff[++msg_len] = '\n';
		msg_len++;
		nBytes = write(cli_socket,buff,msg_len);
		printf("%40d bytes sent with MSG_LEN : %d\n",nBytes,msg_len);
		if(nBytes < 2)
		{
			printf("Disconnecting client\nShutting Down Connection\n");
			shutdown(cli_socket,2);
			break;
		}
	}
}

int main()
{
	struct sockaddr_in serv_addr,cli_addr;
	int serv_socket,cli_socket,cli_len = sizeof(cli_addr);
	char buff[256];

	serv_addr.sin_port = htons(32000);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_family = AF_INET;

	if((serv_socket = socket(AF_INET,SOCK_STREAM,0)) < 0)
		{	perror("Socker ");exit(0);	}
	else
		printf("Socket is Created Successfully\n");

	if(
		bind(serv_socket,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0
	) {		perror("binding ");exit(0);		}
	else
	{
	   	printf("Socket Binding Successfull\n");
	}

	listen(serv_socket,5);

	while(1)
	{
		cli_socket = accept(serv_socket,(struct sockaddr *)&cli_addr,&cli_len);

		if(cli_socket < 0)
		{		perror("cli_socket ");exit(0);		}
		else
		{
			printf("Connection Established With CLient : %s\n",inet_ntoa(cli_addr.sin_addr));
		}

//Threads Creation Starts  here--------------------------------------------------------------------------------------- 
		pthread_t sendThread,recvThread;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&sendThread,&attr,Send,&cli_socket);

		while(1)
		{
			bzero(buff,256);
			int nBytes = read(cli_socket,buff,sizeof(buff));

			if(nBytes < 2)
			{
				printf("Client Disconnecting\nShutting Down Client\n");
				break;
				shutdown(cli_socket,2);
			}
			else
			{
				printf("Client_MSG : %s\n",buff);
			}
		}
		pthread_join(sendThread,NULL);
	}
	return 0;
}
