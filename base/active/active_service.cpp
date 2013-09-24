/*
 * active_server.cpp
 *
 *  Created on: 2012-4-8
 *      Author: qianqians
 */

#include "active_service.h"
#include "scheduling.h"

namespace Hemsleya {
namespace active {

active_service::active_service() : _active_flag(0) {
}

active_service::~active_service() {
}

void active_service::push_task(task * _task){
	in_order_que.push(_task);
}

task * active_service::next_task() {
	task * _task = 0;
	in_order_que.pop(_task);
	return _task;
}
	
void active_service::run(){
	scheduling scheduling(this, 0);
	scheduling.run();
}

bool active_service::isRun(){
	return _active_flag.load() != 0;
}

} /* namespace active */
} /* namespace Hemsleya */
