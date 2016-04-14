import SimHash
from Bio import SeqIO
from multiprocessing import Pool

MD5_LENGTH_BIT = 128
MD5_LENGTH_HEX = 32
HEX_SCALE = 16
BINARY_SCALE = 2
UTF_8 = 'utf-8'


def main():
    eColi_strains = parse_fasta_file('../../datasets/eColiStrains.fasta')

    #with Pool() as pool:
    #    sims = pool.map(SimHash.simhash, eColi_strains.values())
    for seq_id, seq in eColi_strains.items():
       eColi_strains[seq_id] = SimHash.simhash(seq)

    #print(sims)
    #print(sims.sort())
    print(eColi_strains)
    print()

    for k, v in eColi_strains.items():
        print(k, v)

    #print(hem_distance('00101001010111101011000111100000110000010000001100100001000001010101011111111011110000001101001100011001010111100010010010110110',
    #                   '00101001011111000010000101100010100000011111001100110010000011010000001011111110100010000001110110011000010011101110011110111110'))


def hem_distance(str1, str2):
    assert len(str1) == len(str2)
    diffs = 0
    for ch1, ch2 in zip(str1, str2):
            if ch1 != ch2:
                    diffs += 1

    return diffs


def parse_fasta_file(file_path):
    fasta_sequences = SeqIO.parse(open(file_path), 'fasta')
    eColi_strains = {}
    for fasta in fasta_sequences:
        name, sequence = fasta.id, str(fasta.seq)
        eColi_strains[name] = sequence

    return eColi_strains

if __name__ == '__main__':
    main()
