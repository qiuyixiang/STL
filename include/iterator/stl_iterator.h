//
// Created by 11508 on 2023-05-24.
//

#ifndef STL2_0_STL_ITERATOR_H
#define STL2_0_STL_ITERATOR_H

/**
 * Various Iterator to adapt Container, IO Stream
 * Extends Iterator !
 */

#include "./iterator_traits.h"

namespace stl{

    /// Back Inserter Iterator
    template<typename _Container>
    class back_inserter_iterator{
    protected:
        _Container* __container;
    public:
        typedef stl::output_iterator_tag  iterator_category;
        typedef void value_type;
        typedef void pointer;
        typedef void reference;
        typedef void difference_type;

        explicit back_inserter_iterator(_Container& __con) : __container{__con} {  };
        back_inserter_iterator& operator=(const typename _Container::value_type& __val){
            this->__container->push_back(__val);
            return *this;
        }
        back_inserter_iterator& operator=(typename _Container::value_type&& __val){
            this->__container->push_back(std::move(__val));
            return *this;
        }

        back_inserter_iterator& operator*() { return *this;  }
        back_inserter_iterator& operator++() {  return *this; }
        back_inserter_iterator operator++(int) { return *this; }
    };

    template<typename _Container>
    inline back_inserter_iterator<_Container> back_inserter(_Container& __container){
        return back_inserter_iterator<_Container>(__container);
    }

    /// Front Inserter Iterator
    template<typename _Container>
    class front_inserter_iterator{
    protected:
        _Container* __container;
    public:
        typedef stl::output_iterator_tag  iterator_category;
        typedef void value_type;
        typedef void pointer;
        typedef void reference;
        typedef void difference_type;

        explicit front_inserter_iterator(_Container& __con) : __container{__con} {  };
        front_inserter_iterator& operator=(const typename _Container::value_type& __val){
            this->__container->push_front(__val);
            return *this;
        }
        front_inserter_iterator& operator=(typename _Container::value_type&& __val){
            this->__container->push_front(std::move(__val));
            return *this;
        }

        front_inserter_iterator& operator*() { return *this;  }
        front_inserter_iterator& operator++() {  return *this; }
        front_inserter_iterator operator++(int) { return *this; }
    };

    template<typename _Container>
    inline front_inserter_iterator<_Container> front_inserter(_Container& __container){
        return front_inserter_iterator<_Container>(__container);
    }

    /// Inserter Iterator
    template<typename _Container>
    class inserter_iterator {
    protected:
        _Container __container;
        typename _Container::iterator __iter;
    public:
        typedef stl::output_iterator_tag  iterator_category;
        typedef void value_type;
        typedef void pointer;
        typedef void reference;
        typedef void difference_type;

        inserter_iterator(_Container& __con, typename _Container::iterator __Iter)
        : __container{ __con }, __iter{ __Iter } { }
        inserter_iterator& operator=(const typename _Container::value_type& __val) {
            /// Because of the change of the container's size
            /// All iterator has invalid so need to update the iterator
            this->__iter = this->__container->insert(this->__iter, __val);
            /// iterator follows the __container's fixed place !
            this->__iter++;
            return *this;
        }
        inserter_iterator& operator=(typename _Container::value_type&& __val){
            this->__iter = this->__container->insert(this->__iter, std::move(__val));
            this->__iter++;
            return *this;
        }

        inserter_iterator& operator*() {  return *this;  }
        inserter_iterator& operator++() {  return *this;  }
        inserter_iterator operator++(int) {  return *this;  }
    };

    template<typename _Container, typename _Iterator>
    inline inserter_iterator<_Container> inserter(_Container& __container, _Iterator __iter){
        return inserter_iterator<_Container>(__container, __iter);
    }


    /**
     * Base Iterator stl::__normal_iterator
     * This iterator is a nested for stl::vector 's iterator
     * Implementation Here
     */
    template<typename _Iterator>
    class __normal_iterator{
    public:
        typedef stl::iterator_traits<_Iterator> __iterator_traits;

