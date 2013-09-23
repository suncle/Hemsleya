/*
 * task.h
 *
 *  Created on: 2012-3-27
 *      Author: qianqians
 */

#ifndef TASK_H_
#define TASK_H_

#include <map>
#include <list>

#include <boost/atomic.hpp>
#include <boost/function.hpp>
#include <boost/thread/shared_mutex.hpp>

#include <Hemsleya/base/concurrent/abstract_factory/abstract_factory.h>
#include <Hemsleya/base/context/context.h>

namespace Hemsleya {
namespace active {

enum task_state{
	in_order,
	done,
};

struct task{
	task();
	~task();

	uint32_t state;
	uint64_t wait_time;
	boost::function<void() > fn;
};

} /* namespace active */
} /* namespace Hemsleya */
#endif /* TASK_H_ */
