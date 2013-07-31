/*
 * active.cpp
 *
 *  Created on: 2013-1-21
 *      Author: qianqians
 */

#include "active.h"
#include "mirco_active.h"
#include "active_server.h"

namespace Hemsleya {
namespace active {

active::active(active_server & _active_server_) : _active_server(&_active_server_), _is_cancel(false){
	_mirco_active = _active_server->get_mirco_active();
}

active::~active() {
	_active_server->release_mirco_active(_mirco_active);
}

void active::post(event_handle _handle){
	while(!_mirco_active->post(_handle)){
		do{
			boost::unique_lock<boost::shared_mutex> lock(_mu, boost::try_to_lock);
			if (lock.owns_lock()){
				_mirco_active = _active_server->get_mirco_active();
				lock.unlock();
				break;
			}
			
			boost::shared_lock<boost::shared_mutex> shared_lock(_mu);
		}while(0);
	}
}

void active::cancel(){
	_is_cancel.store(true);
}

bool active::is_cancel(){
	return _is_cancel.load();
}

} /* namespace active */
} /* namespace Hemsleya */