        typedef typename __iterator_traits ::iterator_category  iterator_category;
        typedef typename __iterator_traits ::value_type  value_type;
        typedef typename __iterator_traits ::difference_type difference_type;
        typedef typename __iterator_traits ::pointer pointer;
        typedef typename __iterator_traits ::reference reference;

        typedef _Iterator iterator_type;

    protected:
        iterator_type _M_current;

    public:
        _STL_USE_CONSTEXPR __normal_iterator() _STL_NO_EXCEPTION
        : _M_current{iterator_type { } } {  };
        explicit __normal_iterator(iterator_type __i)  _STL_NO_EXCEPTION
        : _M_current{__i} {  };

        _STL_USE_UTILITY_INLINE
        const _Iterator& base() const {
            return this->_M_current;
        }

        __normal_iterator(const __normal_iterator& __i) _STL_NO_EXCEPTION
        :_M_current{__i.base()} { };

        reference operator*() const _STL_NO_EXCEPTION {
            return *(this->base());
        }
        pointer operator->() const _STL_NO_EXCEPTION {
            return this->base();
        }
        __normal_iterator& operator++() _STL_NO_EXCEPTION {
            ++_M_current;
            return *this;
        }
        __normal_iterator operator++(int) _STL_NO_EXCEPTION {
            return __normal_iterator(_M_current++);
        }
        __normal_iterator& operator--() _STL_NO_EXCEPTION{
            --_M_current;
            return *this;
        }
        __normal_iterator operator--(int) _STL_NO_EXCEPTION {
            return __normal_iterator(_M_current--);
        }
        ///// Random access iterator requirements
        reference operator[](difference_type __n) _STL_NO_EXCEPTION{
            return _M_current[__n];
        }

        __normal_iterator& operator+=(difference_type __n) _STL_NO_EXCEPTION {
            _M_current += __n;
            return *this;
        }
        __normal_iterator& operator-=(difference_type __n) _STL_NO_EXCEPTION {
            _M_current -= __n;
            return *this;
        }
        __normal_iterator operator+(difference_type __n) _STL_NO_EXCEPTION {
            return __normal_iterator(_M_current + __n);
        }
        __normal_iterator operator-(difference_type __n) _STL_NO_EXCEPTION {
            return __normal_iterator(_M_current - __n);
        }
    };

    /// Operator Declare For __normal_iterator
    template<typename _Iterator>
    _STL_USE_UTILITY_INLINE bool operator==
    (__normal_iterator<_Iterator>& __l, __normal_iterator<_Iterator>& __r) _STL_NO_EXCEPTION {
        return __l.base() == __r.base();
    }
    template<typename _Iterator>
    _STL_USE_UTILITY_INLINE bool operator!=
            (__normal_iterator<_Iterator>& __l, __normal_iterator<_Iterator>& __r) _STL_NO_EXCEPTION {
        return __l.base() != __r.base();
    }
    template<typename _Iterator>
    _STL_USE_UTILITY_INLINE bool operator>
            (__normal_iterator<_Iterator>& __l, __normal_iterator<_Iterator>& __r) _STL_NO_EXCEPTION {
        return __l.base() > __r.base();
    }
    template<typename _Iterator>
    _STL_USE_UTILITY_INLINE bool operator>=
            (__normal_iterator<_Iterator>& __l, __normal_iterator<_Iterator>& __r) _STL_NO_EXCEPTION {
        return __l.base() >= __r.base();
    }
    template<typename _Iterator>
    _STL_USE_UTILITY_INLINE bool operator<
            (__normal_iterator<_Iterator>& __l, __normal_iterator<_Iterator>& __r) _STL_NO_EXCEPTION {
        return __l.base() < __r.base();
    }
    template<typename _Iterator>
    _STL_USE_UTILITY_INLINE bool operator<=
            (__normal_iterator<_Iterator>& __l, __normal_iterator<_Iterator>& __r) _STL_NO_EXCEPTION {
        return __l.base() <= __r.base();
    }

