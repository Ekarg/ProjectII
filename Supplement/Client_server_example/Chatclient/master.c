#include "master.h"

int main(int argc, char* argv[])
{
    int sockfd, newsock,status,yes=1,fdmax,flag;
    unsigned int port ;
    struct addrinfo hints;
    struct addrinfo *servinfo,*p;  // will point to the results
    fd_set master,read_fd;
    
    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    FD_ZERO(&master);
    FD_ZERO(&read_fd);
    
    if (argc != 4) {
    printf("usage: ./client username serverip port\n");
    return 1;
    }
    port = atoi(argv[3]);
    printf("\nIP Entered\t:%s\nPort\t:%d\nUserID:%s\n",argv[2],port,argv[1]); 
    servinfo= (struct addrinfo*)calloc(1,sizeof(struct addrinfo));
    InitAddress (argv[2], port, servinfo);
   
    // make a socket:
    if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,servinfo->ai_protocol)) == -1) {
        perror("client: socket");
	exit(0);
    }
    // local addresses are reused
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(0);
    }
    // connect 
    joincht(sockfd,servinfo,argv[1]);
    
    //sending data
    FD_SET(STDIN,&master);
    FD_SET(sockfd,&master);
    fdmax = sockfd;

    int exflag=0,cnt=0;
    char msg[MAX_MSG+1]; 
    fflush(stdin);
    fprintf(stderr,"You\t\t:");
    while(1){
      read_fd=master;
      if( select(fdmax+1,&read_fd,NULL,NULL,NULL) == -1){
	  perror("server:select");
	  exit(0);
      }
      if(FD_ISSET(sockfd,&read_fd)){
	   //server msg
	   if(!handle_srvr_msg(sockfd))
	   { 
	     close(sockfd);
	     exit(0);
	   } 	  
      }
      if(FD_ISSET(STDIN,&read_fd)){
	  // stdin msg
	  fgets(msg, MAX_MSG,stdin);
	  fprintf(stderr,"You\t\t:");
	  if(strlen(msg)<MAX_MSG && strlen(msg) >1)  msg[strlen(msg)-1]= '\0'; // removing the end \n character
	  exflag=handle_inp_msg(sockfd,msg);  	    	  
      }
      //Leave Msg
      if(exflag==1) break;
    }
    close(sockfd);
    //printsockaddr((struct sockaddr_in*)servinfo->ai_addr);
    freeaddrinfo(servinfo); // free the linked-list

}
void InitAddress (char* ip, unsigned int port, struct addrinfo *servinfo)
{
  servinfo->ai_flags = AI_PASSIVE;
  servinfo->ai_family = AF_INET;
  servinfo->ai_socktype = SOCK_STREAM;
  servinfo->ai_protocol =0;
  servinfo->ai_addrlen = sizeof(struct sockaddr_in);
  struct sockaddr_in* my_addr = (struct sockaddr_in*)calloc(1,sizeof(struct sockaddr_in));
  my_addr->sin_family = AF_INET;
  my_addr->sin_port = (unsigned short int)htons(port);     // short, network byte order
  my_addr->sin_addr.s_addr = inet_addr(ip);
  memset(my_addr->sin_zero, '\0', sizeof (my_addr->sin_zero));
  servinfo->ai_addr = (struct sockaddr*)my_addr;
  servinfo->ai_next =NULL;

}
void printsockaddr(struct sockaddr_in* ipv4)
{
     char ipstr[INET6_ADDRSTRLEN];
     printf("Family: %d\nPort: %i\n",ipv4->sin_family,ipv4->sin_port);
     inet_ntop(ipv4->sin_family, &(ipv4->sin_addr), ipstr, sizeof ipstr);
     printf("IPv4: %s\n",  ipstr);
   
}

