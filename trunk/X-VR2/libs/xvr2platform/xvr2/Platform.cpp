/* $Id$ */
/***************************************************************************
 *            Platform.cpp
 *
 *  Tue Sep 12 15:59:57 2006
 *  Copyright  2006  Juan V. Guerrero
 *  mindstorm2600 at users dot sourceforge dot net
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include<xvr2/Tokenizer.h>
#include<xvr2/StringBuffer.h>
#include<xvr2/Memory.h>
#include<fstream>
#include<vector>
#include<cerrno>
#include<unistd.h>
#include"Platform.h"
#ifdef XVR2_HOST_PLATFORM_LINUX
#include<sys/types.h>
#include<sys/stat.h>
#include <linux/unistd.h>
#include <linux/types.h>
#include <linux/sysctl.h>
#ifndef LSB_RELEASE_F
#define LSB_RELEASE_F "/etc/lsb-release"
#endif
#ifndef RH_RELEASE_F
#define RH_RELEASE_F "/etc/redhat-release"
#endif
#ifndef FEDORA_RELEASE_F
#define FEDORA_RELEASE_F "/etc/fedora-release"
#endif
#ifndef GENTOO_RELEASE_F
#define GENTOO_RELEASE_F "/etc/gentoo-release"
#endif


#ifndef PIC
//For some reason it is not possible to use the function
//when the code is compiled with PIC
#ifdef __cplusplus
extern "C" {
#endif
extern _syscall1(int, _sysctl, struct __sysctl_args *, args);
#ifdef __cplusplus
}
#endif

#endif

#endif

xvr2::String __read_file_full(const xvr2::String &f){
	char buffer[128];
	xvr2::StringBuffer buf;
	std::ifstream in_f(f.toCharPtr());
	while(!in_f.eof()){
		in_f.getline(buffer, 128);
		buf << buffer;
	}
	in_f.close();
	return xvr2::String(buf.toString());
}



#ifdef XVR2_HOST_PLATFORM_LINUX
	using xvr2::String;

	String __parse_lsb_release(){
		char buffer[128];
		xvr2::String buf;
		std::ifstream in_f(LSB_RELEASE_F);
		while(!in_f.eof()){
			in_f.getline(buffer, 128);
			buf = buffer;
			if(buf.startsWith("DISTRIB_DESCRIPTION")){
				xvr2::Tokenizer t0(buf, "=");
				t0.next();
				buf = t0.next();
				buf.trim('\"');
				break;
			}
		}
		in_f.close();
		return String(buf);
	}
	
	#define SYSCTL_PARM_SIZE(x) sizeof(x)/sizeof(x[0])

	String __computeOSName(){
#ifndef PIC
		char osname[128];
		xvr2::Memory::clearBuffer(osname, 128);
		int name[] = { CTL_KERN, KERN_OSTYPE };
		int nlen = SYSCTL_PARM_SIZE(name);
		size_t olen;
		__sysctl_args args={ name, nlen, osname, &olen, 0, 0};
		_sysctl(&args);
		return String(osname);
#else
		return __read_file_full("/proc/sys/kernel/ostype");
#endif
	}
	String __computeOSVersionString(){
		String _version_str;
#ifndef PIC
		char osname[128];
		xvr2::Memory::clearBuffer(osname, 128);
		int name[] = { CTL_KERN, KERN_OSRELEASE };
		int nlen = SYSCTL_PARM_SIZE(name);
		size_t olen;
		__sysctl_args args={ name, nlen, osname, &olen, 0, 0};
		_sysctl(&args);
		return String(osname);
		_version_str = osname;
#else
		_version_str = __read_file_full("/proc/sys/kernel/osrelease");
#endif
		return _version_str;
	}
#endif


namespace xvr2 {
	namespace Platform {
	
		static std::vector<CPU> _cpulist;
		static UInt64 __swap_size;
		static UInt64 __phys_mem_size;
		static String _os_distro;
		static String _os_name;
		static String _os_version_str;
		static std::vector<int> _os_ver;

		static void __getSystemInformation(){	
			//Obtain CPU Information
#ifdef XVR2_HOST_PLATFORM_LINUX
			//Linux specific cpu information
			char buf[1024];
			String buffer;
			std::ifstream in_f("/proc/cpuinfo");
			while(!in_f.eof()){
				//int pos = cpu_f.tellg();
				in_f.getline(buf, 1024);
				buffer = buf;
				if(buffer.startsWith("processor")){
					//cpu_f.seekg(pos);
					_cpulist.push_back(CPU::create(in_f));
				}
			}
			in_f.close();
			
			//Linux specific memory information
			//std::ifstream in_f("/proc/meminfo");
			in_f.open("/proc/meminfo");
			while(!in_f.eof()){
				in_f.getline(buf, 1024);
				buffer = buf;
				if(buffer.startsWith("SwapTotal")){
					xvr2::Tokenizer t0(buffer, ":");
					t0.next();
					buffer = t0.next();
					xvr2::Tokenizer t1(buffer.trim(' '), " ");
					buffer = t1.next();
					__swap_size = buffer.toInt64();
					buffer = t1.next();
					if(buffer.equals("kB") || buffer.equals("KB")){
						__swap_size = __swap_size * 1024;
					}
					else if(buffer.equals("mB") || buffer.equals("MB")){
						__swap_size = __swap_size * 1024 * 1024;
					}
					break;
				}
			}
			in_f.close();
		
			//Linux specific distribution name query
			struct ::stat _st;
			if(stat("/etc/lsb-release", &_st) == 0){
				_os_distro = __parse_lsb_release();
			}
			else if(stat(RH_RELEASE_F, &_st) == 0){
				_os_distro = __read_file_full(RH_RELEASE_F);
			}
			else if(stat(FEDORA_RELEASE_F, &_st) == 0){
				_os_distro = __read_file_full(FEDORA_RELEASE_F);
			}
			else if(stat(GENTOO_RELEASE_F, &_st) == 0){
				_os_distro = __read_file_full(GENTOO_RELEASE_F);
			}
			_os_name = __computeOSName();
			_os_version_str = __computeOSVersionString();
			Tokenizer tx(_os_version_str, ".");
			while(!tx.finished()){
				String _tmp = tx.next();
				if(isdigit(_tmp[0])){
					try{
						_os_ver.push_back(_tmp.toInt());
					}
					catch(...){
					}
				}
				else{
					break;
				}
			}
#else
#error Platform not supported
#endif
			//Obtain memory information
			__phys_mem_size = sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGE_SIZE);
		}
	
		UInt32 SystemInformation::cpuCount(){
			if(_cpulist.size() == 0){
				__getSystemInformation();
			}
			return _cpulist.size();
		}
	
		const CPU &SystemInformation::getCPU(UInt32 idx){
			if(_cpulist.size() == 0){
				__getSystemInformation();
			}
			return _cpulist[idx];
		}
	
		UInt64 SystemInformation::memorySize(){
			if(_cpulist.size() == 0){
				__getSystemInformation();
			}
			return physicalMemorySize() + swapSize();
		}
	
		UInt64 SystemInformation::physicalMemorySize(){
			if(_cpulist.size() == 0){
				__getSystemInformation();
			}
			return __phys_mem_size;
		}
	
		UInt64 SystemInformation::swapSize(){
			if(_cpulist.size() == 0){
				__getSystemInformation();
			}
			return __swap_size;
		}
	
		const String &SystemInformation::OSDistribution(){
			//HArd to know, depends on the platform in the case of Linux
			//there is no standard way to know the distribution name.
			if(_os_name.size() == 0){
				__getSystemInformation();
			}
			return _os_distro;
		}
	
		const String &SystemInformation::OSName(){
			//Linux, Solaris, AIX, HP-UX, etc, etc
			if(_os_name.size() == 0){
				__getSystemInformation();
			}
			return _os_name;
		}
	
		const String &SystemInformation::OSVersionString(){
			if(_os_name.size() == 0){
				__getSystemInformation();
			}
			return _os_version_str;
		}
	
		const std::vector<int> &SystemInformation::OSVersion(){
			if(_os_name.size() == 0){
				__getSystemInformation();
			}
			return _os_ver;
		}
	};
};
