#include "graph.hpp"

MGraph::MGraph()
{
	graph_matrix = std::vector<std::vector<unsigned>> (Graph::size, 
							   std::vector<unsigned>  (Graph::size, 0));
}

int MGraph::get(unsigned vertex1, unsigned vertex2) const
{
	if (std::max(vertex1, vertex2) >= Graph::size) return 0;
		
	return graph_matrix[vertex1][vertex2];
}

void MGraph::set(unsigned vertex1, unsigned vertex2, int weight)
{
	auto max = std::max(vertex1, vertex2);
	if (max >= Graph::size)
	{
		auto temp = std::vector<std::vector<unsigned>> (2*max, 
								std::vector<unsigned>  (2*max, 0));
								
		for (unsigned i = 0; i < graph_matrix.size(); ++i) 
		{
			for (unsigned j = 0; j < graph_matrix.size(); ++j)
			{
				temp[i][j] = graph_matrix[i][j];
			}
		}
		
		graph_matrix = temp;
		Graph::size = graph_matrix.size();
	}
	
	graph_matrix[vertex1][vertex2] = weight;
}

void MGraph::unset(unsigned vertex1, unsigned vertex2)
{
	auto max = std::max(vertex1, vertex2);
	if (max >= Graph::size)
	{
		auto temp = std::vector<std::vector<unsigned>> (2*max, 
								std::vector<unsigned>  (2*max, 0));
								
		for (unsigned i = 0; i < graph_matrix.size(); ++i) 
		{
			for (unsigned j = 0; j < graph_matrix.size(); ++j)
			{
				temp[i][j] = graph_matrix[i][j];
			}
		}
		
		graph_matrix = temp;
		Graph::size = graph_matrix.size();
	}
	
	graph_matrix[vertex1][vertex2] = 0;
}

int LGraph::get  (unsigned vertex1, unsigned vertex2) const
{
	if (graph_list.find(vertex1) == graph_list.end()) return false;
	
	const auto &l  = graph_list.at(vertex1);
	const auto pos = std::find_if(l.begin(), l.end(), 
						[&](const List_Node &l) 
						{  
							return l.vertex == vertex2;
						});
	
	
	if (pos == l.end()) return false;
	
	return (*pos).weight;
}

void LGraph::set(unsigned vertex1, unsigned vertex2, int weight)
{
	if (graph_list.find(vertex1) == graph_list.end())
	{
		graph_list[vertex1] = std::list<List_Node>();
	}
	
	auto &l = graph_list[vertex1];
	if (std::find_if(l.begin(), l.end(), 
		[&](const List_Node &l) 
		{  
			return l.vertex == vertex2;
		}
	) != l.end()) return;
		
	l.push_back({ vertex2, weight });
}

void LGraph::unset(unsigned vertex1, unsigned vertex2)
{
	if (graph_list.find(vertex1) == graph_list.end()) return;
	
	auto &l  = graph_list[vertex1];
	auto pos = std::find_if(l.begin(), l.end(),
	[&](const List_Node &l)
	{
		return l.vertex == vertex2;
	});
	
	if (pos == l.end()) return;
	
	l.erase(pos);
}

std::vector<unsigned> DGraph::neighbours(unsigned vertex) const
{
	std::vector<unsigned> temp;
	temp.reserve(Graph::size);
	
	for (unsigned i = 0; i < Graph::size; ++i) 
	{
		if (get(vertex, i))
		{
			temp.push_back(i);
		}
	}

	return temp;
}

std::vector<unsigned> NDGraph::neighbours(unsigned vertex) const
{
	std::vector<unsigned> temp;
	temp.reserve(size);
	
	for (unsigned i = 0; i < Graph::size; ++i) 
	{
		if (get(vertex, i) || get(i, vertex))
		{
			temp.push_back(i);
		}
	}
	
	return temp;
}

MDGraph::MDGraph():
	Graph(20)
{  }

int MDGraph::get(unsigned vertex_from, unsigned vertex_to) const 
{ 
	return MGraph::get(vertex_from, vertex_to);
}

void MDGraph::set(unsigned vertex_from, unsigned vertex_to, int weight)
{
	MGraph::set(vertex_from, vertex_to, weight);
}

void MDGraph::unset(unsigned vertex_from, unsigned vertex_to)
{
	MGraph::unset(vertex_from, vertex_to);
}

std::vector<unsigned> MDGraph::neighbours(unsigned vertex) const
{
	return DGraph::neighbours(vertex);
}

MNDGraph::MNDGraph():
	Graph(20)
{  }

int MNDGraph::get(unsigned vertex1, unsigned vertex2) const
{
	return MGraph::get(vertex1, vertex2); //should be same as v2, v1
}

void MNDGraph::set(unsigned vertex1, unsigned vertex2, int weight)
{
	MGraph::set(vertex1, vertex2, weight);
	MGraph::set(vertex2, vertex1, weight);
}

void MNDGraph::unset(unsigned vertex1, unsigned vertex2)
{
	MGraph::unset(vertex1, vertex2);
	MGraph::unset(vertex2, vertex1);
}

std::vector<unsigned> MNDGraph::neighbours(unsigned vertex) const
{
	return NDGraph::neighbours(vertex);
}

LDGraph::LDGraph():
	Graph(20)
{  }

int LDGraph::get(unsigned vertex_from, unsigned vertex_to) const
{
	return LGraph::get(vertex_from, vertex_to);

}
void LDGraph::set(unsigned vertex_from, unsigned vertex_to, int weight)
{
	LGraph::set(vertex_from, vertex_to, weight);
}

void LDGraph::unset(unsigned vertex_from, unsigned vertex_to)
{
	LGraph::unset(vertex_from, vertex_to);
}

std::vector<unsigned> LDGraph::neighbours(unsigned vertex) const
{
	return DGraph::neighbours(vertex);
}

LNDGraph::LNDGraph():
	Graph(20)
{  }

int LNDGraph::get(unsigned vertex1, unsigned vertex2) const
{
	return LGraph::get(vertex1, vertex2);
}

void LNDGraph::set(unsigned vertex1, unsigned vertex2, int weight)
{
	LGraph::unset(vertex1, vertex2);
	LGraph::unset(vertex2, vertex1);
	
	LGraph::set(vertex1, vertex2, weight);
	LGraph::set(vertex2, vertex1, weight);
}

void LNDGraph::unset(unsigned vertex1, unsigned vertex2)
{
	LGraph::unset(vertex1, vertex2);
	LGraph::unset(vertex2, vertex1);
}

std::vector<unsigned> LNDGraph::neighbours(unsigned vertex) const
{
	return NDGraph::neighbours(vertex);
}