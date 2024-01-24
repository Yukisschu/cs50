### Recover Deleted Photos from Memory Card 

---

JPEGs have "signatures," patterns of bytes that can distinguish them from other file formats. Specifically, the first three bytes of JPEGs are `0xff 0xd8 0xff` from first byte to third byte, left to right. The fourth byte, meanwhile, is either `0xe0`, `0xe1`, `0xe2`, `0xe3`, `0xe4`, `0xe5`, `0xe6`, `0xe7`, `0xe8`, `0xe9`, `0xea`, `0xeb`, `0xec`, `0xed`, `0xee`, of `0xef`. Put another way, the fourth byte's first four bits are `1110`.

Digital cameras tend to store photographs contiguously on memory cards, whereby each photo is stored immediately after the previously taken photo. Accordingly, the start of a JPEG usually demarks the end of another. However, digital cameras often initialize cards with a FAT file system whose "block size" is 512 bytes (B). 

This program iterates over a copy of a memory card:
- Read 512 of them at a time into a buffer.
- Look for JPEGs' signatures. Each time find a signature, open a new file for writing and start filling that file with bytes from the memory card, closing that file only once encounter another signature. 