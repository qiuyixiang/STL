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

/// Debugger Option
///#define DEBUGGER
///#define VECTOR_DBG
///#define LIST_MEMORY_DEBUGGER

#include <iostream>
#include <iterator>
#include <vector>
#include <functional>
#include <memory>
#include <deque>
#include <list>
#include <forward_list>

#include "include/iterator.h"
#include "include/memory.h"
#include "include/algorithm.h"
#include "include/functional.h"
#include "include/vector.h"
#include "include/list.h"
#include "include/forward_list.h"

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

        typedef stl::allocator_traits<stl::allocator<int>>::rebind_alloc<double> rebindAllocType;
        rebindAllocType alloc;
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
        int a = 10, b = 20;
        std::cout<<a<<" "<<b<<" "<<std::endl;
        stl::swap(a, b);
        std::cout<<a<<" "<<b<<" "<<std::endl;
        stl::pair<int, int>pair1 = stl::make_pair(10, 10);
        stl::pair<int, int>pair2 = stl::make_pair(20, 20);
        stl::swap(pair1, pair2);
        std::cout<<pair2.first<<" "<<pair2.second<<std::endl;
    }
}

/// sequence container test unit
/// use Macro DISPLAY and DISPLAY_DBG
namespace sequence_container_test{

    class Container_class {
    public:
        int _cs;
        std::string _ifn;

        Container_class(int cs, const std::string& ifn) : _cs(cs), _ifn(ifn) {  }
        ~Container_class() = default;

    };
    /// test for vector
    namespace vector_test{
        void vector_test_unit1(){
            std::vector<int>std_vector = {1,2,3,4,5,6,7,8};
            stl::allocator<int>allocator;

            ///int * ptr = alloc.allocate(1);
            __std__::_Vec_Base<int, stl::allocator<int>>vecBase;
            vecBase.get_Tp_allocator();
            std::allocator<int>allocator1;
            ///allocator1.deallocate();
            std_vector.begin();
            std_vector.back();
            std_vector.empty();
            stl::vector<int>vector(10);
            std::cout<<std::endl;
            vector.display(true);
            stl::vector<int>vector1(10, 10);
            vector1.display(true);
            std::cout<<vector1.front()<<" "<<vector1.back()<<std::endl;
            stl::vector<int>vector2 = {1,2,3,4,5,6,7,8};
            vector2.display(true);
            stl::vector<double>vector3(10);
            std::cout<<vector2.max_size()<<" "<<vector3.max_size()<<std::endl;
            stl::vector<int>vector4(vector2);
            vector4.display(true);
        }

        void vector_test_unit2(){
            stl::vector<int>std_vector(10, 5);
            stl::vector<int>std_vector1(std::move(std_vector));

            std_vector1.display(true);
            std_vector.display(true);

            stl::vector<int>vector = {1,2,3,4,5,6,7};
            stl::vector<int>vector1;
            vector = std::move(vector1);

            vector.display(true);
            vector1.display(true);

            std::vector<int>vector2 = {1,2,3,4,5,6,7};
            std::vector<int>vector3;

            vector3 = std::move(vector2);
            DISPLAY_DBG(vector2);
            std::cout<<vector2.capacity()<<std::endl;
            stl::vector<int>vector4 = {1,2,3,4,5,6,7};
            stl::vector<int>vector5;
            vector5 = std::move(vector4);
            vector5.display(true);
            vector4.display(true);

            stl::vector<int>vector6;
            vector6 = {1,2,3,4,5,6,7,8};
            vector6.display(true);
            vector6 = stl::vector<int>();
            vector6.display(true);

            std::vector<int>vector7;
            int number = 100;
            vector7.push_back(10);
            vector7.push_back(number);
            vector7.emplace_back(100);
        }

