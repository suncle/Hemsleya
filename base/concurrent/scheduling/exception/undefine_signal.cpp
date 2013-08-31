/*
 * exception.h
 *
 *  Created on: May 22, 2013
 *      Author: qianqians
 * Hemsleya exception
 */
#include "undefine_signal.h"

namespace Hemsleya{
namespace scheduling{
namespace exception{

undefine_signal::undefine_signal(const char * info, int signal) : Hemsleya::exception::exception(info){
	std::stringstream strstream;
	strstream << info << "signal:" << signal;
	err = strstream.str();
}


const char * undefine_signal::what( ) const{
	return err.c_str();
}

undefine_signal::~undefine_signal(){
}

}// exception
}// scheduling
}// Hemsleya

