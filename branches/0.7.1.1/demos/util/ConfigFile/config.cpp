#include<xvr2/DebugConsole.h>
#include<xvr2/Console.h>
#include<xvr2/ConfigFile.h>
#include<xvr2/String.h>
#include<ostream>
#include<fstream>

using xvr2::Util::ConfigFile;
using xvr2::Console;
using xvr2::String;
using xvr2::TextOutput;

Console con;

class DebugFile : public TextOutput {
	protected:
		std::ofstream out;
		virtual void outputMethod(const void *buff, UInt32 size){
			out.write((const char *)buff, size);
			out.flush();
		}
	public:
		DebugFile(String fname){
			out.open(fname.toCharPtr());
		}
		~DebugFile(){
			out.close();
		}
};

int main(){
	DebugFile df("debug.log");
	xvr2::debugConsole.setOutput(&df);
	ConfigFile cfg("config.cfg");
	cfg.parse();
	con << "##### Variables obtained from configuration file:\n";
	con << "PARAM_IPADDRESS: " << cfg.getStrValue("PARAM_IPADDRESS") << "\n";
	con << "PARAM_NUM:       " << cfg.getIntValue("PARAM_NUM") << "\n";
	con << "PARAM_X:         " << cfg.getStrValue("PARAM_X") << "\n";
	con << "PARAM_STRING:    " << cfg.getStrValue("PARAM_STRING") << "\n";
	return 0;
}
