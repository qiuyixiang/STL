//
// Created by 11508 on 2023-06-02.
//

#ifndef STL2_0_STL_LIST_H
#define STL2_0_STL_LIST_H
/**
 * This File is The Implementation Of stl::list Standard Components
 * Include List Node And A Special BiDirectional Iterator
 *
 * Create on 2023-6-2
 */
#include "../util/ctt.h"
#include "../iterator/iterator_traits.h"
#include "../allocator/allocator_traits.h"

namespace __std__{

    /// _list_node_base

    struct _list_node_base {
        _list_node_base* _M_prev;
        _list_node_base* _M_next;

        _list_node_base() : _M_next(nullptr), _M_prev(nullptr) {  };
    };

    /// _list_node

    template<typename _Tp>
    struct _list_node_ : public _list_node_base{
        typedef _Tp value_type;

        value_type _M_value;

        _list_node_() : _M_value(value_type()){  }

        value_type get_val() const { return this->_M_value;  }

        value_type * get_valptr() { return std::addressof(this->_M_value);  }
        const value_type * get_valptr() const { return std::addressof(this->_M_value); }
    };

    /// _list_iterator

    template<typename _Tp>
    class _list_iterator {
    public:
        typedef stl::bidirectional_iterator_tag     iterator_category;
        typedef _Tp                                 value_type;
        typedef _Tp*                                pointer;
        typedef _Tp&                                reference;
        typedef const _Tp*                          const_pointer;
        typedef const _Tp&                          const_reference;
        typedef stl::ptrdiff_t                      difference_type;
        typedef stl::size_t                         size_type;

        typedef _list_iterator                      list_iterator;
        typedef __std__::_list_node_<value_type>    list_node;
        typedef __std__::_list_node_<value_type>*   list_node_ptr;

    private:
        /// Private Member Data
        _list_node_base* _M_node_ptr;

    public:
        _list_node_base* base() {  return this->_M_node_ptr;  }
        _list_node_base* base() const {  return this->_M_node_ptr; }
        list_iterator _M_const_cast() const
        {  return *this;  }

    public:
        _STL_USE_CONSTEXPR _list_iterator() _STL_NO_EXCEPTION
                : _M_node_ptr(nullptr) {  }
        explicit _STL_USE_CONSTEXPR _list_iterator(list_node_ptr _Other) _STL_NO_EXCEPTION
                : _M_node_ptr(_Other) { }
        explicit _STL_USE_CONSTEXPR _list_iterator( _list_node_base * _Other) : _M_node_ptr(_Other) {  }
        explicit _STL_USE_CONSTEXPR _list_iterator(const _list_node_base * _Other)
            : _M_node_ptr(const_cast<_list_node_base *>(_Other)) {  }
        _STL_USE_CONSTEXPR _list_iterator(const list_iterator& _Other) : _M_node_ptr(_Other.base()) {  }
        ~_list_iterator() = default;

        bool operator==(const list_iterator& _Other) const
        {  return this->base() == _Other.base();  }
        bool operator!=(const list_iterator& _Other) const
        {  return !(this->operator==(_Other)); }

        /// downcast from _List_node_base to _List_node to get to value.
        reference operator*() const {
            ///*static_cast<_Node*>(_M_node)->_M_valptr();
            return *(static_cast<list_node*>(this->_M_node_ptr)->get_valptr());
        }
        pointer operator->() const {
            return static_cast<list_node*>(this->_M_node_ptr)->get_valptr();
        }

        list_iterator & operator++() _STL_NO_EXCEPTION {
            this->_M_node_ptr = this->_M_node_ptr->_M_next;
            return *this;
        }
        list_iterator operator++(int) _STL_NO_EXCEPTION {
            list_iterator __temp = *this;
            this->_M_node_ptr = this->_M_node_ptr->_M_next;
            return __temp;
        }
        list_iterator & operator--() _STL_NO_EXCEPTION {
            this->_M_node_ptr = this->_M_node_ptr->_M_prev;
            return *this;
        }
        list_iterator operator--(int) _STL_NO_EXCEPTION {
            list_iterator __temp = *this;
            this->_M_node_ptr = this->_M_node_ptr->_M_prev;
            return __temp;
        }
    };

    template<typename _Tp>
    inline bool operator==(const _list_iterator<_Tp>& __l, const _list_iterator<_Tp>& __r){
        return __l.base() == __r.base();
    }
    template<typename _Tp>
    inline bool operator!=(const _list_iterator<_Tp>& __l, const _list_iterator<_Tp>& __r){
        return __l.base() != __r.base();
    }

