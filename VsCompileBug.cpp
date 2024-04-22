#include <stdint.h>
#if defined(__SSE4_2__) && defined(__PCLMUL__)
#include <x86intrin.h>
#elif defined(_MSC_VER) && defined(__AVX__)
#include <intrin.h>
#endif
typedef __m128i V128;

inline V128 V128_From64WithZeroFill(const uint64_t r)
{
    return _mm_set_epi64x(static_cast<int64_t>(0), static_cast<int64_t>(r));
}
inline V128 V128_PMulLow(const V128 l, const V128 r)
{
    return _mm_clmulepi64_si128(l, r, 0x00);
}
inline V128 V128_ShiftLeft64(const V128 l, const V128 r)
{
    return _mm_sll_epi64(l, r);
}
template <int imm>
inline int V128_Extract32(const V128 l)
{
    return _mm_extract_epi32(l, imm);
}
inline uint32_t CRC32_u32(uint32_t crc, uint32_t v)
{
    return _mm_crc32_u32(crc, v);
}

//__declspec(noinline)
uint32_t xmul(uint32_t a, uint32_t b)
{
    //printf("multiply(%u x %u)\n", a, b);
    V128 shifts = V128_From64WithZeroFill(1);
    V128 power = V128_From64WithZeroFill(a);
    V128 crc = V128_From64WithZeroFill(b);
    V128 res = V128_PMulLow(power, crc);

    // Combine crc values
    res = V128_ShiftLeft64(res, shifts);
    return static_cast<uint32_t>(V128_Extract32<1>(res)) ^
        CRC32_u32(0, V128_Extract32<0>(res));
}
