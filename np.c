exp.2.client

//Client
// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080
 
int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}
 

exp.2.server

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                    (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    return 0;
}





exp.3.client

//Client
// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080
 
int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
char hello2[10];
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "172.20.3.28", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    do{
    scanf(" %s",hello2);
    send(sock , hello2 , strlen(hello2) , 0 );
    printf("message sent to server\n");
    valread = read( sock , buffer, 1024);
    buffer[valread]='\0';
    printf("Message from server:%s\n",buffer );
    }while(strcmp(hello2,"quit");
    return 0;
}
 

exp.3.server

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from Anil";
    char ch[20];
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                    (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
   
    do{
    valread = read( new_socket , buffer, sizeof(buffer));
    buffer[valread]='\0';
    printf("Message from client%s\n",buffer );
    scanf(" %s",ch);
    send(new_socket , ch , strlen(ch) , 0 );
    printf("Message send to client\n");
   }while(strcmp(ch,"quit")); 


    return 0;
}


exp.4.client

//Client
// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080
 
int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
char hello2[10];
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "172.20.3.28", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    do{
    scanf(" %[^\n]",hello2);

    send(sock , hello2 , strlen(hello2) , 0 );
    printf("message sent to server\n");
    valread = read( sock , buffer, 1024);
    buffer[valread]='\0';
    printf("Message from server:  %s\n",buffer );
    }while(strcmp(hello2,"quit"));
    return 0;
}
 

exp.4.server

//server-one way
//https://www.geeksforgeeks.org/socket-programming-cc/
// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include<time.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from Anil";
    char ch[20];
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                    (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
       time_t t;   // not a primitive datatype
    do{
    valread = read( new_socket , buffer, sizeof(buffer));
    buffer[valread]='\0';
    printf("Request from client  %s\n",buffer );
    if (!strcmp(buffer,"get time"))
      {    time(&t);
      strcpy (ch,ctime(&t));
      //scanf(" %s",ch);
      send(new_socket , ch , strlen(ch) , 0 );
      printf("Time sent to client\n");
      }
	else{
	strcpy (ch,"Wrong command");
      //scanf(" %s",ch);
      send(new_socket , ch , strlen(ch) , 0 );

	}

   }while(strcmp(ch,"quit")); 


    return 0;
}


exp.5.client

