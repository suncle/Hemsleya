/*
 * wait_any.cpp
 *  Created on: 2013-5-5
 *      Author: qianqians
 * wait_any
 */
#include "wait_any.h"
#include "detail/detail.h"
#include "exception/undefine_signal.h"

#include <boost/thread.hpp>
#include <boost/any.hpp>

#include <Hemsleya/base/concurrent/container/small_hash_map.h>
#include <Hemsleya/base/concurrent/abstract_factory/abstract_factory.h>

namespace Hemsleya{
namespace scheduling{

struct signal_{
	uint32_t token;
	boost::atomic_bool _flag;

	boost::mutex _mu;
	boost::any data;
};

Hemsleya::abstract_factory::abstract_factory<signal_> _abstract_factory_signal;
Hemsleya::container::small_hash_map<uint32_t, signal_*> _map_signal;

template <typename T>
T && data(uint32_t _signal){
	signal_ * _signal_;
	if (!_map_signal.search(_signal, _signal_)){
		throw exception::undefine_signal("undefine_signal", _signal);
	}
	
	return boost::any_cast<T>(_signal_->data);
}

uint32_t signal(){
	uint32_t token = detail::token();
	signal_ * _signal_ = _abstract_factory_signal.create_product();
	_signal_->token = token;
	_signal_->_flag.store(false);
	_map_signal.insert(token, _signal_);

	return token;
}

template <typename T>
T && wait_any(uint32_t _signal, boost::function<void() > DoWaitHandle, clock_t timeout){
	clock_t begin = clock();
	signal_ * _signal_;
	if (!_map_signal.search(_signal, _signal_)){
		throw exception::undefine_signal("undefine_signal", _signal);
	}

	while(!_signal_->_flag.load() && (begin + clock()) < timeout){
		DoWaitHandle();
	}

	return data<T>(_signal);
}

template <typename T>
void post(uint32_t _signal, const T & data){
	signal_ * _signal_;
	if (!_map_signal.search(_signal, _signal_)){
		throw exception::undefine_signal("undefine_signal", _signal);
	}

	_signal_->data = data;

	_signal_->_flag.store(true);
}

}// scheduling
}// Hemsleya