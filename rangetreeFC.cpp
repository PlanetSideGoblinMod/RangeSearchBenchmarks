#include<algorithm>
#include "rangetreeFC.h"
#include "pdqsort.h"

rangetreeFC::rangetreeFC(void)
{
	lchild = NULL;
	rchild = NULL;
}

rangetreeFC::rangetreeFC(vector<Point>& indata )
{
	
	lchild = NULL;
	rchild = NULL;

	if (!issorted(indata, xless))
	{
		sort(indata.begin(), indata.end(), xless);
	}
	
	size_t n = indata.size();
	data=indata;	
	key = data[!(n%2) ? (n/2-1) : (n-1)/2];
	lindex.resize(n+1,-1);
	rindex.resize(n+1,-1);  // an additional size_t to store the end, it would be the size of the subvector.
}



rangetreeFC::~rangetreeFC(void)
{

	delete lchild;

	delete rchild;
}


size_t rangetreeFC::getsize()
{
	return data.size();
}

bool rangetreeFC::buildtree()
{
	size_t n=getsize();
	if (n==0)
		return false;

	if(n==1)
	{
		lchild=NULL;
		rchild=NULL;
	}
	else
	{
		size_t pos= !(n%2) ? n/2-1 : (n-1)/2;
		vector<Point> left,right;
		left.assign(data.begin(),data.begin()+pos+1);
		right.assign(data.begin()+pos+1,data.end());

//		cout<<"\nbuilding left tree..."<<endl;
		lchild=new rangetreeFC(left);
		lchild->buildtree();

//		cout<<"\nbuilding right tree..."<<endl;
		rchild=new rangetreeFC(right);
		rchild->buildtree();

		sort(data.begin(),data.end(),yless);
		sort(left.begin(),left.end(),yless);
		sort(right.begin(),right.end(),yless);
		fcset(data,left,lindex,yless);
		fcset(data,right,rindex,yless);
	}

	return true;
}

//  A2  belong to A1
void rangetreeFC::fcset(vector<Point>& A1,vector<Point>& A2,vector<size_t>& index, CompFun less)
{
	size_t n1 =A1.size();
	size_t n2 =A2.size();
	size_t i=0,j=0;

	for(;j<n2;j++)
	{
		for(;i<n1;i++)
		{
			if( !less(A2[j],A1[i]) ) index[i]=j;
			else break;			
		}
	}
	
}

void rangetreeFC::rangequery(Point from, Point to, vector<Point>& result)
{
	result.clear();
	rangetreeFC* split = find_split(from,to, this);
	if(split==NULL) return;

	size_t lowdex ; //the interval in split
	lowdex = bsearch(from, split->data );
	if(lowdex==-1 ) return;
	if(split->isleaf()) 
	{
		inserttoresult(split, lowdex ,to, result);
		return;
	}	

	rangetreeFC*  s=split->lchild;
	size_t low;  // the lowindex and highindex in subsets
	low=split->lindex[lowdex];
	
	if(low!=-1 )
	{
	if(from.x<=XMIN) 
	{
		inserttoresult(s, low, to, result);
	}
	else
	{
		while( s!=NULL )
		{
			if( !xless(s->key,from) )
			{
				if(s->lchild==NULL && s->rchild==NULL) 
					inserttoresult(s, low, to, result);
				else
				{
					inserttoresult(s->rchild, s->rindex[low], to, result);
				}

				low=s->lindex[low];
				if (low==-1) break;
				s=s->lchild;
			}
			else
			{
				low=s->rindex[low];
				if (low==-1) break;
				s=s->rchild;
			}
		}
	}
	}

	s=split->rchild;
	low=split->rindex[lowdex];
	if(low!=-1 )
	{
	if (to.x>=XMAX) 
	{
		inserttoresult(s, low, to, result);
	}
	else
	{
		while( s!=NULL )
		{
			if( !xless(to,s->key) )
			{
				if(s->lchild==NULL && s->rchild==NULL) 
				{
					inserttoresult(s, low,to, result);
				}
				else
				{
				inserttoresult(s->lchild, s->lindex[low], to, result);
		
				}

				low=s->rindex[low];
				if (low==-1) break;
				s=s->rchild;
			}
			else
			{
				low=s->lindex[low];
				if (low==-1) break;
				s=s->lchild;
			}
		}
	}
	}
}

rangetreeFC* rangetreeFC::find_split(Point& low, Point& high, rangetreeFC* node )
{
	//  if low is greater than high, return NULL
	if (xless(high, low) || yless(high, low))
	{
		return NULL;
	}

		// query
	rangetreeFC* s=node;
	while (s!=NULL)
	{
		if( xless(s->key,low) )
		{
			s=s->rchild;
		}
		else if ( xless(high,s->key) )
		{
			s=s->lchild;
		}
		else
		{
			return s;
		}
	}
	return NULL;
}


// return the first position where the value is not less than the given point P. 
size_t rangetreeFC::bsearch(Point P, vector<Point>& V)   
{
	// binary search
	size_t n = V.size();
	size_t l=0;
	size_t h=n-1;
	size_t m=h,i;
	while(int(l)<=int(h)){
		m=(l+h)/2;
		if( V[m].y == P.y)
		{
			for (i=m;int(i)>=0;i--)    //  in case of some equal elements
			{
				if(V[i].y!=P.y) break; 
			}
			return i+1;
		}
		if( yless(P,V[m])) h=m-1;
		else l=m+1;
	}
	if(h == m-1) return m;
	else return m+1<n ? m+1 : -1;    // if the position exceeds, return -1.
}

void rangetreeFC::inserttoresult(rangetreeFC* datanode, size_t lo, Point to, vector<Point>& result)
{
	
	if(datanode==NULL) return;
	if(lo==-1) return;

	vector<Point>& V=datanode->data;
	size_t i, n=V.size();


	for(i=lo;i<n && !yless(to,V[i]);i++)
	{
		result.push_back(V[i]);
	}


}

bool rangetreeFC::isleaf()
{
	if(lchild==NULL && rchild==NULL) return true;

	return false;
}
