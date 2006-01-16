/*
 * $Id$
 */
#include<xvr2/Exception.h>
#include<xvr2/NetworkException.h>

#ifndef __xvr2_NSFatalException_H__
#define __xvr2_NSFatalException_H__

namespace xvr2 {
	namespace Exception{
		/**
		 * \class NSFatal
		 * \version $Revision$
		 * \brief A non-recoverable name server error occurred. */
		class NSFatal:public Network{
			public:
				/**
				 * Default constructor
				 */
				NSFatal();
		};
	};
};

#endif

