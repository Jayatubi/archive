#ifndef GX_MEMORYPOOL_H
#define GX_MEMORYPOOL_H

namespace GX
{
    template<U32 DataSize, U32 ThunkSize>
    class MemoryPoolImpl
    {
    public:
        union ThunkNode
        {
            U8  m_buffer[DataSize];
            U32 m_nextSlot;
        };

        struct Thunk
        {
        public:
            Thunk()
            : m_head(0)
            {
                for(U32 i = 0; i < ThunkSize; i++)
                {
                    m_data[i].m_nextSlot = i < ThunkSize - 1 ? i + 1 : ~0;  // Consider the right sibling as the next valid slot
                }
            }

            ThunkNode* acquire()
            {
                ThunkNode* pResult = nullptr;

                if (m_data[m_head].m_nextSlot != ~0)
                {
                    pResult = m_data + m_head;
                    // Move head
                    m_head = pResult->m_nextSlot;
                }

                return pResult;
            }

            void release(ThunkNode* pNode)
            {
                if (pNode != nullptr)
                {
                    pNode->m_nextSlot = m_head;
                    m_head = pNode - m_data;
                }
            }

            void release(U8* pValue)
            {
                release(reinterpret_cast<ThunkNode*>(pValue));
            }

            bool owns(ThunkNode* pNode)
            {
                return pNode >= m_data && pNode < m_data + ThunkSize;
            }

        public:
            ThunkNode m_data[ThunkSize];
            U32 m_head;
        };

    public:
        MemoryPoolImpl()
        : m_pActiveThunk(nullptr)
        {}

        U8* acquire()
        {
            U8* pResult;
            ThunkNode* pNode = nullptr;

            if (m_pActiveThunk != nullptr)
            {
                pNode = m_pActiveThunk->acquire();
            }

            if (pNode == nullptr)
            {
                for(Thunk& theThunk : m_thunks)
                {
                    if (m_pActiveThunk != &theThunk)
                    {
                        pNode = theThunk.acquire();
                        if (pNode != nullptr)
                        {
                            m_pActiveThunk = &theThunk;
                            break;
                        }
                    }
                }
            }

            if (pNode == nullptr)
            {
                m_pActiveThunk = &addThunk();
                pNode = m_pActiveThunk->acquire();
            }

            if (pNode != nullptr)
            {
                pResult = pNode->m_buffer;
            }
            return pResult;
        }

        void release(ThunkNode* pNode)
        {
            bool succeed = false;
            if (pNode != nullptr)
            {
                for(Thunk& thunk : m_thunks)
                {
                    if (thunk.owns(pNode))
                    {
                        thunk.release(pNode);
                        succeed = true;
                        break;
                    }
                }
            }

            GX_ASSERT(succeed, "Releasing invalid pointer via MemoryPool");
        }

        void release(U8* pValue)
        {
            release(reinterpret_cast<ThunkNode*>(pValue));
        }

        Thunk& addThunk()
        {
            m_thunks.emplace_back();
            
            return *m_thunks.rbegin();
        }
        
    private:
        List<Thunk> m_thunks;
        Thunk*      m_pActiveThunk;
    };

    template<U32 DataSize>
    class MemoryPoolImpl<DataSize, 1>
    {
        U8* acquire()
        {
            return new U8[DataSize];
        }

        void release(U8* pValue)
        {
            if (pValue != nullptr)
            {
                delete [] pValue;
            }
        }
    };

    template<int DataSize, int ThunkSize = 0x80000 / DataSize>
    struct MemoryPool : public MemoryPoolImpl<DataSize, ThunkSize>
    {
        static MemoryPool s_pool;
    };

    template<int DataSize, int ThunkSize>
    MemoryPool<DataSize, ThunkSize> MemoryPool<DataSize, ThunkSize>::s_pool;

    class MemoryPoolAllocator
    {
    public:
        template<typename DataType, typename ... ArgTypes>
        static DataType* alloc(const ArgTypes& ... args)
        {
            DataType* pResult = reinterpret_cast<DataType*>(MemoryPool<Meta::NextPOT<sizeof(DataType)>::Result>::s_pool.acquire());
            new (pResult) DataType(args ...);
            return pResult;
        }

        template<typename DataType>
        static void free(DataType* pValue)
        {
            if (pValue != nullptr)
            {
                pValue->~DataType();
                MemoryPool<Meta::NextPOT<sizeof(DataType)>::Result>::s_pool.release(reinterpret_cast<U8*>(pValue));
            }
        }
    };

    template<typename DataType>
    class MemoryPoolAllocatorAlias
    {
    public:
        template<typename ... ArgTypes>
        static DataType* alloc(const ArgTypes& ... args)
        {
            return GX::MemoryPoolAllocator::alloc<DataType>(args ...);
        }

        static void free(DataType* pValue)
        {
            GX::MemoryPoolAllocator::free<DataType>(pValue);
        }
    };

#define GX_MemoryPoolNew(DataType, ...) GX::MemoryPoolAllocator::alloc<DataType>(__VA_ARGS__)
#define GX_MemoryPoolDelete(Pointer)    GX::MemoryPoolAllocator::free<typename GX::Meta::RemoveAll<decltype(Pointer)>::Result>(Pointer)
}

#endif
