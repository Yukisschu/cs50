### Encrypt Plain Text with Caesar’s Algorithm

---
The  `caesar` program encrypts messages using Caesar's cipher.

## Encryption Basics

Unencrypted text is generally called _plaintext_. Encrypted text is generally called _ciphertext_. And the secret used is called a _key_.

## Caesar's Cipher

Caesar's algorithm encrypts messages by "rotating" each letter by _k_ positions. The encryption formula is given by:

 {{< katex >}}\\( \(c_i = (p_i + k) \bmod 26\) \\).

where %26 means remainder when dividing by 26.


