//
// Created by 11508 on 2023-05-21.
//

#ifndef STL2_0_ITERATOR_TRAITS_H
#define STL2_0_ITERATOR_TRAITS_H

/// Base Iterator class

#include "../util/ctt.h"

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

}
#endif //STL2_0_ITERATOR_TRAITS_H
