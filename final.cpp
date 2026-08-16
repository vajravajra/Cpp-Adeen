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
    virtual ~Cipher() {} // completely delete all dynamic objects
};

// CAESAR CIPHER

class CaesarCipher : public Cipher
{
private:
    int shift;
public:
    CaesarCipher(int s)
    {
        shift = s;
    }

    string encrypt(string text) override
    {
        string result = text;

        for (char &c : result)
        {
            if (isupper(c))
            {
                c = char((c - 'A' + shift) % 26 + 'A');
            }
            else if (islower(c))
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
            if (isupper(c))
            {
                c = char((c - 'A' - shift + 26) % 26 + 'A');
            }
            else if (islower(c))
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
        string result = text;
        int keyIndex = 0;

        for (char &c : result)
        {
            if (isalpha(c))
            {
                char base;
                if (isupper(c))
                {
                    base = 'A';
                } 
                else
                {
                    base = 'a';
                }
                int shift = toupper(key[keyIndex % key.length()]) - 'A'; // converting cat to 3 1 20 3 1 20 3 1 20...

                c = char((c - base + shift) % 26 + base);

                keyIndex++;
            }
            else
            {
                continue;
            }

        }

        return result;
    }

    string decrypt(string text) override
    {
        string result = text;
        int keyIndex = 0;

        for (char &c : result)
        {
            if (isalpha(c))
            {
                char base;
                if (isupper(c))
                {
                    base = 'A';
                } 
                else
                {
                    base = 'a';
                }
                int shift = toupper(key[keyIndex % key.length()]) - 'A';

                c = char((c - base - shift + 26) % 26 + base);

                keyIndex++;
            }
            else
            {
                continue;
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
        int n = text.length();
        int m = key.length();
        string result = text;

        for (int i = 0; i < n; i++)
        {
            result[i] = text[i] ^ key[i % m]; //just performing XOR operation
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

int generateCaesarKey()
{
    return rand() % 25 + 1;   // random number from 1 to 25
}

string generateTextKey()
{
    const string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    string key;
    for (int i = 0; i < 8; i++)
    {
        key += characters[rand() % 26]; //8 random characters from the string
    }

    return key;
}

string toHex(string text)
{
    string hex;
    char buffer[3]; // 2 hex digit and \0

    for (unsigned char c : text) //for 0-255 values
    {
        sprintf(buffer, "%02X", c); // convert to hex and store in buffer
        hex += buffer;
        hex += ' ';
    }

    return hex;
}

string fromHex(string hex)
{
    string result;
    string byteStr;

    for (char c : hex)
    {
        if (c == ' ') 
        {
            continue;   // skip spaces
        }
        byteStr += c;

        if (byteStr.length() == 2)
        {
            int value = stoi(byteStr, nullptr, 16);   // convert hex string to integer
            result += char(value); // convert integer to char 
            byteStr = "";
        }
    }

    return result;
}

int main()
{
    srand(time(0));  // seed for the random number generator

    int choice;
    int operation;

    string message;
    string key;
    string result;

    //CIPHER CHOOSING

    cout << "Choose Cipher:\n";
    cout << "1. Caesar Cipher\n";
    cout << "2. Vigenere Cipher\n";
    cout << "3. XOR Cipher\n";
    cout << "\nChoice: ";
    cin >> choice;


    // PROMPT TO DISPLAY FOR KEY 

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
        return 1; // telling computer somethings wrong
    }
    cin.ignore(); // ignore \n

    // OPERATION CHOOSING

    cout << "\nChoose operation:\n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "\nChoice: ";
    cin >> operation;
    cin.ignore();

    // MESSAGE INPUT

    if (choice == 3 && operation == 2) 
    {
        cout << "\nEnter message (paste the hex bytes exactly as shown, e.g. \"05 00 07\"): ";
    }
    else
    {
        cout << "\nEnter message: ";
    }
    getline(cin, message);

    // DIRECTING FLOW TO THE CIPHER CLASSES AND INPUT KEYS

    Cipher* cipher = nullptr; //safety against garbage value

    if (choice == 1)
    {
        int shift;

        cout << "\nEnter Caesar key as a number (or -1 for random): ";
        cin >> shift;

        if (shift == -1)
        {
            shift = generateCaesarKey();
            cout << "Generated key: " << shift << endl;
        }

        cipher = new CaesarCipher(shift);
    }
    else
    {
        cout << "\nEnter " << keyPrompt << " key (press R for random): ";
        getline(cin, key);

        if (key == "R" || key == "r")
        {
            key = generateTextKey();
            cout << "Generated key: " << key << endl;
        }

        if (choice == 2)
        {
            cipher = new VigenereCipher(key);
        }
        else if (choice == 3)
        {
            cipher = new XORCipher(key);
        }
    }

    if (operation == 1)
    {
        result = cipher->encrypt(message);

        if (choice == 3)
        {
            cout << "\nEncrypted (hex): " << toHex(result) << endl;
        }
        else
        {
            cout << "\nEncrypted: " << result << endl;
        }
    }
    else if (operation == 2)
    {
        if (choice == 3)
        {
            string rawBytes = fromHex(message);
            result = cipher->decrypt(rawBytes);
        }
        else
        {
            result = cipher->decrypt(message);
        }

        cout << "\nDecrypted: " << result << endl;
    }
    else
    {
        cout << "Invalid operation.\n";
    }

    delete cipher;

    return 0;
}