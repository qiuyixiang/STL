//
// Created by 11508 on 2023-07-07.
//

#ifndef STL2_0_STL_DEQUE_H
#define STL2_0_STL_DEQUE_H

#include "../allocator/allocator_traits.h"
#include "../util/ctt.h"
#include "../util/utility.h"
#include "../iterator/iterator_traits.h"

/// Achievement of STL::deque (std::deque)
/// stl::deque on 2023-7-7
/// Double Ended Queue belong to Sequence Container !


/**
 * This Container Is Used As Double Ended Queue
 * It's Liner In Logical !
 * Advanced Sequence stl::deque !
 *
 * Fist Version Finished on : 2023-7-11
 *
 * Small Patch 0.1: Copy And Move Constructor,
 *              Assignment And Operator==
 *              Finished On 2023-7-12
 */

///#define DEQUE_DESTROY_DEBUGGER
namespace __std__{


    /// Implementation of __std__::_Deque_Base
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    class _Deque_Base {

    protected:
        /// Just Type Define
        /// Without Constructor And Destructor To Simply Layer

        typedef _Tp** _buffer_map_pointer;
        typedef _Tp* _buffer_map_type;
        typedef _Alloc allocator_type;
        typedef stl::__allocator_traits<_Alloc> allocator_traits_type;

        typedef typename stl::__allocator_traits<_Alloc>::template rebind_alloc<_Tp> _Rebind_Tp_type;
        typedef typename stl::__allocator_traits<_Alloc>::template
                rebind_alloc<_buffer_map_type> _Rebind_buffer_node_type;

        _Rebind_Tp_type get_Tp_type_allocator();
        const _Rebind_Tp_type get_Tp_type_allocator() const;

        _Rebind_buffer_node_type get_node_type_allocator();
        const _Rebind_buffer_node_type get_node_type_allocator() const;
    };
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    typename _Deque_Base<_Tp, _Alloc, _BufferSize>::_Rebind_Tp_type
    _Deque_Base<_Tp, _Alloc, _BufferSize>::get_Tp_type_allocator() {
        return _Rebind_Tp_type ();
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    const typename _Deque_Base<_Tp, _Alloc, _BufferSize>::_Rebind_Tp_type
    _Deque_Base<_Tp, _Alloc, _BufferSize>::get_Tp_type_allocator() const {
        return _Rebind_Tp_type ();
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    typename _Deque_Base<_Tp, _Alloc, _BufferSize>::_Rebind_buffer_node_type
    _Deque_Base<_Tp, _Alloc, _BufferSize>::get_node_type_allocator() {
        return _Rebind_buffer_node_type ();
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    const typename _Deque_Base<_Tp, _Alloc, _BufferSize>::_Rebind_buffer_node_type
    _Deque_Base<_Tp, _Alloc, _BufferSize>::get_node_type_allocator() const {
        return _Rebind_buffer_node_type ();
    }

    inline stl::size_t __deque_buffer_size(stl::size_t __buffer, stl::size_t __size);

    /// Implementation of __std__::_deque_iterator
    template<typename _Tp, stl::size_t _BufferSize>
    class _deque_iterator{
            /**
             * Notes :
             *    This Iterator For Deque is Very Complicated Because
             *    Of Deque's unlimited Memory Management
             *    This Allows Iterator Jumps From One Node To The Other by Itself !
             *    So This Class Supports Many Private Auxiliary Function !
             */
    public:
            typedef _deque_iterator<_Tp, _BufferSize> iterator;
            typedef const _deque_iterator<_Tp, _BufferSize> const_iterator;
            /// Essential Iterator Attribute !
            typedef stl::random_access_iterator_tag iterator_category;
            typedef _Tp value_type;
            typedef _Tp* pointer;
            typedef _Tp& reference;
            typedef stl::ptrdiff_t difference_type;
    public:
            typedef _Tp** _buffer_map_pointer;
            typedef _Tp* _buffer_map_type;
            typedef _deque_iterator self;

            /// Member Data
            pointer __current;
            pointer __fist;
            pointer __last;
            _buffer_map_pointer __node;
    public:
            static stl::size_t buffer_size() {  return __deque_buffer_size(_BufferSize, sizeof(_Tp)); }
            /// Set One Node But Do not Change __current !
            void set_node(_buffer_map_pointer __new_node){
                this->__node = __new_node;
                this->__fist = *__new_node;
                this->__last = this->__fist + difference_type (buffer_size());
            }
            void set_mem_null(){
                this->__current = nullptr;
                this->__node = nullptr;
                this->__fist = nullptr;
                this->__last = nullptr;
            }
    public:
            /// Public Member Function

            /// Constructor
            _STL_USE_CONSTEXPR _deque_iterator() _STL_NO_EXCEPTION : __current(nullptr), __fist(nullptr),
            __node(nullptr), __last(nullptr){  };
            ~_deque_iterator() {  }
            _STL_USE_CONSTEXPR _deque_iterator(const _deque_iterator<_Tp, _BufferSize>& _other) :
            __current(_other.__current), __fist(_other.__fist), __node(_other.__node), __last(_other.__last) {  };

            reference operator*() const {  return *__current;  }
            pointer operator->() const {  return &(operator*()); }
            /// Relevant Addition Operation
            self & operator++() {
                this->__current++;
                if (this->__current == this->__last){
                    set_node(this->__node + 1);
                    this->__current = this->__fist;
                }
                return *this;
            }
            self operator++(int){
                self __temp = *this;
                ++(*this);
                return __temp;
            }
            self & operator+=(difference_type __n){
                /**
                 *   Move From First (__first) Perspective Because The Jump Gap From One
                 * Node To The Other Is Buffer Size. And The Last Operation is __first +
                 * (total_offset % buffer_size)
                 */
                difference_type __offset = __n + (__current - __fist), __node_offset;
                if (__offset >= 0 && __offset < difference_type(buffer_size()))
                    __current += __n;
                else{
                    if (__offset > 0){
                        /// Use __first as flag
                        __node_offset = __offset / difference_type(buffer_size());
                        set_node(__node + __node_offset);
                        __current = __fist + __offset % difference_type(buffer_size());
                    } else{
                        /// Use __last as flag
                        __node_offset = __offset / difference_type(buffer_size()) - 1;
                        set_node(__node + __node_offset);
                        __current = __last + __offset % difference_type(buffer_size());
                    }
                }
            }
            self operator+(difference_type __n){
                self __temp = *this;
                __temp += __n;
                return __temp;
            }
            /// Relevant Subtraction Operation
            self & operator--(){
                if (this->__current == this->__fist){
                    set_node(this->__node - 1);
                    this->__current = this->__last;
                }
                --this->__current;
                return *this;
            }
            self operator--(int){
                self __temp = *this;
                --(*this);
                return __temp;
            }
            difference_type operator-(const self& __other) const {
                return difference_type (
                        difference_type (__node - __other.__node - 1) * difference_type(buffer_size()) +
                                (__other.__last - __other.__current) + (__current - __fist)
                        );
            }
            self operator-=(difference_type __n){
                return *this += -__n;
            }
            self operator-(difference_type __n){
                self __temp = *this;
                __temp -= __n;
                return __temp;
            }

            reference operator[](difference_type __n)  {
                return *(*this + __n);
            }
            self & operator=(const _deque_iterator<_Tp, _BufferSize>& __other) {
                if (this != &__other){
                    this->__current = __other.__current;
                    this->__node = __other.__node;
                    this->__fist = __other.__fist;
                    this->__last = __other.__last;
                }
            }
            bool operator==(const self& __other) const {  return this->__current == __other.__current; }
            bool operator!=(const self& __other) const {  return !(*this == __other); }
            bool operator<(const self& __other) const {
                return (__node == __other.__node) ? (__current < __other.__current) : (__node < __other.__node);
            }
            bool operator>(const self& __other) const {
                return (__node == __other.__node) ? (__current > __other.__current) : (__node > __other.__node);
            }
            bool operator<=(const self& __other) const {  return !(*this > __other); }
            bool operator>=(const self& __other) const {  return !(*this < __other);  }

            /// Constructor
    };

    template<typename _Tp, stl::size_t _BufferSize>
    inline bool operator==(const _deque_iterator<_Tp, _BufferSize>& __x ,
            const _deque_iterator<_Tp, _BufferSize>& __y){
        return __x.operator==(__y);
    }
    template<typename _Tp, stl::size_t _BufferSize>
    inline bool operator!=(const _deque_iterator<_Tp, _BufferSize>& __x ,
                           const _deque_iterator<_Tp, _BufferSize>& __y){
        return __x.operator!=(__y);
    }
    template<typename _Tp, stl::size_t _BufferSize>
    inline bool operator>(const _deque_iterator<_Tp, _BufferSize>& __x ,
                           const _deque_iterator<_Tp, _BufferSize>& __y){
        return __x.operator>(__y);
    }
    template<typename _Tp, stl::size_t _BufferSize>
    inline bool operator<(const _deque_iterator<_Tp, _BufferSize>& __x ,
                           const _deque_iterator<_Tp, _BufferSize>& __y){
        return __x.operator<(__y);
    }
    template<typename _Tp, stl::size_t _BufferSize>
    inline bool operator>=(const _deque_iterator<_Tp, _BufferSize>& __x ,
                           const _deque_iterator<_Tp, _BufferSize>& __y){
        return __x.operator>=(__y);
    }
    template<typename _Tp, stl::size_t _BufferSize>
    inline bool operator<=(const _deque_iterator<_Tp, _BufferSize>& __x ,
                           const _deque_iterator<_Tp, _BufferSize>& __y){
        return __x.operator<=(__y);
    }
    /// Global Function For Deque And Deque's Iterator
    /// __buffer : User's appointment for buffer size (size for index)
    /// __size : size of value (_Tp) (byte !)
    inline stl::size_t __deque_buffer_size(stl::size_t __buffer, stl::size_t __size){
        return __buffer != 0 ? __buffer : (__size < 512 ? stl::size_t(512 / __size) : stl::size_t(1));
    }
}

namespace stl{

#define INITIAL_BUFFER_SIZE 8

    /// Implementation of stl::deque
    /// Depends on __std__::_Deque_Base
    template<typename _Tp, typename _Alloc = stl::default_allocator<int>, stl::size_t _BufferSize = 0>
    class deque : protected __std__::_Deque_Base<_Tp, _Alloc, _BufferSize>{
    protected:
        /// Internal Type Define
        typedef __std__::_Deque_Base<_Tp, _Alloc, _BufferSize> _Base;
        typedef typename _Base::_buffer_map_type _buffer_map_type;
        typedef typename _Base::_buffer_map_pointer _buffer_map_pointer;

        typedef typename _Base::_Rebind_Tp_type rebind_Tp_type;
        typedef typename _Base::_Rebind_buffer_node_type rebind_buffer_node_type;
    public:
        typedef typename _Base::allocator_type allocator_type;
        typedef typename _Base::allocator_traits_type allocator_traits_type;
        typedef _Tp                                       value_type;
        typedef _Tp&                                      reference;
        typedef const _Tp&                                const_reference;
        typedef _Tp *                                     pointer;
        typedef const _Tp *                               const_pointer;
        typedef stl::ptrdiff_t                            difference_type;
        typedef stl::size_t                               size_type;

        typedef __std__::_deque_iterator<_Tp, _BufferSize> iterator;
        typedef const __std__::_deque_iterator<_Tp, _BufferSize> const_iterator;
        typedef stl::reverse_iterator<iterator>       reverse_iterator;
        typedef stl::reverse_iterator<const_iterator> const_reverse_iterator;
    private:
        /// Data Member !
        _buffer_map_pointer _M_buffer_map;
        stl::size_t _M_buffer_size;

        iterator _M_start;
        iterator _M_finish;
    private:
        /// Inner Auxiliary Function
        void _M_create_map_buffer(size_type __element_size);
        void _M_fill_initialized(size_type __n, const value_type& __val);
        template<typename ForwardIterator>
        void _M_copy_initialized(ForwardIterator __First, ForwardIterator __Last);

        /// Just Reverse Memory For Map Buffer But Don't Allocate Memory For _Tp Node !
        void _M_reserve_node_back(size_type __node_to_add = 1);
        void _M_reserve_node_front(size_type __node_to_add = 1);

        template<typename ..._Args>
        void _M_emplace_back_auxiliary(_Args&&...__val);
        template<typename ..._Args>
        void _M_emplace_front_auxiliary(_Args&&...__val);

        void _M_reallocate_map(size_type __node_to_add, bool __add_at_front);
        inline _buffer_map_type _M_allocate_Node();
        inline void _M_deallocate_Node(_buffer_map_type __ptr);

        void _M_pop_back_auxiliary();
        void _M_pop_front_auxiliary();
        void _M_clear_and_reserve_one();

        iterator _M_erase_auxiliary(iterator __first, iterator __last);
        template<typename ...Args>
        iterator _M_insert_auxiliary(iterator __position, Args&&...args);

    public:
        /// Public Member Function

        /// Constructor And Destructor
        deque() _STL_NO_EXCEPTION : _M_buffer_map(nullptr), _M_buffer_size(0),
        _M_finish(), _M_start() {
            this->_M_fill_initialized(0, value_type{ });
        }

        deque(size_type n, const value_type& value) : _M_buffer_map(nullptr), _M_buffer_size(0),
        _M_finish(), _M_start()
        { this->_M_fill_initialized(n, value);  }

        deque(std::initializer_list<value_type> _l) : deque() {
            this->template _M_copy_initialized(_l.begin(), _l.end());
        }
        /// Destroy Deque Completely !
        ~deque() {
            /// Delete All Buffer Node
            if (!this->empty())
                this->_M_clear_and_reserve_one();
            if (this->_M_start.__fist != nullptr && this->_M_buffer_map != nullptr){
                this->_M_deallocate_Node(this->_M_start.__fist);
                /// Delete All Buffer
                this->get_node_type_allocator().deallocate(this->_M_buffer_map, this->_M_buffer_size);
            } else{
#ifdef DEQUE_DESTROY_DEBUGGER
                std::cout<<"Doing Nothing !"<<std::endl;
#endif
            }
        }

        /// Copy And Move Constructor
        deque(const deque<_Tp, _Alloc, _BufferSize>& __other) : _M_buffer_map(nullptr), _M_buffer_size(0),
        _M_finish(), _M_start() {
            this->template _M_copy_initialized(__other.begin(), __other.end());
        }

        deque(deque&& __other);

        /// Copy And Move Assignment Operator
        deque& operator=(const deque<_Tp, _Alloc, _BufferSize>& __other);
        deque& operator=(deque<_Tp, _Alloc, _BufferSize>&& __other);

        /// Begin()  End()
        iterator begin() _STL_NO_EXCEPTION {  return this->_M_start; }
        const_iterator begin() const _STL_NO_EXCEPTION {  return this->_M_start; }
        const_iterator cbegin() const _STL_NO_EXCEPTION {  return this->_M_start; }

        reverse_iterator rbegin() _STL_NO_EXCEPTION {  return reverse_iterator (this->_M_finish); }
        const_reverse_iterator rbegin() const _STL_NO_EXCEPTION { return const_reverse_iterator (this->_M_finish); }
        const_reverse_iterator crbegin() const _STL_NO_EXCEPTION { return const_reverse_iterator (this->_M_finish); }

        iterator end() _STL_NO_EXCEPTION {  return this->_M_finish; }
        const_iterator end() const _STL_NO_EXCEPTION {  return this->_M_finish; }
        const_iterator cend() const _STL_NO_EXCEPTION {  return this->_M_finish; }

        reverse_iterator rend() _STL_NO_EXCEPTION {  return reverse_iterator (this->_M_start); }
        const_reverse_iterator rend() const _STL_NO_EXCEPTION { return const_reverse_iterator (this->_M_start); }
        const_reverse_iterator crend() const _STL_NO_EXCEPTION { return const_reverse_iterator (this->_M_start); }

        size_type size() const _STL_NO_EXCEPTION {  return size_type (this->_M_finish - this->_M_start); }
        size_type max_size() const _STL_NO_EXCEPTION {  return this->get_Tp_type_allocator().max_size(); }
        bool empty() const _STL_NO_EXCEPTION {  return this->_M_start == this->_M_finish; }

        reference operator[](difference_type __n) { return this->_M_start[__n];  }
        reference front();
        reference back();

        void display(bool debug = false) const;

        void push_back(value_type&& value);
        void push_back(const value_type& value);

        template<typename... Args>
        void emplace_back(Args&&...args);

        void push_front(value_type&& value);
        void push_front(const value_type& value);

        template<typename... Args>
        void emplace_front(Args&&...args);

        void pop_back();
        void pop_front();
        void clear();

        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);

        iterator insert(iterator position, const value_type& value);
        iterator insert(iterator position, value_type&& value);
        template<typename ...Args>
        iterator emplace(iterator position, Args&&...args);
    };

    /// The Achievement OF Deque's Member Function
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    typename deque<_Tp, _Alloc, _BufferSize>::
    reference deque<_Tp, _Alloc, _BufferSize>::front() {
        return *(this->_M_start);
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    typename deque<_Tp, _Alloc, _BufferSize>::
    reference deque<_Tp, _Alloc, _BufferSize>::back() {
        iterator __temp = this->_M_finish;
        --__temp;
        return *__temp;
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::display(bool debug) const {
        for (__std__::_deque_iterator<_Tp, _BufferSize> __iter = this->begin(); __iter != this->end(); ++__iter)
            std::cout<<*__iter<<" ";
        std::cout<<std::endl;
        if (debug){
            std::cout<<"Container Size : "<< this->size()<<std::endl;
            std::cout<<"Map Node Size : "<< this->_M_buffer_size<<std::endl;
            std::cout<<"Size Of Buffer : "<<__std__::_deque_iterator<_Tp, _BufferSize>::buffer_size()<<std::endl;
            std::cout<<std::endl;
        }
    }
    /// Allocate Memory For Map Buffer And Allocate Memory For Each Node (Every Needed Node )
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::_M_create_map_buffer(size_type __element_size) {
        /// Buffer Size
        size_type __buffer_size = __element_size / __std__::_deque_iterator<_Tp, _BufferSize>::buffer_size() + 1;
        this->_M_buffer_size = stl::max(static_cast<int>(__buffer_size), INITIAL_BUFFER_SIZE);
        this->_M_buffer_map = this->get_node_type_allocator().allocate(this->_M_buffer_size);
        /// Keep n_start and n_finish in the middle of buffer
        _buffer_map_pointer n_start = this->_M_buffer_map + (this->_M_buffer_size - __buffer_size) / 2;
        _buffer_map_pointer n_finish = n_start + __buffer_size - 1;
        /// [n_start, n_finish] is a range that contains have already allocated memory !
        _buffer_map_pointer __current;
        /// Allocate Memory For Buffer Node
        try {
            for (__current = n_start; __current <= n_finish; ++__current)
                *__current = this->get_Tp_type_allocator().
                        allocate(__std__::_deque_iterator<_Tp, _BufferSize>::buffer_size());
        } catch (...) {
            _buffer_map_pointer __del;
            for (__del = n_start; __del <= __current; ++__del)
                this->get_Tp_type_allocator().deallocate(*__del,
                      __std__::_deque_iterator<_Tp, _BufferSize>::buffer_size());
            throw ;
        }
        this->_M_start.set_node(n_start);
        this->_M_finish.set_node(n_finish);

        this->_M_start.__current = this->_M_start.__fist;
        this->_M_finish.__current = this->_M_finish.__fist + __element_size %
                __std__::_deque_iterator<_Tp, _BufferSize>::buffer_size();
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::_M_fill_initialized(size_type __n, const value_type &__val) {
        this->_M_create_map_buffer(__n);
        _buffer_map_pointer __current;
        for (__current = this->_M_start.__node; __current < this->_M_finish.__node; ++__current)
            stl::uninitialized_fill(*__current, *__current +
            __std__::_deque_iterator<_Tp, _BufferSize>::buffer_size(), __val);
        stl::uninitialized_fill(this->_M_finish.__fist, this->_M_finish.__current, __val);
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    template<typename ForwardIterator>
    void deque<_Tp, _Alloc,  _BufferSize>::_M_copy_initialized(ForwardIterator __First, ForwardIterator __Last) {
        difference_type __dif = stl::distance(__First, __Last);
        this->_M_create_map_buffer(__dif);
        auto __current = __First;
        _buffer_map_pointer __node_current;
        for (__node_current = this->_M_start.__node;
        __node_current < this->_M_finish.__node; ++__node_current){
            stl::advance(__current, __std__::_deque_iterator<_Tp, _BufferSize>::buffer_size());
            stl::uninitialized_copy(__First, __current, *__node_current);
            __First = __current;
        }
        stl::uninitialized_copy(__current, __Last, this->_M_finish.__fist);
    }
    /// Push Back Implementation
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::push_back(value_type &&value) {
        this->template emplace_back(std::move(value));
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::push_back(const value_type &value) {
        if (this->_M_finish.__current != this->_M_finish.__last - 1){
            stl::_Construct(this->_M_finish.__current, value);
            ++this->_M_finish.__current;
        } else
            this->template _M_emplace_back_auxiliary(value);
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    template<typename ...Args>
    void deque<_Tp, _Alloc,  _BufferSize>::emplace_back(Args&&...args) {
        if (this->_M_finish.__current != this->_M_finish.__last - 1){
            stl::_Construct(this->_M_finish.__current, std::forward<Args>(args)...);
            ++this->_M_finish.__current;
        } else
            this->template _M_emplace_back_auxiliary(std::forward<Args>(args)...);
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::_M_reserve_node_back(size_type __node_to_add) {
        if (__node_to_add > (this->_M_buffer_size - (this->_M_finish.__node - this->_M_buffer_map) - 1))
            this->_M_reallocate_map(__node_to_add, false);
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    template<typename ...Args>
    void deque<_Tp, _Alloc,  _BufferSize>::_M_emplace_back_auxiliary(Args &&...__val) {
        /// Reverse One Node At Back!
        this->_M_reserve_node_back();
        *(this->_M_finish.__node + 1) = this->_M_allocate_Node();
        try {
            stl::_Construct(this->_M_finish.__current, std::forward<Args>(__val)...);
            this->_M_finish.set_node(this->_M_finish.__node + 1);
            this->_M_finish.__current = this->_M_finish.__fist;
        } catch (...) {
            /// Catch Exception Deallocate New Allocated Memory !
            this->_M_deallocate_Node(*(this->_M_finish.__node + 1));
            throw ;
        }
    }
    /// Push Front Implementation
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::push_front(value_type &&value) {
        this->template emplace_front(std::move(value));
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::push_front(const value_type &value) {
        if (this->_M_start.__current != this->_M_start.__fist){
            stl::_Construct(this->_M_start.__current - 1, value);
            --this->_M_start.__current;
        } else
            this->template _M_emplace_front_auxiliary(value);
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    template<typename ...Args>
    void deque<_Tp, _Alloc,  _BufferSize>::emplace_front(Args&&...args) {
        if (this->_M_start.__current != this->_M_start.__fist){
            stl::_Construct(this->_M_start.__current - 1, std::forward<Args>(args)...);
            --this->_M_start.__current;
        } else
            this->template _M_emplace_front_auxiliary(std::forward<Args>(args)...);
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::_M_reserve_node_front(size_type __node_to_add) {
        if (__node_to_add > this->_M_start.__node - this->_M_buffer_map)
            this->_M_reallocate_map(__node_to_add, true);
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    template<typename ...Args>
    void deque<_Tp, _Alloc,  _BufferSize>::_M_emplace_front_auxiliary(Args &&...__val) {
        /// Reverse One Node At Front!
        this->_M_reserve_node_front();
        *(this->_M_start.__node - 1) = this->_M_allocate_Node();
        try {
            this->_M_start.set_node(this->_M_start.__node - 1);
            this->_M_start.__current = this->_M_start.__last - 1;
            stl::_Construct(this->_M_start.__current, std::forward<Args>(__val)...);
        }catch (...){
            this->_M_start.set_node(this->_M_start.__node + 1);
            this->_M_start.__current = this->_M_start.__fist;
            this->_M_deallocate_Node(*(this->_M_start.__node - 1));
            throw ;
        }
    }
    /// Other Auxiliary Function
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::
    _M_reallocate_map(size_type __node_to_add, bool __add_at_front) {
        /// Calculate Buffer Size
        const size_type __old_num_nodes = this->_M_finish.__node - this->_M_start.__node + 1;
        const size_type __new_num_nodes = __old_num_nodes + __node_to_add;

        _buffer_map_pointer __new_start;
        /// Still Have Adequate Memory And Both Sides Asymmetric !
        if (this->_M_buffer_size > 2 * __new_num_nodes){
            __new_start = this->_M_buffer_map + (this->_M_buffer_size - __new_num_nodes) / 2 +
                    (__add_at_front ? __node_to_add : 0);
            if (__new_start < this->_M_start.__node)
                std::copy(this->_M_start.__node, this->_M_finish.__node + 1, __new_start);
            else
                std::copy_backward(this->_M_start.__node, this->_M_finish.__node + 1,
                                   __new_start + __old_num_nodes);
        } else{
            const size_type __new_map_size = this->_M_buffer_size + stl::max(this->_M_buffer_size, __node_to_add) + 2;
            _buffer_map_pointer __new_map = this->get_node_type_allocator().allocate(__new_map_size);
            __new_start = __new_map + (__new_map_size - __new_num_nodes) / 2 + (__add_at_front ? __node_to_add : 0);
            /// Copy Old Buffer Memory
            std::copy(this->_M_start.__node, this->_M_finish.__node + 1, __new_start);
            this->_M_buffer_map = __new_map;
            this->_M_buffer_size = __new_map_size;
        }
        this->_M_start.set_node(__new_start);
        this->_M_finish.set_node(__new_start + __old_num_nodes - 1);
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    typename deque<_Tp, _Alloc,  _BufferSize>:: _buffer_map_type
    deque<_Tp, _Alloc,  _BufferSize>::_M_allocate_Node() {
        return this->get_Tp_type_allocator().allocate
        (__std__::_deque_iterator<_Tp, _BufferSize>::buffer_size());
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::_M_deallocate_Node(_buffer_map_type __ptr) {
        this->get_Tp_type_allocator().deallocate
        (__ptr, __std__::_deque_iterator<_Tp, _BufferSize>::buffer_size());
    }
    /// Pop Function Implementation
    /// The Standard Of Invoking __auxiliary is whether The Node Can Deallocate
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::pop_back() {
        if (this->_M_finish.__current != this->_M_finish.__fist){
            --this->_M_finish.__current;
            stl::_Destroy(this->_M_finish.__current);
            ///if (this->_M_finish.__current == this->_M_finish.__fist)
            /// NO Element At This Node Buffer Just As A End Flag !
        } else
            this->_M_pop_back_auxiliary();
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::_M_pop_back_auxiliary() {
        this->_M_deallocate_Node(this->_M_finish.__fist);
        this->_M_finish.set_node(this->_M_finish.__node - 1);
        this->_M_finish.__current = this->_M_finish.__last - 1;
        stl::_Destroy(this->_M_finish.__current);
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::pop_front() {
        if (this->_M_start.__current != this->_M_start.__last - 1){
            stl::_Destroy(this->_M_start.__current);
            ++this->_M_start.__current;
            /// The Last One Of Element At The Node !
        } else
            this->_M_pop_front_auxiliary();
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::_M_pop_front_auxiliary() {
        stl::_Destroy(this->_M_start.__current);
        this->_M_deallocate_Node(this->_M_start.__fist);
        this->_M_start.set_node(this->_M_start.__node + 1);
        this->_M_start.__current = this->_M_start.__fist;
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::clear() {
        this->_M_clear_and_reserve_one();
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    void deque<_Tp, _Alloc,  _BufferSize>::_M_clear_and_reserve_one() {
        /// Clear Buffer But Reverse One Buffer Node As Original !

        /// Clear All Filled Buffer
        for (_buffer_map_pointer __Del = this->_M_start.__node + 1 ;
        __Del < this->_M_finish.__node; ++__Del){
            stl::_Destroy(*__Del, *__Del + __std__::_deque_iterator<_Tp, _BufferSize>::buffer_size());
            this->_M_deallocate_Node(*__Del);
        }
        /// Clear The Rest (Head And Tail)
        /// First Node != Last Node
        if (this->_M_start.__node != this->_M_finish.__node){
            stl::_Destroy(this->_M_start.__current, this->_M_start.__last);
            stl::_Destroy(this->_M_finish.__fist, this->_M_finish.__current);
            /// Reverse First Node As Buffer Node !
            this->_M_deallocate_Node(this->_M_finish.__fist);
        } else{
            /// First Node And Last Node in Same Buffer !
            stl::_Destroy(this->_M_start.__current, this->_M_finish.__current);
        }
        this->_M_finish = this->_M_start;
    }
    /// Consider Deque As A Liner Sequence !
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    typename deque<_Tp, _Alloc,  _BufferSize>::iterator
    deque<_Tp, _Alloc,  _BufferSize>::erase(iterator position) {
        iterator __erase_after = position;
        ++__erase_after;
        difference_type __diff_front = position - this->_M_start;
        /// this->size() >> 1  =  this->size() / 2
        if (__diff_front < (this->size() >> 1) ){
            std::copy_backward(this->_M_start, position, __erase_after);
            /// Pop Spare Element !
            this->pop_front();
        } else{
            std::copy(__erase_after, this->_M_finish, position);
            /// Pop Spare Element !
            this->pop_back();
        }
        return iterator(this->_M_start + __diff_front);
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    typename deque<_Tp, _Alloc,  _BufferSize>::iterator
    deque<_Tp, _Alloc,  _BufferSize>::erase(iterator first, iterator last) {
        if (first == this->_M_start && last == this->_M_finish) {
            this->clear();
            return this->_M_finish;
        }
        else
            return this->_M_erase_auxiliary(first, last);
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    typename deque<_Tp, _Alloc,  _BufferSize>::iterator
    deque<_Tp, _Alloc,  _BufferSize>::_M_erase_auxiliary(iterator __first, iterator __last) {
        difference_type __n = __last - __first;
        difference_type __elems_front = __first - this->_M_start;
        difference_type __elems_back = this->_M_finish - __last;
        if (__elems_front < __elems_back){
            std::copy_backward(this->_M_start, __first, __last);
            iterator __new_start = this->_M_start + __n;
            stl::_Destroy(this->_M_start, __new_start);
            for (_buffer_map_pointer __cur = this->_M_start.__node; __cur < __new_start.__node; ++ __cur)
                this->_M_deallocate_Node(*__cur);
            this->_M_start = __new_start;
        } else{
            std::copy(__last, this->_M_finish, __first);
            iterator __new_finish = this->_M_finish - __n;
            stl::_Destroy(__new_finish, this->_M_finish);
            for (_buffer_map_pointer __cur = __new_finish.__node + 1; __cur <= this->_M_finish.__node; ++__cur)
                this->_M_deallocate_Node(*__cur);
            this->_M_finish = __new_finish;
        }
        return this->_M_start + __elems_front;
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    typename deque<_Tp, _Alloc,  _BufferSize>::iterator
    deque<_Tp, _Alloc,  _BufferSize>::insert(iterator position, const value_type &value) {
        if (position.__current == this->_M_start.__current){
            this->push_front(value);
            return this->_M_start;
        } else if (position.__current == this->_M_finish.__current){
            this->push_back(value);
            iterator __temp = _M_finish;
            --__temp;
            return __temp;
        } else
            return this->template _M_insert_auxiliary(position, value);
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    typename deque<_Tp, _Alloc,  _BufferSize>::iterator
    deque<_Tp, _Alloc,  _BufferSize>::insert(iterator position, value_type &&value) {
        return this->template emplace(position, std::move(value));
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    template<typename...Args>
    typename deque<_Tp, _Alloc,  _BufferSize>::iterator
    deque<_Tp, _Alloc,  _BufferSize>::emplace(iterator position, Args&&...args) {
        if (position.__current == this->_M_start.__current){
            this->template emplace_front(std::forward<Args>(args)...);
            return this->_M_start;
        } else if (position.__current == this->_M_finish.__current){
            this->template emplace_back(std::forward<Args>(args)...);
            iterator __temp = _M_finish;
            --__temp;
            return __temp;
        } else
            return this->template _M_insert_auxiliary(position, std::forward<Args>(args)...);
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    template<typename...Args>
    typename deque<_Tp, _Alloc,  _BufferSize>::iterator
    deque<_Tp, _Alloc,  _BufferSize>::_M_insert_auxiliary(iterator __position, Args&&...args) {
        difference_type __diff_front = __position - this->_M_start;
        value_type X_copy(std::forward<Args>(args)...);

        if (__diff_front < this->size() / 2){
            iterator __new_position = __position - 1;
            iterator old_start = this->_M_start;
            this->push_front(this->front());
            std::copy(old_start, __position, this->_M_start);
            *__new_position = std::move(X_copy);
            return __new_position;
        } else{
            iterator __new_position = __position + 1;
            iterator old_finish = this->_M_finish;
            this->push_back(this->back());
            std::copy_backward(__position, old_finish, this->_M_finish);
            *__position = std::move(X_copy);
            return __position;
        }
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    deque<_Tp, _Alloc,  _BufferSize>::deque(deque &&__other)
    : _M_buffer_map(__other._M_buffer_map), _M_buffer_size(__other._M_buffer_size),
    _M_finish(__other._M_finish), _M_start(__other._M_start) {
        __other._M_start.set_mem_null();
        __other._M_finish.set_mem_null();
        __other._M_buffer_size = 0;
        __other._M_buffer_map = nullptr;
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    deque<_Tp, _Alloc,  _BufferSize>& deque<_Tp, _Alloc,  _BufferSize>::
    operator=(const deque<_Tp, _Alloc, _BufferSize> &__other) {
        if (this != &__other){
            if (!this->empty())
                this->_M_clear_and_reserve_one();
            if (this->_M_start.__fist != nullptr && this->_M_buffer_map != nullptr){
                this->_M_deallocate_Node(this->_M_start.__fist);
                /// Delete All Buffer
                this->get_node_type_allocator().deallocate(this->_M_buffer_map, this->_M_buffer_size);
            }
            this->template _M_copy_initialized(__other.begin(), __other.end());
        }
        return *this;
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    deque<_Tp, _Alloc,  _BufferSize>& deque<_Tp, _Alloc,  _BufferSize>::
    operator=(deque<_Tp, _Alloc, _BufferSize> &&__other) {
        if (this != &__other){
            if (!this->empty())
                this->_M_clear_and_reserve_one();
            if (this->_M_start.__fist != nullptr && this->_M_buffer_map != nullptr){
                this->_M_deallocate_Node(this->_M_start.__fist);
                /// Delete All Buffer
                this->get_node_type_allocator().deallocate(this->_M_buffer_map, this->_M_buffer_size);
            }
            this->_M_start = __other._M_start;
            this->_M_finish = __other._M_finish;
            this->_M_buffer_size = __other._M_buffer_size;
            this->_M_buffer_map = __other._M_buffer_map;

            __other._M_start.set_mem_null();
            __other._M_finish.set_mem_null();
            __other._M_buffer_size = 0;
            __other._M_buffer_map = nullptr;
        }
        return *this;
    }
    /// TODO Replace Main Compare Function
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    bool operator==(const deque<_Tp, _Alloc, _BufferSize>&__x, const deque<_Tp, _Alloc, _BufferSize>&__y){
        return (__x.size() == __y.size() && std::equal(__x.begin(), __x.end(), __y.begin()));
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    bool operator!=(const deque<_Tp, _Alloc, _BufferSize>&__x, const deque<_Tp, _Alloc, _BufferSize>&__y){
        return !(__x == __y);
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    bool operator<(const deque<_Tp, _Alloc, _BufferSize>&__x, const deque<_Tp, _Alloc, _BufferSize>&__y){
        return std::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    bool operator>(const deque<_Tp, _Alloc, _BufferSize>&__x, const deque<_Tp, _Alloc, _BufferSize>&__y){
        return __y < __x;
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    bool operator>=(const deque<_Tp, _Alloc, _BufferSize>&__x, const deque<_Tp, _Alloc, _BufferSize>&__y){
        return !(__x < __y);
    }
    template<typename _Tp, typename _Alloc, stl::size_t _BufferSize>
    bool operator<=(const deque<_Tp, _Alloc, _BufferSize>&__x, const deque<_Tp, _Alloc, _BufferSize>&__y){
        return !(__x > __y);
    }
}
#endif //STL2_0_STL_DEQUE_H
