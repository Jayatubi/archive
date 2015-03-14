#ifndef GX_STRINGHASH_H
#define GX_STRINGHASH_H

namespace GX
{
    class StringHash
    {
    public:
        template <U32 N, U32 I>
        struct HashHelper
        {
            __attribute__((always_inline))
            constexpr static U32 Calculate(const Char (&str)[N])
            {
                return (HashHelper<N, I - 1>::Calculate(str) ^ (str[I - 1] & 0xFF)) * StringHash::PRIME;
            }
        };

        template <U32 N>
        struct HashHelper<N, 1>
        {
            __attribute__((always_inline))
            constexpr static U32 Calculate(const Char (&str)[N])
            {
                return (StringHash::OFFSET ^ (str[0] & 0xFF)) * StringHash::PRIME;
            }
        };

        template<U32 N>
        __attribute__((always_inline))
        constexpr static U32 StaticHash(const Char (&str)[N])
        {
            return HashHelper<N, N>::Calculate(str);
        }

        template<U32 N>
        __attribute__((always_inline))
        explicit StringHash(const Char (&str)[N])
        : m_hash(HashHelper<N, N>::Calculate(str))
        {}

        operator U32()
        {
            return GetHash();
        }

        U32 GetHash()
        {
            return m_hash;
        }

        static U32 CalculateHash(const Char* pStr)
        {
            U32 result = OFFSET;

            const Char* pStrCalc = pStr;
            while(*pStrCalc != 0)
            {
                result = (result ^ (*pStrCalc & 0xFF)) * PRIME;
                ++pStrCalc;
            }
            return result * PRIME;
        }

        constexpr static U32 CalculateHash(const Char* pStr, U32 index, U32 length)
        {
            return index == 0 ?
                ((pStr[0] & 0xFF) ^ OFFSET) * PRIME :
                ((index != length ? (pStr[index] & 0xFF) : 0) ^ CalculateHash(pStr, index - 1, length)) * PRIME;
        }

        static const U32 OFFSET = 0x01234567;
        static const U32 PRIME = 0x89ABCDEF;
        
    private:
        U32 m_hash;
    };
}

constexpr GX::U32 operator "" _hash(const char * pStr, std::size_t length)
{
    return GX::StringHash::CalculateHash(pStr, length, length);
}

#define GX_STRING_HASH(String) GX::StringHash::CalculateHash(String)
#define GX_STRING_HASH_STATIC(String) GX::StringHash::StaticHash(String)

#endif
