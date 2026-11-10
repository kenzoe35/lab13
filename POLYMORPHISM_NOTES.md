# Polymorphism notes

Answer in your own words. Use the words **static dispatch** and **dynamic dispatch**.

## 1. The non-virtual destructor

What did the sanitizer report when `~Game` was not virtual? Explain which destructor ran and which did not.

## 2. Game is abstract

In two sentences, explain why `Game g;` no longer compiles.

## 3. override

What does `override` protect you from? Give an example of a mistake it catches.

## 4. Last week versus this week

Repeat the Week 12 experiment: `Game *g = &hangman; g->play();`. What printed last week, and what prints now? Name the kind of dispatch that happened each time.
