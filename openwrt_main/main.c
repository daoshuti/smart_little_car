#include <stdio.h>  
#include <string.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include "serialport.h"

#define 	BUF_SIZE 	32
#define 	IP_ADDR 	"0.0.0.0"
#define 	IP_PORT 	50000
#define 	MAX_EVENTS 	50

int main(int argc,char *argv[])  
{
	int sockfd,confd;
	int iResult = -1;     
	int fd = -1,iCommPort,iBaudRate,iDataSize,iStopBit;
	char cParity;  
	int iLen,i;
	int ret_recv;
	char sendbuf[BUF_SIZE];
	char recvbuf[BUF_SIZE];  

	//******************************************************//
	//*****************serial串口初始化*********************//
	//******************************************************//
	
	//设置打开的串口为ttyUSB0
	iCommPort = 1;  
	//打开串口
	fd = open_port(iCommPort);  
	if( fd<0 )  
	{  
		perror("open_port error !");  
		return 1;  
	}  
	//填充串口通通信的波特率等参数
	iBaudRate = 9600;//波特率
	iDataSize = 8;//8位数据位
	cParity = 'N';//没有奇偶校验位
	iStopBit = 1;//1位停止位
	//初始化串口
	iResult = set_port(fd,iBaudRate,iDataSize,cParity,iStopBit);      
	if( iResult<0 )  
	{  
		perror("set_port error !");  
		return 1;  
	}     
	//打印串口设备，在本文程序中的文件描述符
	printf("fd = %d \n",fd);

	//******************************************************//
	//*****************TCP服务器,epoll**********************//
	//******************************************************//
	
	//创建一个socket
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(socket < 0)
	{
		perror("fail to socket!!!\n");
		return sockfd;
	}
	//实例化一个sockaddr_in结构体
	//并给成员变量赋值
	struct sockaddr_in seraddr;
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(IP_PORT);
	seraddr.sin_addr.s_addr = inet_addr(IP_ADDR);

	//绑定
	int ret_bind;
	ret_bind = bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
	if(ret_bind < 0)
	{
		perror("fail to bind!!!");
		return ret_bind;
	}

	//监听
	listen(sockfd,5);

	//实例化 struct epoll_event 结构体
	struct epoll_event ev,events[MAX_EVENTS];
	int nfds,epollfd;

	//通过文件描述符来操作epoll
	epollfd = epoll_create(MAX_EVENTS);
	//linux 旧版本需要填充足够大的数
	//较劲内核 数值填充小了，在后期不影响监控范围
	if(epollfd < 0)
	{
		perror("fail to epoll");
		return -1;
	}

	ev.events = EPOLLIN;//监视读资源
	ev.data.fd = sockfd;//把sockfd放到“表”里面
	if(epoll_ctl(epollfd,EPOLL_CTL_ADD,sockfd,&ev) == -1)
	{
		//epoll_ctl返回值如果为-1说明，sockfd放入表中失败
		perror("fail to add fd");
		return -1;
	}
	
	//epoll 优点1 添加一次，不需要重复添加
	while(1)
	{
		/*
		 * 参数1：epollfd 属于 代表epoll操作的文件描述符
		 * 参数2：填入，用于返回结果的数组
		 * 参数3：最大监控个数
		 * 参数4：超时 -1 代表不监视
		 * 返回值：错误时，小于0
		 * 			正确时，返回数组中最大就绪的事件的序号+1
		 * */
		nfds = epoll_wait(epollfd,events,MAX_EVENTS,-1);//等同于select
		if(nfds < 0)
		{
			perror("fail to epoll_wait");
			return -1;
		}
		//当有事件相应时，epoll_wait停止阻塞
		//开始for循环，依次处理事件
		for(i=0; i<nfds; i++)
		{
			//当sockfd就绪时
			if(events[i].data.fd == sockfd)
			{
				//连接客户端，并得到一个文件描述符
				confd = accept(sockfd,NULL,NULL);
				printf("confd:%d\n",confd);
				if(confd < 0)
				{
					perror("fail to accept");
					return -1;
				}
				ev.events = EPOLLIN;//监视读资源
				ev.data.fd = confd;
				if(epoll_ctl(epollfd,EPOLL_CTL_ADD,confd,&ev) == -1)
				{
					perror("fail to add fd");
					return -1;
				}
			}
			else
			{
				//清空buffer
				memset(recvbuf,'\0',sizeof(recvbuf));
				//接收客户端数据
				ret_recv = recv(events[i].data.fd,recvbuf,sizeof(recvbuf),0);
				if(ret_recv < 0)//出错时
				{
					perror("fail to recv!!!");
					return -1;
				}
				else if(ret_recv == 0)//断开连接时
				{
					printf("peer is closed:%d\n",events[i].data.fd);
					if(epoll_ctl(epollfd,EPOLL_CTL_DEL,events[i].data.fd,NULL) == -1)
					{
						perror("fail to epoll_ctl_del!!!");
						return -1;
					}
					close(events[i].data.fd);
				}
				else//正常接收到数据时
				{
					printf("recv app:%s\n",recvbuf);
					//send(events[i].data.fd,buf,sizeof(buf),0);
					//拼接字符串，完善命令格式
					sprintf(sendbuf,"%s\r\n",recvbuf);
					//向串口发送sendbuf
					iLen = write_port(fd,sendbuf,strlen(sendbuf));
					//读取得到的数据，并打印
					iLen = read_port(fd,recvbuf,6);
					if(iLen > 0)
						if(recvbuf[4] == '\r' && recvbuf[5] == '\n')
							printf("iLen = %d,recvbuf = %s \n",iLen,recvbuf);

				}
			}
		}
	}


#if 0
	//测试程序
	char buf[BUF_SIZE];
	char *ret_fgets;
	while(1)
	{
		//将Buffer清零
		memset(buf,'\0',sizeof(buf));
		memset(recvbuf,'\0',sizeof(recvbuf));
		memset(sendbuf,'\0',sizeof(sendbuf));
		ret_fgets = fgets(buf,sizeof(buf),stdin);
		if(ret_fgets != NULL)
		{
			sprintf(sendbuf,"%s\r\n",buf);
			//向串口发送sendbuf
			iLen = write_port(fd,sendbuf,strlen(sendbuf));
			//读取得到的数据，并打印
			iLen = read_port(fd,recvbuf,6);
			if(iLen > 0)
				if(recvbuf[4] == '\r' && recvbuf[5] == '\n')
					printf("iLen = %d,recvbuf = %s \n",iLen,recvbuf);
		}
	}
#endif


	//******************************************************//
	//******************************************************//



	return 0;
}
