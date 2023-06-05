//
// Created by 11508 on 2023-06-05.
//

#ifndef STL2_0_FORWARD_LIST_H
#define STL2_0_FORWARD_LIST_H

/**
 * This File is Just A Connection With Header
 * File stl_fwd_list.h
 */

#include "sequence_container/stl_fwd_list.h"

namespace stl{

    /// typedef for forward list
    template<typename _Tp, typename _Alloc = stl::default_allocator<_Tp>>
    using forward_list = stl::_fwd_list<_Tp, _Alloc>;

    /// typedef for forward list iterator
    template<typename _Tp>
    using forward_list_iterator = __std__::__fwd_list_iterator<_Tp>;

}

#endif //STL2_0_FORWARD_LIST_H
