#ifndef GXFACTORY_H__
#define GXFACTORY_H__

namespace GX
{
    template<typename ClassType>
    class Factory : public Singleton< Factory<ClassType> >
    {
    public:
        typedef Function<ClassType*> CreatorFuncType;
        typedef Map<U32, CreatorFuncType>   CreaterFuncMap;

        bool registerCreatorFunc(U32 classId, const CreatorFuncType& func)
        {
            m_creatorMap[classId] = func;

            return true;
        }

        void unregisterCreatorFunc(U32 classId)
        {
            m_creatorMap.erase(classId);
        }

        ClassType* createInstance(U32 classId)
        {
            auto iter = m_creatorMap.find(classId);

            return iter != m_creatorMap.end() ? (iter->second)() : nullptr;
        }

    private:
        CreaterFuncMap m_creatorMap;
    };
}


#define GX_FACTORY_REGISTOR_CLASS_CLASS_ID_TAG(BaseClassNS, BaseClass, ConcreteClassNS, ConcreteClass, ClassId, TAG) \
    bool factory_##TAG = \
    GX::Factory<BaseClassNS::BaseClass>::getInstance()->registerCreatorFunc( \
    ClassId, []() -> BaseClassNS::BaseClass* { return new ConcreteClassNS::ConcreteClass(); })


#define GX_FACTORY_REGISTOR_CLASS_CLASS_ID(BaseClassNS, BaseClass, ConcreteClassNS, ConcreteClass, ClassId) \
    GX_FACTORY_REGISTOR_CLASS_CLASS_ID_TAG(BaseClassNS, BaseClass, ConcreteClassNS, ConcreteClass, ClassId, BaseClass_##ConcreteClass)

#define GX_FACTORY_REGISTOR_CLASS(BaseClassNS, BaseClass, ConcreteClassNS, ConcreteClass) \
    GX_FACTORY_REGISTOR_CLASS_CLASS_ID(BaseClassNS, BaseClass, ConcreteClassNS, ConcreteClass, ConcreteClassNS::ConcreteClass::CLASS_ID)

#endif // GXFACTORY_H__
