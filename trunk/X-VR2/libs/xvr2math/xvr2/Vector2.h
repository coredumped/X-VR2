/*
 * $Id$
 */
#ifndef __XVR2_GFX_VECTOR2_H__
#define __XVR2_GFX_VECTOR2_H__
#include<xvr2/xvr2config.h>
#include<xvr2/xvr2mathdefs.h>
#include<xvr2/String.h>

namespace xvr2 {
namespace Math {

	/** This class implements 2-D Vectors.
	 * A 2-D vector is the composition of two scalar components named
	 * in algebra as X and Y, this class stores such components in the.
	 * c array so the 0th index corresponds to the X component and the
	 * 1st index corresponds to Y. */
	class Vector2:public xvr2::Object {
		protected:
			/** Holds the magnitud of the current vector, we call
			 * magnitud the hipotenuse of the resulting square triagle
			 * whose other two sides corresponds to the lenght of X 
			 * and Y. */
			Scalar mag;
		public:
			/** Holds the X and Y component values, c[0] corresponds to
			 * X and c[1] corresponds to Y. */
			Scalar c[2];
			/** Default constructor, initilizes mag to -1, since the 
			 * magnitud can never be negative we initilized it to this 
			 * value in order to the class to recalculate its value
			 * the next somebody asks for it by calling the magnitude()
			 * method. */
			Vector2();
			/** Call this constructor to directly initialize the X,Y 
			 * components in the class from a unidimensional array
			 * with two elements being each element the X,Y component
			 * respectively. */
			Vector2(const Scalar *_c);
			/** Initilizes the c[] array to the values specified by x and
			 * y a maps them to the 0th and 1st elements respectively, the
			 * mag variable is initilized to -1. */
			Vector2(const Scalar x, const Scalar y);
			/** Creates a new Vector2 as copy from another Vector2 object
			 * the c[] array and the mag variables are copied as well. */
			Vector2(const Vector2 &v);
			/** Dummy destructor, this guy doesn't really do anything useful. */
			~Vector2();
			/** Negation operator, call this guy to obtain the inverse Vector to
			 * this object. In here the ! operator is used in its mathematical
			 * sense, note that the ! operator is commonly used as boolean 
			 * negation, in here we used to strictly get the vector inverse
			 * representation. */
			const Vector2 operator! ();
			/** Equality operator, use it to verify if this vector is the
			 * same as its parameter, basically it verifies if X and Y 
			 * components are the same on both vectors, if they are, true is
			 * returned if not false. */
			const bool    operator==(const Vector2 &v);
			/** Inequality comparison, negates the above operator, returning 
			 * false if the X and Y components are the same, true in any other
			 * case. */
			const bool    operator!=(const Vector2 &v);
			/** Another form of the vector arithmetic addition, this method 
			 * adds the magnitud of the X and Y components of the parameter
			 * vector to this vector, just like in:
			 * \code
			 * Vector2 a(1, 1);
			 * Vector2 b(2, 2);
			 * a += b;
			 * // a.c[0] = 3
			 * // a.c[1] = 3 
			 * \endcode */
			const Vector2 operator+=(const Vector2 &v);
			/** Same as the += operator, however the v vector is inversed first
			 * so the resulting operation can be something like:
			 * \code
			 * Vector2 a(1, 1);
			 * Vector2 b(2, 2);
			 * a -= b;
			 * // a.c[0] = -1
			 * // a.c[1] = -1 
			 * \endcode */
			const Vector2 operator-=(const Vector2 &v);
			/** Dot product netween this vector and the
			 * Scalar s which expands to each component multiplied
			 * by the value of s */
			const Vector2 operator*=(const Scalar  s);
			/** Calculates and returns the unitarian vector corresponding
			 * to this one. */
			const Vector2 unit();
			/** Calculates the hipotenuse of the squared rectangle formed by the
			 * X and Y components by using the Pitagoras equation. This methods 
			 * recalcultes the magnitud only if the mag variables has been set
			 * to -1, if its value is greater than that then when you call this
			 * method the hipotenuse will be calculated again. */
			const Scalar  magnitude();
			/** Computes a String representation of the current vector and returns
			 * it as a pointer to a String object, after using this object dont
			 * forget to delete it from memory by using the xvr2_delete function.*/
			//const String *toString();
			const std::string &toString();
			/** Return the value of the x component by extracting it from the c[]
			 * array, the x component correspond to c[0] */
			const Scalar x(){
				return c[0];
			}
			/** Return the value of the y component by extracting it from the c[]
			 * array, the y component correspond to c[1] */
			const Scalar y(){
				return c[1];
			}
			/** Changes the X component to the value of x and resets the mag variable
			 * to -1 to force recalculation */
			const void setX(const Scalar x){
				c[0] = x;
				mag = -1;
			}
			/** Changes the Y component to the value of x and resets the mag variable
			 * to -1 to force recalculation */
			const void setY(const Scalar y){
				c[1] = y;
				mag = -1;
			}
			/** This is a great method, it let's you print the Vector2 X and Y components
			 * while using the cout object like this:
			 * \code
			 * Vector2 a(1, 1);
			 * cout << a << endl; //(1,1)
			 * \endcode */
			friend std::ostream& operator<<(std::ostream& stream, Vector2 s);
	};

	/** This function represents the vectorial sum operator, it basically adds to vectors 
	 * according to common linear algebra rules:
	 * \code
	 * Vector2 A(1, 1);
	 * Vector2 B(1, 1);
	 * Vector2 result;
	 * result = A + B;
	 * cout << A << "+" << B << "=" << result << endl; // (2,2)
	 * \endcode */
	inline const Vector2 operator+(const Vector2 &v1, const Vector2 &v2){
		return Vector2(v1.c[0] + v2.c[0], v1.c[1] + v2.c[1]);
	}

	/** Even though there is not vectorial substraction this operator is a vectorial addition
	 *  in which the second operator is inverted example below:
	 * \code
	 * Vector2 A(1, 1);
	 * Vector2 B(1, 1);
	 * Vector2 result;
	 * result = A - B;
	 * cout << A << " - " << B << " = " << result << endl;  // (0,0)
	 * result = A + !B;
	 * cout << A << " + !" << B << " = " << result << endl; // (0,0)
	 * //Both calculations return the same result.
	 * \endcode */
	inline const Vector2 operator-(const Vector2 &v1, const Vector2 &v2){
		return Vector2(v1.c[0] - v2.c[0], v1.c[1] - v2.c[1]);
	}

	/** Scalar product operation, this function lets you multiply both components of this vector
	 * with a scalar value following all linear algebra rules:
	 * \code
	 * Vector2 A(1, 1);
	 * Scalar n = 2;
	 * Vector2 result;
	 * result = n * A;
	 * cout << n << " * " << A << " = " << result << endl; // (2,2)
	 * \endcode */
	inline const Vector2 operator*(const Vector2 &v1, const Scalar s){
		return Vector2(v1.c[0] * s, v1.c[1] * s);
	}

	/** Vector dot product operation, same as the linear algebra operation, this operation
	 * will allways return an scalar value:
	 * \code
	 * Vector2 A(2, 3);
	 * Vector2 B(2, 2);
	 * Scalar result;
	 * result = A * B;
	 * cout << A << " * " << B << " = " << result << endl; // 10
	 * \endcode */
	inline const Scalar operator*(const Vector2 &v1, const Vector2 &v2){
		return v1.c[0] * v2.c[0] + v1.c[1] * v2.c[1];
	}
};
};

#endif

