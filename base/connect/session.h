/*
 * session.h
 *   Created on: 2013-10-26
 *       Author: qianqians
 * session
 */
#ifndef _SESSION_H
#define _SESSION_H

#include <Hemsleya/base/async_net/async_net.h>

#include <boost/signals2.hpp>

#include "address.h"

namespace Hemsleya { 
namespace connect {

class connservice;

enum session_state{
	no_conn,
	tcp_conn,
	udp_conn,
};

class session{
public:
	session(connect::connservice & _service, const address & tcpaddr, const address & udpaddr);
	~session();

private:
	session();

public:
	void connect(const address & remoteaddr);

	void send(char * buff, uint32_t len);

	boost::signals2::signal<void() > sigConn;

	boost::signals2::signal<void() > sigSend;

	boost::signals2::signal<void(char * , uint32_t) > sigData;

private:
	void onConnect();

	void onSend();

	void onData(char * buff, uint32_t len);

private:
	session_state _state;

	async_net::TCP::socket tcpsocket;
	async_net::UDP::socket udpsocket;

	address remoteaddr;

	connservice * pservice;

	uint32_t id;

	friend class connservice;

};  

} //connect
} //Hemsleya


#endif //_SESSION_H
