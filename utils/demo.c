/**
 * Copyright 2025 MFtalk    
 * Demostration of encryption.h alias AmberChriffre....
 */

#include "encryption.h"
#include <stdio.h>

#define MAXTEXTLENGHT 350



int main() {
    printf("skript start\n");


    unsigned char text[MAXTEXTLENGHT] = "Hello World! This is AmberChriffre. An advanced, but simple and hard-to-crack chiffre developed by ItsGraphax, originally for AmberOS in OSWars 10 for scratch. It has now been made **even** better with v3! Am I the only one who's confused tho at why the heck theres a big G and a big D in for AmberOS and been?";
    unsigned char key[MAXTEXTLENGHT] = "pizzalover122";
    const unsigned int seed1 = 67676767;
    const unsigned int seed2 = 7890345;

    printf("\nORIGINAL: `%s`", text);

    //unsigned char *result = baseEncryption(text, key, &seed1, &seed2, 1);
    unsigned char *result = encrypt(text, key, &seed1, &seed2);

    printf("\nENCRYPTED: `%s`", result);

    unsigned char *decrypted = decrypt(result, key, &seed1, &seed2);

    printf("\nDECRYPTED: `%s`",decrypted);

   //free((void *)v);

   return 0;
}