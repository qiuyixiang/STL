//
// Created by 11508 on 2023-06-05.
//

#ifndef STL2_0_STL_FWD_LIST_H
#define STL2_0_STL_FWD_LIST_H

/**
 * The Achievement Of C++ Forward List
 *
 * Create on 2023-6-5
 *
 * Version 1.0.0 Just Achieve Some Basic Function
 * fwd_list is the Basic Implementation of stl::forward_list
 *
 * Notes :
 *      forward list is a single forward list
 *      and without circulation of its' head
 *      single linked list
 */

#include "../allocator/allocator_traits.h"
#include "../util/ctt.h"
#include "../util/utility.h"
#include "../iterator/iterator_traits.h"

/// TODO List  implementation reverse

namespace __std__{

    /// Base Node For _fwd_list_node !
    struct __Fwd_list_base_node{

        __Fwd_list_base_node * _M_next = nullptr;

        _STL_USE_CONSTEXPR __Fwd_list_base_node() = default;
        explicit _STL_USE_CONSTEXPR
        __Fwd_list_base_node(__Fwd_list_base_node * __ptr) : _M_next(__ptr) {  }
    };

    /// Implementation of __fwd_list_node
    template<typename _Tp>
    struct __fwd_list_node : public __Fwd_list_base_node {
        /// Only Data Member !
        _Tp _M_storage;

        _Tp _M_get_val() const {  return this->_M_storage;  }

        _Tp * _M_ptr() {  return std::addressof(this->_M_storage);  }
        const _Tp* _M_ptr() const {return std::addressof(this->_M_storage); }

        _Tp * _M_get_valptr() {  return this->_M_ptr(); }
        const _Tp* _M_get_valptr() const noexcept {  return this->_M_ptr(); }
    };

    template<typename _Tp>
    class __fwd_list_iterator {
    public:
        typedef stl::forward_iterator_tag           iterator_category;
        typedef _Tp                                 value_type;
        typedef _Tp*                                pointer;
        typedef _Tp&                                reference;
        typedef const _Tp*                          const_pointer;
        typedef const _Tp&                          const_reference;
        typedef stl::ptrdiff_t                      difference_type;
        typedef stl::size_t                         size_type;

        typedef __fwd_list_iterator<_Tp>    fwd_list_iterator;
        typedef __fwd_list_node<_Tp>        Node_type;
        typedef __Fwd_list_base_node        Base_Node_type;
        typedef __fwd_list_iterator         _Self;

        /// The Only Data Member
        Base_Node_type * _M_ptr;

    public:
        /// Constructor

        /// Without Move Constructor Because The Move Constructor Has
        /// Same Efficiency With Copy Constructor !
        _STL_USE_CONSTEXPR __fwd_list_iterator() : _M_ptr(nullptr) {  }
        explicit _STL_USE_CONSTEXPR
        __fwd_list_iterator(Base_Node_type * __other) : _M_ptr(__other) {  }

        _STL_USE_CONSTEXPR
        __fwd_list_iterator(_Self& __other) : _M_ptr(__other._M_ptr) {  }

        _STL_USE_CONSTEXPR
        __fwd_list_iterator(const _Self& __other) _STL_NO_EXCEPTION
        : _M_ptr(__other._M_ptr) {  }

        ~__fwd_list_iterator() = default;

        /// Member Function

        Base_Node_type* base() const {
            return this->_M_ptr;
        }
        reference operator*() {
            return *(static_cast<Node_type*>(_M_ptr))->_M_get_valptr();
        }
        pointer operator->(){
            return static_cast<Node_type*>(_M_ptr)->_M_get_valptr();
        }
        _Self & operator++() _STL_NO_EXCEPTION{
            this->_M_ptr = this->_M_ptr->_M_next;
            return *this;
        }
        _Self operator++(int) _STL_NO_EXCEPTION {
            _Self __temp = *this;
            this->_M_ptr = this->_M_ptr->_M_next;
            return __temp;
        }
        bool operator==(const _Self& __other){
            return (this->base() == __other.base());
        }
        bool operator!=(const _Self& __other){
            return !(*this == __other);
        }
        _Self _M_Next_Iter() const _STL_NO_EXCEPTION {
            if (this->_M_ptr)
                return _Self (this->_M_ptr->_M_next);
            else
                return _Self (nullptr);
        }
    };

