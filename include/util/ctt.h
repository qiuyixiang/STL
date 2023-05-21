//
// Created by 11508 on 2023-05-21.
//

#ifndef STL2_0_CTT_H
#define STL2_0_CTT_H

/// Base Functional and Macro Library


/// Exception For New Delete

#define  _STL_THROWN(_Ecp) throw(_Ecp)
#define _STL_NO_EXCEPTION noexcept


namespace stl{
    /// Base type define
    typedef unsigned int size_t;
    typedef stl::size_t ptrdiff_t;
}

#endif //STL2_0_CTT_H