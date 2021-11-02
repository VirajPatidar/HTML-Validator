#include<bits/stdc++.h>
using namespace std;

vector<string> tags;
void addTagToList(string);
void printTagList();

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

    printTagList();
}

void addTagToList(string s){
    const regex tagSyntax("\\<.*?\\>");

    sregex_iterator iter(s.begin(), s.end(), tagSyntax);
    sregex_iterator end;

    while(iter != end) {
        for(unsigned i = 0; i < iter->size(); ++i) {
            tags.push_back((*iter)[i]);
        }
        ++iter;
    }
}

void printTagList(){
    cout << "\n------------------------------------------\n";
    cout << "List of HTML Tags\n";
    cout << "------------------------------------------\n";
    for(auto i : tags){
        cout << i << endl;
    }
}