# A0: Corpus Dance

Learning Outcomes
-----------------

1. **Write** a Makefile to compile a simple C program.
2. **Use** raw file I/O functions to open and read files.
3. **Create** a program that will parse file content for display.
4. **Use** memory allocator functions.

Specifications
--------------

For this assignment, you will complete a program that counts the number of words in a file. This is similar to the common Linux tool `wc` (word count). In fact, you can check that your program is functioning correctly by running `wc -w` on the provided corpus files.

### Buffering Your Own I/O

You must use raw file I/O for this assignment which means you will be filling a buffer of 1024 bytes using the `read()` system call and then parsing text out of that buffer. You should use `strsep()` to parse the text by space or newline character. This will result in a series of non-whitespace tokens that need to be saved in an **array of structs**. When you reach the end of this series of tokens, two things might happen:

1. The filled buffer ends on a word boundary 😀 **OR**
2. The filled buffer ends in the middle of a word 😕

Because this may happen, **you cannot trust the final token in the buffer to be complete**. You must move the (potentially) partial token to the front of the buffer and then fill the buffer starting from where that token ends (so the information is not overwritten). **This is very difficult to get correct**, and if you do not, the resulting word count will not be correct.

Many functions in the C stdlib return values **that are important, do not ignore them**.

### Array of Structs

We need a data structure where each word is associated with its count. This is a good opportunity to use an **array of structs** where the struct is a data structure that consists of the word and the number of times it occurs in the file. This has already been defined for you and given the type name `WORD_T`. An array of these elements is declared as `words` and the size of that array is being tracked with `total_words`. When you encounter a word from the file (complete token), you need to perform a linear search of the array to see if that word has already been enounctered:

1. If it has, you simply increment the `.count` field from the struct.
2. If this is the first time the word has been countered, you must **resize the array** (using `realloc()`) and add the word and the count of 1 to the end of the array.

Since the `word` field in the struct is an array of 42 characters, you can copy the characters from the token to the field using `strcpy()`. Don't forget a _null-terminator_, though.

### Restrictions

* You must compile your program using the flags `std=gnu11`, `-Werror` and `-Wall`.
* You may not write functions or code outside of the locations indicated with `TODO`s (line 29, lines 32-45, line 48).
* You may not use any file stream functions such as `fopen()`, `fread()` or `fclose()`. If you are unsure if a C stdlib function is banned, please just ask.
* You may not `lseek()` or reposition the file pointer (other than by calling `read()`).
* You may not use a buffer size other than 1024 bytes.

### Submission

Submit only your completed `wc.c` file and associated `Makefile`. When `make` is executed in the directory, a binary named `wc` should be created. If not, the autograder will fail. You can make a submission as many times as you'd like in order to see the autograder feedback. The maximum points you can receive from the autograder is 20 and the remaining 12 points are from code review.

The 🌟 Code Golf score will compare your program against the solution program to determine how many more lines of code you used to complete the program. This score is worth 2 assignment points.

### Functions

Here is a list of functions that are used by the solution program. This might help in completing the assignment.

    close()
    comparator()
    free()
    lfind()
    main()
    memmove()
    open()
    print_and_free()
    printf()
    read()
    realloc()
    strcmp()
    strlen()
    strncpy()
    strsep()

Example
-------

Here's a sample interaction with a working program. **Your program must not print out anything other than what's shown or the autograder will fail**. The `$` character represents the terminal prompt, you do not type this character when executing commands.

    $ ./wc msno.txt
    MissingNo.: 23
    for: 6
    and: 35
    the: 92
    is: 11
    an: 12
    Pokemon: 29
    species: 2
    in: 29
    video: 5
    games: 7
    Red: 5
    Due: 2
    to: 40
    of: 41
    certain: 2
    in-game: 4
    players: 10
    can: 8
    encounter: 7
    a: 32
    glitch.: 2
    graphical: 3
    by: 12
    increasing: 2
    number: 2
    items: 2
    sixth: 2
    player's: 4
    inventory: 2
    glitch's: 2
    guides: 2
    game: 12
    Nintendo: 5
    warned: 3
    that: 20
    encountering: 3
    glitch: 5
    may: 4
    IGN: 2
    MissingNo.'s: 3
    Blue: 4
    was: 5
    one: 3
    most: 2
    glitches: 4
    commented: 2
    on: 9
    its: 5
    role: 2
    Fans: 2
    have: 6
    attempted: 2
    incorporate: 2
    as: 22
    part: 2
    games': 2
    actual: 2
    ==: 10
    Game: 5
    series: 2
    with: 11
    In: 4
    these: 2
    player: 10
    goal: 2
    capture: 3
    creatures: 2
    Pokemon.: 2
    abilities: 2
    other: 2
    Pokemon,: 3
    also: 3
    game's: 7
    such: 4
    travel: 3
    The: 5
    from: 6
    not: 6
    are: 2
    but: 2
    it: 7
    events: 2
    appear: 2
    could: 2
    your: 2
    or: 4
    remove: 2
    several: 2
    games.: 2
    Viridian: 2
    City: 2
    location.: 2
    uses: 2
    move: 2
    Cinnabar: 3
    Island: 2
    up: 2
    generate: 2
    invalid: 2
    area: 2
    within: 2
    data: 4
    be: 5
    encountered: 2
    area.: 2
    this: 4
    used: 2
    tutorial,: 2
    character's: 4
    name: 4
    temporarily: 2
    read: 3
    same: 2
    viewing: 2
    being: 3
    appears: 2
    even: 2
    cut: 2
    commonly: 2
    how: 2
    game,: 2
    article,: 3
    helped: 2
    book: 3
    MissingNo[.]: 2
    his: 3
    Wilma: 2
    Bainbridge,: 2
    then: 2
    2019: 2
    Ars: 2
    at: 2
    belief: 2
    professor: 2
    world: 2
    fan: 2
    theories: 2
    related: 2
    Explained: 2
    -: 2
    
    1274 msno.txt

