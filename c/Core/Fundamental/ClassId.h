#ifndef GXCLASSID_H__
#define GXCLASSID_H__

#include "../BasicType/BasicType.h"
#include "../Meta/Result.h"
#include "../Meta/IsSame.h"
#include "../Meta/IsRef.h"

namespace GX
{
    namespace Details
    {
        template<typename ValueType>
        struct HasSuper
        {
            template<typename _>
            struct Matcher;

            template<typename TestType>
            static Meta::Yes Tester(Matcher<typename TestType::Super>*);

            template<typename TestType>
            static Meta::No Tester(...);

            enum
            {
                Result = sizeof(Tester<ValueType>(nullptr)) == sizeof(Meta::Yes)
            };
        };

        template<bool>
        struct IsClassImpl
        {
            template<typename ValueType>
            static bool Test(GX::U32 classId)
            {
                return ValueType::is_impl(classId);
            }
        };
        template<>
        struct IsClassImpl<true>
        {
            template<typename ValueType>
            static bool Test(GX::U32 classId)
            {
                return ValueType::is_impl(classId) || ValueType::Super::is_impl(classId);
            }
        };
    }
}

#define GX_DEF_CLASSID(id) \
    enum { CLASS_ID = id }; \
    virtual GX::U32 getClassId() const { return CLASS_ID; } \
    static bool is_impl(GX::U32 classId) { return CLASS_ID == classId; } \

#define GX_CLASSID(id) \
    GX_DEF_CLASSID(id) \
    virtual bool is(GX::U32 classId) const \
    { \
        typedef typename GX::Meta::RemoveRef<decltype(*this)>::Result ThisType; \
        return GX::Details::IsClassImpl<GX::Details::HasSuper< ThisType >::Result>::template Test<ThisType>(classId); \
    }

#define GX_CLASSID_ROOT(id) \
    GX_DEF_CLASSID(id) \
    virtual bool is (GX::U32 classId) const { return is_impl(classId); } \
    template<typename ValueType> bool is() const { return is(ValueType::CLASS_ID); } \
    template<typename ValueType> ValueType* as() { return is<ValueType>() ? static_cast<ValueType*>(this) : nullptr; } \
    template<typename ValueType> explicit operator ValueType*() { return as<ValueType>(); } \
    template<typename ValueType> explicit operator const ValueType*() const { return as<ValueType>(); } \
    template<typename ValueType> const ValueType* as() const { return is<ValueType>() ? static_cast<const ValueType*>(this) : nullptr; }

#define GX_CLASSTAG(tag) GX_CLASSID(GX::StringHash::StaticHash(tag))

#endif // ClassId_h__
