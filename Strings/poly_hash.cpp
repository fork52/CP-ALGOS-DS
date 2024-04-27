#include <bits/stdc++.h>


// Credits: https://github.com/sgtlaugh/algovault/blob/master/code_library/hashing.cpp

/**
 * @snip-start
 * snip-name: PolyHash
 * snip-prefix: polyhash
 * snip-description: Polynomial hashing
*/
// -------------------------------- POLY HASH START-------------------------------------------
const int POLY_HASH_MAX_LEN = 1e6 + 10;
constexpr uint64_t POLY_MOD = (1ULL << 61) - 1;
const uint64_t POLY_SEED = std::chrono::system_clock::now().time_since_epoch().count();
const uint64_t POLY_BASE = std::mt19937_64(POLY_SEED)() % (POLY_MOD / 3) + (POLY_MOD / 3);
uint64_t poly_base_pow[POLY_HASH_MAX_LEN];

class PolyHash
{
private:
    /// Remove suff vector and usage if reverse hash is not required for more speed
    std::vector<int64_t> pref, suff;

    static int64_t modmul(uint64_t a, uint64_t b)
    {
        uint64_t l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
        uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
        uint64_t ret = (l & POLY_MOD) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
        ret = (ret & POLY_MOD) + (ret >> 61);
        ret = (ret & POLY_MOD) + (ret >> 61);
        return ret - 1;
    }

    static void init()
    {
        poly_base_pow[0] = 1;
        for (int i = 1; i < POLY_HASH_MAX_LEN; i++)
        {
            poly_base_pow[i] = modmul(poly_base_pow[i - 1], POLY_BASE);
        }
    }

public:
    PolyHash() {}

    template <typename T>
    PolyHash(const std::vector<T> &ar)
    {
        if (poly_base_pow[0] == 0)
        {
            init();
        }

        int n = ar.size();

        pref.resize(n + 3, 0), suff.resize(n + 3, 0);

        for (int i = 1; i <= n; i++)
        {
            pref[i] = modmul(pref[i - 1], POLY_BASE) + ar[i - 1] + 997;
            if (pref[i] >= POLY_MOD)
                pref[i] -= POLY_MOD;
        }

        for (int i = n; i >= 1; i--)
        {
            suff[i] = modmul(suff[i + 1], POLY_BASE) + ar[i - 1] + 997;
            if (suff[i] >= POLY_MOD)
                suff[i] -= POLY_MOD;
        }
    }

    PolyHash(const char *str)
        : PolyHash(std::vector<char>(str, str + std::strlen(str))) {}

    /**
     * Indices are 0-indexed and inclusive.
    */
    uint64_t get_hash(int l, int r)
    {
        int64_t h = pref[r + 1] - modmul(poly_base_pow[r - l + 1], pref[l]);
        return h < 0 ? h + POLY_MOD : h;
    }

    /**
     * Indices are 0-indexed and inclusive.
    */
    uint64_t rev_hash(int l, int r)
    {
        int64_t h = suff[l + 1] - modmul(poly_base_pow[r - l + 1], suff[r + 2]);
        return h < 0 ? h + POLY_MOD : h;
    }
};
// -------------------------------- POLY HASH END -------------------------------------------
// @snip-end

