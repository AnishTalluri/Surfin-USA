#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
/*
Main
	getopt()
	read input .graph file
	create a graph with the input read
	for all the cities, initialize the graph->visited to False
	for each city 
		create path
		call tsp function with start city and path
		print path. — this prints all hamiltonian paths, one at a time
		keep track of the minimum total weight
		free if the path is not the current minimum
	print the path with the minimal weight
	free the minimum path

tsp(city. path)
	mark city in graph->visited as True
	add city to path
	find the next_city to go to = find_next_city(city)
	if no more cities to visit,
		update path total_weight 
		return;
	call tsp on the next_city

find_next_city(city)
	for each of the cities (ncity)
		if city is not visited && there is an edge with weight to ncity from city  &&  weight is less than a min
			update tempweight with the edge weight // track the minimum weight
			min is the new weight
			min index is the current index
	ncity = min index
	total_weight += tempweight
	return ncity
*/

/*
    dfs()
        vertex is visited = True
        add to path path[path_index] 
        increment path_index
        if no more vertices to visit 
            update all_paths[path_index] by path, isHamiltonian
        if more vertices to visit
            call dfs()
*/

void dfs(Path *current, Path *shortest, Graph *g, uint32_t v, FILE *ofile) {
    graph_visit_vertex(g, v);
    Path *p = current;
    path_add(p, v, g);

    if (path_vertices(p) == graph_vertices(g)) {
        //printf("entering if when path verts = graph verts\n");
        //printf("graph vertices: %u\n", graph_vertices(g));
        //printf("path vertices: %u\n", path_vertices(p));
        if (graph_get_weight(g, v, START_VERTEX) != 0) {
            //printf("entering when edge from last vert to first vert exists\n");
            path_add(p, START_VERTEX, g);
            //printf("Adding to path\n");
            //path_print(p, ofile, g);
            //fprintf(ofile, "Total distance: %u\n", path_distance(p));
            if (path_distance(p) < path_distance(shortest) || path_vertices(shortest) == 0) {
                //printf("entering when p is less than shortest\n");
                path_copy(shortest, p);
                //path_remove(p, g);
                return;
            }
        }

        /*
        else {
            fprintf(ofile, "No path found! Alissa is lost!\n");
        }
        */
    }

    for (uint32_t i = 0; i < graph_vertices(g); i++) {
        if (graph_visited(g, i) == false) {
            if (graph_get_weight(g, v, i) != 0) {
                //printf("before recursive dfs: %u\n", i);
                dfs(current, shortest, g, i, ofile);
                //printf("after recursive dfs: %u\n", i);
            }
        }
    }

    graph_unvisit_vertex(g, v);
    path_remove(p, g);
}

/*
bool all_vertices_visited(bool *v, const Graph *g) {
    for (uint32_t i = 0; i < graph_vertices(g);i++) {
	if (v[i] == false) {
	   return false;
	}
    }
    return true;
} 
void dfs(uint32_t v1, bool *visited, Path **all_paths, 
        uint32_t v_index, uint32_t *p_index, FILE *ofile, Graph *g) {
    // Add the current vertex to the 
    
    Path *path=all_paths[*p_index];
	
    // add v1 as visited
    visited[v1] = true;
	fprintf(ofile, "adding vertex %d to path at index %d in all_paths\n", v1, *p_index);
    path_add(path, v1, g);
    v_index++;

    // path_print(path, ofile, g);

    // if all vertices are visited and the last verice has a path to the start (the first vertex in the path)
    if (all_vertices_visited(visited, g) == true) {
		if (graph_get_weight(g, v1, START_VERTEX) != 0) { // using START_VERTEX is a kluge
			path_add(path, START_VERTEX, g); // add the first vertex to the end of the path
		}

		fprintf(ofile, "Found %d path\n", *p_index);
        path_print(path, ofile, g);
        *p_index += 1;
		all_paths[*p_index] = path_create(graph_vertices(g));
	
		fprintf(ofile, "Indexes  output %d\n", *p_index);
   		// return - since the path is captured in all_paths
        return;
    }
    else { // current vertex is not the end
        // recurse for all edges of v1
        for (uint32_t i = 0; i < graph_vertices(g); i++) {
            if (graph_get_weight(g, v1, i) != 0) {
				fprintf(ofile, "start %d end %d Weight is not zero visited %d\n", v1, i,  visited[i]);
                if (visited[i] == false)  { // i vertex is not visited then recurse
					fprintf(ofile, "Calling dfs on vertex %d\n", i);
					
                    dfs(i, visited, all_paths, v_index, p_index, ofile, g);
                }

            }
        }
    }
    // remove current vertex from path
	fprintf(ofile, "remove v1 %d from path\n", v1);
    path_remove(path, g);
    visited[v1] = false;
	// finished one path - considering the next
	// copy the existing path to the all_paths
	*p_index += 1;
	fprintf(ofile, "copy path to new %d\n", *p_index);
	path_copy(all_paths[*p_index], all_paths[*p_index -1]);
	
	
    return;
}

void get_all_paths(uint32_t start_vertex, Path **all_paths, uint32_t *max_index, FILE *ofile, Graph *g) {
    //initialize all_paths to 0s
    uint32_t first_path = 0, path_index = 0, v_index = 0, num_vertices = graph_vertices(g); // indicates no paths
    bool visited[num_vertices];

	printf("in get_all_paths start \n");
    for (uint32_t i = 0; i < num_vertices; i++) {
        visited[i] = false;
    }
    // create the placeholder for first path
    all_paths[first_path] = path_create(num_vertices);
    
    dfs(start_vertex, visited, all_paths, v_index, &path_index, ofile, g);
	fprintf(ofile, "Path index update %d\n", path_index);
	*max_index = path_index;
    // print all the paths
	fprintf(ofile,"End of get_all_paths - Max index %lu\n", (unsigned long) *max_index);
	path_print(all_paths[*max_index], ofile, g);
 	for (uint32_t i = 0; i <= *max_index; i++) {
		path_print(all_paths[i], ofile, g);
	}   
}
*/

