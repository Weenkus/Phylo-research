print("Starting to parse the file...")

fName = "/home/weenkus/workspace/queries/hs-blastn-0.0.4+-src/hsblastnResultThread4UNparsed.txt"
output = open("/home/weenkus/workspace/results/hsblastnThread4.csv", "w+")
outString = "preprocessing time, sequence, query length, query numeration, query time\n"

count = 0
with open(fName) as f:
    for line in f:
        if line == "":
            continue
        print (line)
        if line.find("[HS-BLASTN] done") != -1:
            count = count + 1
            chunks = line.split(" ")
            if count % 2 == 0:
                outString = outString + "," + chunks[4] + "\n"
            else :
                outString = outString + chunks[4] + ","
        if line.find("[HS-BLASTN] Processing") != -1:
            chunks = line.split(" ")
            first = chunks[2].split("_")[0].split("/")[1]
            second = chunks[2].split("_")[1].split(".")[0].split("q")
            outString = outString + first + "," + second[0] + ",q" + second[1]

output.write(outString)
output.close()
print("Finished")
