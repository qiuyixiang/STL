//
// Created by 11508 on 2023-06-05.
//

#ifndef STL2_0_STL_ARRAY_H
#define STL2_0_STL_ARRAY_H

/**
 * The Implementation OF C++ Standard Array
 *
 * Until Now It Has Not Implemented Operator==
 * And Other Operator Operations
 * TODO Implementation Operator== and get()
 * Create on 2023-6-7
 */

#include "../allocator/allocator_traits.h"
#include "../util/ctt.h"
#include "../util/utility.h"
#include "../iterator/iterator_traits.h"
#include "../iterator/stl_iterator.h"


namespace __std__{

    /// A Simple Array Traits That Support Zero-Size !
    template<typename _Tp, stl::size_t _Size>
    struct _array_traits{
        typedef _Tp _Type[_Size];
    };

    /// Partial Specialization For Array
    template<typename _Tp>
    struct _array_traits<_Tp, 0>{
        struct _Type { };
    };
}
namespace stl{

    /// Implementation OF array
    template<typename _Tp, stl::size_t _Size>
    struct array{
    public:
        typedef _Tp                     value_type;
        typedef _Tp&                    reference;
        typedef _Tp*                    pointer;
        typedef stl::size_t             size_type;
        typedef const _Tp&              const_reference;
        typedef const _Tp*              const_pointer;
        typedef stl::ptrdiff_t          difference_type;

        typedef pointer                                     iterator;
        typedef const_pointer                               const_iterator;
        typedef stl::reverse_iterator<pointer>              reverse_iterator;
        typedef stl::reverse_iterator<const_iterator>       const_reverse_iterator;

        /// The Data Member Is Just A C-Build-in  Array
        typename __std__::_array_traits<_Tp, _Size>::_Type _M_element;

        /// This Class Without Constructor And Destructor !
    public:
        iterator data() _STL_NO_EXCEPTION {
            return this->_M_element;
        }
        const_iterator data() const _STL_NO_EXCEPTION {
            return this->_M_element;
        }
        /// Public Member Function !

        /// Iterator
        iterator begin() _STL_NO_EXCEPTION {
            return iterator (this->data());
        }
        iterator end() _STL_NO_EXCEPTION {
            return iterator (this->data() + _Size);
        }
        const_iterator begin() const _STL_NO_EXCEPTION {
            return const_iterator (this->data());
        }
        const_iterator end() const _STL_NO_EXCEPTION {
            return const_iterator (this->data() + _Size);
        }
        const_iterator cbegin() const _STL_NO_EXCEPTION {
            return const_iterator (this->data());
        }
        const_iterator cend() const _STL_NO_EXCEPTION {
            return const_iterator (this->data() + _Size);
        }
        reverse_iterator rbegin() _STL_NO_EXCEPTION {
            return reverse_iterator (this->end());
        }
        reverse_iterator rend() _STL_NO_EXCEPTION {
            return reverse_iterator (this->begin());
        }
        const_reverse_iterator rbegin() const _STL_NO_EXCEPTION {
            return const_reverse_iterator (this->end());
        }
        const_reverse_iterator rend() const _STL_NO_EXCEPTION {
            return const_reverse_iterator (this->begin());
        }
        const_reverse_iterator crbegin() const _STL_NO_EXCEPTION {
            return const_reverse_iterator (this->end());
        }
        const_reverse_iterator crend() const _STL_NO_EXCEPTION {
            return const_reverse_iterator (this->begin());
        }
        /// Capacity
        size_type size() const _STL_NO_EXCEPTION {
            return _Size;
        }
        size_type max_size() const _STL_NO_EXCEPTION {
            return _Size;
        }
        bool empty() const _STL_NO_EXCEPTION {
            return (this->size() == 0);
        }
        /// Access Element
        reference operator[](difference_type __n)  _STL_NO_EXCEPTION {
            return this->_M_element[__n];
        }
        _STL_USE_CONSTEXPR const_reference
        operator[](difference_type __n) const _STL_NO_EXCEPTION{
            return this->_M_element[__n];
        }
        void display(bool __debugger = false) const _STL_NO_EXCEPTION {
            for (auto __Iter = this->begin(); __Iter != this->end(); ++__Iter)
                std::cout<<*__Iter<<" ";
            std::cout<<std::endl;
            if (__debugger)
                std::cout<<"Size : "<< this->size()<<std::endl;
        }
        void fill(const value_type& _val) _STL_NO_EXCEPTION {
            std::fill_n(this->_M_element, this->size(), _val);
        }

        reference at(size_type __n){
            if (__n >= _Size)
                throw std::out_of_range("Error : Array index out of Range !");
            return _M_element[__n];
        }
        const_reference at(size_type __n) const {
            if (__n >= _Size)
                throw std::out_of_range("Error : Array index out of Range !");
            return _M_element[__n];
        }
        reference front()_STL_NO_EXCEPTION {
            return *this->begin();
        }
        const_reference front() const _STL_NO_EXCEPTION{
            return *this->begin();
        }
        reference back() _STL_NO_EXCEPTION {
            return _Size ? *(this->end() - 1) : *this->end();
        }
        const_reference back() const _STL_NO_EXCEPTION {
            return _Size ? *(this->end() - 1) : *this->end();
        }
        void swap(array& _other);
    };

    template<typename _Tp, stl::size_t _Size>
    void array<_Tp, _Size>::swap(array<_Tp, _Size> &_other) {
        /// TODO swap() function is wait to achieve !
    }

    /// TODO get() function is wait to achieve !


    /// TODO Logic Operator function is wait to achieve !
}
#endif //STL2_0_STL_ARRAY_H
