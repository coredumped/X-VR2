/*
 * $Id$
 */
#include<xvr2/SemaphoreException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Semaphore::Semaphore(){
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


