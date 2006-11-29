/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include"_xvr2netClassNames.h"
#include<xvr2/Memory.h>
#include"X509.h"
#include<openssl/x509.h>

#ifndef X509_READ_BUFFER_SIZE
#define X509_READ_BUFFER_SIZE 1024
#endif

namespace xvr2 {
namespace Net {


	X509::X509(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_Net_X509);
#endif
		_startDate = 0;
		_endDate = 0;
		_issuer = 0;
		dont_free = false;
		idata = (::X509 *)X509_new();
	}
	X509::X509(void *x509_ptr){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_Net_X509);
#endif
		BIO *bio;
		dont_free = true;
		idata = x509_ptr;
		//Try to read the inputted X509 cert structure
		char *tmp;
		//Get Issuer
		tmp = X509_NAME_oneline(X509_get_issuer_name((::X509 *)idata), 0, 0);
		_issuer = new X509Issuer(tmp);
		Memory::freeBuffer((void **)&tmp);
		//Get subject
		tmp = X509_NAME_oneline(X509_get_subject_name((::X509 *)idata), 0, 0);
		_subject = new X509Subject(tmp);
		Memory::freeBuffer((void **)&tmp);
		//Get serial number
		BIGNUM *serialBN = ASN1_INTEGER_to_BN(X509_get_serialNumber((::X509 *)idata),NULL);
		tmp = BN_bn2hex(serialBN);
		_serial = tmp;
		BN_free(serialBN);
		Memory::freeBuffer((void **)&tmp);

		//Read subject hash
#if __WORDSIZE == 64 && defined(__x86_64__)
		_hash = (Int64)X509_subject_name_hash((::X509 *)idata);
#else
		_hash = (Int32)X509_subject_name_hash((::X509 *)idata);
#endif

		//Read not before
		bio = BIO_new(BIO_s_mem());
		BIO_reset(bio);
		ASN1_TIME_print(bio, X509_get_notBefore((::X509 *)idata));
		BIO_get_mem_data(bio, (char **)&tmp);
		_startDate = new Date("%b %d %H:%M:%S %Y GMT", tmp);
		//Read not after
		BIO_reset(bio);
		ASN1_TIME_print(bio, X509_get_notAfter((::X509 *)idata));
		_endDate = new Date("%b %d %H:%M:%S %Y GMT", tmp);
		BIO_free(bio);
#if __WORDSIZE == 64 && defined(__x86_64__)
		_version = (Int64)X509_get_version((::X509 *)idata);
#else
		_version = (UInt32)X509_get_version((::X509 *)idata);
#endif
	}
	X509::~X509(){
		if(!dont_free)
			X509_free((::X509 *)idata);
		if(_startDate)
			delete _startDate;
		if(_endDate)
			delete _endDate;
		if(_issuer)
			delete _issuer;
		if(_subject)
			delete _subject;
	}
	const X509Issuer &X509::issuer() const {
		return *_issuer;
	}
	const X509Subject &X509::subject() const {
		return *_subject;
	}
	const String &X509::serial() const {
		return _serial;
	}
	const String &X509::hash() const {
		return _hash;
	}
	const Date &X509::startDate() const {
		return *_startDate;
	}
	const Date &X509::endDate() const {
		return *_endDate;
	}
	const String &X509::version() const {
		return _version;
	}

};
};
