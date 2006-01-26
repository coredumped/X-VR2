/*
 * This class represents a Byte, bit by bit and provides a means for accesing each beat individually
 *
 * $Id$
 */
#include"config.h"
#include"Byte.h"
#include<endian.h>
#include<sstream>

namespace xvr2{

	class _b_byte:public Object{
		public:
#if ( __BYTE_ORDER == __LITTLE_ENDIAN )
		unsigned int b0:1;
		unsigned int b1:1;
		unsigned int b2:1;
		unsigned int b3:1;
		unsigned int b4:1;
		unsigned int b5:1;
		unsigned int b6:1;
		unsigned int b7:1;
#else
#if ( __BYTE_ORDER == __BIG_ENDIAN )
		unsigned int b7:1;
		unsigned int b6:1;
		unsigned int b5:1;
		unsigned int b4:1;
		unsigned int b3:1;
		unsigned int b2:1;
		unsigned int b1:1;
		unsigned int b0:1;
#else
//PGP Byte ordering
		unsigned int b6:1;
		unsigned int b7:1;
		unsigned int b4:1;
		unsigned int b5:1;
		unsigned int b2:1;
		unsigned int b3:1;
		unsigned int b0:1;
		unsigned int b1:1;
#endif
#endif
	};

	// Start definition of local variables
	// End definition of local variables

	// Start definition of local functions
	// End definition of local functions




	//Start implementation of class: Byte

	Byte::Byte(){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Byte);
#endif
		setValue();
	}

	Byte::Byte(UInt8 v){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Byte);
#endif
		setValue(v);
	}

	Byte::Byte(const char *v){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Byte);
#endif
		setValue(v);
	}

	Byte::Byte(const String &v){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Byte);
#endif
		setValue(v);
	}

	Byte::~Byte(){
	}

	UInt8 Byte::theByte(){
		return value;
	}

	UInt8 Byte::reversedByte(){
		UInt8 rev;
		UInt8 *trev;
		_b_byte *tmp, tmp2;
		tmp = (_b_byte *)&value;
		tmp2.b0 = tmp->b7;
		tmp2.b1 = tmp->b6;
		tmp2.b2 = tmp->b5;
		tmp2.b3 = tmp->b4;
		tmp2.b4 = tmp->b3;
		tmp2.b5 = tmp->b2;
		tmp2.b6 = tmp->b1;
		tmp2.b7 = tmp->b0;
		trev = (UInt8 *)&tmp2;
		rev = *trev;
		return rev;
	}

	void Byte::reverse(){
		setValue(reversedByte());
	}

	bool Byte::bit0(){
		bool r;
		_b_byte *tmp;
		tmp = (_b_byte *)&value;
		r = tmp->b0;
		return r;
	}

	bool Byte::bit1(){
		bool r;
		_b_byte *tmp;
		tmp = (_b_byte *)&value;
		r = tmp->b1;
		return r;
	}

	bool Byte::bit2(){
		bool r;
		_b_byte *tmp;
		tmp = (_b_byte *)&value;
		r = tmp->b2;
		return r;
	}

	bool Byte::bit3(){
		bool r;
		_b_byte *tmp;
		tmp = (_b_byte *)&value;
		r = tmp->b3;
		return r;
	}

	bool Byte::bit4(){
		bool r;
		_b_byte *tmp;
		tmp = (_b_byte *)&value;
		r = tmp->b4;
		return r;
	}

	bool Byte::bit5(){
		bool r;
		_b_byte *tmp;
		tmp = (_b_byte *)&value;
		r = tmp->b5;
		return r;
	}

	bool Byte::bit6(){
		bool r;
		_b_byte *tmp;
		tmp = (_b_byte *)&value;
		r = tmp->b6;
		return r;
	}

	bool Byte::bit7(){
		bool r;
		_b_byte *tmp;
		tmp = (_b_byte *)&value;
		r = tmp->b7;
		return r;
	}

	void Byte::setValue(UInt8 v){
		UInt8 tmp;
		_b_byte *data;
		tmp = v;
		value = tmp;
		data = (_b_byte *)&tmp;
		/*str_value.deleteString();
		str_value = (int)data->b7;
		str_value += (int)data->b6;
		str_value += (int)data->b5;
		str_value += (int)data->b4;
		str_value += (int)data->b3;
		str_value += (int)data->b2;
		str_value += (int)data->b1;
		str_value += (int)data->b0;*/
		std::stringstream stream;
		if(string_representation != 0){
			delete string_representation;
		}
		stream << (int)data->b7 << data->b6 << data->b5 << data->b4 << data->b3 << data->b2 << data->b1 << data->b0;
		string_representation = new std::string(stream.str());
	}

	void Byte::setValue(const char *v){
		_b_byte data;
		UInt8 *tmp, x;
		data.b0 = v[7] - '0';
		data.b1 = v[6] - '0';
		data.b2 = v[5] - '0';
		data.b3 = v[4] - '0';
		data.b4 = v[3] - '0';
		data.b5 = v[2] - '0';
		data.b6 = v[1] - '0';
		data.b7 = v[0] - '0';

		tmp = (UInt8 *)&data;
		x = *tmp;
		setValue(x);
	}

	void Byte::setValue(const String &v){
		_b_byte data;
		UInt8 *tmp, x;
		data.b0 = v.charAt(7) - '0';
		data.b1 = v.charAt(6) - '0';
		data.b2 = v.charAt(5) - '0';
		data.b3 = v.charAt(4) - '0';
		data.b4 = v.charAt(3) - '0';
		data.b5 = v.charAt(2) - '0';
		data.b6 = v.charAt(1) - '0';
		data.b7 = v.charAt(0) - '0';

		tmp = (UInt8 *)&data;
		x = *tmp;
		setValue(x);
	}

	/*const String &Byte::toString(){
		return str_value;
	}*/
	const std::string &Byte::toString(){
		//return str_value.toString();
		return *string_representation;
	}
	//End implementation of class: Byte
};
