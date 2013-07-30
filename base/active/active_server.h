/*
 * active_server.h
 *
 *  Created on: 2012-4-8
 *      Author: qianqians
 */

#ifndef ACTIVE_SERVER_H_
#define ACTIVE_SERVER_H_

#include <vector>

#include <boost/thread.hpp>
#include <boost/atomic.hpp>
#include <boost/pool/pool_alloc.hpp>

#include <Hemsleya/base/concurrent/container/no_blocking_pool.h>

namespace Hemsleya {
namespace active {

class active;
class mirco_active;

class active_server {
public:
	active_server();
	~active_server();

	void do_wait();

	void run();

private:
	mirco_active * get_mirco_active();
	
	void release_mirco_active(mirco_active * _mirco_active);

private:
	friend class mirco_active;
	friend class active;

	boost::pool_allocator<mirco_active> pool_mirco_active;

	boost::shared_mutex _swap_mu;
	Hemsleya::container::no_blocking_pool<mirco_active> *_current_pool, *_backstage_pool;

	Hemsleya::container::no_blocking_pool<mirco_active> _free_active_pool;

	Hemsleya::container::no_blocking_pool<mirco_active> _active_pool[2];

};

} /* namespace active */
} /* namespace Hemsleya */
#endif /* ACTIVESERVER_H_ */
