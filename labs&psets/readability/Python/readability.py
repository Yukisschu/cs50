from cs50 import get_string

l = 0
w = 0
s = 0
text = get_string("Text: ")
ends = ['.', '!', '?']

for letter in range(len(text)):
    if text[letter].isalpha():
        l += 1
    elif text[letter] == ' ':
        w += 1
    elif text[letter] in ends:
        s += 1
w += 1
L = l / w * 100
S = s / w * 100
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