//Client program
//./a.oout 127.0.0.1 5300
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<stdlib.h>
void main(int argc, char * argv[])
{
int i,j,n;
int sock_fd;
struct sockaddr_in servaddr;

int matrix_1[10][10], matrix_2[10][10], matrix_product[10][10];
int size[2][2];
int num_rows_1, num_cols_1, num_rows_2, num_cols_2;
if(argc != 3)
{
fprintf(stderr, "Usage: ./client IPaddress_of_server port\n");
exit(1);
}
printf("Enter the number of rows of first matrix\n");
scanf("%d", &num_rows_1);
printf("Enter the number of columns of first matrix\n");
scanf("%d", &num_cols_1);
printf("Enter the values row by row one on each line\n" );
for ( i = 0; i < num_rows_1; i++)
for( j=0; j<num_cols_1; j++)
{
scanf("%d", &matrix_1[i][j]);
}
size[0][0] = num_rows_1;
size[0][1] = num_cols_1;
printf("Enter the number of rows of second matrix\n");
scanf("%d", &num_rows_2);
printf("Enter the number of columns of second matrix\n");
scanf("%d", &num_cols_2);
if( num_cols_1 != num_rows_2)
{
printf("MATRICES CANNOT BE MULTIPLIED\n");
exit(1);
}
printf("Enter the values row by row one on each line\n");
for (i = 0; i < num_rows_2; i++)
for(j=0; j<num_cols_2; j++)
{


scanf("%d", &matrix_2[i][j]);
}
size[1][0] = num_rows_2;
size[1][1] = num_cols_2;
if((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
{
printf("Cannot create socket\n");
exit(1);
}
bzero((char*)&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(atoi(argv[2]));
inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

// SENDING MATRIX WITH SIZES OF MATRICES 1 AND 2
n = sendto(sock_fd, size, sizeof(size),0, (struct sockaddr*)&servaddr, sizeof(servaddr));
if( n < 0)
{
perror("error in matrix 1 sending");
exit(1);
}
// SENDING MATRIX 1
n = sendto(sock_fd, matrix_1, sizeof(matrix_1),0, (struct sockaddr*)&servaddr, sizeof(servaddr));
if( n < 0)
{
perror("error in matrix 1 sending");
exit(1);
}
// SENDING MATRIX 2
n = sendto(sock_fd, matrix_2, sizeof(matrix_2),0, (struct sockaddr*)&servaddr, sizeof(servaddr));
if( n < 0)
{
perror("error in matrix 2 sending");
exit(1);


}
if((n=recvfrom(sock_fd, matrix_product, sizeof(matrix_product),0, NULL, NULL)) == -1)
{
perror("read error from server:");
exit(1);
}
printf("\n\nTHE PRODUCT OF MATRICES IS \n\n\n");
for( i=0; i < num_rows_1; i++)
{
for( j=0; j<num_cols_2; j++)
{
printf("%d ",matrix_product[i][j]);
}
printf("\n");
}
//close(sock_fd);
}


exp.5.server

//Server Program
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<stdlib.h>

void main(int argc, char * argv[])
{
int n;
int sock_fd;
int i,j,k;
int row_1, row_2, col_1, col_2;
struct sockaddr_in servaddr, cliaddr;

int len = sizeof(cliaddr);
int matrix_1[10][10], matrix_2[10][10], matrix_product[10][10];
int size[2][2];
if(argc != 2)
{
fprintf(stderr, "Usage: ./server port\n");
exit(1);
}

if((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
{
printf("Cannot create socket\n");
exit(1);
}
bzero((char*)&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(atoi(argv[1]));
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
if(bind(sock_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
{
perror("bind failed:");
exit(1);
}
// MATRICES RECEIVE
if((n = recvfrom(sock_fd, size, sizeof(size), 0, (struct sockaddr *)&cliaddr, &len)) == -1)
{
perror("size not received:");
exit(1);
}
// RECEIVE MATRIX 1
if((n = recvfrom(sock_fd, matrix_1, sizeof(matrix_1), 0, (struct sockaddr *)&cliaddr, &len)) == -1)
{
perror("matrix 1 not received:");
exit(1);
}

// RECEIVE MATRIX 2
if((n = recvfrom(sock_fd, matrix_2, sizeof(matrix_2), 0, (struct sockaddr *)&cliaddr, &len)) == -1)
{
perror("matrix 2 not received:");
exit(1);
}
row_1 = size[0][0];
col_1 = size[0][1];
row_2 = size[1][0];
col_2 = size[1][1];
for (i =0; i < row_1 ; i++)
for (j =0; j <col_2; j++)
{
matrix_product[i][j] = 0;
}
for(i =0; i< row_1 ; i++)
for(j=0; j< col_2 ; j++)
for (k=0; k < col_1; k++)
{
matrix_product[i][j] += matrix_1[i][k]*matrix_2[k][j];
}
n = sendto(sock_fd, matrix_product, sizeof(matrix_product),0, (struct sockaddr*)&cliaddr,
sizeof(cliaddr));
if( n < 0)
{
perror("error in matrix product sending");
exit(1);
}
//close(sock_fd);
}


exp.6.client

//Client program
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<stdlib.h>
void main(int argc, char* argv[])
{
char buffer[100], line[100], cmd[100];
char name[100];
int sock_fd;
char  user[100],pass[100];
char * p;
struct sockaddr_in servaddr;
int x,y,op,z;

if((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
{
printf("Cannot create socket\n");
}

bzero(line, sizeof(line));
bzero(buffer, sizeof(buffer));

bzero((char*)&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(5556);   
inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
printf("Enter the user name\n");
scanf("%s", user);
sendto(sock_fd, user, sizeof(user),0, (struct sockaddr*)&servaddr, sizeof(servaddr));

printf("Enter the password\n");
scanf("%s", pass);
sendto(sock_fd, pass, sizeof(pass),0, (struct sockaddr*)&servaddr, sizeof(servaddr));

int v2=recvfrom(sock_fd, &buffer, sizeof(buffer),0, NULL, NULL);
buffer[v2]='\0';
printf("\n\nFrom server:\n");
	printf("%s \n",buffer);

if (strcmp(buffer,"login success")==0)
   {printf("Enter the name of file\n");
   scanf("%s", name);
   sendto(sock_fd, name, sizeof(name),0, (struct sockaddr*)&servaddr, sizeof(servaddr));
   int v=recvfrom(sock_fd, &buffer, sizeof(buffer),0, NULL, NULL);
//buffer[v]='\0';
    printf("\n\nTHE RESULT IS \n");
   printf("%s \n",buffer);
   }
   

}

exp.6.server

//Server Program
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<stdlib.h>

void main(int argc, char * argv[])
{
int n;
int sock_fd;
int i,j,k;
int y,z,op;
char x[100],user[100],pass[100],result[100];
char str [100];

int row_1, row_2, col_1, col_2;
struct sockaddr_in servaddr, cliaddr;
int len = sizeof(cliaddr);
if((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
     {
     printf("Cannot create socket\n");
     exit(1);
     }
bzero((char*)&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(5556);
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
if(bind(sock_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
     {
     exit(1);
     }
         
if((n = recvfrom(sock_fd, &user, sizeof(user), 0, (struct sockaddr *)&cliaddr, &len)) == -1)
     {
     exit(1);
     }
if((n = recvfrom(sock_fd, &pass, sizeof(pass), 0, (struct sockaddr *)&cliaddr, &len)) == -1)
     {
     exit(1);
     }
if(strcmp(user,"arun")==0 && strcmp(pass,"abcd")==0)
     { strcpy(result,"login success");
     printf("login success");
     sendto(sock_fd, result, sizeof(result),0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
     }
else
     { strcpy(result,"login failure");
     printf("\n login failure");
     sendto(sock_fd, result, sizeof(result),0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
      //exit(1);
      }
                  

    
if((n = recvfrom(sock_fd, &x, sizeof(x), 0, (struct sockaddr *)&cliaddr, &len)) == -1)
     {
     exit(1);
     }

 FILE *fp= fopen(x, "r"); // read only  
     
          if (!fp ) // equivalent to saying if ( in_file == NULL ) 
             {  
                printf("oops, file can't be read\n"); 
                //exit(-1); 
                strcpy(str," File not found");
             }
        else     fgets (str, 60, fp);

   sendto(sock_fd, str, sizeof(str),0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
 

}


exp.7.sender

#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include <arpa/inet.h>
struct packet
{	int data;
	int seq;
};
struct ackn
{
	int seq;
	int ack;
};
void main()
{
  int sender,len,wind,j,l,k,c,i,r;
  struct ackn a;
   char buffer[1024];
   struct packet p[10];
  struct sockaddr_in receiver;
  sender=socket(AF_INET,SOCK_STREAM,0);
  receiver.sin_family=AF_INET;
  receiver.sin_port=htons(2060);
  receiver.sin_addr.s_addr=inet_addr("192.168.1.19");
   connect(sender,(struct sockaddr*)&receiver,sizeof(receiver));
  send(sender,"hai",strlen("hai"),0);
 
  i=read(sender,buffer,1024);
  buffer[i]='\0';
  printf("Received %s\n",buffer);
  
j=1;
l=1;
k=1;

printf("Sending frame \n");
while(j<=8)
{  printf("Enter Packet data");
   scanf("%d",&p[j].data);
     p[j].seq=j;
	j++;
		
} 
while(l<=4)
{	send(sender,(char*)&p[l],sizeof(p[l]),0);
	printf("sending packet with data %d and seq no %d\n",p[l].data,p[l].seq);
	l++;
}
c=0;
while(c<8)
{	        
	   r=read(sender,(char *)&a,sizeof(a));
	   if (a.ack==1)
	  {	c=c+1;
		printf("received ack for packet %d\n",a.seq);
                if(l<=8)
		{printf("sending packet with data %d and seq no %d\n",p[l].data,p[l].seq);
		send(sender,(char*)&p[l],sizeof(p[l]),0);
		l++;}
	   }
	    if (a.ack==-1)
		{	printf("\n\ntime expired for packet %d\n",a.seq);
			for(k=a.seq;k<l;k++)
			{	printf("resending packet with data %d and seq no %d\n",p[k].data,p[k].seq);
				send(sender,(char*)&p[k],sizeof(p[k]),0);
				
			}
                }
	
}
close(sender);
}

		
exp.7.reciever

#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include <arpa/inet.h>
struct packet
{	int data;
	int seq;
};
struct ackn
{
	int seq;
	int ack;
};
void main()
{	int receiver,sender,len,c,t,wind,j,l,k,r,ran,f,i;
  	int opt=1;
	struct ackn a[10];
 	char buffer[1024];
   	struct packet p[15];
  	struct sockaddr_in senderadd,recvadr;
 	receiver=socket(AF_INET,SOCK_STREAM,0);	
	recvadr.sin_family=AF_INET;
 	 recvadr.sin_port=htons(2060);
 	 recvadr.sin_addr.s_addr=inet_addr("192.168.1.19");
	setsockopt(receiver, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt));
	if (bind(receiver,(struct sockaddr*)&recvadr,sizeof(recvadr))<0)
               printf("Not Connected\n");
	listen(receiver,3);
         sender=accept(receiver,(struct sockaddr*)&senderadd,&len);	
 	i=read(sender,buffer,1024); 
	buffer[i]='\0';
	printf("Received %s\n",buffer);
  	send(sender,"hello",strlen("hello"),0);
	j=1;
	k=1;
        c=0;
	while(j<=4)
	{       r=read(sender,(char *)&p[j],sizeof(p[j]));
		j++;
	}
        t=4;
	j=1;
	while(c<8)
	{       
		ran=rand()%3;
		if(ran==0)
          	{	a[j].ack=-1;
			a[j].seq=p[j].seq;
		}
		else{ a[j].ack=1;
			a[j].seq=p[j].seq;
		}
                
                if(a[j].ack==1)
                {  printf("Received Packet with data %d and seq %d\n",p[j].data,p[j].seq);
			send(sender,(char*)&a[j],sizeof(a[j]),0);c++;j++;
		   
                  if(t<8){ t++;read(sender,(char*)&p[t],sizeof(p[t]));  }
                  }
		else
		{   send(sender,(char*)&a[j],sizeof(a[j]),0);
                         printf("\n\n");
		
                    for(k=j;k<=t;k++)
                     { read(sender,(char*)&p[k],sizeof(p[k]));}
				
                 }

	}	
		
		
close(receiver);
}

		

EXP 8


Algorithm
Sender Site Algorithm of Selective Repeat Protocol
begin
   frame s; //s denotes frame to be sent
   frame t; //t is temporary frame
   S_window = power(2,m-1); //Assign maximum window size
   SeqFirst = 0; // Sequence number of first frame in window
   SeqN = 0; // Sequence number of Nth frame window
   while (true) //check repeatedly
      do
         Wait_For_Event(); //wait for availability of packet
         if ( Event(Request_For_Transfer)) then
            //check if window is full
            if (SeqN–SeqFirst >= S_window) then
               doNothing();
            end if;
            Get_Data_From_Network_Layer();
            s = Make_Frame();
            s.seq = SeqN;
            Store_Copy_Frame(s);
            Send_Frame(s);
            Start_Timer(s);
            SeqN = SeqN + 1;
         end if;
         if ( Event(Frame_Arrival) then
            r = Receive_Acknowledgement();
            //Resend frame whose sequence number is with ACK
            if ( r.type = NAK) then
               if ( NAK_No > SeqFirst && NAK_No < SeqN ) then
                  Retransmit( s.seq(NAK_No));
                  Start_Timer(s);
               end if
                  //Remove frames from sending window with positive ACK
               else if ( r.type = ACK ) then
                  Remove_Frame(s.seq(SeqFirst));
                  Stop_Timer(s);
                  SeqFirst = SeqFirst + 1;
               end if
         end if
         // Resend frame if acknowledgement haven’t been received
         if ( Event(Time_Out)) then
            Start_Timer(s);
            Retransmit_Frame(s);
         end if
end
Receiver Site Algorithm of Selective Repeat Protocol
Begin
   frame f;
   RSeqNo = 0; // Initialise sequence number of expected frame
   NAKsent = false;
   ACK = false;
   For each slot in receive_window
   Mark(slot)=false;
   while (true) //check repeatedly
      do
         Wait_For_Event(); //wait for arrival of frame
         if ( Event(Frame_Arrival) then
            Receive_Frame_From_Physical_Layer();
            if ( Corrupted ( f.SeqNo ) AND NAKsent = false) then
               SendNAK(f.SeqNo);
               NAKsent = true;
            end if
            if ( f.SeqNo != RSeqNo AND NAKsent = false ) then
               SendNAK(f.SeqNo);
               NAKsent = true;
               if ( f.SeqNo is in receive_window ) then
                  if ( Mark(RSeqNo) = false ) then
                     Store_frame(f.SeqNo);
                     Mark(RSeqNo) = true;
                  end if
               end if
               else
               while ( Mark(RSeqNo))
                  Extract_Data(RSeqNo);
                  Deliver_Data_To_Network_Layer();
                  RSeqNo = RSeqNo + 1;
                  Send_ACK(RSeqNo);
               end while
            end if
         end if
   end while
end

Program
Sender program
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include <arpa/inet.h>
struct packet
{	int data;
	int seq;
};
struct ackn
{
	int seq;
	int ack;
};
void main()
{
  int sender,len,wind,j,l,k,c,i,r;
  struct ackn a;
   char buffer[1024];
   struct packet p[25];
  struct sockaddr_in receiver;
  sender=socket(AF_INET,SOCK_STREAM,0);
  receiver.sin_family=AF_INET;
  receiver.sin_port=htons(2069);
  receiver.sin_addr.s_addr=inet_addr("192.168.1.19");
   connect(sender,(struct sockaddr*)&receiver,sizeof(receiver));
  send(sender,"hai",strlen("hai"),0);
 
  i=read(sender,buffer,1024);
  buffer[i]='\0';
  printf("Received %s\n",buffer);
  
j=1;
l=1;
k=1;

printf("Sending frame \nNo: of frames=8\nWindow size=4\n");
while(j<=8)
{  printf("Enter frame data");
   scanf("%d",&p[j].data);
     p[j].seq=j;
	j++;
		
} 
while(l<=4)
{	send(sender,(char*)&p[l],sizeof(p[l]),0);
	printf("sending packet with data %d and seq no %d\n",p[l].data,p[l].seq);
	l++;
}
c=0;
n=8;
while(c<8)
{	        
	   r=read(sender,(char *)&a,sizeof(a));
	   if (a.ack==1)
	  {	c=c+1;
		printf("received ack for packet %d\n",a.seq);
	
                if(l<=8)
		{printf("sending packet with data %d and seq no %d\n",p[l].data,p[l].seq);
		send(sender,(char*)&p[l],sizeof(p[l]),0);
		l++;}
	   }
	   else if (a.ack==-1)
		{	printf("\n\ntime expired for packet %d\n",a.seq);
			printf("resending packet with data %d and seq no %d\n",p		[a.seq].data,a.seq);
				send(sender,(char*)&p[a.seq],sizeof(p[a.seq]),0);
				
			}
               
	
}

close(sender);
}

		
Receiver Program
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include <arpa/inet.h>
struct packet
{	int data;
	int seq;
};
struct ackn
{
	int seq;
	int ack;
};
void main()
{	int receiver,sender,len,c,t,wind,j,l,k,r,ran,f,i,n;
  	int opt=1;
	struct ackn a[20];
 	char buffer[1024];
   	struct packet p[25];
  	struct sockaddr_in senderadd,recvadr;
 	receiver=socket(AF_INET,SOCK_STREAM,0);	
	recvadr.sin_family=AF_INET;
 	 recvadr.sin_port=htons(2069);
 	 recvadr.sin_addr.s_addr=inet_addr("192.168.1.19");
	setsockopt(receiver, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt));
	if (bind(receiver,(struct sockaddr*)&recvadr,sizeof(recvadr))<0)
               printf("Not Connected\n");
	listen(receiver,3);
         sender=accept(receiver,(struct sockaddr*)&senderadd,&len);	
 	i=read(sender,buffer,1024); 
	buffer[i]='\0';
	printf("Received %s\n",buffer);
  	send(sender,"hello",strlen("hello"),0);
	j=1;
	k=1;
        c=0;
	while(j<=4)
	{       r=read(sender,(char *)&p[j],sizeof(p[j]));
		j++;
	}
        t=4;
	j=1;
	n=8;
	while(c<8)
	{       
		ran=rand()%3;
		if(ran==0)
          	{	a[j].ack=-1;
			a[j].seq=p[j].seq;
		}
		else{ a[j].ack=1;
			a[j].seq=p[j].seq;
		}
                
                if(a[j].ack==1)
                {  printf("Received Packet with data %d and seq %d\n",p[j].data,p[j].seq);
			send(sender,(char*)&a[j],sizeof(a[j]),0);c++;j++;
		 
		
                  }
		else
		{   send(sender,(char*)&a[j],sizeof(a[j]),0);
                         printf("\n\n");
		      j++;     n++;       
				
                 }
  	  		if(t< n)  
              { t++;read(sender,(char*)&p[t],sizeof(p[t])); }
            
		
	}	
		
		
close(receiver);
}

		


 

Result
This implementation of the program  helped us to develop network application programs and protocols.




© 2023 SphericalKat 
