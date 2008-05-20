/* $Id$ */
#include"DBCommand.h"

namespace xvr2 {
	namespace DB {
	
		Command::Command(){
			conn = 0;
			real_cmd.clear();
		}
		
		Command::Command(xvr2::DB::Connection *c){
			conn = c;
			real_cmd.clear();
		}
		
		Command::Command(const xvr2::DB::Command &c){
			conn = c.conn;
			real_cmd << c.real_cmd.toString();
		}
	
		int Command::exec(){
			int retval = -1;
			retval = conn->execCommand(real_cmd);
			real_cmd.clear();
			return retval;
		}
		
		Command &Command::operator<<(const xvr2::String &s){
			real_cmd << s;
			return *this;
		}
		
		Command &Command::operator<<(const xvr2::StringBuffer &s){
			real_cmd << s.toString();
			return *this;
		}
		
		Command &Command::operator<<(const Command &c){
			real_cmd << c.real_cmd.toString();
			return *this;
		}
		
		
		CommandMT::CommandMT(){
			conn = 0;
			real_cmd.clear();
		}
		
		CommandMT::CommandMT(xvr2::DB::Connection *c){
			conn = c;
			real_cmd.clear();
		}
		
		CommandMT::CommandMT(const xvr2::DB::CommandMT &c){
			conn = c.conn;
			real_cmd << c.real_cmd.toString();
		}
	
		int CommandMT::exec(){
			int retval = -1;
			retval = conn->execCommand(real_cmd);
			real_cmd.clear();
			return retval;
		}
		
		CommandMT &CommandMT::operator<<(const xvr2::String &s){
			real_cmd << s;
			return *this;
		}
		
		CommandMT &CommandMT::operator<<(const xvr2::StringBuffer &s){
			real_cmd << s.toString();
			return *this;
		}
		
		CommandMT &CommandMT::operator<<(const CommandMT &c){
			real_cmd << c.real_cmd.toString();
			return *this;
		}
	}
}
