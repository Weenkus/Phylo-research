HASH_LENGTH = 64
SEQUENCE_ID_LEN = 60
HASH = 'Boost'
WINDOWS_SIZE = 3


blast_hits_file_path = "/home/weenkus/workspace/Phylo-research/results_simHash/blast_comparison/" \
                       "ENSP1146/ENSP00000001146_hits_blast.txt"

hash_hits_file_path = "/home/weenkus/workspace/Phylo-research/results_simHash/blast_comparison/" \
                      "ENSP1146/ENSP1146_hits_boost_3.txt"

output_file_path = "ENSP1146_boost_3_compare.txt"
csv_comparison = "ENSP1146_boost_3_compare.csv"

blast_hits_file = open(blast_hits_file_path, "r")
hash_hits_file = open(hash_hits_file_path, "r")
output_file = open(output_file_path, "w")
csv_file = open(csv_comparison, "w")

blast_hits_list = blast_hits_file.read().split("\n")
hash_hits_list = hash_hits_file.read().split("\n")


porgess = 0
csv_string = 'window_size,hash,ham_distance,similarity,error,blast_output,bitscore,eValue'
print(csv_string, file=csv_file)

for blast_hit in blast_hits_list:

    porgess += 1
    print(porgess, len(blast_hits_list))

    for hash_hit in hash_hits_list:

        blast_string_chunks = blast_hit.split("\t")
        hash_string_chunks = hash_hit.split(" ")

        if blast_string_chunks[0] == hash_string_chunks[0] and blast_string_chunks[1] == hash_string_chunks[1]:

            sequence_ids = blast_string_chunks[0] + " " + blast_string_chunks[1]

            if len(sequence_ids) < SEQUENCE_ID_LEN:
                while len(sequence_ids) < SEQUENCE_ID_LEN:
                    sequence_ids += " "

            sim = str(float(HASH_LENGTH-int(hash_string_chunks[2]))/HASH_LENGTH*100)

            out_string = '{sequence_ids} {ham_distance:2} {similarity:9} {error:05.2f}  | {blast_output}'.format(
                sequence_ids=sequence_ids,
                ham_distance=hash_string_chunks[2],
                error=abs(float(sim)-float(blast_string_chunks[2])),
                similarity=sim,
                blast_output=' '.join(blast_string_chunks[2:])
            )

            print(out_string, file=output_file)

            csv_string = '{window_size},{hash},{ham_distance},{similarity},{error:2f},{blast_output},{bitmap},{eValue}'.format(
                window_size=WINDOWS_SIZE,
                hash=HASH,
                sequence_ids=sequence_ids,
                ham_distance=hash_string_chunks[2],
                error=abs(float(sim)-float(blast_string_chunks[2])),
                similarity=sim,
                blast_output=blast_string_chunks[2],
                bitmap=blast_string_chunks[-1],
                eValue=blast_string_chunks[-2]
            )

            print(csv_string, file=csv_file)

            hash_hits_list.remove(hash_hit)
            break
