/*
 * abstract_factory.h
 *   Created on: 2013-8-25
 *	     Author: qianqians
 * abstract_factory
 */
#ifndef _abstract_factory_h
#define _abstract_factory_h

#include <vector>

#include <boost/atomic.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/shared_ptr.hpp>

#include <Hemsleya/base/tools/tools.h>

namespace Hemsleya {
namespace abstract_factory {

template <typename T, typename _Allocator_ = std::allocator<T> >
class abstract_factory{
private:
	struct mirco_pool{
		mirco_pool() : _pool(0){}
		~mirco_pool() {}

		void * _pool; 	
		boost::atomic_flag _mu;
	};

	typedef typename _Allocator_::template rebind<mirco_pool>::other _Allocator_mirco_pool_;

public:
	abstract_factory(){
		_pool_count = processors_count();
		_vector_mirco_pool = _Allocator_mirco_pool.allocate(_pool_count);
		for(uint32_t i = 0; i < _pool_count; i++){
			new(&_vector_mirco_pool[i]) mirco_pool();
		}

		min_count = (8+sizeof(T)-1)/sizeof(T);
	}

	~abstract_factory(){
		for(uint32_t i = 0; i != _pool_count; i++){
			void * _pool = _vector_mirco_pool[i]._pool; 
			while (_pool != 0){
				void * tmp = _pool;
				_pool = *((void**)_pool);
				_Allocator.deallocate((T*)tmp, min_count);
			}
		}
		_Allocator_mirco_pool.deallocate(_vector_mirco_pool, _pool_count);
	}

	template <size_t count>
	T * create_product(){
		T * pT = _alloc(count);
		
		while(count > 0){
			new(&pT[--count]) T;
		}
		
		return pT;
	}

	T * create_product(){
		T * pT = _alloc(1);
		
		new(pT) T;
		
		return pT;
	}

	template <size_t count, typename t1>
	T * create_product(t1 & _t1){
		T * pT = _alloc(count);

		while(count > 0){
			new(&pT[--count]) T(_t1);
		}
		
		return pT;
	}

	template <typename t1>
	T * create_product(t1 & _t1){
		T * pT = _alloc(1);

		new(pT) T(_t1);
		
		return pT;
	}

	template <size_t count, typename t1, typename t2>
	T * create_product(t1 & _t1, t2 & _t2){
		T * pT = _alloc(count);

		while(count > 0){
			new(&pT[--count]) T(_t1, _t2);
		}
		
		return pT;
	}

	template <typename t1, typename t2>
	T * create_product(t1 & _t1, t2 & _t2){
		T * pT = _alloc(count);

		new(pT) T(_t1, _t2);
		
		return pT;
	}

	template <size_t count, typename t1, typename t2, typename t3>
	T * create_product(t1 & _t1, t2 & _t2, t3 & _t3){
		T * pT = _alloc(count);
		
		while(count > 0){
			new(&pT[--count]) T(_t1, _t2, _t3);
		}
		
		return pT;
	}

	template <typename t1, typename t2, typename t3>
	T * create_product(t1 & _t1, t2 & _t2, t3 & _t3){
		T * pT = _alloc(count);
		
		new(pT) T(_t1, _t2, _t3);
		
		return pT;
	}

	template <size_t count, typename t1, typename t2, typename t3, typename t4>
	T * create_product(t1 & _t1, t2 & _t2, t3 & _t3, t4 & _t4){
		T * pT = _alloc(count);
		
		while(count > 0){
			new(&pT[--count]) T(_t1, _t2, _t3, _t4);
		} 
		
		return pT;
	}

	template <typename t1, typename t2, typename t3, typename t4>
	T * create_product(t1 & _t1, t2 & _t2, t3 & _t3, t4 & _t4){
		T * pT = _alloc(count);
		
		new(pT) T(_t1, _t2, _t3, _t4);
		
		return pT;
	}

	template <size_t count, typename t1, typename t2, typename t3, typename t4, typename t5>
	T * create_product(t1 & _t1, t2 & _t2, t3 & _t3, t4 & _t4, t5 & _t5){
		T * pT = _alloc(count);
		
		while(count > 0){
			new(&pT[--count]) T(_t1, _t2, _t3, _t4, _t5);
		} 
		
		return pT;
	}

	template <typename t1, typename t2, typename t3, typename t4, typename t5>
	T * create_product(t1 & _t1, t2 & _t2, t3 & _t3, t4 & _t4, t5 & _t5){
		T * pT = _alloc(count);
		
		new(pT) T(_t1, _t2, _t3, _t4, _t5);
		
		return pT;
	}

	template <size_t count, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6>
	T * create_product(t1 & _t1, t2 & _t2, t3 & _t3, t4 & _t4, t5 & _t5, t6 & _t6){
		T * pT = _alloc(count);
		
		while(count > 0){
			new(&pT[--count]) T(_t1, _t2, _t3, _t4, _t5, _t6);
		}
		
		return pT;
	}

