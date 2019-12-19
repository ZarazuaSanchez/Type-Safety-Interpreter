# Data Type Safety

This interpreter program developed in C++ detects type-unsafe statements in Python source code. A type-unsafe statement is a statement in which there are operations with unlike data types. (Also see type safe languages and type-unsafe languages.) In the following examples,

1. 1 + "word"
2. 100 + "dog"
3. 50 + "hat"

we are trying to add strings (or words) to ints (or numbers). What is the result?
Let's take a look at operations where we know the results.

Adding numbers, for example

4. 100 + 1 -> 101
5. 0 + 10 -> 10
6. 50 + 50 -> 100,

gives numbers as results
But adding a  number and a word does give a result with real-world meaning.

1. 1 + "word" -> ?
2. 100 + "dog" -> ?
3. 50 + "hat" -> ?.
