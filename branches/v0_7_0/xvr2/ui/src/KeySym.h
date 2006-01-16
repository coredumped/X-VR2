/*
 * $Id$
 */
#ifndef __XVR2_UI_KEYSYM_H__
#define __XVR2_UI_KEYSYM_H__
#include<xvr2/Object.h>

namespace xvr2 {
namespace ui {

	class KeySym:public Object {
		private:
		protected:
			int _keycode;
		public:
			KeySym();
			KeySym(int keycode);
			int code() const;
	};
};
};
#endif