    /// Global Operator== For Forward List Iterator
    template<typename _Tp>
    _STL_USE_UTILITY_INLINE bool
    operator==(__fwd_list_iterator<_Tp>& __l, const __fwd_list_iterator<_Tp>& __r){
        return __l.base() == __r.base();
    }

    template<typename _Tp>
    _STL_USE_UTILITY_INLINE bool
    operator!=(__fwd_list_iterator<_Tp>& __l, const __fwd_list_iterator<_Tp>& __r){
        return __l.base() != __r.base();
    }

    template<typename _Tp, typename _Alloc>
    class __fwd_list_base {
    public:
            typedef typename  stl::__allocator_traits<_Alloc>::allocator_type
            allocator_type;
            typedef typename stl::__allocator_traits<_Alloc>::
            template rebind_alloc<__fwd_list_node<_Tp>> rebind_allocator_type;
            typedef allocator_type _Tp_allocator_type;
            typedef stl::size_t  size_type;

            typedef __Fwd_list_base_node Base_Node_type;
            typedef __fwd_list_node<_Tp> Node_type;

    public:
            /// Data Member Only Have a Pointer point at next position !
            Base_Node_type _M_head;

            /// Constructor
            _STL_USE_CONSTEXPR __fwd_list_base() : _M_head() {  };
            /// Move A List Base
            explicit __fwd_list_base(__fwd_list_base&& __other) : _M_head() {
                this->_M_head._M_next = __other._M_head._M_next;
                __other._M_head._M_next = nullptr;
            }
            /// Destructor Doing Nothing
            ~__fwd_list_base() = default;

    protected:
            /// Functional Operation
            Node_type * _get_node();

            template<typename ..._Args>
            Node_type * _create_node(_Args&&...args);

            void _put_node(Node_type * __ptr);
            void _destroy_node(Node_type* __ptr);
            rebind_allocator_type get_allocator() const;
    };

    template<typename _Tp, typename _Alloc>
    typename __fwd_list_base<_Tp, _Alloc>::Node_type*
    __fwd_list_base<_Tp, _Alloc>::_get_node() {
        Node_type * __temp = this->get_allocator().allocate(1);
        return __temp;
    }
    template<typename _Tp, typename _Alloc>
    template<typename ..._Args>
    typename __fwd_list_base<_Tp, _Alloc>::Node_type*
    __fwd_list_base<_Tp, _Alloc>::_create_node(_Args&&...args){
        Node_type * __temp = this->_get_node();
        __temp->_M_next = nullptr;
        /// Construct for Value
        stl::_Construct(std::addressof(__temp->_M_storage),
                        std::forward<_Args>(args)...);
        return __temp;
    }
    template<typename _Tp, typename _Alloc>
    void __fwd_list_base<_Tp, _Alloc>::_put_node(Node_type *__ptr) {
        if (__ptr)
            this->get_allocator().deallocate(__ptr);
    }
    template<typename _Tp, typename _Alloc>
    void __fwd_list_base<_Tp, _Alloc>::_destroy_node(Node_type *__ptr) {
        stl::_Destroy(std::addressof(__ptr->_M_storage));
        this->_put_node(__ptr);
    }
    template<typename _Tp, typename _Alloc>
    typename __fwd_list_base<_Tp, _Alloc>::rebind_allocator_type
    __fwd_list_base<_Tp, _Alloc>::get_allocator() const {
        return rebind_allocator_type ();
    }
}
namespace stl{

    /// The Implementation OF stl::forward_list
    template<typename _Tp, typename _Alloc = stl::default_allocator<_Tp>>
    class _fwd_list : protected __std__::__fwd_list_base<_Tp, _Alloc>{
    public:
        /// Public Type Define
        typedef __std__::__Fwd_list_base_node Base_Node_type;
        typedef typename __std__::__fwd_list_base<_Tp, _Alloc>
        ::allocator_type allocator_type;
        typedef __std__::__fwd_list_node<_Tp> Node_type;
        typedef typename __std__::__fwd_list_base<_Tp, _Alloc>
        ::rebind_allocator_type rebind_allocator_type;
        typedef typename __std__::__fwd_list_base<_Tp, _Alloc>
        ::_Tp_allocator_type _Tp_allocator_type;

