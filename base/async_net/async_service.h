/*
 * async_service.h
 *   Created on: 2012-10-16
 *       Author: qianqians
 * async_service
 */
#ifndef _NET_SERVICE_H
#define _NET_SERVICE_H

#ifdef _WIN32
#include "win32/winhdef.h"
#elif __linux__ 
//class socket_base_linux;
#endif

#include <boost/function.hpp>

#include <Hemsleya/base/concurrent/container/msque.h>
#include <Hemsleya/base/concurrent/abstract_factory/abstract_factory.h>

#include "error_code.h"

namespace Hemsleya { 
namespace async_net { 
namespace win32 { 
#ifdef _WIN32
class socket_base_win32;
#elif __linux__ 
class socket_base_linux;
#endif
}// win32

class async_service{
public:
	async_service();
	~async_service();

private:
	async_service(const async_service & _async_service){}

	void run();

private:
	void Init();

	bool network();

	bool do_one();

private:
#ifdef _WIN32
	HANDLE hIOCP;
	friend class win32::socket_base_win32;
#elif __linux__
	int epollfd_write, epollfd_read;
	friend class win32::socket_base_linux;
#endif //_WIN32

	boost::atomic_uint32_t thread_count;
	
	boost::uint32_t nConnect;
	unsigned long nMaxConnect;

};  

} //async_net
} //Hemsleya


#endif //_NET_SERVICE_H
