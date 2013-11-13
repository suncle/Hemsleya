/*
 * socket_udp_impl.h
 *   Created on: 2013-10-20
 *       Author: qianqians
 * socket_udp_impl
 */
#ifndef _SOCKET_UDP_IMPL_H
#define _SOCKET_UDP_IMPL_H

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

namespace UDP{

class socket_impl : public async_net::socket_impl{
public:
	socket_impl();
	~socket_impl();

	socket_impl(async_net::async_service & _service);

public:
	void async_sendto(const sockaddr * addr, char * buf, uint32_t len);

private:
	writebuff outbuff;

public:
	void async_recvfrom(recv_state _state);

private:
	readbuf inbuff;
	recv_state _revc_state;

public:
	void registersendtocallback(sendtocallback _fnsendcallback);
	sendtocallback fnsendcallback;

private:
	boost::atomic_flag _sendcallbackmutex;

public:
	void registerrecvfromcallback(recvfromcallback _fnrecvcallback);
	recvfromcallback fnrecvcallback;

private:
	boost::atomic_flag _recvcallbackmutex;
	
private:
	friend class endpoint;

};  

socket_impl * create_socket_udp_impl(async_service & _service);
void delete_socket_udp_impl(socket_impl * _s);

}// UDP

} //async_net
} //Hemsleya


#endif //_SOCKET_UDP_IMPL_H
