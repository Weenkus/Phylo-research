

inputFileName = "/home/weenkus/workspace/Phylo-research/results/megablast/mb_q25_t1.txt"
outputLine = ''

outputLine = 'ms,sequence,query length\n'
with open(inputFileName) as f:
    for line in f:
        print (line)

        # query name line
        if "query" in line:
            chunks = line.split("_")
            smallChunks = chunks[1].split("query")
            outputLine = outputLine + chunks[0] + ',' +  smallChunks[0] + '\n'
        # number line
        else:
            chunks = line.split(" ")
            outputLine = outputLine + chunks[0] + ','

output = open("/home/weenkus/workspace/Phylo-research/results/megablast/mb_q25_t1.csv","w")
output.write(outputLine)