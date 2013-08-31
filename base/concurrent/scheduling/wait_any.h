/*
 * wait_any.h
 *  Created on: 2013-5-5
 *      Author: qianqians
 * wait_any
 */
#ifndef _WAIT_ANY_H
#define _WAIT_ANY_H

#include <ctime>
#include <string>

#include <boost/function.hpp>

namespace Hemsleya{
namespace scheduling{

uint32_t signal();

template <typename T>
T && wait_any(uint32_t _signal, boost::function<void() > DoWaitHandle, clock_t timeout);

template <typename T>
void post(uint32_t _signal, const T & data);

}// scheduling
}// Hemsleya

#endif //_WAIT_ANY_H