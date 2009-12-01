#include<xvr2.h>

using namespace xvr2;

Console con;

int main(){
	Net::SSLContext ctx2;
	con << "Reading RSA private key with passphrase...\n";
	ctx2.setPassphrase("xvr2");
	ctx2.pemCertificateChainFile("req.pem");
	ctx2.privateKeyfile("key.pem");
	ctx2.loadVerifyLocations("req.pem", ".");
	con << "Verifying keyfiles...\n";
	if(ctx2.privateKeyIsValid()){
		con << "ctx2: valid\n";
	}
	else{
		con << "ctx2: invalid\n";
	}
	return 0;
}
