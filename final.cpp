
#include <iostream>
#include <string>
#include <cstdlib>   // for rand(), srand()
#include <ctime>     // for time()
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
        bool isNumber = true;
 
        for (char c : key)
        {
            if (isdigit(c) == 0)
            {
                isNumber = false;
                break;
            }
        }
 
        if (isNumber)
        {
            shift = stoi(key);
        }
        else
        {
            shift = 0;
        }
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
    VigenereCipher(string k)
    {
        key = k;
    }
 
    string encrypt(string text) override
    {
        string result;
        int keyIndex = 0;
 
        for (char c : text)
        {
            if (isalpha(c))
            {
                char base;
                if (isupper(c)) 
                {
                    base = 'A';
                } else 
                {
                    base = 'a';
                }
                int shift = toupper(key[keyIndex % key.length()]) - 'A';
 
                result += char((c - base + shift) % 26 + base);
 
                keyIndex++;
            }
            else
            {
                result += c;
            }
        }
 
        return result;
    }
 
    string decrypt(string text) override 
    {
        string result;
        int keyIndex = 0;
 
        for (char c : text)
        {
            if (isalpha(c))
            {
                char base;
                if (isupper(c)) 
                {
                    base = 'A';
                } else 
                {
                    base = 'a';
                }
                int shift = toupper(key[keyIndex % key.length()]) - 'A';
 
                result += char((c - base - shift + 26) % 26 + base);
 
                keyIndex++;
            }
            else
            {
                result += c;
            }
        }
 
        return result;
    }
};
 
 
// XOR CIPHER  

 
class XORCipher : public Cipher
{
private:
    string key;
 
public:
    XORCipher(string k)
    {
        key = k;
    }
 
    string encrypt(string text) override
    {
        string result = text;
 
        for (size_t i = 0; i < text.length(); i++)
        {
            result[i] = text[i] ^ key[i % key.length()];
        }
 
        return result;
    }
 
    string decrypt(string text) override
    {
        // XOR encryption and decryption are the same operation
        return encrypt(text);
    }
};
 
 
// RANDOM KEY GENERATOR FUNCTIONS

string generateCaesarKey()
{
    int shift = rand() % 25 + 1;   // random number from 1 to 25
    return to_string(shift);
}
 
string generateTextKey()
{
    const string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
 
    string key;
    for (int i = 0; i < 8; i++)
    {
        key += characters[rand() % 26];
    }
 
    return key;
}

int main() 
{
    srand(time(0));  // seed for the random number generator 
 
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
 
    CaesarCipher caesar(key);
    VigenereCipher vigenere(key);
    XORCipher xorCipher(key);
 
    Cipher* cipher;
 
    if (choice == 1)
    {
        cipher = &caesar;
    }
    else if (choice == 2)
    {
        cipher = &vigenere;
    }
    else if (choice == 3)
    {
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
 