/**
 * C++ Standard Library
 * Based On GNU Glibc
 * Based On C++ 11
 *
 * @CopyRight : qiuyixiang
 * Create on 2023-5-19
 *
 * Main Source (Header File ) ./include
 * The Content is divided into different proportions
 *
 * Test Unit For Different Parts in ./testunit
 * In Here you can see some samples to test this library
 * Tiny C++ Library base on C++ Standard Library
 * And add some components such as AVL_tree, hash_table, tuple and so on
 *
 *
 * This file is Just a explanation of the whole project
 * No entry point of this application
 *
 * the source file version : 2.0  (complete version )
 * the release static library version : 1.1 (.lib)
 *
 * you can download this file for studying but not been commercial !!!
 *
 * Reading More In The Next Source File
 *
 * My namespace for public stl::
 * Recommended to use stl::
 * for Private Implementation __std__::
 *
 * These Standard Memory or Container Library Depended on std::cin, std::cout
 * (basic classic input output !)
 *
 * Finish on : Unknown
 * Report Bug Here :
 *
 *     #
 *     #
 *     #
 */


/// Test Unit Migrate Here

/// Debugger Entry
#define DEBUGGER

#include <iostream>
#include <iterator>
#include <vector>
#include <functional>
#include <memory>

#include "include/iterator.h"
#include "include/memory.h"
#include "include/allocator.h"
#include "include/functional.h"

namespace memory_test_unit{
    void my_new_handler(){
        std::cerr<<"Error Out of Memory"<<std::endl;
        exit(2);
    }
    void _memory_test_unit(){
        ///::operator new()
        std::set_new_handler(&my_new_handler);
        stl::_new_del::operator new(size_t(-1));

        /// No throw operator new
        void * __ptr = stl::_new_del::operator new(size_t(-1), stl::no_throw { });
        if (__ptr == nullptr){
            std::cerr<<"nullptr catch Error !"<<std::endl;
        }
        stl::_new_del::operator delete(__ptr);
    }
}

namespace construct_test_unit{

    void construct_test(){
        int * _ptr = (int *)stl::_new_del::operator new(10 * sizeof(int ));
        int * _Cur = _ptr;
        for (int i = 0; i < 10; ++i) {
            stl::_Construct(_Cur, i);
            ++_Cur;
        }
        for (int i = 0; i < 10; ++i) {
            std::cout<<*(_ptr + i)<<" ";
        }
        std::cout<<std::endl;
        stl::_Destroy(_ptr, _ptr + 10);
        stl::_new_del::operator delete(_ptr);
    }

    void uninitialized_test(){
        //std::uninitialized_copy_n()
        int group1[10] = {1,2,3,4,5,6,7,8,9,10};
        int group2[10];

        int *_end = stl::uninitialized_copy_n(group1, 10, group2);
        std::cout<<(*_end)<<" "<<*(_end - 1)<<std::endl;

        for (int & i : group2){
            std::cout<<i<<" ";
        }
        std::cout<<std::endl;
    }
}
namespace allocator_test_unit{

    void new_allocator_test(){
        ///std::allocator<int> allocator;
        int number = 100;
        stl::allocator<int>allocator;
        std::cout<<*(allocator.address(number))<<std::endl;

        stl::allocator_traits<stl::allocator<int>>::rebind_alloc<double> allocator1;
        double * ptr = allocator1.allocate(1);
        stl::allocator_traits<stl::allocator<int>>::allocate(allocator, 10);
    }
}
namespace functor_test{
    void functor_test(){
        ///std::plus<>(10, 20);
        std::cout<<stl::plus<>()(10, 3.2342)<<std::endl;
        stl::plus<int>()(10, 10);
        std::cout<<stl::negate<>()(-34.3424)<<std::endl;
        ///std::back_inserter()
    }
    class functor_{
    public:
        explicit constexpr functor_() {  };
        void __display() {
            std::cout<<"Member Function Test"<<std::endl;
        }
    };
    void functor_mem_test(){
        functor_test::functor_ func;
        stl::mem_fun_t<functor_, void>memFun(&functor_::__display);
        auto ptr1 = std::mem_fn(&functor_::__display);
        ptr1(&func);
        auto ptr2 = stl::mem_fun(&functor_::__display);
        ptr2(&func);
    }
}

namespace iterator_test{
    void inserter_iterator_test(){
        ///std::back_inserter()
        std::vector<int>group = {1,2,3,4,5,6,7};
        ///std::cout<<*group.insert(group.begin(), 0)<<std::endl;
        int number = 100;
        stl::__normal_iterator<int*>normalIterator(&number);
        stl::__normal_iterator<int*>normalIterator1(normalIterator);
        std::cout<<*(normalIterator1.base())<<std::endl;
        DISPLAY(group.begin(), group.end());
        DISPLAY_DBG(group);
    }
    void reverse_iterator_test(){
        stl::reverse_iterator<int*>reverseIterator;
        stl::reverse_iterator<double*>reverseIterator1;
        ///stl::reverse_iterator<int*>reverseIterator2(reverseIterator1);
        std::vector<int>group = {1,2,3,4,5,6,7};
        stl::reverse_iterator<std::vector<int>::iterator>reverseIterator2(group.end());
        stl::reverse_iterator<std::vector<int>::iterator>reverseIterator3(group.begin());
        for ( ; reverseIterator2 != reverseIterator3; ++reverseIterator2)
            std::cout<<*reverseIterator2<<" ";
        std::cout<<std::endl;

    }

    void stream_iterator_test(){
        std::istream_iterator<int>istreamIterator;
        stl::istream_iterator<int>istreamIterator1;
        stl::istream_iterator<int>istreamIterator2;
        std::cout<<std::boolalpha<<(istreamIterator1 != istreamIterator2)<<std::endl;
        ++istreamIterator1;
        std::cout<<*istreamIterator1<<std::endl;
        stl::ostream_iterator<std::string>ostreamIterator(std::cout, "\n");
        ostreamIterator = "Hello ostream Iterator !";
    }
}
namespace utility_test{

    void pair_test(){
        ///std::pair<>
        auto pairs = stl::make_pair("Hello World ", 10);
        std::cout<<pairs.first<<" "<<pairs.second<<std::endl;
        ///std::mem_fn()
    }
}
int main(int argc, char ** argv){

    ///memory_test_unit::_memory_test_unit();
    ///construct_test_unit::construct_test();
    ///allocator_test_unit::new_allocator_test();
    ///construct_test_unit::uninitialized_test();
    ///functor_test::functor_test();
    ///iterator_test::inserter_iterator_test();
    ///iterator_test::reverse_iterator_test();
    ///iterator_test::stream_iterator_test();
    ///utility_test::pair_test();
    functor_test::functor_mem_test();

    return 0;
}