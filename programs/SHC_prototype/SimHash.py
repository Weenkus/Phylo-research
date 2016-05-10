import hashlib

MD5_LENGTH_BIT = 128
MD5_LENGTH_HEX = 32
HEX_SCALE = 16
BINARY_SCALE = 2
UTF_8 = 'utf-8'

SLIDING_WINDOW_LENGTH = 3


def simhash(text):
    sliding_window_length = SLIDING_WINDOW_LENGTH
    sh = [0] * MD5_LENGTH_BIT
    for i in range(0, len(text) - sliding_window_length):
        word = text[i:i+sliding_window_length]
        bit_hash = hex_to_binary(hash_md5(word), MD5_LENGTH_BIT)
        i = 0
        for bit in bit_hash:
            if bit == '1':
                sh[i] += 1
            else:
                sh[i] -= 1
            i += 1

    bit_sh_list = sh_to_bit(sh)
    bit_sh = ''.join(str(v) for v in bit_sh_list)  # Turn list into a string
    return bit_sh


def hash_md5(word):
    return hashlib.md5(word.encode(UTF_8))


def hex_to_binary(hex_value, length):
    hex_value = bin(int('1'+str(hex_value.hexdigest()), HEX_SCALE))[3:]  # Don't remove leading zeroes
    while len(hex_value) < length:
        hex_value = '0' + hex

    return hex_value


def sh_to_bit(final_sh):
    i = 0
    for bit in final_sh:
        if int(bit) >= 0:
            final_sh[i] = 1
        else:
            final_sh[i] = 0
        i += 1
    return final_sh
