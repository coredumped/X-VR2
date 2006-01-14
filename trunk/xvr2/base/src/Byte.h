/*
 * $Id$
 */
#ifndef __XVR2_Byte_H__
#define __XVR2_Byte_H__

#include<xvr2/System.h>
#include<xvr2/String.h>

namespace xvr2{
	/**
	 * This class represents a Byte, bit by bit and provides a means for 
	 * accesing each bit individually.
	 * According to the system the ordering of every bit may vary. Depending on 
	 * what you think the ordering should be for every bit we will use the 
	 * following standard in this library<br>
	 * <table cellspacing=0 cellpadding=0 border=1 bgcolor=silver rules=none>
	 * <tr><td>bit 7</td><td>bit 6</td><td>bit 5</td><td>bit 4</td><td>bit 3</td><td>bit 2</td><td>bit 1</td><td>bit 0</td>
	 * </table><br>
	 * Please note that every bit is ordered from right to left, it is going to 
	 * remain this way no matter the architecture or system you're working on.
	 *
	 * <b>TODO:</b> TAKE CARE OF THE PLATFORM ENDIANNESS
	 *
	 */
	class Byte:public System{
		private:
		protected:
			/** As the name says this is the binary value */
			UInt8 value;
			String str_value;
		public:
			/** Default constructor, it will initialize value to zero */
			Byte();
			/** This constructor will initialize the Byte value to <b>v</b> */
			Byte(UInt8 v);
			/** This constructor will parse an array of 0s and 1s
			 *  and will construct a byte, if you use characters
			 *  different from '0' or '1' or if you use a string
			 *  larger than 8 chars then you will receive the
			 *  appropiate exception */
			Byte(const char *binary);
			/** Almost the sam as the above constructor but the 
			 *  the argument is now a String. The same restrictions
			 *  apply */
			Byte(const String &binary);
			~Byte();
			/** This will set the interval value to <b>v</b> */
			void setValue(UInt8 v = 0);
			/** This will set the interval value to <b>binary</b> */
			void setValue(const char *binary);
			/** This will set the interval value to <b>binary</b> */
			void setValue(const String &binary);
			/** This will return the binary bit as whole */
			UInt8 theByte();
			/** This will return a reversed binary version of the value */
			UInt8 reversedByte();
			/** This will invert the byte ordering of every bit */
			void reverse();
			/** Returns the bit in position 0 */
			bool bit0();
			/** Returns the bit in position 1 */
			bool bit1();
			/** Returns the bit in position 2 */
			bool bit2();
			/** Returns the bit in position 3 */
			bool bit3();
			/** Returns the bit in position 4 */
			bool bit4();
			/** Returns the bit in position 5 */
			bool bit5();
			/** Returns the bit in position 6 */
			bool bit6();
			/** Returns the bit in position 7 */
			bool bit7();
			/** Returns a string representation of this Byte using 
			 *  0s and 1s */
			//const String &toString();
			const std::string &toString();
	};
};

#endif
