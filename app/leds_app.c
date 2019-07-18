/**********************************************************************************************************
** �ļ���		:leds_app.c
** ����			:maxlicheng<licheng.chn@outlook.com>
** ����github	:https://github.com/maxlicheng
** ���߲���		:https://www.maxlicheng.com/	
** ��������		:2019-07-18
** ����			:iTop4412ȫ�ܰ�led cӦ�ó���
************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include <time.h>
#include <sys/time.h>

#include <linux/input.h>

#define LED_IOC_SET  		_IO ('k', 0)
#define LED_IOC_GET 		_IO ('k', 1)
#define LED_IOC_SET_BLINK 	_IO ('k', 2)
#define LED_IOC_GET_BLINK	_IO ('k', 3)

void delay_ms(unsigned int ms)
{
	usleep(ms*1000);
}

int main(int argc, char **argv){
	//char *leds = "/dev/led0";
	int fd,ret;
	int val;
	
	if((fd = open(argv[1], O_RDWR|O_NOCTTY|O_NDELAY))<0){
		printf("open %s failed\n", argv[1]);
		exit(1);
	}
	
	if(!strcmp("0", argv[2]))
	{
		ret = ioctl(fd, LED_IOC_SET, atoi(argv[3]));
	}
	else if(!strcmp("1", argv[2]))
	{
		ret = ioctl(fd, LED_IOC_GET, &val);
		printf("led_status is %d\n", val);
	}
	else if(!strcmp("2", argv[2]))
	{
		ret = ioctl(fd, LED_IOC_SET_BLINK, atoi(argv[3]));
	}
	else if(!strcmp("3", argv[2]))
	{
		ret = ioctl(fd, LED_IOC_GET_BLINK, &val);
		printf("freq_val is %d\n", val);
	}
	else if(!strcmp("read", argv[2]))
	{
		read(fd, &val, 1);
		printf("read leds_status %d\n", (unsigned char)val);
	}
	else if(!strcmp("write", argv[2]))
	{
		val = atoi(argv[3]);
        write(fd, &val, 1);
		printf("write leds\n");
	}
	close(fd);
	
	return ret;
}
