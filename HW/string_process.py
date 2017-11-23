# -*- coding: utf-8 -*-
import sys

string = ''
keywords = []

string_input = str(sys.argv[1])
keywords_input = str(sys.argv[2])
csv_output = str(sys.argv[3])

with open(string_input) as f:
    string = str(f.read())
with open(keywords_input) as f:
    keywords = str(f.read()).split()

outputFile = open(csv_output, 'w')

keywords.sort()
for x in keywords:
    posi = 0
    outputFile.write(x)
    while (string[posi + 1:].find(x) != -1):
        posi = posi + string[posi:].find(x) + 1
        outputFile.write(',')
        outputFile.write(str(posi - 1))
    outputFile.write('\n')
outputFile.close()
