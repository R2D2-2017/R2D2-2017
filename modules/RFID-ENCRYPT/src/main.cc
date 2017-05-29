/**
 * \file
 * \brief     test main
 * \author    Rik Honcoop
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include "Encryptie.hh"
using namespace std;


int main(int argc, char** argv) {
    cout << "Encrypt with locked key: 1134134!" << endl;

    Encryptie * test = new Encryptie(1134134);
    string testString = "TEST string with fixed key";

    cout << "Plain String: " << testString << endl;  
	cout << "Encrypted String: " << test->Encrypt(testString) << endl;
    cout << "Decrypted String: " << test->Decrypt(test->Encrypt(testString)) << endl;
    cout << endl;

    cout << "Encrypt with user specific key!" << endl;

    Encryptie * testObj2 = new Encryptie();
    string testString2 = "TEST string with flexible key. test1234567";

    cout << "Plain String: " << testString << endl;
    cout << "Encrypted String with flexible key: 1337: " << testObj2->Encrypt(testString,1337) << endl;
    cout << "Decrypted String with flexible key: 1337: " << testObj2->Decrypt(testObj2->Encrypt(testString,1337),1337) << endl;
    cout << "Decrypted String with wrong flexible key: 7331: " << testObj2->Decrypt(testObj2->Encrypt(testString, 1337),7331) << endl;

	cin.get();

    cout << "Done!" << endl;
    delete test;
    return 0;
}

