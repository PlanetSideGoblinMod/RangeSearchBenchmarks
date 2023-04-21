#pragma once
#include<vector>
#include "point.h"

class rangetreeFC
{
	// constructor
public:
	rangetreeFC(void);
	rangetreeFC(vector<Point>& indata);
	//destructor 
public:
	~rangetreeFC(void);
	// member variable
public:
	Point key;
	vector<Point>  data;
	rangetreeFC* lchild;
	rangetreeFC* rchild;
	vector<size_t> lindex;   // data index in the left child data
	vector<size_t> rindex;   // data index in the righ child data
	// member function
public:
	size_t getsize();
	bool buildtree();
	void rangequery(Point from, Point to, vector<Point>& result);
	static rangetreeFC* find_split(Point& low, Point& high, rangetreeFC* node);
	static void fcset(vector<Point>& A1, vector<Point>& A2, vector<size_t>& index, CompFun less);   // set the index for fractional cascading
	static size_t bsearch(Point P, vector<Point>& V);
	static void inserttoresult(rangetreeFC* datanode, size_t lo, size_t hi, vector<Point>& result);
	static void inserttoresult(rangetreeFC* datanode, size_t lo, Point to, vector<Point>& result);
	bool isleaf();  //whether this node is a leaf node
};