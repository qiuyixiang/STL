//
// Created by 11508 on 2023-05-21.
//

#ifndef STL2_0_NEW_H
#define STL2_0_NEW_H

#include <new>               /// for std::bad_alloc
#include <cstdlib>           /// for malloc()

#include "../util/ctt.h"
/// For Type Define

namespace __std__{

    typedef std::size_t SIZE_T;
}

/// Base Memory Management

namespace stl{

    /// Exception as a Flag !!!

    struct no_throw{
        explicit no_throw() = default;
    };

    /// Overwrite C++ Global operator new and operator delete !

    class _new_del{

    public:
        /// new operator that don't throw an exception
        static void * operator new (__std__::SIZE_T) _STL_THROWN(std::bad_alloc);
        static void * operator new[] (__std__::SIZE_T) _STL_THROWN(std::bad_alloc);

        static void operator delete (void * ) _STL_NO_EXCEPTION;
        static void operator delete[] (void *) _STL_NO_EXCEPTION;

        /// new operator that throw an exception
        static void * operator new (__std__::SIZE_T, const no_throw&) _STL_NO_EXCEPTION;
        static void * operator new [](__std__::SIZE_T, const no_throw&) _STL_NO_EXCEPTION;

        static void operator delete (void *, const no_throw&) _STL_NO_EXCEPTION;
        static void operator delete[] (void *, const no_throw&) _STL_NO_EXCEPTION;

        /// placement new
        inline static void * operator new (__std__::SIZE_T, void * __p) _STL_NO_EXCEPTION {
            return __p;
        }
        inline static void * operator new[] (__std__::SIZE_T, void * __p) _STL_NO_EXCEPTION {
            return __p;
        }

        inline static void operator delete (void *, void * )_STL_NO_EXCEPTION {  }
        inline static void operator delete[] (void *, void * )_STL_NO_EXCEPTION {  }

    };
    /// new operator that don't throw an exception

    /// Tips : __size  byte
    void * _new_del::operator new(__std__::SIZE_T __size) _STL_THROWN(std::bad_alloc) {
        if(__size == 0)
            throw std::bad_alloc {  };
        void * _ptr;
        while (true){
            if ((_ptr = malloc(__size)) != nullptr)
                return _ptr;
            std::new_handler __cur_handler = std::get_new_handler();
            if(__cur_handler)
                (*__cur_handler)();
            /// call current new handler
            else
                throw std::bad_alloc {  };
        }
    }
    void * _new_del::operator new[](__std__::SIZE_T __size) _STL_THROWN(std::bad_alloc) {
       return _new_del::operator new(__size);
    }
    void _new_del::operator delete(void * __p) noexcept {
        if(__p)
            free(__p);
    }
    void _new_del::operator delete[](void * __p) noexcept {
        _new_del::operator delete(__p);
    }

    /// new operator that throw an exception
    void *_new_del::operator new(__std__::SIZE_T __size, const no_throw &) _STL_NO_EXCEPTION {
        try {
            return _new_del::operator new(__size);
        } catch (std::bad_alloc&) {
            return nullptr;
        }
    }
    void *_new_del::operator new[](__std__::SIZE_T __size, const no_throw &) _STL_NO_EXCEPTION {
        _new_del::operator new(__size, no_throw{ });
    }

    void _new_del::operator delete[](void * __p, const no_throw &) _STL_NO_EXCEPTION {
        _new_del::operator delete(__p);
    }

    void _new_del::operator delete(void * __p, const no_throw &) _STL_NO_EXCEPTION {
        _new_del::operator delete(__p);
    }

}
#endif //STL2_0_NEW_H
