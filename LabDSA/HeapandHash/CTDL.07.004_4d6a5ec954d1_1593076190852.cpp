#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <queue>
#define MAX_SIZE 1000
using namespace std;

int minCost(int arr[], int n) 
{ 
		priority_queue<int, vector<int>, greater<int>> pq(arr, arr + n); 
  
    // Initialize result 
    int res = 0; 
  
    // While size of priority queue is more than 1 
    while (pq.size() > 1) { 
        // Extract shortest two ropes from pq 
        int first = pq.top(); 
        pq.pop(); 
        int second = pq.top(); 
        pq.pop(); 
  
        // Connect the ropes: update result and 
        // insert the new rope to pq 
        res += first + second; 
        pq.push(first + second); 
    } 
  
    return res;
} 

int main(int argc, char *argv[])
{
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);

	string line;
	getline(ifs, line);
	int size = stoi(line);

	int *arr = new int[size];
	for (int i = 0; i < size; i++)
	{
		getline(ifs, line);
		int element = stoi(line);
		arr[i] = element;
	}

	cout << "Total cost for connecting ropes is " << minCost(arr, size); 

	ifs.close();

	return 0;
}