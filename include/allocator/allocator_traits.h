//
// Created by 11508 on 2023-05-23.
//

#ifndef STL2_0_ALLOCATOR_TRAITS_H
#define STL2_0_ALLOCATOR_TRAITS_H


/**
 * Type Traits for allocator
 *
 * All Standard allocator can use This allocator traits to trait attributes
 * And use this attributes to rebind other type
 *
 * public API For Allocators :
 *      #  allocate
 *      #  deallocate
 *      #  max_size
 *      #  construct
 *      #  destruct
 */

namespace stl{

    /// Base Type Define for default_allocator
    template<typename _Tp>
    using default_allocator = stl::new_allocator<_Tp> ;


    /// Allocator Traits
    template<typename _Alloc>
    class __allocator_traits{

    public:
        /// Type Define For Allocator Traits
        using allocator_type = _Alloc;
        using value_type            = typename allocator_type::value_type;
        using pointer               = typename allocator_type::pointer;
        using reference             = typename allocator_type::reference;
        using const_pointer         = typename allocator_type::const_pointer;
        using const_reference       = typename allocator_type::const_reference;
        using size_type             = typename allocator_type::size_type;
        using void_pointer          = void*;
        using const_void_pointer    = const void * ;

        template<typename _Up>
        using rebind_alloc = typename allocator_type::template rebind<_Up>::other;

        /// allocator traits for static member function
        static inline pointer allocate(allocator_type& __alloc, size_type __n);
        static inline void deallocate(allocator_type& __alloc, pointer __p);

        template<typename _alloc, typename _Up, typename... _Args>
        static auto construct(_alloc& __alloc, _Up * __p, _Args&& ...__args)
        -> decltype(__alloc.allocate(__p, std::forward<_Args>(__args)...)){
            return __alloc.allocate(__p, std::forward<_Args>(__args)...);
        }

        static void destroy(allocator_type& __alloc, pointer __p){
            __alloc.destroy(__p);
        }

        static size_type max_size(allocator_type& __alloc){
            return __alloc.max_size();
        }
    };

    template<typename _Alloc>
    typename __allocator_traits<_Alloc>::pointer
    __allocator_traits<_Alloc>::allocate(allocator_type &__alloc, size_type __n) {
        return __alloc.allocate(__n);
    }
    template<typename _Alloc>
    void __allocator_traits<_Alloc>::deallocate(allocator_type &__alloc, pointer __p) {
        __alloc.deallocate(__p);
    }
}
#endif //STL2_0_ALLOCATOR_TRAITS_H
