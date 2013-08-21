/*
 * ringque.h
 *  Created on: 2012-1-13
 *      Author: qianqians
 * ringque
 */
#ifndef _RINGQUE_H
#define _RINGQUE_H

#include <boost/atomic.hpp>
#include <boost/thread.hpp>
#include <boost/pool/pool_alloc.hpp>

namespace Hemsleya{
namespace container{

template<typename T, typename _Allocator = boost::pool_allocator<T>, unsigned detailsize = 1024 >
class ringque{ 
private:
	typedef typename _Allocator::template rebind<boost::atomic<typename T *> >::other _Allque;
	typedef boost::atomic<typename T *> * que;

public:
	ringque(){
		_que = get_que(detailsize);
		
		_push_slide.store(0);
		_que_max = detailsize;
		_pop_slide.store(_que_max);
		_size.store(0);
	}

	~ringque(){
		put_que(_que, _que_max);
	}

	void clear(){
		boost::unique_lock<boost::shared_mutex> lock(_mu);

		boost::atomic<typename T *> * _tmp = _que;
		boost::uint32_t _tmp_push_slide = _push_slide.load();
		boost::uint32_t _tmp_pop_slide = _pop_slide.load();

		_que = get_que(_que_max);
		_push_slide.store(0);
		_pop_slide.store(_que_max);
		_size.store(0);

		lock.unlock();

		while(1){
			if (_tmp_pop_slide == _que_max){
				_tmp_pop_slide = 0;
			}

			if (_tmp_pop_slide != _tmp_push_slide){
				break;
			}

			_tmp[_tmp_pop_slide]->~T();
			_T_alloc.deallocate(_tmp[_tmp_pop_slide], 1);
		}
		put_que(_tmp, _que_max);
	}

	std::size_t size(){
		return _size.load();
	}

	void push(T data){
		boost::upgrade_lock<boost::shared_mutex> lock(_mu);

		unsigned int slide = _push_slide.load();
		unsigned int newslide = 0;
		while(1){
			newslide = slide+1; 
			if (newslide == _que_max){
				newslide = 0;
			}

			if (newslide == _pop_slide.load()){
				boost::unique_lock<boost::shared_mutex> uniquelock(boost::move(lock));
				slide = _push_slide.load();
				if (newslide == _que_max){
					newslide = 0;
				}
				if (newslide == _pop_slide.load()){
					resize();
				}
			}

			if (_push_slide.compare_exchange_strong(slide, newslide)){		
				T * _tmp = _T_alloc.allocate(1);
				::new (_tmp) T(data);
				_que[slide].store(_tmp);
				_size++;
				break;
			}
		}
	}

	bool pop(T & data){
		boost::shared_lock<boost::shared_mutex> lock(_mu);

		T * _tmp = 0;
		unsigned int slide = _pop_slide.load();
		unsigned int newslide = 0;
		while(1){
			newslide = (slide == _que_max) ? 0 : (slide + 1);
			if (newslide == _que_max){
				newslide = 0;
			}
			
			if (newslide == _push_slide.load()){
				break;
			}

			if (_pop_slide.compare_exchange_strong(slide, newslide)){
				while((_tmp = _que[newslide].exchange(0)) == 0);
				data = *_tmp;
				_tmp->~T();
				_T_alloc.deallocate(_tmp, 1);
				_size--;
				return true;
			}
		}

		return false;
	}

private:
	void resize(){
		size_t size = 0, size1 = 0, size2 = 0;
		unsigned int pushslide = _push_slide.load();
		unsigned int popslide = _pop_slide.load();
		boost::atomic<typename T *> * _tmp = 0;
		unsigned int newslide = pushslide+1;

		if (newslide == popslide){
			size = _que_max*sizeof(boost::atomic<typename T *>)*2;
			while((_tmp = (boost::atomic<typename T *>*)malloc(size)) == 0);
			size1 = pushslide*sizeof(boost::atomic<typename T *>);
			size2 = _que_max*sizeof(boost::atomic<typename T *>)-size1;
			memcpy(_tmp, _que, size1);
			memcpy((char*)_tmp+size-size2, (char*)_que+size1, size2); 
			_pop_slide += _que_max;
			_que_max *= 2;
			free(_que);
			_que = _tmp;
		}
	}

private:
	que get_que(uint32_t size){
		que _que = _que_alloc.allocate(size);

		return _que;
	}

	void put_que(que _que, uint32_t size){
		_que_alloc.deallocate(_que, size);
	}

private:
	boost::shared_mutex _mu;
	que _que;
	boost::atomic_uint _push_slide, _pop_slide, _size;
	unsigned int _que_max;
	
	_Allocator _T_alloc;
	_Allque _que_alloc;
};

}//container
}//Hemsleya

#endif //_RINGQUE_H