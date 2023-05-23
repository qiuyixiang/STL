//
// Created by 11508 on 2023-05-21.
//

#ifndef STL2_0_CONSTRUCT_H
#define STL2_0_CONSTRUCT_H

#include "../util/ctt.h"
#include "../iterator/iterator_traits.h"

#include <bits/move.h>
#include <iostream>

/// Construct and Destroy For Base Memory Management

namespace stl{
    template<typename _Tp>
    inline void _Destroy(_Tp * __p);
}
namespace __std__{
    /// Destroy Auxiliary Function (Packed in Structure)
    template<bool>
    struct _Destruct_Aux{
        template<typename _ForwardIterator>
        static inline void __destroy_aux(_ForwardIterator _First, _ForwardIterator _Last){
            for (; _First != _Last; ++_First)
                stl::_Destroy(_First);
        }
    };

    /// Partial Specialization For Destructor
    template<>
    struct _Destruct_Aux<true>{
        template<typename _ForwardIterator>
        static inline void __destroy_aux(_ForwardIterator _First, _ForwardIterator _Last)  {
#ifdef DEBUGGER
            std::cout<<"has_trivial_destructor"<<std::endl;
#endif
        }
    };
}
namespace stl{

    /// Construct
    /// Variable Argument Type
    template<typename _Tp, typename ..._Args>
    inline void _Construct(_Tp * __p, _Args&&... __args){
        new (static_cast<void* >(__p)) _Tp(std::forward<_Args>(__args)...);
    }

    /// Invoke Object's Destructor !
    template<typename _Tp>
    inline void _Destroy(_Tp * __p){
        __p->~_Tp();
    }

    template<typename _ForwardIterator>
    inline void _Destroy(_ForwardIterator _First, _ForwardIterator _Last){
        typedef typename stl::iterator_traits<_ForwardIterator>::value_type _Val_Type;
        __std__::_Destruct_Aux<__has_trivial_destructor(_Val_Type)>::__destroy_aux(_First, _Last);
    }
}
#endif //STL2_0_CONSTRUCT_H
