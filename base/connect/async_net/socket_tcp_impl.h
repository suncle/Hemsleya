/*
 * socket_tcp_impl.h
 *   Created on: 2013-10-4
 *       Author: qianqians
 * socket_tcp_impl
 */
#ifndef _SOCKET_TCP_IMPL_H
#define _SOCKET_TCP_IMPL_H

#include "async_service.h"
#include "address.h"
#include "writebuff.h"
#include "readbuff.h"
#include "enumdef.h"
#include "callbackdef.h"
#include "socket_base_impl.h"

#ifdef _WINDOWS
#include "windows/socket_function.h"
#elif __linux__ 
//class socket_base_linux;
#endif

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

namespace Hemsleya { 
namespace async_net { 

namespace TCP{

class socket_impl : public async_net::socket_impl{
public:
	socket_impl();
	~socket_impl();

	socket_impl(async_net::async_service & _service);

public:
	void async_send(char * buf, uint32_t len);

private:
	writebuff outbuff;

public:
	void async_recv(recv_state _state);

private:
	readbuf inbuff;
	recv_state _revc_state;

public:
	void async_connect(const address & addr);
	
private:
	connect_state _connect_state;

public:
	void registersendcallback(sendcallback _fnsendcallback);
	sendcallback fnsendcallback;

private:
	boost::atomic_flag _sendcallbackmutex;

public:
	void registerrecvcallback(recvcallback _fnrecvcallback);
	recvcallback fnrecvcallback;

private:
	boost::atomic_flag _recvcallbackmutex;
	
public:
	void registerconnectcallback(connectcallback _fnconnectcallback);
	connectcallback fnconnectcallback;
	
private:
	boost::atomic_flag _connectcallbackmutex;

private:
	friend class endpoint;

};  

socket_impl * create_socket_tcp_impl(async_service & _service);
void delete_socket_tcp_impl(socket_impl * _s);

}// TCP

} //async_net
} //Hemsleya


#endif //_SOCKET_TCP_IMPL_H
