/*
 * swapquebasetest.cpp
 *  Created on: 2013-8-17
 *	    Author: qianqians
 * swapquebasetest��׼����
 */
#include <Hemsleya\base\concurrent\container\ringque.h>
#include <Hemsleya\test\concurrent\container\testbase\base_test.h>

int main(){
	base_test<Hemsleya::container::ringque<test> > test;
	test(100);

	return 1;
}