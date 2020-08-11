from sys import argv, exit
from csv import reader
from cs50 import SQL


# Setup database connection
db = SQL("sqlite:///students.db")

# Check correct number of arguments
if len(argv) != 2:
    print("Incorrect number of arguments")
    exit()

# Load csv file
characters = []
with open(argv[1], "r") as csvfile:
    # Pass the file object to reader() to get the reader object
    csv_reader = reader(csvfile)
    # Pass reader object to list() to get a list of lists
    characters = list(csv_reader)
    characters.pop(0)

#For each student, insert into database
sql = "INSERT INTO students (first, middle, last, house, birth ) VALUES (%s, %s, %s, %s, %s)"
for character in characters:
    #Check if student has 2 or 3 names
    names = character[0].split()
    print(names)
    if len(names) == 3:
        val = (names[0], names[1], names[2], character[1], character[2])
    else:
        val = (names[0], None, names[1], character[1], character[2])
    db.execute(sql, val)
