//
// Created by 11508 on 2023-05-21.
//

#ifndef STL2_0_ALLOCATOR_H
#define STL2_0_ALLOCATOR_H

#include "./allocator/new_allocator.h"
#include "./allocator/pool_allocator.h"
#include "./allocator/allocator_traits.h"


/**
 * This File is a simple TypeDefine Of allocator
 * New allocator Standard
 */
namespace stl{
    /// Type Define For New Standard Allocator
    template<typename _Tp>
    using allocator = stl::new_allocator<_Tp>;

    /// type Define For Pool allocator !
    using alloc = __std__::__pool_alloc_base;

    template<typename _Tp>
    using pool_allocator = __std__::__pool_alloc<_Tp>;

    /// Type Define For Allocator Traits !
    template<typename _Alloc>
    using allocator_traits = stl::__allocator_traits<_Alloc>;
}


#endif //STL2_0_ALLOCATOR_H
