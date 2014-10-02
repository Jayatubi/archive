struct Hash
{
    template <unsigned int N, unsigned int I>
    struct Helper
    {
        __forceinline static unsigned int Calculate(const char (&str)[N])
        {
            return (Helper<N, I - 1>::Calculate(str) ^ str[I - 1]) * PRIME;
        }
    };
 
    template <unsigned int N>
    struct Helper<N, 1>
    {
        __forceinline static unsigned int Calculate(const char (&str)[N])
        {
            return (OFFSET ^ str[0]) * PRIME;
        }
    };
 
    template <unsigned int N>
    static unsigned int Calculate(const char (&str)[N])
    {
        return Helper<N, N>::Calculate(str);
    }
};
