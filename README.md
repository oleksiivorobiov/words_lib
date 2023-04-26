# Description
The goal is to create a small "library" for working with words. Here are the main requirements:
- Comments should only be present where necessary.
- The efficiency of algorithms is up to you.
- The package must include everything needed to compile your code (e.g., Visual Studio project, make, cmake).
- Implementation must be thread-safe.
- Object-oriented programming should be used.
- Code duplication should be avoided.
- Multithreaded tests are optional.
- You can use the std library, except when a task is already performed by an existing function.

Task:
Words
Input string: "this is a test string waaay to simple"
Delimiter: customizable, default is 1 space.
1. Count of words
    DO NOT DO - string.split(" ").size();
    1.1 - Output: number of words – int
    1.2 Optional: output - array of structures with word/number of occurrences
2. Find the longest word
3. Find the word with the longest repeatable sequence
4. Reverse words order
5. Optional but important - unit tests
     For example, something like
    #define CHECK_EQUAL(a, b)
6. Ascending and descending sorting
7. Reverse letters
    “siht si a tset gnirts yaaaw ot elpemis”
8. Multithread support with tests.
    For example, something like
```
class SomeApi {
  some_type get_words();
};

int main() {
  get_words();
}

int main() {
  createThread();
  createThread();
}

int main() {
  addTask(task);
}
```
# Implementation
Words parsing part is needed for every task so it makes sense to implement it in *WordsParser* class, every task is a separate class implementing the common *ITask* interface. We can parse words from string, then start every task in a separate thread. Every thread access parsed words but it's thread-safe because It's read-only. We can move tasks in vector and call methods polymorphically through the *ITask* interface(see should_execute_tasks_polymorphically).
## Compilation
googletest lib submodule is required:
```
git submodule update --init
```
build words_lib.sln with visual studio
