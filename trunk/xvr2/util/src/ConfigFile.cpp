/*
 * $Id$
 *
 *			Juan V. Guerrero <coredumped@esolutions4all.com>
 */
#include<xvr2/ConfigFile.h>
#include<xvr2/Memory.h>
#if __GNUC__ < 3
#include<string.h>
#include<stdio.h>
#endif
#include<limits.h>

extern int config_parse(xvr2::Util::ConfigFile *store, const char *);

int param_value_add(xvr2::Util::ConfigFile *store, const char *param_name, const char *data){
	store->addVariable(param_name, data);
	return 1;
}

int param_value_add(xvr2::Util::ConfigFile *store, const char *param_name, int data){
	store->addVariable(param_name, data);
	return 1;
}

int param_value_add(xvr2::Util::ConfigFile *store, const char *param_name, double data){
	store->addVariable(param_name, data);
	return 1;
}

namespace xvr2 {
	namespace Util {
		/* Since our config file parser is not reentrant we have to
		 * provide this mutex as a safety measure to guarantee one 
		 * time access to be object */
		static Mutex ConfigFileLock;

		ConfigFile::ConfigFile(const char *fname){
#if __GNUC__ < 3
			setClassName(xvr2::_xvr2ConfigFile);
#endif
			filepath = strdup(fname);
		}

		ConfigFile::~ConfigFile(){
			unsigned int i = 0;
			__ParamAndVal *pv;
			Memory::freeBuffer((void **)&filepath);
			cache.rewind();
			for(i = 0; i < cache.size(); i++){
				pv = cache.get(i);
				delete pv;
			}
		}

		int ConfigFile::parse(){
			int ret;
			ConfigFileLock.lock();
			ret = config_parse(this, filepath);
			ConfigFileLock.unlock();
			return ret;
		}

		void ConfigFile::addVariable(const char *vname, int val){
			__ParamAndVal *pv = new __ParamAndVal(vname);
			pv->setVal(val);
			cache.add(pv);
		}

		void ConfigFile::addVariable(const char *vname, const char *val){
			__ParamAndVal *pv = new __ParamAndVal(vname);
			pv->setVal(val);
			cache.add(pv);
		}

		void ConfigFile::addVariable(const char *vname, double val){
			__ParamAndVal *pv = new __ParamAndVal(vname);
			pv->setVal(val);
			cache.add(pv);
		}

		__ParamAndVal *ConfigFile::search(const char *key){
			unsigned int i;
			__ParamAndVal *pv;
			for(i = 0; i < cache.size(); i++){
				pv = cache.get(i);
				if(strcmp(pv->getName(), key) == 0)
					return pv;
			}
			return 0;
		}

		const int ConfigFile::getIntValue(const char *vname){
			__ParamAndVal *pv;
			pv = search(vname);
			if(pv == 0) throw Exception::ElementNotFound();
			return pv->getIVal();
		}

		const double ConfigFile::getFloatValue(const char *vname){
			__ParamAndVal *pv;
			pv = search(vname);
			if(pv == 0) throw Exception::ElementNotFound();
			return pv->getFPVal();
		}

		const char *ConfigFile::getStrValue(const char *vname){
			__ParamAndVal *pv;
			pv = search(vname);
			if(pv == 0) throw Exception::ElementNotFound();
			return pv->getSVal();
		}

		void ConfigFile::saveConfig(){
			FILE *fptr;
			unsigned int i;
			__ParamAndVal *pv;
			fptr = fopen(filepath, "w");
#ifdef USE_DEBUG
			std::cout << "Saving file \"" << filepath << "\" ..." << std::endl;
#endif
			if(fptr != 0){
				for(i = 0; i < cache.size(); i++){
					pv = cache.get(i);
					switch(pv->getDataType()){
						case xvr2::Util::ConfigFile::TYPE_INTEGER:
							fprintf(fptr, "%s: %d\n", pv->getName(), pv->getIVal());
#ifdef USE_DEBUG
							std::cout << pv->getName() << ":  " << pv->getIVal() << std::endl;
#endif
							break;
						case xvr2::Util::ConfigFile::TYPE_FLOAT:
							fprintf(fptr, "%s: %lf\n", pv->getName(), pv->getFPVal());
#ifdef USE_DEBUG
							std::cout << pv->getName() << ":  " << pv->getFPVal() << std::endl;
#endif
							break;
						default:
							fprintf(fptr, "%s: %s\n", pv->getName(), pv->getSVal());
#ifdef USE_DEBUG
							std::cout << pv->getName() << ":  " << pv->getSVal() << std::endl;
#endif
					}
				}
				fclose(fptr);
			}
			else{
				throw Exception::File();
			}
		}