	template <typename t1, typename t2, typename t3, typename t4, typename t5, typename t6>
	T * create_product(t1 & _t1, t2 & _t2, t3 & _t3, t4 & _t4, t5 & _t5, t6 & _t6){
		T * pT = _alloc(count);
		
		new(pT) T(_t1, _t2, _t3, _t4, _t5, _t6);
		
		return pT;
	}

	template <size_t count, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7>
	T * create_product(t1 & _t1, t2 & _t2, t3 & _t3, t4 & _t4, t5 & _t5, t6 & _t6, t7 & _t7){
		T * pT = _alloc(count);
		
		while(count > 0){
			new(&pT[--count]) T(_t1, _t2, _t3, _t4, _t5, _t6, _t7);
		}
		
		return pT;
	}

	template <typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7>
	T * create_product(t1 & _t1, t2 & _t2, t3 & _t3, t4 & _t4, t5 & _t5, t6 & _t6, t7 & _t7){
		T * pT = _alloc(count);
		
		new(pT) T(_t1, _t2, _t3, _t4, _t5, _t6, _t7);
		
		return pT;
	}

	template <size_t count, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8>
	T * create_product(t1 & _t1, t2 & _t2, t3 & _t3, t4 & _t4, t5 & _t5, t6 & _t6, t7 & _t7, t8 & _t8){
		T * pT = _alloc(count);
		
		while(count > 0){
			new(&pT[--count]) T(_t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8);
		}
		
		return pT;
	}

	template <typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8>
	T * create_product(t1 & _t1, t2 & _t2, t3 & _t3, t4 & _t4, t5 & _t5, t6 & _t6, t7 & _t7, t8 & _t8){
		T * pT = _alloc(count);
		
		new(pT) T(_t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8);
		
		return pT;
	}

	template <size_t count, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8, typename t9>
	T * create_product(t1 & _t1, t2 & _t2, t3 & _t3, t4 & _t4, t5 & _t5, t6 & _t6, t7 & _t7, t8 & _t8, t9 & _t9){
		T * pT = _alloc(count);
		
		while(count > 0){
			new(&pT[--count]) T(_t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8, _t9);
		}
		
		return pT;
	}

	template <typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8, typename t9>
	T * create_product(t1 & _t1, t2 & _t2, t3 & _t3, t4 & _t4, t5 & _t5, t6 & _t6, t7 & _t7, t8 & _t8, t9 & _t9){
		T * pT = _alloc(count);
		
		new(pT) T(_t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8, _t9);
		
		return pT;
	}

	template <size_t count, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8, typename t9, typename t10>
	T * create_product(t1 & _t1, t2 & _t2, t3 & _t3, t4 & _t4, t5 & _t5, t6 & _t6, t7 & _t7, t8 & _t8, t9 & _t9, t10 & _t10){
		T * pT = _alloc(count);
		
		while(count > 0){
			new(&pT[--count]) T(_t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8, _t9, _t10);
		}

		return pT;
	}

	template <typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8, typename t9, typename t10>
	T * create_product(t1 & _t1, t2 & _t2, t3 & _t3, t4 & _t4, t5 & _t5, t6 & _t6, t7 & _t7, t8 & _t8, t9 & _t9, t10 & _t10){
		T * pT = _alloc(count);
		
		new(pT) T(_t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8, _t9, _t10);
		
		return pT;
	}

	void release_product(T * pT, size_t count){
		for(uint32_t i = 0; i < count; i++){
			pT[i].~T();
		}

		_free(pT, count);
	}

private:
	T * _alloc(size_t count){
		if (count <= min_count){
			for(uint32_t i = 0; i < _pool_count; i++){
				if (!_vector_mirco_pool[i]._mu.test_and_set()){
					if (_vector_mirco_pool[i]._pool != 0){
						T * tmp = (T*)_vector_mirco_pool[i]._pool;
						_vector_mirco_pool[i]._pool = *((void**)_vector_mirco_pool[i]._pool);
						_vector_mirco_pool[i]._mu.clear();

						return tmp;
					}
					_vector_mirco_pool[i]._mu.clear();
				}
			}
		}
		
		return _Allocator.allocate(count < min_count ? min_count : count);
	}

	void _free(T * mem, size_t count){
		if (count <= min_count){
			uint32_t i = 0;
			while(1){
				if (!_vector_mirco_pool[i]._mu.test_and_set()){
					*((void**)mem) = _vector_mirco_pool[i]._pool;
					_vector_mirco_pool[i]._pool = (void*)mem;
					_vector_mirco_pool[i]._mu.clear();

					break;
				}

				if (++i == _pool_count){
					i = 0;
				}
			}
		}else{
			_Allocator.deallocate(mem, count);
		}
	}

private:
	_Allocator_ _Allocator;
	_Allocator_mirco_pool_ _Allocator_mirco_pool;

	uint32_t _pool_count;
	mirco_pool * _vector_mirco_pool;

	size_t min_count;

};

} // abstract_factory
} // Hemsleya

#endif //_abstract_factory_h