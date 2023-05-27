//
// Created by 11508 on 2023-05-26.
//

#ifndef STL2_0_STL_VECTOR_H
#define STL2_0_STL_VECTOR_H

#include "../allocator/allocator_traits.h"
#include "../iterator/iterator_traits.h"
#include "../iterator/stl_iterator.h"
#include "../util/utility.h"

#include <iostream>

/// The Implementation Of stl::vector

namespace __std__{

    /// Base class for vector
    /// This class Create Memory for Storage But Not Initialized !
    template<typename _Tp, typename _Alloc>
    struct _Vec_Base{

        /// Type Define For _Vec_Base
        typedef typename stl::__allocator_traits<_Alloc>::allocator_type     _Alloc_type;
        typedef typename stl::__allocator_traits<_Alloc>:: template rebind_alloc<_Tp>  _Rebind_Alloc_type;

        typedef typename stl::__allocator_traits<_Alloc>::pointer pointer;

        struct _Vec_Imp : public _Rebind_Alloc_type{
            pointer _M_start;
            pointer _M_finish;
            pointer _M_end_of_storage;

            /// Public Constructor
            _STL_USE_CONSTEXPR _Vec_Imp() : _Rebind_Alloc_type (),
            _M_start(), _M_finish(), _M_end_of_storage() {  };

            _STL_USE_CONSTEXPR _Vec_Imp(const _Rebind_Alloc_type& _alloc) _STL_NO_EXCEPTION
            : _Rebind_Alloc_type(_alloc), _M_start(), _M_finish(), _M_end_of_storage() { };

            _STL_USE_CONSTEXPR _Vec_Imp(_Rebind_Alloc_type&& _alloc) _STL_NO_EXCEPTION
            :  _Rebind_Alloc_type(std::move(_alloc)), _M_start(), _M_finish(), _M_end_of_storage() { };

            void _M_swap_data(_Vec_Imp& _Other){
                stl::swap(_M_start, _Other._M_start);
                stl::swap(_M_finish, _Other._M_finish);
                stl::swap(_M_end_of_storage, _Other._M_end_of_storage);
            }
        };

        /// public Member Data
        _Vec_Imp _M_imp;

        typedef _Alloc_type allocator_type;
        typedef typename allocator_type ::size_type size_type;

        /// Public Member Function
        _Rebind_Alloc_type& get_Tp_allocator() {
            return *static_cast<_Rebind_Alloc_type*>(&this->_M_imp);
        }

        const _Rebind_Alloc_type& get_Tp_allocator() const {
            return *static_cast<const _Rebind_Alloc_type*>(&this->_M_imp);
        }
        allocator_type get_allocator() const {
            return allocator_type { };
        }

        pointer _M_allocate(size_type __n) {
            typedef stl::__allocator_traits<_Rebind_Alloc_type> _Ac;
            return __n != 0 ? _Ac ::allocate(this->_M_imp, __n) : pointer();
        }

        void _M_deallocate(pointer __p, size_type){
            if (__p){
                typedef stl::__allocator_traits<_Rebind_Alloc_type> _Ac;
                _Ac ::deallocate(this->_M_imp, __p);
            }
        }
        /// This Function Create Storage but not initialize
        void _M_create_storage(size_type __n){
            _M_imp._M_start = this->_M_allocate(__n);
            _M_imp._M_finish = _M_imp._M_start + __n;
            _M_imp._M_end_of_storage = _M_imp._M_finish;
        }
        /// Public Member Constructor
        _STL_USE_CONSTEXPR _Vec_Base() : _M_imp() {  };
        explicit _Vec_Base(size_type __n) : _M_imp()
        { this->_M_create_storage(__n);  }

        _Vec_Base(size_type __n, const _Rebind_Alloc_type& _other) : _M_imp(_other) {
            this->_M_create_storage(__n);
        }
        _Vec_Base( _Vec_Base&& _Other) : _M_imp() {
            this->_M_imp._M_swap_data(_Other._M_imp);
        }
        ~_Vec_Base(){
#ifdef VECTOR_DBG
            std::cout<<"_Vec_Base invoked Destructor !!!"<<std::endl;
#endif
            if (this->_M_imp._M_start){
                this->_M_deallocate(_M_imp._M_start, _M_imp._M_end_of_storage - _M_imp._M_start);
            }
        }
    };
}
namespace stl{

