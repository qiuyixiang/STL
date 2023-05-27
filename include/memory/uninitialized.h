//
// Created by 11508 on 2023-05-21.
//

#ifndef STL2_0_UNINITIALIZED_H
#define STL2_0_UNINITIALIZED_H

/**
 * Base Memory Management Function
 * Base on C library memory function
 *
 * create on 2023-05-23
 */

#include <iostream>
#include <cstring>

#include "../util/ctt.h"
#include "../iterator/iterator_traits.h"


namespace stl{
    template<typename _InputIterator, typename _ForwardIterator>
    inline _ForwardIterator uninitialized_copy
    (_InputIterator _First, _InputIterator _Last, _ForwardIterator _Result);
}
namespace __std__{
    /// uninitialized_fill_n

    template<typename _ForwardIterator, typename _Tp>
    inline _ForwardIterator
    __uninitialized_fill_n_aux(_ForwardIterator _First, stl::size_t __n, const _Tp& __val, std::true_type){
        return std::fill_n(_First, __n, __val);
    }
    template<typename _ForwardIterator, typename _Tp>
    inline _ForwardIterator
    __uninitialized_fill_n_aux(_ForwardIterator _First, stl::size_t __n, const _Tp& __val, std::false_type){
        _ForwardIterator _Current = _First;
        for (; _Current != _First + __n; ++_Current){
            stl::_Construct(_Current, __val);
        }
        return _Current;
    }

    /// uninitialized_fill
    template<typename _ForwardIterator, typename _Tp>
    inline void __uninitialized_fill_aux
    (_ForwardIterator _First ,_ForwardIterator _Last, const _Tp& __val, std::true_type){
        std::fill(_First, _Last, __val);
    }

    template<typename _ForwardIterator, typename _Tp>
    inline void __uninitialized_fill_aux
    (_ForwardIterator _First ,_ForwardIterator _Last, const _Tp& __val, std::false_type){
        for ( ; _First != _Last; ++_First)
            stl::_Construct(_First, __val);
    }

    ///uninitialized_copy
    template<typename _InputIterator, typename _ForwardIterator>
    inline _ForwardIterator __uninitialized_copy_aux
    (_InputIterator _First, _InputIterator _Last, _ForwardIterator _Result, std::true_type){
        return std::copy(_First, _Last, _Result);
    }

    template<typename _InputIterator, typename _ForwardIterator>
    inline _ForwardIterator __uninitialized_copy_aux
    (_InputIterator _First, _InputIterator _Last, _ForwardIterator _Result, std::false_type){
        _ForwardIterator _Current = _Result;
        for ( ; _First != _Last; ++_First, ++_Current)
            stl::_Construct(_Current, *_First);

        return _Current;
    }

    /// uninitialized_copy_n
    template<typename _InputIterator, typename _ForwardIterator>
    inline _ForwardIterator __uninitialized_copy_n_aux
    (_InputIterator _First, stl::size_t __n, _ForwardIterator _Result, stl::input_iterator_tag){
        _ForwardIterator _Current = _Result;
        for (; __n > 0; --__n, ++_Current, ++_First)
            stl::_Construct(_Current, *_First);
        return _Current;
    }

    template<typename _RandomIterator, typename _ForwardIterator>
    inline _ForwardIterator __uninitialized_copy_n_aux
    (_RandomIterator _First, stl::size_t __n, _ForwardIterator _Result, stl::random_access_iterator_tag){
        return stl::uninitialized_copy(_First, _First + __n, _Result);
    }
}
namespace stl{

    /// uninitialized_fill_n

    template<typename _ForwardIterator, typename _Tp>
    inline _ForwardIterator
    uninitialized_fill_n(_ForwardIterator _First, stl::size_t __n, const _Tp& __val){
        typedef typename stl::iterator_traits<_ForwardIterator>::value_type _Val_Type;
        return __std__::__uninitialized_fill_n_aux(_First, __n, __val, std::is_pod<_Val_Type> { });
    }

    /// uninitialized_fill
    template<typename _ForwardIterator, typename _Tp>
    inline void
    uninitialized_fill(_ForwardIterator _First, _ForwardIterator _Last, const _Tp& __val){
        typedef typename stl::iterator_traits<_ForwardIterator>::value_type _Val_Type;
        __std__::__uninitialized_fill_aux(_First, _Last, __val,  std::is_pod<_Val_Type> {  });
    }

    ///uninitialized_copy
    template<typename _InputIterator, typename _ForwardIterator>
    inline _ForwardIterator
    uninitialized_copy(_InputIterator _First, _InputIterator _Last, _ForwardIterator _Result){
#ifdef DEBUGGER
        std::cout<<"uninitialized_copy() invoked !!!"<<std::endl;
#endif
        typedef typename stl::iterator_traits<_ForwardIterator>::value_type _Val_Type;
        return __std__::__uninitialized_copy_aux
        (_First, _Last, _Result, std::is_pod<_Val_Type>{ });
    }

    /// Specialization for uninitialized_copy
    inline char *
    uninitialized_copy(const char * __first, const char * __last, char * __result){
        memmove(static_cast<void*>(__result),
                static_cast<void*>(const_cast<char*>(__first)), sizeof(char ) * (__last - __first));
        return __result + (__last - __first);
    }

    inline wchar_t *
    uninitialized_copy(const wchar_t * __first, const wchar_t *__last, wchar_t * __result){
        memmove(static_cast<void*>(__result),
                static_cast<void*>
                (const_cast<wchar_t*>(__first)), sizeof(wchar_t ) * (__last - __first));
        return __result + (__last - __first);
    }

    /// uninitialized_copy_n
    template<typename InputIterator, typename ForwardIterator>
    inline ForwardIterator
    uninitialized_copy_n(InputIterator _First, stl::size_t __n, ForwardIterator _Result){
        typedef typename stl::iterator_traits<InputIterator>::iterator_category _Category;
        return __std__::__uninitialized_copy_n_aux(_First, __n, _Result, _Category{ });
    }
}
#endif //STL2_0_UNINITIALIZED_H
