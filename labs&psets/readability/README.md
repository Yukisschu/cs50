### Readability Test using Coleman-Liau index 

---
A number of “readability tests” have been developed over the years that define formulas for computing the reading level of a text. One such readability test is the Coleman-Liau index. The Coleman-Liau index of a text is designed to output that (U.S.) grade level that is needed to understand some text. The formula is:
`index = 0.0588 * L - 0.296 * S - 15.8`
where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.

This program calculates the approximate grade level needed to comprehend some text in C and Python. 
- Output “Grade X” is the grade level computed, rounded to the nearest integer. 
- If the grade level is 16 or higher (equivalent to or greater than a senior undergraduate reading level), the program outputs “Grade 16+”.
- If the grade level is less than 1, your program should output “Before Grade 1”.