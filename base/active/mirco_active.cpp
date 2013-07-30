/*
 * mirco_active.cpp
 *
 *  Created on: 2012-3-27
 *      Author: qianqians
 */

#include "mirco_active.h"
#include "active_server.h"

namespace Hemsleya {
namespace active {

mirco_active::mirco_active() {
	// TODO Auto-generated constructor stub
}

mirco_active::~mirco_active() {
	// TODO Auto-generated destructor stub
}

bool mirco_active::post(event_handle _handle){
	boost::shared_lock<boost::shared_mutex> lock(_mu, boost::try_to_lock);
	if (!lock.owns_lock()){
		return false;
	}
	event_que.push(_handle);
	return true;
}

bool mirco_active::do_one(){
	boost::unique_lock<boost::shared_mutex> lock(_mu);

	event_handle _handle;

	if (!event_que.pop(_handle)){
		return false;
	}

	_handle();

	return true;
}

void mirco_active::run(){
	boost::unique_lock<boost::shared_mutex> lock(_mu);

	event_handle _handle;

	while(1){
		if (event_que.pop(_handle)){
			_handle();
		}else{
			break;
		}
	}
}

} /* namespace active */
} /* namespace Hemsleya */
