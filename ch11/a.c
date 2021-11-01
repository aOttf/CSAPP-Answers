#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int
main (int argc, char *argv[])
{
	struct addrinfo *p, *listp, hints;
	char buf[MAXLINE];
	int rc, flags;
	
	if(argc != 2)
	{fprintf(stderr,"Usage: %s <domain name>\n", argv[0])};
	
	/* Setup hints to zeros */
	memset(hints,0 , sizeof (struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
	if((rc = getaddrinfo(argv[1], NULL, &hints, &listp) != 0)){
	fprintf(stderr, "gedaddrinfo error");
	exit(1);
	}
	()
	flags = NI_NUMERICHOST;
	
	for(p = listp, p; p = p->ai_next){
		getnameinfo()
	}
	return 0;
}
