/*
 * $Id$
 */
#ifndef __XVR2_EV_KEYBOARD_H__
#define __XVR2_EV_KEYBOARD_H__
#include<xvr2/Object.h>

namespace xvr2 {
namespace ui {
	class evKeyboard : public Object {
		private:
		protected:
		public:
			evKeyboard();
			int getKey();
			int getModifier();
			void shutDown();
			void startUp();
	};
};
};
#endif