        typedef typename stl::__allocator_traits<rebind_allocator_type>
        allocator_traits_type;
        typedef  __std__::__fwd_list_base<_Tp, _Alloc> _Base;

        typedef _Tp                                       value_type;
        typedef _Tp&                                      reference;
        typedef const _Tp&                                const_reference;
        typedef _Tp *                                     pointer;
        typedef const _Tp *                               const_pointer;
        typedef typename __std__::__fwd_list_base<_Tp, _Alloc>
        ::size_type size_type;

        typedef __std__::__fwd_list_iterator<_Tp>                iterator;
        typedef const __std__::__fwd_list_iterator<_Tp>          const_iterator;
        /// Notes This Single Linked List Dose not support reverse Iterator

    private:
        /// Private Utility Member Function
        template<typename BidirectionalIterator>
        void _M_copy(BidirectionalIterator _first, BidirectionalIterator _last);

    public:
        /// Constructor
        _STL_USE_CONSTEXPR _fwd_list() : _Base() {  };
        _fwd_list(const std::initializer_list<value_type>&_Li) : _Base()
        { this->template _M_copy(_Li.begin(), _Li.end());  }

        /// Copy And Move Constructor
        /// Recommend To Use Move Operator To Increase Efficiency !
        _fwd_list(const _fwd_list& __other);
        _fwd_list(_fwd_list&& __other);

        _fwd_list& operator=(const _fwd_list& __other);
        _fwd_list& operator=(_fwd_list&& __other);

        /// Destructor
        ~_fwd_list(){
            if (this->_M_head._M_next)
                this->clear();
        }

    public:
        /// Public Member Function
        bool empty() const _STL_NO_EXCEPTION;
        /// Don't Recommend to use this function !
        size_type _size() const _STL_NO_EXCEPTION;
        size_type max_size() const _STL_NO_EXCEPTION;

        reference front();
        const_reference front() const;

        void push_front(const value_type& _val);
        void push_front(value_type&& _val);

        template<typename ..._Args>
        void emplace_front(_Args&&...args);

        void pop_front();

        iterator erase_front();
        iterator erase_after(const_iterator __pos);

        iterator insert_after(const_iterator __pos, const value_type& _val);
        iterator insert_after(const_iterator __pos, value_type&& _val);

        template<typename ..._Args>
        iterator emplace_after(const_iterator __pos, _Args&&...__args);

        void clear();
        void display(bool debugger = false) const;
        void swap(_fwd_list& __other);

        template<typename InputIterator>
        void assign(InputIterator __first, InputIterator __last);

        void assign(std::initializer_list<value_type>& _Li);

        void reverse() _STL_NO_EXCEPTION;
        void unique() _STL_NO_EXCEPTION;
        void sort();
        void remove(const value_type& _val);
        void merge();
        void splice_after();

