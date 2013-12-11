#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include<string>
using namespace std;

struct node {
	char name;
	int sumweight;
	bool done;
	vector<char> adjacent;
//	vector<char> outlist;
};

struct edge {
	char start;
	char end;
	int weight;
};

bool nodecheck(char thenode, int max, vector<node>& nodelist)
{
	bool invector = false;
	for(int i = 0; i <= max; i++)
	{
		if(nodelist[i].name == thenode)
			invector = true;
	}
	return invector;
}

int extractmin(vector<node>& nodelist, int max)
{
	int index;
	int value=1000000000;
	for(int i = 0; i <= max; i++)
	{
		if((nodelist[i].sumweight < value) && (nodelist[i].done == false))
		{
			index = i;
			value = nodelist[i].sumweight;
		}
	}
	return index;
}

bool done(vector<node>& nodelist, int max)
{
	bool done = true;
	for(int i = 0; i <= max; i++)
	{
		if(nodelist[i].done == false)
		{
			done = false;
			break;
		}
	}
	return done;
}

int main(int argc, char* argv[])
{
	vector<node> nodes;
	nodes.reserve(10);
	vector<edge> edges;
	edges.reserve(45);
	ifstream myfile(argv[1]);
	int numedges = 0;
	int numnodes = 0;
	char char1;
	char char2;
	int num;
	bool good = true;
	char startnode;
	int startnodeindex;
	string directed;

	ofstream outfile;
	outfile.open ("out.txt");	

	if (!myfile)
	{
		cout << "Unable to open file" << endl;
		return 0;
	}
	
	if(myfile.peek() == EOF)
		good = false;

	myfile >> directed;
//	cout << directed << endl;

	if(directed.compare("D") == 0)
	{
//		cout << "DIRECTED" << endl;
	}
	else if(directed.compare("UD") == 0)
	{
//		cout << "UN-DIRECTED" << endl;
	}

	while (!myfile.eof())
	{
		myfile >> char1 >> char2 >> num;


		if(nodecheck(char1, numnodes, nodes) == false)
		{
			nodes[numnodes].name = char1;
			nodes[numnodes].done = false;
			nodes[numnodes].sumweight = 999999999;
			nodes[numnodes].adjacent.push_back(char2);
			numnodes++;
		}
		if(nodecheck(char2, numnodes, nodes) == false)
		{
			nodes[numnodes].name = char2;
			nodes[numnodes].done = false;
			nodes[numnodes].sumweight = 999999999;
			numnodes++;
		}
		
		if(directed.compare("D") == 0)
		{
			edges[numedges].start = char1;
			edges[numedges].end = char2;
			edges[numedges].weight = num;

			numedges++;
		}

		if(directed.compare("UD") == 0)
		{
			edges[numedges].start = char1;
			edges[numedges].end = char2;
			edges[numedges].weight = num;

			numedges++;


			edges[numedges].start = char2;
			edges[numedges].end = char1;
			edges[numedges].weight = num;

			numedges++;

		}


		if(myfile.eof())
			break;
	}
	numedges--;


	cout << "Enter start-node character:" << endl;
	cin >> startnode;

	for(int i = 0; i < numnodes; i++)
	{
		if(nodes[i].name == startnode)
		{
			startnodeindex = i;
			break;
		}		
	}
	
//	cout << "index = " << startnodeindex << endl;

	nodes[startnodeindex].sumweight = 0;

	int current;	
	char currentchar;
	int adjsize;
	int secondnode;
	while(!done(nodes, numnodes))
	{
		current = extractmin(nodes, numnodes);
		nodes[current].done = true;

		//adjsize = nodes[current].adjacent.size;

		for(int i = 0; i < numedges; i++)
		{
			if(edges[i].start == nodes[current].name)
			{
			
				for(int j = 0; j < numnodes; j++)
				{
					if(nodes[j].name == edges[i].end)
					{
						secondnode = j;
						break;
					}		
				}
				

				if(nodes[current].sumweight + edges[i].weight < nodes[secondnode].sumweight)
					nodes[secondnode].sumweight = nodes[current].sumweight + edges[i].weight;
			}
		}		



	}


	outfile << "Dijkstra" << endl;
	outfile << "Source : " << startnode << endl;

	for(int i = 0; i < numnodes; i++)
	{
		outfile << "NODE " << nodes[i].name << " : " << nodes[i].sumweight << endl;
	}
	outfile << "End Dijkstra" << endl;

	outfile << endl << "Reliable Paths Algorithm is unimplemented" << endl;

	outfile.close();
//	cout << "\nTotal Number of Edges = " << numedges << endl;
//	cout << "\nTotal Number of Nodes = " << numnodes << endl;

	return 0;
}

