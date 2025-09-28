#include <iostream>
#include <string>
using namespace std;

// Tìm nghịch đảo modulo
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

// Mã hóa
string affineEncrypt(string plaintext, int a, int b) {
    string ciphertext = "";
    for (char c : plaintext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            ciphertext += (char)((a * (c - base) + b) % 26 + base);
        } else {
            ciphertext += c; // giữ nguyên ký tự không phải chữ
        }
    }
    return ciphertext;
}

// Giải mã
string affineDecrypt(string ciphertext, int a, int b) {
    string plaintext = "";
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        cout << "Khong tim duoc nghich dao cua a modulo 26!" << endl;
        return "";
    }
    for (char c : ciphertext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int x = (a_inv * ((c - base - b + 26)) % 26);
            plaintext += (char)(x + base);
        } else {
            plaintext += c;
        }
    }
    return plaintext;
}

int main() {
    string text;
    int a, b;
    cout << "Nhap van ban: ";
    getline(cin, text);
    cout << "Nhap khoa a (gcd(a,26)=1): ";
    cin >> a;
    cout << "Nhap khoa b: ";
    cin >> b;

    string encrypted = affineEncrypt(text, a, b);
    cout << "Ban ma hoa: " << encrypted << endl;

    string decrypted = affineDecrypt(encrypted, a, b);
    cout << "Ban giai ma: " << decrypted << endl;

    return 0;
}