        /// Public Member Function For Iterator
        iterator begin() _STL_NO_EXCEPTION {
            return iterator (this->_M_head._M_next);
        }
        iterator end() _STL_NO_EXCEPTION{
            return iterator (nullptr);
        }
        const_iterator begin() const _STL_NO_EXCEPTION {
            return const_iterator (this->_M_head._M_next);
        }
        const_iterator end() const _STL_NO_EXCEPTION {
            return const_iterator (nullptr);
        }
        const_iterator cbegin() const _STL_NO_EXCEPTION {
            return const_iterator (this->_M_head._M_next);
        }
        const_iterator cend() const _STL_NO_EXCEPTION {
            return const_iterator (nullptr);
        }
        iterator before_begin() _STL_NO_EXCEPTION {
            return iterator (std::addressof(this->_M_head));
        }
        const_iterator before_begin() const _STL_NO_EXCEPTION {
            return const_iterator (std::addressof(this->_M_head));
        }
        const_iterator cbefore_begin() const _STL_NO_EXCEPTION {
            return const_iterator (std::addressof(this->_M_head));
        }
    };
    template<typename _Tp, typename _Alloc>
    void _fwd_list<_Tp, _Alloc>::display(bool debugger) const {
        for (auto _Iter = this->begin(); _Iter != iterator (nullptr); ++_Iter)
            std::cout<<*_Iter<<" ";
        std::cout<<std::endl;
        if (debugger)
            std::cout<<"Size : "<<this->_size()<<std::endl;
    }
    /// Recommend Don't Use This Function Because of This Functions'
    /// Speed And Efficiency is to low!
    template<typename _Tp, typename _Alloc>
    typename _fwd_list<_Tp, _Alloc>::size_type _fwd_list<_Tp, _Alloc>::_size() const noexcept {
        size_type __size = 0;
        auto __current_iter = this->begin();
        while (__current_iter != this->end()){
            ++__current_iter;
            ++__size;
        }
        return __size;
    }
    template<typename _Tp, typename _Alloc>
    typename _fwd_list<_Tp, _Alloc>::size_type _fwd_list<_Tp, _Alloc>::max_size() const noexcept {
        return this->get_allocator().max_size();
    }
    template<typename _Tp, typename _Alloc>
    template<typename ..._Args>
    typename _fwd_list<_Tp, _Alloc>::iterator _fwd_list<_Tp, _Alloc>::
    emplace_after(const_iterator __pos, _Args&&...__args) {
        Node_type * __temp = this->template _create_node
                (std::forward<_Args>(__args)...);
        __temp->_M_next = __pos.base()->_M_next;
        __pos.base()->_M_next = __temp;
        return iterator (__temp);
    }
    template<typename _Tp, typename _Alloc>
    void _fwd_list<_Tp, _Alloc>::push_front(value_type &&_val) {
        this->template emplace_after(this->before_begin(), std::move(_val));
    }
    template<typename _Tp, typename _Alloc>
    void _fwd_list<_Tp, _Alloc>::push_front(const value_type &_val) {
        this->template emplace_after(this->before_begin(), _val);
    }
    template<typename _Tp, typename _Alloc>
    template<typename ..._Args>
    void _fwd_list<_Tp, _Alloc>::emplace_front(_Args &&...args) {
        this->template emplace_after(this->before_begin(), std::forward<_Args>(args)...);
    }
    template<typename _Tp, typename _Alloc>
    template<typename BidirectionalIterator>
    void _fwd_list<_Tp, _Alloc>::_M_copy(BidirectionalIterator _first, BidirectionalIterator _last) {
        /// Copy Reversely
        /// Copy [_last, _first) In Other Word is [__first, __last);
        BidirectionalIterator __first = --_last;
        BidirectionalIterator __last = --_first;
        while (__first != __last)
            this->template emplace_front(*__first--);
    }
    template<typename _Tp, typename _Alloc>
    typename _fwd_list<_Tp, _Alloc>::iterator _fwd_list<_Tp, _Alloc>::
    insert_after(const_iterator __pos, value_type &&_val) {
        return this->template emplace_after(__pos, std::move(_val));
    }
    template<typename _Tp, typename _Alloc>
    typename _fwd_list<_Tp, _Alloc>::iterator _fwd_list<_Tp, _Alloc>::
    insert_after(const_iterator __pos, const value_type &_val) {
        return this->template emplace_after(__pos, _val);
    }
    template<typename _Tp, typename _Alloc>
    typename _fwd_list<_Tp, _Alloc>::iterator _fwd_list<_Tp, _Alloc>::
    erase_after(const_iterator __pos) {
        Base_Node_type *__del_iter = __pos.base()->_M_next;
        __pos.base()->_M_next = __del_iter->_M_next;
        this->_destroy_node(static_cast<Node_type*>(__del_iter));

        return iterator (__pos.base()->_M_next);
    }
    template<typename _Tp, typename _Alloc>
    void _fwd_list<_Tp, _Alloc>::pop_front() {
        this->erase_after(this->before_begin());
    }
    template<typename _Tp, typename _Alloc>
    typename _fwd_list<_Tp, _Alloc>::iterator _fwd_list<_Tp, _Alloc>::
    erase_front() {
        return this->erase_after(this->before_begin());
    }
    template<typename _Tp, typename _Alloc>
    typename _fwd_list<_Tp, _Alloc>::reference _fwd_list<_Tp, _Alloc>::front() {
        return *(this->begin());
    }
    template<typename _Tp, typename _Alloc>
    typename _fwd_list<_Tp, _Alloc>::const_reference _fwd_list<_Tp, _Alloc>::front() const {
        return *(this->begin());
    }
    template<typename _Tp, typename _Alloc>
    bool _fwd_list<_Tp, _Alloc>::empty() const noexcept {
        return (this->_M_head._M_next == nullptr);
    }
    /// Clear Whole Forward List
    template<typename _Tp, typename _Alloc>
    void _fwd_list<_Tp, _Alloc>::clear() {
        auto __current = this->begin();
        while (__current != this->end()){
            auto __del = __current;
            ++__current;
            this->_destroy_node(static_cast<Node_type*>(__del.base()));
        }
        this->_M_head._M_next = nullptr;
    }
    /// Copy And Move Operator
    template<typename _Tp, typename _Alloc>
    _fwd_list<_Tp, _Alloc>& _fwd_list<_Tp, _Alloc>::
    operator=(_fwd_list&& __other) {
        /// Deal With Self-Assignment !
        if (std::addressof(*this) != std::addressof(__other)){
            this->_M_head._M_next = __other._M_head._M_next;
            __other._M_head._M_next = nullptr;
        }
    }
    template<typename _Tp, typename _Alloc>
    _fwd_list<_Tp, _Alloc>& _fwd_list<_Tp, _Alloc>::
    operator=(const _fwd_list<_Tp, _Alloc> &__other) {
        /// Low Efficiency !  O(n)

        if (std::addressof(*this) != &__other){
            /// Clear Old List
            this->clear();
            /// push_front at begin_before position
            this->template assign(__other.begin(), __other.end());
        }
    }
    /// Copy And Move Constructor
    template<typename _Tp, typename _Alloc>
    _fwd_list<_Tp, _Alloc>::
    _fwd_list(const _fwd_list<_Tp, _Alloc> &__other) :_Base() {
        /// push_front at begin_before position
        this->template assign(__other.begin(), __other.end());
    }
    template<typename _Tp, typename _Alloc>
    _fwd_list<_Tp, _Alloc>::
    _fwd_list(_fwd_list &&__other) :_Base() {
        this->_M_head._M_next = __other._M_head._M_next;
        __other._M_head._M_next = nullptr;
    }
    template<typename _Tp, typename _Alloc>
    void _fwd_list<_Tp, _Alloc>::swap(_fwd_list&__other) {
        stl::swap(this->_M_head._M_next, __other._M_head._M_next);
    }
    template<typename _Tp, typename _Alloc>
    template<typename InputIterator>
    void _fwd_list<_Tp, _Alloc>::assign(InputIterator __first, InputIterator __last) {
        if (!this->empty())
            this->clear();
        const size_type __size = stl::distance(__first, __last);
        /// Set a Buffer to Transfer Element !
        /// TODO Replace stl::vector to stl::array to Buffer !
        stl::vector<_Tp, _Alloc>__buffer(__size);
        /// Copy From Buffer
        for (size_type  __index = 0 ; __first != __last; ++__first)
            __buffer[__index++] = *__first;

        this->template _M_copy(__buffer.begin(), __buffer.end());
    }

    template<typename _Tp, typename _Alloc>
    void _fwd_list<_Tp, _Alloc>::assign(std::initializer_list<value_type> &_Li) {
        this->template _M_copy(_Li.begin(), _Li.end());
    }
    /// TODO Implementation of reverse() double pointer !
    template<typename _Tp, typename _Alloc>
    void _fwd_list<_Tp, _Alloc>::reverse() noexcept {


    }
    template<typename _Tp, typename _Alloc>
    void _fwd_list<_Tp, _Alloc>::sort() {

    }
    template<typename _Tp, typename _Alloc>
    void _fwd_list<_Tp, _Alloc>::remove(const value_type &_val) {

    }
    template<typename _Tp, typename _Alloc>
    void _fwd_list<_Tp, _Alloc>::merge() {

    }
    template<typename _Tp, typename _Alloc>
    void _fwd_list<_Tp, _Alloc>::splice_after() {

    }
    /// Global Swap For forward_list
    template<typename _Tp, typename _Alloc>
    void swap(_fwd_list<_Tp, _Alloc>& __l, _fwd_list<_Tp, _Alloc>& __r){
        __l.swap(__r);
    }
}
#endif //STL2_0_STL_FWD_LIST_H
