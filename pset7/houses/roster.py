from sys import argv, exit
from csv import reader
from cs50 import SQL


# Setup database connection
db = SQL("sqlite:///students.db")

# Check correct number of arguments
if len(argv) != 2:
    print("Incorrect number of arguments")
    exit()

sql = f"select first, middle, last, birth from students where house = '{argv[1]}' order by last asc, first asc;"
result = db.execute(sql)

for people in result:
    name = ""
    if bool(people["middle"]):
        name = people["first"] + " " + people["middle"] + " " + people["last"]
    else:
        name = people["first"] + " " + people["last"]

    print(name, ", born ", people["birth"], sep="")