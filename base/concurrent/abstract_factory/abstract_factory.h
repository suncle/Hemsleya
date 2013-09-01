/*
 * abstract_factory.h
 *   Created on: 2013-8-25
 *	     Author: qianqians
 * abstract_factory
 */
#ifndef _abstract_factory_h
#define _abstract_factory_h

#include <boost/thread/mutex.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/shared_ptr.hpp>

#include <Hemsleya/base/tools/tools.h>

namespace Hemsleya {
namespace abstract_factory {

template <typename T, typename _Allocator_ = boost::pool_allocator<char> >
class abstract_factory{
private:
	struct mirco_pool{
		mirco_pool() : _pool(0){}
		~mirco_pool() {}

		char * _pool; 	
		boost::mutex _mu;
	};

	typedef typename _Allocator_::template rebind<mirco_pool>::other _Allocator_mirco_pool_;

public:
	abstract_factory(){
		count = processors_count();

		_mirco_pool = _Allocator_mirco_pool.allocate(count);
		for(uint32_t i = 0; i < count; i++){
			new(&_mirco_pool[i]) mirco_pool();
		}
	}

	~abstract_factory(){
		for(uint32_t i = 0; i < count; i++){
			char * _pool = (_mirco_pool++)->_pool; 
			while (_pool != 0){
				char * tmp = _pool;
				_pool = *((char**)_pool);
				_Allocator.deallocate(tmp, (sizeof(T) > 8) ? sizeof(T) : 8);
			}
		}
		_Allocator_mirco_pool.deallocate(_mirco_pool, count);
	}

	T * create_product(){
		T * pT = 0;
		for(uint32_t i = 0; i < count; i++){
			boost::mutex::scoped_lock lock(_mirco_pool[i]._mu, boost::try_to_lock);

			if (lock.owns_lock()){
				if (_mirco_pool[i]._pool != 0){
					pT = (T*)_mirco_pool[i]._pool;
					_mirco_pool[i]._pool = *((char**)_mirco_pool[i]._pool);

					break;
				}
			}
		}

		while (pT == 0){
			pT = (T*)_Allocator.allocate((sizeof(T) > 8) ? sizeof(T) : 8);
		}

		new(pT) T();
		
		return pT;
	}

	template <typename t1>
	T * create_product(t1 _t1){
		T * pT = 0;
		for(uint32_t i = 0; i < count; i++){
			boost::mutex::scoped_lock lock(_mirco_pool[i]._mu, boost::try_to_lock);

			if (lock.owns_lock()){
				if (_mirco_pool[i]._pool != 0){
					pT = (T*)_mirco_pool[i]._pool;
					_mirco_pool[i]._pool = *((char**)_mirco_pool[i]._pool);

					break;
				}
			}
		}

		while (pT == 0){
			pT = (T*)_Allocator.allocate((sizeof(T) > 8) ? sizeof(T) : 8);
		}

		new(pT) T(_t1);
		
		return pT;
	}

	template <typename t1, typename t2>
	T * create_product(t1 _t1, t2 _t2){
		T * pT = 0;
		for(uint32_t i = 0; i < count; i++){
			boost::mutex::scoped_lock lock(_mirco_pool[i]._mu, boost::try_to_lock);

			if (lock.owns_lock()){
				if (_mirco_pool[i]._pool != 0){
					pT = (T*)_mirco_pool[i]._pool;
					_mirco_pool[i]._pool = *((char**)_mirco_pool[i]._pool);

					break;
				}
			}
		}

		while (pT == 0){
			pT = (T*)_Allocator.allocate((sizeof(T) > 8) ? sizeof(T) : 8);
		}

		new(pT) T(_t1, _t2);
		
		return pT;
	}

	template <typename t1, typename t2, typename t3>
	T * create_product(t1 _t1, t2 _t2, t3 _t3){
		T * pT = 0;
		for(uint32_t i = 0; i < count; i++){
			boost::mutex::scoped_lock lock(_mirco_pool[i]._mu, boost::try_to_lock);

			if (lock.owns_lock()){
				if (_mirco_pool[i]._pool != 0){
					pT = (T*)_mirco_pool[i]._pool;
					_mirco_pool[i]._pool = *((char**)_mirco_pool[i]._pool);

					break;
				}
			}
		}

		while (pT == 0){
			pT = (T*)_Allocator.allocate((sizeof(T) > 8) ? sizeof(T) : 8);
		}

		new(pT) T(_t1, _t2, _t3);
		
		return pT;
	}

	template <typename t1, typename t2, typename t3, typename t4>
	T * create_product(t1 _t1, t2 _t2, t3 _t3, t4 _t4){
		T * pT = 0;
		for(uint32_t i = 0; i < count; i++){
			boost::mutex::scoped_lock lock(_mirco_pool[i]._mu, boost::try_to_lock);

			if (lock.owns_lock()){
				if (_mirco_pool[i]._pool != 0){
					pT = (T*)_mirco_pool[i]._pool;
					_mirco_pool[i]._pool = *((char**)_mirco_pool[i]._pool);

					break;
				}
			}
		}

		while (pT == 0){
			pT = (T*)_Allocator.allocate((sizeof(T) > 8) ? sizeof(T) : 8);
		}

		new(pT) T(_t1, _t2, _t3, _t4);
		
		return pT;
	}

