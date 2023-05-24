//
// Created by 11508 on 2023-05-24.
//

#ifndef STL2_0_FUNCTIONAL_H
#define STL2_0_FUNCTIONAL_H

/**
 * This File include all Functor
 * And some utility functor
 */

#include "./functor/functor.h"
#include "./util/ctt.h"

#include <iostream>

namespace stl{

    /// Inner Display (Debugger) for Container

    template<typename _ForwardIterator>
    _STL_USE_UTILITY_INLINE void __display__(_ForwardIterator _First, _ForwardIterator _Last){
        for ( ; _First != _Last; ++_First)
            std::cout<<*_First<<" ";
        std::cout<<std::endl;
    }

    /// This Function Must Define Macro DEBUGGER to work properly !
    template<typename _Container>
    _STL_USE_UTILITY_INLINE void
    __display_dbg(_Container& __container){
        __display__(__container.cbegin(), __container.cend());
#ifdef DEBUGGER
        std::cout<<"Size : "<<__container.size()<<std::endl;
        std::cout<<std::endl;
#endif
    }
}

#endif //STL2_0_FUNCTIONAL_H
