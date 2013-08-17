/*
 * base_test.h
 *  Created on: 2013-8-17
 *	    Author: qianqians
 * base_test: lock-free que »ù×¼²âÊÔÓÃÀı
 */
#ifndef _BASE_TEST_H
#define _BASE_TEST_H

#include <boost/atomic.hpp>
#include <ctime>
#include <iostream>
#include <process.h>
#include <Hemsleya\base\concurrent\container\msque.h>

struct test{
	int thid;
	int num;
};

template<class que = Hemsleya::container::msque<test> >
class base_test{
private:
	que _que;
	boost::atomic_int count;
	bool bpopend;
	test back[4];

	struct data{
		base_test * pthis;
		int thid;
	};


	static void push(void* handle){
		data * _data = (data*)handle;
		int thid = _data->thid;
		base_test * pthis = _data->pthis;
		test t;
		for(int i = 0; i < 100000; i++){
			t.thid = thid;
			t.num = i;
			pthis->_que.push(t);
		}
		pthis->count--;
		_endthread();
	}

	static void pop(void * _pthis){
		base_test * pthis = (base_test * )_pthis;
		test t;
		bool bpop = false;
		while((bpop = pthis->_que.pop(t)) || pthis->count.load() > 0){
			if (bpop){
				if (pthis->back[t.thid].num != t.num){
					abort();
				}
				pthis->back[t.thid].num++;
			}else{
				_sleep(1);
			}
		}
		pthis->bpopend = true;
		_endthread();
	}

public:
	void operator() (){
		data data[4];
		clock_t begin, runtime;
		for(int i = 0; i < 100; i++){
			count = 4;
			for(int i = 0; i < 4; i++){
				back[i].thid = i;
				back[i].num = 0;
			}
			bpopend = false;

			begin = clock();
			_beginthread(pop, 0, this);
			for(int i = 0; i < 4; i++){
				data[i].pthis = this;
				data[i].thid = i;
				_beginthread(&push, 0, &data[i]);
			}
			while(!bpopend){
				_sleep(1);
			}
			runtime = clock() - begin;
			std::cout << runtime << std::endl;
		}
	}
	
};

#endif //_BASE_TEST_H