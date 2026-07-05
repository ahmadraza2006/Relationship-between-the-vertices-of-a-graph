# Relationship-between-the-vertices-of-a-graph
The project is a functional program to determine the type of relationship between the vertices of the graph. Whether the connected vertices form a Path, Trail, Cycle and more.

## Description 
A C++ command-line application that reads a graph of cities from a file and evaluates user-inputted travel routes. It automatically classifies sequences of vertices into fundamental graph theory concepts, including Walks, Trails, Paths, Circuits, and Simple Circuits.

## Features
* **Dynamic Text Parsing:** Automatically breaks apart sequential inputs formatted as `CITY_A->CITY_B->CITY_C`.
* **Adjacency Matrix Engine:** Validates connectivity layouts using an $N \times N$ binary grid framework.
* **Mathematical Property Verification:** Classifies inputs dynamically as Walks, Trails, Paths, Circuits, or Simple Circuits.
* **Auto-grading Subsystem:** Runs a hardcoded diagnostic sequence at initialization to verify structural module compliance.

## Classification Rules
**Walk:** A sequence of vertices where every consecutive pair is connected by a valid edge.
**Trail:** A walk where no edge is repeated.
**Path:** A trail where no vertex is repeated.
**Cloed Walk:** A walk that starts and ends at the same vertex.
**Circuit:** A closed walk with no repeated edges.
**Closed Circuit:** A circuit where no internal vertices are repeated except the start/end vertex.
