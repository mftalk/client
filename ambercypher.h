#ifndef MFTALK_LIBRARY_H
#define MFTALK_LIBRARY_H
#endif

#include <stdlib.h>
#include <string.h>
#include <math.h>



//unsigned char * INVALID = "\n";


unsigned int py_mod(const unsigned int a, const unsigned long long int b) {
    const int c_mod = a % (int)b;

    if (c_mod < 0) {
        return (unsigned int)b + c_mod;
    }
    return (unsigned int)c_mod;
}


unsigned char *getAllChars(void) {

    unsigned char * str = malloc((126-32 + 2) * sizeof(unsigned char));
    if (str == NULL) return NULL;

    for (int i=32; i <= 126; i++) {
        str[i-32] = (char)i;
    }

    //str[127-32] = *INVALID;
    str[126-32 + 1] = '\0';

    return str;
}


unsigned int randseed(const unsigned long int seed, const unsigned long long int max, unsigned int *randtick) {
    const double tmp = (532.0 - (double)*randtick) * 2.3;
    const unsigned int part1 = (int)ceil(tmp);
    const unsigned int part2 = (int)floor((double)seed / 3.0);

    const unsigned int random = py_mod(part1 + part2, max);
    *randtick = *randtick + random + 1 + 1;
    return random;
}


int includes(const int *indexElement, const size_t length, const int checkedelement) {
    for (size_t i = 0; i < length; ++i) {
        if (indexElement[i] == checkedelement) return 1;
    }
    return 0;
}



unsigned char *shuffle(const unsigned long int *seed1, const unsigned long int *seed2) {

    unsigned int randint = 1;


    const unsigned char *ALL_LETTERS = getAllChars();
    const size_t lenAllLetters = strlen((char *)ALL_LETTERS);

    int *checked_keys = calloc(lenAllLetters, sizeof(int));

    unsigned char *letters = malloc(lenAllLetters + 1);


    int unsigned i = randseed(*seed1, (int)lenAllLetters, &randint);

    for (size_t j = 0; j < lenAllLetters; ++j) {

        int whileCount= 0;
        while (includes(checked_keys, j, (int)i)){
            ++whileCount;
            i = randseed(*seed2, (int)lenAllLetters, &randint);

            if (whileCount > 30) {
                for (int k = 0; k < (int)lenAllLetters; ++k) {
                    if (!includes(checked_keys, j, k)) {
                        i = k;
                        break;
                    }
                }
                whileCount = 0;
                randint = 1;
                break;
            }
        }
        letters[j] = ALL_LETTERS[i];
        checked_keys[j] = (int)i;

        //i = randseed(seed2, (int)lenAllLetters, &randint);
    }
    letters[lenAllLetters] = '\0';

    free((void *)ALL_LETTERS);
    free(checked_keys);
    //free(letters);
    return letters;
}


unsigned int generate_keysum(const char unsigned str[], const unsigned char letters[]) {
    unsigned int key_sum = 0;
    for (unsigned int i = 0; str[i] != '\0'; i++) {
        int isInStr = 0;
        for(unsigned int j = 0; letters[j] != '\0'; j++) {
            if(str[i] == letters[j]) {
                isInStr = 1;
                key_sum += j;
            }
        }

        if (!isInStr) {
            //printf("invalid!");
            key_sum++;
        }
    }
    return key_sum;
}





unsigned char *baseEncryption(const unsigned char text[], const unsigned char key[], const unsigned long int *seed1, const unsigned long int *seed2, const int mode) {
    unsigned char *letters = shuffle(seed1, seed2);

    unsigned int key_sum = generate_keysum(key, letters);


    const size_t keyLen = strlen((const char *)key);
    const size_t textLen = (int)strlen((const char *)text);

    const size_t lettersLen = strlen((const char *)letters);

    unsigned int key_index = py_mod(((int)round((double)keyLen / 3) + key_sum + textLen), (unsigned int)keyLen);



    unsigned char *output = calloc(textLen + 1, sizeof(unsigned char));


    //printf("\nInvalid: %s\n", *INVALID);

    for (unsigned int i = 0; text[i] != '\0'; ++i) {
        unsigned char key_char = key[key_index];
        unsigned char charInText = text[i];

        //if (!strchr(letters, key_char)) key_char = *INVALID; // TODO: INVALID CARACTERS SHOULD BE SUPPORTED
        const unsigned char *key_charPos = strchr((const char *)letters, key_char);
        //if (!key_charPos) exit(-1); //TODO: FIX
        const unsigned int key_val = key_charPos - letters;

        //if (!strchr(&letters, charInText)) charInText = *INVALID; // " " " " " "
        const unsigned char *charInText_Pos = strchr((const char *)letters, charInText);
        //if (!charInText_Pos) exit(-1); //TODO: FIX
        const unsigned int char_val =  charInText_Pos - letters;

        unsigned int encrypted_val = py_mod((char_val + (key_val * mode)), (unsigned int)lettersLen);

        unsigned char encrypted_char = letters[encrypted_val];

        output[i] = encrypted_char;

        key_index = py_mod((key_index + 1), (unsigned int)keyLen);
    }
    free(letters);
    return output;

}

unsigned char *amberCencrypt(const unsigned char text[], const unsigned char key[], const unsigned long int seed1, const unsigned long int seed2) {
    unsigned char *result = baseEncryption(text, key, &seed1, &seed2, 1);
    return result;
}


unsigned char *amberCdecrypt(const unsigned char text[], const unsigned char key[], const unsigned long int seed1, const unsigned long int seed2) {
    unsigned char *result = baseEncryption(text, key, &seed1, &seed2, -1);
    return result;
}