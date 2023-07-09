//
// Created by 11508 on 2023-07-07.
//

#ifndef STL2_0_DEQUE_H
#define STL2_0_DEQUE_H

#include "./sequence_container/stl_deque.h"

namespace stl{

    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize = 0>
    using deque_base = __std__::_Deque_Base<_Tp, _Alloc, _BufferSize>;
}
#endif //STL2_0_DEQUE_H
