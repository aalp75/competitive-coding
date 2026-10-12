using namespace std;

/**
 * Booth's algorithm
 *
 * Lexicographically minimal string rotation
 * 
 * Based on https://en.wikipedia.org/wiki/Lexicographically_minimal_string_rotation
 * 
 * Naive implementation would be O(n^2) but this algorithm works in O(n)
 * 
 */

string smallestRotation(const std::string& s) {
    int n = s.length();
    if (n == 0) return "";

    std::vector<int> f(2 * n, -1);
    int k = 0;

    for (int j = 1; j < 2 * n; ++j) {
        int i = f[j - k - 1];
        while (i != -1 && s[j % n] != s[(k + i + 1) % n]) {
            if (s[j % n] < s[(k + i + 1) % n]) {
                k = j - i - 1;
            }
            i = f[i];
        }

        if (i == -1 && s[j % n] != s[(k + i + 1) % n]) {
            if (s[j % n] < s[(k + i + 1) % n]) {
                k = j;
            }
            f[j - k] = -1;
        } else {
            f[j - k] = i + 1;
        }
    }

    string rotated = s.substr(k) + s.substr(0, k);
    return rotated;
}

int main() {

    // Booth's algorithm
    s = "BBAACCAADD";
    string r = smallestRotation(s);
    cout << "The smallest rotation of " << s << " is " << r << '\n';

    cout << '\n';
    
	return 0;
}