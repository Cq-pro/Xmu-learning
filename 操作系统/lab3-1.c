 #include<stdio.h>
 # include<stdlib.h>
 # include<string.h>
 # include<unistd.h>
 # include<sys/types.h>
 # includc<linux/msg.h>
 #define MAXMSG 512 //定义消息长度
 struct my_msg//定义消息缓冲区数据结构
 {
	long int my_msg_type;
	char some_text[MAXMSG];
 }msg;
main()
{
	int p;
	int msgid;                   //定义消息缓冲区内部标识
	char buffcr[BUFSIZ];         //定义用户缓冲区
	msgid=msgget(1234,0666|IPC_CREAT);   //创建消息队列，key 为 1234
	long int msg_to_receive=0;
	while((p=fork( ))==-l);
	if (p==0){
		while(1)
		{
			puts("Enter some text:");      //提示键入消息内容
			fgets(buffer, BUFS1Z,stdin);   //标准输入送 buffer
			msg.my_msg_type=1;             //设置消息类型为1
			strcpy(msg.some_text,buffer);  //buffer 送消息缓冲
			msgsnd (msgid,&msg,MAXMSG,0);  //发送消息到消息队列
			if(strncmp(msg.some_text, "end",3)==0)//消息为“end”则结束
				break；
		}
		exit(0)
}
else{
	wait(O);
	while (1)
	{
		msgrcv(msgid,&msg,BUFSIZ,msg_to_receive,0);      //接收消息
		printf("You wrote:%s" ,msg.some_text);           //显示消息
		if (strncmp (msg.some_text,"end",3)==0)       //消息为“end”则结束
			break;
	}
	msgctl (msgid, IPC_RMID,0)                       //撤消消息队列
	}
}