from cs50 import get_int
from sys import exit


def main():
    card = get_int("Please enter your card's number: ")

    digits = []

    evenDigits = []
    oddDigits = []
    otherDigit = True

    for digit in str(card):
        digits.append(digit)
        if otherDigit:
            evenDigits.append(int(digit) * 2)
            otherDigit = False
        else:
            oddDigits.append(digit)
            otherDigit = True

    total = sumDigits(oddDigits) + sumDigits(evenDigits)

    if total % 10 != 0:
        print("INVALID\n")
        exit()

    if int(digits[0]) == 4:
        print("VISA\n")
    elif int(digits[0]) == 3 and int(digits[1]) in [4, 7]:
        print("AMEX\n")
    elif int(digits[0]) == 5 and int(digits[1]) in [1, 2, 3, 4, 5]:
        print("MASTERCARD\n")


def sumDigits(digits):
    total = 0
    for digit in digits:
        if int(digit) > 9:
            for i in str(digit):
                total += int(i)
        else:
            total += int(digit)
    return total


main()