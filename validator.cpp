#include<bits/stdc++.h>
using namespace std;

vector<string> singleton = {"!DOCTYPE", "link", "meta", "br", "hr", "embed", "img", "input", "source", "col"};
vector<string> tags;
int addTagToList(string);
void printTagList();
void isClosed();

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
    isClosed();
    printTagList();
}

bool find(stack<string> stack, string i){
    while (!stack.empty() && stack.top().substr(1, (stack.top().find_first_of(" >"))-1) != i.substr(2, (i.size()-3)))
        stack.pop();
    if (!stack.empty())
        return true;
    return false;
}

void isClosed(){
    stack<string> stack;
    for(auto i : tags){
        bool isInVect=false;
        string s = i.substr(1, (i.find_first_of(" >"))-1);
        isInVect = find(singleton.begin(), singleton.end(), s) != singleton.end();
        if(isInVect == true){
            continue;
        }
        char n=i[1];
        if(n!='/'){
            stack.push(i);
        }
        else{
            if(stack.empty() && i=="</html>"){
                cout << "\nError: No opeing tag found for "+ i << endl;
                exit(0);
            }
            string newstring = stack.top().substr(1, (stack.top().find_first_of(" >"))-1);
            if(i.substr(2, (i.size()-3)) == newstring){
                stack.pop();
            }
            else{
                if(!find(stack, i)){
                   cout << "\nError: No opening tag found for "+ i << endl;
                   exit(0); 
                }
                else{
                    cout << "\nError: No closing tag found for "+ stack.top() << endl;
                    exit(0);
                }
            }
        }
        
    }
    if(!stack.empty()){
        cout << "\nError: No closing tag found for "+ stack.top()<<endl;
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