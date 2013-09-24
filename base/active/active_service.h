/*
 * active_server.h
 *
 *  Created on: 2012-4-8
 *      Author: qianqians
 */

#ifndef ACTIVE_SERVER_H_
#define ACTIVE_SERVER_H_

#include <vector>

#include <boost/thread.hpp>
#include <boost/atomic.hpp>

#include <Hemsleya/base/concurrent/container/msque.h>

namespace Hemsleya {
namespace active {

struct task;
class active;
class mirco_active_service;

class active_service {
public:
	active_service();
	~active_service();

	void push_task(task * _task);

	task * next_task();
	
	void run();

	bool isRun();

private:
	boost::atomic_int32_t _active_flag;
	container::msque<task * > in_order_que;

};

} /* namespace active */
} /* namespace Hemsleya */
#endif /* ACTIVESERVER_H_ */
