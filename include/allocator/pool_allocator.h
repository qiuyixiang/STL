//
// Created by 11508 on 2023-05-23.
//

#ifndef STL2_0_POOL_ALLOCATOR_H
#define STL2_0_POOL_ALLOCATOR_H


/**
 * Pool Allocator Implementation
 *
 * @new context
 *
 */

///#define STATIC_DATA_CHECK

namespace __std__{

    /// Default allocator for some special circumstances  !
    /// This Class Without Constructor and Destructor !

    class __default_pool_alloc {
    public:
        __default_pool_alloc() = default;
        ~__default_pool_alloc() = default;

        /// Just a Simple Wrapping For CRT malloc() and free()
        static void * allocate(size_t __byte );
        static void * oom_malloc(size_t __byte);
        static void deallocate(void * __ptr, size_t);
    };

    /// __byte is a Byte Conception ! Directly Send into malloc
    void * __default_pool_alloc::allocate(size_t __byte ) {
        void * __result = nullptr;
        if ((__result = malloc(__byte)) != nullptr)
            return __result;
        else
            return __default_pool_alloc::oom_malloc(__byte);
    }
    void * __default_pool_alloc::oom_malloc(size_t __byte) {
        /// Out Of Memory Alloc
        std::new_handler __my_malloc_handler = std::get_new_handler();
        void * __result = nullptr;
        for ( ; ; ){
            if (__my_malloc_handler != nullptr){
                /// This New Handler May Free Memory !
                (*__my_malloc_handler)();
                __result = malloc(__byte);
                if (__result != nullptr)
                    return __result;
            }
            else
                throw std::bad_alloc ();
        }
    }
    void __default_pool_alloc::deallocate(void *__ptr, size_t) {
        /// Just Free Memory !
        free(__ptr);
    }

    /// The Implementation OF __gnu_cxx::__pool_allocator
    /// Base Component of stl::pool_allocator (alloc)
    /// Remove MultiThread Perspective
    /// This Type of pool_allocator 's unit is byte

    class __pool_alloc_base {
    protected:
        /// Enum for static data
        enum {  __S_align_ = 8  };
        enum {  __S_max_bytes = 128  };
        /// Size is 16
        enum {  __S_buffer_size = (stl::size_t) __S_max_bytes / (stl::size_t) __S_align_};

        /// Build-In Type Define For next linker !
        struct _Obj{
            struct _Obj* _S_next_free_list;
        };

        /// Primarily important Static Data Member !
        /// An Array That Contains Type of pointer (_Obj *)
        static _Obj*  _S_free_list_buffer[__S_buffer_size];

        /// Buffer Pool pointer
        /// Use char * to adapt byte memory !
        static char * _S_free_start;
        static char * _S_free_end;

        /// Just A Flag as additional-quantity
        static stl::size_t _S_heap_size;

        static stl::size_t ROUND_UP(stl::size_t __size){
            return ((__size) + __pool_alloc_base::__S_align_ - 1) &
                   ~(__pool_alloc_base::__S_align_ - 1);
        }
        /// Return __size in free_list's index
        static stl::size_t FREELIST_INDEX(stl::size_t __size){
            return ((__size + __pool_alloc_base::__S_align_ - 1) / __pool_alloc_base::__S_align_ - 1);
        }

#ifdef STATIC_DATA_CHECK
        public:
        static void _check_static_data(){
            for ( size_t __index = 0; __index != __S_buffer_size; ++__index)
                if (_S_free_list_buffer[__index] == nullptr)
                    continue;
                else
                    std::cout<<"Static Check Error "<<std::endl;
        };
#endif
    public:
        /// Memory Control !
        static void * __allocate(stl::size_t __byte);
        static void __deallocate(void * __ptr, size_t __byte);

        static void * __refill(size_t __n);
        static char * __chunk_alloc(size_t __byte, int& __node);

        inline static void __addition();
    };