    /// Reverse Iterator
    template<typename _Iterator>
    class reverse_iterator{
    protected:
            _Iterator _M_current;
    public:
        typedef typename stl::iterator_traits<_Iterator>::iterator_category iterator_category;
        typedef typename stl::iterator_traits<_Iterator>::value_type value_type;
        typedef typename stl::iterator_traits<_Iterator>::pointer pointer;
        typedef typename stl::iterator_traits<_Iterator>::reference reference;
        typedef typename stl::iterator_traits<_Iterator>::difference_type difference_type;

        typedef _Iterator iterator_type;
        typedef reverse_iterator<iterator_type> reverse_iterator_type;

    public:
        reverse_iterator() {  };
        explicit reverse_iterator(iterator_type __i) : _M_current(__i) {  };
        reverse_iterator(const reverse_iterator_type& __i) : _M_current(__i._M_current) {  };

        iterator_type base() const { return _M_current; }

        template<typename _Iter>
        reverse_iterator(const reverse_iterator<_Iter>& _Other) : _M_current(_Other.base()) {
#ifdef DEBUGGER
            std::cout<<"Template Type Convict !"<<std::endl;
#endif
        };
        reference operator*() const {
            iterator_type __temp = _M_current;
            return *(--__temp);
        }

        pointer operator->() const {
            return &(this->operator*());
        }
        reverse_iterator_type& operator++(){
            --_M_current;
            return *this;
        }
        reverse_iterator_type operator++(int){
            reverse_iterator_type __temp = *this;
            --_M_current;
            return __temp;
        }
        reverse_iterator_type& operator--(){
            ++_M_current;
            return *this;
        }
        reverse_iterator_type operator--(int){
            reverse_iterator_type __temp = *this;
            ++_M_current;
            return __temp;
        }
        reverse_iterator_type operator+(difference_type __n) const{
            return reverse_iterator_type (_M_current - __n);
        }
        reverse_iterator_type operator-(difference_type __n) const{
            return reverse_iterator_type (_M_current + __n);
        }
        reverse_iterator_type & operator+=(difference_type __n){
            _M_current -= __n;
            return *this;
        }
        reverse_iterator_type & operator-=(difference_type __n){
            _M_current += __n;
            return *this;
        }
        reference operator[](difference_type __n) const {
            return *(*this + __n);
        }
    };

    /// Operator for Reverse Iterator
    template<typename _Iterator>
    _STL_USE_UTILITY_INLINE bool operator==
    (const reverse_iterator<_Iterator>& __l, const reverse_iterator<_Iterator>& __r){
        return __l.base() == __r.base();
    }
    template<typename _Iterator>
    _STL_USE_UTILITY_INLINE bool operator!=
            (const reverse_iterator<_Iterator>& __l, const reverse_iterator<_Iterator>& __r){
        return __l.base() != __r.base();
    }
    template<typename _Iterator>
    _STL_USE_UTILITY_INLINE bool operator>
            (const reverse_iterator<_Iterator>& __l, const reverse_iterator<_Iterator>& __r){
        return __l.base() > __r.base();
    }
    template<typename _Iterator>
    _STL_USE_UTILITY_INLINE bool operator<
            (const reverse_iterator<_Iterator>& __l, const reverse_iterator<_Iterator>& __r){
        return __l.base() < __r.base();
    }
    template<typename _Iterator>
    _STL_USE_UTILITY_INLINE bool operator>=
            (const reverse_iterator<_Iterator>& __l, const reverse_iterator<_Iterator>& __r){
        return __l.base() >= __r.base();
    }
    template<typename _Iterator>
    _STL_USE_UTILITY_INLINE bool operator<=
            (const reverse_iterator<_Iterator>& __l, const reverse_iterator<_Iterator>& __r){
        return __l.base() <= __r.base();
    }
}
#endif //STL2_0_STL_ITERATOR_H
