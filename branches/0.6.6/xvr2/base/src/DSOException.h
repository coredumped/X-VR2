/*
 * $Id$
 */
#ifndef __XVR2_DSO_EXCEPTION_H__
#define __XVR2_DSO_EXCEPTION_H__
#include<Exception.h>
#include<IOException.h>

namespace xvr2 {
	namespace Exception{

		/**
		 * Use this exception whenever you want to throw a generic exception over
		 * a dso (dynamic shared object) event */
		class DSO:public IO{
			public:
				/**
				 * Default Constructor
				 */
				DSO(const char *msg = 0);
		};

		/**
		 * This exception is thown whenever you're trying to load a DSO and some error
		 * ocurred
		 */
		class CantLoadDSO:public DSO{
			public:
				/**
				 * Default constructor
				 */
				CantLoadDSO();

		};

		/**
		 * If a DSO cannot be unloaded, this exception is thrown
		 */
		class CantUnloadDSO:public DSO{
			public:
				/**
				 * Default constructor
				 */
				CantUnloadDSO();

		};

		/**
		 * This is a common error appearing whenever you cant load
		 * a symbol from a DSO
		 */
		class DSOSymbol:public DSO{
			public:
				/**
				 * Default constructor
				 */
				DSOSymbol();
		};

	};
};


#endif