    void * __pool_alloc_base::__allocate(stl::size_t __byte) {
        //std::cout<<__byte<<std::endl;
        /// Judge whether __byte greater that max limit !
        if (__byte > __S_max_bytes)
            return __default_pool_alloc::allocate(__byte);

        /// Search appropriate Memory chunk !
        _Obj * __free_list_index;
        _Obj * __result;
        /// Search Index For __byte
        __free_list_index = _S_free_list_buffer[0  + FREELIST_INDEX(__byte)];
        __result = __free_list_index;
        /// The Proper Block Is Empty
        if (__result == nullptr)
            return __refill(ROUND_UP(__byte));
        /// Reset _S_free_list_buffer
        _S_free_list_buffer[0  + FREELIST_INDEX(__byte)] = _S_free_list_buffer
                [0  + FREELIST_INDEX(__byte)]->_S_next_free_list;
        return __result;
    }
    void __pool_alloc_base::__deallocate(void *__ptr, size_t __byte) {
        if (__byte > __S_max_bytes){
            __default_pool_alloc::deallocate(__ptr, __byte);
            return;
        }
        /// Free Memory But Don't Invoke free() ; !
        /// Do not free them to OS (Operating System)!
        _Obj * __memory_ptr = reinterpret_cast<_Obj*>(__ptr);
        __memory_ptr->_S_next_free_list = _S_free_list_buffer[0 + FREELIST_INDEX(__byte)];
        _S_free_list_buffer[0 + FREELIST_INDEX(__byte)] = __memory_ptr;
    }
    /// Refill Memory From Memory-Pool-Buffer
    /// If Memory Pool is Empty Than Invoke __chunk_alloc to Get a New Chunk !
    /// Splice from raw memory to block !
    void * __pool_alloc_base::__refill(size_t __byte) {
        /// The Amount Of Memory Buffer is 20
        int __buffer_size = 20;
        char * __chunk_ptr = __chunk_alloc(__byte, __buffer_size);
        if (__buffer_size == 1)
            return reinterpret_cast<void*>(__chunk_ptr);

        /// Splice Many Block For Client !
        _Obj * __result = reinterpret_cast<_Obj*>(__chunk_ptr);
        _Obj * __current_block, *__next_block;
        _S_free_list_buffer[0 + FREELIST_INDEX(__byte)] = __next_block = (_Obj*)(__chunk_ptr + __byte);

        for (int i = 1; ; i++){
            __current_block = __next_block;
            __next_block = (_Obj*) ((char *)__current_block + __byte);
            /// Formulate As Embedded Pointer !
            if (i == __buffer_size - 1){
                __current_block->_S_next_free_list = nullptr;
                break;
            } else
                __current_block->_S_next_free_list = __next_block;
        }

        return reinterpret_cast<void*>(__result);
    }
    /// Allocate Raw Chunk Memory From malloc() ! ;
    char * __pool_alloc_base::__chunk_alloc(size_t __byte, int &__node) {

        char * __result;
        /// total size  :   byte of (_Tp) * 20  (default)
        size_t __total_size = __node * __byte;
        /// The Rest of Memory of Free List Buffer ! (Memory Pool)
        size_t __buffer_left = _S_free_end - _S_free_start;

        /// Splice 20 for Demand
        if (__buffer_left >= __total_size){
            __result = _S_free_start;
            _S_free_start += __total_size;
            return __result;
            /// Splice Less Than 20 But at least 1
        } else if (__buffer_left >= __byte){
            /// Splice All The Rest Of Memory to Respond
            __node = __buffer_left / __byte;
            __total_size = __node * __byte;
            __result = _S_free_start;
            _S_free_start += __total_size;
            return __result;
            /// Splice Less Than 1
        } else {
            /// Allocate New Memory's Size
            /// Additional-quantity : _S_heap_size / 16 and round_up to 8
            size_t __malloc_size = 2 * __total_size + ROUND_UP(_S_heap_size >> 4);
            /// Handle The Small Block !
            if (__buffer_left > 0){
                _Obj * __list_ptr = _S_free_list_buffer[0 + FREELIST_INDEX(__buffer_left)];
                reinterpret_cast<_Obj*>(_S_free_start)->_S_next_free_list = __list_ptr;
                _S_free_list_buffer[0 + FREELIST_INDEX(__buffer_left)] = reinterpret_cast<_Obj*>(_S_free_start);
            }
            /// Allocate New Memory
            _S_free_start = reinterpret_cast<char*>(malloc(__malloc_size));
            /// Out Of Memory
            if (_S_free_start == nullptr){
                _Obj *  __list_ptr = nullptr;
                for (int i = __byte; i <= __S_max_bytes; i+=__S_align_) {
                    __list_ptr = _S_free_list_buffer[0 + FREELIST_INDEX(i)];
                    /// Lend One Block Form Bigger Proper Chunk
                    if (__list_ptr != nullptr){
                        _S_free_list_buffer[0 + FREELIST_INDEX(i)] = __list_ptr->_S_next_free_list;
                        _S_free_start = reinterpret_cast<char*>(__list_ptr);
                        _S_free_end = _S_free_start + i;

                        /// Recursion itself to reset &__node
                        return (__chunk_alloc(__byte, __node));
                    }
                }
                /// Completely Run Out Of Memory
                /// Try To Use __default_pool_alloc::allocate To Handle
                /// May Be Throw Bad Alloc !
                _S_free_end = nullptr;
                _S_free_start = reinterpret_cast<char*>(__default_pool_alloc::allocate(__malloc_size));
            }
            /// Get New Memory Successfully !
            _S_heap_size += __malloc_size;
            _S_free_end = _S_free_start + __malloc_size;
            return (__chunk_alloc(__byte, __node));
        }
    }

