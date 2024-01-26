from cs50 import get_string

number = get_string("Number: ")

if not (number.isdigit()):
    number = get_string("Number: ")


length = len(number)
sum = 0

for digit in range(length - 2, -1, -2):
    tmp = int(number[digit]) * 2
    sum += tmp // 10 + tmp % 10

for digit in range(length - 1, -1, -2):
    sum += int(number[digit])

reminder = int(sum % 10)

if (reminder == 0):
    if len(number) == 15 and number[0] == '3' and (number[1] == '4' or number[1] == '7'):
        print("AMEX")

    elif len(number) == 16 and number[0] == '5' and number[1] in ['1', '2', '3', '4', '5']:
        print("MASTERCARD")

    elif length == 13 or length == 16 and number[0] == '4':
        print("VISA")

    else:
        print("INVALID")

else:
    print("INVALID")
