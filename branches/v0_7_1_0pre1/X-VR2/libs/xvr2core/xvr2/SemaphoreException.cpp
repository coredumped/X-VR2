/*
 * $Id$
 */
#include"config.h"
#include "SemaphoreException.h"
#include "MessageStrings.h"

namespace xvr2 {
	namespace Exception{

		SemaphoreException::SemaphoreException(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2SemaphoreException);
#endif
			description = (char *)xvr2::excepSemaphore;
		}


		SemaphoreInitValue::SemaphoreInitValue(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2SemaphoreInitValueException);
#endif
			description = (char *)xvr2::excepSemaphoreInitValue;
		}


		SemaphoreUnableToDestroy::SemaphoreUnableToDestroy(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2SemaphoreUnableToDestroyException);
#endif
			description = (char *)xvr2::excepSemaphoreUnableToDestroy;
		}


		SemaphoreUnableToDecrease::SemaphoreUnableToDecrease(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2SemaphoreUnableToDecreaseException);
#endif
			description = (char *)xvr2::excepSemaphoreUnableToDecrease;
		}


			SemaphoreUnableToIncrease::SemaphoreUnableToIncrease(){
#if __GNUC__ < 3
				setClassName((char *)xvr2::_xvr2SemaphoreUnableToIncreaseException);
#endif
				description = (char *)xvr2::excepSemaphoreUnableToIncrease;
			}

	};
};


