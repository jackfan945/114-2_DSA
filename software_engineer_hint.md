# DSA Software Engineering Project Notes

## Assignment Summary

- Build a **visualized data structure or algorithm** project.
- The goal is not just correctness; the project should make the DSA easier to understand through movement, color changes, or other visual feedback.
- Backend should implement correct logic for legal operations.
- Frontend should present the state clearly and connect user input to the backend.
- QA should test correctness and reliability.
- Personal documentation matters for grading.

## Good Starter Choices

### 1. Binary Search Tree

Why it is a good choice:
- Clear visual structure
- Standard operations
- Easy to demonstrate inserts, searches, deletes, and traversals
- Strong balance between difficulty and presentation quality

Suggested core operations:
- `insert(x)`
- `search(x)`
- `delete(x)`
- `inorder()`
- `preorder()`
- `postorder()`

Suggested internal structure:

```text
Node {
  value
  left
  right
  x
  y
  color
}

root
```

### 2. Min Heap / Priority Queue

Why it is a good choice:
- Probably the safest option if the goal is to finish reliably
- Very clean backend representation
- Easy to animate swaps and heapify
- Can display both the array and tree view

Suggested core operations:
- `push(x)`
- `pop()`
- `top()`
- `heapify()`

Suggested internal structure:

```text
heap[]
```

Use array indices for the real structure and map each index to a tree position for drawing.

### 3. Trie

Why it is a good choice:
- Great for interactive input
- Good visualization for word insertion and prefix matching
- Easy to explain in a demo

Suggested core operations:
- `insert(word)`
- `search(word)`
- `startsWith(prefix)`
- optional: `delete(word)`

Suggested internal structure:

```text
Node {
  children: map<char, Node>
  isEnd: boolean
}
```

### 4. Union-Find

Why it is interesting:
- Simpler backend than it first appears
- Path compression and union by size/rank are nice animation opportunities
- Can visualize connected groups with colors

Suggested core operations:
- `find(x)`
- `union(a, b)`
- `connected(a, b)`

Suggested internal structure:

```text
parent[]
size[] or rank[]
```

### 5. Graph + BFS / Dijkstra

Why it is impressive:
- Strongest visual impact
- User can click nodes and edges
- Traversal or shortest-path animations look good in a booth demo

Suggested internal structure:

```text
nodes[]
edges[]
adjacencyList[]
visited[]
dist[]
parent[]
```

This is more visually impressive, but also more work than BST or Heap.

## Recommended Ranking

If the priority is finishing cleanly:

1. Min Heap
2. Binary Search Tree
3. Trie
4. Union-Find
5. Graph + Dijkstra

If the priority is strongest demo value:

1. Graph + Dijkstra
2. Binary Search Tree
3. Trie
4. Union-Find
5. Min Heap

## Best Recommendation

If unsure, start with **Binary Search Tree**.

Why:
- Not too hard
- Visually natural
- Enough operations to show meaningful behavior
- Easier to split work between frontend and backend

If the team wants the safest path, choose **Min Heap** instead.

## Important Design Advice

Separate:

- the **real data structure state**
- the **animation step sequence**

Example animation step types:

```text
highlight(node)
compare(a, b)
move(node, x, y)
swap(a, b)
visit(node)
markDone(node)
```

This separation makes the frontend much easier to build and debug.

## Suggested MVP

If building a BST MVP:

Phase 1:
- Draw the tree
- Insert nodes
- Search nodes
- Highlight visited nodes during search

Phase 2:
- Add delete
- Add traversal animations
- Add speed control / step-by-step playback

Phase 3:
- Improve visuals
- Add explanations beside each step
- Add preset examples for demo use

If building a Heap MVP:

Phase 1:
- Show array
- Show tree layout
- Support insert and pop
- Animate swaps

Phase 2:
- Add heapify animation
- Add step-by-step controls
- Add random test input generation

## Avoid As First Choice

Avoid these unless the team is very confident:

- Red-Black Tree
- B-Tree
- Skip List
- Fibonacci Heap
- Advanced string matching structures with heavy edge cases

They are possible, but the bug risk is much higher.

## Deliverable Reminder

Keep evidence of your own contribution:
- screenshots
- code snippets
- bugs found or fixed
- UI work
- test work
- planning decisions

That will help a lot when writing personal documentation later.
