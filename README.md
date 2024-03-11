<h1 align="center">Repetitive sequence</h1>

<h4 align="center">A data structure designed to be used efficiently in situations where intervals of consecutive keys are associated with the same value.</h4>

## Project Overview

`RepetitiveSequence<Key,Value>` is a data structure that associates keys of type `Key` with values of type `Value`.  It is designed to be used efficiently in situations where intervals of consecutive keys are associated with the same value. 

`RepetitiveSequence<Key,Value>` is implemented on top of `std::map`.  Initially, the whole range of `Key` is associated with a given initial value, passed to the constructor of the `RepetitiveSequence<Key,Value>` data structure.  Each key-value-pair (key,value) in `RepetitiveSequence<Key,Value>::intervals` means that the value `value` is associated with all keys from `key` (including) to the next key (excluding) in `intervals`.  The member `RepetitiveSequence<Key,Value>::every` holds the value that is associated with all keys less than the first key in `interval`.

Example: Let `rs` be an instance of `RepetitiveSequence<int,char>` where

```C++
rs.intervals=={(1,'B'),(3,'A')};
rs.every=='A';
```

Then `rs` represents the mapping

```C++
...
-2 -> 'A'
-1 -> 'A'
0 -> 'A'
1 -> 'B'
2 -> 'B'
3 -> 'A'
4 -> 'A'
5 -> 'A'
...
```

## Usage Guide

From your command line:

```Bash
$ make # Compile
$ ./test_repetitive_sequence # Run tests
```

## License

GPL-3.0-or-later
