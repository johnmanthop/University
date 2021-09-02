#ifndef GRAPH
#define GRAPH

#include <algorithm>
#include <vector>
#include <map>
#include <list>

struct List_Node
{
	unsigned vertex;
	int weight;
};

struct Graph
{
protected:
	unsigned size;
public:
	Graph(unsigned initial):
		size(initial)
	{  }

	virtual int  get  (unsigned vertex1, unsigned vertex2) const 			= 0;
	virtual void set  (unsigned vertex1, unsigned vertex2, int weight = 1) 	= 0;
	virtual void unset(unsigned vertex1, unsigned vertex2) 		 			= 0;
	
	virtual std::vector<unsigned> neighbours(unsigned vertex) const	 = 0;
	
	unsigned get_size() const { return size; }
};

class MGraph: public virtual Graph
{
private:
	std::vector<std::vector<unsigned>> graph_matrix;
protected:
	int get   (unsigned vertex1, unsigned vertex2) const;
	void set  (unsigned vertex1, unsigned vertex2, int weight);
	void unset(unsigned vertex1, unsigned vertex2);
	
public:
	MGraph();
};

class LGraph: public virtual Graph
{
private:
	std::map<unsigned, std::list<List_Node>> graph_list;
protected:
	int get   (unsigned vertex1, unsigned vertex2) const;
	void set  (unsigned vertex1, unsigned vertex2, int weight);
	void unset(unsigned vertex1, unsigned vertex2);
};

class DGraph: public virtual Graph
{
protected:
	std::vector<unsigned> neighbours(unsigned vertex) const;
};

class NDGraph: public virtual Graph
{
protected:
	std::vector<unsigned> neighbours(unsigned vertex) const;
};

/*Final four classes are publicly available for users*/
struct MDGraph: public MGraph, public DGraph
{
	MDGraph();

	int get   (unsigned vertex_from, unsigned vertex_to) const ;
	void set  (unsigned vertex_from, unsigned vertex_to, int weight = 1);
	void unset(unsigned vertex_from, unsigned vertex_to);
	
	std::vector<unsigned> neighbours(unsigned vertex) const;
};

struct MNDGraph: public MGraph, public NDGraph
{
	MNDGraph();
	
	int get   (unsigned vertex1, unsigned vertex2) const;
	void set  (unsigned vertex1, unsigned vertex2, int weight = 1);
	void unset(unsigned vertex1, unsigned vertex2);
	
	std::vector<unsigned> neighbours(unsigned vertex) const;
};

struct LDGraph: public LGraph, public DGraph
{
	LDGraph();

	int get   (unsigned vertex_from, unsigned vertex_to) const;
	void set  (unsigned vertex_from, unsigned vertex_to, int weight = 1);
	void unset(unsigned vertex_from, unsigned vertex_to);
	
	std::vector<unsigned> neighbours(unsigned vertex) const;
};

struct LNDGraph: public LGraph, public NDGraph
{
	LNDGraph();

	int get   (unsigned vertex1, unsigned vertex2) const;
	void set  (unsigned vertex1, unsigned vertex2, int weight = 1);
	void unset(unsigned vertex1, unsigned vertex2);
	
	std::vector<unsigned> neighbours(unsigned vertex) const;
};

#endif