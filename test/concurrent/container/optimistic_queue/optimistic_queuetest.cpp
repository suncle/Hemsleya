/*
 *  optimistic_queuetest.cpp
 *  Created on: 2013-8-17
 *	    Author: qianqians
 *  optimistic_queue»ù×¼²âÊÔ
 */
#include <Hemsleya\base\concurrent\container\optimistic_queue.h>
#include <Hemsleya\test\concurrent\container\testbase\base_test.h>

int main(){
	base_test<Hemsleya::container::optimistic_queue<test> > test;
	test();

	return 1;
}