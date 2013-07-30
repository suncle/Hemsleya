/*
 * mirco_active.h
 *
 *  Created on: 2012-3-27
 *      Author: qianqians
 */

#ifndef MIRCO_ACTIVE_H_
#define MIRCO_ACTIVE_H_

#include <boost/atomic.hpp>
#include <boost/function.hpp>
#include <boost/thread/shared_mutex.hpp>

#include <Hemsleya/base/concurrent/container/msque.h>

namespace Hemsleya {
namespace active {

class active;
class active_server;

class mirco_active {
private:
	typedef boost::function<void(void) > event_handle;

public:
	mirco_active();
	~mirco_active();

	bool post(event_handle _handle);

	bool do_one();
	
	void run();

private:
	friend class active_server;

	active * owner;

	boost::shared_mutex _mu;

	Hemsleya::container::msque<event_handle > event_que;

};

} /* namespace active */
} /* namespace Hemsleya */
#endif /* MIRCO_ACTIVE_H_ */
