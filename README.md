\# Data Structures and Algorithms (NTU)



Coursework, core algorithm implementations, and projects from the Data Structures and Algorithms course at National Taiwan University.



The repository centers on low-level data structure implementations in C and an interactive visualization tool built with the Godot Engine.



\---



\## Featured Projects



\### 1. Max Heap Visualizer (Godot 4)

An interactive visualization tool built to demonstrate step-by-step state transitions and invariant maintenance in a priority queue.



\* \*\*Role:\*\* Backend Engineer

\* \*\*Core Responsibilities \& Implementation:\*\*

&#x20; \* Developed the core backend logic in GDScript, supporting both \*\*array-based\*\* (using zero-indexed arithmetic `2i + 1`, `2i + 2` for parent/child traversal) and \*\*tree-based\*\* representations.

&#x20; \* Implemented key heap operations: dynamic array resizing, `insert`, `extract\_max`, iterative/recursive `sift\_up`, and `sift\_down`.

&#x20; \* Designed a signal-driven interface (`item\_inserted(value: int, index: int)`, swap events, index updates) to decouple internal data structure state from frontend UI animation logic.



\### 2. Graph Algorithms \& Core Structures (C)

Direct implementations of fundamental graph algorithms and linear containers written in standard C without third-party libraries.



\* \*\*Key Implementations:\*\*

&#x20; \* Depth-First Search (DFS), cycle detection in directed/undirected graphs, and topological sorting on DAGs.

&#x20; \* Explicit memory management using `malloc` and `free` to construct dynamic adjacency lists.

&#x20; \* Pointer-based stacks and linked nodes optimized for low overhead.



\---



\## Topics Covered



\* \*\*Linear Data Structures:\*\* Array-based lists, singly/doubly linked lists, stacks, and circular queues.

\* \*\*Trees \& Priority Queues:\*\* Binary search trees, tree traversals (pre/in/post-order), array-based heaps, and sift operations.

\* \*\*Graph Theory:\*\* Adjacency matrix vs. adjacency list representations, DFS/BFS traversals, connected components, and pathfinding.

\* \*\*Algorithmic Analysis:\*\* Time and space complexity using Big-O notation, recursion tree methods, and loop invariants.

