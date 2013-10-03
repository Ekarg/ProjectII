#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define MAX_USERNAME 16
#define MAX_MSG 512

enum Msg_Type{
  JOIN=2,
  SEND=4,
  FWD=3
}msgt;

enum Att_Type{
  USERNAME=2,
  MSG=4,
  REASON=1,
  CLIENT_COUNT=3
}attt;


struct attr_hdr
{
  unsigned short  length;        
  unsigned short  type;
};

struct msg_hdr
{
  unsigned short  length;
  unsigned short  type :7;    
  unsigned short  vrsn :9;
};

struct pay_ld
{
  struct attr_hdr a_h;
  char *msg;
};
struct sbcp_msg 
{
  struct msg_hdr m_h;
  struct pay_ld* pld;
  int n_plds;
  int size;
  char* current;
  char* buffer;
};
struct list{
  int id;
  char userid[17];
  struct list* next;
};

extern struct list* userlist;
extern int MAX_COUNT;

struct list* initlist();
void addlist(int ,char* userid,struct list* );
struct list* deletelist(int ,struct list* );
int searchlist(int ,struct list*,char* );
void printlist(struct list* );
int list_size(struct list*);
int check_list(struct list*,char*);

void getaddress( char* , char* ,  struct addrinfo* , struct addrinfo**);
void printsockaddr(struct sockaddr_in* );
void InitAddress (char* , unsigned int , struct addrinfo *);

// ...sbcp.c
void mk_sbcp_hdr(unsigned int ,struct sbcp_msg* ,int );
void mk_sbcp_pyld(unsigned int ,int , char* ,struct sbcp_msg* ,int );
void print_sbcp(struct sbcp_msg* );
void encd_sbcp_msg(struct sbcp_msg* );
void decd_sbcp_hdr(char* ,struct sbcp_msg* );
void decd_sbcp_payld(char* ,struct sbcp_msg* ,int );
int recvhdr(int ,struct sbcp_msg* );
int recvpld(char*,int ,struct sbcp_msg* );

// ...server.c
void mk_fwd_pkt(char* ,char* ,struct sbcp_msg* );
int open_join_pkt(char* , struct sbcp_msg* );
int open_send_pkt(char* , struct sbcp_msg* );
int handle_new_cnt(int , fd_set ,int *);
int handle_old_cnt(int , fd_set ,int,int );


