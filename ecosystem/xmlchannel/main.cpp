
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/poll.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <cstdio>

#include <errno.h>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <string>
#include <string.h>
#include <map>
#include <queue>
#include <vector>

#include "expat.h"
#include "logger.h"

using namespace std;

#define VERSION                 "3.00 unix"
#define PORT                    2323
#define BUFF_SIZE               1024


int MAXCLIENTS = 255;                   ///< That many clients can connect to the server simultaneously
int maxclients;                         ///< That many clients are connectet at this moment (list might include holes, -1)
struct pollfd pollclient[4096];         ///< This array holds the file descriptiors to all connected clients
XML_Parser parser[4096];                ///< This array holds the XML parsers for all connected clients

queue<string> outqueue;
Logger *log;

void XMLCALL xmlStart(void *data, const char *el, const char **attr) {
  map<string,string> myattr ;
  
  for (int i = 0; attr[i]; i += 2) {
    myattr[ attr[i] ] = attr[i+1] ;
  }
  
  if (!strcmp(el, "welcome")) { // no need to send welcome to all subscribers
    return; 
  }
  
  map<string,string>::iterator it;
  stringstream s;
  s << "<" << el << " ";
  for (it=myattr.begin(); it!=myattr.end(); it++) {
    pair<string, string> p = *it;
    s << p.first << "=\"" << p.second << "\" ";
  }
  s << " />" << ends; 
  outqueue.push(s.str());
  //  log->add(s.str());
}

void receive(int timeout) {
  int nready = poll(pollclient, maxclients+1, timeout);

  if (pollclient[0].revents & POLLRDNORM) { // new client connection
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr);
    int connfd = accept(pollclient[0].fd, (sockaddr*)&cliaddr, &clilen);

    int i = 0; // falsches scope fuer i :( acc. to stevens-unp ok
    for (i = 1; i < MAXCLIENTS; i++) {
      if (pollclient[i].fd < 0) {  // noch frei, also:
	pollclient[i].fd = connfd; // den nehmen wir
 	ostringstream os; 
 	os << "Client #" << i << " connected from " << inet_ntoa(cliaddr.sin_addr);
 	log->add(os.str());   
	
	string s = "<welcome source=\"XMLChannel\">\n\r";
	int ret = send(pollclient[i].fd, s.c_str(), strlen(s.c_str()), MSG_DONTWAIT);
	if (ret < 0) { // something went wrong
	  ostringstream os; 
	  os << "Client #" << i << " Transmit error. Closing connection for this client.";
	  log->add(os.str());   
	  close(pollclient[i].fd);
	  pollclient[i].fd = -1;
	  XML_ParserFree(parser[i]);
	}
	
	// create an xml parser object
	parser[i] = XML_ParserCreate(NULL);       
	XML_SetStartElementHandler(parser[i], xmlStart);


	break; 
      }
    }
    if (i == MAXCLIENTS) {
      log->add("Too many clients");
      return;
    }
    pollclient[i].events = POLLRDNORM;
    if (i > maxclients) { maxclients = i; }

    // folgende 3 zeilen bei kuehlerem wetter nochmals genau anschauen. 
    if (--nready <= 0) { // fertig mit adden neuer verbindungen (data rec. naechstens mal ...ok gem stevens-unp)
      return;            // problem: es findet kein receive auf den gepollten sockets statt so
    }
  }
  for (int i = 1; i <= maxclients; i++) {
    int sockfd;
    if ((sockfd = pollclient[i].fd) < 0) continue;
    if (pollclient[i].revents & (POLLRDNORM | POLLERR)) {
      const int MAXLINE = 2048;
      char line[MAXLINE];
      bzero(line, MAXLINE); // not strictly encessary unless line is used as a char* later on. expat does not.
      int n = 0;
      if ((n = read(sockfd, line, MAXLINE)) < 0) { // stevens-unp uses 'readline' instead
	if (errno == ECONNRESET) { // reset by peer
	  close(sockfd);
	  pollclient[i].fd = -1;
	  XML_ParserFree(parser[i]);
	  ostringstream os; 
	  os << "Client #" << i << " reset by peer";
	  log->add(os.str());   
	} else {
	  ostringstream os; 
	  os << "Client #" << i << ": read error";
	  log->add(os.str());   
	}	  
      } else if (n == 0) { // closed by client
	close(sockfd);
	pollclient[i].fd = -1;
	  XML_ParserFree(parser[i]);
	ostringstream os; 
	os << "Client #" << i << " closed connection";
	log->add(os.str());   
      } else {
	// to parse
	//log->add(line);
	int ret = XML_Parse(parser[i], line, n, false);
	if (ret < 0) { // something went wrong
	  ostringstream os; 
	  os << "Client #" << i << " XML Parse error. Closing connection for this client.";
	  log->add(os.str());   
	  close(sockfd);
	  pollclient[i].fd = -1;
	  XML_ParserFree(parser[i]);
	}
      }
      if (--nready <= 0) break; 
    }           
  }       
}


int main(int argc, char* argv[]) {
  /*
  pid_t pid;
  if ((pid=fork()) < 0) {
    exit(-1);
  } else if (pid != 0) {
    exit(0);
  }
  setsid();

  chdir("/");
  umask(0);
  
  freopen( "/dev/null", "r", stdin);
  freopen( "/dev/null", "w", stdout);
  freopen( "/dev/null", "w", stderr);
*/
  log = new Logger();
  
  ostringstream os1; 
  os1 << "PEDSIM XML Channel Version " << VERSION << ends;
  log->add(os1.str());   
  ostringstream os2; 
  os2 << "Listening on TCP Port " << PORT << " for incoming connections" << ends;
  log->add(os2.str());   
  
  struct rlimit rlim;
  getrlimit(RLIMIT_NOFILE, &rlim);
  ostringstream os; 
  os << "Available File descriptors: soft " << rlim.rlim_cur << ", hard " << rlim.rlim_max << ends;
  log->add(os.str());   

  if (rlim.rlim_cur <= 4096) {
    MAXCLIENTS = rlim.rlim_cur;
  }
  

  struct sockaddr_in servaddr;
  int listenfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  int reuse = 1;         
  setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

  bind(listenfd, (sockaddr*)&servaddr, sizeof(servaddr));
  listen(listenfd, 128);

  pollclient[0].fd = listenfd;
  pollclient[0].events = POLLRDNORM;
  for (int i=1; i<MAXCLIENTS; i++) {
    pollclient[i].fd = -1; // -1 indicates available entry
  }
  maxclients = 0;

  while(1) {
    receive(100);
 
    if (!outqueue.empty()) {
      string s = (string)outqueue.front();
      outqueue.pop();

      for (int i = 1; i <= maxclients; i++) {
	if ((pollclient[i].fd) != -1) {
	         
	   int ret = send(pollclient[i].fd, s.c_str(), strlen(s.c_str()), MSG_DONTWAIT);	   
	   if (ret < 0) { // something went wrong
	      ostringstream os; 
	      os << "Client #" << i << " Transmit error. Closing connection for this client.";
	      log->add(os.str());   
	      close(pollclient[i].fd);
	      pollclient[i].fd = -1;
	      XML_ParserFree(parser[i]);
	   }
	}
      }
    }
 }

  return 0;
}

