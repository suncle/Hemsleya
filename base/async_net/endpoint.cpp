/*
 * endpoint.cpp
 *   Created on: 2013-10-9
 *       Author: qianqians
 * endpoint
 */
#include "endpoint.h"
#include "socket_tcp_impl.h"

#ifdef _WINDOWS
#include "windows/socket_function.h"
#elif __linux__ 
//class socket_base_linux;
#endif

#include "exception/AcceptException.h"
#include "exception/bindException.h"

namespace Hemsleya { 
namespace async_net { 

namespace TCP{

endpoint::endpoint(async_service & _service, const address & addr) : _pservice(&_service){
	_state = addr.version();

	if (_state == ipv4){
		s = ::socket(AF_INET, SOCK_STREAM, 0);
	}else if (_state == ipv6){
		s = ::socket(AF_INET6, SOCK_STREAM, 0);
	}
	
	if (bind(s, addr.getsockaddr(), addr.addrlen()) != 0){
		throw exception::bindException("bind fail", WSAGetLastError());
	}

	_service.addsocket(s);
}

endpoint::~endpoint(){
	CancelIo((HANDLE)s);
	closesocket(s);
}

void endpoint::async_accept(acceptstate _acceptstate){
	if (s == INVALID_SOCKET){
		throw exception::AcceptException("socket is invalid", 0);
	}

	socket _sa(*_pservice);
	TCP::async_accept(s, _sa.sptr->s, _sa.sptr->inbuff.buff, boost::bind(_acceptcallback, _sa));
}

void endpoint::registeracceptcallback(acceptcallback _acceptcallback_){
	while(_mutex.test_and_set());
	_acceptcallback = _acceptcallback_;
	_mutex.clear();
}

} //TCP

} //async_net
} //Hemsleya