    /// List_Base Implementation

    /// Allocate And Deallocate Memory
    /// But Don't Support Other Function
    template<typename _Tp, typename _Alloc>
    class _List_Base{
    protected:
        /// Protected Type Define
        typedef typename stl::__allocator_traits<_Alloc> allocator_traits_type;
        typedef typename stl::__allocator_traits<_Alloc>:: allocator_type allocator_type;
        typedef typename stl::__allocator_traits<_Alloc>:: template
        rebind_alloc<__std__::_list_node_<_Tp>> rebind_allocator_type;
        typedef __std__::_list_node_<_Tp> list_node_type;
        typedef __std__::_list_node_<_Tp> * list_node_ptr_type;
        typedef stl::size_t size_type;

    protected:
        /// Only Data Member Not A Pointer
        /**
         * Parameter :
         *           @ _M_Base_Node         :  end()
         *          @ _M_Base_Node._M_value : size
         *          @ _M_Base_Node._M_next  : begin()
         *          @ _M_Base_Node._M_prev  :  end() - 1
         */
        _list_node_<stl::size_t> _M_Base_Node;

        /// Inner Distance Function
        static stl::ptrdiff_t _M_distance(const _list_node_base* __first, const _list_node_base* __last) {
            stl::ptrdiff_t _diff = 0;
            while (__first != __last){
                __first = __first->_M_next;
                ++_diff;
            }
            return _diff;
        }
        rebind_allocator_type get_allocator() const {
            return rebind_allocator_type ();
        }

        size_type _M_get_size() const {  return this->_M_Base_Node.get_val(); }
        void _M_inc_size(size_type __n) {  (*this->_M_Base_Node.get_valptr()) += __n;  }
        void _M_dec_size(size_type __n) {  (*this->_M_Base_Node.get_valptr()) -= __n;  }
        void _M_set_size(size_type __n) {  (*this->_M_Base_Node.get_valptr()) = __n;  }

    public:
        _STL_USE_CONSTEXPR _List_Base() : _M_Base_Node() {  }
        ~_List_Base() = default;
    };
}
namespace stl{

    /// The Implementation Of stl::list
    template<typename _Tp, typename _Alloc = stl::default_allocator<_Tp>>
    class list : protected __std__::_List_Base<_Tp, _Alloc>{
    public:
        typedef typename __std__::_List_Base<_Tp, _Alloc>::allocator_type allocator_type;
        typedef typename __std__::_List_Base<_Tp, _Alloc>::rebind_allocator_type
        rebind_allocator_type;
        typedef typename __std__::_List_Base<_Tp, _Alloc>::allocator_traits_type
        allocator_traits_type;
        typedef typename __std__::_List_Base<_Tp, _Alloc>::rebind_allocator_type Node_allocator_type;
        typedef __std__::_list_node_base list_node_base_type;
        typedef __std__::_list_node_<_Tp> list_node_type;

        typedef _Tp                                                     value_type;
        typedef _Tp&                                                    reference;
        typedef const _Tp&                                              const_reference;
        typedef _Tp *                                                   pointer;
        typedef const _Tp *                                             const_pointer;
        typedef typename __std__::_List_Base<_Tp, _Alloc>::size_type    size_type;
        typedef stl::ptrdiff_t                                          difference_type;

        /// type Define For Iterator
        typedef __std__::_list_iterator<_Tp>                    iterator;
        typedef const __std__::_list_iterator<_Tp>              const_iterator;
        typedef stl::reverse_iterator<iterator>                 reverse_iterator;
        typedef stl::reverse_iterator<const_iterator>           const_reverse_iterator;

#ifdef USE_EXPLICIT_FUNC
        using __std__::_List_Base<_Tp, _Alloc>::get_allocator;
        using __std__::_List_Base<_Tp, _Alloc>::_M_set_size;
        using __std__::_List_Base<_Tp, _Alloc>::_M_get_size;
        using __std__::_List_Base<_Tp, _Alloc>::_M_dec_size;
        using __std__::_List_Base<_Tp, _Alloc>::_M_inc_size;
        using __std__::_List_Base<_Tp, _Alloc>::_M_distance;
#endif
    private:
        /// Construct and Allocate Memory
        list_node_type * _M_create_Node(const value_type& _Val);
        template<typename ..._Args>
        list_node_type * _M_create_Node(_Args&& ..._args);

        list_node_type * _M_malloc_Node();

