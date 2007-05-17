/* $Id$ */
/***************************************************************************
 *            CPU.cpp
 *
 *  Tue Sep 12 17:11:14 2006
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
#include"CPU.h"
#include"Platform.h"

namespace xvr2 {
namespace Platform {
	using xvr2::Tokenizer;

	/*CPU::CPU(const CPU &_cpu){
		model = _cpu.model;
		clockSpeed = _cpu.clockSpeed;
		cacheSize = _cpu.cacheSize;
	}*/

	std::string CPU::toString(){
		StringBuffer txt;
		txt << "Model:       " << model << xvr2::NL;
		txt << "Clock speed: " << (clockSpeed / 1000.0 / 1000.0) << " MHz" << xvr2::NL;
		txt << "Cache size:  " << (cacheSize / 1024.0) << " KB" << xvr2::NL;
		return std::string(txt.toString());
	}

	std::string CPU::toString() const{
		StringBuffer txt;
		txt << "Vendor:      " << vendor << xvr2::NL;
		txt << "Model:       " << model << xvr2::NL;
		txt << "Clock speed: " << (clockSpeed / 1000.0 / 1000.0) << " MHz" << xvr2::NL;
		txt << "Cache size:  " << (cacheSize / 1024.0) << " KB" << xvr2::NL;
		return std::string(txt.toString());
	}

#ifdef XVR2_HOST_PLATFORM_LINUX
	const CPU CPU::create(std::ifstream &in){
		String buffer;
		CPU dummy;
		char buf[1024];
		int pos;
		while(!in.eof()){
			pos = in.tellg();
			in.getline(buf, 1024);
			String buffer = buf;
			if(buffer.startsWith("processor")){
				in.seekg(pos);
				break;
			}
			else if(buffer.startsWith("vendor_id")){
				Tokenizer t0(buffer, ":");
				t0.next();
				dummy.vendor = t0.next();
				dummy.vendor.trim(' ');
				if(dummy.vendor.equals("GenuineIntel")){
					dummy.vendor = "Intel(R)";
				}
			}
			else if(buffer.startsWith("cpu MHz")){
				Tokenizer t1(buffer, ":");
				t1.next();
				String sp = t1.next();
				sp.trim(' ');
				dummy.clockSpeed = sp.toDouble() * 1000.0 * 1000.0;
			}
			else if(buffer.startsWith("model name")){
				Tokenizer t2(buffer, ":");
				t2.next();
				dummy.model = t2.next();
				dummy.model.trim(' ');
			}
			else if(buffer.startsWith("cache size")){
				Tokenizer t3(buffer, ":");
				t3.next();
				String spd = t3.next();
				Tokenizer t4(spd.trim(' '), " ");
				String v = t4.next();
				String unit = t4.next();
				dummy.cacheSize = (UInt64)v.toInt64();
				if(unit.equals("MB")){
					dummy.cacheSize = dummy.cacheSize * 1024 * 1024;
				}
				else if(unit.equals("KB")){
					dummy.cacheSize = dummy.cacheSize * 1024;
				}
				else {
					throw PlatformException("Unable to parse cache size: " + spd);
				}
			}
		}
		return CPU(dummy);
	}
#else
#error Unsupported platform
#endif
};
};
