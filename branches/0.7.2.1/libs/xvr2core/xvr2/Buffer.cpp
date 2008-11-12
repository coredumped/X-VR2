#include "Buffer.h"
#if ((__GLIBC__ == 2) && (__GLIBC_MINOR__ > 7))
#include<cstring>
#else
#include<string>
#endif

namespace xvr2{

	Buffer::Buffer(){
		_data = 0;
		_size = 0;
		freeme = false;
	}
	
	Buffer::Buffer(void *__data, UInt32 __size, bool _freeme){
		if(_freeme){
			_data = new UInt8[__size];
			memcpy(_data, __data, __size);
		}
		else{
			_data = (UInt8 *)__data;
		}
		_size = __size;
		freeme = _freeme;
	}
	
	Buffer::Buffer(const void *__data, UInt32 __size, bool _freeme){
		if(_freeme){
			_data = new UInt8[__size];
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
			//UInt8 *buf = (UInt8 *)_data;
			delete[] _data;
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
			buf = new UInt8[1];
			buf[0] = v;
			_data = buf;
			_size = 1;
			freeme = true;
		}
		else{
			UInt8 *buf;
			buf = new UInt8[_size + 1];
			//Now copy the contents of data in buf
			memcpy(buf, _data, _size);
			//Append v
			buf[_size] = v;
			/*if(freeme){
				//Now free data
				UInt8 *b = (UInt8 *)_data;
				delete b;
				_data = 0;
			}
			else{		
				freeme = true;
			}*/
			empty();
			//Now point data to buf
			_data = buf;
			_size++;
		}
		return *this;
	}
	
	const Buffer &Buffer::append(const void *idata, UInt32 isize){
		if(data() == 0){
			UInt8 *buf;
			buf = new UInt8[isize];
			memcpy(buf, idata, isize);
			_data = buf;
			_size = isize;
			freeme = true;
		}
		else{
			UInt8 *buf;
			buf = new UInt8[_size + isize];
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
				delete[] _data;
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
	const Buffer &Buffer::insert(UInt32 pos, UInt8 v){
		insert(pos, (const void *)&v, sizeof(UInt8));
		return *this;
	}
	const Buffer &Buffer::insert(UInt32 pos, const void *__data, UInt32 __size){
		UInt8 *dest;
		if(pos > size()){
			throw xvr2::ArrayIndexOutOfLimits(pos, size());
		}
		dest = new UInt8[size() + __size];
		//Copy all data from _data up to position pos
#ifdef _GNU_SOURCE
		UInt8 *ptr1 = (UInt8 *)mempcpy(dest, data(), pos);
		UInt8 *ptr2 = (UInt8 *)mempcpy(ptr1, __data, __size) - 1;
		memcpy(ptr2, (void *)(((UInt8 *)data()) + pos), size() - pos);
#else
		UInt8 *ptr1 = (UInt8 *)(dest + pos);
		UInt8 *ptr2 = (UInt8 *)(dest + (pos + __size));
		memcpy(dest, data, pos);
		memcpy(ptr1, __data, __size);
		memcpy(ptr2, (void *)(((UInt8 *)data()) + pos), size() - pos);
#endif
		UInt32 _tmp_size = _size;
		empty();
		_data = dest;
		_size = _tmp_size + __size;
		freeme = true;
		return *this;
	}
	const Buffer &Buffer::insert(UInt32 pos, const Buffer &b){
		insert(pos, (const void *)b.data(), b.size());
		return *this;
	}
	const Buffer &Buffer::insert(UInt32 pos, const String &s){
		insert(pos, (const void *)s.toCharPtr(), s.size() + 1);
		if(pos + s.size() + 1 >= size()){
		} 
		return *this;
	}
	
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
		buf = new UInt8[__size];
		memcpy(buf, __data, __size);
		_data = buf;
		_size = __size;
		freeme = true;
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
		_data = (UInt8 *)b.data();
		_size = b.size();
		freeme = false;
		return *this;
	}
	const Buffer &Buffer::refTo(void *_buf, UInt32 _siz, bool __f){
		empty();
		_data = (UInt8 *)_buf;
		_size = _siz;
		freeme = __f;
		return *this;
	}
	
	//Empty
	void Buffer::empty(){
		if(freeme){
			freeme = false;
			delete[] _data;
			_size = 0;
		}
	}
	void Buffer::clear(){
		if(freeme){
			freeme = false;
			delete[] _data;
			_size = 0;
		}
	}

	std::string Buffer::toString(){
		return std::string((const char *)_data, _size - 1);
	}
};

