#include<bits/stdc++.h>
using namespace std;

vector<string> tags;
int addTagToList(string);
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
        if(addTagToList(s) == 1) {
            cout << s << endl;
            cout << "^Error: Invalid HTML tag syntax caught above";
            exit(0);
        }
        cout << s << endl;
    }

    printTagList();
}

bool isValidHTMLTag(string str) {
    // Function is not checking all cases
    // Regex to check valid HTML tag.
    const regex pattern("<(\"[^\"]*\"|'[^']*'|[^'\">])*>");
 
    // If the HTML tag
    // is empty return false
    if (str.empty()) {
        return false;
    }
    
    // Return true if the HTML tag
    // matched the ReGex
    if(regex_match(str, pattern)) {
        return true;
    }
    else {
        return false;
    }
}

int addTagToList(string s){
    const regex tagSyntax("\\<.*?\\>");

    int tagCount = 0;
    sregex_iterator iter(s.begin(), s.end(), tagSyntax);
    sregex_iterator end;

    while(iter != end) {
        for(unsigned i = 0; i < iter->size(); ++i) {
            if(isValidHTMLTag((*iter)[i])) {
                tags.push_back((*iter)[i]);
                tagCount++;
            }
            else{
                return 1;
            }
        }
        ++iter;
    }
    return 0;
}

void printTagList(){
    cout << "\n------------------------------------------\n";
    cout << "List of HTML Tags\n";
    cout << "------------------------------------------\n";
    for(auto i : tags){
        cout << i << endl;
    }
}