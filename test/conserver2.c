//Radhe Shyam Lodhi
//20144069
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<pthread.h>
void *receive(void *args)
{
                 char str[1000];
                 int clientsock = *(int *)args;
                printf("Client Connected\n");
                printf("%d\n",clientsock);
                sleep(5);
                int recvmessage = recv(clientsock,str,1000,0);
                if(recvmessage < 0)
                {
                    printf("Error receiving the message\n");
                    return ;
                }
                    if(str[0]=='G' && str[1]=='E' && str[2]=='T')
                    {
                        int i;
                        char filename[100000];
                        int k = 0;
                       
                        for(i=5;str[i]!=32;i++)
                        {
                            filename[k++] = str[i];
                        }
                        filename[k]='\0';
                        
                        if(access(filename,0)!=0)
                        {
                            char reply[10000];
                            strcpy(reply,"HTTP/1.1 404 NOT FOUND");
                            send(clientsock,reply,13,0); 
                            close(clientsock);      
                        }
                        else
                        {
                        FILE *fp = fopen(filename,"r");
                        char reply[100000];
                        int rlen = 0;
                        char ch;
                        while(fscanf(fp,"%c",&ch)!=EOF)
                        {
                            reply[rlen++] = ch;
                        }
                        reply[rlen] = '\0';
                        send(clientsock,reply,rlen,0); 
                        fclose(fp);
                        close(clientsock);  
                    } 
                  }
                    else 
                    {
                        int i;
                        char filename1[100000];
                        int k = 0;
                        for(i=5;str[i]!=32;i++)
                        {
                            filename1[k++] = str[i];
                        }
                        filename1[k++]='_';
                        filename1[k]='\0';
                       
                        i++;
                        i+=10;
                        FILE *fp1 = fopen(filename1,"w");
                        char ch;
                        for(;str[i]!=32;i++)
                        {
                            fprintf(fp1,"%c",str[i]);
                        }
                        fclose(fp1);
                        char reply[10000];
                        strcpy(reply,"HTTP/1.1 200 OK FILE CREATED");
                        int len = strlen(reply);
                        send(clientsock,reply,len,0); 
                        close(clientsock);
                    }  
                      
}
int main(int argc,char *argv[])
{
        pthread_t threads[100];
        int servsocket = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
        if(servsocket < 0)
        {
            printf("Error creating socket\n");
            return 0;
        }
        int clientsock;
        struct sockaddr_in server,client;
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(argv[1]);
        server.sin_port = htons(atoi(argv[2]));
        memset(server.sin_zero,'\0',sizeof(server.sin_zero));
        int b = bind(servsocket,(struct sockaddr *)&server,sizeof(server));
        if(b<0)
        {
            printf("Could not bind socket and port\n");
           return 0;
        }
        listen(servsocket,10);
        int k = 0;
        while(1)
        {
            
            int clength =  sizeof(client);
            clientsock = accept(servsocket,(struct sockaddr *)&client,&clength);
            if(clientsock<0)
            {
                printf("Could not accept client\n");
                return 0;
            }
            pthread_create(&threads[k],NULL,receive,(void *)&clientsock);   
            k++;
        }
        close(clientsock);
        close(servsocket);
        return 0;
}
