/*
 * async_service.cpp
 *   Created on: 2012-11-14
 *       Author: qianqians
 * async_service
 */
#include "async_service.h"

namespace Hemsleya { 
namespace async_net { 

async_service::async_service(){
}

async_service::~async_service(){
}

void async_service::run(){
	_impl.run();
}

void async_service::addsocket(SOCKET s){
	_impl.addsocket(s);
}

} //async_net
} //Hemsleya