	template <typename t1, typename t2, typename t3, typename t4, typename t5>
	T * create_product(t1 _t1, t2 _t2, t3 _t3, t4 _t4, t5 _t5){
		T * pT = 0;
		for(uint32_t i = 0; i < count; i++){
			boost::mutex::scoped_lock lock(_mirco_pool[i]._mu, boost::try_to_lock);

			if (lock.owns_lock()){
				if (_mirco_pool[i]._pool != 0){
					pT = (T*)_mirco_pool[i]._pool;
					_mirco_pool[i]._pool = *((char**)_mirco_pool[i]._pool);

					break;
				}
			}
		}

		while (pT == 0){
			pT = (T*)_Allocator.allocate((sizeof(T) > 8) ? sizeof(T) : 8);
		}

		new(pT) T(_t1, _t2, _t3, _t4, _t5);
		
		return pT;
	}

	template <typename t1, typename t2, typename t3, typename t4, typename t5, typename t6>
	T * create_product(t1 _t1, t2 _t2, t3 _t3, t4 _t4, t5 _t5, t6 _t6){
		T * pT = 0;
		for(uint32_t i = 0; i < count; i++){
			boost::mutex::scoped_lock lock(_mirco_pool[i]._mu, boost::try_to_lock);

			if (lock.owns_lock()){
				if (_mirco_pool[i]._pool != 0){
					pT = (T*)_mirco_pool[i]._pool;
					_mirco_pool[i]._pool = *((char**)_mirco_pool[i]._pool);

					break;
				}
			}
		}

		while (pT == 0){
			pT = (T*)_Allocator.allocate((sizeof(T) > 8) ? sizeof(T) : 8);
		}

		new(pT) T(_t1, _t2, _t3, _t4, _t5, _t6);
		
		return pT;
	}

	template <typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7>
	T * create_product(t1 _t1, t2 _t2, t3 _t3, t4 _t4, t5 _t5, t6 _t6, t7 _t7){
		T * pT = 0;
		for(uint32_t i = 0; i < count; i++){
			boost::mutex::scoped_lock lock(_mirco_pool[i]._mu, boost::try_to_lock);

			if (lock.owns_lock()){
				if (_mirco_pool[i]._pool != 0){
					pT = (T*)_mirco_pool[i]._pool;
					_mirco_pool[i]._pool = *((char**)_mirco_pool[i]._pool);

					break;
				}
			}
		}

		while (pT == 0){
			pT = (T*)_Allocator.allocate((sizeof(T) > 8) ? sizeof(T) : 8);
		}

		new(pT) T(_t1, _t2, _t3, _t4, _t5, _t6, _t7);
		
		return pT;
	}

	template <typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8>
	T * create_product(t1 _t1, t2 _t2, t3 _t3, t4 _t4, t5 _t5, t6 _t6, t7 _t7, t8 _t8){
		T * pT = 0;
		for(uint32_t i = 0; i < count; i++){
			boost::mutex::scoped_lock lock(_mirco_pool[i]._mu, boost::try_to_lock);

			if (lock.owns_lock()){
				if (_mirco_pool[i]._pool != 0){
					pT = (T*)_mirco_pool[i]._pool;
					_mirco_pool[i]._pool = *((char**)_mirco_pool[i]._pool);

					break;
				}
			}
		}

		while (pT == 0){
			pT = (T*)_Allocator.allocate((sizeof(T) > 8) ? sizeof(T) : 8);
		}

		new(pT) T(_t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8);
		
		return pT;
	}

	template <typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8, typename t9>
	T * create_product(t1 _t1, t2 _t2, t3 _t3, t4 _t4, t5 _t5, t6 _t6, t7 _t7, t8 _t8, t9 _t9){
		T * pT = 0;
		for(uint32_t i = 0; i < count; i++){
			boost::mutex::scoped_lock lock(_mirco_pool[i]._mu, boost::try_to_lock);

			if (lock.owns_lock()){
				if (_mirco_pool[i]._pool != 0){
					pT = (T*)_mirco_pool[i]._pool;
					_mirco_pool[i]._pool = *((char**)_mirco_pool[i]._pool);

					break;
				}
			}
		}

		while (pT == 0){
			pT = (T*)_Allocator.allocate((sizeof(T) > 8) ? sizeof(T) : 8);
		}

		new(pT) T(_t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8, _t9);
		
		return pT;
	}

	template <typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8, typename t9, typename t10>
	T * create_product(t1 _t1, t2 _t2, t3 _t3, t4 _t4, t5 _t5, t6 _t6, t7 _t7, t8 _t8, t9 _t9, t10 _t10){
		T * pT = 0;
		for(uint32_t i = 0; i < count; i++){
			boost::mutex::scoped_lock lock(_mirco_pool[i]._mu, boost::try_to_lock);

			if (lock.owns_lock()){
				if (_mirco_pool[i]._pool != 0){
					pT = (T*)_mirco_pool[i]._pool;
					_mirco_pool[i]._pool = *((char**)_mirco_pool[i]._pool);

					break;
				}
			}
		}

		while (pT == 0){
			pT = (T*)_Allocator.allocate((sizeof(T) > 8) ? sizeof(T) : 8);
		}

		new(pT) T(_t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8, _t9, _t10);

		return pT;
	}

	void release_product(T * pT){
		pT->~T();

		int _count = 0;
		while(1){
			boost::mutex::scoped_lock lock(_mirco_pool[_count]._mu, boost::try_to_lock);
			if (lock.owns_lock()){
				*((char**)pT) = _mirco_pool[_count]._pool;
				_mirco_pool[_count]._pool = (char*)pT;

				break;
			}

			if (++_count == count){
				_count = 0;
			}
		}
	}

private:
	_Allocator_mirco_pool_  _Allocator_mirco_pool;
	_Allocator_ _Allocator;

	uint32_t count;
	mirco_pool * _mirco_pool;

};

} // abstract_factory
} // Hemsleya

#endif //_abstract_factory_h