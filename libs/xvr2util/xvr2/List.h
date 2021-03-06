/*
 $Id$

 This class is responsible for the management of linked lists using templates
 please take in account that this is not a thread safe class, so use it
 wisely
 */
#ifndef __XVR2_LIST_H__
#define __XVR2_LIST_H__
#include<xvr2/xvr2config.h>
#ifdef USE_EMBEDDED_CLASSNAMES
#include<xvr2/Util/_xvr2utilClassNames.h>
#endif
#include<xvr2/Util/Container.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2{
	namespace Util {
		using namespace xvr2;
		/**
		 * \class List List.h
		 * This class handles single linked lists using templates, 
		 * don't use this class if you intend to share it's data 
		 * between threads if you do please use the appropiate 
		 * semaphore or mutex code to prevent data corruption
		 * between threads, you have been warned
		 */
		template<class T>
		class List:public Container{
			protected:
				/**
				 * This subclass represents a node in the 
				 * list it stores the information in the 
				 * <b>data</b>* member and has a pointer to 
				 * the following node int the member 
				 * <b>next</b>
				 */
				class nodeT:public Container{
					public:
					/** Stores the information */
					T data;
					/** Keeps a pointer to the next 
					 *  node */
					nodeT *next;
					/** Keeps a pointer to the node 
					 *  before this */
					nodeT *before;
					/** 
					 * This is the default constructor, 
					 * initializes its data to zero 
					 * (NULL) and the next node to none 
					 * by making it point to NULL
					 */
#if __GNUC__ < 3
					nodeT():Container(_xvr2List__nodeT){
#else
					nodeT():Container(){
#endif
						next = 0;
						before = 0;
					}
					/** 
					 * This is the default constructor, 
					 * initializes its data to <b>d</b> 
					 * and the next node to none
					 * by making it point to <b>NULL</b>
					 */
					nodeT(T d){
#if __GNUC__ < 3
						setClassName(__xvr2_Util_List__nodeT);
#endif
						data = d;
						next = 0;
						before = 0;
					}
				};
				/**
				 * Keeps the index of the data in the middle 
				 * of the list */
				unsigned int middle;
				/**
				 * Points to the beginning of the list
				 */
				nodeT *list;
				/**
				 * Points to the beginning of the list
				 */
				nodeT *end;
				nodeT *act;
			public:
				/**
				 * This is the default constructor, it 
				 * initilizes all data to zero
				 */
				List(){
#if USE_EMBEDDED_CLASSNAMES
					Container(__xvr2_Util_List);
#endif
					list = 0;
					end = 0;
					act = 0;
				}
				/**
				 * By default we only destroy the list 
				 * itself, without destroying its data
				 */
				~List(){
					destroy();
				}
				/**
				 * Use this method to destroy the list 
				 * without destroying its data
				 */
				void destroy(){
					nodeT *q = 0, *t = 0;
					q = list;
					while(q != 0){
						t = q;
						q = q->next;
						delete t;
					}
				}
				/** 
				 * Appends an element to the end of the list 
				 */
				void add(T data){
					nodeT *q;
					q = new nodeT(data);
					if(list == 0){
						list = q;
						end = list;
					}
					else{
						end->next = q;
						q->before = end;
						end = q;
					}
					num_data++;
					middle = num_data / 2;
					act = list;
				}
				/**
				 * Removes an element from the end of the 
				 * list
				 */
				void remove(unsigned int idx){
					nodeT *q, *b, *a, *t;
					unsigned int i;
					q = list;
					b = list;
					if(idx < 0 || idx >= num_data)
						throw ElementNotFound();
					for(i = 0; q != 0; i++, q = q->next){
						if(i == idx){
							t = q;
							a = q->next;
							b->next = a;
							if(a != 0)
								a->before = b;
							if(t == list){
								if(list != 0){
									list = t->next;
									if(list != 0)
										list->before = 0;
								}
							}
							if(t == end){
								if(end != 0){
									end = end->before;
									if(end != 0)
										end->next = 0;
								}
							}
							delete t;
							num_data--;
							break;
						}
						b = q;
					}
				}
	
				/**
				 * Return the element at the j position of the 
				 * list starting by the head
				 */
				T get(unsigned int j){
					nodeT *r;
					nodeT *t;
					nodeT *q;
					unsigned int i;
					q = list;
					r = end;
					if(j >= num_data){
						throw ArrayIndexOutOfLimits();
					}
					if(j < middle){
						for(i = 0; i != j; i++)
							q=q->next;
						t = q;
					}
					else{
						for(i = num_data - 1; i != j; i--)
							r=r->before;
						t = r;
					}
					return t->data;
				}
	
				/**
				 * Obtains the current element
				 */
				T &get() const{
					if(act != 0){
						return act->data;
						act = act->next;
					}
					return (T)0;
				}
				/**
				 * Obtains the current element
				 */
				T &get(){
					if(act != 0){
						return act->data;
						act = act->next;
					}
					return (T)0;
				}
	
				/**
				 * Rewinds the list
				 */
				void rewind(){
					act = list;
				}
	
		};
	};
};

#endif
