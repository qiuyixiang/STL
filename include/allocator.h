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
    template<typename _Tp>
    using allocator = stl::new_allocator<_Tp>;

    template<typename _Tp>
    using alloc = stl::pool_allocator<_Tp>;

    template<typename _Alloc>
    using allocator_traits = stl::__allocator_traits<_Alloc>;
}


#endif //STL2_0_ALLOCATOR_H
