#ifndef GXFIGHTER_GXBITSET_H
#define GXFIGHTER_GXBITSET_H

#include "BasicType.h"
#include "Math.h"
#include "Assert.h"

namespace GX
{
    class BitsetProxy
    {
    public:
        BitsetProxy(const U8* pData, U32 bitIndex)
            : m_pData(const_cast<U8*>(pData))
            , m_bitIndex(bitIndex)
        {}

        operator bool() const
        {
            U32 byteIndex = m_bitIndex / 8;
            U32 bitIndex = m_bitIndex % 8;
            U8 mask = static_cast<U8>(1 << bitIndex);

            return (m_pData[byteIndex] & mask) != 0;
        }

        BitsetProxy& operator=(bool flag)
        {
            U32 byteIndex = m_bitIndex / 8;
            U32 bitIndex = m_bitIndex % 8;
            U8 mask = static_cast<U8>(1 << bitIndex);

            if (flag) m_pData[byteIndex] |= mask;
            else m_pData[byteIndex] &= ~mask;

            return *this;
        }

    private:
        U8* m_pData;
        U32 m_bitIndex;
    };

    template<int BitCount>
    class Bitset
    {
    public:
        Bitset()
        {
            for(U32 i = 0; i < ByteSize; i++) m_data[i] = 0;
        }

        ~Bitset()
        {
        }
        
        BitsetProxy operator[](U32 bitIndex) const
        {
            GX_ASSERT(bitIndex < BitCount, "Out of range: %u", bitIndex);
            return BitsetProxy(m_data, bitIndex);
        }

        template<typename ValueType>
        operator ValueType()
        {
            ValueType result;
            static const U32 ValueSize = sizeof(ValueType);

            U8* pAccessor = static_cast<U8*>(static_cast<void*>(&result));
            for(U32 i = 0; i < ValueSize; i++)
            {
                pAccessor[i] = i < ByteSize ? m_data[i] : 0;
            }

            return result;
        }

        template<typename ValueType>
        Bitset& operator=(const ValueType& data)
        {
            U32 srcSize = min<U32>(sizeof(ValueType), sizeof(m_data));

            const U8* pAccessor = reinterpret_cast<const U8*>(&data);

            for(U32 i = 0; i < srcSize; i++)
            {
                m_data[i] = pAccessor[i];
            }

            return *this;
        }
    private:
        static const U32 ByteSize = (BitCount + 7) / 8;
        U8 m_data[ByteSize];
    };
}

#endif