        void vector_test_unit3(){
            stl::vector<int>group;
            group.push_back(10);
            group.push_back(20);
            group.emplace_back(30);
            group.emplace_back(40);
            group.emplace_back(50);

            stl::vector<Container_class> group_cl;
            group_cl.emplace_back(10 ,"Hello");
            std::cout<<group_cl.size()<<std::endl;
            std::cout<<group_cl[0]._cs<<" "<<group_cl[0]._ifn<<std::endl;
            group_cl.push_back(Container_class(10, "Test"));
            std::cout<<group_cl.size()<<" "<<group_cl.capacity()<<std::endl;
            std::cout<<BREAK<<std::endl;
            stl::vector<int>hr = {1,2,3,4,5,6,7,8};
            hr.erase(hr.begin() + 3);
            hr.display(true);
            hr.pop_back();
            hr.display(true);
            hr.erase(hr.begin() + 1, hr.begin() + 3);
            hr.display(true);
            std::vector<int>any = {1,2,3};
            any.shrink_to_fit();

            any.insert(any.begin() + 1, 5, 6);
        }
        void vector_test_unit4(){
            std::vector<int>group = {1,2,3,4,5,6,7,8,9,10};
            std::vector<int>group1(group.size());

            group.shrink_to_fit();

            auto result = std::copy_backward(group.begin(), group.end(), group1.end());
            std::cout<<*result<<std::endl;
            DISPLAY(group1.begin(), group1.end());
            ///std::cout<<BREAK<<std::endl;

            stl::vector<int>group2 = {1,2,3,4,5,6,7,8,9,10};
            stl::vector<int>group3(group2.begin(), group2.end());
            group3.display(true);
            stl::vector<int>group4(group.begin(), group.end());
            group4.display(true);
            std::cout<<BREAK<<std::endl;

            group.insert(group.begin() + 3, 3, 4);
            DISPLAY_DBG(group);
            std::cout<<BREAK<<std::endl;

            group4.push_back(11);
            group4.display(true);
            group4.insert(group4.begin() + 3, 3, 4);
            group4.display(true);

            group4.insert(group4.begin() + 3, 21, 4);
            group4.display(true);

            group4.push_back(100);
            group4.display(true);

            std::cout<<BREAK<<BREAK<<std::endl;

            stl::vector<char>v_char = {'q', 'y', 'x'};
            stl::vector<char>v_char1;
            v_char1.insert(v_char1.begin(), v_char.begin(), v_char.end());
            v_char1.display(true);
            v_char1.push_back('x');
            v_char1.push_back('x');
            v_char1.push_back('x');
            v_char1.push_back('x');
            v_char1.display(true);
            v_char1.insert(v_char1.begin() + 1, v_char.begin(), v_char.end());
            v_char1.display(true);
            char temp = 's';
            v_char1.insert(v_char1.end(), temp);
            v_char1.display(true);
            v_char1.insert(v_char1.end(), std::initializer_list<char>{'d', 'w'});
            v_char1.display(true);
            std::cout<<BREAK<<BREAK<<BREAK<<std::endl;
            stl::vector<int>groups = {1,2,3,4,5,6,7,8,9,10};
            groups.insert(groups.begin() + 2, 3);
            groups.display(true);
            groups.insert(groups.begin() + 2, 3);
            groups.display(true);

            groups.shrink_to_fit();
            groups.display(true);
            groups.resize(10);
            groups.display(true);
            groups.resize(15, 9);
            groups.display(true);
        }
    }

    /// test for deque
    namespace deque_test{

    }

    /// test for list
    namespace list_test{
        void list_test_unit1(){
            std::list<int>group;
            int number = 100;
            std::list<int>::pointer ptr = &number;
            group.begin();
            stl::list<int>groups;
            groups.display();
            group.push_back(100);
            std::cout<<groups.back()<<std::endl;
            std::cout<<groups.front()<<std::endl;
            std::cout<<BREAK<<std::endl;
            groups.push_back(100);
            groups.push_back(number);
            groups.emplace_back(1000);
            groups.push_front(10);
            groups.emplace_front(1);
            auto Iter = groups.begin();
            stl::advance(Iter, 3);
            groups.insert(Iter, 99);
            groups.insert(stl::list<int>::advance(groups.begin(), 3), 9);
            groups.display();

            stl::list<int>group1 = {1,2,3,4,5,6,7,8,9};
            group1.display();
            ///group = std::initializer_list<int>{1,2,3,4,5,6,7};
            group1.erase(group1.begin());
            group1.display();
        }
        void list_test_unit2(){
            stl::list<int>list1 = {1,2,3,4,5,6};
//            list1.clear();
//            list1.display();

            std::list<int>group = {1,2,3,4,5,6,7};
            std::list<int>group1;
            group1 = std::move(group);

            stl::list<int>list2 = std::move(list1);
            list1.display();
            list2.display();
            std::cout<<BREAK<<std::endl;

            stl::list<int>list3;
            list3 = std::move(list2);
            list3.display();
            list2.display();
            std::cout<<BREAK<<std::endl;

            stl::list<int>list4 = {1,2,2,2,3,3,4,5};
            list4.display();
            list4.remove(2);
            list4.display();
            std::cout<<BREAK<<std::endl;

            stl::list<int>list5 = {1,2,2,2,3,3,4,5,5,6};
            list5.display();
            list5.unique();
            list5.display();
            std::cout<<BREAK<<std::endl;

            stl::list<int>list = {1,1,1,2,2,3,4,5,5,6,6,7};
            list.unique();
            list.display();
        }
        void list_test_unit3(){
            stl::list<int>list = {1,2,3,4,5};
            stl::list<int>list1 = {6,7,8,9,10};

            std::list<int>list2 = {1,2,3,4,5,6};
            list2.sort();
            list1.splice(list1.begin(), list);
            list.display();
            list1.display();

            stl::list<int>list3 = {1,2,3,4,5};
            list1.splice(list1.end(), list3, list3.begin(),
                         stl::list<int, stl::allocator<int>>::advance(list3.begin(), 3));
            list1.display();
            list3.display();
            list2.sort();
            std::cout<<BREAK<<std::endl;

            stl::list<int>group = {1,2,3,4,5,6,7};
            stl::list<int>group1 = group;
            group1.display();
            group1.splice(group1.begin(), group, group.begin());
            group.display();
            group1.display();
        }
        void list_test_unit4(){
            std::list<int>list = {1,2,3,4,5,6};
            /// 1,3,5,7,9   first1
            /// 2,4,6,8,10  first2
            stl::list<int>list1 = {1,3,5,7,9};
            stl::list<int>list2 = {2,4,6,8,10};

            list2.merge(list1);
            list2.display();
            list1.display();
            list2.reverse();
            list2.display();
            std::cout<<BREAK<<std::endl;

            stl::list<int>group = {2,5,1,3,4,8,7,9};
            group.sort();
            group.display();
            std::cout<<BREAK<<std::endl;

            stl::list<int>list3 = {3,6,8,7,2,3,4,9,8,1};
            list3.sort();
            list3.display();
            stl::list<int>list4 = {1,1,1};
            list4.swap(list3);
            list4.display();
            list3.display();
        }
    }

