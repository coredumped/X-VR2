/*
 * $Id$
 */
#ifndef __XVR2_DSO_EXCEPTION_H__
#define __XVR2_DSO_EXCEPTION_H__
#include<xvr2/Exception.h>
#include<xvr2/IOException.h>

namespace xvr2 {
	/**
	 * Use this exception whenever you want to throw a generic exception over
	 * a dso (dynamic shared object) event */
	class DSOException:public IOException{
		public:
			/**
			 * Default Constructor
			 */
			DSOException(const char *msg = 0);
	};

	/**
	 * This exception is thown whenever you're trying to load a DSOException and some error
	 * ocurred
	 */
	class CantLoadDSO:public DSOException{
		public:
			/**
			 * Default constructor
			 */
			CantLoadDSO();
	};

	/**
	 * If a DSOException cannot be unloaded, this exception is thrown
	 */
	class CantUnloadDSO:public DSOException{
		public:
			/**
			 * Default constructor
			 */
			CantUnloadDSO();
	};

	/**
	 * This is a common error appearing whenever you cant load
	 * a symbol from a DSOException
	 */
	class DSOSymbol:public DSOException{
		public:
			/**
			 * Default constructor
			 */
			DSOSymbol();
	};
};


#endif
