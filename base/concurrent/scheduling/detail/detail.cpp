/*
 * detail.cpp
 *  Created on: 2013-8-31
 *      Author: qianqians
 * detail
 */
#include "detail.h"

#include <boost/atomic.hpp>
#include <boost/thread.hpp>

#include <Hemsleya/base/concurrent/container/optimisticque.h>

namespace Hemsleya{
namespace scheduling{

void wait(){
	boost::this_thread::sleep(boost::posix_time::microseconds(1));
}

namespace detail{

class detail{
	friend const uint32_t token();
	friend void recover_token(const uint32_t token);

private:
	static void initialize(){
		static boost::mutex _mu;

		boost::mutex::scoped_lock lock(_mu, boost::try_to_lock);
		if (lock.owns_lock()){
			uint32_t end = _token.load() + 1000;
			while(_token < end){
				_recover.push(_token++);
			}
		}
	}

	static boost::atomic_uint32_t _token;
	static Hemsleya::container::optimisticque<uint32_t> _recover;

};

const uint32_t token(){
	uint32_t token;
	
	while(!detail::_recover.pop(token)){
		detail::initialize();
	}

	return token;
}

void recover_token(const uint32_t token){
	detail::_recover.push(token);
}

}// detail

}// scheduling
}// Hemsleya
