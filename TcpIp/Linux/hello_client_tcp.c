#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char* message);

int main(int argc, char* argv[]){
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len;

	if(argc!=3){
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock=socket(PF_INET,sock_STREAM,0); // 클라이언트 소켓생성
	if(sock==-1)
		error_handling("socket() error");

	// 주소정보를 담기 위한 구조체변수 선언 및 초기화
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(argv[2]);

	// 서버로 연결요청
	if(connect(sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
		error_handling("connect() error");
	
	// 연결 성공 후 서버로부터 전송되는 데이터 수신
	str_len=read(sock, message, sizeof(message)-1);
	if(str_len==-1)
		error_handling("read() error!");
	
	printf("Message from server : %s \n",message);
	close(sock);
	return 0;
}

void error_handling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