    /// Formal Vector's Implementation
    template<typename _Tp, typename _Alloc = stl::default_allocator<_Tp>>
    class vector : protected __std__::_Vec_Base<_Tp, _Alloc>{
    protected:
        typedef _Alloc allocator_type;
        typedef typename stl::__allocator_traits<_Alloc>:: template rebind_alloc<_Tp> rebind_allocator_type;
    public:
        /// Public Type Define

        typedef _Tp value_type;
        typedef _Tp* pointer;
        typedef _Tp& reference;
        typedef const _Tp* const_pointer;
        typedef const _Tp& const_reference;
        typedef stl::size_t size_type;
        typedef stl::ptrdiff_t difference_type;

        typedef stl::__normal_iterator<pointer> iterator;
        typedef const stl::__normal_iterator<pointer> const_iterator;

        typedef stl::reverse_iterator<iterator> reverse_iterator;
        typedef const stl::reverse_iterator<iterator> const_reverse_iterator;

        typedef __std__::_Vec_Base<_Tp, _Alloc> _Vec_base;
    protected:
        /// Protected Functional Member Function
        void _M_Fill_n(const value_type& __val);
        void _M_Clear();

        template<typename _FrowardIterator>
        void _M_Copy(_FrowardIterator _First, _FrowardIterator _Last);

        template<typename ...Args>
        void _M_emplace_back_auxiliary(Args&&...args);

    public:
        /// Public Constructor
        _STL_USE_CONSTEXPR vector() : _Vec_base() {  };

        explicit  vector(size_type __n) : _Vec_base(__n) {
            stl::uninitialized_fill(this->begin(), this->end(), value_type());
        };

        vector(size_type n, const value_type& val) : _Vec_base(n)
        { this->_M_Fill_n(val);  }
        vector(int n, const value_type& val) : _Vec_base(n)
        { this->_M_Fill_n(val);  }
        vector(long n, const value_type& val) : _Vec_base(n)
        { this->_M_Fill_n(val);  }

        vector(const std::initializer_list<value_type>& _li) : _Vec_base(_li.size()) {
            this->_M_Copy(_li.begin(), _li.end());
        }

        /// Copy And Move Constructor
        vector(const vector<value_type>& _Other) : _Vec_base(_Other.size()){
            this->_M_Copy(_Other.begin(), _Other.end());
        }
        vector(vector<value_type>&& _Other) : _Vec_base(std::move(_Other)) {  }

        /// Copy And Move Operator
        vector& operator=(const vector& _Other);
        vector& operator=(std::initializer_list<value_type>& _Li);
        vector& operator=(vector&& _Other){
            if (this != &_Other){
                this->_M_Clear();
                this->_M_imp._M_swap_data(_Other._M_imp);
            }
            return *this;
        }
        /// Public  Destructor
        ~vector() {
            if (!this->empty())
                stl::_Destroy(this->begin(), this->end());
        }
    public:
        /// Return Iterator

        /// Formal begin, end
        iterator begin() _STL_NO_EXCEPTION {
            return iterator (this->_M_imp._M_start);
        }
        iterator end() _STL_NO_EXCEPTION {
            return iterator (this->_M_imp._M_finish);
        }
        /// const begin, end
        const_iterator begin() const _STL_NO_EXCEPTION {
            return const_iterator (this->_M_imp._M_start);
        }
        const_iterator end() const _STL_NO_EXCEPTION {
            return const_iterator (this->_M_imp._M_finish);
        }
        /// explicit const begin, end
        const_iterator cbegin() const _STL_NO_EXCEPTION {
            return const_iterator (this->_M_imp._M_start);
        }
        const_iterator cend() const _STL_NO_EXCEPTION {
            return const_iterator (this->_M_imp._M_finish);
        }
        /// rbegin, rend
        reverse_iterator rbegin() _STL_NO_EXCEPTION {
            return reverse_iterator (this->end());
        }
        reverse_iterator rend() _STL_NO_EXCEPTION {
            return reverse_iterator (this->begin());
        }
        /// const rbegin, rend
        const_reverse_iterator rbegin() const _STL_NO_EXCEPTION {
            return const_reverse_iterator (this->end());
        }
        const_reverse_iterator rend() const _STL_NO_EXCEPTION {
            return const_reverse_iterator (this->begin());
        }
        /// explicit rbegin, rend
        const_reverse_iterator crbegin() const _STL_NO_EXCEPTION {
            return const_reverse_iterator (this->end());
        }
        const_reverse_iterator crend() const _STL_NO_EXCEPTION {
            return const_reverse_iterator (this->begin());
        }

