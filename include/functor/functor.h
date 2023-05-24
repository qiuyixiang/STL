//
// Created by 11508 on 2023-05-24.
//

#ifndef STL2_0_FUNCTOR_H
#define STL2_0_FUNCTOR_H

/**
 * Base File For C++ Standard Functor
 * Implementation of unary and binary functors
 *
 */
#include "../util/ctt.h"
#include <bits/move.h>

namespace stl{

    /// Base Class For Functor
    template<typename _Arg, typename _Res>
    struct unary_functor{
        typedef _Arg  argument_type;
        typedef _Res  result_type;
    };

    template<typename _Arg1, typename _Arg2, typename _Res>
    struct binary_functor{
        typedef _Arg1 first_argument_type;
        typedef _Arg2 second_argument_type;
        typedef _Res result_type;
    };


    /// Arithmetic Functor

    template<typename _Tp = void>
    struct plus;

    template<typename _Tp = void>
    struct minus;

    template<typename _Tp = void>
    struct multiply;

    template<typename _Tp = void>
    struct divide;

    template<typename _Tp = void>
    struct modulus;

    template<typename _Tp = void>
    struct negate;

    /// Implementation of Formal Arithmetic Functor
    template<typename _Tp>
    struct plus : public binary_functor<_Tp, _Tp, _Tp>{
        _STL_USE_CONSTEXPR _Tp operator()(const _Tp& __l, const _Tp& __r) const {
            return __l + __r;
        }
    };
    template<typename _Tp>
    struct minus : public binary_functor<_Tp, _Tp, _Tp>{
        _STL_USE_CONSTEXPR _Tp operator()(const _Tp& __l, const _Tp& __r) const {
            return __l - __r;
        }
    };
    template<typename _Tp>
    struct multiply : public binary_functor<_Tp, _Tp, _Tp>{
        _STL_USE_CONSTEXPR _Tp operator()(const _Tp& __l, const _Tp& __r) const {
            return __l * __r;
        }
    };
    template<typename _Tp>
    struct divide : public binary_functor<_Tp, _Tp, _Tp>{
        _STL_USE_CONSTEXPR _Tp operator()(const _Tp& __l, const _Tp& __r) const {
            return __l / __r;
        }
    };
    template<typename _Tp>
    struct modulus : public binary_functor<_Tp, _Tp, _Tp>{
        _STL_USE_CONSTEXPR _Tp operator()(const _Tp& __l, const _Tp& __r) const {
            return __l % __r;
        }
    };
    template<typename _Tp>
    struct negate : public unary_functor<_Tp, _Tp>{
        _STL_USE_CONSTEXPR _Tp operator()(const _Tp& __l) const {
            return -(__l);
        }
    };
    /// Partial Specialization For Arithmetic Functor
    /// Base on C++ 11
    template<>
    struct plus<void>{
        template<typename _Tp, typename _Up>
        _STL_USE_CONSTEXPR auto operator()(_Tp&& __l, _Up&& __r)
        const noexcept(noexcept(std::forward<_Tp>(__l) + std::forward<_Up>(__r)))
        -> decltype(std::forward<_Tp>(__l) + std::forward<_Up>(__r)){
            return std::forward<_Tp>(__l) + std::forward<_Up>(__r);
        }
    };
    template<>
    struct minus<void>{
        template<typename _Tp, typename _Up>
        _STL_USE_CONSTEXPR auto operator()(_Tp&& __l, _Up&& __r)
        const noexcept(noexcept(std::forward<_Tp>(__l) - std::forward<_Up>(__r)))
        -> decltype(std::forward<_Tp>(__l) - std::forward<_Up>(__r)){
            return std::forward<_Tp>(__l) - std::forward<_Up>(__r);
        }
    };
    template<>
    struct multiply<void>{
        template<typename _Tp, typename _Up>
        _STL_USE_CONSTEXPR auto operator()(_Tp&& __l, _Up&& __r)
        const noexcept(noexcept(std::forward<_Tp>(__l) * std::forward<_Up>(__r)))
        -> decltype(std::forward<_Tp>(__l) * std::forward<_Up>(__r)){
            return std::forward<_Tp>(__l) * std::forward<_Up>(__r);
        }
    };
    template<>
    struct divide<void>{
        template<typename _Tp, typename _Up>
        _STL_USE_CONSTEXPR auto operator()(_Tp&& __l, _Up&& __r)
        const noexcept(noexcept(std::forward<_Tp>(__l) / std::forward<_Up>(__r)))
        -> decltype(std::forward<_Tp>(__l) / std::forward<_Up>(__r)){
            return std::forward<_Tp>(__l) / std::forward<_Up>(__r);
        }
    };
    template<>
    struct modulus<void>{
        template<typename _Tp, typename _Up>
        _STL_USE_CONSTEXPR auto operator()(_Tp&& __l, _Up&& __r)
        const noexcept(noexcept(std::forward<_Tp>(__l) % std::forward<_Up>(__r)))
        -> decltype(std::forward<_Tp>(__l) % std::forward<_Up>(__r)){
            return std::forward<_Tp>(__l) % std::forward<_Up>(__r);
        }
    };
    template<>
    struct negate<void>{
        template<typename _Tp>
        _STL_USE_CONSTEXPR auto operator()(_Tp&& __l)
        const noexcept(noexcept(-std::forward<_Tp>(__l)))
        -> decltype(-std::forward<_Tp>(__l)){
            return -std::forward<_Tp>(__l);
        }
    };
    /// Relational Functor

