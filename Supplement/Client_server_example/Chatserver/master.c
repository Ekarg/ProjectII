#include "master.h"
struct list* userlist;
int MAX_COUNT;
int main(int argc, char* argv[])
{
    int sockfd, clientfd,status,yes=1,fdmax,p,fd,j;
    unsigned int port;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct sockaddr_in* clientinfo;  // will point to the results
    fd_set master,read_fd;
    
    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    FD_ZERO(&master);
    FD_ZERO(&read_fd);
    
    if (argc != 4) {
    printf("usage: ./server ip port clientcount\n");
    return 1;
    }
    
    port =atoi(argv[2]);
    printf("IP Entered,%s\n",argv[1]);                                
    servinfo= (struct addrinfo*)calloc(1,sizeof(struct addrinfo));
    InitAddress (argv[1], port, servinfo);
    
    MAX_COUNT = atoi(argv[3]);                               //Max number of clients
    
    // create userlist
    userlist = initlist();
     
    // make a socket:
    if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,servinfo->ai_protocol)) == -1) {
        perror("server: socket");
	exit(0);
    }
    // local addresses are reused
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    // binding to a port
    if (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        close(sockfd);
        perror("server: bind");
    }
    //listen
    if(listen(sockfd,MAX_COUNT)==-1){          
      close(sockfd);
      perror("server:listen");
    }

    FD_SET(sockfd,&master);
    fdmax = sockfd;
   
    while(1){   
      
      read_fd = master;
      if( select(fdmax+1,&read_fd,NULL,NULL,NULL) == -1){
	  perror("server:select");
	  exit(0);
      }
      for(p=0;p<=fdmax;p++)
      {
	
	if(FD_ISSET(p,&read_fd)){
	  if(p==sockfd){ // New connection
	      int clientfd = handle_new_cnt(p,master,&fdmax);  
	      if(clientfd)
	         FD_SET(clientfd,&master);
	   } else {// received some msg from old connection
	      if(!handle_old_cnt(p,master,fdmax,sockfd))
	      {
		char usrname[17];
		if(searchlist(p,userlist,usrname)) userlist=deletelist(p,userlist);;      //closing the user incase he has quit
		printf("\nNumber of valid users\t:%d\n",list_size(userlist));
		close(p);
		FD_CLR(p,&master);
	      }
	       
	  }
	 } //data handling done
	}//data for particular p over
      }// infinite loop 
    
    
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
