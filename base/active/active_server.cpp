/*
 * active_server.cpp
 *
 *  Created on: 2012-4-8
 *      Author: qianqians
 */

#include "active_server.h"
#include "mirco_active.h"

#include <Windows.h>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace Hemsleya {
namespace active {

active_server::active_server() {
	// TODO Auto-generated constructor stub

	_current_pool = &_active_pool[0];
	_backstage_pool = &_active_pool[1];
}

active_server::~active_server() {
	// TODO Auto-generated destructor stub
}

void active_server::do_wait(){
	boost::shared_lock<boost::shared_mutex> shared_lock(_swap_mu, boost::try_to_lock);

	mirco_active * _active = next_active.get();
	if (_active == 0){
		if ((_active = _current_pool->pop()) != 0){
			next_active.reset(_active);
		}
	}

	if (_active != 0){
		if (!_active->do_one()){
			next_active.release();
		}
	}
}

void active_server::run(){
	boost::shared_lock<boost::shared_mutex> shared_lock(_swap_mu, boost::try_to_lock);

	while(1){
		mirco_active * _active = next_active.release();
		if (_active == 0){
			mirco_active * _active = _current_pool->pop();
		}
		if (_active == 0){
			shared_lock.unlock();
			break;
		}

		_active->run();
		release_mirco_active(_active);
	}

	boost::unique_lock<boost::shared_mutex> lock(_swap_mu, boost::try_to_lock);
	if (lock.owns_lock()){
		std::swap(_current_pool, _backstage_pool);
	}
}

mirco_active * active_server::get_mirco_active(){
	mirco_active * _mirco_active = _free_active_pool.pop();
	if (_mirco_active == 0){
		_mirco_active = pool_mirco_active.allocate(1);
		::new (_mirco_active) mirco_active();
	}

	_backstage_pool->put(_mirco_active);

	return _mirco_active;
}

void active_server::release_mirco_active(mirco_active * _mirco_active){
	_free_active_pool.put(_mirco_active);
}

} /* namespace active */
} /* namespace Hemsleya */
