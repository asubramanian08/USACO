long long pow(long long a, long long b)
{
    if (b == 0)
        return 1;
    long long half_pow = pow(a, b / 2);
    long long pow_ish = (half_pow * half_pow) % MOD;
    return (pow_ish * (b % 2 ? a : 1)) % MOD;
}
long long inverse(long long p) { return pow(p, MOD - 2); }
long long choose(long long a, long long b) { return ((fact[a] * inverse(fact[b])) % MOD * inverse(fact[a - b])) % MOD; }
