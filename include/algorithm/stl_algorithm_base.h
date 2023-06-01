//
// Created by 11508 on 2023-06-01.
//

#ifndef STL2_0_STL_ALGORITHM_BASE_H
#define STL2_0_STL_ALGORITHM_BASE_H

/**
 * Algorithm include Base Dependent Algorithm
 * Base Algorithm Header File
 * Create on 2023-6-1
 *
 */


/// Base Algorithm Function

#include "../util/ctt.h"

namespace __std__{

}

namespace stl{

    /// max()

    template<typename _Tp>
    _STL_USE_CONSTEXPR inline const _Tp&
    max(const _Tp& __l, const _Tp& __r){
        return __l < __r ? __r : __l;
    }
    template<typename _Tp, typename _Compare>
    _STL_USE_CONSTEXPR inline const _Tp&
    max(const _Tp& __l, const _Tp& __r, _Compare __comp){
        if (__comp(__l, __r))
            return __r;
        return __l;
    }

    /// min()

    template<typename _Tp>
    _STL_USE_CONSTEXPR inline const _Tp&
    min(const _Tp& __l, const _Tp& __r){
        return __l < __r ? __l : __r;
    }
    template<typename _Tp, typename _Compare>
    _STL_USE_CONSTEXPR inline const _Tp&
    min(const _Tp& __l, const _Tp& __r, _Compare __comp){
        if (__comp(__l, __r))
            return __l;
        return __r;
    }
}
#endif //STL2_0_STL_ALGORITHM_BASE_H
