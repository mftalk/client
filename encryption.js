function mod(a, b) {
  return ((a % b) + b) % b;
}


let asciiLetters = '';

for (let i = 32; i <= 126; i++) {
    asciiLetters += String.fromCharCode(i);
}

const INVALID = "¤";
//const ALL_LETTERS = asciiLetters + INVALID;
const ALL_LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890,.-;:_¦@#°§¬|¢[]{}+\"*%&/()= °~^'?`!"
let randtick = 1;

let found_letters = [];
for (const letter in ALL_LETTERS){
    if (letter in found_letters){
        throw new Error(`${letter} is double!`);
    }
    found_letters.push(letter);
}

/**
 * 
 * @param {number} seed 
 * @param {number} max 
 * @returns {number} random
 */
function randseed(seed, max){
    let random;
    random = (Math.ceil((532 - randtick) * 2.3)) + Math.floor(seed / 3);
    random = (random % max) + 1;
    randtick ++;
    return random;
}

let checked_keys = [];
let letters = "";
let i = randseed(76549134735931, ALL_LETTERS.length);
for (const _ of ALL_LETTERS){
    while (checked_keys.includes(i)){
        i = randseed(4827532021, ALL_LETTERS.length);
    }
    letters += ALL_LETTERS[i - 1];
    checked_keys.push(i);
}

/**
 * 
 * @param {string} key 
 * @returns {number} key_sum
 */
function generate_keysum(key){
    let key_sum = 0;
    for (let key_char in key){
        if (!letters.includes(key_char)) {
            key_char = INVALID;
        }
        let key_val = letters.indexOf(key_char);
        key_sum += key_val;
    }
    return key_sum;
}

/**
 * (en/de)crypt the provided text
 * @param {string} text 
 * @param {string} key 
 * @param {number} mode 1 = encrypt, -1 = decrypt
 * @returns  {string} output
 */
function base_crypt(text, key, mode){
    let key_sum = generate_keysum(key);
    let key_i = (Math.round(key.length / 3) + key_sum) % key.length;
    let output = "";

    for (let char of text) {
        let key_char = key[key_i]
        if (!letters.includes(char)) key_char = INVALID;

        let key_val = letters.indexOf(key_char);

        if (!letters.includes(char)) {
            console.log("char:", char);
            char = INVALID;
        }
        let char_val = letters.indexOf(char);
        
        let encrypted_val = mod((char_val + (key_val * mode)), letters.length);
        
        let encrypted_char = letters[encrypted_val];

        output += encrypted_char;
        key_i = (key_i + 1) % key.length;
    }
    return output;
}

export function encrypt(text, key) {
    return base_crypt(text, key, 1);
}

export function decrypt(text, key) {
    return base_crypt(text, key, -1);
}

const v = encrypt(
        "Hello World! This is AmberChriffre. An advanced, but simple and hard-to-crack chiffre developed by ItsGraphax, originally for AmberOS in OSWars 10 for scratch. It has now been made **even** better with v2! Am I the only one who's confused tho at why the heck theres a big G and a big D in for AmberOS and been?",
        "pizzalover122",
    );
console.log("%c" + "encrypted:", "color:green;font-weight:bold;", v);
console.log("%c" + "decrypted:", "color:green;font-weight:bold;", decrypt(v, "pizzalover122"));

