/*
 * endpoint.h
 *   Created on: 2013-10-2
 *       Author: qianqians
 * endpoint
 */
#ifndef _ENDPOINT_H
#define _ENDPOINT_H

#ifdef _WINDOWS
#include "windows/winhdef.h"
#elif __linux__ 
//class socket_base_linux;
#endif

#include "async_service.h"
#include "address.h"
#include "socket.h"
#include "callbackdef.h"
#include "enumdef.h"
#include "signaldef.h"

#include <boost/function.hpp>
#include <boost/atomic.hpp>

#include <Hemsleya/base/concurrent/container/msque.h>
#include <Hemsleya/base/concurrent/abstract_factory/abstract_factory.h>

namespace Hemsleya { 
namespace async_net { 

namespace TCP {
	
class endpoint{
public:
	endpoint(async_service & _service, const address & addr);
	~endpoint();

	void async_accept(acceptstate _acceptstate);

private:
	void acceptcallback(socket & s);

public:
	acceptsignal _acceptsignal;

private:
	boost::atomic_flag _mutex;

private:
	ipstate _state;
	async_service * _pservice;
	SOCKET s;

	friend class async_service;

};  

} // TCP

} //async_net
} //Hemsleya

#endif //_ENDPOINT_H
