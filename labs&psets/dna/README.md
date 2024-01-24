### Validate the Credit Cards in C and Python

---

## Types of Credit Card
Credit card numbers have specific patterns for different card networks. For instance:
- American Express: Starts with 34 or 37
- MasterCard: Starts with 51, 52, 53, 54, or 55
- Visa: Starts with 4

In addition to these patterns, credit card numbers also apply a "checksum" to detect errors without querying a database.

## Luhn's Algorithm

Hans Peter Luhn devised an algorithm to syntactically validate credit card numbers. The process involves:

1. Multiply every other digit by 2, starting from the second-to-last digit, and sum the digits of the products.
2. Add the sum to the sum of the digits that weren't multiplied by 2.
3. If the total's last digit is 0 (or the total modulo 10 is congruent to 0), the number is valid.
   
This program determines whether a provided credit card number is valid according to Luhn's algorithm.

