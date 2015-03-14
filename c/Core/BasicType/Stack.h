#ifndef GX_STACK_H__
#define GX_STACK_H__

#include <stack>
#include <algorithm>

namespace GX
{
    template<typename ValueType>
    class Stack : public std::stack<ValueType>
    {
    private:
        typedef std::stack<ValueType> BaseType;
    public:
        typedef typename BaseType::size_type SizeType;

        Stack()
        : BaseType()
        {}
    };
}

#endif // GXLIST_H__
