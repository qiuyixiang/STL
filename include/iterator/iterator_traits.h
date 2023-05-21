//
// Created by 11508 on 2023-05-21.
//

#ifndef STL2_0_ITERATOR_TRAITS_H
#define STL2_0_ITERATOR_TRAITS_H

/// Base Iterator class

#include "../util/ctt.h"

/// Declare of Inner Private Function
namespace stl{

    /// basic iterator tag
    struct input_iterator_tag {  };
    struct output_iterator_tag {  };
    struct forward_iterator_tag : public input_iterator_tag {  };
    struct bidirectional_iterator_tag : public forward_iterator_tag {  };
    struct random_access_iterator_tag : public bidirectional_iterator_tag {  };


    /// Base Iterator Template
    template<typename _Category, typename _Ele_t, typename _Distance = stl::ptrdiff_t,
            typename _Ptr = _Ele_t* , typename _Ref = _Ele_t&>
    struct iterator {
        typedef _Category           iterator_category;
        typedef _Ele_t              value_type;
        typedef _Distance           difference_type;
        typedef _Ptr                pointer;
        typedef _Ref                reference;
    };

    /// Iterator traits
    template<typename Iterator>
    struct iterator_traits{
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
    };

    /// Partial Specialization For Iterator traits (tp)
    template<typename _Tp>
    struct iterator_traits<_Tp*>{
        typedef _Tp                                 value_type;
        typedef stl::ptrdiff_t                      difference_type;
        typedef random_access_iterator_tag          iterator_category;
        typedef _Tp*                                pointer;
        typedef _Tp&                                reference;
    };

    /// Partial Specialization For Iterator traits ( const tp)
    template<typename _Tp>
    struct iterator_traits<const _Tp*>{
        typedef _Tp                                 value_type;
        typedef stl::ptrdiff_t                      difference_type;
        typedef random_access_iterator_tag          iterator_category;
        typedef const _Tp*                          pointer;
        typedef const _Tp&                          reference;
    };

    /// Traits for Category
    template<typename Iterator>
    inline typename iterator_traits<Iterator>::iterator_category Category(){
        return typename stl::iterator_traits<Iterator>::iterator_category { } ;
    }

    /// Traits for Value Type
    template<typename Iterator>
    inline typename iterator_traits<Iterator>::value_type * ValueType(){
        typedef typename stl::iterator_traits<Iterator>::value_type* Vl;
        return Vl {nullptr};
    }

    ///Traits for Difference Type
    template<typename Iterator>
    inline typename iterator_traits<Iterator>::difference_type * DifferenceType(){
        typedef typename stl::iterator_traits<Iterator>::difference_type* Vl;
        return Vl {nullptr};
    }

}
namespace __std__{

    /// Iterator Base Function

    /// The Implementation of Distance
    template<typename InputIterator>
    inline typename stl::iterator_traits<InputIterator>::difference_type
    __distance(InputIterator _First, InputIterator _Last, stl::input_iterator_tag){
        typename stl::iterator_traits<InputIterator>::difference_type _Result = 0;
        for ( ; _First != _Last; ++_First)
            ++_Result;
        return _Result;
    }

    template<typename InputIterator>
    inline typename stl::iterator_traits<InputIterator>::difference_type
    __distance(InputIterator _First, InputIterator _Last, stl::random_access_iterator_tag){
        return _Last - _First;
    }

    /// The Implementation of Advance
    template<typename InputIterator, typename Distance>
    inline void advance(InputIterator& __iter, Distance __n, stl::input_iterator_tag){
        while (__n > 0){
            --__n;
            ++__iter;
        }
    }

    template<typename InputIterator, typename Distance>
    inline void advance(InputIterator& __iter, Distance __n, stl::bidirectional_iterator_tag){
        if (__n >= 0)
            while (__n--)
                ++__iter;
        else
            while (__n++)
                --__iter;
    }

    template<typename InputIterator, typename Distance>
    inline void advance(InputIterator& __iter, Distance __n, stl::random_access_iterator_tag){
        __iter += __n;
    }
}

namespace stl{

    /// Iterator Base Function

    /// distance
    template<typename InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator _First, InputIterator _Last){
        typedef typename stl::iterator_traits<InputIterator>::iterator_category _Category;
        return __std__::__distance(_First, _Last, _Category{ });
    }

    /// advance
    template<typename InputIterator, typename Distance>
    inline void advance(InputIterator& Iter, Distance n){
        typedef typename stl::iterator_traits<InputIterator>::iterator_category _Category;
        __std__::advance(Iter, n, _Category{ } );
    }
}

#endif //STL2_0_ITERATOR_TRAITS_H
