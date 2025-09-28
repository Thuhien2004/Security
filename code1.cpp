// vigenere.cpp
#include <bits/stdc++.h>
using namespace std;

// Chuyển ký tự A-Z / a-z thành số 0-25
int charToNum(char c) {
    if (isupper(c)) return c - 'A';
    if (islower(c)) return c - 'a';
    return -1; // ký tự khác
}

// Chuyển số 0-25 thành chữ hoa
char numToChar(int n, bool isUpper=true) {
    return (isUpper ? 'A' : 'a') + n;
}

// Mã hóa Vigenère
string encryptVigenere(const string &plaintext, const string &key) {
    string cipher = "";
    int keyLen = key.size();
    for (int i = 0, j = 0; i < plaintext.size(); i++) {
        int p = charToNum(plaintext[i]);
        if (p != -1) { // nếu là chữ cái
            int k = charToNum(key[j % keyLen]);
            int c = (p + k) % 26;
            cipher += isupper(plaintext[i]) ? numToChar(c,true) : numToChar(c,false);
            j++;
        } else {
            cipher += plaintext[i]; // giữ nguyên ký tự khác
        }
    }
    return cipher;
}

// Giải mã Vigenère
string decryptVigenere(const string &ciphertext, const string &key) {
    string plain = "";
    int keyLen = key.size();
    for (int i = 0, j = 0; i < ciphertext.size(); i++) {
        int c = charToNum(ciphertext[i]);
        if (c != -1) {
            int k = charToNum(key[j % keyLen]);
            int p = (c - k + 26) % 26;
            plain += isupper(ciphertext[i]) ? numToChar(p,true) : numToChar(p,false);
            j++;
        } else {
            plain += ciphertext[i];
        }
    }
    return plain;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Vigenere Cipher ===\n";
    cout << "Chon che do: (E)ncrypt  (D)ecrypt\n> " << flush;
    string modeLine; getline(cin, modeLine);
    if (modeLine.empty()) return 0;
    char mode = modeLine[0];

    cout << "Nhap van ban:\n> " << flush;
    string text; getline(cin, text);

    cout << "Nhap khoa (key):\n> " << flush;
    string key; getline(cin, key);
    if (key.empty()) { cerr << "Key khong hop le!\n"; return 1; }

    string result;
    if (mode == 'E' || mode == 'e') {
        result = encryptVigenere(text, key);
        cout << "\n== Ciphertext ==\n" << result << "\n";
    } else if (mode == 'D' || mode == 'd') {
        result = decryptVigenere(text, key);
        cout << "\n== Plaintext ==\n" << result << "\n";
    } else {
        cerr << "Che do khong ho tro. Chon E hoac D.\n";
    }

    return 0;
}

