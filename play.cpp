#include <bits/stdc++.h>
using namespace std;

string prepareKey(string key) {
    string res;
    set<char> seen;
    for (char c : key) {
        if (!isalpha(c)) continue;
        c = toupper(c);
        if (c == 'J') c = 'I'; // gộp I/J
        if (!seen.count(c)) { res += c; seen.insert(c); }
    }
    // Thêm các chữ cái còn lại
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;
        if (!seen.count(c)) res += c;
    }
    return res; // 25 ký tự
}

pair<int,int> findPos(char c, vector<vector<char>>& table) {
    if (c == 'J') c = 'I';
    for (int i=0;i<5;i++)
        for (int j=0;j<5;j++)
            if (table[i][j] == c) return {i,j};
    return {-1,-1};
}

string prepareText(string text) {
    string res;
    for (char c : text) {
        if (isalpha(c)) {
            char ch = toupper(c);
            if (ch == 'J') ch = 'I';
            res += ch;
        }
    }
    // chia cặp, chèn X nếu trùng ký tự
    string finalText = "";
    for (int i =0; i<res.size(); i++) {
        finalText += res[i];
        if (i+1 < res.size()) {
            if (res[i]==res[i+1]) finalText += 'X';
        }
    }
    if (finalText.size()%2!=0) finalText += 'X';
    return finalText;
}

string encryptPair(char a, char b, vector<vector<char>>& table) {
    auto [r1,c1] = findPos(a, table);
    auto [r2,c2] = findPos(b, table);
    if (r1==r2) return string(1, table[r1][(c1+1)%5]) + table[r2][(c2+1)%5];
    else if (c1==c2) return string(1, table[(r1+1)%5][c1]) + table[(r2+1)%5][c2];
    else return string(1, table[r1][c2]) + table[r2][c1];
}

string decryptPair(char a, char b, vector<vector<char>>& table) {
    auto [r1,c1] = findPos(a, table);
    auto [r2,c2] = findPos(b, table);
    if (r1==r2) return string(1, table[r1][(c1+4)%5]) + table[r2][(c2+4)%5]; // -1 mod 5
    else if (c1==c2) return string(1, table[(r1+4)%5][c1]) + table[(r2+4)%5][c2];
    else return string(1, table[r1][c2]) + table[r2][c1];
}

string encryptPlayfair(string text, vector<vector<char>>& table) {
    text = prepareText(text);
    string cipher = "";
    for (int i=0;i<text.size();i+=2)
        cipher += encryptPair(text[i], text[i+1], table);
    return cipher;
}

string decryptPlayfair(string cipher, vector<vector<char>>& table) {
    string plain = "";
    for (int i=0;i<cipher.size();i+=2)
        plain += decryptPair(cipher[i], cipher[i+1], table);
    return plain;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Playfair Cipher ===\n";
    cout << "Nhap key:\n> " << flush;
    string key; getline(cin,key);
    string key25 = prepareKey(key);

    // Tao bang 5x5
    vector<vector<char>> table(5, vector<char>(5));
    for (int i=0;i<5;i++)
        for (int j=0;j<5;j++)
            table[i][j] = key25[i*5 + j];

    cout << "\nBang Playfair:\n"; 
    for (int i=0;i<5;i++){
        for (int j=0;j<5;j++) cout << table[i][j] << ' ';
        cout << '\n';
    }

    cout << "\nChon che do: (E)ncrypt / (D)ecrypt\n> " << flush;
    string modeLine; getline(cin, modeLine);
    char mode = modeLine[0];

    cout << "Nhap van ban:\n> " << flush;
    string text; getline(cin, text);

    if (mode=='E' || mode=='e') {
        string cipher = encryptPlayfair(text, table);
        cout << "\n== Ciphertext ==\n" << cipher << "\n";
    } else if (mode=='D' || mode=='d') {
        string plain = decryptPlayfair(text, table);
        cout << "\n== Plaintext (co the con padding X) ==\n" << plain << "\n";
    } else {
        cerr << "Che do khong ho tro!\n";
    }

    return 0;
}

