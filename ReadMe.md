## Tuple's parsing & tests

This repository contains a template function that being initially developed 
for easy CSV like content parsing, through generic programming is now able
to achieve much more than that. The code solves much of the limitations I've
found in other common algorithms:

+ Embed the concept of `lines`, by giving a way to choose EOL sequence.
+ Embed the concept of `fields` by giving a way to choose a fields separator.
+ `EOL` and the fields are collections (i.e. not a single `char`). 
+ Can skip lines from the beginning (by allowing being used iteratively).
+ Can limit the number of lines to be read (by allowing partial parsing).
+ Allows multiple unintended usages (i.e. splitting strings, tokenizing...)

### Performance
The overall complexity in the worst case should be of order `N`, where `N` 
is the size of the input.

### Building
Just use the `parse_tuple.hpp` file wherever you need it. Some template
features used by the code requires a C++ 17 capable compiler; older 
compiler may generate some warning, unwanted behaviour, or not compile
at all. In those cases be sure to run at least the basic functional tests
given.

### Tests
In the code are given some basic functional tests which demonstrate some
use cases and check expected behaviour is confirmed for some edge cases.
The tests make use of the Catch2 test framework.

### Contributions
Contribution are welcome in any form they came. I hope this content has
been and will be useful to you, and let's this be for other newcomers. 

### Licensing (MIT License)
Basically the software is provided as is, without any warranty. You can
use and distribute it freely or commercially provided you don't remove 
the license notice and the attributions. See `License.md`.
