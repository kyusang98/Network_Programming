#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
int simpleSocket = 0;
int simplePort = 0;
int returnStatus = 0;
char buffer[512] = "";
struct sockaddr_in simpleServer;
if (3 != argc) {
fprintf(stderr, "Usage: %s <server> <port>\n", argv[0]);
exit(1);
}
/* create a streaming socket */
simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
if (simpleSocket == -1) {
fprintf(stderr, "Could not create a socket!\n");
exit(1);
}

else {
fprintf(stderr, "Command Socket created!\n");
}
/* retrieve the port number for connecting */
simplePort = atoi(argv[2]);
/* set up the address structure */
/* use the IP address argument for the server address */
bzero(&simpleServer, sizeof(simpleServer));
simpleServer.sin_family = AF_INET;
simpleServer.sin_addr.s_addr=inet_addr(argv[1]);
simpleServer.sin_port = htons(simplePort);
/* connect to the address and port with our socket */
returnStatus = connect(simpleSocket,
(struct sockaddr *)&simpleServer,
sizeof(simpleServer));
if (returnStatus == 0) {
fprintf(stderr, "Connect successful!\n");
}
else {
fprintf(stderr, "Could not connect to address!\n");
close(simpleSocket);
exit(1);
}

/* send the request to the server */
const char REQUESTMESSAGE1[] = "USER elec\r\n";
write(simpleSocket, REQUESTMESSAGE1, strlen(REQUESTMESSAGE1));

/* get the message from the server */
returnStatus = read(simpleSocket, buffer, sizeof(buffer));

if ( returnStatus > 0 ) {
printf("%d: %s", returnStatus, buffer);
}
else {
fprintf(stderr, "Return Status = %d \n", returnStatus);
}

/* send the request to the server */
const char REQUESTMESSAGE2[] = "PASS comm\r\n";
write(simpleSocket, REQUESTMESSAGE2, strlen(REQUESTMESSAGE2));

/* get the message from the server */
returnStatus = read(simpleSocket, buffer, sizeof(buffer));

if ( returnStatus > 0 ) {
printf("%d: %s", returnStatus, buffer);
}
else {
fprintf(stderr, "Return Status = %d \n", returnStatus);
}

/* send the request to the server */
const char REQUESTMESSAGE3[] = "PASV\r\n";
write(simpleSocket, REQUESTMESSAGE3, strlen(REQUESTMESSAGE3));

/* get the message from the server */
returnStatus = read(simpleSocket, buffer, sizeof(buffer));

if ( returnStatus > 0 ) {
printf("%d: %s", returnStatus, buffer);
}
else {
fprintf(stderr, "Return Status = %d \n", returnStatus);
}


/*Extract and Calculate the IP and Port Number from buffer*/
char str[512]; //대상 문자열
sprintf(str,"%s",buffer);


int i = 0;
// '('가 나타나면 ','로 바꿔준다.
while (1)
    {
        if (str[i] == '(')
        {
            str[i] = ',';
            break;
        }
        i++;
    }
// ')'가 나타나면 ','로 바꿔준다.

while (1)
    {
        if (str[i] == ')')
        {
            str[i] = ',';
            break;
        }
        i++;
    }

/*컴마를 기준으로 문자열 자르기*/
char* context = NULL;
char* temp = strtok_r(str, ",", &context);
int arr[6];

i = 0;
while (temp != NULL)              //tem가 NULL일때까지 (= strtok 함수가 NULL을 반환할때까지)
    {
        if (i != 0)
        {

            arr[i - 1] = atoi(temp);

        }

        temp = strtok_r(NULL, " ,",&context);     //자른 문자 다음부터 구분자 또 찾기
        i++;
        if (i == 7)
            break;
    }



char data_ip[20];
sprintf(data_ip, "%d.%d.%d.%d", arr[0],arr[1],arr[2],arr[3]);
printf("%s\n",data_ip);

int data_port=arr[4] * 256 + arr[5];
printf("%d\n", data_port);


//new datasocket
int data_simpleSocket = 0;
int data_simplePort = 0;
int data_returnStatus = 0;
char data_buffer[512] = "";
struct sockaddr_in data_simpleServer;
/*
if (3 !=data_argc) {
fprintf(stderr, "Usage: %s <server> <port>\n", data_argv[0]);
exit(1);
}
*/
/* create a streaming socket */
data_simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
if (data_simpleSocket == -1) {
fprintf(stderr, "Could not create a socket!\n");
exit(1);
}

else {
fprintf(stderr, "Data Socket created!\n");
}
/* retrieve the port number for connecting */
data_simplePort = data_port;
/* set up the address structure */
/* use the IP address argument for the server address */
bzero(&data_simpleServer, sizeof(data_simpleServer));
data_simpleServer.sin_family = AF_INET;
data_simpleServer.sin_addr.s_addr=inet_addr(data_ip);
data_simpleServer.sin_port = htons(data_simplePort);
/* connect to the address and port with our socket */
returnStatus = connect(data_simpleSocket,
(struct sockaddr *)&data_simpleServer,
sizeof(data_simpleServer));
if (returnStatus == 0) {
fprintf(stderr, "Connect successful!\n");
}
else {
fprintf(stderr, "Could not connect to address!\n");
close(data_simpleSocket);
exit(1);
}



/* send the request to the server */
const char REQUESTMESSAGE4[] = "RETR welcome.txt\r\n";
write(simpleSocket, REQUESTMESSAGE4, strlen(REQUESTMESSAGE4));
/*Command Client gets the message from the server */
returnStatus = read(simpleSocket, data_buffer, sizeof(data_buffer));

if ( returnStatus > 0 ) {
printf("%d: %s", returnStatus, data_buffer);
}
else {
fprintf(stderr, "Return Status = %d \n", returnStatus);
}




/*Data Client gets the message from the server */
returnStatus = read(data_simpleSocket, data_buffer, sizeof(data_buffer));

if ( returnStatus > 0 ) {
printf("%d: %s", returnStatus, data_buffer);
}
else {
fprintf(stderr, "Return Status = %d \n", returnStatus);
}


close(data_simpleSocket);
close(simpleSocket);

return 0;
}

