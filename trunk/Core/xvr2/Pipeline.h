/*
 * $Id$
 *
 * X-VR2 
 * 
 * Copyright (C) Juan V. Guerrero 2007
 * 
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 * 
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#ifndef __XVR2_PIPELINE_H__
#define __XVR2_PIPELINE_H__
#include<xvr2/CoreExceptions.h>
#include<xvr2/SharedVar.h>
#include<xvr2/PipelineFilter.h>
#include<xvr2/String.h>
#include<xvr2/Vector.h>
#include<xvr2/Thread.h>
#include<xvr2/Map.h>
#include<xvr2/Queue.h>
#include<xvr2/Deque.h>
#include<xvr2/String.h>

namespace xvr2 {

	template<typename _Tp = xvr2::String >
	class Pipeline : public xvr2::Thread {
		public:
			typedef PipelineFilter<_Tp> PipelineFilterT;
		private:
			typedef Pipeline<_Tp> MyPipelineT;
			Int64 id_counter;
		protected:
			struct task {
				_Tp val;
				Int64 id;
				task(){
					id = 0;
					val = _Tp();
				}
				task(Int64 _id, const _Tp &v){
					id = _id;
					val = v;
				}
				task(const task &t){
					val = t.val;
					id = t.id;
				}
				task &operator=(const task &t){
					val = t.val;
					id = t.id;
					return *this;
				}
			};
			xvr2::Deque<task> pqueue;
			SharedVar<bool> is_active;
			xvr2::Vector< PipelineFilterT*  > filter;
			struct lt {
				bool operator()(int a, int b){
					return (a < b)?true:false;
				}
			};
			/** @brief A map containing which tasks have been completed. */
			xvr2::Map<Int64, bool, lt> fones;
			/** @brief A map containing filtering results. */
			xvr2::Map<Int64, _Tp, lt> dones;
		public:
			class Reader {
				private:
					MyPipelineT *pipeline;
				protected:
					Int64 id;
				public:
					Reader(){ }
					Reader(Int64 pid, MyPipelineT *_pipe){
						id = pid;
						pipeline = _pipe;
					}
					Reader(const Reader &t){
						id = t.id;
						pipeline = t.pipeline;
					}
					bool finished(){
						bool ret = false;
						pipeline->fones.lock();
						if(pipeline->fones[id]){
							ret = true;
						}
						pipeline->fones.unlock();
						return ret;
					}
					_Tp read(bool wait = false){
						if(!finished() && wait){
							while(!finished()) usleep(100);
						}
						pipeline->dones.lock();
						_Tp v = pipeline->dones[id];
						pipeline->dones.unlock();
						return _Tp(v);
					}
			};
			/** @brief Mandatory default constructor. */
			Pipeline() : xvr2::Thread() {
				id_counter = time(0);
			}
			
			~Pipeline(){
				
			}
			
			/** @brief Turns off this Pipeline processing. */
			void shutdown(){
				is_active = false;
			}
			
			Reader write(const _Tp &val){
				pqueue.lock();
				pqueue.push_back(task(id_counter, val));
				Reader t(id_counter++, this);
				pqueue.unlock();
				return Reader(t);
			}
			
			/** @brief Adds a new filtering function to the filtering vector. */
			void addFilter(PipelineFilterT *f){
				filter.lock();
				filter.push_back(f);
				filter.unlock();
			}
			
			void operator()(){
				while(is_active.getValue()){
					//Get a value from the input queue;
					pqueue.lock();
					if(pqueue.size() > 0){
						task ts = pqueue.front();
						pqueue.pop_front();
						pqueue.unlock();
						filter.lock();
						_Tp tmp;
						for(size_t i = 0; i < filter.size(); i++){
							if(i == 0){
								tmp = filter[i]->operator()(ts.val);
							}
							else{
								tmp = filter[i]->operator()(tmp);
							}
						}
						ts.val = tmp;
						filter.unlock();
						dones.lock();
						dones[ts.id] = ts.val;
						dones.unlock();
						fones.lock();
						fones[ts.id] = true;
						fones.unlock();
					}
					else{
						pqueue.unlock();
						usleep(100);
					}
				}
			}
			
			void run(){
				this->operator()();
			}
	};
}

#endif
