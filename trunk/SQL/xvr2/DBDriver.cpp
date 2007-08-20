/* $Id$ */
#include"Driver.h"


namespace xvr2 {
	namespace SQL {
		Driver::Driver(){
			conn_requires_lock = false;
			query_requires_lock = true;
			bulk_requires_specific_lock = true;
			resultset_requires_lock = false;
		}
	};
};

