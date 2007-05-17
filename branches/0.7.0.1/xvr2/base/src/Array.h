/*
 * $Id$
 */
#ifndef __XVR2_ARRAY_H__
#define __XVR2_ARRAY_H__
#include<xvr2/Container.h>
#include<xvr2/c_utilities.h>

namespace xvr2{
	namespace Util {
		/**
		 * \class Array Array.h
		 * \brief Please use this class to implement dynamic arrays of objects
		 */
		template<class T>
		class Array:public Container{
			protected:
				/**
				 * \var T *array
				 * Holds the actual data stored in the class, please note that this pointer
				 * has a template value, we want to make use and reuse of this class as
				 * much as possible, that is whay the class itself is a template
				 */
				T *array;
				/**
				 * \fn void copy(T *dst, T *src, unsigned int n)
				 * \brief Copies the contents of array src into dst
				 * \param dst Is a pointer to a destination array (it must be previously
				 * allocated and has to be larger or equal to src in size)
				 * \param src This pointer holds the data to be copied onto dst
				 * \param n Is the amount of elements to be copied from src to dst
				 */
				void copy(T dst[], T src[], unsigned int n){
					unsigned int i;
					for(i = 0; i < n; i++){
						dst[i] = src[i];
					}
				}
			public:
				/**
				 * \fn Array()
				 * \brief Default constructor, it initializes the array pointer and sets its datasize
				 * to zero
				 */
			#ifdef USING_GCC3
				Array(){
			#else
				Array():Container(xvr2::_xvr2Array){
			#endif
					array = 0;
					num_data = 0;
				}

				~Array(){
					delete[] array;
				}

				/**
				 * \fn Array &add(T data)
				 * \brief Dinamically allocates space for the new datum and then copies it
				 * to the internal array. This is a copy operation using the = operator, so
				 * the T class must have overriden the = operator overloaded.
				 * \param data The value to be added to the array.
				 * \return Returns a reference to the Array class instantiated.
				 */
				void add(T data){
					T *tmp;
					if(array == 0){
						array = new T[1];
						array[0] = data;
						num_data = 1;
					}
					else{
						tmp = new T[num_data + 1];
						copy(tmp, array, num_data);
						delete[] array;
						tmp[num_data] = data;
						array = tmp;
						num_data++;
					}
				}

				/**
				 * \fn T operator[](int idx)
				 * \brief Use the [] operator to obtain the datum contained in the idx position
				 * of the array
				 * \param idx Is the position where to find the datum you want
				 * \return a copy of the datum
				 * \todo Validate the idx number to be >= 0 and <= size()
				 */
				T &operator[](int idx) const{
					return array[idx];
				}
				T &operator[](int idx) {
					return array[idx];
				}

				/**
				 * \fn T get(int idx)
				 * \brief Same thing as the T Array::operator[](int idx) method
				 * \param idx Is the position where to find the datum you want
 				 * \return a copy of the datum
				 * \todo Validate the idx number to be >= 0 and <= size()
				 */
				T &get(int idx) const{
					return array[idx];
				}
				T &get(int idx) {
					return array[idx];
				}
		};
	};
};

#endif
