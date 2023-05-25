//
// Created by 11508 on 2023-05-24.
//

#ifndef STL2_0_UTILITY_H
#define STL2_0_UTILITY_H

/**
 * Some Utility Class Or Function For C++ Standard Library
 *
 * Create on 2023-4-24
 *
 * class pair (Structure)
 */

#include "./ctt.h"
namespace stl{

    /// Pair Implementation

    template<typename _Arg1, typename _Arg2>
    struct pair {
        using first_type = _Arg1;
        using second_type = _Arg2;

        /// Public Member
        first_type first;
        second_type second;

        _STL_USE_CONSTEXPR pair() : first{ }, second { } { };

        pair(const _Arg1& __l, const _Arg2& __r) : first(__l), second(__r) {  };
        pair(_Arg1&& __l, _Arg2&& __r) : first(std::move(__l)), second(std::move(__r)) {  };

        pair(const pair& _Other) : first(_Other.first), second(_Other.second) { };
        pair(pair&& _Other) : first(std::move(_Other.first)), second(std::move(_Other.second)) { };

        template<typename _Other1, typename _Other2>
        pair(const _Other1& __other1, const _Other2& __other2)
        : first(__other1), second(__other2) {  };

        template<typename _Other1, typename _Other2>
        pair( _Other1&& __other1, _Other2&& __other2)
        : first(std::forward<_Other1>(__other1)), second(std::forward<_Other2>(__other2)) {
#ifdef DEBUGGER
            std::cout<<"Forward Constructor"<<std::endl;
#endif
        };

        _STL_USE_UTILITY_INLINE pair& operator=(const pair& _Other){
            if (&_Other != this){
                first = _Other.first;
                second = _Other.second;
            }
            return *this;
        }
        _STL_USE_UTILITY_INLINE pair& operator=(pair&& _Other){
            if (&_Other != this){
                first = std::move(_Other.first);
                second = std::move(_Other.second);
            }
            return *this;
        }
        ~pair() = default;

        /*TODO Implementation Of Swap*/
        void swap(pair& _Other);

        template<typename _Other1, typename _Other2>
        pair& operator=(const pair<_Other1, _Other2>& __other){
            if (&__other != this){
                first = __other.first;
                second = __other.second;
            }
            return *this;
        }
        template<typename _Other1, typename _Other2>
        pair& operator=(pair<_Other1, _Other2>&& __other){
            if (&__other != this){
                first = std::forward<_Other1>(__other.first);
                second = std::forward<_Other2>(__other.second);
            }
            return *this;
        }
    };

    template<typename _Tp1, typename _Tp2>
    pair<_Tp1, _Tp2> make_pair(_Tp1&& __l, _Tp2&& __r){
        return pair<_Tp1, _Tp2>(std::forward<_Tp1>(__l), std::forward<_Tp2>(__r));
    }

    /// Operator OverWrite For Pair
    template<typename _Tp1, typename _Tp2>
    _STL_USE_UTILITY_INLINE bool operator==
    (const pair<_Tp1, _Tp2>& __l, const pair<_Tp1, _Tp2>& __r){
        return __l.first == __r.first && __l.second == __r.second;
    }
    template<typename _Tp1, typename _Tp2>
    _STL_USE_UTILITY_INLINE bool operator!=
            (const pair<_Tp1, _Tp2>& __l, const pair<_Tp1, _Tp2>& __r){
        return !(__l == __r);
    }
    template<typename _Tp1, typename _Tp2>
    _STL_USE_UTILITY_INLINE bool operator<
    (const pair<_Tp1, _Tp2>& __l, const pair<_Tp1, _Tp2>& __r){
        return __l.first < __r.first || (__l.first == __r.first && __l.second < __r.second);
    }
    template<typename _Tp1, typename _Tp2>
    _STL_USE_UTILITY_INLINE bool operator>
    (const pair<_Tp1, _Tp2>& __l, const pair<_Tp1, _Tp2>& __r){
        return __l.first > __r.first || (__l.first == __r.first && __l.second > __r.second);
    }

}
#endif //STL2_0_UTILITY_H
