/*
 * fsm.cpp
 *
 *  Created on: 2013-10-4
 *      Author: qianqians
 * Hemsleya fsm
 */
#include "fsm.h"

namespace Hemsleya{
namespace exception{

exception::exception(const char * info){
	std::stringstream strstream;
	strstream << info << " file:" << __FILE__ << " line:" << __LINE__;
	err = strstream.str();
}

exception::exception(const std::string & info){
	std::stringstream strstream;
	strstream << info << " file:" << __FILE__ << " line:" << __LINE__;
	err = strstream.str();
}

exception::exception(const char * info, int errcode){
	std::stringstream strstream;
	strstream << info << errcode << " file:" << __FILE__ << " line:" << __LINE__;
	err = strstream.str();
}

exception::exception(const std::string & info, int errcode){
	std::stringstream strstream;
	strstream << info << errcode << " file:" << __FILE__ << " line:" << __LINE__;
	err = strstream.str();
}

exception::~exception(){
}

const char * exception::what( ) const{
	return err.c_str();
}

exception::exception(){
}

}// exception
}// Hemsleya

