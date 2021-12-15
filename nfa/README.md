# Non-Deterministic Finite Automata Simulator
Fotis Antonatos

September 2021

## Description

This program constructs and simulates a partially non-deterministic finite automaton (NFA). It does not handle epsilon transitions.

## Design Decisions and Goals
I chose C because it is a simple, powerful, and easily optimized programming language.

Two ways to simulate:
 - **Breadth first search**: From the initial state, the program would start checking for transitions to
follow, push them onto a queue, and continue this process until the end of input.
 - **Depth first search**: The program calls [`simulate`](antonatos.c#L104) at
the initial state, which compares the next character in the input string against the current state’s
outgoing transitions. [`simulate`](antonatos.c#L104) follows these transitions by recursively calling itself. The NFA only accepts if it reaches the last input character in an accept state.

The first method would require the use of dynamic memory and a data structure; I chose the recursive method out of concern for performance.

## Implementation
 - Input file is handled by [`ldfile`](antonatos.c#L70) and `ldfile_*`
 - Simulation in [`simulate`](antonatos.c#L104), can be done without dynamic memory
 - Less than 150 lines long