/* $Id$ */
#ifndef __XVR2_BUFFER_H__
#define __XVR2_BUFFER_H__

#include <xvr2/DataTypes.h>
#include <xvr2/CoreExceptions.h>
#include <xvr2/Object.h>
#include <xvr2/String.h> 

namespace xvr2{
	/** \class Buffer
	 *  Represents a data block and as such it holds a data store and a means
	 *  to account the amount of stored data.
	 *  Buffers has two operation modes:
	 *  1. They can be references to another Buffers in the same way a
	 *     pointer points to an already defined data block.
	 *  2. They can be copies of existing data blocks.
	 *  In case #2 during the object destruction the contents of the data store
	 *  will be properly freed from memory, however for case #1 they won't since
	 *  they are "pointing" to a data block defined externally to them, so it is
	 *  responsability of the other end to properly release the data block after it
	 *  is used, in either case you must take care that if the external data block
	 *  is released your Buffer will be pointing to that old memory address just
	 *  like standard pointers do, you have been warned. */ 
	class Buffer : public Object{
		private:
			/** Tells whether the data store is a reference or copy
			 *  of an exiting buffer, if it is copy its value will
			 *  be true, so the destructor can delete[] _data, however
			 *  if it is false no such operation takes place. */ 
			bool freeme;
		protected:
			/** The buffer's data store itself, this might point to another
			 *  datastore or just be a copy of another datastore, if
			 *  it is a copy then freeme will be set to true, however if it
			 *  is a pointer to an external datastore then freeme will be
			 *  false. This variable is also commonly called as data store. */
			UInt8 *_data;
			/** Holds the amount of data bytes stored in _data. */
			UInt32 _size;
		public:
			/** Default constructor, initializes _data and _size to 0
			 *  and sets freeme to false. (A reference to NULL) */
			Buffer();
			/** If freeme is true, then it will construct a Buffer which
			 *  its data store will be a copy of __data, however if freeme
			 *  is false then if will be just a reference to __data so 
			 *  the contents of _data will not be delete[] during the
			 *  destruction stage. (By default it will create a copy
			 *  buffer) */
			Buffer(void *__data, UInt32 __size, bool _freeme = true);
			/** If freeme is true, then it will construct a Buffer which
			 *  its data store will be a copy of __data, however if freeme
			 *  is false then if will be just a reference to __data so 
			 *  the contents of _data will not be delete[] during the
			 *  destruction stage. (By default it will create a
			 *  reference buffer) */
			Buffer(const void *__data, UInt32 __size, bool _freeme = false);
			/** Creates a reference buffer whose _data will point to b._data
			 *  and its datastore won't be freed during the object's
			 *  destruction. */ 
			Buffer(const Buffer &b);
			/** The destructor will attept to free the data store only if
			 *  freeme has been set to true, the idea behind this is that
			 *  only copied buffers need to delete its datastore (because
			 *  they're copies) and references will not (because their data
			 *  store is not actually theirs). */
			virtual ~Buffer();
			/** Returns the amount of bytes stored in the data store. */
			UInt32 size();
			/** Returns the amount of bytes stored in the data store. */
			UInt32 size() const;

			//Read data
			/** Returns a pointer to the data store. */
			const void *data();
			/** Returns a pointer to the data store. */
			const void *data() const;
			/** Returns the value of the byte stored at position pos. */
			const UInt8 operator[](int pos);
			/** Returns the value of the byte stored at position pos. */
			const UInt8 operator[](int pos) const;
			/** Returns the value of the byte stored at position pos. */
			const UInt8 get(int pos);
			/** Returns the value of the byte stored at position pos. */
			const UInt8 get(int pos) const;
			/** Returns a pointer to position pos within the data store. */
			const void *getBuf(int pos);
			/** Returns a pointer to position pos within the data store. */
			const void *getBuf(int pos) const;
			
			//Append data
			/** Appends (inserts at the end) the value of v to the data store. */
			const Buffer &append(UInt8 v);
			/** Appends (inserts at the end) the datablock pointed by __data 
			 *  with size __size to the data store. */
			const Buffer &append(const void *__data, UInt32 __size);
			/** Appends (inserts at the end) the Buffer b to the data store. */
			const Buffer &append(const Buffer &b);
			/** Appends (inserts at the end) the String s to the data store. */
			const Buffer &append(const String &s);
			/** Appends (inserts at the end) the value of v to the data store. */
			const Buffer &operator<<(UInt8 v);
			/** Appends (inserts at the end) the Buffer b to the data store. */
			const Buffer &operator<<(const Buffer &b);
			/** Appends (inserts at the end) the String s to the data store. */
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
			const Buffer &refTo(void *_buf, UInt32 _siz, bool __f = false);
			
			//Empty
			/** Clears the buffer contents */
			void empty();
			void clear();
	};

};

#endif
