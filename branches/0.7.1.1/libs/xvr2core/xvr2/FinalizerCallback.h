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
#ifndef __XVR2_FINALIZER_CALLBACK_H__
#define __XVR2_FINALIZER_CALLBACK_H__
#include<xvr2/Function.h>
#include<xvr2/String.h>

namespace xvr2{

	class FinalizerCallback : public Function {
		public:
			FinalizerCallback();
			virtual ~FinalizerCallback();
			virtual void operator()();
	};
};

#endif
