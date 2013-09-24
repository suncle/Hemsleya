/*
 * active.cpp
 *
 *  Created on: 2013-1-21
 *      Author: qianqians
 */

#include "active.h"
#include "active_service.h"
#include "task.h"

namespace Hemsleya {
namespace active {

active::active(active_service & _active_service_, boost::function<void(void) > fn){
	task.fn = fn;
	_active_service_.push_task(&task);
}

active::~active(){
}

void active::join(){
	while(task.state != done){
		boost::this_thread::yield();
	}
}

} /* namespace active */
} /* namespace Hemsleya */