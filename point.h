#pragma once

#include<iostream>
#include<vector>
#include <fstream>
#include<string>
#include<float.h>
#include<algorithm>
#include<numeric>  //std::iota

#define XMIN 0
#define XMAX DBL_MAX
#define YMIN 0
#define YMAX DBL_MAX



using namespace std;

class Point
{
public:
	uint16_t x;  // x-coordinate
	uint16_t y;  // y-coordinate
	uint16_t player_index;

public:

	Point() : x(0), y(0), player_index(0) { }

	Point(uint16_t i) : x(i), y(i), player_index(0) { }

	Point(uint16_t a, uint16_t b): x(a), y(b), player_index(0) {}

	Point(uint16_t a, uint16_t b, uint16_t c) : x(a), y(b), player_index(c) {}

	~Point() {  }

	void put_value(uint16_t x_, uint16_t y_) 
	{
		x = x_; 
		y = y_;
	}

	uint16_t get_value(int d) 
	{
		switch (d){
		  case 1: return x; break;
		  case 2: return y; break;
		  default: return -1;
		}
	}

	void  display()
	{
		cout<<"("<<x<<","<<y<<")";
	}

	friend ostream& operator << (ostream& output, Point& P)
	{
		output << "(" << P.x << "," << P.y << ")";
		return output;
	}

	bool operator==(const Point& P ) const
	{
		return this->y==P.y;
	}

	bool operator<(const Point& P) const
	{
		return this->y < P.y;
	}


	static void rangequery(vector<Point>& data, Point from, Point to, vector<Point>& result )
	{
		result.clear();
		size_t i, n=data.size();
		for(i=0;i<n;i++)
		{
			if(data[i].x>=from.x && data[i].x<=to.x && data[i].y>=from.y && data[i].y<=to.y)
				result.push_back(data[i]);
		}
	}
};


static void display(Point& p)
{
	p.display();
}

static void displayint(size_t p)
{

	cout<<p<<",";
}




static bool xless(const Point& l, const Point& r) 
{
	return l.x < r.x;
}

static bool yless(const Point& l, const Point& r) 
{
	return l.y < r.y;
}

static bool xequal(const Point& l, const Point& r) 
{
	return l.x == r.x;
}

static bool yequal(const Point& l, const Point& r) 
{
	return l.y == r.y;
}

typedef bool (*CompFun)(const Point&, const Point&);


static bool issorted(const vector<Point>& V, CompFun comp)
{
	int i;
//	cout<<int(V.size()-1)<<endl;
	for(i=0; i< int(V.size()-1) ;i++)
	{
		if( comp(V[i+1],V[i]) )  return false;
	}
	return true;
}

static vector<Point> readfile(const string& filename)
{
	vector<Point> origin;
	ifstream indata; 

	indata.open(filename.data()); // opens the file
		if(!indata) 
		{ // file couldn't be opened
			cerr << "Error: file " << filename << " could not be opened" << endl;
			exit(1);
		}
		cout<<"file "<<filename<<" is opened."<<endl; 


	uint16_t xin,yin;
	Point t;
	while ( indata >>xin>>yin ){
		t.put_value(xin, yin);
        origin.push_back(t);
    };
    indata.close();
	return origin;
}

template <typename T>
vector<size_t> sort_index(const vector<T> &v, bool (*comp)(const T&,const T&)) {

	// initialize original index locations
	vector<size_t> idx(v.size());
	iota(idx.begin(), idx.end(), 0);
//    for(int i=0;i<v.size();i++)  idx[i]=i;


	// sort indexes based on comparing values in v
	sort(idx.begin(), idx.end(),[&v,&comp](size_t i1, size_t i2) {return (*comp)(v[i1] , v[i2]); });

	return idx;
}

template <typename T>
vector<size_t> sort_index(const vector<T> &v,  vector<size_t>& idx) {
	// sort indexes based on comparing values in v
	sort(idx.begin(), idx.end(),
		[&v](size_t i1, size_t i2) {return v[i1] < v[i2]; });

	return idx;
}

template <typename T>
vector<size_t> sort_index(const vector<T> &v, vector<size_t>& idx, bool(*comp)(const T&, const T&)) {
	// sort indexes based on comparing values in v
	sort(idx.begin(), idx.end(), [&v,&comp](size_t i1, size_t i2) {return (*comp)(v[i1], v[i2]); });

	return idx;
}

