/*
 * socket.h
 *   Created on: 2013-10-2
 *       Author: qianqians
 * socket
 */
#ifndef _SOCKET_H
#define _SOCKET_H

#include "enumdef.h"
#include "callbackdef.h"

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

namespace Hemsleya { 
namespace async_net { 

class async_service;
class address;

namespace TCP{

class socket_impl;

class socket{
public:
	socket(async_service & _service);
	~socket();

public:
	void bind(const address & addr);

	void async_send(char * buf, uint32_t len);

	void async_recv(recv_state _state);

	void async_connect(const address & addr);
	
	void shutdown();

	void cancelio();

public:
	void registersendcallback(sendcallback _fnsendcallback);
	
	void registerrecvcallback(recvcallback _fnrecvcallback);

	void registerconnectcallback(connectcallback _fnconnectcallback);

private:
	boost::shared_ptr<socket_impl> sptr;

	friend class endpoint;
	friend class async_service;

};  

} //TCP

namespace UDP{

class socket_impl;

class socket{
public:
	socket(async_service & _service);
	~socket();

	void bind(const address & addr);

	void async_sendto(const sockaddr * addr, char * buf, uint32_t len);

	void async_recvfrom(recv_state _state);

	void shutdown();

	void cancelio();

public:
	void registersendtocallback(sendtocallback _fnsendcallback);

	void registerrecvfromcallback(recvfromcallback _fnrecvcallback);

private:
	boost::shared_ptr<socket_impl> sptr;
	
	friend class async_service;

};

} //UDP

} //async_net
} //Hemsleya


#endif //_SOCKET_H
