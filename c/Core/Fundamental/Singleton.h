#ifndef __SINGLETON_H__
#define __SINGLETON_H__

template <typename ConcreteType, typename BaseType = CCObject>
class Singleton : public BaseType
{
public:
    inline static ConcreteType* getInstance();
    inline static ConcreteType* getInstanceRaw();
    inline static void releaseInstance();
    inline static ConcreteType* newInstance();
private:
    static ConcreteType* s_pInstance;
};

template <typename ConcreteType, typename BaseType>
inline ConcreteType* Singleton<ConcreteType, BaseType>::getInstance()
{
    if (s_pInstance == nullptr)
    {
        s_pInstance = new ConcreteType();
    }
    return s_pInstance;
}

template <typename ConcreteType, typename BaseType>
inline ConcreteType* Singleton<ConcreteType, BaseType>::getInstanceRaw()
{
    return s_pInstance;
}

template<typename ConcreteType, typename BaseType>
inline void Singleton<ConcreteType, BaseType>::releaseInstance()
{
    if (s_pInstance != nullptr)
    {
        delete s_pInstance;
        s_pInstance = nullptr;
    }
}

template <typename ConcreteType, typename BaseType>
inline ConcreteType* Singleton<ConcreteType, BaseType>::newInstance()
{
    if (s_pInstance == nullptr)
    {
        s_pInstance = new ConcreteType;
    }
    else
    {
        s_pInstance->~ConcreteType();
        s_pInstance = new (s_pInstance)ConcreteType();
    }

    return s_pInstance;
}

template <typename ConcreteType, typename BaseType>
ConcreteType* Singleton<ConcreteType, BaseType>::s_pInstance = nullptr;

#endif // __SINGLE_H__