/*
 * active.h
 *
 *  Created on: 2013-1-21
 *      Author: qianqians
 */
#ifndef _ACTIVE_H
#define _ACTIVE_H

#include <boost/function.hpp>

#include "task.h"

namespace Hemsleya {
namespace active {

class active_service;

class active {
public:
	active(active_service & _active_service_, boost::function<void(void) > fn);
	~active();

	void join();

private:
	task task;
	active_service * _active_service;

};

} /* namespace mirco_active */
} /* namespace Hemsleya */

#endif //_ACTIVE_H