#ifndef GXSTRING_H__
#define GXSTRING_H__


#include "BasicType.h"
#include "Math.h"
#include "Vector.h"
#include <cstring>
#include <cwchar>
#include <cstdlib>


namespace GX
{
    namespace Details
    {
        template<typename T>
        struct ToStringValueCalc
        {
            typedef T ValueType;
        };
        
        template<typename CharType, typename ValueType>
        struct ToString
        {
            
        };
        
        template<typename CharType>
        struct StringHelper
        {
            static void copy(const CharType* pSrc, CharType* pDst, U32 length);
            static void format(CharType* pDst, const CharType* pFormat, U32 length, va_list args);
            static S32 compare(const CharType* pStrA, const CharType* pStrB);
            static S32 icompare(const CharType* pStrA, const CharType* pStrB);
            static U32 toUInt(const CharType* pStr);
            static S32 toInt(const CharType* pStr);
            static F32 toFloat(const CharType* pStr);
            static S32 toBool(const CharType* pStr);
            static void toLower(CharType* pStr);
            static void toUpper(CharType* pStr);
            static U32 strLength(const CharType* pStr);
        };

        template<>
        struct StringHelper<Char>
        {
            inline static void copy(const Char* pSrc, Char* pDst, U32 length)
            {
                strncpy(pDst, pSrc, length);
            }

            inline static void format(Char* pDst, const Char* pFormat, U32 length, va_list args)
            {
                vsnprintf(pDst, length, pFormat, args);
            }

            inline static S32 compare(const Char* pStrA, const Char* pStrB)
            {
                return strcmp(pStrA, pStrB);
            }

            inline static S32 icompare(const Char* pStrA, const Char* pStrB)
            {
                return strcasecmp(pStrA, pStrB);
            }

            inline static U32 toUInt(const Char* pStr)
            {
                return strtoul(pStr, 0, 0);
            }

            inline static S32 toInt(const Char* pStr)
            {
                return atoi(pStr);
            }

            inline static F32 toFloat(const Char* pStr)
            {
                return static_cast<F32>(atof(pStr));
            }

            inline static S32 toBool(const Char* pStr)
            {
                return icompare(pStr, "true") == 0;
            }

            inline static void toLower(Char* pStr)
            {
                U32 length = strLength(pStr);
                for(U32 i = 0; i < length; i++)
                {
                    pStr[i] = static_cast<Char>(tolower(pStr[i]));
                }
            }

            inline static void toUpper(Char* pStr)
            {
                U32 length = strLength(pStr);
                for(U32 i = 0; i < length; i++)
                {
                    pStr[i] = static_cast<Char>(toupper(pStr[i]));
                }
            }

            inline static U32 strLength(const Char* pStr)
            {
                return strlen(pStr);
            }
        };

        template<>
        struct StringHelper<WChar>
        {
            inline static void copy(const WChar* pSrc, WChar* pDst, U32 length)
            {
                wcsncpy(pDst, pSrc, length);
            }

            inline static void format(WChar* pDst, const WChar* pFormat, U32 length, va_list args)
            {
                vswprintf(pDst, length, pFormat, args);
            }

            inline static S32 compare(const WChar* pStrA, const WChar* pStrB)
            {
                return wcscmp(pStrA, pStrB);
            }

            inline static S32 icompare(const WChar* pStrA, const WChar* pStrB)
            {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
                // Not implemented
                return 0;
#else
                return wcscasecmp(pStrA, pStrB);
#endif
            }

            inline static U32 toUInt(const WChar* pStr)
            {
                return wcstoul(pStr, 0, 0);
            }

            inline static S32 toInt(const WChar* pStr)
            {
                return wcstol(pStr, 0, 0);
            }

            static F32 toFloat(const WChar* pStr)
            {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
                // Not implemented
                return 0;
#else
                return wcstof(pStr, 0);
#endif
            }

            static S32 toBool(const WChar* pStr)
            {
                return icompare(pStr, L"true") == 0;
            }

            inline static void toLower(WChar* pStr)
            {
                U32 length = strLength(pStr);
                for(U32 i = 0; i < length; i++)
                {
                    pStr[i] = towlower(pStr[i]);
                }
            }

            inline static void toUpper(WChar* pStr)
            {
                U32 length = strLength(pStr);
                for(U32 i = 0; i < length; i++)
                {
                    pStr[i] = towupper(pStr[i]);
                }
            }

            inline static U32 strLength(const WChar* pStr)
            {
                return wcslen(pStr);
            }
        };
    }

