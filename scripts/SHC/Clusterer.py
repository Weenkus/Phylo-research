

def main():
    with open('completeGenomesSimHash8.txt') as f:
        lines = f.read().splitlines()

    with open('completeGenomesSummery.txt') as f:
        genomeNames = f.read().splitlines()

    genome_key = create_genome_name_key_dictionary(genomeNames)
    #print(genome_key)

    dictionary = make_dictionary(lines)
    already_gruped = []

    for k, v in dictionary.items():
        if v in already_gruped:
            continue

        print('********************************************************************************************************'
              '****************************************************')
        key = k.split("|")[3]
        print(genome_key[key])
        print(k, v)

        for k2, v2 in dictionary.items():
            if v == v2 or v2 in already_gruped:
                continue

            if hem_distance(v, v2) <= 3:
                already_gruped.append(v2)
                key = k2.split("|")[3]
                print(genome_key[key])
                print(k2, v2)


def make_dictionary(list):
    dictionary = {}
    for v in list:
        dictionary[v.split(' ')[0]] = v.split(' ')[1]

    return dictionary


def hem_distance(str1, str2):
    assert len(str1) == len(str2)
    diffs = 0
    for ch1, ch2 in zip(str1, str2):
            if ch1 != ch2:
                    diffs += 1

    return diffs


def create_genome_name_key_dictionary(genomeNames):
    d = {}
    i = 0
    for v in genomeNames:
        if i == 0:
            name = v
        if i == 2:
            d[v.split(" ")[0]] = name
        if i == 3:
            i = -1
        i += 1

    return d

if __name__ == '__main__':
    main()
