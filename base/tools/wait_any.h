/*
 * wait_any.h
 *  Created on: 2013-5-5
 *      Author: qianqians
 * wait_any
 */
#ifndef _WAIT_ANY_H
#define _WAIT_ANY_H

#include <string>

#include <boost/function.hpp>

#include <Hemsleya/base/concurrent/container/small_hash_map.h>

namespace Hemsleya{
namespace tools{

extern Hemsleya::container::small_hash_map<std::string, void*> wait_data;

void addwait(std::string key, void * data);

void* getwait(std::string key);

void wait_any(std::string key, boost::function<bool() > WaitConditionHandle, boost::function<void() > DoWaitHandle);

void wait();

}// tools
}// Hemsleya

#endif //_WAIT_ANY_H