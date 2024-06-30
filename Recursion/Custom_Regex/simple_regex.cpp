// =========
// Exercise:
// =========
// 	Given a regex containing '.','(',')', and '*' return for each string given "YES" if it follows the given regex and "NO" otherwise
//	Rules:
//		* Each given string only contains lowercase latin letters
//		* '.' matches with any lowercase letter
//		* There are no nested parenthesis
//		* Each parenthesis is followed by '*'
//		* There are no '*' inside any parenthesis
//
// =========
// Solution:
// =========
//	Use two pointers, one for the current position in the string and one for the candidate character to match in regex.
//	At each position follow the rules if the regex at regex_index is either '.' or a character
//	If there is a missmatch then return false otherwise increase both regex_idx and str_idx
//	For the special case of '(' split the universe in two (one for deciding to go into the parenthesis and try patternmatching and one that we continue after the parenthesis (i.e. after the '*')
//	Do the same for the case of '*' by deciding whether you want to go back in the beginning of theparenthesis or continue after the asterisk.
//	Now return true if in either scenario the result was true
//	For the special case ')' just increment regex_idx
//
// =====
// Tags:   recursion, universe_splitting, decision, regex
// =====

#include <bits/stdc++.h>

using namespace std;

bool test(string regex, string str, int regex_idx, int str_idx, int open){
    
	while(str_idx<int(str.size())){
		//cout<<"TESTING "<<str<<"["<<str_idx<<"] AGAIST "<<regex<<"["<<regex_idx<<"]\n";
		if(regex_idx>=regex.size())
			return false;
		if(regex[regex_idx]=='.'){
			regex_idx ++;
		    	str_idx ++;
		}
		else if(regex[regex_idx]=='('){
			open = regex_idx;
			int i = regex_idx;
			while(regex[i]!='*'){
				i++;
			}
			return test(regex,str,regex_idx+1,str_idx,open) ||
				test(regex,str,i+1,str_idx,open);
		}
		else if(regex[regex_idx]=='*'){
			return test(regex,str,open+1,str_idx,open) ||
				test(regex,str,regex_idx+1,str_idx,open);
		}
		else if(regex[regex_idx]==')'){
		    	regex_idx++;
		}
		else{
		    	if(regex[regex_idx]==str[str_idx]){
				regex_idx++;
				str_idx++;
		    	}
		    	else{
				return false;
		    	}
		}
        }
	if(regex_idx==regex.size() && str_idx==str.size()){
		return true;
	}
    	return false;
}
vector<string> isRegexMatching(string regex, vector<string> arr) {
    
	vector<string> answers;
    
	for(int q=0; q<int(arr.size()); q++){
		if(test(regex, arr[q],0,0,-1)){
			answers.push_back("YES");
		}
		else{
			answers.push_back("NO");
		}
	}
    
	return answers;
}
int main(){

	string regex;
	getline(cin, regex);

	int n;
	cin>>n;
	
	string _;
	//Remove newline char
	getline(cin, _);

	vector<string> arr(n);

	for (int i=0; i<n; i++) {
		string arr_item;
		getline(cin, arr_item);
		cout<<"OP: "<<arr_item<<endl;
		arr[i] = arr_item;
	}

	vector<string> result = isRegexMatching(regex, arr);

	for (size_t i = 0; i < result.size(); i++) {
		cout << result[i];
		if (i != result.size() - 1) {
		    cout << "\n";
		}
	}

return 0;
}
