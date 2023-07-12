//
// Created by 11508 on 2023-07-11.
//

#ifndef STL2_0_STL_STACK_H
#define STL2_0_STL_STACK_H

#include "./stl_deque.h"

namespace stl{

    template<typename _Tp, typename _Sequence = stl::deque<_Tp>>
    class stack;

    template<typename _Tp1, typename _Sequence1>
    bool operator==(const stack<_Tp1, _Sequence1>& __x, const stack<_Tp1, _Sequence1>& __y);

    template<typename _Tp1, typename _Sequence1>
    inline bool operator<(const stack<_Tp1, _Sequence1>& __x, const stack<_Tp1, _Sequence1>& __y);

    /// The Implementation Of Stack !
    /// First-In-Last-Out Sequence FILO Structure !
    template<typename _Tp, typename _Sequence>
    class stack {
        template<typename _Tp1, typename _Sequence1>
        friend bool operator==(const stack<_Tp1, _Sequence1>& __x, const stack<_Tp1, _Sequence1>& __y);

        template<typename _Tp1, typename _Sequence1>
        friend bool operator<(const stack<_Tp1, _Sequence1>& __x, const stack<_Tp1, _Sequence1>& __y);
    protected:
        /// The Default Inner Adapter Container is stl::deque
        _Sequence _M_i_sequence;
    public:
        typedef typename _Sequence::value_type   value_type;
        typedef typename _Sequence::pointer      pointer;
        typedef typename _Sequence::size_type    size_type;
        typedef typename _Sequence::reference    reference;
        typedef typename _Sequence::difference_type  difference_type;
        typedef typename _Sequence::const_pointer   const_pointer;
        typedef typename _Sequence::const_reference const_reference;
    public:
        stack() : _M_i_sequence()  {  };
        stack(const _Sequence& __seq) : _M_i_sequence(__seq) {  };
        stack(_Sequence&& __seq) : _M_i_sequence(std::move(__seq)) {  };
        ~stack() = default;

    public:
        bool empty() {  return _M_i_sequence.empty();  }
        size_type size() const {  return _M_i_sequence.size();  }
        void display(bool flag) const {  _M_i_sequence.display(flag);  }

        reference top() { return _M_i_sequence.back(); }
        const_reference top() const { return _M_i_sequence.back(); }

        void push(const value_type& __val) {  _M_i_sequence.push_back(__val);  }
        void push(value_type&& __val) {  _M_i_sequence.push_back(std::move(__val)); }

        template<typename... Args>
        void emplace(Args&&...args) {  _M_i_sequence.emplace_back(std::forward<Args>(args)...); }

        void pop() {  _M_i_sequence.pop_back();  }
    };

    template<typename _Tp1, typename _Sequence1>
    inline bool operator==(const stack<_Tp1, _Sequence1>& __x, const stack<_Tp1, _Sequence1>& __y){
        return (__x._M_i_sequence == __y._M_i_sequence);
    }
    template<typename _Tp1, typename _Sequence1>
    inline bool operator!=(const stack<_Tp1, _Sequence1>& __x, const stack<_Tp1, _Sequence1>& __y){
        return !(__x == __y);
    }
    template<typename _Tp1, typename _Sequence1>
    inline bool operator<(const stack<_Tp1, _Sequence1>& __x, const stack<_Tp1, _Sequence1>& __y){
        return __x._M_i_sequence < __y._M_i_sequence;
    }
    template<typename _Tp1, typename _Sequence1>
    inline bool operator>(const stack<_Tp1, _Sequence1>& __x, const stack<_Tp1, _Sequence1>& __y){
        return __y < __x;
    }
    template<typename _Tp1, typename _Sequence1>
    inline bool operator<=(const stack<_Tp1, _Sequence1>& __x, const stack<_Tp1, _Sequence1>& __y){
        return !(__x > __y);
    }
    template<typename _Tp1, typename _Sequence1>
    inline bool operator>=(const stack<_Tp1, _Sequence1>& __x, const stack<_Tp1, _Sequence1>& __y){
        return !(__x < __y);
    }
}
#endif //STL2_0_STL_STACK_H
