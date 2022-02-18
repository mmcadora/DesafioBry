#include "config/certificate_config.h"
#include "/home/noc/DesafioBRy/test-cert-test-main/desafio_bry/include/reader.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <openssl/pem.h>
#include <openssl/evp.h>

using std::cout;
using std::endl;

int main(int argc, char ** argv)
{
	// Executar a leitura dos certificados com caminho enviado nos argumentos da execução da aplicacao
	if(argc == 2){
		cout <<"---- Iniciando execução da aplicação com os caminhos enviados por argumentos ----" << endl;
		Reader * cert_reader = new Reader(argv[0], argv[1]);
	} else {
		cout <<"---- Iniciando execução da aplicação com os certificados inclusos no projeto ----" << endl;
		//Executa usando os certificados na pasta Resources caso não sejam enviados os 2 argumentos com o caminho esperados
		Reader * cert_reader = new Reader(VERISIGN_CERT_LOCATION, BRY_CERT_LOCATION);
	}
}
