/*
 * context.h
 *
 *  Created on: 2013-9-14
 *      Author: qianqians
 * Hemsleya context
 */
#ifndef _CONTEXT_H
#define _CONTEXT_H

#include <boost/function.hpp>

namespace Hemsleya{
namespace context{

namespace detail {

#ifdef _WINDOWS
#include <Windows.h>
typedef LPVOID _context;
void WINAPI PFIBER_START_ROUTINE(LPVOID lpFiberParameter);
#endif // _WINDOWS

}//detail

class context{
public:
	context(boost::function<void()> _fn_handle);
	~context();

	void operator()();
	void yield(context & _context);
	
private:
	detail::_context _contex;
	boost::function<void()> fn_handle;

	friend void WINAPI detail::PFIBER_START_ROUTINE(LPVOID lpFiberParameter);

};

}// context
}// Hemsleya

#endif //_CONTEXT_H