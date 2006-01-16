/*
 * $Id$
 */
#ifndef __XVR2_UI_KEYBOARD_EVENT_H__
#define __XVR2_UI_KEYBOARD_EVENT_H__
#include<xvr2/Object.h>
#include<xvr2/KeySym.h>

namespace xvr2 {
namespace ui {

	class KeyboardEvent:public Object {
		private:
		protected:
			bool ev_pressed();
			int ev_scancode;
			KeySym ev_key;
		public:
			KeyboardEvent();
			/** Says if the key has been pressed */
			bool pressed();
			/** Says if the key has been released */
			bool released();
			const KeySym &key() const;
	};

};
};
#endif
