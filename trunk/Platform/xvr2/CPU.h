/***************************************************************************
 *            CPU.h
 *
 *  Tue Sep 12 16:47:31 2006
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
 
#ifndef __XVR2_CPU_H__
#define __XVR2_CPU_H__

#include<xvr2/String.h>
#include<xvr2/Platform/PlatformException.h>
#include<fstream>

namespace xvr2 {
namespace Platform {
	struct CPU : public xvr2::Object {
		const static CPU create(std::ifstream &in);
		double clockSpeed;
		UInt64 cacheSize;
		String model;
		String vendor;
		std::string toString();
		std::string toString() const;
	};
};
};

#endif /* _CPU_H */
