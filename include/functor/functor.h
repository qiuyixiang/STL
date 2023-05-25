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

    /// unary negate
    template<typename _Predicate>
    class unary_negate :
            public unary_functor<typename _Predicate::argument_type, bool>{
    protected:
        _Predicate __opt;
    public:
        _STL_USE_CONSTEXPR explicit unary_negate(const _Predicate& __x) : __opt(__x) {  };
        bool operator()(const typename _Predicate::argument_type& __val) const {
            return !(__opt(__val));
        }
    };

    template<typename _Predicate>
    _STL_USE_UTILITY_INLINE unary_negate<_Predicate> not1(const _Predicate& __opt){
        return unary_negate<_Predicate>(__opt);
    }

    /// binary negate
    template<typename _Predicate>
    class binary_negate :
            public binary_functor<typename _Predicate::first_argument_type,
            typename _Predicate::second_argument_type, bool>{
    protected:
            _Predicate __opt;
    public:
        _STL_USE_CONSTEXPR explicit binary_negate(const _Predicate& __x) : __opt(__x) {  };
        bool operator()(const typename _Predicate::first_argument_type& __x,
                const typename _Predicate::second_argument_type& __y) const {
            return !(this->__opt(__x, __y));
        }
    };
    template<typename _Predicate>
    _STL_USE_UTILITY_INLINE unary_negate<_Predicate> not2(const _Predicate& __opt){
        return binary_negate<_Predicate>(__opt);
    }

    /// binder1st
    template<typename _Predicate>
    class binder1st :
            public unary_functor<typename _Predicate::second_argument_type,
            typename _Predicate::result_type>{
    protected:
            typename _Predicate::first_argument_type __val;
            _Predicate __opt;
    public:
        _STL_USE_CONSTEXPR binder1st(const _Predicate& __opt,
                                     const typename _Predicate::first_argument_type& __val)
                                     : __opt(__opt), __val(__val) {  };
        typename _Predicate::result_type
        operator ()(const typename _Predicate::second_argument_type& __x){
            return this->__opt(this->__val, __x);
        }
    };

    template<typename _Predicate, typename _Tp>
    _STL_USE_UTILITY_INLINE binder1st<_Predicate>
    bind1st(const _Predicate& __opt, const _Tp& __val){
        return binder1st<_Predicate>(__opt, __val);
    }

    /// binder2nd
    template<typename _Predicate>
    class binder2nd :
            public unary_functor<typename _Predicate::first_argument_type,
                    typename _Predicate::result_type>{
    protected:
        typename _Predicate::second_argument_type __val;
        _Predicate __opt;
    public:
        _STL_USE_CONSTEXPR binder2nd(const _Predicate& __opt,
                                     const typename _Predicate::second_argument_type& __val)
                : __opt(__opt), __val(__val) {  };
        typename _Predicate::result_type
        operator ()(const typename _Predicate::first_argument_type& __x){
            return this->__opt(__x, this->__val);
        }
    };

    template<typename _Predicate, typename _Tp>
    _STL_USE_UTILITY_INLINE binder1st<_Predicate>
    bind2nd(const _Predicate& __opt, const _Tp& __val){
        return binder1st<_Predicate>(__opt, __val);
    }

    /// unary_compose
    template<typename _Operation1, typename _Operation2>
    class unary_compose :
            public unary_functor<typename _Operation2::argument_type,
            typename _Operation1::result_type>{
    protected:
            _Operation1 __opt1;
            _Operation2 __opt2;
    public:
        _STL_USE_CONSTEXPR unary_compose
        (const _Operation1& _opt1, const _Operation2& _opt2) : __opt1(_opt1), __opt2(_opt2) {  };
        typename _Operation1::result_type
        operator()(const typename _Operation2::argument_type& __val){
            return this->__opt1(this->__opt2(__val));
        }
    };

    template<typename _Operation1, typename _Operation2>
    _STL_USE_UTILITY_INLINE unary_compose<_Operation1, _Operation2>
    compose1(const _Operation1& __opt1, const _Operation2& __opt2){
        return unary_compose<_Operation1, _Operation2>(__opt1, __opt2);
    }

    /// binary_compose
    template<typename _Operation1, typename _Operation2, typename _Operation3>
    class binary_compose :
            public unary_functor<typename _Operation3::argument_type,
            typename _Operation1::result_type>{
    protected:
        _Operation1 __opt1;
        _Operation2 __opt2;
        _Operation3 __opt3;
    public:
        _STL_USE_CONSTEXPR binary_compose
        (const _Operation1& _opt1, const _Operation2& _opt2, const _Operation3& _opt3)
        : __opt1(_opt1), __opt2(_opt2) , __opt3(_opt3) {  };

        typename _Operation1::result_type
        operator()(const typename _Operation3::argument_type& __val){
            return this->__opt1(this->__opt2(__val, this->__opt3(__val)));
        }
    };
    template<typename _Operation1, typename _Operation2, typename _Operation3>
    _STL_USE_UTILITY_INLINE binary_compose<_Operation1, _Operation2, _Operation3>
    compose2(const _Operation1& _opt1, const _Operation2& _opt2, const _Operation3& _opt3){
        return binary_compose<_Operation1, _Operation2, _Operation3>(_opt1, _opt2, _opt3);
    }

    /**
     * Pointer to Function
     * Pointer to Member Function
     * Just a simple package for pointer
     */

    /// pointer_to_unary_function
    template<typename _Arg, typename _Res>
    class pointer_to_unary_function
            : public unary_functor<_Arg, _Res>{
    protected:
        _Res (*_M_ptr)(_Arg);
    public:
        explicit _STL_USE_CONSTEXPR pointer_to_unary_function() {  }
        explicit _STL_USE_CONSTEXPR
        pointer_to_unary_function(_Res (*__ptr)(_Arg)) : _M_ptr(__ptr) {  }

        _Res operator()(_Arg __val) const {
            return this->_M_ptr(__val);
        }
    };

    template<typename _Arg, typename _Res>
    _STL_USE_UTILITY_INLINE pointer_to_unary_function<_Arg, _Res>
            ptr_fun(_Res (*__ptr)(_Arg)){
        return pointer_to_unary_function<_Arg, _Res>(__ptr);
    }

    /// pointer_to_binary_function
    template<typename _Arg1, typename _Arg2, typename _Res>
    class pointer_to_binary_function :
            public binary_functor<_Arg1, _Arg2, _Res>{
    protected:
            _Res (*_M_ptr)(_Arg1, _Arg2);
        explicit _STL_USE_CONSTEXPR pointer_to_binary_function() {  }
        explicit _STL_USE_CONSTEXPR
        pointer_to_binary_function (_Res (*__ptr)(_Arg1, _Arg2)) : _M_ptr(__ptr) { }

        _Res operator()(_Arg1 arg1, _Arg2 arg2) const {
            return this->_M_ptr(arg1, arg2);
        }
    };

    template<typename _Arg1, typename _Arg2, typename _Res>
    _STL_USE_UTILITY_INLINE pointer_to_binary_function<_Arg1, _Arg2, _Res>
    ptr_fun(_Res (*__ptr)(_Arg1, _Arg2)){
        return pointer_to_binary_function<_Arg1, _Arg2, _Res>(__ptr);
    }

    /// Pointer To member Function
    template<typename _Class, typename _Res>
    class mem_fun_t : public unary_functor<_Class*, _Res>{
    protected:
            _Res (_Class::*_M_ptr)();
    public:
            explicit _STL_USE_CONSTEXPR mem_fun_t(_Res (_Class::*__ptr)()) : _M_ptr(__ptr) {  };
            _Res operator()(_Class * __ptr) const {
                return (__ptr->*_M_ptr)();
            }
    };

    template<typename _Class, typename _Res>
    _STL_USE_UTILITY_INLINE mem_fun_t<_Class, _Res> mem_fun(_Res (_Class::*__ptr)()){
        return mem_fun_t<_Class, _Res>(__ptr);
    }
}
#endif //STL2_0_FUNCTOR_H
