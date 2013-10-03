#include "master.h"

int min(int , int );

//making forward packet
void mk_fwd_pkt(char* usrname,char* msg,struct sbcp_msg* sb_ms)
{
  int length = strlen(usrname)+strlen(msg)+12;
  unsigned int m_t = FWD;
  unsigned int a_t = USERNAME;
  // Header
  mk_sbcp_hdr(m_t,sb_ms,length);
  // payld
  sb_ms->pld =(struct pay_ld*)calloc(2,sizeof(struct pay_ld));
  /// chk msg lngth
  mk_sbcp_pyld(a_t,min(MAX_USERNAME,strlen(usrname)),usrname,sb_ms,0);
  a_t = MSG;
  mk_sbcp_pyld(a_t,min(MAX_MSG,strlen(msg)),msg,sb_ms,1);
  //print
  //print_sbcp(sb_ms);
  encd_sbcp_msg(sb_ms);
}

//opening join packet
int open_join_pkt(char* pkt, struct sbcp_msg* sb_ms)
{
  sb_ms->pld =(struct pay_ld*)calloc(1,sizeof(struct pay_ld));
  decd_sbcp_payld(pkt,sb_ms,0);
  // chk msg lngth
  sb_ms->n_plds=1;
  sb_ms->pld[0].a_h.length = min(MAX_USERNAME,sb_ms->pld[0].a_h.length);
  int i = check_list(userlist,sb_ms->pld[0].msg);
  printf("/n got it %i /n",i);
  strncpy(sb_ms->pld[0].msg,sb_ms->pld[0].msg,sb_ms->pld[0].a_h.length );
  print_sbcp(sb_ms); 
  if((sb_ms->pld[0].a_h.type == USERNAME)&&(i==1)) return(1);
  else return(0);  
} 


//opening send packet
int open_send_pkt(char* pkt, struct sbcp_msg* sb_ms)
{
  sb_ms->pld =(struct pay_ld*)calloc(1,sizeof(struct pay_ld));
  decd_sbcp_payld(pkt,sb_ms,0);
  /// chk msg lngth
  sb_ms->n_plds=1;
  sb_ms->pld[0].a_h.length = min(MAX_MSG,sb_ms->pld[0].a_h.length);
  strncpy(sb_ms->pld[0].msg,sb_ms->pld[0].msg,sb_ms->pld[0].a_h.length );
  
  //print_sbcp(sb_ms);
  if(sb_ms->pld[0].a_h.type == MSG) return(1);
  else return(0);
}


//handling new connection
int handle_new_cnt(int sockfd, fd_set master,int *fdmax)
{
  int clientfd,succ=0;        
  struct sockaddr_in* clientinfo= (struct sockaddr_in*)calloc(1,sizeof(struct sockaddr_in));
  int addrlen = sizeof(struct sockaddr_in);
   
  if((clientfd = accept(sockfd,(struct sockaddr*)clientinfo,&addrlen)) == -1){
    close(sockfd);
    perror("server:accept");   
  }
  else {
    if (clientfd > *fdmax)  // keep track of the max
    *fdmax = clientfd;
    succ =1;       
  }   
  free(clientinfo); 
  if(succ) return(clientfd);
  else return(0);
}


//handling old connection
int handle_old_cnt(int sockfd, fd_set master,int fdmax,int waitid)
{
    int fd=0,succ;
    struct sbcp_msg* sb_ms = (struct sbcp_msg*) calloc(1,sizeof(struct sbcp_msg));
    char* pld,i;
    if((succ=recvhdr(sockfd,sb_ms)) <= 0)
    {
      printf("\n Invalid Version or Length or Msg\n");
    }
    else {  /*if(sb_ms->m_h.vrsn == 3)*/ 
	
      switch(sb_ms->m_h.type)
      {
	case JOIN:{                                                     //Join Case
	  if(list_size(userlist) < MAX_COUNT)
	  {
	    pld = (char*) calloc(1,(sb_ms->m_h.length)*sizeof(char));
	    if(recvpld(pld,sockfd,sb_ms)){
	      if(open_join_pkt(pld,sb_ms)){
                 addlist(sockfd,sb_ms->pld->msg,userlist); }
                 else{succ=0;}            }
     //add user
	    for(i=0;i<sb_ms->n_plds;i++)
		  free(sb_ms->pld[i].msg);
		free(sb_ms->pld);
		free(pld);
		printf("\nNumber of valid users\t:%d\n",list_size(userlist));
	  } else { succ =0;}
	  break;
	}
	case SEND:{                                                   //Send Case
	  pld = (char*) calloc(sb_ms->m_h.length,sizeof(char));
	  if(recvpld(pld,sockfd,sb_ms))
	    if(open_send_pkt(pld,sb_ms))
	    {  
	      print_sbcp(sb_ms);
	      char usrname[17]; 
		  char unknwn[17];                    
	      if( searchlist(sockfd,userlist,usrname))
	      {
	      
		struct sbcp_msg* sb_ms_fwd = (struct sbcp_msg*) calloc(1,sizeof(struct sbcp_msg));
		mk_fwd_pkt(usrname,sb_ms->pld->msg,sb_ms_fwd);
		for(fd =0;fd <=fdmax;fd++)
		  if(FD_ISSET(fd,&master))
		    if(fd !=waitid && fd != sockfd)
		      if(searchlist(fd,userlist,unknwn))
		     send(fd,sb_ms_fwd->buffer,sb_ms_fwd->m_h.length*sizeof(char),0);
	      
		    print_sbcp(sb_ms_fwd);
		    free(sb_ms_fwd->buffer); 
		    for(i=0;i<sb_ms_fwd->n_plds;i++)
		      free(sb_ms_fwd->pld[i].msg);
		    free(sb_ms_fwd->pld);
		    free(sb_ms_fwd); 
	      }
	    }
	    
	    for(i=0;i<sb_ms->n_plds;i++)
		  free(sb_ms->pld[i].msg);
	    free(sb_ms->pld);
	    free(pld); break;
	}
	
	default:{printf("\n Invalid Msg Type");break;}
      } // end switch
      free(sb_ms->buffer);       
    } 
    
    
    free(sb_ms);  
    return(succ);
}


int min(int a, int b)
{
  if(a>b) return(b);
  else return(a);
}
