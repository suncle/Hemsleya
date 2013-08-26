/*
 * abstract_factory.h
 *   Created on: 2013-8-25
 *	     Author: qianqians
 * abstract_factory
 */
#ifndef _abstract_factory_h
#define _abstract_factory_h

#include <Hemsleya/base/tools/tools.h>

#include <boost/thread/mutex.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/shared_ptr.hpp>

namespace Hemsleya {
namespace abstract_factory {

template <typename T, typename _Allocator_ = boost::pool_allocator<char> >
class abstract_factory{
private:
	struct mirco_pool{
		mirco_pool() : _pool(0){}
		~mirco_pool() {
			while (_pool != 0){
				char * tmp = _pool;
				_pool = *((char**)_pool);
				_Allocator.deallocate(tmp, (sizeof(T) > 8) ? sizeof(T) : 8);
			}
		}

		char * _pool; 	
		boost::mutex _mu;
	};

	typedef typename _Allocator::template rebind<mirco_pool>::other _Allocator_mirco_pool_;

public:
	abstract_factory(){
		count = processors_count();

		_mirco_pool = _Allocator_mirco_pool.allocate(count);
		for(int i = 0; i < count; i++){
			new(_mirco_pool++) mirco_pool();
		}
	}

	~abstract_factory(){
		for(int i = 0; i < count; i++){
			(_mirco_pool++)->~mirco_pool();
		}
		_Allocator_mirco_pool.deallocate(_mirco_pool, count);
	}

	boost::shared_ptr<T> create_product(){
		T * pT = 0;
		for(int i = 0; i < count; i++){
			boost::mutex::scoped_lock lock(_mirco_pool[i]._mu, boost::try_to_lock);

			if (lock.owns_lock()){
				if (_mirco_pool[i]._pool != 0){
					pT = _mirco_pool[i]._pool;
					_mirco_pool[i]._pool = *((char**)_mirco_pool[i]._pool);

					break;
				}
			}
		}

		while (pT == 0){
			pT = _Allocator.allocate((sizeof(T) > 8) ? sizeof(T) : 8);
		}

		new(pT) T();
		boost::shared_ptr<T> _shared_ptr(_mirco_pool, boost::bind(&abstract_factory::release_product, this, _1));
		
		return _shared_ptr;
	}

private:
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