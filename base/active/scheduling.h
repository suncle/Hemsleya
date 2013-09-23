/*
 * mirco_active_service.h
 *
 *  Created on: 2012-3-27
 *      Author: qianqians
 */

#ifndef SCHEDULING_H_
#define SCHEDULING_H_

#include <map>
#include <list>

#include <boost/atomic.hpp>
#include <boost/function.hpp>
#include <boost/thread/shared_mutex.hpp>

#include <Hemsleya/base/concurrent/abstract_factory/abstract_factory.h>
#include <Hemsleya/base/context/context.h>

namespace Hemsleya {
namespace active {

struct task;
class active_service;

class scheduling {
public:
	scheduling(active_service * _active_service_, boost::function<void(void)> _fn_scheduling_);
	~scheduling();

	void run();
	void work();
	bool onscheduling();

	void yield();

private:
	active_service * _active_service;
	
	context::context * _main_context;

	std::map<uint64_t, context::context * > time_wait_task_que;
	std::list<context::context * > in_signal_context_list;

	boost::function<void(void)> _fn_scheduling;

};

} /* namespace active */
} /* namespace Hemsleya */
#endif /* MIRCO_ACTIVE_SERVICE_H_ */
