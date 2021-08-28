#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

void error_handling(char* message);

int main(int argc, char* argv[]){
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr-size;

	char message[]="Hello World!";

	if(argc!=2){
		printf("Usage : %s <port> \n",argv[0]);
		exit(1);
	}
	
	// 서버소켓 생성
	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	if(serv_sock==-1)
		error_hangling("socket() error");
	
	// 주소정보를 담을 구조체 변수 선언 및 초기화
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); // INADDR_ANY를 사용하면  소켓이 동작하는 컴퓨터의 IP주소가 자동으로 할당
	serv_addr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind() error");
	
	if(listen(serv_sock,5)==-1) // 연결요청 대기상태 및 연결요청 대기 큐 생성
		error_handling("listen() error");

	clnt_addr_size=sizeof(clnt_addr);
	clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size); // 연결요청을 참조하여 클라이언트와의 연결 구성
	if(clnt_sock==-1)
		error_handling("accept() error");

	write(clnt_sock, message, sizeof(message)); // 클라이언트에 데이터 전송
	close(clnt_sock);
	close(serv_sock);
	return 0;
}

void error_handling(char *message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
