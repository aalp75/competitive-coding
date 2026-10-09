// return the ceil number of x / y e.g. ceil_division(5, 2) = 3
long long ceil_division(long long x, long long y) {
    long long res = x / y + (x % y != 0);
    return res;
}