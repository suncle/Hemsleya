/*
 * detail.h
 *  Created on: 2013-8-31
 *      Author: qianqians
 * detail
 */
#ifndef _SCHEDULING_DETAIL_H
#define _scheduling_detail_h

#include <boost/cstdint.hpp>

namespace Hemsleya{
namespace scheduling{

void wait();

namespace detail{

const uint32_t token();

void recover_token(const uint32_t token);

}// detail

}// scheduling
}// Hemsleya

#endif //_scheduling_detail_h