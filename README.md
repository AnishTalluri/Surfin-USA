# Surfin-USA

Purpose:
Designed to crack the Traveling Salesman Problem, this program employs graph theory, depth-first search, and a stack for efficient route optimization. Tailored for budget-conscious users navigating city routes, it guarantees an optimal journey starting and concluding in Santa Cruz, with each city visited precisely once. Whether you're exploring coastal landscapes or grappling with similar logistical challenges, this tool stands ready to provide a practical and effective solution, ensuring a seamless and cost-conscious experience.


How to use program:
To utilize the Traveling Salesman Program (TSP), you first need to compile the source code using the provided Makefile. Ensure all source code files (tsp.c, graph.c, stack.c, path.c) and header files (graph.h, stack.h, path.h, vertices.h) are in your working directory. Create a Makefile with the specified compiler and flags. Execute make all to compile the program. Once compiled, run the program with ./tsp [OPTIONS] -i input_file, where [OPTIONS] include -o output_file to specify an output file, -d to treat graphs as directed, and -h for help. For example, ./tsp -i maps/basic.graph finds the shortest path in an undirected graph, ./tsp -d -i maps/directed.graph considers directed edges, and ./tsp -i maps/undirected.graph -o output.txt saves results to a file. The program outputs Alissa’s journey and total distance, displaying error messages if issues arise. Experiment with different graphs and options for optimal paths. If errors occur, check the displayed messages for guidance.
