/*
 * $Id$
 */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef __USE_GNU
#define __USE_GNU
#endif
#include<string.h>
#include"config.h"
#include<xvr2/xvr2config.h>
#include<xvr2/Util/c_utilities.h>
#include"_xvr2mathClassNames.h"
#include"Polygon.h"


namespace xvr2 {
	namespace Math {
		Polygon::Polygon():xvr2::Object(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Math_Polygon);
#endif
			ncoords = 0;
			nelems = 0;
			p = 0;
		}
		Polygon::Polygon(int numcoords):xvr2::Object(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Math_Polygon);
#endif
			ncoords = numcoords;
			nelems = 0;
			p = 0;
		}
		Polygon::Polygon(const Scalar *_points, int numcoords):xvr2::Object(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Math_Polygon);
#endif
			ncoords = numcoords;
			p = 0;
			addPoint(_points);
		}
		Polygon::Polygon(const Scalar *_points, int numcoords, int numelem):xvr2::Object(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Math_Polygon);
#endif
			ncoords = numcoords;
			p = 0;
			addData(_points, numelem);
		}
		void Polygon::addPoint(const Scalar *pdata){
			register int i;
			Scalar *tmp;
			void *pos;
			if(ncoords == 0)
				throw PolygonAlignmentException();
			if(p == 0){
				p = new Scalar[ncoords];
				for(i = 0; i < ncoords; i++){
					p[i] = pdata[i];
				}
				nelems++;
			}
			else{
				tmp = new Scalar[ncoords * (nelems + 1)];
				pos = __xvr2_util_mempcpy((void *)tmp, (void *)p, ncoords * nelems * sizeof(Scalar));
				++nelems;
				memcpy(pos, (void *)pdata, ncoords * sizeof(Scalar));
				delete[] p;
				p = tmp;
			}
		}
		void Polygon::addData(const Scalar *pdata, int numpoints){
			if(ncoords == 0)
				throw PolygonAlignmentException();
		}
	};
};
