//
// Created by 11508 on 2023-07-11.
//

#ifndef STL2_0_STL_QUEUE_H
#define STL2_0_STL_QUEUE_H

#include "./stl_deque.h"

namespace stl{

    template<typename _Tp, typename _Sequence = stl::deque<_Tp>>
    class queue;

    template<typename _Tp1, typename _Sequence1>
    inline bool operator==(const queue<_Tp1, _Sequence1>& __x, const queue<_Tp1, _Sequence1>& __y);

    template<typename _Tp1, typename _Sequence1>
    inline bool operator<(const queue<_Tp1, _Sequence1>& __x, const queue<_Tp1, _Sequence1>& __y);

    /// The Implementation Of Queue
    /// Fist-In-Fist-Out Sequence ! FIFO Structure
    template<typename _Tp, typename _Sequence>
    class queue{
        template<typename _Tp1, typename _Sequence1>
        friend bool operator==(const queue<_Tp1, _Sequence1>& __x, const queue<_Tp1, _Sequence1>& __y);

        template<typename _Tp1, typename _Sequence1>
        friend bool operator<(const queue<_Tp1, _Sequence1>& __x, const queue<_Tp1, _Sequence1>& __y);
    protected:
        _Sequence _M_I_sequence;

    public:
        queue() : _M_I_sequence( ) {  };
        queue(const _Sequence& __other) : _M_I_sequence(__other) {  };
        queue(_Sequence&& __other) : _M_I_sequence(std::move(__other)) {  };
        ~queue() = default;

    public:
        typedef typename _Sequence::value_type   value_type;
        typedef typename _Sequence::pointer      pointer;
        typedef typename _Sequence::size_type    size_type;
        typedef typename _Sequence::reference    reference;
        typedef typename _Sequence::difference_type  difference_type;
        typedef typename _Sequence::const_pointer   const_pointer;
        typedef typename _Sequence::const_reference const_reference;
    public:
        bool empty() {  return _M_I_sequence.empty();  }
        size_type size() const {  return _M_I_sequence.size();  }
        void display(bool flag) const {  _M_I_sequence.display(flag);  }

        reference front() { return _M_I_sequence.front(); }
        const_reference front() const { return _M_I_sequence.front(); }
        reference back() {  return _M_I_sequence.back();  }
        const_reference back() const { return _M_I_sequence.back(); }

        void push(const value_type& __val) {  _M_I_sequence.push_back(__val);  }
        void push(value_type&& __val) {  _M_I_sequence.push_back(std::move(__val)); }

        template<typename... Args>
        void emplace(Args&&...args) {  _M_I_sequence.emplace_back(std::forward<Args>(args)...); }

        void pop() {  _M_I_sequence.pop_front();  }
    };
    template<typename _Tp1, typename _Sequence1>
    inline bool operator==(const queue<_Tp1, _Sequence1>& __x, const queue<_Tp1, _Sequence1>& __y){
        return (__x._M_I_sequence == __y._M_I_sequence);
    }
    template<typename _Tp1, typename _Sequence1>
    inline bool operator!=(const queue<_Tp1, _Sequence1>& __x, const queue<_Tp1, _Sequence1>& __y){
        return !(__x == __y);
    }
    template<typename _Tp1, typename _Sequence1>
    inline bool operator<(const queue<_Tp1, _Sequence1>& __x, const queue<_Tp1, _Sequence1>& __y){
        return (__x._M_I_sequence < __y._M_I_sequence);
    }
    template<typename _Tp1, typename _Sequence1>
    inline bool operator>(const queue<_Tp1, _Sequence1>& __x, const queue<_Tp1, _Sequence1>& __y){
        return __y < __x;
    }
    template<typename _Tp1, typename _Sequence1>
    inline bool operator<=(const queue<_Tp1, _Sequence1>& __x, const queue<_Tp1, _Sequence1>& __y){
        return !(__x > __y);
    }
    template<typename _Tp1, typename _Sequence1>
    inline bool operator>=(const queue<_Tp1, _Sequence1>& __x, const queue<_Tp1, _Sequence1>& __y){
        return !(__x < __y);
    }
}
#endif //STL2_0_STL_QUEUE_H
