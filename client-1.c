/*****************************
 * COEN 146, UDP, client
 *****************************/
#include "tfv1.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/***********
 *  main
 ***********/
int main (int argc, char *argv[])
{
	PACKET pac,rec;
	int sock, portNum, nBytes;
	size_t data;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	FILE *f1;
	if (argc != 5)
	{
		printf ("Usage: %s <input file, output file,ip of server,server port> \n",argv[0]);
		return 1;
	} 

	// configure address
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons (atoi (argv[4]));
	if(inet_pton (AF_INET, argv[3], &serverAddr.sin_addr.s_addr) <=0)
	{
		printf("inet_pton error occurred\n");
		return 1;
	}
	memset (serverAddr.sin_zero, '\0', sizeof (serverAddr.sin_zero));  
	addr_size = sizeof serverAddr;
	
	/*Create UDP socket*/
	sock = socket (PF_INET, SOCK_DGRAM, 0);
	// input, send to server, receive it back, and output it
	f1 = fopen(argv[1], "r");
	if(f1 == NULL)
	{
		printf("can't open %s file \n", argv[1]);
		exit(0);
	}

	srand(time(NULL));
	int previous = rand() % 2;
	strncpy(rec.data, argv[2], sizeof(argv[2]));
	sendto (sock,&rec, sizeof(rec), 0, (struct sockaddr *)&serverAddr, addr_size);
	while (0 < (data =fread(buffer,1,10,f1)))

{
		strncpy(pac.data, buffer, 10);
		if(previous == 0)
		{
			pac.header.seq_ack = 1;
	
		}
		else
		{
			pac.header.seq_ack = 0;
		}
		previous = pac.header.seq_ack;

		sendto (sock,&pac, sizeof(PACKET), 0, (struct sockaddr *)&serverAddr, addr_size);
		nBytes = recvfrom (sock,&pac, sizeof(PACKET), 0, (struct sockaddr *)&serverAddr, &addr_size);
		memset(buffer, '\0', sizeof(buffer));

}
	fclose(f1);
	return 0;
}
