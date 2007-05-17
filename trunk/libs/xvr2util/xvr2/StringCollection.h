/*
 * $Id$
 */
#ifndef __XVR2_STRING_COLLECTION_H__
#define __XVR2_STRING_COLLECTION_H__
#include<xvr2/xvr2config.h>
#include<xvr2/CoreExceptions.h>
#include<xvr2/String.h>
#ifdef USE_EMBEDDED_CLASSNAMES
#include<xvr2/Util/_xvr2utilClassNames.h>
#endif
#include<vector>

namespace xvr2 {
	namespace Util {
		/** \class BasicStringCollection StringCollection.h <xvr2/StringCollection.h>
		 *  This template class represents the collection of several other strings of
		 *  type _strType, these strings must be derived from xvr2::BasicString */
		template<typename _strType>
		class BasicStringCollection:public Object, public std::vector<_strType> {
			private:
			protected:
			public:
				/** Default constructor, it does nothing */
				BasicStringCollection(){
#ifdef USE_EMBEDDED_CLASSNAMES
					setClassName(__xvr2_Util_BasicStringCollection);
#endif
				}
				/** Constructs a BasicStringCollection instance from another.
				 *  \param[in] bsc The BasicStrincCollection to be copied from */
				BasicStringCollection(const BasicStringCollection<_strType> &bsc){
#ifdef USE_EMBEDDED_CLASSNAMES
					setClassName(__xvr2_Util_BasicStringCollection);
#endif
					insert(std::vector<_strType>::begin(), bsc.begin(), bsc.end());
				}
				/** Constructs a BasicStringCollection instance from a std::vector<_strType>.
				 *  \param[in] vec The std::vector<_strType> to be copied from */
				BasicStringCollection(const std::vector<_strType> &vec){
#ifdef USE_EMBEDDED_CLASSNAMES
					setClassName(__xvr2_Util_BasicStringCollection);
#endif
					insert(std::vector<_strType>::begin(), vec.begin(), vec.end());
				}
				/** Constructs a BasicStringCollection instance from a _strType[].
				 *  \param[in] s The _strType[] array to be copied from.
				 *  \param n The amount of elements contained in s. */
				BasicStringCollection(const _strType s[], int n){
#ifdef USE_EMBEDDED_CLASSNAMES
					setClassName(__xvr2_Util_BasicStringCollection);
#endif
					for(int i = 0; i < n; i++){
						push_back(s[i]);
					}
				}
		};
	
		/** \class StringCollection StringCollection.h <xvr2/StringCollection.h>
		 *  This class represents the collection of several other strings of
		 *  type xvr2::String. */
		class StringCollection : public BasicStringCollection<xvr2::String> {
			private:
			protected:
			public:
				/** Default constructor, it does nothing */
				StringCollection();
				/** Constructs a StringCollection instance from another.
				 *  \param[in] sc The StrincCollection to be copied from */
				StringCollection(const StringCollection &sc);
				/** Constructs a StringCollection instance from a std::vector<xvr2::String>.
				 *  \param[in] vec The std::vector<xvr2::String> to be copied from */
				StringCollection(const std::vector<xvr2::String> &vec);
				/** Constructs a StringCollection instance from a String[].
				 *  \param[in] s The xvr2::String[] array to be copied from.
				 *  \param n The amount of elements contained in s. */
				StringCollection(const xvr2::String s[], int n);
		};
	};
};

#endif