    ///test for forward_list
    namespace forward_list_test{
        void forward_list_test_unit1(){
            std::forward_list<int>forwardList = {1,2,3,4,5,6,7};
            forwardList.before_begin();
            stl::forward_list<int>forwardList1;
            forwardList1.display(true);
            std::cout<<stl::allocator<int>().max_size()<<std::endl;
            std::cout<<forwardList1.max_size()<<std::endl;
            std::cout<<stl::allocator<double>().max_size()<<std::endl;
            forwardList.pop_front();
            std::cout<<BREAK<<std::endl;
            forwardList1.push_front(10);
            forwardList1.push_front(0);
            forwardList1.display(true);
            std::cout<<BREAK<<std::endl;
            stl::forward_list<int>forwardList2 = {1,2,3,4,5,6};
            forwardList2.display(true);
            std::cout<<std::endl;
            auto Iter = forwardList2.erase_after(forwardList2.before_begin());
            forwardList2.display(true);
            std::cout<<*Iter<<std::endl;
            std::cout<<forwardList2.front()<<std::endl;
            std::cout<<std::boolalpha<<forwardList2.empty()<<std::endl;
            stl::forward_list<int>forwardList3;
            std::cout<<std::boolalpha<<forwardList3.empty()<<std::endl;
        }
        void forward_list_test_unit2(){
            stl::forward_list<int>list = {1,2,3,4,5,6,7,8};
            list.clear();
            list.display(true);
            std::forward_list<int>list1 = {1,2,3,4,5,6};
            std::forward_list<int>list2({1,2,3,4,5,6});
            list1 = list2;
            std::cout<<BREAK<<std::endl;

            stl::forward_list<int>group = {1,2,3,4,5,6,7};
            stl::forward_list<int>group1(std::move(group));
            group1.display(true);
            group.display(true);
            group.swap(group1);
            group.display(true);
            group1.display(true);
            std::cout<<BREAK<<std::endl;
            stl::forward_list<int>list3;
            stl::forward_list<int>list4 = {1,2,3,4,5,6};
            list3.assign(list4.begin(), list4.end());
            list3.display(true);
            list4.display(true);
            list1.reverse();
            list1.remove(10);
            std::cout<<BREAK<<std::endl;
            stl::forward_list<int>list5 = {1,2,3,4,5,6,7,8};
            list5.display(true);
            list5.reverse();
            list5.display(true);
        }
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
    ///functor_test::functor_mem_test();

    ///sequence_container_test::vector_test::vector_test_unit1();
    ///sequence_container_test::vector_test::vector_test_unit2();
    ///sequence_container_test::vector_test::vector_test_unit3();
    ///sequence_container_test::vector_test::vector_test_unit4();

    ///sequence_container_test::list_test::list_test_unit1();
    ///sequence_container_test::list_test::list_test_unit2();
    ///sequence_container_test::list_test::list_test_unit3();
    ///sequence_container_test::list_test::list_test_unit4();

    ///sequence_container_test::forward_list_test::forward_list_test_unit1();
    sequence_container_test::forward_list_test::forward_list_test_unit2();
    return 0;
}