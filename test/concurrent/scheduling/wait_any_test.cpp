/*
 * wait_any_test.h
 *  Created on: 2013-8-17
 *	    Author: qianqians
 * wait_any_test»ù×¼²âÊÔ
 */
#include <Hemsleya/base/concurrent/scheduling/wait_any.h>

uint32_t signal = 0;

struct test{
	int data;
};

void dowait(){
	test test;
	test.data = 1001;
	Hemsleya::scheduling::post(signal, test);
}

int main(){
	signal = Hemsleya::scheduling::signal();

	test t = Hemsleya::scheduling::wait_any<test>(signal, dowait);

	return 1;
}