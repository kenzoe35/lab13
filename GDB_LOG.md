# GDB log

One dated section per week. Paste the commands you used and the output you saw, then explain what it means in your own words. Pasted output with no explanation earns partial credit at most.

## Week 12 (Lab 12)

### The constructor chain

Commands, in the order you typed them, with one line on what each did:

Backtrace inside `Hangman::Hangman` (paste it):

Backtrace inside `Game::Game` (paste it):

Where `finish` returned to:

Order of destructor breakpoints when the program ended:

Construction order and destruction order, as read from the backtraces:

### What a base pointer shows

`print hangman` (paste it):

`print *g` (paste it):

What is different, and why:

`ptype Hangman` and `ptype g` (paste them):

One sentence on what `ptype Hangman` revealed about inheritance:

## Week 13 (Lab 13)

Each partner writes their own section. Put your name here:

### A Game pointer with a virtual play()

`set print object on`, then `print *g` (paste it). What changed from Week 12?

`info vtbl *g` (paste it). Which functions are in the table?

Where `step` into `g->play()` landed, and how that compares with Week 12:

### A Monster pointer

`print *monster` and `ptype monster` with `set print object on` (paste them). Which shows the derived object, and which still shows the base type?

`info vtbl *monster` for a Goblin, then for a Troll (paste both). Compare the entries:

Where `step` into `monster->attack_damage()` landed for each kind:
