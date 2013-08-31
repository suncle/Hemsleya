/*
 * undefine_signal.h
 *
 *  Created on: 2013-9-1
 *      Author: qianqians
 * undefine_signal
 */
#ifndef UNDEFINE_SIGNAL_H
#define UNDEFINE_SIGNAL_H

#include <Hemsleya/base/exception/exception.h>

namespace Hemsleya{
namespace scheduling{
namespace exception{

class undefine_signal : public Hemsleya::exception::exception{
public:
	undefine_signal(const char * info, int signal);
	~undefine_signal();

	virtual const char *what( ) const;

private:
	undefine_signal();

};

}// exception
}// scheduling
}// Hemsleya

#endif /* UNDEFINE_SIGNAL_H */
