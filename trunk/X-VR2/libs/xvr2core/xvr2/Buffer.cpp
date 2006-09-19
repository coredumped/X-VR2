#include "Buffer.h"

namespace xvr2{

	Buffer::Buffer(){
		_data = 0;
		_size = 0;
		freeme = false;
	}
	
	Buffer::Buffer(void *__data, UInt32 __size, bool _freeme){
		UInt8 *buf;
		if(_freeme){
			buf = new UInt8(__size);
			_data = buf;
			memcpy(_data, __data, __size);
		}
		else{
			_data = __data;
		}
		_size = __size;
		freeme = _freeme;
	}
	
	Buffer::Buffer(const void *__data, UInt32 __size, bool _freeme){
		UInt8 *buf;
		if(_freeme){
			buf = new UInt8(__size);
			_data = buf;
			memcpy(_data, __data, __size);
		}
		else{
			_data = _data;
		}
		_size = __size;
		freeme = _freeme;
	}
	
	Buffer::Buffer(const Buffer &b){
		_data = b._data;
		_size = b._size;
		freeme = false;
	}

	Buffer::~Buffer(){
		if(freeme){
			UInt8 *buf = (UInt8 *)_data;
			delete buf;
			_data = 0;
			_size = 0;
			freeme = false;
		}
	}

	UInt32 Buffer::size(){
		return _size;
	}
	UInt32 Buffer::size() const{
		return _size;
	}
	
	//Data reading
	const void *Buffer::data(){
		return _data;
	}
	const void *Buffer::data() const{
		return _data;
	}
	const UInt8 Buffer::operator[](int pos){
		return get(pos);
	}
	const UInt8 Buffer::operator[](int pos) const{
		return get(pos);
	}
	const UInt8 Buffer::get(int pos){
		if(_data == 0){
			throw NullPointer();
		}
		/*else if(pos >= _size){
			throw Array
		}*/
		return ((UInt8 *)_data)[pos];
	}
	const UInt8 Buffer::get(int pos) const{
		if(_data == 0){
			throw NullPointer();
		}
		return ((UInt8 *)_data)[pos];
	}
	const void *Buffer::getBuf(int pos){
		if(data() == 0){
			throw NullPointer();
		}
		return (const void *)(((UInt8 *)_data) + pos);
	}
	const void *Buffer::getBuf(int pos) const{
		if(data() == 0){
			throw NullPointer();
		}
		return (const void *)(((UInt8 *)_data) + pos);
	}
	
	//Data appending
	const Buffer &Buffer::append(UInt8 v){
		if(data() == 0){
			UInt8 *buf;
			buf = new UInt8(1);
			buf[0] = v;
			_data = buf;
			_size = 1;
			freeme = true;
		}
		else{
			UInt8 *buf;
			buf = new UInt8(_size + 1);
			//Now copy the contents of data in buf
			memcpy(buf, _data, _size);
			//Append v
			buf[_size] = v;
			if(freeme){
				//Now free data
				UInt8 *b = (UInt8 *)_data;
				delete b;
				_data = 0;
			}
			else{		
				freeme = true;
			}
			//Now point data to buf
			_data = buf;
			_size++;
		}
		return *this;
	}
	
	const Buffer &Buffer::append(const void *idata, UInt32 isize){
		if(data() == 0){
			UInt8 *buf;
			buf = new UInt8(isize);
			memcpy(buf, idata, isize);
			_data = buf;
			_size = isize;
			freeme = true;
		}
		else{
			UInt8 *buf;
			buf = new UInt8(_size + isize);
#ifdef _GNU_SOURCE
			//Now copy the contents of data in buf
			void *ptr = mempcpy(buf, _data, _size);
			//Append idata
			memcpy(ptr, idata, isize); 
#else
			//Now copy the contents of data in buf
			memcpy(buf, _data, _size);
			//Append idata
			memcpy(buf + _size, idata, isize); 
#endif
			if(freeme){
				//Now free data
				delete (UInt8 *)_data;
				_data = 0;
			}
			else{		
				freeme = true;
			}
			//Now point data to buf
			_data = buf;
			_size += isize;
		}
		return *this;
	}
	const Buffer &Buffer::append(const Buffer &b){
		append(b.data(), b.size());
		return *this;
	}
	const Buffer &Buffer::append(const String &s){
		append((void *)s.toCharPtr(), s.size());
		return *this;
	}
	const Buffer &Buffer::operator<<(UInt8 v){
		append(v);
		return *this;
	}
	const Buffer &Buffer::operator<<(const Buffer &b){
		append(b);
		return *this;
	}
	const Buffer &Buffer::operator<<(const String &s){
		append(s);
		return *this;
	}
	
	//Insert methods
	
	//Cloning methods
	Buffer Buffer::cloneMe(){
		return Buffer(data(), size(), true);
	}
	Buffer Buffer::clone(const Buffer &b){
		return Buffer(b.data(), b.size(), true);
	}
	
	//Copying/Assigning
	const Buffer &Buffer::copy(const Buffer &b){
		copy(b.data(), b.size());
		return *this;
	}
	const Buffer &Buffer::copy(const void *__data, UInt32 __size){
		empty();
		UInt8 *buf;
		buf = new UInt8(__size);
		memcpy(buf, __data, __size);
		_data = buf;
		_size = __size;
		return *this;
	}
	const Buffer &Buffer::copy(UInt8 v){
		copy((const void *)&v, 1);
		return *this;
	}
	const Buffer &Buffer::copy(const String &s){
		copy((const void *)s.toCharPtr(), s.size());
		return *this;
	}
	const Buffer &Buffer::assign(const Buffer &b){
		copy(b);
		return *this;
	}
	const Buffer &Buffer::assign(const void *__data, UInt32 __size){
		copy(__data, __size);
		return *this;
	}
	const Buffer &Buffer::assign(UInt8 v){
		copy(v);
		return *this;
	}
	const Buffer &Buffer::assign(const String &s){
		copy(s);
		return *this;
	}
	//Referencing
	Buffer Buffer::ref(){
		return Buffer(data(), size(), false);
	}
	const Buffer &Buffer::refTo(const Buffer &b){
		empty();
		_data = (void *)b.data();
		_size = b.size();
		freeme = false;
	}
	const Buffer &Buffer::refTo(void *_buf, UInt32 _siz){
		empty();
		_data = _buf;
		_size = _siz;
		freeme = false;
	}
	
	//Empty
	void Buffer::empty(){
		if(freeme){
			freeme = false;
			delete (UInt8 *)_data;
			_size = 0;
		}
	}
	void Buffer::clear(){
		if(freeme){
			freeme = false;
			delete (UInt8 *)_data;
			_size = 0;
		}
	}
};
