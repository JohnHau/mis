  #include <stdio.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <string.h>
  
  #define SERVER_PORT 8888
  #define BUFF_LEN 1024
  
 void handle_udp_msg(int fd)
 {
     char buf[BUFF_LEN];  
     socklen_t len;
     int count;
     struct sockaddr_in clent_addr; 
     while(0)
     {
         memset(buf, 0, BUFF_LEN);
         len = sizeof(clent_addr);
         count = recvfrom(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&clent_addr, &len); 
         if(count == -1)
         {
             printf("recieve data fail!\n");
             return;
         }
         printf("client:%s\n",buf); 
         memset(buf, 0, BUFF_LEN);
         sprintf(buf, "I have recieved %d bytes data!\n", count); 
         printf("server:%s\n",buf); 
         sendto(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&clent_addr, len); 
 
     }


     memset(buf, 0, BUFF_LEN);
     len = sizeof(clent_addr);
     count = recvfrom(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&clent_addr, &len); 

     printf("count is %d\n",count);

 }


/*
server:
socket-->bind-->recvfrom-->sendto-->close
*/

int main(int argc, char* argv[])
{
	int server_fd, ret;
	struct sockaddr_in ser_addr; 

	server_fd = socket(AF_INET, SOCK_DGRAM, 0); //AF_INET:IPV4;SOCK_DGRAM:UDP
	if(server_fd < 0)
	{
		printf("create socket fail!\n");
		return -1;
	}

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY); //IP地址，需要进行网络序转换，INADDR_ANY：本地地址
	ser_addr.sin_port = htons(SERVER_PORT);  //端口号，需要网络序转换

	ret = bind(server_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
	if(ret < 0)
	{
		printf("socket bind fail!\n");
		return -1;
	}

	handle_udp_msg(server_fd);   //处理接收到的数据

	close(server_fd);
	return 0;
}
