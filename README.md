# Slightly better Huffman + RLE

## Idea

It's a simple observation that makes Huffman coding produce bit sequence that can be more effeciently encoded using RLE afterwards.
After building Huffman tree we assign codes to the nodes. This is usually done by traversing tree from the top and assigning 0 bits
when moving left and 1's when moving right. We can hook in here and provide algorithm that will decide which bit to assign.

In run-length-encoding (RLE) it's better if we have more consequtive bits that are the same. Let's try assigning Huffman codes having
this idea in mind. While building Huffman tree we assign each node an integer value - frequency. The tree is built in a greedy manner
unifying the least frequent nodes. We can use this information during code assignment. Let's assign the same bit value to the most
frequent child as parent assigned to us.

Here is an example of the Huffman coding without optimization described above.

```
               /\              Symbol    Code   Freq
              0  1             ------    ----   ----
             /    \                A     01     35%
            /\     B               B     1      50%
           1  0                    C     001    10%
          /    \                   D     000    5%
         A     /\
              0  1
             /    \
            D      C
```

And these codes use frequencies to assign bits differently.

```
               /\              Symbol    Code   Freq
              1  0             ------    ----   ----
             /    \                A     11     35%
            /\     B               B     0      50%
           1  0                    C     100    10%
          /    \                   D     101    5%
         A     /\
              1  0
             /    \
            D      C
```

Now when we try to encode a string that has correct distribution of chars we get

```
str        BCBBABABDAABCBBCAABBADBADACBBBABABBBAABBBBAABBBBACCABABBBABCBCAACBDABABBAAABBCAAABBADABBABBABBABBABB
w/o        100111011011000010110011100101011101000101000010011110110111101011111010111110100100101101111011001100101010011000011011101010111001010101110100001110111011101110111
with       010000110110101111101000010011110011101011101111000001101100011110000111100001110010011011000110100010011111000101110110011111100100111111001110111001100110011001100
RLE w/o    1001110110114@0101100111001010111010001014@01004@101104@10105@10105@10100100101104@10110011001010100114@01101110101011100101010111014@01110111011101110111
RLE with   014@0110110105@1014@01004@10011101011104@15@0110110004@14@04@14@0111001001101100011010001005@100010111011006@1001006@1001110111001100110011001100
```

As you can we've got a shorter sequence after applying optimization technique described above.

## Results

After testing on some English texts I've estimated that average win is only ~1%.
In order to check the results one can run `make` to check via text in the repo, or just pipe the text into the program. 
