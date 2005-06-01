/*
 * $Id$
 *
 *			Juan V. Guerrero <coredumped@esolutions4all.com>
 */
#ifndef __XVR2_CONFIG_FILE__
#define __XVR2_CONFIG_FILE__
#include<xvr2/Object.h>
#include<xvr2/String.h>
#include<xvr2/Mutex.h>
#include<xvr2/Array.h>
#include<xvr2/List.h>
#include<xvr2/ElementNotFoundException.h>

namespace xvr2 {
	namespace Util {
		class __ParamAndVal;

		/** This class parses a specific config file and caches the data
		 *  contained therein so when you need to query the value of a 
		 *  specific config parameter you read it from memory and not 
		 *  directly from the file itself.
		 *  This class implements a simple parsing engine, however, the 
		 *  syntax it understands is very simple, lines starting with the
		 *  # character are considered comments 
		 *  And the paramater value combination follows the syntax:
		 *  PARAMETER_NAME: PARAMETER_VALUE
		 *         or
		 *  PARAMETER_NAME=PARAMETER_VALUE
		 */
		class ConfigFile:public Object{
			private:
				/** This variable holds the path corresponding to 
				 *  the configuration file to be parsed */
				char *filepath;
				/** Parameter/value pair cached from the 
				 *  configuration file */
				List<__ParamAndVal *> cache;
				__ParamAndVal *search(const char *key);
				void saveConfig();
			protected:
			public:
				/** This are the three possible values for a config
				 *  datatype */
				enum {
					/** Data is an integer */
					TYPE_INTEGER = 1,
					/** Data is a floating point number */
					TYPE_FLOAT = 2,
					/** Data is a literal string (not enclosed
					 *  in double quotes) */
					TYPE_STRING = 3
				};
				/** This constructor will initialize the ConfigFile
				 *  parsers to read its input from the file fname */
				ConfigFile(const char *fname);
				/** Mandatory destructor, this method will take care
				 *  of freeing the parameter/value cache */
				~ConfigFile();
				/** Call this method to parse the configuration 
				 *  file and initialize the plist and vlist arrays */
				int parse();
				/** This method will add a new variable to the cache
				 *  and automatically set its value to val */
				void addVariable(const char *vname, int val);
				/** This method will add a new variable to the cache
				 *  and automatically set its value to val */
				void addVariable(const char *vname, const char *val);
				/** This method will add a new variable to the cache
				 *  and automatically set its value to val */
				void addVariable(const char *vname, double val);
				/** Returns an integer representation for the value
				 *  of parameter vname */
				const int    getIntValue(const char *vname);
				/** Returns an integer representation for the value
				 *  of parameter vname */
				const char  *getStrValue(const char *vname);
				/** Returns an integer representation for the value
				 *  of parameter vname */
				const double getFloatValue(const char *vname);
				/** Will change the value for the variable
				 *  vname and update the corresponfing config 
				 *  file */
				void setValue(const char *vname, int val);
				/** Will change the value for the variable
				 *  vname and update the corresponfing config 
				 *  file */
				void setValue(const char *vname, double val);
				/** Will change the value for the variable
				 *  vname and update the corresponfing config 
				 *  file */
				void setValue(const char *vname, const char *val);
		};

		/**
		 * Utilitary class to be used within the ConfigFile class in order
		 * to store parameter/value pairs
		 */
		class __ParamAndVal:public Object{
			private:
			protected:
				/** Holds de parameter name */
				char   *myname;
				/** If the variable value is integer, then it will
				 *  be stored here */
				int     ival;
				/** If the variable value is a string, then it 
				 *  will be stored here */
				char   *sval;
				/** If the variable value is a floating point 
				 *  number, then it will be stored here */
				double  fpval;
				/** Stores a datatype enumerator value */
				int datatype;
			public:
				/** Default constructor, this one takes care of
				 *  initializing all internal variables and string
				 *  based pointers */
				__ParamAndVal();
				/** Initializes the myname pointer to the contents 
				 *  of pname */
				__ParamAndVal(const char *pname);
				/** This destructor takes care of releasing the 
				 *  internal buffers: myname and sval */
				~__ParamAndVal();
				/** Overrides the = operator in order to provide
				 *  a safe copy method */
				__ParamAndVal &operator=(__ParamAndVal pv);
				/** Use this method to test equality with another
				 *  __ParamAndVal object */
				bool operator==(const __ParamAndVal &pv);
				/** Use this method to test if the current object 
				 *  has the name pname */
				bool operator==(const char *pname);
				/** Sets this object's value to the integer x */
				void setVal(int x);
				/** Sets this object's value to the string x */
				void setVal(const char *x);
				/** Sets this object's value to the floating point 
				 *  number x */
				void setVal(double x);
				/** Returns a integer representation of the current
				 *  value */
				const int getIVal();
				/** Returns a string representation of the current
				 *  value */
				const char *getSVal();
				/** Returns a floating point representation of the 
				 *  current value */
				const double getFPVal();
				/** Returns the name of this object*/
				const char *getName();
				/** Returns a integer representation of the current
				 *  value */
				const int getDataType();
		};
	};
};

#endif
