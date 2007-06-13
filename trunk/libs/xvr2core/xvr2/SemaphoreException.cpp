/*
 * $Id$
 */
#include"config.h"
#include "SemaphoreException.h"
#include "MessageStrings.h"

namespace xvr2 {
	namespace Exception{

		SemaphoreException::SemaphoreException(){
			description = (char *)xvr2::excepSemaphore;
		}


		SemaphoreInitValue::SemaphoreInitValue(){
			description = (char *)xvr2::excepSemaphoreInitValue;
		}


		SemaphoreUnableToDestroy::SemaphoreUnableToDestroy(){
			description = (char *)xvr2::excepSemaphoreUnableToDestroy;
		}


		SemaphoreUnableToDecrease::SemaphoreUnableToDecrease(){
			description = (char *)xvr2::excepSemaphoreUnableToDecrease;
		}


			SemaphoreUnableToIncrease::SemaphoreUnableToIncrease(){
				description = (char *)xvr2::excepSemaphoreUnableToIncrease;
			}

	};
};


