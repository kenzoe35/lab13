# Inheritance notes

Answer in your own words. Use your GDB log for the constructor and destructor order.

## 1. Overriding or hiding?

`Game *g = &hangman; g->play();` What printed?

Is the derived `play()` overriding or hiding the base `play()`? How would a call through a `Game *` show you which one it is?

## 2. Slicing

`Game copy = hangman;` What was lost? Explain slicing.

## 3. protected

What does `protected` allow that `private` does not? Why is `set_score` `protected` instead of `public`?
