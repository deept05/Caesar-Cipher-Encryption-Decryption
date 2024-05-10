#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>

using namespace std;

//  For encryption 

string encryptCaesar(const string& message, int shift)
{
    string encryptedMessage = "";
    for( char c : message)
    {
        if(isalpha(c))
        {
           char shiftedChar = (isupper(c)) ? 'A' + ((c - 'A' + shift) % 26) : 'a' + ((c - 'a' + shift) % 26);
           encryptedMessage = encryptedMessage + shiftedChar;

        } 
        else
        {
            encryptedMessage += c;
        }   
    }
    return encryptedMessage;
}

//  For decryption 

string decryptCaesar(const string& encryptedMessage, int shift)
{
    return encryptCaesar(encryptedMessage, 26-shift);
}

int normalizeShift(int shift)
{
    return (shift % 26 + 26) % 26;
}

int main()
{
    cout << "Welcome to Encryption and Decryption Tool!" << endl;
    int shift;
    string message;

    cout << "Enter the message to Encrypt: ";
    getline(cin, message);

    cout << "Enter the shift value for Caesar cipher: ";
    cin >> shift;
    shift = normalizeShift(shift);

    string encryptMessage = encryptCaesar(message,shift);
    cout << "Encrypted Message : " << encryptMessage << endl;

    string decryptedMessage = decryptCaesar(encryptMessage, shift);
    cout << "Decrypted message: " << decryptedMessage << endl;

    char ConvertCase;
    cout << "Do you want to convert the case of the decrypted message? (y/n): ";
    cin >> ConvertCase;
    if(tolower(ConvertCase) == 'y')
    {
        transform(decryptedMessage.begin(), decryptedMessage.end(), decryptedMessage.begin(), ::toupper);
        cout << "Converted message to uppercase: " << decryptedMessage << endl;

    }

    char writeToFile;
    cout << "Do you want to write the encrypted message to a file? (y/n): ";
    cin >> writeToFile;
    if (tolower(writeToFile) == 'y') {
        ofstream outputFile("encrypted_message.txt");
        if (outputFile.is_open()) {
            outputFile << encryptMessage;
            cout << "Encrypted message written to file successfully." << endl;
        } else {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }

    char readFromFile;
    cout << "Do you want to read an encrypted message from a file and decrypt it? (y/n): ";
    cin >> readFromFile;
    if (tolower(readFromFile) == 'y') {
        ifstream inputFile("encrypted_message.txt");
        if (inputFile.is_open()) {
            string encryptedFromFile;
            getline(inputFile, encryptedFromFile);
            string decryptedFromFile = decryptCaesar(encryptedFromFile, shift);
            cout << "Decrypted message from file: " << decryptedFromFile << endl;
        } else {
            cout << "Error: Unable to open file for reading." << endl;
        }
    }

    return 0;
}

