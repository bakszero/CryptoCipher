// Client side program

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <time.h>
#include <netinet/in.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
//Important for client
#include <netdb.h>

//Define the port no.
#define PORT 8034


//Set global public variables
long long int q = 29;
long long int alpha = 11;

//Set global int array holding values of q, alpha, Y_a
long long int arr[3]={0};

//Set global encoding
char encoding[67] = {' ','A','B','C','D','E','F','G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 
					 'O', 'P','Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ',','.', '?','0','1'
					 ,'2','3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
					 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
					 'w', 'x', 'y', 'z', '!'};     


//Error function
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
  

//Generalized caesar cipher encryption
long long int encrypt_cipher(long long int p, long long int k, long long int m)
{
	return ((p%m)+(k%m))%m;
}


//Generalized caesar cipher decryption
long long int decrypt_cipher(long long int c, long long int k, long long int m)
{
    return ((((c-k)%m) + m)%m);
}

//Finding index in array
int findIndex(char *array, int size, char target) 
{
    int i=0;
    while((i<size) && (array[i] != target))
    	i++;

    return (i<size) ? (i) : (-1);
}



//Modular exponentiation
long long int power(long long int b, long long int e, long long int m)
{  
    //base case
    if (m==1)
        return 0;

    long long int result = 1;
    b = b %m ;
    while (e > 0)
    {
    	if (e %2)
    		result = ((result*b) % m);
    	e = e >> 1;
    	b = ((b*b)%m);
    }

    return result;
    
}

int main(int argc, char const *argv[])
{
	//Get random integer X_a less than q, X_b less than q
	srand(time(NULL));
	long long int X_a = (long long int) rand() % q;


    //Compute public function Y_a
    long long int Y_a  = power (alpha, X_a, q);


    //Set the global values
    arr[0] = Y_a;
    arr[1] = q;
    arr[2] = alpha;

    printf("%lld %lld %lld %lld\n",q,alpha,X_a,Y_a );


    //Connection protocols
    //------------------------------------------------------------------

    struct sockaddr_in serv_addr;
    int sock = 0, valread;

    char *hello = "Hello from client";
    long long int buffer[3] = {0};

    struct hostent *server;


    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	    error("socket creation error.\n");


	bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    //bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(PORT);

  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("error connecting...");



    //------------------------------------------------------------------

	//Key exchange

	//Send key to B
    int n = write(sock , arr , sizeof(arr) );
    if (n< 0)
    	error("Error writing to socket.");


    //Receive key from B
    int x = read(sock, buffer, sizeof(buffer));
    if (x<0)
        error("Error reading from the client socket.");

    //printf("%s\n", buffer );
    printf("Y_b = %lld\n", buffer[0]);
    printf("q = %lld\n", buffer[1]);
    printf("alpha = %lld\n", buffer[2]);

    long long int Y_b = buffer[0];
   //------------------------------------------------------------------

    //Generate secret key by User A
    long long int k = power(Y_b, X_a,q);
    printf("k = %lld\n", k);



    //------------------------------------------------------------------
    //Send ciphertext from A
    //Encryption of text

    char mssg[] = "Meet me after the new year party at 10 P.M. night at IIIT felicity ground.";

    int len_mssg = strlen(mssg);
    printf("%d\n", len_mssg );
    int int_mssg[len_mssg];
    char encrypt_mssg[len_mssg];

    int i = 0,j=0;

    //Encode
    for (i=0; i < len_mssg; i++)
    {
    	int_mssg[i] = findIndex(encoding, 67, mssg[i]);
    	printf("%c - %d\n", mssg[i], int_mssg[i] );
    }

    //Encrypt
    for (j=0; j < len_mssg; j++)
    {	
    	//printf("%lld\n", );
    	encrypt_mssg[j] =  encoding[encrypt_cipher(int_mssg[j], k , 67)];
    	printf("%c", encrypt_mssg[j] );
    }

    //------------------------------------------------------------------

    //Send the encrypted text

    //Send the length first, so that we can track it.
    long long int len_arr[1]={strlen(encrypt_mssg)};
    printf("size of encrypt_mssg %lld\n", len_arr[0] );
    int l= write(sock , len_arr, sizeof(len_arr));
    if (l< 0)
    	error("Error writing to socket.");
   
    l= write(sock , encrypt_mssg , sizeof(encrypt_mssg));
    if (l< 0)
    	error("Error writing to socket.");

    //------------------------------------------------------------------
    
    //Receive ciphertext from B
    
    int y;
    int recv_arr[1]={0};

    x = read(sock , recv_arr, sizeof(recv_arr));
    if (x<0)
        error("Error reading from the client socket.");

    printf("X %lld\n", recv_arr[0] );

    char cipherb[recv_arr[0]];
    while((y = read(sock , cipherb, (size_t) recv_arr[0]))>0)
    {
        cipherb[y] = '\0';
        //printf("%s\n", cipher );
    }

    //printf("%s\n", cipher);

    //Decrypt the cipher
    printf("strlen of ciphertext %d\n",strlen(cipherb) );
    char plain_cipher[strlen(cipherb)];
    for (j=0 ; j < strlen(cipherb); j++)
        plain_cipher[j]= encoding[decrypt_cipher(findIndex(encoding, 67, cipherb[j]), k , 67)];
    
    printf("plain %s\n", plain_cipher);
	


    return 0;


}