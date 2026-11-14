# Polymorphism notes

Answer in your own words. Use the words **static dispatch** and **dynamic dispatch**.

## 1. The non-virtual destructor

What did the sanitizer report when `~Game` was not virtual? Explain which destructor ran and which did not.
    It cannot compile, as fake game cannot override.
    FakeGame::~FakeGame()’ marked ‘override’, but does not override
   17 |   ~FakeGame() override { --live_fakes; }
      |   ^
    Without a virtual destructor, the compiler uses static dispatch as default. It invokes the non virtual version
    of ~Game, which violates override

## 2. Game is abstract

In two sentences, explain why `Game g;` no longer compiles.
    Game is now abstract since it contains a virtual function. C++ cannot create an object directly

## 3. override

What does `override` protect you from? Give an example of a mistake it catches.
    override protects you from spelling mistakes and parameter mismatches. For example, if you accidentally misspell a function name you meant to update, the compiler catches the mistake immediately instead of silently treating it as a brand-new function.

## 4. Last week versus this week

Repeat the Week 12 experiment: `Game *g = &hangman; g->play();`. What printed last week, and what prints now? Name the kind of dispatch that happened each time.
    Last week, calling g->play() used static dispatch, meaning it just looked at the pointer type and ran the generic Game version. This week, it uses dynamic dispatch, meaning the program checks what the object actually is at runtime and correctly runs Hangman::play().
