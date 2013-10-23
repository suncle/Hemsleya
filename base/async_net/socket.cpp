/*
 * socket.cpp
 *   Created on: 2013-10-11
 *       Author: qianqians
 * async_service
 */
#include "socket.h"

#include "async_service.h"
#include "socket_tcp_impl.h"
#include "socket_udp_impl.h"

namespace Hemsleya { 
namespace async_net { 
	
namespace TCP{

socket::socket(async_service & _service) : sptr(create_socket_tcp_impl(_service), delete_socket_tcp_impl){
}

socket::~socket(){
}

void socket::bind(const address & addr){
	sptr->bind(addr);
}

void socket::async_send(char * buf, uint32_t len){
	sptr->async_send(buf, len);
}

void socket::async_recv(recv_state _state){
	sptr->async_recv(_state);
}

void socket::async_connect(const address & addr){
	sptr->async_connect(addr);
}
	
void socket::shutdown(){
	sptr->shutdown();
}

void socket::cancelio(){
	sptr->cancelio();
}

void socket::registersendcallback(sendcallback _fnsendcallback){
	sptr->registersendcallback(_fnsendcallback);
}
	
void socket::registerrecvcallback(recvcallback _fnrecvcallback){
	sptr->registerrecvcallback(_fnrecvcallback);
}

void socket::registerconnectcallback(connectcallback _fnconnectcallback){
	sptr->registerconnectcallback(_fnconnectcallback);
}

} // TCP

namespace UDP{

socket::socket(async_service & _service) : sptr(create_socket_udp_impl(_service), delete_socket_udp_impl){
}

socket::~socket(){
}

void socket::bind(const address & addr){
	sptr->bind(addr);
}

void socket::shutdown(){
	sptr->shutdown();
}

void socket::cancelio(){
	sptr->cancelio();
}

} //UDP

} //async_net
} //Hemsleya
