#include<bits/stdc++.h>
using namespace std;

vector<string> tags;
int addTagToList(string);
void printTagList();
int checkOrder();

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

    if(checkOrder() == 1){
        cout << "^Error: Invalid HTML tag syntax caught above";
        exit(0);
    }
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

int checkOrder() {
    
    if(tags[0] != "<!DOCTYPE html>") {
        cout << "^Error: '<!DOCTYPE html>' tag not included.";
        return 1;
    }
    if(tags[1].find("html") == 4294967295) {
        cout << "^Error: '<html>' tag not initialized.";
        return 1;
    }
    int flag1 = -1;
    int flag2 = 0;
    char * head_tags[2] = {"meta", "title"};
    
    for(auto i : tags){
        
        flag2 = 0;
        if(i == "<head>") {
            flag1 = 0;
            continue;
        }
        if(i == "</head>") {
            flag1 = 1;
            continue;
        }

        if(flag1 == -1 && i == "<body>") {
            cout << "^Error: <body> tag must come after </head> tag.";
            return 1;
        }

        if(flag1 == 0) {
            for(auto j : head_tags) {
                cout << i << ", " << j << ", ";
                cout << i.find(j) << endl;
                if(i.find(j) != 4294967295) {
                    flag2 = 1;
                    break;
                }
            }
            if(flag2 == 0) {
                cout << "^Error: "<< i <<" tag must not come inside <head> tag.";
                return 1;
            }
        }
    }
    return 0;
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
    cout << "------------------------------------------\n";
    cout << "------------------------------------------\n";
}