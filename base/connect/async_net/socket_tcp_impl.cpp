/*
 * socket_tcp_impl.cpp
 *   Created on: 2013-10-4
 *       Author: qianqians
 * socket_tcp_impl
 */
#include "socket_tcp_impl.h"

#include <Hemsleya/base/concurrent/abstract_factory/abstract_factory.h>

// Exception
#include "exception/ConnectException.h"
#include "exception/SendException.h"
#include "exception/RecvException.h"
#include "exception/SendtoException.h"
#include "exception/RecvfromException.h"
#include "exception/bindException.h"

namespace Hemsleya { 
namespace async_net { 

namespace TCP{

socket_impl::socket_impl() : _revc_state(_no_recv), _connect_state(_not_connect){
}
	
socket_impl::~socket_impl(){
}

socket_impl::socket_impl(async_net::async_service & _service) : async_net::socket_impl(_service), _revc_state(_no_recv), _connect_state(_not_connect){
}

void socket_impl::async_connect(const address & addr){
	if (s == INVALID_SOCKET){
		throw exception::ConnectException("invalid socket");
	}

	if (_connect_state == _connect){
		throw exception::ConnectException("is connected");
	}

	TCP::async_connect(s, addr.getsockaddr(), fnconnectcallback);
}

void socket_impl::async_send(char * inbuf, uint32_t len){
	outbuff.write(inbuf, len, boost::bind(TCP::async_send, s, _1, fnsendcallback));
}

void socket_impl::async_recv(recv_state _state){
	if (_revc_state != _recv && _state == _recv){
		_revc_state = _state;

		TCP::async_recv(s, inbuff.buff, inbuff.max, fnrecvcallback);
	}
}

void socket_impl::registersendcallback(sendcallback _fnsendcallback){
	while(_sendcallbackmutex.test_and_set());
	fnsendcallback = _fnsendcallback;
	_sendcallbackmutex.clear();
}

void socket_impl::registerrecvcallback(recvcallback _fnrecvcallback){
	while(_recvcallbackmutex.test_and_set());
	fnrecvcallback = _fnrecvcallback;
	_sendcallbackmutex.clear();
}

void socket_impl::registerconnectcallback(connectcallback _fnconnectcallback){
	while(_connectcallbackmutex.test_and_set());
	fnconnectcallback = _fnconnectcallback;
	_connectcallbackmutex.clear();
}

Hemsleya::abstract_factory::abstract_factory<socket_impl> _abstract_factory_socket_impl;

socket_impl * create_socket_tcp_impl(async_service & _service){
	return _abstract_factory_socket_impl.create_product(_service);
}

void delete_socket_tcp_impl(socket_impl * _s){
	_abstract_factory_socket_impl.release_product(_s);
}

} //TCP

} //async_net
} //Hemsleya
