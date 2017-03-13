/*
* Mohamed Samatar - 101848
* Assignment 6 - Heap Sort
* Description - Uses a heap to sort an array of key-value pairs
*/
#include "heap.h"

int main(){
	cout << "/*\n * Mohamed Samatar - 101848\n * Assignment 6 - Heap Sort\n"
		<< " * Description - Uses a heap to sort an array of key-value pairs\n */\n\n";
	node nodes[10]{
		node(33, "Rams"),
		node(22, "Vikings"),
		node(88, "Lions"),
		node(44, "Dolphins"),
		node(123, "Patriots"),
		node(44, "Bengals"),
		node(69, "Packers"),
		node(24, "Broncos"),
		node(13, "Bears"),
		node(49, "Chargers")
	};
	heap<node> nodeHeap(nodes, 10);
	cout << nodeHeap << endl << endl;
	//heap<node>::heapSort(nodes, 10);
	for(int i = 0; i < 10; ++i){
		nodes[i] = nodeHeap.top();
		nodeHeap.remove();
		cout << nodeHeap << endl << endl;
	}
	cout << "Sorted Heap:\n";
	for(int i = 0; i < 10; ++i)
		cout << nodes[i] << endl;
}
