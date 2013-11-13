/*
 * session.cpp
 *   Created on: 2013-10-26
 *       Author: qianqians
 * connect
 */
#include "session.h"
#include "connservice.h"

namespace Hemsleya { 
namespace connect {

enum udp_state{
	try_link1,
	try_link2,
};

session::session(connect::connservice & _service, const address & tcpaddr, const address & udpaddr) : 
pservice(&_service), tcpsocket(_service._service), udpsocket(_service._service){
	_state = no_conn;

	tcpsocket.bind(tcpaddr);
	udpsocket.bind(udpaddr);

	tcpsocket.registerconnectcallback(boost::bind(&session::onConnect, this));
}

session::~session(){
}

void session::connect(const address & remoteaddr){
	tcpsocket.async_connect(remoteaddr);
}

void session::onConnect(){
	_state = tcp_conn;

	sigConn();

	tcpsocket.registerrecvcallback(boost::bind(&session::onData, this, _1, _2));
}

void session::send(char * buff, uint32_t len){
	if (_state == tcp_conn){
		tcpsocket.async_send(buff, len);
	} else if (_state == udp_conn){
		char * tampbuff[4096];
		uint32_t * _id = (uint32_t *)tampbuff;
		*_id++ = id;
		memcpy((char*)_id, buff, len);

		udpsocket.async_sendto(&remoteaddr, buff, len);
	}
}

void session::onSend(){
	sigConn();
}

void session::onData(char * buff, uint32_t len){
	if (_state == tcp_conn){
		sigData(buff, len);
	} else if (_state == udp_conn){
		uint32_t * _id = (uint32_t *)buff;
		if (*_id++ == id){
			sigData((char*)_id, len-sizeof(uint32_t));
		}
	}
}



} //connect
} //Hemsleya
