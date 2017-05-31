/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Rik Honcoop
 *
 * Created on 28 May 2017, 01:36
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include "Encryption.hh"
using namespace std;

/*
 *
 */
int main(int argc, char** argv) {
   cout << "Encrypt with locked key: 1134134!" << endl;

   Encryption * test = new Encryption(1134134);
   string testString = "TEST string with fixed key";

   cout << "Plain String: " << testString << endl;
   cout << "Encrypted String: " << test->Encrypt(testString) << endl;
   cout << "Decrypted String: " << test->Decrypt(test->Encrypt(testString)) << endl;
   cout << endl;

   cout << "Encrypt with user specific key!" << endl;

   Encryption * testObj2 = new Encryption();
   string testString2 = "TEST string with flexible key. test1234567";

   cout << "Plain String: " << testString << endl;
   cout << "Encrypted String with flexible key: 1337: " << testObj2->Encrypt(testString,1337) << endl;
   cout << "Decrypted String with flexible key: 1337: " << testObj2->Decrypt(testObj2->Encrypt(testString,1337),1337) << endl;
   cout << "Decrypted String with wrong flexible key: 7331: " << testObj2->Decrypt(testObj2->Encrypt(testString, 1337),7331) << endl;


   cout << "Done!" << endl;
   cin.get();
   delete test;
   return 0;
}

