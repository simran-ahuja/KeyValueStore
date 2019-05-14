//Radhe Shyam Lodhi
//20144069
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <sys/fcntl.h>
#include <netdb.h>
int main(int argc,char *argv[])
{
   struct hostent *hp ;
   char *hostname;
   char *final;
   int clientsocket = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
   struct sockaddr_in server,client;
   server.sin_family = AF_INET;
   hp = gethostbyname(argv[1]);
   server.sin_addr.s_addr = *((unsigned long *)(hp->h_addr_list[0]));
   server.sin_port = htons(atoi(argv[2]));
   memset(server.sin_zero,'\0',sizeof(server.sin_zero));
   connect(clientsocket,(struct sockaddr *)&server,sizeof(server));
   char str[1000];
   if(strcmp(argv[3],"GET")==0)
   {
   		sprintf(str,"GET /%s HTTP/1.0\r\nHost:%s\r\n\r\n",argv[4],hp->h_name);
   		int strl = strlen(str);
   		send(clientsocket,str,strl,0);
    	   char input[100000];
   		int recmessage = recv(clientsocket,input,100000,0);
         
   		printf("%s\n",input);
   		close(clientsocket);
   		close(c);
   }
   else if(strcmp(argv[3],"PUT")==0)
   {
   	   FILE *fp = fopen(argv[4],"r");
   	   char file[100000];
   	   char ch;
   	   int k = 0;
   	   while(fscanf(fp,"%c",&ch)!=EOF)
   	   {
 		   	file[k++] = ch;
   	   }
   	   file[k]='\0';
   		sprintf(str,"PUT /%s HTTP/1.0\r\nHost:%s\r\n%s\r\n\r\n",argv[4],hp->h_name,file);
   		int strl = strlen(str);
   		send(clientsocket,str,strl,0);
    	   char input[100000];
         fclose(fp);
   		int recmessage = recv(clientsocket,input,100000,0);
   		printf("%s\n",input);
   		close(clientsocket);
   		close(c);
   }
   return 0;
}
