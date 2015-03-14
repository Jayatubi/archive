#include "CryptoDynamic.h"
#include <assert.h>



unsigned int CryptoDynamic::DEFAULT_KEY = 0;
namespace CryptoDynamicInternal
{

    unsigned int DEFAULT_CODE = 0x3564533;
    
    template<typename _to,typename _from >
    static _to horible_cast(const _from& f)
    {
        union horible_caster
        {
        public:
            _from from;
            _to to;
        };
        
        horible_caster caster;
        caster.from = f;
        return caster.to;
    }
    
    
    
    unsigned int encode(char *pbyBuf ,unsigned int uSize, unsigned int uKey)
    {
        assert((horible_cast<int>(pbyBuf) & 0x3) == 0);    //make sure the alignment
        
        unsigned int *puBuf = (unsigned int *)pbyBuf;
        unsigned int uRemainSize = uSize % 4;
        uSize /= 4;
        
        uKey = htonl(uKey);
        unsigned int cb = DEFAULT_CODE;
        
        while (uSize-- > 0)
        {
            unsigned char *pu = (unsigned char*)(puBuf);
            unsigned int &v = *puBuf++;
            v ^= uKey;
            unsigned char pc = (pu[0] + pu[1] + pu[2]) ^ pu[3];
            cb += pc;
        }
        
        char *pCurByBuf = (char *)puBuf;
        
        while (uRemainSize-- > 0)
        {
            char &v = *pCurByBuf++;
            v ^= (char)(uKey & 0xff);
            uKey >>= 8;
            cb += (unsigned char)v;
        }
        return cb;
    }
    
    unsigned int decode(char *pbyBuf ,unsigned int uSize, unsigned int uKey)
    {
        assert((horible_cast<int>(pbyBuf) & 0x3) == 0);    //make sure the alignment
        
        unsigned int *puBuf = (unsigned int *)pbyBuf;
        unsigned int uRemainSize = uSize % 4;
        uSize /= 4;
        
        uKey = htonl(uKey);
        unsigned int cb = DEFAULT_CODE;
        
        while (uSize-- > 0)
        {
            unsigned char *pu = (unsigned char*)(puBuf);
            unsigned char pc = (pu[0] + pu[1] + pu[2]) ^ pu[3];
            cb += pc;
            unsigned int &v = *puBuf++;
            v ^= uKey;
        }
        
        char *pCurByBuf = (char *)puBuf;
        
        while (uRemainSize-- > 0)
        {
            char &v = *pCurByBuf++;
            cb += (unsigned char)v;
            v ^= (char)(uKey & 0xff);
            uKey >>= 8;
        }
        return cb;
    }



    
    
};




CryptoDynamic::CryptoDynamic(unsigned int key):mCurkey(key)
{

}

CryptoDynamic::CryptoDynamic():mCurkey(DEFAULT_KEY)
{

}



unsigned int CryptoDynamic::encode( char *pbyBuf ,unsigned int uSize )
{
    if (mCurkey==0)
    {
        return 0;
    }
    return CryptoDynamicInternal::encode(pbyBuf,uSize,mCurkey);
}

unsigned int CryptoDynamic::decode( char *pbyBuf ,unsigned int uSize )
{
    if (mCurkey==0)
    {
        return 0;
    }

    return CryptoDynamicInternal::decode(pbyBuf,uSize,mCurkey);
}

