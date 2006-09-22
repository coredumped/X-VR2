/* $Id$ */
#ifndef __XVR2_BUFFER_H__
#define __XVR2_BUFFER_H__

#include <xvr2/DataTypes.h>
#include <xvr2/CoreExceptions.h>
#include <xvr2/Object.h>
#include <xvr2/String.h> 

namespace xvr2{

	class Buffer : public Object{
		private:
			bool freeme;
		protected:
			UInt8 *_data;
			UInt32 _size;
		public:
			Buffer();
			Buffer(void *__data, UInt32 __size, bool _freeme = true);
			Buffer(const void *__data, UInt32 __size, bool _freeme = false);
			Buffer(const Buffer &b);
			virtual ~Buffer();
			UInt32 size();
			UInt32 size() const;

			//Read data
			/** Read all stored data */
			const void *data();
			const void *data() const;
			/** Returns the value of the byte stored at position pos */
			const UInt8 operator[](int pos);
			const UInt8 operator[](int pos) const;
			/** Returns the value of the byte stored at position pos */
			const UInt8 get(int pos);
			const UInt8 get(int pos) const;
			/** Returns a pointer to position pos within the buffer */
			const void *getBuf(int pos);
			const void *getBuf(int pos) const;
			
			//Append data
			const Buffer &append(UInt8 v);
			const Buffer &append(const void *__data, UInt32 __size);
			const Buffer &append(const Buffer &b);
			const Buffer &append(const String &s);
			const Buffer &operator<<(UInt8 v);
			const Buffer &operator<<(const Buffer &b);
			const Buffer &operator<<(const String &s);
			
			//Insert data
			const Buffer &insert(UInt32 pos, UInt8 v);
			const Buffer &insert(UInt32 pos, const void *__data, UInt32 __size);
			const Buffer &insert(UInt32 pos, const Buffer &b);
			const Buffer &insert(UInt32 pos, const String &s);
			
			//Remove data portions
			
			//Cloning
			Buffer cloneMe();
			static Buffer clone(const Buffer &b);
			
			//Copy/Assign
			/** Copies the contents of b */
			const Buffer &copy(const Buffer &b);
			const Buffer &copy(const void *__data, UInt32 __size);
			const Buffer &copy(UInt8 v);
			const Buffer &copy(const String &s);
			const Buffer &assign(const Buffer &b);
			const Buffer &assign(const void *__data, UInt32 __size);
			const Buffer &assign(UInt8 v);
			const Buffer &assign(const String &s);
			
			//Referencing
			/** Returns a reference to this object */
			Buffer ref();
			/** Converts this buffer in a reference of Buffer b. */
			const Buffer &refTo(const Buffer &b);
			const Buffer &refTo(void *_buf, UInt32 _siz);
			
			//Empty
			/** Clears the buffer contents */
			void empty();
			void clear();
	};

};

#endif
