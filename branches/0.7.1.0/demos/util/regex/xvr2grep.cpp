#include<xvr2/Regex.h>
#include<iostream>

xvr2::Util::Regex *regexp;

void usage();
void grep(FILE *f, bool show, const char *fname);
void grep(const char *fname, bool show);

void usage(){
	using namespace std;
	cout << "Usage:" << endl;
	cout << "xvr2grep <PATTERN> [FILE1] [FILE2]...." << endl;
}


void grep(const char *fname, bool show){
	FILE *f;
	f = fopen(fname, "r");
	if(f != NULL){
		grep(f, show, fname);
		fclose(f);
	}
}

void grep(FILE *f, bool show, const char *fname){
	using namespace std;
	char *buffer;
	int linenum = 1;
	buffer = new char[16384];
	while(fgets(buffer, 16384, f)){
		if(regexp->matches(buffer)){
			if(show)
				cout << fname << ":";
			cout << linenum << ":" << buffer;
			cout.flush();
		}
		linenum++;
	}
	xvr2::xvr2_delete_array(buffer);
}

int main(int argc, char *argv[]){
	using namespace xvr2;
	int numfiles, i;
	if(argc < 2){
		usage();
		return 1;
	}
	numfiles = argc - 2;
	regexp = new Util::Regex(argv[1]);
	if(numfiles > 0){
		if(numfiles == 1)
			grep(argv[2], false);
		else{
			for(i = 0; i < numfiles; i++){
				grep(argv[2 + i], true);
			}
		}
	}
	else{
		grep(stdin, false, 0);
	}
	xvr2_delete(regexp);
	return 0;
}
