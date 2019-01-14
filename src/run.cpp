#include <iostream>
#include <stdlib.h>
#include <boost/array.hpp>
#include <boost/graph/grid_graph.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/heap/priority_queue.hpp>
#include <map>
#include <limits>
#include <vector>
#include <algorithm> 
#include <math.h>  
#include <ctime>

using namespace std;

typedef boost::grid_graph<2> Graph;
typedef boost::graph_traits<Graph> Traits;

#include "algorithms.hpp"

int main()
{
	int n[] = { 30, 60, 80 };

	for (int i = 0; i < 3; ++i) {
		boost::array<size_t, 2> lengths = { { n[i], 100 } };
		Graph G(lengths);
		Traits::vertex_descriptor s, t;
		srand (time(NULL));
		
		s.elems[0] = rand() % n[i];
		s.elems[1] = 0;
		t.elems[0] = rand() % n[i];
		t.elems[1] = lengths[1] - 1;
		
		map<Traits::edges_size_type, int> e_weights;

		for (Traits::edges_size_type e_index = 0;
			e_index < num_edges(G); ++e_index) {
			e_weights[e_index]=(rand() % 99) + 1;
		}
		algorithms *da = new algorithms(e_weights, G, s, t);


		da->Dijkstra_SP();
		da->A_star();
		
		cout << "--------------------------" << endl;
		cout <<"Case: "<< i << endl;
		cout << "--------------------------" << endl;
		cout << "Vertices visited: " << endl;
		cout << "Dijkstra: " << da->visited_vertices_dijkstra << endl << "A*      : " << da->visited_vertices_Astar << endl;
		cout << "--------------------------" << endl;
		cout << "Time elapsed: " << endl;
		cout << "Dijkstra: " << da->time_dijkstra << endl << "A*      : " << da->time_Astar << endl;
		cout << "--------------------------" << endl << endl << endl;


		delete da;
	}

	return 0;
}


