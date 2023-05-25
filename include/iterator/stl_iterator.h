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

    /// Input Stream Iterator

    template<typename _Tp, typename _Distance = stl::ptrdiff_t>
    class istream_iterator;

    template<typename _Tp>
    _STL_USE_UTILITY_INLINE bool operator==
            (const istream_iterator<_Tp>& __x, const istream_iterator<_Tp>&__y);
    template<typename _Tp>
    _STL_USE_UTILITY_INLINE bool operator!=
            (const istream_iterator<_Tp>& __x, const istream_iterator<_Tp>&__y);

    template<typename _Tp, typename _Distance>
    class istream_iterator{
        /// Friend Member Declare
        friend bool operator== _STL_USE_MULL_TMP_ARG
                (const istream_iterator<_Tp>& __x, const istream_iterator<_Tp>&__y);
        friend bool operator!= _STL_USE_MULL_TMP_ARG
                (const istream_iterator<_Tp>& __x, const istream_iterator<_Tp>&__y);
    public:
           typedef _Tp value_type;
           typedef _Distance difference_type;
           typedef const _Tp* pointer;
           typedef const _Tp& reference;
           typedef const _Tp* const_pointer;
           typedef const _Tp& const_reference;
           typedef stl::input_iterator_tag iterator_category;

           /// Protected Member
    protected:
            value_type _M_value;
            bool _M_end_mark;
            std::istream* _M_stream;

            void __read(){
                _M_end_mark = (*_M_stream) ? true : false;
                if (_M_stream)
                    *_M_stream >> _M_value;
                /// Update The Status OF the istream
                _M_end_mark = (*_M_stream) ? true : false;
            }
            bool _M_equal(const istream_iterator& __other) const {
                return _M_end_mark == __other._M_end_mark &&
                       (!_M_end_mark || _M_stream == __other._M_stream);
            }
    public:
        _STL_USE_CONSTEXPR istream_iterator() : _M_stream(&std::cin), _M_end_mark(false) {  }
        istream_iterator(std::istream& __is) : _M_stream(&__is) { this->__read(); }

        reference operator*() const {  return _M_value; }
        pointer operator->() const {  return &(this->operator*()); }

        istream_iterator& operator++() {
            this->__read();
            return *this;
        };
        istream_iterator operator++(int){
            istream_iterator __temp = *this;
            this->__read();
            return __temp;
        }
    };
    template<typename _Tp>
    _STL_USE_UTILITY_INLINE bool operator==
    (const istream_iterator<_Tp>& __x, const istream_iterator<_Tp>&__y){
        return __x._M_equal(__y);
    }

    template<typename _Tp>
    _STL_USE_UTILITY_INLINE bool operator!=
            (const istream_iterator<_Tp>& __x, const istream_iterator<_Tp>&__y){
        return !__x._M_equal(__y);
    }

    /// Output Stream Iterator

    template<typename _Tp>
    class ostream_iterator;

    template<typename _Tp>
    _STL_USE_UTILITY_INLINE bool operator==
            (const ostream_iterator<_Tp>& __x, const ostream_iterator<_Tp> __y);

    template<typename _Tp>
    class ostream_iterator{
        friend bool operator== _STL_USE_MULL_TMP_ARG
                (const ostream_iterator<_Tp>& __x, const ostream_iterator<_Tp> __y);
    public:
            typedef stl::output_iterator_tag iterator_category;
            typedef void value_type;
            typedef void pointer;
            typedef void reference;
            typedef void difference_type;
    protected:
            std::ostream * _M_stream;
            const char * _M_string;
    public:
        _STL_USE_CONSTEXPR ostream_iterator(std::ostream & __os)
        : _M_stream(&__os), _M_string(nullptr) {  }

        _STL_USE_CONSTEXPR ostream_iterator(std::ostream & __os, const char * __ptr)
        : _M_string(__ptr), _M_stream(&__os) {  }

        ostream_iterator& operator=(const _Tp& __val){
            *_M_stream << __val;
            if (_M_string)
                *_M_stream << _M_string;
            return *this;
        }

        ostream_iterator& operator++() {  return *this;  }
        ostream_iterator operator++(int) {  return *this; }
        ostream_iterator& operator*() {  return *this;  }
    };

    template<typename _Tp>
    _STL_USE_UTILITY_INLINE bool operator==
    (const ostream_iterator<_Tp>& __x, const ostream_iterator<_Tp> __y){
        return __x._M_string == __y._M_string && __x._M_stream == __y._M_stream;
    }
    template<typename _Tp>
    _STL_USE_UTILITY_INLINE bool operator!=
    (const ostream_iterator<_Tp>& __x, const ostream_iterator<_Tp> __y){
        return !(__x == __y);
    }
}
#endif //STL2_0_STL_ITERATOR_H