    template<typename CharType>
    class BaseString : public std::basic_string<CharType, std::char_traits<CharType>, std::allocator<CharType>>
    {
    public:
        typedef std::basic_string<CharType, std::char_traits<CharType>, std::allocator<CharType>>   BaseType;
        typedef std::basic_stringstream<CharType, std::char_traits<CharType>>                       StreamType;
        typedef typename BaseType::iterator                                                         Iterator;
        typedef typename BaseType::reverse_iterator                                                 ReverseIterator;
        typedef typename BaseType::const_iterator                                                   ConstIterator;
        typedef typename BaseType::const_reverse_iterator                                           ConstReverseIterator;
    public:
        BaseString()
        {}

        BaseString(const CharType* pStr)
            : BaseType(pStr)
        {}

        BaseString(const CharType* pStr, U32 size)
            : BaseType(pStr, size)
        {}

        BaseString(const BaseString& right)
            : BaseType(right)
        {}

        BaseString(const BaseString&& right)
            : BaseType(std::move(right))
        {}

        BaseString(const BaseType& right)
            : BaseType(right)
        {}

        BaseString(const BaseType&& right)
            : BaseType(std::move(right))
        {}

        BaseString& operator = (const CharType* right)
        {
            BaseType::operator = (right);
            return *this;
        }

        BaseString& operator = (const BaseString& right)
        {
            BaseType::operator = (right);
            return *this;
        }

        BaseString& operator = (const BaseString&& right)
        {
            BaseType::operator = (std::move(right));
            return *this;
        }

        operator const CharType*() const
        {
            return cstr();
        }

        const CharType* cstr() const
        {
            return BaseType::c_str();
        }
        
        CharType* mutable_cstr()
        {
            return &BaseType::operator[](0);
        }

        bool compare(const BaseString& r) const
        {
            return 0==Details::StringHelper<CharType>::compare(cstr(),r.cstr());
        }
        
        bool icompare(const BaseString& r) const
        {
            return 0==Details::StringHelper<CharType>::icompare(cstr(),r.cstr());
        }
        
        BaseString replaceEx(const BaseString& oldValue, const BaseString& newValue)const
        {
            BaseString result = *this;
            typename BaseType::size_type pos = result.find(oldValue);
            while (pos != BaseType::npos)
            {
                result.replace(pos, oldValue.length(), newValue);
                pos = result.find(oldValue, pos + newValue.length());
            }

            return result;
        }

        BaseString substring(S32 index, S32 length = -1) const
        {
            return BaseString(BaseType::substr(index, length));
        }

        Vector<BaseString> split(const CharType& spliter)
        {
            Vector<BaseString> result;
            StreamType stream(*this);
            BaseString segment;
            while (std::getline(stream, segment, spliter))
            {
                result.push_back(segment);
            }
            return result;
        }

        template<typename ValueType>
        Vector<ValueType> splitInto(const CharType& spliter);

        template < typename PredicateType >
        BaseString& trim_left(const PredicateType& predicate)
        {
            for( Iterator iter = BaseType::begin(); iter != BaseType::end(); ++iter )
            {
                if( !predicate(*iter) )
                {
                    if( iter != BaseType::begin() )
                    {
                        BaseType::erase( BaseType::begin(), iter );
                    }

                    break;
                }
            }

            return *this;
        }

        template < typename PredicateType >
        BaseString& trim_right(const PredicateType& predicate)
        {
            for( ReverseIterator iter = BaseType::rbegin(); iter != BaseType::rend(); ++iter )
            {
                if( !predicate(*iter) )
                {
                    if( iter != BaseType::rbegin() )
                    {
                        BaseType::erase( iter.base(), BaseType::end());
                    }

                    break;
                }
            }

            return *this;
        }

        template < typename PredicateType >
        BaseString& trim(const PredicateType& predicate)
        {
            trim_left(predicate);
            trim_right(predicate);
            return *this;
        }

        BaseString& trim()
        {
            return trim([](CharType c)->bool { return std::isspace(c); });
        }

        U32 toUInt() const
        {
            return Details::StringHelper<CharType>::toUInt(cstr());
        }

        S32 toInt() const
        {
            return Details::StringHelper<CharType>::toInt(cstr());
        }

        F32 toFloat() const
        {
            return Details::StringHelper<CharType>::toFloat(cstr());
        }

        bool toBool() const
        {
            return Details::StringHelper<CharType>::toBool(cstr());
        }

        BaseString toLower() const
        {
            BaseString result(*this);
            Details::StringHelper<CharType>::toLower(result.mutable_cstr());
            return result;
        }

        BaseString toUpper() const
        {
            BaseString result(*this);
            Details::StringHelper<CharType>::toUpper(result.mutable_cstr());
            return result;
        }

        template<int ArraySize>
        void copyToArray(CharType (& array)[ArraySize]) const
        {
            const U32 realLength = min<U32>(ArraySize, BaseType::length());
            Details::StringHelper<CharType>::copy(BaseType::c_str(), &array[0], realLength);
            array[realLength] = 0;
        }

