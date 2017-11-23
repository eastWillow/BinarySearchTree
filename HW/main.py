# -*- coding: utf-8 -*-
import random
import itertools
import sys
import PyPDF2

passwd = '0z23'
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

SearchResultFile = open('SearchResultFile.csv', 'w')

minPWD = str(sys.argv[4])
maxPWD = str(sys.argv[5])

pdf1File = open('input.pdf', 'rb')
pdf1Reader = PyPDF2.PdfFileReader(pdf1File)
pdfWriter = PyPDF2.PdfFileWriter()
for pageNum in range(pdf1Reader.numPages):
    pageObj = pdf1Reader.getPage(pageNum)
    pdfWriter.addPage(pageObj)

pdfWriter.encrypt(passwd)
pdfOutputFile = open('encrypt.pdf', 'wb')
pdfWriter.write(pdfOutputFile)
pdfOutputFile.close()
pdf1File.close()

pdfEncryptFile = open('encrypt.pdf', 'rb')
pdfEncryptFileReader = PyPDF2.PdfFileReader(pdfEncryptFile)

for x in itertools.product(
    ''.join(chr(x) for x in range(
        min([ord(c) for c in minPWD]),
        max([ord(c) for c in maxPWD]) + 1)), repeat=len(maxPWD)):

    temp = str(''.join(x))
    flag = False
    for y in range(len(maxPWD)):
        if ord(temp[y]) <= ord(maxPWD[y]):
            flag = True
        else:
            flag = False
            break
    if (flag):
        SearchResultFile.write(temp)
        SearchResultFile.write('\n')
        # SearchResultFile.flush()
        print(temp)
        if(pdfEncryptFileReader.decrypt(temp) != 0):
            break

for pageNum in range(pdfEncryptFileReader.numPages):
    pageObj = pdfEncryptFileReader.getPage(pageNum)
    print(pageObj.extractText())

SearchResultFile.close()
pdfEncryptFile.close()
