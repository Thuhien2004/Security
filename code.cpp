// code.cpp (fix: ensure prompts are shown before reading input)
// Compile: g++ -std=c++17 code.cpp -O2 -o code.exe
// Run (PowerShell): .\code.exe

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>

using namespace std;

char shift_char(char ch, int k, bool enc=true) {
    if (isupper((unsigned char)ch)) {
        int base = 'A';
        int v = ch - base;
        if (!enc) v = (v - k) % 26;
        else v = (v + k) % 26;
        if (v < 0) v += 26;
        return char(base + v);
    }
    if (islower((unsigned char)ch)) {
        int base = 'a';
        int v = ch - base;
        if (!enc) v = (v - k) % 26;
        else v = (v + k) % 26;
        if (v < 0) v += 26;
        return char(base + v);
    }
    return ch;
}

string caesar_encrypt(const string &s, int k) {
    string out; out.reserve(s.size());
    k = ((k % 26) + 26) % 26;
    for (char c: s) out.push_back( shift_char(c, k, true) );
    return out;
}

string caesar_decrypt(const string &s, int k) {
    k = ((k % 26) + 26) % 26;
    return caesar_encrypt(s, (26 - k) % 26);
}

void brute_force(const string &cipher) {
    cout << "Brute-force (26 shifts):\n";
    for (int k = 0; k < 26; ++k) {
        cout << setw(2) << k << " : " << caesar_decrypt(cipher, k) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    // tie cin to cout so prompts flush before input
    cin.tie(&cout);

    cout << "Caesar Cipher tool\n";
    cout << "Chon thao tac:\n";
    cout << "  1) Ma hoa (encrypt)\n";
    cout << "  2) Giai ma (decrypt)\n";
    cout << "  3) Brute-force (liet ke 26 ket qua)\n";
    cout << "Nhap so (1/2/3): " << flush;    // ensure prompt is shown

    int choice;
    if (!(cin >> choice)) return 0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 1 || choice == 2) {
        cout << "Nhap khoa k (so nguyen): " << flush;
        int k;
        if (!(cin >> k)) return 0;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nhap mot dong plaintext/ciphertext: " << flush;
        string text;
        getline(cin, text); // single-line input

        if (choice == 1) {
            cout << "\n=== Ciphertext ===\n" << caesar_encrypt(text, k) << "\n";
        } else {
            cout << "\n=== Plaintext ===\n" << caesar_decrypt(text, k) << "\n";
        }
    } else if (choice == 3) {
        cout << "Nhap mot dong ciphertext: " << flush;
        string cipher;
        getline(cin, cipher);
        if (cipher.empty()) getline(cin, cipher); // in case previous newline
        brute_force(cipher);
    } else {
        cout << "Lua chon khong hop le.\n";
    }

    return 0;
}
