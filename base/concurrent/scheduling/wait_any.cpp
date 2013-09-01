/*
 * wait_any.cpp
 *  Created on: 2013-5-5
 *      Author: qianqians
 * wait_any
 */
#include "wait_any.h"
#include "detail/detail.h"
#include "detail/wait_any_detail.h"
#include "exception/undefine_signal.h"

#include <Hemsleya/base/concurrent/container/small_hash_map.h>
#include <Hemsleya/base/concurrent/abstract_factory/abstract_factory.h>

namespace Hemsleya{
namespace scheduling{

namespace detail{

Hemsleya::abstract_factory::abstract_factory<signal_> _abstract_factory_signal;
Hemsleya::container::small_hash_map<uint32_t, signal_*> _map_signal;

signal_ * get_signal(uint32_t _signal){
	signal_ * _signal_;
	if (!_map_signal.search(_signal, _signal_)){
		throw exception::undefine_signal("undefine_signal", _signal);
	}
	
	return _signal_;
}

void release_signal(signal_ * _signal_){
	detail::recover_token(_signal_->token);
	_abstract_factory_signal.release_product(_signal_);
}

}//detail

clock_t MaximumOuttime = -1;

uint32_t signal(){
	uint32_t token = detail::token();
	signal_ * _signal_ = detail::_abstract_factory_signal.create_product(token);
	detail::_map_signal.insert(token, _signal_);

	return token;
}

}// scheduling
}// Hemsleya