        template<int ArraySize>
        BaseString operator >> (CharType (& array)[ArraySize]) const
        {
            copyToArray(array);

            return *this;
        }

        template<int MaxSize = 1024>
        static BaseString format(const CharType* pFormat, ...)
        {
            CharType buffer[MaxSize] = {0};
            va_list args;
            va_start(args, pFormat);
            Details::StringHelper<CharType>::format(buffer, pFormat, MaxSize, args);
            va_end(args);

            return BaseString(buffer);
        }

        template<typename ValueType>
        static BaseString join(const ValueType& strs, const BaseString& spliter)
        {
            BaseString result;

            auto iter = strs.begin();
            auto end  = strs.end();

            for(; iter != end; ++iter)
            {
                if (!result.empty())
                {
                    result += spliter;
                }

                result += *iter;
            }

            return result;
        }

        static bool isEmpty(const CharType* pStr)
        {
            return pStr == nullptr || Details::StringHelper<CharType>::strLength(pStr) == 0;
        }

        S32 indexOf(const CharType* pStr, S32 index = 0) const
        {
            return BaseType::find_first_of(pStr, index);
        }

        S32 lastIndexOf(const CharType* pStr, S32 index = 0) const
        {
            return BaseType::find_last_of(pStr);
        }

        BaseString asFilename() const
        {
            S32 begin = lastIndexOf("/"); 

            return substring(begin + 1);
        }

        BaseString asDirname() const
        {
            S32 begin = lastIndexOf("/");

            return substring(0, begin);
        }

        U32 hashCode() const
        {
            return StringHash::CalculateHash(cstr());
        }

        template<typename ValueType>
        static BaseString fromValue(const ValueType &value, const CharType* pattern = nullptr)
        {
            return Details::ToString<CharType, typename Details::ToStringValueCalc<ValueType>::ValueType >::convert(value, pattern);
        }
    };
    
    namespace Details
    {
      
        template<typename CharType>
        struct ToString<CharType, GX::U8>
        {
            static BaseString<CharType> convert(GX::U8 value, const CharType* pattern)
            {
                return BaseString<CharType>::format(pattern != nullptr ? pattern : "%u", value);
            }
        };
        
        template<typename CharType>
        struct ToString<CharType, GX::S8>
        {
            static BaseString<CharType> convert(GX::S8 value, const CharType* pattern)
            {
                return BaseString<CharType>::format(pattern != nullptr ? pattern : "%d", value);
            }
        };
        
        template<typename CharType>
        struct ToString<CharType, GX::S32>
        {
            static BaseString<CharType> convert(GX::S32 value, const CharType* pattern)
            {
                return BaseString<CharType>::format(pattern != nullptr ? pattern : "%d", value);
            }
        };
        
        template<typename CharType>
        struct ToString<CharType, GX::U32>
        {
            static BaseString<CharType> convert(GX::U32 value, const CharType* pattern)
            {
                return BaseString<CharType>::format(pattern != nullptr ? pattern : "%u", value);
            }
        };
        
        template<typename CharType>
        struct ToString<CharType, GX::F32>
        {
            static BaseString<CharType> convert(GX::F32 value, const CharType* pattern)
            {
                return BaseString<CharType>::format(pattern != nullptr ? pattern : "%f", value);
            }
        };
    }

    typedef BaseString<Char> String;
    typedef BaseString<WChar> WString;

    namespace Details
    {
        template<typename CharType>
        class FromString
        {
        public:
            typedef GX::BaseString<CharType> StringType;

            FromString(const StringType& str)
            : m_str(str)
            {}

            operator U8() const
            {
                return m_str.toUInt();
            }

            operator U16() const
            {
                return m_str.toUInt();
            }

            operator U32() const
            {
                return m_str.toUInt();
            }

            operator U64() const
            {
                return m_str.toUInt();
            }

            operator S8() const
            {
                return m_str.toInt();
            }

            operator S16() const
            {
                return m_str.toInt();
            }

            operator S32() const
            {
                return m_str.toInt();
            }

            operator S64() const
            {
                return m_str.toInt();
            }

            operator F32() const
            {
                return m_str.toFloat();
            }

            operator typename StringType::BaseType() const
            {
                return m_str;
            }
        private:
            const StringType& m_str;
        };
    }

    template<typename CharType>
    template<typename ValueType>
    Vector<ValueType> BaseString<CharType>::splitInto(const CharType& spliter)
    {
        return split(spliter).template select<ValueType>([](const BaseString<CharType>& str)
                                                {
                                                    return static_cast<ValueType>(Details::FromString<CharType>(str));
                                                });
    }
}


inline GX::String operator "" _gs(const char * pStr, std::size_t length)
{
    return GX::String(pStr, length);
}


#endif // GXSTRING_H__
