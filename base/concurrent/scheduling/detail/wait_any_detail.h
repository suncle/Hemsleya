/*
 * wait_any.h
 *  Created on: 2013-5-5
 *      Author: qianqians
 * wait_any
 */
#ifndef _WAIT_ANY_DETAIL_H
#define _WAIT_ANY_DETAIL_H

#include <ctime>
#include <string>

#include <boost/any.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/atomic.hpp>

namespace Hemsleya{
namespace scheduling{

extern clock_t MaximumOuttime;

struct signal_{
	signal_(uint32_t nToken) : token(nToken), _flag(false){
	}

	uint32_t token;
	boost::atomic_bool _flag;

	boost::mutex _mu;
	boost::any data;
};

namespace detail{

signal_ * get_signal(uint32_t signal);
void release_signal(signal_ * _signal_);

}

}// scheduling
}// Hemsleya

#endif //_WAIT_ANY_DETAIL_H