#include<bits/stdc++.h>
using namespace std;

vector<string> tags;
void addTagToList(string);

int main() {
    #ifndef INPUT_OUTPUT
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int c =0;
    while(!feof(stdin)) {
        string s;
        getline(cin, s);
        addTagToList(s);
        cout << s << endl;
    }

    for (auto i : tags)
    {
        cout << i << endl;
    }
    
}

void addTagToList(string s){
    const regex tagSyntax("\\<.*?\\>");
    smatch match;
    if (regex_search(s, match, tagSyntax)){
        for (int i = 0 ; i < match.size(); ++i){
            tags.push_back(match[i]);
        }
    }
}