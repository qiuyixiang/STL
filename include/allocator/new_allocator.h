//
// Created by 11508 on 2023-05-21.
//

#ifndef STL2_0_NEW_ALLOCATOR_H
#define STL2_0_NEW_ALLOCATOR_H

/// Base Allocator
/// Just a simple packaging for operator::new

/// Base Type Allocator (new_allocator)

#include "../memory/new.h"

namespace stl{

    /// The Implementation of stl::allocator

    template<typename _Tp>
    class new_allocator{
    public:
        /// Type define for allocator

        typedef _Tp                         value_type;
        typedef _Tp *                       pointer;
        typedef _Tp &                       reference;
        typedef const _Tp*                  const_pointer;
        typedef const _Tp&                  const_reference;
        typedef stl::size_t                 size_type;
        typedef new_allocator<value_type>       allocator_type;

        template<typename _Tp1>
        struct rebind{
            typedef new_allocator<_Tp1> other;
        };

        new_allocator() _STL_NO_EXCEPTION {  }
        new_allocator(const new_allocator& ) _STL_NO_EXCEPTION {  }

        template<typename _Up>
        explicit new_allocator(const new_allocator<_Up>& ) _STL_NO_EXCEPTION {  }

        ~new_allocator() _STL_NO_EXCEPTION {  }

        /// Public Member Function
        size_type max_size() const _STL_NO_EXCEPTION {
            return size_t (-1) / sizeof(value_type);
        }

        pointer address(reference _val) const _STL_NO_EXCEPTION {
            return static_cast<pointer>(&_val);
        }

        const_pointer address(const_reference _val) const _STL_NO_EXCEPTION{
            return static_cast<const_pointer>(&_val);
        }

        /// Essential Application Program Interface (API)

        /// allocate and deallocate
        pointer allocate(size_type __n) const {
            if (__n == 0)
                return pointer {nullptr};
            if (this->max_size() < __n)
                throw std::bad_alloc { };
            void * __p = stl::_new_del::operator new(sizeof(value_type) * __n);
            return static_cast<pointer>(__p);
        }

        void deallocate(pointer __p) const {
            ///std::cout<<"Deallocate"<<std::endl;
            if (__p){
                stl::_new_del::operator delete(__p);
            }
        }

        void deallocate(pointer __p, size_type) const{
            this->deallocate(__p);
        }

        /// construct and destroy

        /// almighty variable argument
        template<typename _Up, typename ..._Args>
        inline void construct(_Up * __p, _Args&& ...args){
            new (static_cast<void*>(__p)) _Up(std::forward<_Args>(args)...);
        }

        void destroy(pointer __p){
            __p -> ~value_type();
        }
    };

    template<typename _Tp>
    inline bool operator==(new_allocator<_Tp>&, new_allocator<_Tp>&){
        return true;
    }

    template<typename _Tp>
    inline bool operator!=(new_allocator<_Tp>&, new_allocator<_Tp>&){
        return false;
    }
}
#endif //STL2_0_NEW_ALLOCATOR_H
