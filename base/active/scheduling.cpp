/*
 * mirco_active.cpp
 *
 *  Created on: 2012-3-27
 *      Author: qianqians
 */
#include "scheduling.h"
#include "active_service.h"
#include "task.h"

#include <Hemsleya/base/timer/clock.h>

namespace Hemsleya {
namespace active {

scheduling::scheduling(active_service * _active_service_, boost::function<void(void)> _fn_scheduling_){
	_active_service = _active_service_;
	_fn_scheduling = _fn_scheduling_;
}

scheduling::~scheduling(){
}

void scheduling::run(){
	context::context _contex(boost::bind(&scheduling::work, this));
	_main_context = &_contex;

	(*_main_context)();
}

void scheduling::work(){
	while(_active_service->isRun()){
		task * _task = _active_service->next_task();
		if (_task != 0){
			_task->fn();
			_task->state = done;
		}

		if(!onscheduling()){
			if(_task == 0){
				boost::this_thread::yield();
			}
		}
	}
}

bool scheduling::onscheduling(){
	context::context * _context = 0;
	
	{
		uint64_t t = timer::clock();
		std::map<uint64_t, context::context * >::iterator iterend = time_wait_task_que.upper_bound(t);
		for(std::map<uint64_t, context::context * >::iterator iter = time_wait_task_que.begin(); iter != iterend; iter++){
			_context = iter->second;
			goto do_task;
		}
	}
		
	{
		for(std::list<context::context * >::iterator iter = in_signal_context_list.begin(); iter != in_signal_context_list.end(); iter++){
			_context = *iter;
			goto do_task;
		}
	}

do_task:
	{
		if(_context != 0){
			context::yield(*_context);
			return true;
		}
	}

	return false;
}

void scheduling::yield(){
	context::yield(*_main_context);
}

} /* namespace active */
} /* namespace Hemsleya */
