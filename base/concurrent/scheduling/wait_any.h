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

template <typename T>
T * data(uint32_t _signal);

uint32_t signal();

void wait_any(uint32_t _signal, boost::function<void() > DoWaitHandle, clock_t timeout);

void post(uint32_t _signal);

}// scheduling
}// Hemsleya

#endif //_WAIT_ANY_H