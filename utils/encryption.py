from math import ceil, floor

# ALL_LETTERS = string.printable # should be hardcoded and the same for ALL versions in all languages
ALL_LETTERS = ""
for i in range(32, 127):
    ALL_LETTERS += chr(i)

INVALID = "¤"
randtick = 1

found_letters = []
for letter in ALL_LETTERS:
    if letter in found_letters:
        print(f"{letter} is double!")
        exit(1)
    found_letters.append(letter)


def randseed(seed: int, max: int) -> int:
    global randtick
    random = (ceil((532 - randtick) * 2.3)) + floor(seed / 3)
    random = (random % max) + 1
    randtick += 1
    return random

#shuffle
checked_keys = []
letters = ""
i = randseed(76549134735931, len(ALL_LETTERS))
for _ in range(len(ALL_LETTERS)):
    while i in checked_keys:
        i = randseed(4827532021, len(ALL_LETTERS))
    letters += ALL_LETTERS[i - 1]
    checked_keys.append(i)


def generate_keysum(key: str) -> int:
    key_sum = 0
    for key_char in key:
        if not key_char in letters:
            key_char = INVALID

        key_val = letters.index(key_char)
        key_sum += key_val

    return key_sum


def __base_crypt(text: str, key: str, mode: int) -> str:
    key_sum: int = generate_keysum(key)
    text_keysum: int = generate_keysum(text)
    key_i: int = (round(len(key) / 3) + key_sum + text_keysum) % len(key)
    output = ""

    for char in text:
        key_char: str = key[key_i]
        if not key_char in letters:
            key_char = INVALID
        key_val = letters.index(key_char)

        if not char in letters:
            char = INVALID
        char_val = letters.index(char)

        encrypted_val: int = (char_val + (key_val * mode)) % len(letters)

        encrypted_char: str = letters[encrypted_val]

        output += encrypted_char
        key_i = (key_i + 1) % len(key)

    return output


def encrypt(text: str, key: str) -> str:
    return __base_crypt(text=text, key=key, mode=1)


def decrypt(text: str, key: str) -> str:
    return __base_crypt(text=text, key=key, mode=-1)


if __name__ == "__main__":
    import json

    v = encrypt(
        "hello!",
        "pizzalover122",
    )
    print(v)
    print(decrypt(v, "pizzalover122"))