        /// Destroy and Deallocate Memory
        void _M_destroy_Node(list_node_type * _Tar);
        void _M_free_Node(list_node_type * _Tar);
        void _M_empty_initialized();

        template<typename... _Args>
        iterator _M_insert(const_iterator __pos, _Args&&...__args);

        template<typename _InputIterator>
        void _M_Copy(_InputIterator __first, _InputIterator __last);

    public:
        /// Constructor
        list() _STL_NO_EXCEPTION {
            this->_M_empty_initialized();
        }
        list(const std::initializer_list<value_type>& _Li){
            this->_M_empty_initialized();
            this->template _M_Copy(_Li.begin(), _Li.end());
        }
        list(const list& _Other) {
            this->_M_empty_initialized();
            this->template _M_Copy(_Other.begin(), _Other.end());
        }

        /// Public Member Function
        size_type size() const _STL_NO_EXCEPTION;
        bool empty() const _STL_NO_EXCEPTION ;

        void display(bool flag = true) const _STL_NO_EXCEPTION;
        reference front() _STL_NO_EXCEPTION;
        reference back() _STL_NO_EXCEPTION;

        void push_back(const value_type& _val);
        void push_back(value_type&& _val);

        template<typename... _Args>
        void emplace_back(_Args&& ..._args);

        void push_front(const value_type& _val);
        void push_front(value_type&& _val);

        template<typename... _Args>
        void emplace_front(_Args&& ..._args);

        iterator insert(const_iterator _pos, const value_type& _val);
        iterator insert(const_iterator _pos, value_type&& _val);

        static iterator advance(iterator _Iter, difference_type _Diff);

        /// Iterator Function
        iterator begin() {  return iterator (this->_M_Base_Node._M_next);  }
        iterator end()  {  return iterator (&this->_M_Base_Node);  }

        const_iterator begin() const {  return const_iterator (this->_M_Base_Node._M_next); }
        const_iterator end() const {  return const_iterator (&this->_M_Base_Node); }

        const_iterator cbegin() const {  return const_iterator (this->_M_Base_Node._M_next); }
        const_iterator cend() const {  return const_iterator (&this->_M_Base_Node); }

        reverse_iterator rbegin() {  return reverse_iterator (this->end()); }
        reverse_iterator rend()  {  return reverse_iterator (this->begin());  }

        const_reverse_iterator rbegin() const {  return const_reverse_iterator (this->end()); }
        const_reverse_iterator rend() const {  return const_reverse_iterator (this->begin()); }

        const_reverse_iterator crbegin() const {  return const_reverse_iterator (this->end()); }
        const_reverse_iterator crend() const {  return const_reverse_iterator (this->begin()); }
    };

    /// Functions' Implementation

    template<typename _Tp, typename _Alloc>
    void list<_Tp,  _Alloc>::_M_destroy_Node(list_node_type *_Tar){
        /// Note : Just Destroy pointer's object
        stl::_Destroy(_Tar->get_valptr());
        this->_M_free_Node(_Tar);
    }
    template<typename _Tp, typename _Alloc>
    void list<_Tp,  _Alloc>::_M_free_Node(list_node_type *_Tar) {
        this->get_allocator().deallocate(_Tar);
    }
    template<typename _Tp, typename _Alloc>
    typename list<_Tp,  _Alloc>::list_node_type * list<_Tp,  _Alloc>::_M_create_Node(const value_type &_Val) {
        list_node_type * __temp = this->_M_malloc_Node();
        stl::_Construct(__temp->get_valptr(), _Val);
        return __temp;
    }
    template<typename _Tp, typename _Alloc>
    template<typename ..._Args>
    typename list<_Tp,  _Alloc>::list_node_type * list<_Tp,  _Alloc>::_M_create_Node(_Args&&..._args) {
        list_node_type * __temp = this->_M_malloc_Node();
        stl::_Construct(__temp->get_valptr(), std::forward<_Args>(_args)...);
        return __temp;
    }
    template<typename _Tp, typename _Alloc>
    typename list<_Tp,  _Alloc>::list_node_type * list<_Tp,  _Alloc>::_M_malloc_Node() {
        return this->get_allocator().allocate(1);
    }
    template<typename _Tp, typename _Alloc>
    void list<_Tp,  _Alloc>::_M_empty_initialized() {
        this->_M_Base_Node._M_next = &this->_M_Base_Node;
        this->_M_Base_Node._M_prev = &this->_M_Base_Node;
        this->_M_set_size(0);
    }
    template<typename _Tp, typename _Alloc>
    typename list<_Tp,  _Alloc>::size_type list<_Tp,  _Alloc>::
            size() const _STL_NO_EXCEPTION{
        return this->_M_get_size();
    }
    template<typename _Tp, typename _Alloc>
    bool list<_Tp,  _Alloc>::empty() const _STL_NO_EXCEPTION {
        return (this->size() == 0);
    }