    inline void __pool_alloc_base::__addition() {
        std::cout<<"addition-quantity : "<<_S_heap_size<<std::endl;
    }
    /// Allocate Static Memory To Data
     typename __pool_alloc_base::_Obj* __pool_alloc_base::_S_free_list_buffer[__S_buffer_size] = { };

     char * __pool_alloc_base::_S_free_start = nullptr;
     char * __pool_alloc_base::_S_free_end = nullptr;
     stl::size_t __pool_alloc_base::_S_heap_size = 0;

#define POOL_ALLOC_ADD_QU __std__::__pool_alloc_base::__addition();

    /// Implementation OF Standard allocator type of pool_allocator
    /// This Standard Allocator type adapt for stl::allocator traits
    /// Just a simple package for __pool_alloc_base !
    template<typename _Tp>
    class __pool_alloc : protected __pool_alloc_base {
    public:
        typedef _Tp                         value_type;
        typedef _Tp *                       pointer;
        typedef _Tp &                       reference;
        typedef const _Tp*                  const_pointer;
        typedef const _Tp&                  const_reference;
        typedef stl::size_t                 size_type;
        typedef __pool_alloc                allocator_type;

        template<typename _Tp1>
        struct rebind{
            typedef __pool_alloc<_Tp1> other;
        };

        __pool_alloc() _STL_NO_EXCEPTION {  }
        __pool_alloc(const __pool_alloc& ) _STL_NO_EXCEPTION {  }

        template<typename _Up>
        explicit __pool_alloc(const __pool_alloc<_Up>& ) _STL_NO_EXCEPTION {  }

        ~__pool_alloc() _STL_NO_EXCEPTION {  }

        /// Public Member Function
        size_type max_size() const _STL_NO_EXCEPTION {
            return size_t (-1) / sizeof(value_type);
        }
        pointer address(reference _val) const _STL_NO_EXCEPTION {
            return static_cast<pointer>(&_val);
        }
        const_pointer address(const_reference _val) const _STL_NO_EXCEPTION{
            return static_cast<const_pointer>(&_val);
        }
        /// Essential API
        pointer allocate(size_t __n) const {
            if (__n > this->max_size())
                throw std::bad_alloc{ };
            return reinterpret_cast<pointer>
            (__pool_alloc_base::__allocate(sizeof(value_type) * __n));
        }
        void deallocate(pointer __ptr, size_type __n){
            __pool_alloc_base::__deallocate(reinterpret_cast<void*>(__ptr),
                                            sizeof(value_type) * __n);
        }
        template<typename _Up, typename ..._Args>
        inline void construct(_Up * __p, _Args&& ...args){
            new (static_cast<void*>(__p)) _Up(std::forward<_Args>(args)...);
        }
        void destroy(pointer __p){
            __p -> ~value_type();
        }
     };
}


#endif //STL2_0_POOL_ALLOCATOR_H