    template<typename _Tp>
    struct equal_to : public binary_functor<_Tp, _Tp, bool>{
        _STL_USE_CONSTEXPR bool operator()(const _Tp& __l, const _Tp& __r) const {
            return __l == __r;
        }
    };
    template<typename _Tp>
    struct not_equal_to : public binary_functor<_Tp, _Tp, bool>{
        _STL_USE_CONSTEXPR bool operator()(const _Tp& __l, const _Tp& __r) const {
            return __l != __r;
        }
    };
    template<typename _Tp>
    struct greater_than : public binary_functor<_Tp, _Tp, bool>{
        _STL_USE_CONSTEXPR bool operator()(const _Tp& __l, const _Tp& __r) const {
            return __l > __r;
        }
    };
    template<typename _Tp>
    struct greater_equal : public binary_functor<_Tp, _Tp, bool>{
        _STL_USE_CONSTEXPR bool operator()(const _Tp& __l, const _Tp& __r) const {
            return __l >= __r;
        }
    };
    template<typename _Tp>
    struct less_than : public binary_functor<_Tp, _Tp, bool>{
        _STL_USE_CONSTEXPR bool operator()(const _Tp& __l, const _Tp& __r) const {
            return __l < __r;
        }
    };
    template<typename _Tp>
    struct less_equal : public binary_functor<_Tp, _Tp, bool>{
        _STL_USE_CONSTEXPR bool operator()(const _Tp& __l, const _Tp& __r) const {
            return __l <= __r;
        }
    };

    /// Logic Functor
    template<typename _Tp>
    struct logic_and : public binary_functor<_Tp, _Tp, bool>{
        _STL_USE_CONSTEXPR bool operator()(_Tp& __l, _Tp&& __r) const {
            return __l && __r;
        }
    };
    template<typename _Tp>
    struct logic_or : public binary_functor<_Tp, _Tp, bool>{
        _STL_USE_CONSTEXPR bool operator()(_Tp& __l, _Tp&& __r) const {
            return __l || __r;
        }
    };

    template<typename _Tp>
    struct logic_not : public unary_functor<_Tp, bool>{
        _STL_USE_CONSTEXPR bool operator()(_Tp& __l) const {
            return !__l;
        }
    };

    /// Other Functor

    /// identity
    template<typename _Tp>
    struct identity : public unary_functor<_Tp, _Tp>{
        _STL_USE_CONSTEXPR const _Tp& operator()(_Tp& __val) const {
            return __val;
        }
    };

    /// select1st
    template<typename _Pair>
    struct select1st : public unary_functor<_Pair, typename _Pair::first_type>{
        _STL_USE_CONSTEXPR const typename _Pair::first_type&
        operator()(const _Pair& __pair) const {
            return __pair.first;
        }
    };

    /// select2nd
    template<typename _Pair>
    struct select2nd : public unary_functor<_Pair, typename _Pair::second_type>{
        _STL_USE_CONSTEXPR const typename _Pair::second_type&
        operator()(const _Pair& __pair) const {
            return __pair.second;
        }
    };

    /// project1st
    template<typename _Arg1, typename _Arg2>
    struct project1st : public binary_functor<_Arg1, _Arg2, _Arg1>{
        _STL_USE_CONSTEXPR _Arg1 operator()(const _Arg1& __l, const _Arg2&) const {
            return __l;
        }
    };

    /// project2ed
    template<typename _Arg1, typename _Arg2>
    struct project2ed : public binary_functor<_Arg1, _Arg2, _Arg2>{
        _STL_USE_CONSTEXPR _Arg1 operator()(const _Arg1&, const _Arg2& __r) const {
            return __r;
        }
    };
}
#endif //STL2_0_FUNCTOR_H
