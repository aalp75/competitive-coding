#include <bits/stdc++.h>

using namespace std;

/**
 * 
 * Polynoms multiplication using Fast Fourier Transform
 * (Cooley-Tukey algorithm)
 * 
 * based on CLRS - chapter 30
 * 
 * Steps to compute coefficients of P1(x) * P2(x):
 * 1) compute dft of P1(x) and P2(x) using fft O(n)
 * 2) multiply dft of P1 and P2 pointwise O(n log(n))
 * 3) compute the inverse fft of dft O(n)
 * 
 * Complexity: O(nlog(n)) where n is the degree of polynoms
 * 
 * Note: It's a recuversive implementation, which is way 
 * slower than an iterative implementation
 */

template <typename T>
vector<T> multiplyNaive(vector<T>& p1, vector<T>& p2) {
    int n = p1.size();
    int m = p2.size();
    vector<T> res(n + m - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res[i + j] += p1[i] * p2[j];
        }
    }
    return res;
}

template <typename T>
void printPolynom(vector<T>& p1) {
    int n = p1.size();
    for (int i = 0; i < n; i++) {
        cout << p1[i];
        if (i == 1) {
            cout << "x";
        }
        if (i > 1) {
            cout << "x^" << i;
        }
        if (i < n - 1) {
            cout << " + ";
        }
    }
    cout << '\n';
}

// define complex number

const double PI = numbers::pi;

vector<complex<double>> fft(vector<complex<double>>& p, bool inverse) {
    int n = p.size(); // n must be a power of 2
    if (n == 1) {
        return p;
    }
    vector<complex<double>> even;
    vector<complex<double>> odd;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            even.push_back(p[i]);
        }
        else {
            odd.push_back(p[i]);
        }
    }

    auto yEven = fft(even, inverse);
    auto yOdd = fft(odd, inverse);

    vector<complex<double>> res(n);

    double theta = inverse ? -2 * PI / n : 2 * PI /n;
    complex<double> w(cos(theta), sin(theta));
    complex<double> wn(1);

    for (int i = 0; 2 * i < n; i++) {
        res[i] = yEven[i] + wn * yOdd[i];
        res[i + n / 2] = yEven[i] - wn * yOdd[i];

        wn = wn * w;
    }
    if (inverse) {
        for (int i = 0; 2 * i < n; i++) {
            res[i] /= 2;
            res[i + n / 2] /= 2;
        }
    }
    return res;
}

template <typename T>
vector<T> multiply(vector<T>& p1, vector<T>& p2) {
    vector<complex<double>> cp1(p1.begin(), p1.end());
    vector<complex<double>> cp2(p2.begin(), p2.end());

    // n is the smaller power of 2 greater than degree(p1) + degree(p2)
    int n = 1;
    while (n < p1.size() + p2.size()) n *= 2;

    cp1.resize(n);
    cp2.resize(n);

    // compute discrete fourier transform of both p1 and p2
    vector<complex<double>> dft1 = fft(cp1, false);
    vector<complex<double>> dft2 = fft(cp2, false);

    vector<complex<double>> dft(n);

    // multiply in value 
    for (int i = 0; i < n; i++) {
        dft[i] = dft1[i] * dft2[i];
    }

    vector<complex<double>> p = fft(dft, true);

    vector<T> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = p[i].real();
    }
    return res;
}

int main() {

    vector<int> p1 = {1, 1, 2}; // 1 + x + 2x^2
    vector<int> p2 = {2, 3, 4}; // 2 + 3x + 4x^2

    vector<int> res = multiplyNaive(p1, p2);

    printPolynom(res); // 2 + 5x + 11x^2 + 10x^3 + 8x^4

    vector<complex<double>> p = {1, 1, 2, 4};

    vector<complex<double>> dft = fft(p, true);
    // (8,0) (-1,-3) (-2,0) (-1,3) 
    for (auto e : dft) {
        cout << e << " ";
    }
    cout << '\n';

    vector<int> res2 = multiply(p1, p2);
    printPolynom(res2);

    cout << '\n';

    return 0;
}
