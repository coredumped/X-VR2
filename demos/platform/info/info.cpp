/* $Id$ */
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
#include<xvr2/String.h>
#include<xvr2/StringBuffer.h>
#include<xvr2/Platform.h>
#include<iostream>

using std::cout;
using std::endl;
using xvr2::Platform::SystemInformation;
using xvr2::String;
using xvr2::StringBuffer;

#ifndef KB_ABS_VALUE
#define KB_ABS_VALUE 1024
#endif

#ifndef MB_ABS_VALUE
#define MB_ABS_VALUE 1048576
#endif

#ifndef GB_ABS_VALUE
#define GB_ABS_VALUE 1073741824
#endif

String format(UInt64 value){
	StringBuffer buf;
	double val = 0;
	if(value > GB_ABS_VALUE){
		buf << ((double)(value / GB_ABS_VALUE)) << " GB";
	}
	else if(value > MB_ABS_VALUE){
		buf << ((double)(value / MB_ABS_VALUE)) << " MB";
	}
	else if(value > KB_ABS_VALUE){
		buf << ((double)(value / KB_ABS_VALUE)) << " KB";
	}
	else if(value == -1){
		buf << "N/A";
	}
	else {
		buf << value << " B";
	}
	return String(buf.toString());
}

int main(){
	cout << "X-VR2 Running on: " << SystemInformation::OSDistribution() << endl;
	cout << "Kernel: " << SystemInformation::OSName() << " " << SystemInformation::OSVersionString() << endl;
	cout << "== PROCESSOR INFORMATION ==" << endl;
	cout << "Detected CPUs: " << SystemInformation::cpuCount() << endl;
	for(int i = 0; i < SystemInformation::cpuCount(); i++){
		cout << "CPU #" << (i + 1) << endl;
		cout << SystemInformation::getCPU(i).toString() << endl;
	}
	cout << "== SYSTEM MEMORY == " << endl;
	cout << "Physical memory size: " << format(SystemInformation::physicalMemorySize()) << endl;
	cout << "Swap size:            " << format(SystemInformation::swapSize()) << endl;
	cout << "Total:                " << format(SystemInformation::memorySize()) << endl;
	return 0;
}
