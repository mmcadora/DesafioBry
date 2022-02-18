#ifndef __reader_h
#define __reader_h

#include <openssl/x509.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

class Reader
{

public:
	Reader(const char * keystore_path, const char * keystore_password);
	~Reader();
	
private:
	char * cert_pem;

};

#endif
