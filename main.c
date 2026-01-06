/******************************************************************************
Bank System

*******************************************************************************/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void _read(){
    
}

void _write(){
    
}

int static staticPayment(){
    static int solde = 0;
    solde-=3;
    return solde;
}
static int staticConsultationBank(){
    static int i = 0;
    return i++;
}

static int staticDrawBank(){
    static int i = 0;
    return i++;
}


char bufferNetwork[32];

void * serverHandle(void * args){
    int serverCPT = 0;
    int response = 0;
    init:
        if(serverCPT == 0){
            goto receive;
        }
    
    send:{
        serverCPT = response;
        sprintf(bufferNetwork, ":%d", serverCPT);
        printf("Server: RPC Object From: sent: %d\n", serverCPT);
        sleep(1);
    }
        
    
    receive:{
        printf("Server<<<<: %s\n", bufferNetwork);
        sscanf(bufferNetwork, ">%d", &serverCPT);
        printf("Server Received: %d\n", serverCPT);
        switch(serverCPT){
            case 0:
                printf("\033[35;1;4m");
                printf("Exec Object Payment()\n");
                response = staticPayment();
                printf("\033[0m");
                break;
            
            case 1:
                printf("\033[35;1;4m");
                printf("<Exec Object ConsultationBank()>\n");
                response = staticConsultationBank();
                printf("\033[0m");
                break;
            case 2:
                printf("\033[35;1;4m");
                printf("<Exec Object DrawBank()>\n");
                response = staticDrawBank();
                printf("\033[0m");
                break;
            default:
                printf("\033[35;1;4m");
                printf("<Exec Object <ResetSystem>()>\n");
                response = -100;
                printf("\033[0m");
                break;
        }
        printf("Server: RPC Server Object Executor\n");
    }
    //system("sleep 3");
    
    goto send;
    return NULL;
}

__attribute__((constructor)) static void init() {
    pthread_t server;
    pthread_create(&server, NULL, serverHandle, NULL);
    pthread_detach(server);
}

__attribute__((destructor)) static void deinit()  {

}


int main()
{
    int cpt = 0;
    srand(time(NULL));
  
    send:{
        cpt = rand() % 5;
        sprintf(bufferNetwork, ">%d", cpt);
        printf("\033[33;1;4m");
        printf("Client : write RPC Object: [Request] %s\n", bufferNetwork);
        printf("\033[0m");
        sleep(1);
    }
    
    
    receive:{
        //sleep(1);
        sscanf(bufferNetwork, ":%d", &cpt);
        printf("\033[31;1;4m");
        printf("Client Received: [Response] %d\n", cpt);
        if(cpt == -100){
            //goto error;
        }
        memset(bufferNetwork, 0, sizeof(bufferNetwork));
        printf("Client: read RPC Server Object Executor\n");
        printf("\033[0m");
    }
    if(cpt %40==0 ) {
        system("clear");
    }
    //system("sleep 3");
    //sleep(2);
    goto send;
    
    error:

    return 0;
}
