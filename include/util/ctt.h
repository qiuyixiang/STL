//
// Created by 11508 on 2023-05-21.
//

#ifndef STL2_0_CTT_H
#define STL2_0_CTT_H

#include <bits/move.h>
/// Base Functional and Macro Library


/// Exception For New Delete

#define  _STL_THROWN(_Ecp) throw(_Ecp)

#define _STL_NO_EXCEPTION noexcept

#define _STL_USE_CONSTEXPR constexpr

#define _STL_USE_UTILITY_INLINE inline
#define _STL_USE_MULL_TMP_ARG <>

#define __STL_GCC_MOVE(__val) std::move(__val)

#define BREAK "-----------------------------------------"

namespace stl{
    /// Base type define
    typedef unsigned int size_t;
    typedef signed int ptrdiff_t;

}

#endif //STL2_0_CTT_H
