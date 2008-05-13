/*
 * $Id$
 */

#include"StringCollection.h"

namespace xvr2 {
	namespace Util {
		StringCollection::StringCollection(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Util_StringCollection);
#endif
		}
		StringCollection::StringCollection(const StringCollection &sc){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Util_StringCollection);
#endif
			insert(begin(), sc.begin(), sc.end());
		}
		StringCollection::StringCollection(const std::vector<xvr2::String> &vec){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Util_StringCollection);
#endif
			insert(begin(), vec.begin(), vec.end());
		}
		StringCollection::StringCollection(const xvr2::String s[], int n):BasicStringCollection<String>(s, n){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Util_StringCollection);
#endif
		}
	};
};
