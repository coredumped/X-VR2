/*
 * $Id$
 */
#include<SemaphoreException.h>
#include<MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Semaphore::Semaphore(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2SemaphoreException);
#endif
			description = (char *)xvr2::excepSemaphore;
		}


		SemaphoreInitValue::SemaphoreInitValue(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2SemaphoreInitValueException);
#endif
			description = (char *)xvr2::excepSemaphoreInitValue;
		}


		SemaphoreUnableToDestroy::SemaphoreUnableToDestroy(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2SemaphoreUnableToDestroyException);
#endif
			description = (char *)xvr2::excepSemaphoreUnableToDestroy;
		}


		SemaphoreUnableToDecrease::SemaphoreUnableToDecrease(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2SemaphoreUnableToDecreaseException);
#endif
			description = (char *)xvr2::excepSemaphoreUnableToDecrease;
		}


			SemaphoreUnableToIncrease::SemaphoreUnableToIncrease(){
#ifndef USING_GCC3
				setClassName((char *)xvr2::_xvr2SemaphoreUnableToIncreaseException);
#endif
				description = (char *)xvr2::excepSemaphoreUnableToIncrease;
			}

	};
};


