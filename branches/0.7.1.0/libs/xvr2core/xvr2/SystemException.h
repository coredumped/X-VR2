#ifndef __XVR2_SYSTEMEXCEPTION_H__
#define __XVR2_SYSTEMEXCEPTION_H__
#include<xvr2/CoreExceptions.h>
#include<xvr2/String.h>

namespace xvr2 {
	/** TODO: Document this class */
	class SystemException : public Exception {
		private:
		protected:
			int _err_code;
			String _err_str;
		public:
			SystemException(int _code = 0);
			int code();
			virtual String message(); 
	};
};


#endif
