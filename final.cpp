
#include <iostream>
#include <string>
using namespace std;


// ABSTRACT BASE CLASS  
 
class Cipher 
{
public:
    virtual string encrypt(string text) = 0;
    virtual string decrypt(string text) = 0;
};
 
 
// CAESAR CIPHER   

 
class CaesarCipher : public Cipher 
{
private:
    int shift;
public:
    CaesarCipher(string key) 
    {
        shift = stoi(key);
    }
 
    string encrypt(string text) override 
    {
        string result = text;
 
        for (char &c : result) 
        {
            if (isupper(c) == 1) 
            {
                c = char((c - 'A' + shift) % 26 + 'A');
            }
            else if (islower(c) == 1) 
            {
                c = char((c - 'a' + shift) % 26 + 'a');
            }
        }
 
        return result;
    }
 
    string decrypt(string text) override 
    {
        string result = text;
 
        for (char &c : result) 
        {
            if (isupper(c) == 1) 
            {
                c = char((c - 'A' - shift + 26) % 26 + 'A');
            }
            else if (islower(c) == 1) 
            {
                c = char((c - 'a' - shift + 26) % 26 + 'a');
            }
        }
        return result;
    }
};
 
 
// VIGENERE CIPHER   

 
class VigenereCipher : public Cipher 
{
private:
    string key;
 
public:
    VigenereCipher(string key) {
        this->key = key;
    }
 
    string encrypt(string text) override {
        cout << "[dummy function]\n";
        return text;
    }
 
    string decrypt(string text) override {
        cout << "[dummy function]\n";
        return text;
    }
};
 
 
// XOR CIPHER  

 
class XORCipher : public Cipher {
private:
    string key;
 
public:
    XORCipher(string key) {
        this->key = key;
    }
 
    string encrypt(string text) override {
        cout << "[dummy function]\n";
        return text;
    }
 
    string decrypt(string text) override {
        cout << "[dummy function]\n";
        return text;
    }
};
 
 
// RANDOM KEY GENERATOR FUNCTIONS

 
string generateCaesarKey() 
{
    return "meow";
}
 
string generateTextKey() 
{
    return "meow";
}
 

int main() 
{ 
    int choice;
    int operation;
 
    string message;
    string key;
    string result;
 
    cout << "Choose Cipher:\n";
    cout << "1. Caesar Cipher\n";
    cout << "2. Vigenere Cipher\n";
    cout << "3. XOR Cipher\n";
    cout << "\nChoice: ";
    cin >> choice; 

    string keyPrompt;
    if (choice == 1) 
        keyPrompt = "Caesar";
    else if (choice == 2) 
        keyPrompt = "Vigenere";
    else if (choice == 3) 
        keyPrompt = "XOR";
    else 
    {
        cout << "Invalid choice.\n";
        return 1;
    }

    cin.ignore();
 
    cout << "\nEnter message: ";
    getline(cin, message);
 
    cout << "\nEnter " << keyPrompt << " key (press R for random): ";
    getline(cin, key);
 
    if (key == "R" || key == "r") 
    {
       if (choice == 1) 
       {
            key = generateCaesarKey();
       }
       else
       {
            key = generateTextKey();
        }
        cout << "Generated key: " << key << endl;
    }
 
    Cipher* cipher;
 
    if (choice == 1) 
    {
        CaesarCipher caesar(key);
        cipher = &caesar;
    }
    else if (choice == 2) 
    {
        VigenereCipher vigenere(key);
        cipher = &vigenere;
    }
    else if (choice == 3) 
    {
        XORCipher xorCipher(key);
        cipher = &xorCipher;
    }
 
    cout << "\nChoose operation:\n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "\nChoice: ";
    cin >> operation;
 
    if (operation == 1) 
    {
        result = cipher->encrypt(message);
        cout << "\nEncrypted: " << result << endl;
    }
    else if (operation == 2) 
    {
        result = cipher->decrypt(message);
        cout << "\nDecrypted: " << result << endl;
    }
    else 
    {
        cout << "Invalid operation.\n";
    }
    return 0;
}
 