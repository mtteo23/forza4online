#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


using namespace std;
/*
int CreateSocket(const string& host, const string& port) {
    struct addrinfo hints, *res;
    int sockfd;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host.c_str(), port.c_str(), &hints, &res) != 0) {
        cerr << "getaddrinfo() failed" << endl;
        exit(EXIT_FAILURE);
    }

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0) {
        cerr << "Socket creation failed" << endl;
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
        cerr << "Connection failed" << endl;
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);
    return sockfd;
}

string invia(int mossa, string host){
	const string port = "80";  // HTTP uses port 80
	
	// Create and connect the socket
    int sockfd = CreateSocket(host, port);
    
	string tmp="";
	tmp+=(char) '0'+mossa;
	tmp+="\n";
	
    send(sockfd, tmp.c_str(), tmp.length(), 0);
    
    // Receive and print the response
    char buffer[4096]={0};
    int bytes;
	string response="";
    while ((bytes = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        response+=buffer;
    }

    // Clean up
    close(sockfd);
    
    return response;
}
//*/
void inizializza(int listaMosse[6*7], int matrice[6][7], char schermo[6+1][7*2+2])
{
	for(int i=0; i<6*7; i++)
		listaMosse[i]=0;
		
	for(int i=0; i<6; i++)
	{
		for(int j=0; j<7; j++)
		{
			matrice[i][j]=0;
		}
	}
	
	for(int i=0; i<6+1; i++)
	{
		for(int j=0; j<7*2+2; j++)
		{
			schermo[i][j]=' ';
		}
	}
	for(int i=0; i<7; i++)
		schermo[6][i*2+1]='1'+i;
	
	for(int i=0; i<6; i++)
	{
		schermo[i][0]='|';
		schermo[i][7*2+1]='|';
	}
}

void aggiorna(char schermo[6+1][7*2+2], int matrice[6][7])
{
	char simbolo[3]={' ', 'X', 'O'};
	for(int i=0; i<6; i++)
	{
		for(int j=0; j<7; j++)
		{
			schermo[i][j*2+1]=simbolo[matrice[i][j]];
		}
	}
}

void aggiungi(int matrice[6][7], int mossa, int turno)
{
	int i=6;
	while(matrice[i][mossa]!=0)
		i--;
		
	matrice[i][mossa]=2-turno%2;
}

void stampa(char schermo[6+1][7*2+2])
{
	string tmp="";
	for(int i=0; i<6+1; i++)
	{
		for(int j=0; j<7*2+2; j++)
		{
			tmp+=schermo[i][j];
		}
		tmp+='\n';
	}
	cout<<tmp;
}

int fine(int matrice[6][7])
{
	for(int i=0; i<7; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(matrice[i][j]!=0 &&
			   matrice[i][j+0]==matrice[i][j+1] &&
			   matrice[i][j+1]==matrice[i][j+2] &&
			   matrice[i][j+2]==matrice[i][j+3])
				return matrice[i][j];
		}
	}
	
	for(int i=0; i<6; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(matrice[j][i]!=0 &&
			   matrice[j+0][i]==matrice[j+1][i] &&
			   matrice[j+1][i]==matrice[j+2][i] &&
			   matrice[j+2][i]==matrice[j+3][i])
				return matrice[j][i];
		}
	}
	
	return 0;
}

void gioca()
{
	int mossa[6*7];
	int matrice[6][7];
	char schermo[6+1][7*2+2];
	int turno=0;
	bool giocatore;
	
	inizializza(mossa, matrice, schermo);
	
	while(!fine(matrice))
	{
		aggiorna(schermo, matrice);
		system("clear");
		cout<<"\n FORZA 4 ONLINE\n\n";
		if(turno%2==giocatore)
		{
			cout<<"Fai la tua mossa!\n";
			stampa(schermo);
			do{
				cout<<"Colonna da giocare: ";
				cin>>mossa[turno];
			}while(mossa[turno]<1 || mossa[turno]>7 || matrice[0][mossa[turno]]!=0);
			//invia mossa
		}
		else
		{
			cout<<"Aspetta la mossa dell'avversario\n";
			stampa(schermo);
			mossa[turno]=1;//ricevi mossa
		}
		aggiungi(matrice, mossa[turno]-1, turno);
		turno++;
	}
	
	system("clear");
	cout<<"\n FORZA 4 ONLINE\n\n";
	if(fine(matrice)%2==giocatore)
		cout<<"Complimenti, hai vinto!";
	else
		cout<<"Ritenta, sarai piu' fortunato";
	cout<<"\n";
	aggiorna(schermo, matrice);
	stampa(schermo);
}


int main()
{
	//connessione();
	gioca();
	return 0;
}

/*


using namespace std;

// Function to initialize OpenSSL
SSL_CTX* InitSSL() {
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
    const SSL_METHOD* method = TLS_client_method();
    SSL_CTX* ctx = SSL_CTX_new(method);
    if (!ctx) {
        cerr << "Unable to create SSL context" << endl;
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    return ctx;
}






*/
