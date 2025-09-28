// hoanvi.cpp
// Block permutation / transposition cipher (encrypt & decrypt)
// Compile: g++ -std=c++17 hoanvi.cpp -o hoanvi
// Run: ./hoanvi

#include <bits/stdc++.h>
using namespace std;

bool is_valid_permutation(const vector<int>& P) {
    int n = P.size();
    vector<int> seen(n+1, 0);
    for (int x : P) {
        if (x < 1 || x > n) return false;
        if (seen[x]) return false;
        seen[x] = 1;
    }
    return true;
}

vector<int> inverse_permutation(const vector<int>& P) {
    int n = P.size();
    vector<int> inv(n);
    for (int i = 0; i < n; ++i) inv[P[i] - 1] = i + 1;
    return inv;
}

vector<string> split_blocks(const string& text, int n, char padChar) {
    vector<string> blocks;
    int len = text.size();
    for (int i = 0; i < len; i += n) {
        string block = text.substr(i, n);
        if ((int)block.size() < n) block.append(n - block.size(), padChar);
        blocks.push_back(block);
    }
    return blocks;
}

string encrypt_block(const string& block, const vector<int>& P) {
    int n = P.size();
    string out(n, ' ');
    for (int i = 0; i < n; ++i) out[i] = block[P[i] - 1];
    return out;
}

string decrypt_block(const string& block, const vector<int>& invP) {
    int n = invP.size();
    string out(n, ' ');
    for (int i = 0; i < n; ++i) out[i] = block[invP[i] - 1];
    return out;
}

string encrypt_text(const string& plaintext, const vector<int>& P, char padChar) {
    int n = P.size();
    vector<string> blocks = split_blocks(plaintext, n, padChar);
    string cipher = "";
    for (auto &blk : blocks) cipher += encrypt_block(blk, P);
    return cipher;
}

string decrypt_text(const string& ciphertext, const vector<int>& invP) {
    int n = invP.size();
    vector<string> blocks = split_blocks(ciphertext, n, 'X');
    string plain = "";
    for (auto &blk : blocks) plain += decrypt_block(blk, invP);
    return plain;
}

vector<int> parse_permutation(const string& line) {
    vector<int> P;
    string token;
    for (char c : line) {
        if (isdigit((unsigned char)c)) token.push_back(c);
        else {
            if (!token.empty()) {
                P.push_back(stoi(token));
                token.clear();
            }
        }
    }
    if (!token.empty()) P.push_back(stoi(token));
    return P;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Block Permutation / Transposition Cipher ===\n";

    // Prompt mode
    string modeLine;
    cout << "Chon che do: (E)ncrypt  (D)ecrypt\n> " << flush;
    if (!getline(cin, modeLine)) return 0;
    if (modeLine.empty()) {
        cerr << "Khong hop le: phai nhap E hoac D.\n";
        return 1;
    }
    char mode = modeLine[0];

    // Prompt text
    cout << "Nhap van ban (plaintext hoặc ciphertext):\n> " << flush;
    string text;
    if (!getline(cin, text)) return 0;

    // Prompt permutation
    cout << "Nhap hoan vi (vd: 3 1 4 2) :\n> " << flush;
    string permLine;
    if (!getline(cin, permLine)) return 0;
    vector<int> P = parse_permutation(permLine);

    if (!is_valid_permutation(P)) {
        cerr << "Loi: hoan vi khong hop le! Phai la permutation cua 1.." << P.size() << "\n";
        return 1;
    }

    if (mode == 'E' || mode == 'e') {
        cout << "Nhap ky tu padding (mac dinh 'X') :\n> " << flush;
        string tmp;
        if (!getline(cin, tmp)) tmp = "";
        char pad = 'X';
        if (!tmp.empty()) pad = tmp[0];

        string cipher = encrypt_text(text, P, pad);
        cout << "\n== Ciphertext ==\n" << cipher << "\n";
    } else if (mode == 'D' || mode == 'd') {
        vector<int> invP = inverse_permutation(P);
        string plain = decrypt_text(text, invP);
        cout << "\n== Plaintext (co the con padding o cuoi) ==\n" << plain << "\n";
    } else {
        cerr << "Che do khong ho tro. Chon E hoac D.\n";
    }

    return 0;
}
