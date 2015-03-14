#ifndef _CRYPTO_DYNAMIC_H_
#define _CRYPTO_DYNAMIC_H_



class CryptoDynamic
{
public:
    //specialkey
    CryptoDynamic(unsigned int key);
    //defaltkey
    CryptoDynamic();

    static unsigned int DEFAULT_KEY;

    // return check code,check code is net order
    unsigned int encode(char *pbyBuf ,unsigned int uSize);
    unsigned int decode(char *pbyBuf ,unsigned int uSize);

protected:

    unsigned int mCurkey;
};




#endif