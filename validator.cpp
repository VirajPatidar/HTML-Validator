#include<bits/stdc++.h>
using namespace std;

vector<string> tags;
vector<string> singleton = {"!DOCTYPE", "link", "meta", "br", "hr", "embed", "img", "input", "source", "col"};
vector<string> elements = {"a", "abbr", "acronym", "address", "applet", "area", "article", "aside", "audio", "b", "base", "basefont", "bdi", "bdo", "big", "blockquote", 
                           "body", "br", "button", "canvas", "caption", "center", "cite", "code", "col", "colgroup", "data", "datalist", "dd", "del", "details", "dfn", 
                           "dialog", "dir", "div", "dl", "dt", "em", "embed", "fieldset", "figcaption", "figure", "font", "footer", "form", "frame", "frameset", "h1", "h2",
                           "h3", "h4", "h5", "h6", "head", "header", "hr", "html", "i", "iframe", "img", "input", "ins", "kbd", "label", "legend", "li", "link", "main", 
                           "map", "mark", "meta", "meter", "nav", "noframes", "noscript", "object", "ol", "optgroup", "option", "output", "p", "param", "picture", "pre", 
                           "progress", "q", "rp", "rt", "ruby", "s", "samp", "script", "section", "select", "small", "source", "span", "strike", "strong", "style", "sub", 
                           "summary", "sup", "svg", "table", "tbody", "td", "template", "textarea", "tfoot", "th", "thead", "time", "title", "tr", "track", "tt", "u", "ul", 
                           "var", "video", "wbr"};

int addTagToList(string);
void printTagList();
void checkOpeningClosing();

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

    checkOpeningClosing();
    //printTagList();
}


/* ===== Checking HTML tag and attribute syntax ===== */
bool isValidHTMLTag(string str) {
    if(str[1] == '/'){
        string closing = str.substr(2, (str.size()-3));
        if(find(elements.begin(), elements.end(), closing) == elements.end()) {
            return false;
        }
    }
    else{
        string opening = str.substr(1, (str.find(">")) - 1);
        if(opening == "!DOCTYPE html") {
            return true;
        }
        string opening_element = str.substr(1, (str.find_first_of(" >")) - 1);
        if(find(elements.begin(), elements.end(), opening_element) == elements.end()) {
            return false;
        }
    }

    return true;
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


/* ===== Checking Opening and Closing Tags ===== */
bool find(stack<string> stack, string i){
    while (!stack.empty() && stack.top().substr(1, (stack.top().find_first_of(" >"))-1) != i.substr(2, (i.size()-3)))
        stack.pop();
    if (!stack.empty())
        return true;
    return false;
}

void checkOpeningClosing(){
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
                cout << "\nError: No opening tag found for "+ i << endl;
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
        cout << "\nError: No closing tag found for "+ stack.top() << endl;
        exit(0); 
    }
}


/* ===== Printing Tag List ===== */
void printTagList(){
    cout << "\n------------------------------------------\n";
    cout << "List of HTML Tags\n";
    cout << "------------------------------------------\n";
    for(auto i : tags){
        cout << i << endl;
    }
}