		void ConfigFile::setValue(const char *vname, int val){
			__ParamAndVal *pv;
			pv = search(vname);
			if(pv == 0) throw Exception::ElementNotFound();
			pv->setVal(val);
			saveConfig();
		}

		void ConfigFile::setValue(const char *vname, double val){
			__ParamAndVal *pv;
			pv = search(vname);
			if(pv == 0) throw Exception::ElementNotFound();
			pv->setVal(val);
			saveConfig();
		}

		void ConfigFile::setValue(const char *vname, const char *val){
			__ParamAndVal *pv;
			pv = search(vname);
			if(pv == 0) throw Exception::ElementNotFound();
			pv->setVal(val);
			saveConfig();
		}

		__ParamAndVal::__ParamAndVal(){
#if __GNUC__ < 3
			setClassName(xvr2::_xvr2__ParamAndVal);
#endif
			myname = 0;
			sval = 0;
			ival = 0;
			fpval = 0;
		}

		__ParamAndVal::__ParamAndVal(const char *pname){
#if __GNUC__ < 3
			setClassName(xvr2::_xvr2__ParamAndVal);
#endif
			sval = 0;
			ival = 0;
			fpval = 0;
			myname = strdup(pname);
		}

		__ParamAndVal::~__ParamAndVal(){
			if(myname != 0)
				Memory::freeBuffer((void **)&myname);
			if(sval != 0)
				Memory::freeBuffer((void **)&sval);
#ifdef USE_DEBUG
#if __WORDSIZE == 64 && defined(__x86_64__)
			std::cerr << "__ParamAndVal " << ((Int64)this) << " destroyed" << std::endl;
#else
			std::cerr << "__ParamAndVal " << ((unsigned int)this) << " destroyed" << std::endl;
#endif
#endif
		}

		__ParamAndVal &__ParamAndVal::operator=(__ParamAndVal pv){
		//void __ParamAndVal::operator=(const __ParamAndVal &pv){
			if(pv.myname != 0)
				myname = strdup(pv.myname);
			if(pv.sval != 0)
				myname = strdup(pv.sval);
			ival = pv.ival;
			fpval = pv.fpval;
			return *this;
		}

		bool __ParamAndVal::operator==(const __ParamAndVal &pv){
			if(strcmp(myname, pv.myname) == 0){
				return true;
			}
			return false;
		}

		bool __ParamAndVal::operator==(const char *pname){
			if(strcmp(myname, pname) == 0){
				return true;
			}
			return false;
		}

		void __ParamAndVal::setVal(int v){
			ival = v;
			fpval = ival;
			if(sval != 0)
				Memory::freeBuffer((void **)&sval);
			sval = (char *)Memory::allocBuffer(128);
			sprintf(sval, "%d", ival);
			datatype = ConfigFile::TYPE_INTEGER;
		}

		void __ParamAndVal::setVal(const char *s){
			datatype = ConfigFile::TYPE_STRING;
			if(sval != 0)
				Memory::freeBuffer((void **)&sval);
			sval = 0;
			sval = strdup(s);
#ifdef USE_DEBUG
			std::cout << myname << ".sval=" << sval << std::endl;
#endif
		}

		void __ParamAndVal::setVal(double fp){
			fpval = fp;
			ival = (int)fpval;
			if(sval != 0)
				Memory::freeBuffer((void **)&sval);
			sval = (char *)Memory::allocBuffer(128);
			sprintf(sval, "%lf", fp);
			datatype = ConfigFile::TYPE_FLOAT;
		}

		const char *__ParamAndVal::getName(){
			return myname;
		}

		const int __ParamAndVal::getIVal(){
			return ival;
		}

		const char *__ParamAndVal::getSVal(){
			return sval;
		}

		const double __ParamAndVal::getFPVal(){
			return fpval;
		}

		const int __ParamAndVal::getDataType(){
			return datatype;
		}
	};
};
