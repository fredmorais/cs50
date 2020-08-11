from sys import argv, exit
from csv import reader
import re


# Checks correct number os arguments
if len(argv) != 3:
    print("Incorrect number of arguments!")
    exit()


# Open CSV and load content into memory
STR = []
people = []
with open(argv[1], "r") as csvfile:
    # pass the file object to reader() to get the reader object
    csv_reader = reader(csvfile)
    # Pass reader object to list() to get a list of lists
    list_of_rows = list(csv_reader)
    # Create list of STR
    STR = list_of_rows[0]
    STR.pop(0)
    # Create list of people
    people = list_of_rows
    people.pop(0)


# Open DNA sequence and load content into memory
data = ""
with open(argv[2], "r") as dnafile:
    data = dnafile.read()


# Compute the highest number of repeats for each STR
strCount = {}
for i in STR:
    maxCount = 0
    currentCount = 0
    cursor = 0
    while cursor <= len(data):
        x = data.find(i, cursor)
        if x == cursor or (cursor == 0 and x > 0):
            cursor = x + len(i)
            currentCount += 1
        elif x == -1:
            if maxCount < currentCount:
                maxCount = currentCount
            currentCount = 1
            break
        else:
            if maxCount < currentCount:
                maxCount = currentCount
            currentCount = 1
            cursor = x + len(i)
    strCount.update({i: maxCount})


# Check against database to return the identified person. Print "No match" if no match is made
peopleDNA = []
for counter, person in enumerate(people):
    name = people[counter][0]
    dnaData = {}
    for counter2, data in enumerate(person):
        if counter2 != 0:
            dnaData.update({STR[counter2 - 1]: int(person[counter2])})
    peopleDNA.append({name: dnaData})

for counter, person in enumerate(peopleDNA):
    if person.get(people[counter][0]) == strCount:
        print(people[counter][0])
        exit()

print("No match")
