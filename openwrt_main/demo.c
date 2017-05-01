#include <stdio.h>  
#include <string.h>  
#include "serialport.h"  

int main(int argc,char *argv[])  
{  
	int iResult = -1;     
	int fd = -1,iCommPort,iBaudRate,iDataSize,iStopBit;  
	char cParity;  
	int iLen;  
	char szBuffer[30];  

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
#if 0
	//测试程序1
	//向串口发送Hello
	iLen = write_port(fd,"Hello",5);
	//将szBuffer清零
	memset(szBuffer,0,sizeof(szBuffer));
	//读取得到的数据，并打印
	iLen = read_port(fd,szBuffer,5);
	if(iLen > 0)
		printf("iLen = %d,szBuffer = %s \n",iLen,szBuffer);
#endif

#if 1
	//测试程序2
	char buf[32];
	char sendbuf[32];
	char *ret_fgets;
	while(1)
	{
		memset(buf,'\0',sizeof(buf));
		memset(sendbuf,'\0',sizeof(sendbuf));
		ret_fgets = fgets(buf,sizeof(buf),stdin);
		if(ret_fgets != NULL)
		{
			sprintf(sendbuf,"%s\r\n",buf);
			//向串口发送sendbuf
			iLen = write_port(fd,sendbuf,strlen(sendbuf));
			//将szBuffer清零
			memset(szBuffer,0,sizeof(szBuffer));
			//读取得到的数据，并打印
			iLen = read_port(fd,szBuffer,6);
			if(iLen > 0)
				if(szBuffer[4] == '\r' && szBuffer[5] == '\n')
					printf("iLen = %d,szBuffer = %s \n",iLen,szBuffer);
		}
	}
#endif


	//******************************************************//
	//***********************TCP服务器**********************//
	//******************************************************//



	return 0;
}
