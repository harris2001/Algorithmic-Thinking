// ==========
// Excercise:
// ==========
// 	Given a list of items and a list of queries do the following:
// 	For each query:
// 		If the query (q) is negative (i.e. q<0):
// 			Then remove the first of occurance of the item -(q) form the list of items
// 		If the query (q) is positive (i.e. q>0):
// 			Then add item q in the list of items
// 	Return the list of items after all queries have been executed
//
//
// =========
// Solution:
// =========
//
// 	Use a lookup map that saves the position of set containing the positions where we find each item
// 	Then use a vector of booleans to mark the elements that have been deleted. 
// 		The reasong we need to do that is because we don't want to mess up the indexes after deleting and adding new items in the list
// 	Then for each query, if q is negative mark that position as deleted
// 	If q is positive then create a new entry in the items array with the element q and a non-deleted entry in the deleted vector.
// 	In the last round go over all elements in the items list and see which of them have not been deleted. Add them in a new list and return that new list
//
//
// =====
// Tags:   map, hashmap, lookup
// =====
#include<bits/stdc++.h>

using namespace std;

vector<int> solve(vector<int> items, vector<int>queries){
	map<int,set<int>> lookup;
	vector<bool>deleted(items.size(),false);
	for(int i=0; i<items.size(); i++){
		lookup[items[i]].insert(i);
	}
	for(int q:queries){
		if(q<0){
			auto it = lookup.find(q*-1);
			if(it!=lookup.end() && !it->second.empty()){
				deleted[*(it->second).begin()]=true;
				it->second.erase(it->second.begin());
			}
		}
		else{
			lookup[q].insert(items.size());
			items.push_back(q);
			deleted.push_back(false);
		}
		for(int i=0; i<items.size(); i++){
			if(!deleted[i])
				printf("%d ",items[i]);
		}
		printf("\n");
	}
	vector<int> solution;
	for(int i=0; i<deleted.size(); i++){
		if(!deleted[i])
			solution.push_back(items[i]);
	}
	return solution;
}

int main(){
	int n,q;
	scanf("%d %d",&n,&q);
	vector<int>items;
	vector<int>queries;
	for(int i=0; i<n; i++){
		int item;
		scanf("%d",&item);	
		items.push_back(item);
	}
	for(int i=0; i<q; i++){
		int query;
		scanf("%d",&query);
		queries.push_back(query);
	}
	vector<int>result = solve(items,queries);
	for(int i=0; i<result.size(); i++){
		printf("%d ",result[i]);
	}
	printf("\n");
	return 0;
}
