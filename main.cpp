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
#include <memory>

#include "include/iterator.h"
#include "include/memory.h"
#include "include/allocator.h"

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

        for (int i = 0; i < 10; ++i){
            std::cout<<(group2[i])<<" ";
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

int main(int argc, char ** argv){

    ///memory_test_unit::_memory_test_unit();
    ///construct_test_unit::construct_test();
    ///allocator_test_unit::new_allocator_test();
    construct_test_unit::uninitialized_test();

    return 0;
}