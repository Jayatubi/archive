struct Hash
{
    template <unsigned int N, unsigned int I>
    struct Helper
    {
        // __forceinline could make the string turn into integer in the optimize phase on MSVC. Thus, it couldn't be used as const value
        /*__forceinline*/
        constexpr static unsigned int Calculate(const char (&str)[N])
        {
            return (Helper<N, I - 1>::Calculate(str) ^ str[I - 1]) * PRIME;
        }
    };
 
    template <unsigned int N>
    struct Helper<N, 1>
    {
        /*__forceinline*/
        constexpr static unsigned int Calculate(const char (&str)[N])
        {
            return (OFFSET ^ str[0]) * PRIME;
        }
    };
 
    template <unsigned int N>
    constexpr static unsigned int Calculate(const char (&str)[N])
    {
        return Helper<N, N>::Calculate(str);
    }
};
