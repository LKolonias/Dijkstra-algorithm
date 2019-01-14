class algorithms{
public:
	void Dijkstra_SP();
	void A_star();
	algorithms(map<Traits::edges_size_type, int> e_weights, Graph G
	, Traits::vertex_descriptor sc, Traits::vertex_descriptor tc) :weights(e_weights), GR(G), s(sc),t(tc) {};
	int visited_vertices_dijkstra;
	int visited_vertices_Astar;
	double time_Astar;
	double time_dijkstra;

private:	
	map<Traits::edges_size_type, int> weights;
	Graph GR;
	Traits::vertex_descriptor s;
	Traits::vertex_descriptor t;
	int euclidean(Traits::vertices_size_type k, Traits::vertices_size_type l);
};

Traits::vertices_size_type find_m(map<Traits::vertices_size_type, int> D, map<Traits::vertices_size_type, bool> vv) {
	
	Traits::vertices_size_type pos;
	int min;
	bool fst = true;

	for (map<Traits::vertices_size_type, int>::iterator it = D.begin();  it != D.end(); ++it) {
		if (!vv[it->first]) {
			if (fst) { min = it->second; pos = it->first; fst = false; }
			if (it->second < min) { min = it->second; pos = it->first; }
		}
	}
	return pos;
}

int algorithms::euclidean(Traits::vertices_size_type k, Traits::vertices_size_type l) {
	double euc;
	Traits::vertex_descriptor x = vertex(k, GR);
	Traits::vertex_descriptor y = vertex(l, GR);

	euc = sqrt(pow(x.elems[0]-y.elems[0],2)+ pow(x.elems[1] - y.elems[1], 2));
	return (int)euc;
}

void algorithms::Dijkstra_SP() {


	map<Traits::vertices_size_type, int> dist;
	map<Traits::edges_size_type, bool> visited_edges;
	map<Traits::vertices_size_type, int>::iterator it = dist.begin();
	map<Traits::edges_size_type, bool>::iterator edge_it = visited_edges.begin();
	map<Traits::vertices_size_type, bool> visited_vert;
	map<Traits::vertices_size_type, bool>::iterator vert_it = visited_vert.begin();


	for (Traits::edges_size_type e_index = 0;
		e_index < num_edges(GR); ++e_index) {
		visited_edges.insert(edge_it, pair<Traits::edges_size_type, bool>(e_index, false));
	}


	for (Traits::vertices_size_type v_index = 0;
		v_index < num_vertices(GR); ++v_index) {
		dist.insert(it, pair<Traits::vertices_size_type, int>(v_index, numeric_limits<int>::max()) );	
		visited_vert.insert(vert_it, pair<Traits::vertices_size_type, bool>(v_index, false));
	}

	clock_t begin = clock();

	visited_vertices_dijkstra = 0;
	dist[get(boost::vertex_index, GR, s)] = 0;
	
	while (!dist.empty()) {

		visited_vertices_dijkstra++;

		Traits::vertices_size_type p = find_m(dist, visited_vert);
		Traits::vertex_descriptor u = vertex(p, GR);

		Traits::out_edge_iterator ei, ei_end;
		for (boost::tie(ei, ei_end) = out_edges(u, GR); ei != ei_end; ++ei) {
		
			if (!visited_edges[get(boost::edge_index, GR, *ei)]) {
				Traits::vertex_descriptor v = target(*ei, GR);
				int alt = dist[get(boost::vertex_index, GR, u)] + weights[get(boost::edge_index, GR, *ei)];		
				if (alt < dist[get(boost::vertex_index, GR, v)]) {  dist[get(boost::vertex_index, GR, v)] = alt; }
				visited_edges[get(boost::edge_index, GR, *ei)] = true;
			}
		}
		visited_vert[p] = true;
		it = dist.find(p);
		if (it->first == get(boost::vertex_index, GR, t)) { break; }
	}
	clock_t end = clock();
	time_dijkstra= double(end - begin) / CLOCKS_PER_SEC;
}



void algorithms::A_star() {
	
	map<Traits::vertices_size_type, int> dist;
	map<Traits::edges_size_type, bool> visited_edges;
	map<Traits::vertices_size_type, int>::iterator it = dist.begin();
	map<Traits::edges_size_type, bool>::iterator edge_it = visited_edges.begin();
	map<Traits::vertices_size_type, bool> visited_vert;
	map<Traits::vertices_size_type, bool>::iterator vert_it = visited_vert.begin();


	for (Traits::edges_size_type e_index = 0;
		e_index < num_edges(GR); ++e_index) {
		visited_edges.insert(edge_it, pair<Traits::edges_size_type, bool>(e_index, false));
	}


	for (Traits::vertices_size_type v_index = 0;
		v_index < num_vertices(GR); ++v_index) {
		dist.insert(it, pair<Traits::vertices_size_type, int>(v_index, numeric_limits<int>::max()));
		visited_vert.insert(vert_it, pair<Traits::vertices_size_type, bool>(v_index, false));
	}


	clock_t begin = clock();

	visited_vertices_Astar = 0;
	dist[get(boost::vertex_index, GR, s)] = 0 + euclidean(get(boost::vertex_index, GR, s), get(boost::vertex_index, GR, t));

	while (!dist.empty()) {

		visited_vertices_Astar++;

		Traits::vertices_size_type p = find_m(dist, visited_vert);
		Traits::vertex_descriptor u = vertex(p, GR);

		Traits::out_edge_iterator ei, ei_end;
		for (boost::tie(ei, ei_end) = out_edges(u, GR); ei != ei_end; ++ei) {

			if (!visited_edges[get(boost::edge_index, GR, *ei)]) {
				Traits::vertex_descriptor v = target(*ei, GR);
				int alt = dist[get(boost::vertex_index, GR, u)] + weights[get(boost::edge_index, GR, *ei)] + euclidean(get(boost::vertex_index, GR, v), get(boost::vertex_index, GR, t));
				if (alt < dist[get(boost::vertex_index, GR, v)]) { dist[get(boost::vertex_index, GR, v)] = alt; }
				visited_edges[get(boost::edge_index, GR, *ei)] = true;
			}
		}
		visited_vert[p] = true;
		it = dist.find(p);
		if (it->first == get(boost::vertex_index, GR, t)) { break; }
		
	}
	clock_t end = clock();
	time_Astar = double(end - begin) / CLOCKS_PER_SEC;
}
