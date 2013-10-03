#include "master.h"

//making sbcp header
void mk_sbcp_hdr(unsigned int m_t,struct sbcp_msg* sb_ms,int length)
{
  sb_ms->m_h.vrsn = 3;
  sb_ms->m_h.type = m_t;
  sb_ms->m_h.length = length;
  sb_ms->buffer = (char*)calloc(length,sizeof(char));
  sb_ms->current =  sb_ms->buffer;
  
}


//making sbcp payload
void mk_sbcp_pyld(unsigned int a_t,int length, char* buffer,struct sbcp_msg* sb_ms,int pldnum)
{
  sb_ms->pld[pldnum].a_h.type = a_t;
  sb_ms->pld[pldnum].a_h.length = length;
  sb_ms->pld[pldnum].msg =(char*)calloc(length+1,sizeof(char));
  strncpy(sb_ms->pld[pldnum].msg,buffer,length);
  sb_ms->n_plds =pldnum+1;
}



//encoding the message to be sent to the client
void encd_sbcp_msg(struct sbcp_msg* sb_ms)
{
  int i,j;
  unsigned  int *temp1 =(unsigned int*)sb_ms->current;
  unsigned  int *temp2 =(unsigned  int*)(&sb_ms->m_h);
  
  *temp1 = htonl(*temp2);
  temp1++;
   
  sb_ms->current=(char*)temp1;
 
  for(i=0;i<sb_ms->n_plds;i++)
  {
      sb_ms->pld[i].a_h.length =sb_ms->pld[i].a_h.length+4;
      temp1 = (unsigned int*)sb_ms->current;
      *temp1 = htonl(*((unsigned int*)&sb_ms->pld[i].a_h));
      temp1++;
      sb_ms->current = (char*)temp1;
      sb_ms->pld[i].a_h.length =sb_ms->pld[i].a_h.length-4;
      char* tmp1 = sb_ms->pld[i].msg;
      for(j=0;j<sb_ms->pld[i].a_h.length;j++)
      {*sb_ms->current=*tmp1;sb_ms->current++;tmp1++;}
      
  }
}


//decoding the message to the client
void decd_sbcp_hdr(char* pkt,struct sbcp_msg* sb_ms)
{
  unsigned int v = ntohl(*((unsigned int*)pkt));
  sb_ms->m_h =*((struct msg_hdr*)&v);
  sb_ms->buffer = (char*)calloc(sb_ms->m_h.length,sizeof(char));
  sb_ms->current =  sb_ms->buffer;
}
void decd_sbcp_payld(char* pkt,struct sbcp_msg* sb_ms,int pldnum)
{
  int i;
  unsigned int v =ntohl(*((unsigned int*)pkt));
  sb_ms->pld[pldnum].a_h = *((struct attr_hdr*)&v);
  pkt+=4;
  
  sb_ms->pld[pldnum].a_h.length-=4;
  sb_ms->pld[pldnum].msg =(char*)calloc(sb_ms->pld[pldnum].a_h.length+1,sizeof(char));
  char* tmp=sb_ms->pld[pldnum].msg;
  for(i=0;i<sb_ms->pld[pldnum].a_h.length;i++)
  {     *tmp = *pkt; tmp++;pkt++;}
  *tmp ='\0';
  
}


//to print sbcp message
void print_sbcp(struct sbcp_msg* sb_ms)
{
  int i;
  printf("Printing SBCP Message\n");
  printf("Version\t:%d\n",sb_ms->m_h.vrsn);
  switch(sb_ms->m_h.type)
  {
    case JOIN: printf("Msg Type\t:JOIN\n");break;
    case SEND: printf("Msg Type\t:SEND\n");break;
    case FWD: printf("Msg Type\t:FWD\n");break;
  }
  printf("Msg Length\t:%d\n",sb_ms->m_h.length);
  for (i=0;i<sb_ms->n_plds;i++)
  {
    switch(sb_ms->pld[i].a_h.type)
    {
      case USERNAME: {
      printf("Att Type\t:USERNAME\n");
      break;
      }
      case MSG: {
      printf("Att Type\t:MSG\n");
      break;
      }
      case REASON: {
      printf("Att Type\t:REASON\n");
      break;
      }
      case CLIENT_COUNT: {                          
      printf("Att Type\t:CLIENT_COUNT\n");           
      break;
      }
      default:{
      printf("Att Type\t:unknown\n");
      break;
      }
    }   
    printf("pld Length\t:%d\n",sb_ms->pld[i].a_h.length);
    printf("Msg \t:%s\n",sb_ms->pld[i].msg);
  }

}
 

//receive header part from the socket
int recvhdr(int sockfd,struct sbcp_msg* sb_ms)
{
  char hdr[4];
  int flag,succ=-1;
 
      if( (flag = recv(sockfd,hdr,4*sizeof(char),0)) <0){ 
	succ=-1;
	perror("server:recving hdr");
      }else if(flag == 0){  
	 succ=0;
	 printf("connection closed"); 
      }else {
	decd_sbcp_hdr(hdr,sb_ms);
	if(sb_ms->m_h.vrsn == 3)                 
	  if(sb_ms->m_h.length <1024)       
		succ =1;
	
      }
  return(succ);
    
}



//receive payload part from the socket
int recvpld(char* pld,int sockfd,struct sbcp_msg* sb_ms)
{
  int fl1,succ=-1,HDLEN=4;
     if( (fl1 = recv(sockfd,pld,(sb_ms->m_h.length-HDLEN)*sizeof(char),0)) <0){
      succ=-1;
       perror("server:recving"); 
    } else if(fl1 == 0){  
     succ=0;
      printf("connection closed"); 
    }else {   
     
      succ=1; 
    }
   return(succ);
}
