/*
 * $Id$
 *
 * X-VR2 
 * 
 * Copyright (C) Juan V. Guerrero 2007
 * 
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 * 
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#ifndef __XVR2_PIPELINE_FILTER_H__
#define __XVR2_PIPELINE_FILTER_H__
#include<xvr2/CoreExceptions.h>
#include<xvr2/Function.h>
#include<xvr2/String.h>

namespace xvr2 {

	template<typename _Ft = xvr2::String >
	class PipelineFilter : public Function {
		private:
		protected:
		public:
			typedef _Ft FilteredT;
			
			PipelineFilter(): xvr2::Function() { }
			virtual ~PipelineFilter(){ }
			virtual FilteredT operator()(const FilteredT &input){
				return FilteredT(input);
			}
	};

}

#endif
