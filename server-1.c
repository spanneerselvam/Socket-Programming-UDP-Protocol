
/********************
 * COEN 146, UDP example, server
 ********************/
#include "tfv1.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

/********************
 * main
 ********************/
int main (int argc, char *argv[])
{
	PACKET pac,rec;
	size_t data,n;
	int sock, nBytes;
	char buffer[10];
	char name[10];
	char fileName[1024];
	FILE *f2;
	struct sockaddr_in serverAddr, clientAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size, client_addr_size;
	
	int i;

    if (argc != 2)
    {
        printf ("need the port number\n");
        return 1;
    }

	// init 
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons ((short)atoi (argv[1]));
	serverAddr.sin_addr.s_addr = htonl (INADDR_ANY);
	memset ((char *)serverAddr.sin_zero, '\0', sizeof (serverAddr.sin_zero));  
	addr_size = sizeof (serverStorage);

	// create socket
	if ((sock = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf ("socket error\n");
		return 1;
	}


	// bind
	if (bind (sock, (struct sockaddr *)&serverAddr, sizeof (serverAddr)) != 0)
	{
		printf ("bind error\n");
		return 1;
	}


	if((n = recvfrom (sock, &rec, sizeof(PACKET), 0, (struct sockaddr *)&serverStorage, &addr_size)>0))
	{
		printf("%s", rec.data);
		sendto (sock, &rec, sizeof(PACKET), 0, (struct sockaddr *)&serverStorage, addr_size);
		fflush(stdout);
		f2 = fopen(rec.data, "wb");
		fclose(f2);
	}

	while ((1))
	{
		memset(pac.data,'\0',sizeof(pac.data));
		nBytes = recvfrom (sock, &pac, sizeof(PACKET), 0, (struct sockaddr *)&serverStorage, &addr_size);
		f2 = fopen(rec.data, "a");
		printf("%s", pac.data);
		fwrite (pac.data,strlen(pac.data),1,f2); 
		fflush(stdout);


		
		sendto (sock, &pac, sizeof(PACKET), 0, (struct sockaddr *)&serverStorage, addr_size);
fclose(f2);
	}
		
fclose(f2);
	return 0;
}
