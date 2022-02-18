#include "/home/noc/DesafioBRy/test-cert-test-main/desafio_bry/include/reader.h"
#include <openssl/pem.h>
#include <openssl/x509.h>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

Reader::Reader(const char *cert_path1, const char *cert_path2)
{
	// Para armazenar os streams e certificados instanciados, respectivamente
	FILE *fpVerisign;
	FILE *fpBRy;
	X509 *certVerisign;
	X509 *certBRy;

	OpenSSL_add_all_algorithms();

	// Lendo os .cers e instanciando um object certificado da biblioteca openssl para cada um

	std::cout << "Lendo o certificado da Verisign..." << std::endl;
	if (!(fpVerisign = fopen(cert_path1, "rb")))
	{
		std::cout << "Certificado da Verisign nao encontrado" << std::endl;
		exit(1);
	}

	std::cout << "Lendo o certificado da BRy..." << std::endl;
	if (!(fpBRy = fopen(cert_path2, "rb")))
	{
		std::cout << "Certificado da BRy nao encontrado" << std::endl;
		exit(1);
	}

	// Convertendo os certificados para o formato que permite a leitura dos atributos

	std::cout << "Efetuando conversao para X509 (.CER)..." << std::endl;
	certVerisign = d2i_X509_fp(fpVerisign, NULL);

	std::cout << "Efetuando conversao para X509 (.CRT)..." << std::endl;
	certBRy = PEM_read_X509(fpBRy, NULL, NULL, NULL);

	// Início da leitura dos atributos dos certificados - Primeiro Verisign, em seguida BRy

	cout << "----Inicio da Leitura dos Atributos - Certificado Verisign----" << endl;
	BIO *bio_out = BIO_new_fp(stdout, BIO_NOCLOSE);
	long l = X509_get_version(certVerisign);
	BIO_printf(bio_out, "Versao do Certificado: %ld\n", l + 1);

	ASN1_INTEGER *bs = X509_get_serialNumber(certVerisign);
	BIO_printf(bio_out, "Numero Serial: ");
	for (int i = 0; i < bs->length; i++)
	{
		BIO_printf(bio_out, "%02x", bs->data[i]);
	}
	BIO_printf(bio_out, "\n");

	BIO_printf(bio_out, "Imprimindo campo Subject: ");
	X509_NAME_print(bio_out, X509_get_subject_name(certVerisign), 0);
	BIO_printf(bio_out, "\n");

	BIO_printf(bio_out, "Imprimindo campo Issuer: ");
	X509_NAME_print(bio_out, X509_get_issuer_name(certVerisign), 0);
	BIO_printf(bio_out, "\n");

	BIO_printf(bio_out, "Imprimindo campo Valid From: ");
	ASN1_TIME_print(bio_out, X509_get_notBefore(certVerisign));
	BIO_printf(bio_out, "\n");

	BIO_printf(bio_out, "Imprimindo campo Valid Until: ");
	ASN1_TIME_print(bio_out, X509_get_notAfter(certVerisign));
	BIO_printf(bio_out, "\n");

	EVP_PKEY *pkey = X509_get_pubkey(certVerisign);
	BIO_printf(bio_out, "Imprimindo campo que contém a Chave Pública e o Modulus/Exponent: ");
	EVP_PKEY_print_public(bio_out, pkey, 0, NULL);
	EVP_PKEY_free(pkey);

	BIO_free(bio_out);

	cout << "----Inicio da Leitura dos Atributos - Certificado BRy ----" << endl;
	BIO *bio_out2 = BIO_new_fp(stdout, BIO_NOCLOSE);
	long l2 = X509_get_version(certBRy);
	BIO_printf(bio_out2, "Versao do Certificado: %ld\n", l2 + 1);

	ASN1_INTEGER *bs2 = X509_get_serialNumber(certBRy);
	BIO_printf(bio_out2, "Numero Serial: ");
	for (int i = 0; i < bs2->length; i++)
	{
		BIO_printf(bio_out2, "%02x", bs2->data[i]);
	}
	BIO_printf(bio_out2, "\n");

	BIO_printf(bio_out2, "Imprimindo campo Subject: ");
	X509_NAME_print(bio_out, X509_get_subject_name(certBRy), 0);
	BIO_printf(bio_out2, "\n");

	BIO_printf(bio_out2, "Imprimindo campo Issuer: ");
	X509_NAME_print(bio_out2, X509_get_issuer_name(certBRy), 0);
	BIO_printf(bio_out2, "\n");

	BIO_printf(bio_out2, "Imprimindo campo Valid From: ");
	ASN1_TIME_print(bio_out, X509_get_notBefore(certBRy));
	BIO_printf(bio_out2, "\n");

	BIO_printf(bio_out2, "Imprimindo campo Valid Until: ");
	ASN1_TIME_print(bio_out2, X509_get_notAfter(certBRy));
	BIO_printf(bio_out2, "\n");

	EVP_PKEY *pkey2 = X509_get_pubkey(certBRy);

	BIO_printf(bio_out2, "Imprimindo campo que contém a Chave Pública e o Modulus/Exponent: ");
	EVP_PKEY_print_public(bio_out2, pkey2, 0, NULL);
	EVP_PKEY_free(pkey2);

	BIO_free(bio_out2);

	// Finalização da execução da aplicação
	cout << "---- Fim da execução da aplicação ----" << endl;
	exit(0);
}
