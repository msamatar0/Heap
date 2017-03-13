#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <queue>
#include <vector>
#include <sstream>
using namespace std;

struct node{
	int key;
	string value;
	node(int k = 0, string v = ""): key(k), value(v){}
	bool operator<(node &n){
		return key < n.key;
	}
	bool operator>(node &n){
		return key > n.key;
	}
	friend ostream &operator<<(ostream &nout, node &n){
		return nout << n.key << ", " << n.value;
	}
};

//Vector heap
template<typename t> class heap{
	vector<t> vecHeap;
	//Recursively swaps a new element until it fits in heap order
	void upHeap(int i){
		if(i == 0)
			return;
		int pidx = (i - 1) / 2;
		if(vecHeap[pidx] > vecHeap[i]){
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
		if(lidx >= len)
			return;
		int min = i;
		if(vecHeap[i] > vecHeap[lidx])
			min = lidx;

		if((ridx < len) && (vecHeap[min] > vecHeap[ridx]))
			min = ridx;

		if(min != i){
			t temp = vecHeap[i];
			vecHeap[i] = vecHeap[min];
			vecHeap[min] = temp;
			downHeap(min);
		}
	}
protected:
	//For priority queue: loads all heap elements into a passed-in vector
	void getVector(vector<t> &v){
		for(int i = 0; i < size(); ++i)
			v.push_back(vecHeap[i]);
	}
public:
	heap(){}
	//size_t used to prevent negative vector size
	heap(size_t s) : vecHeap(vector<t>(s)){}
	//constructs heap from array
	heap(t *a, size_t len){
		for(int i = 0; i < len; ++i)
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
	//returns minimum element
	t top(){
		return vecHeap[0];
	}
	//heap height = log(n)
	int height(){
		return empty() ? 0 : log2(size());
	}
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
	void remove(){
		vecHeap[0] = vecHeap[size() - 1];
		vecHeap.pop_back();
		downHeap(0);
	}
	static void heapSort(t *ar, size_t len){
		heap<t> h(ar, len);
		for (int i = 0; i < h.size(); ++i){
			ar[i] = h.top();
			h.remove();
		}
	}
	friend ostream &operator<<<t>(ostream &hout, heap<t> &h);
};

template<typename t> ostream &operator<<(ostream &hout, heap<t> &h){
	hout << "Heap[\n";
	for (int i = 0; i < h.size(); ++i)
		hout << "  " << h.vecHeap[i] << endl;
	return hout << "]\n";
}