        size_type size() const {
            return size_type (this->_M_imp._M_finish - this->_M_imp._M_start);
        }
        size_type capacity() const {
            return size_type (this->_M_imp._M_end_of_storage - this->_M_imp._M_start);
        }
        size_type max_size() const {
            return this->get_allocator().max_size();
        }
        bool empty() const {  return (this->begin() == this->end());  }

        reference front()  _STL_NO_EXCEPTION {  return *(this->begin());  }
        reference back() _STL_NO_EXCEPTION {  return *(this->end() - 1);  }

        reference operator[](size_type __n) {  return *(this->begin() + __n);  }

        void display(bool flag = false) const;

        void push_back(const value_type& _val);
        void push_back(value_type&& _val);

        template<typename ...Args>
        void emplace_back(Args&&... args);

        void pop_back() noexcept;
        iterator erase(iterator _first, iterator _last);
        iterator erase(iterator _position);
        void clear();
        void shrink_to_fit()noexcept;
    };

    /// Implementation of Member Functions
    template<typename _Tp, typename _Alloc>
    void vector<_Tp, _Alloc>::display(bool flag) const {
        for ( iterator _iter =(iterator) this->begin(); _iter != this->cend(); ++_iter)
            std::cout<<*_iter<<" ";
        std::cout<<std::endl;
        if (flag){
            std::cout<<"capacity : "<< this->capacity()<<" "<<"size : "<< this->size()<<std::endl;
            std::cout<<std::endl;
        }
    }
    template<typename _Tp, typename _Alloc>
    void vector<_Tp, _Alloc>::_M_Fill_n(const value_type &__val) {
        std::uninitialized_fill_n(this->begin(), this->end() - this->begin(), __val);
    }
    template<typename _Tp, typename _Alloc>
    template<typename _FrowardIterator>
    void vector<_Tp, _Alloc>::_M_Copy(_FrowardIterator _First, _FrowardIterator _Last){
        stl::uninitialized_copy(_First, _Last, this->begin());
    }
    /// Deallocate Memory and Destroy Objects !

    template<typename _Tp, typename _Alloc>
    void vector<_Tp, _Alloc>::_M_Clear() {
        stl::_Destroy(this->begin(), this->end());
        this->_M_deallocate(this->_M_imp._M_start, this->_M_imp._M_end_of_storage - this->_M_imp._M_start);
        this->_M_imp._M_start = nullptr;
        this->_M_imp._M_finish = nullptr;
        this->_M_imp._M_end_of_storage = nullptr;
    }

    template<typename _Tp, typename _Alloc>
    vector<_Tp, _Alloc>& vector<_Tp, _Alloc>::operator=(const vector<_Tp, _Alloc> &_Other) {
        if (this != &_Other){
            if (this->capacity() >= _Other.size()){
                this->_M_imp._M_finish = stl::uninitialized_copy
                        (_Other.begin(), _Other.end(),this->_M_imp._M_start);
            } else{
                /// Current Vector Capacity is not enough to caught new Vector's Memory
                this->_M_Clear();
                this->_M_imp._M_start = this->get_allocator().allocate(_Other.size());
                this->_M_imp._M_finish = stl::uninitialized_copy
                        (_Other.begin(), _Other.end(), this->_M_imp._M_start);
                this->_M_imp._M_end_of_storage = this->_M_imp._M_finish;
            }
        }
        return *this;
    }
    template<typename _Tp, typename _Alloc>
    vector<_Tp, _Alloc>& vector<_Tp, _Alloc>::operator=(std::initializer_list<value_type> &_Li) {
        if (this->capacity() >= _Li.size()){
            this->_M_imp._M_finish = stl::uninitialized_copy
                    (_Li.begin(), _Li.end(), this->_M_imp._M_start);
        } else{
            this->_M_Clear();
            this->_M_imp._M_start = this->get_allocator().allocate(_Li.size());
            this->_M_imp._M_finish = stl::uninitialized_copy
                    (_Li.begin(), _Li.end(), this->_M_imp._M_start);
            this->_M_imp._M_end_of_storage = this->_M_imp._M_finish;
        }
        return *this;
    }
    template<typename _Tp, typename _Alloc>
    void vector<_Tp, _Alloc>::push_back(const value_type &_val) {
        if (this->_M_imp._M_finish != this->_M_imp._M_end_of_storage){
            stl::_Construct(this->_M_imp._M_finish, _val);
            ++this->_M_imp._M_start;
        } else
            this->template _M_emplace_back_auxiliary(_val);
    }

