# Spell Checker via HASH TABLE implementation

## This program takes a .txt dictionary file of any size and loads it into memory via a HASH TABLE. 

### Usage:

```
./speller.c <dictionary.txt> <text.txt>
```



#### ONLY the HASH TABLE code (dictionary.c and dictionaryt.h) is my own. This repo is my implementation of CS50's "speller" problem and as such part of the code (speller.c) was pre completed.


This repo shows my understanding and ability to create a dynamically sized hash table. Provided in the repo are a number of resources in order to try and test the program:

* Dictionaries (first arg)
    * large - containts 143,092 words.
    * small- contains 2 words.
* Texts (second arg)
    * Assortment of texts of varings sizes.
    * Contain misspelled words.
* Keys 
    * List of incorrect words in each text.
    * Used to confirm output of program.
