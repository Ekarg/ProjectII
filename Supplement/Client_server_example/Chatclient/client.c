#include "master.h"

int min(int , int );
void mk_join_pkt(char* usrname,struct sbcp_msg* sb_ms)
{
  int length = strlen(usrname)+8;
  unsigned int m_t = JOIN;
  unsigned int a_t = USERNAME;
  // Header
  mk_sbcp_hdr(m_t,sb_ms,length);
  // validate and encd 
  sb_ms->pld =(struct pay_ld*)calloc(1,sizeof(struct pay_ld));
  mk_sbcp_pyld(a_t,min(MAX_USERNAME,strlen(usrname)),usrname,sb_ms,0);
  //print
  //print_sbcp(sb_ms);
  //encd
  encd_sbcp_msg(sb_ms);
}
int open_fwd_pkt(char* pkt, struct sbcp_msg* sb_ms)
{
  int i;
  
  sb_ms->pld =(struct pay_ld*)calloc(2,sizeof(struct pay_ld));
  decd_sbcp_payld(pkt,sb_ms,0);
  
 
  pkt = pkt + sb_ms->pld[0].a_h.length+4;
  sb_ms->n_plds=1;
  if(sb_ms->m_h.length-sb_ms->pld[0].a_h.length-4>0)
  {
    decd_sbcp_payld(pkt,sb_ms,1);
    sb_ms->n_plds++;
  }
  
  // validate msg lengths
  for(i=0;i<sb_ms->n_plds;i++)
  {
    sb_ms->pld[0].a_h.length = min(MAX_USERNAME,sb_ms->pld[0].a_h.length);
    strncpy(sb_ms->pld[0].msg,sb_ms->pld[0].msg,sb_ms->pld[0].a_h.length );
    sb_ms->pld[1].a_h.length = min(MAX_MSG,sb_ms->pld[1].a_h.length);
    strncpy(sb_ms->pld[1].msg,sb_ms->pld[1].msg,sb_ms->pld[1].a_h.length );
  }
  
  //print_sbcp(sb_ms);
  
  if(sb_ms->n_plds==2) 
    if(sb_ms->pld[0].a_h.type == USERNAME && sb_ms->pld[1].a_h.type == MSG)
     return(1);
  else return(0);
}
void mk_send_pkt(char* msg,struct sbcp_msg* sb_ms)
{
  int length = strlen(msg)+8;
  unsigned int m_t = SEND;
  unsigned int a_t = MSG;
  // Header
  mk_sbcp_hdr(m_t,sb_ms,length);
  // payld
  sb_ms->pld =(struct pay_ld*)calloc(1,sizeof(struct pay_ld));
  // chk msg lngth
  mk_sbcp_pyld(a_t,min(MAX_MSG,strlen(msg)),msg,sb_ms,0);
  // print_sbcp(sb_ms);
  encd_sbcp_msg(sb_ms);
}
void mk_leave_pkt(struct sbcp_msg* sb_ms)
{
  int length = 4;
  unsigned int m_t =LEAVE;
  mk_sbcp_hdr(m_t,sb_ms,length);
  sb_ms->n_plds=0;
  encd_sbcp_msg(sb_ms);
  
}
void joincht(int sockfd, struct addrinfo* servinfo,char* usrname )
{
   struct sbcp_msg* sb_ms = (struct sbcp_msg*) calloc(1,sizeof(struct sbcp_msg));
   mk_join_pkt(usrname,sb_ms);
   if (connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        close(sockfd);
        perror("client: connect");
	exit(0);
   } else {
      if(send(sockfd,sb_ms->buffer,sb_ms->m_h.length*sizeof(char),0) >0);
	//printf("........connection done...");
   }
    
    free(sb_ms->buffer);
    free(sb_ms->pld->msg);
    free(sb_ms->pld);
    free (sb_ms);
}
int handle_srvr_msg(int sockfd)
{
   int clientfd,succ;
   struct sbcp_msg* sb_ms = (struct sbcp_msg*) calloc(1,sizeof(struct sbcp_msg));  
   char* pld,i;
   if((succ=recvhdr(sockfd,sb_ms))<=0)
   {  
     fprintf(stderr,"Invalid Version Type or Length");
   }else
   {
     
     /*if(sb_ms->m_h.vrsn==1) {*/
      switch(sb_ms->m_h.type)
      {
       case FWD:{
	    pld = (char*) calloc(sb_ms->m_h.length,sizeof(char));
	    if(recvpld(pld,sockfd,sb_ms))
	      if(open_fwd_pkt(pld,sb_ms))
		fprintf(stderr,"\n%s\t\t:%s\nYou\t\t:",sb_ms->pld[0].msg,sb_ms->pld[1].msg);    
		

	    for(i=0;i<sb_ms->n_plds;i++)
		  free(sb_ms->pld[i].msg);
	    free (sb_ms->pld);
	    free(pld); break;
	  }
       default:{ printf("unknown msg"); }
      }  
      free(sb_ms->buffer);      
    } 
    
    free(sb_ms);
    
    return(succ);
}
int handle_inp_msg(int sockfd,char* msg)
{
   int clientfd,succ,i;
   struct sbcp_msg* sb_ms = (struct sbcp_msg*) calloc(1,sizeof(struct sbcp_msg));  
   
   //fgets(msg,MAX_MSG,stdin);
   if(strcmp(msg,"LEAVE"))
   {
	  mk_send_pkt(msg,sb_ms);
	  send(sockfd,sb_ms->buffer,sb_ms->m_h.length*sizeof(char),0);
	 
   }
   else
   {
	  mk_leave_pkt(sb_ms);
	  send(sockfd,sb_ms->buffer,sb_ms->m_h.length*sizeof(char),0);
	  free(sb_ms->buffer);
	  free(sb_ms);
	  close(sockfd);
	  return(1);
   }
  free(sb_ms->buffer);
  for(i=0;i<sb_ms->n_plds;i++)
     free(sb_ms->pld[i].msg);
  free (sb_ms->pld);
  free(sb_ms);
  return(0);
}
int min(int a, int b)
{
  if(a>b) return(b);
  else return(a);
}