    template<typename _Tp, typename _Alloc>
    void vector<_Tp, _Alloc>::push_back(value_type &&_val) {
        this->template emplace_back(__STL_GCC_MOVE(_val));
    }

    /// Medium Junction Member Function (invoked by push_back(obj&&) )
    template<typename _Tp, typename _Alloc>
    template<typename ...Args>
    void vector<_Tp, _Alloc>::emplace_back(Args&&... args) {
        if (this->_M_imp._M_finish != this->_M_imp._M_end_of_storage){
            stl::_Construct(this->_M_imp._M_finish , std::forward<Args>(args)...);
            ++this->_M_imp._M_finish;
        } else
            this->template _M_emplace_back_auxiliary(std::forward<Args>(args)...);
    }

    /// Do Real Push Back (Allocate or Create) New Memory Operation
    template<typename _Tp, typename _Alloc>
    template<typename ...Args>
    void vector<_Tp, _Alloc>::_M_emplace_back_auxiliary(Args&&... args){
        const size_type __old_size = this->size();
        const size_type __new_size = this->size() == 0 ? 1 : 2 * __old_size;
        pointer _new_start = this->get_allocator().allocate(__new_size);
        pointer _new_finish = _new_start;
        try {
            _new_finish = stl::uninitialized_copy(this->_M_imp._M_start, this->_M_imp._M_finish, _new_start);
            stl::_Construct(_new_finish, std::forward<Args>(args)...);
            ++_new_finish;
        } catch (...) {
            stl::_Destroy(_new_start, _new_finish);
            this->get_allocator().deallocate
            (_new_start, size_type(_new_finish - _new_start));
            throw ;
        }
        /// If Throw An Exception These Statements will not be executed !
        /// Deallocate and Destroy Previous Memory (object) !
        this->_M_Clear();

        /// Reset this pointer to new memory
        this->_M_imp._M_start = _new_start;
        this->_M_imp._M_finish = _new_finish;
        this->_M_imp._M_end_of_storage = _new_start + __new_size;
    }

    template<typename _Tp, typename _Alloc>
    void vector<_Tp, _Alloc>::pop_back() noexcept {
        --this->_M_imp._M_finish;
        stl::_Destroy(this->_M_imp._M_finish);
    }
    template<typename _Tp, typename _Alloc>
    void vector<_Tp, _Alloc>::clear() {
        this->erase(this->begin(), this->end());
    }
    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator vector<_Tp, _Alloc>::erase(iterator _position) {
        if (_position + 1 != this->end()){
            /// TODO Replace std::copy to stl::copy
            std::copy(_position + 1, this->end(), _position);
            --this->_M_imp._M_finish;
            stl::_Destroy(this->_M_imp._M_finish);
        } else
            this->pop_back();
        return _position;
    }
    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator vector<_Tp, _Alloc>::erase(iterator _first, iterator _last) {
        iterator __temp = std::copy(_last, this->end(), _first);
        stl::_Destroy(__temp, this->end());
        this->_M_imp._M_finish = __temp.base();
        return _first;
    }
    template<typename _Tp, typename _Alloc>
    void vector<_Tp, _Alloc>::shrink_to_fit() noexcept {
        if (this->size() == this->capacity())
            return;
        /// TODO Shrink_to_fit
    }
}
#endif //STL2_0_STL_VECTOR_H
