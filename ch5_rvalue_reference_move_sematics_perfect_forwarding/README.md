# Chapter 5 Rvalue References, Move Semantics, and Perfect Forwarding

## Item 23

* Hardness: 3/5

* Usefulness: 5/5

The parameter of std::move is a universal reference, it just cast the parameter to rvalue

The parameter of std::forward is a reference. Do nothing for lvalue, cast to rvalue reference for rvalue. (Reference collapsing)

Good to read the implementations.

## Item 24

* Hardness: 3/5

* Usefulness: 5/5

## Item 25

* Hardness: 4/5

* Usefulness: 5/5

## Item 26

* Hardness: 3/5

* Usefulness: 4/5

Don't use perfect-forwarding in ctors

## Item 27

* Hardness: 4/5

* Usefulness: 4/5

## Item 28

* Hardness: 3/5

* Usefulness: 5/5

## Item 29

* Hardness: 2/5

* Usefulness: 3/5

## Item 30

* Hardness: 3/5

* Usefulness: 4/5
