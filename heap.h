#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <queue>
#include <vector>
#include <sstream>
#include <functional>
using namespace std;

struct node{
	int key;
	string value;
	node(int k = 0, string v = "") : key(k), value(v){}

	/*bool operator<(node &n){
		return key < n.key;
	}

	bool operator>(node &n){
		return key > n.key;
	}*/

	friend ostream &operator<<(ostream &nout, node &n){
		return nout << n.key << ", " << n.value;
	}
};

auto nodeComp = [](node n1, node n2){ return n1.key - n2.key; };

//Vector heap
template<class t> class heap{
	vector<t> vecHeap;
	typedef function<int(t, t)> comparator;
	comparator c;

	//Takes index of left child
	int left(int i){
		return 2 * i + 1;
	}

	//Takes index of right child
	int right(int i){
		return  2 * i + 2;
	}

	//Takes index of parent
	int parent(int i){
		return i == 0 ? 0 : (i - 1) / 2;
	}

	//Recursively swaps a new element until it fits in heap order
	void upHeap(int i){
		if (i == 0)
			return;
		int pidx = (i - 1) / 2;
		if (c(vecHeap[pidx], vecHeap[i])){
			t temp = vecHeap[pidx];
			vecHeap[pidx] = vecHeap[i];
			vecHeap[i] = temp;
			upHeap(pidx);
		}
	}

	void downHeap(int i){
		int len = vecHeap.size();
		int lidx = 2 * i + 1;
		int ridx = 2 * i + 2;
		if (lidx >= len)
			return;
		int min = i;
		if (c(vecHeap[i], vecHeap[lidx]))
			min = lidx;

		if ((ridx < len) && (c(vecHeap[min], vecHeap[ridx])))
			min = ridx;

		if (min != i){
			t temp = vecHeap[i];
			vecHeap[i] = vecHeap[min];
			vecHeap[min] = temp;
			downHeap(min);
		}
	}
protected:
	//For priority queue: loads all heap elements into a passed-in vector
	void getVector(vector<t> &v){
		for (int i = 0; i < size(); ++i)
			v.push_back(vecHeap[i]);
	}
public:

	heap() = delete;

	heap(comparator func): c(func){}

	//size_t used to prevent negative vector size
	heap(size_t s, comparator func): vecHeap(vector<t>(s)), c(func){}

	//constructs heap from array
	heap(t *a, size_t len, comparator func): c(func){
		for (int i = 0; i < len; ++i)
			add(a[i]);
	}

	~heap(){}

	void add(t o){
		vecHeap.push_back(o);
		upHeap(size() - 1);
	}

	//size = all elements in h
	int size(){
		return vecHeap.size();
	}

	bool empty(){
		return size() == 0;
	}
		
	//heap height = log(n)
	int height(){
		return empty() ? 0 : log2(size());
	}

	//returns minimum element
	t top(){
		return vecHeap[0];
	}

	void remove(){
		vecHeap[0] = vecHeap[size() - 1];
		vecHeap.pop_back();
		downHeap(0);
	}

	static void heapSort(t *ar, size_t len, comparator func){
		heap<t> h(ar, len, func);
		for(int i = 0; i < len; ++i){
			ar[i] = h.top();
			h.remove();
		}
	}

	friend ostream &operator<<(ostream &hout, heap<t> &h){
		hout << "Heap[\n";
		for (int i = 0; i < h.size(); ++i)
			hout << "  " << h.vecHeap[i] << endl;
		return hout << "]\n";
	}
};
