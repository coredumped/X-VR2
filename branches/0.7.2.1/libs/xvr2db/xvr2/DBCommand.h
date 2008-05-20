/*
 * $Id$
 */

#ifndef __XVR2_DB_COMMAND_H__
#define __XVR2_DB_COMMAND_H__
#include<xvr2/DBConnection.h>
#include<xvr2/DBConnectionMT.h>
#include<xvr2/DBResultSet.h>

namespace xvr2 {
	namespace DB {
		class Command : public xvr2::Object {
			private:
				xvr2::StringBuffer real_cmd;
			protected:
				xvr2::DB::Connection *conn;
				Command();
			public:
				Command(xvr2::DB::Connection *c);
				Command(const xvr2::DB::Command &c);
				int exec();
				xvr2::DB::Command &operator<<(const xvr2::String &);
				xvr2::DB::Command &operator<<(const xvr2::StringBuffer &);
				xvr2::DB::Command &operator<<(const Command &);
		};
		
		class CommandMT : public xvr2::Object {
			private:
				xvr2::StringBuffer real_cmd;
			protected:
				xvr2::DB::ConnectionMT *conn;
				Command();
			public:
				CommandMT(xvr2::DB::Connection *c);
				CommandMT(const xvr2::DB::CommandMT &c);
				int exec();
				xvr2::DB::CommandMT &operator<<(const xvr2::String &);
				xvr2::DB::CommandMT &operator<<(const xvr2::StringBuffer &);
				xvr2::DB::CommandMT &operator<<(const xvr2::DB::CommandMT &);
		};
	}
}

#endif
