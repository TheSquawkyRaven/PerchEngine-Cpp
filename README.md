# PerchEngine-Cpp
```
An SDL2 game engine implemented with C++
```

## Description

Perch Engine is an object-oriented game engine framework in which 2D games can be built upon. The engine uses SDL2 for rendering, input, audio and many others.

Objects, known as Branches in Perch Engine, have their own lifecycle and are extendable. Scripts can also be easily attached to any Branch to introduce behaviour, as well as to construct its own Branch and children.

## Tree/Branch System

Perch engine uses a hierarchical layout to represent "objects", in this case each "object" is a branch.

This system is inspired by Godot's node system, and represents the "objects" in game as branches to form a tree, with the root being a branch itself.

## Sample Projects
* [Flappy Birb](https://github.com/TheSquawkyRaven/FlappyBirb-PerchEngine-Cpp)

## Acknowledgements
Lazy Foo' Productions
* [Beginning Game Programming v2.0; SDL Tutorials](https://lazyfoo.net/tutorials/SDL/index.php)
