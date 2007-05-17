/*
  $Id$

 Este header redefine el operador delete

*/
#ifndef __XVR2_OBJECT_H__
#error "Don't include this file directly, instead include xvr2/Object.h"
#endif

#ifndef ____XVR2_DESTRUCT_H__
#define ____XVR2_DESTRUCT_H__
namespace xvr2{
/**
 * \fn inline void xvr2_delete(__ttype_x &ptr)
 * \brief Use this function in place of the delete operator for pointers, after it has
 * been successfully called the argument will point to the NULL (0x0) address.
 * \param ptr Is a reference to the dinamically allocated resource to be deleted
 */
template<class __ttype_x>
inline void xvr2_delete(__ttype_x &ptr){
	delete ptr;
	ptr = 0;
}

/**
 * \fn void xvr2_delete_array(__ttype_y &array)
 * \brief Use this function in place of the delete[] operator for arrays, after it has
 * been successfully called the argument will point to the NULL (0x0) address.
 * \param array Is a reference to the dinamically allocated resource to be deleted
 */
template<class __ttype_y>
inline void xvr2_delete_array(__ttype_y &array){
	delete[] array;
	array = 0;
}


}
#endif
