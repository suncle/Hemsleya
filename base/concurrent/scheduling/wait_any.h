/*
 * wait_any.h
 *  Created on: 2013-5-5
 *      Author: qianqians
 * wait_any
 */
#ifndef _WAIT_ANY_H
#define _WAIT_ANY_H

#include "detail/wait_any_detail.h"

#include <ctime>
#include <string>

#include <boost/function.hpp>

namespace Hemsleya{
namespace scheduling{

uint32_t signal();

template <typename T>
T wait_any(uint32_t _signal, boost::function<void() > DoWaitHandle, clock_t timeout = MaximumOuttime){
	clock_t begin = clock();
	signal_ * _signal_ = detail::get_signal(_signal);

	while(!_signal_->_flag.load() && (begin + clock()) < (unsigned long)timeout){
		DoWaitHandle();
	}

	T ret = boost::any_cast<T>(_signal_->data);
	detail::release_signal(_signal_);

	return ret;
}

template <typename T>
void post(uint32_t _signal, const T & data){
	signal_ * _signal_ = detail::get_signal(_signal);

	_signal_->data = data;
	_signal_->_flag.store(true);
}

}// scheduling
}// Hemsleya

#endif //_WAIT_ANY_H