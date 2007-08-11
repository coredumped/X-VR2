/*
 * $Id$
 *
 * This is the main class for exception treatment, this section
 * is going to be completely rewritten
 *
 */
#ifndef __XVR2_EXCEPTION_H__
#define __XVR2_EXCEPTION_H__

#include<xvr2/Object.h>
#include<xvr2/TraceDumper.h>
#include<xvr2/String.h>

namespace xvr2{
	/**
	 * \class Exception Exception.h
	 * This is the parent class of all the exceptions
	 */
	class Exception:public ExceptionTracer {
		private:
		protected:
			/**
			 * \var char *description
			 * Stores the exception's description as a string
			 */
			char *description;
		public:
			/**
			 * \fn Exception();
			 * \brief Default constructor
			 */
			Exception();
			~Exception();
			/**
			 * \fn Exception(const char *d)
			 * \brief This constructor assigns to the description the string
			 * contained in d
			 * \param d Description string (the name and or description of the exception
			 */
			Exception(const char *d);
			/**
			 * \fn const char *toString();
			 * \brief Displays the description of the exception
			 */
			const char *toString() const;
	};

};
#endif