    template<typename _Tp, typename _Alloc>
    typename list<_Tp,  _Alloc>::reference list<_Tp,  _Alloc>::front() noexcept {
        return *(this->begin());
    }
    template<typename _Tp, typename _Alloc>
    typename list<_Tp,  _Alloc>::reference list<_Tp,  _Alloc>::back() noexcept {
        iterator _End_temp = this->end();
        --_End_temp;
        return *(_End_temp);
    }
    template<typename _Tp, typename _Alloc>
    void list<_Tp,  _Alloc>::display(bool flag) const noexcept {
        for (iterator _Iter = this->begin()._M_const_cast(); _Iter != this->end(); ++_Iter)
            std::cout<<*_Iter<<" ";
        std::cout<<std::endl;
        if (flag)
            std::cout<<"Size : "<< this->size()<<std::endl;
        std::cout<<std::endl;
    }
    template<typename _Tp, typename _Alloc>
    void list<_Tp,  _Alloc>::push_back(const value_type &_val) {
        this->template _M_insert(this->end(), _val);
    }
    template<typename _Tp, typename _Alloc>
    void list<_Tp,  _Alloc>::push_back(value_type &&_val) {
        this->template _M_insert(this->end(), std::move(_val));
    }
    template<typename _Tp, typename _Alloc>
    template<typename ..._Args>
    void list<_Tp,  _Alloc>::emplace_back(_Args &&..._args) {
        this->template _M_insert(this->end(), std::forward<_Args>(_args)...);
    }
    template<typename _Tp, typename _Alloc>
    void list<_Tp,  _Alloc>::push_front(const value_type &_val) {
        this->template _M_insert(this->begin(), _val);
    }
    template<typename _Tp, typename _Alloc>
    void list<_Tp,  _Alloc>::push_front(value_type &&_val) {
        this->template _M_insert(this->begin(), std::move(_val));
    }
    template<typename _Tp, typename _Alloc>
    template<typename ..._Args>
    void list<_Tp,  _Alloc>::emplace_front(_Args &&..._args) {
        this->template _M_insert(this->begin(), std::forward<_Args>(_args)...);
    }
    template<typename _Tp, typename _Alloc>
    template<typename ..._Args>
    typename list<_Tp,  _Alloc>::iterator list<_Tp,  _Alloc>::_M_insert(const_iterator __pos, _Args&&...__args) {
        list_node_type * __temp = this->template _M_create_Node(std::forward<_Args>(__args)...);
        __temp->_M_prev = __pos.base()->_M_prev;
        __temp->_M_next = __pos.base();
        __temp->_M_prev->_M_next = __temp;
        __pos.base()->_M_prev = __temp;
        /// Increase Size
        this->_M_inc_size(1);
        return iterator (__temp);
    }
    template<typename _Tp, typename _Alloc>
    typename list<_Tp,  _Alloc>::iterator list<_Tp,  _Alloc>::insert(const_iterator _pos, value_type &&_val) {
        this->template _M_insert(_pos, std::move(_val));
    }
    template<typename _Tp, typename _Alloc>
    typename list<_Tp,  _Alloc>::iterator list<_Tp,  _Alloc>::insert(const_iterator _pos, const value_type &_val) {
        this->template _M_insert(_pos, _val);
    }
    /// A More Convenient OverRide Advanced Function With An Return Type !
    /// A Specialization For typename list<_Tp,  _Alloc>::iterator
    template<typename _Tp, typename _Alloc>
    typename list<_Tp,  _Alloc>::iterator list<_Tp,  _Alloc>::advance(iterator _Iter, difference_type _Diff) {
        /// Invoke Standard Advance
        typename list<_Tp,  _Alloc>::iterator __temp = _Iter;
        stl::advance(__temp, _Diff);
        return __temp;
    }
    template<typename _Tp, typename _Alloc>
    template<typename _InputIterator>
    void list<_Tp, _Alloc>::_M_Copy(_InputIterator __first, _InputIterator __last){
        for ( ; __first != __last ; ++__first){
            this->template _M_insert(this->end(), *__first);
        }
    }
}
#endif //STL2_0_STL_LIST_H