int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;

    int opt;
    bool directed
        = false; // Flag to see if cmdline calls for directed graphs and if so sets it to true
    uint32_t num_vertices, num_edges, start, end, weight;

    while ((opt = getopt(argc, argv, "i:o:dh")) != -1) {
        switch (opt) {
        case 'i':
            infile = fopen(optarg, "r");
            if (infile != NULL) {
                break;
            }

            else {
                fprintf(stderr, "infile is NULL\n");
                return 1;
            }
        case 'o':
            outfile = fopen(optarg, "w");
            if (outfile != NULL) {
                break;
            }

            else {
                fprintf(stderr, "outfile is NULL\n");
                return 1;
            }
        case 'd': directed = true; break;
        case 'h':
            printf("Usage: tsp [options]\n\n");
            printf("-i infile    Specify the input file path containing the cities and edges\n");
            printf("             of a graph. If not specified, the default input should be\n");
            printf("             set as stdin.\n\n");
            printf("-o outfile   Specify the output file path to print to. If not specified,\n");
            printf("             the default output should be set as stdout.\n\n");
            printf("-d           Specifies the graph to be directed.\n\n");
            printf("-h           Prints out a help message describing the purpose of the\n");
            printf("             graph and the command-line options it accepts, exiting the\n");
            printf("             program afterwards.\n");
            return 0;
        case '?':
            fprintf(stderr, "tsp:  unknown or poorly formatted option -%c\n", optopt);
            return 1;
        }
    }

    // Read the number of vertices
    fscanf(infile, "%u", &num_vertices);
    fgetc(
        infile); // For vertex names, it takes the newline in so that fgets() can take the next string instead of that newline character
    //fprintf(outfile, "input numbers of vertices %d%c", num_vertices, c);

    // Create the graph
    Graph *g = graph_create(num_vertices, directed);

    // Make sure each vertex is unvistied before going through each one
    for (uint32_t i = 0; i < num_vertices; i++) {
        graph_unvisit_vertex(g, i);
    }

    for (uint32_t i = 0; i < num_vertices; i++) {
        char name[100];
        if (fgets(name, sizeof(name), infile)) {
            // Remove the newline character
            name[strcspn(name, "\n")] = '\0';
            graph_add_vertex(g, name, i);
        } else {
            fprintf(stderr, "ERROR: Vertex name error\n");
        }
    }

    //for (uint32_t i = 0; i < graph_vertices(g); i++) {
    //fprintf(outfile, "%s\n", graph_get_vertex_name(g, i));
    //}

    fscanf(infile, "%u", &num_edges);
    fgetc(
        infile); // Accounts for the newline character that is present after the integer that represents the number of edges

    // Add edges into g
    for (uint32_t edge = 0; edge < num_edges; edge++) {
        fscanf(infile, "%u %u %u", &start, &end, &weight);
        fgetc(infile); // Accounts for the newline character that's present after each edge
        graph_add_edge(g, start, end, weight);
        //if (!directed) {
        //	graph_add_edge(g,  end, start, weight);
        //}
        //printf("\n");
    }
    //graph_print(g);

    // uint32_t max_index = 0, min_index = INT_MAX;
    // uint32_t min_weight = INT_MAX;
    // Path *min_path = NULL;

    Path *current_path = path_create(num_vertices + 1);
    Path *min_path = path_create(num_vertices + 1);
    //uint32_t min_weight = UINT32_MAX;

    start = START_VERTEX;

    dfs(current_path, min_path, g, start, outfile);

    // Print intro statement
    if (path_distance(min_path) > 0) {
        printf("Alissa starts at:\n");
        // Path prints
        path_print(min_path, outfile, g);
        fprintf(outfile, "Total Distance: %u\n", path_distance(min_path));
    }

    else {
        fprintf(outfile, "No path found! Alissa is lost!\n");
    }
    //get_all_paths(start, all_paths, &max_index, outfile, g);
    // all the possible paths are in all_paths
    // from all_paths
    //	find the paths that are Hamiltonian ; i.e all vertices are visited
    //	for the minimum total_weight in those paths
    //	print the minimum path
    //	free the paths which are not Hamiltonian and not minimum path
    // for (uint32_t i = 0; i <= max_index;i++) {
    // 	Path *path = all_paths[i];
    // 	uint32_t curr_distance = path_distance(path);

    // 	path_print(path, outfile, g);

    // 	// check min path only for Hamiltonian
    // 	if (path_vertices(path) == (graph_vertices(g) + 1)) { // account for the loop back to start vertex
    // 		// print Hamiltonian path
    // 		path_print(path, outfile, g);
    // 		if (curr_distance < min_weight) {
    // 			min_weight = curr_distance;
    // 			min_index = i;
    // 		}
    // 	}
    // }
    // if (min_index != INT_MAX) {
    // 	min_path = all_paths[min_index];
    // 	printf("Minimum path for minimum  weight of %d\n", min_weight);
    // 	path_print(min_path, outfile, g);
    // } else {
    // 	printf("No path found! Alissa is lost!\n");
    // }

    // free all resources path, graph, etc.
    path_free(&current_path);
    path_free(&min_path);
    graph_free(&g);
    return 0;
}
