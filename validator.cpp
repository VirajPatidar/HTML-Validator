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
vector<string> body_valid_tags = {"a", "abbr", "acronym", "address", "applet", "area", "article", "aside", "audio", "b", "base", "basefont", "bdi", "bdo", "big", "blockquote", 
                           "body", "br", "button", "canvas", "caption", "center", "cite", "code", "col", "colgroup", "data", "datalist", "dd", "del", "details", "dfn", 
                           "dialog", "dir", "div", "dl", "dt", "em", "embed", "fieldset", "figcaption", "figure", "font", "footer", "form", "frame", "frameset", "h1", "h2",
                           "h3", "h4", "h5", "h6", "header", "hr", "i", "iframe", "img", "input", "ins", "kbd", "label", "legend", "li", "link", "main", 
                           "map", "mark", "meta", "meter", "nav", "noframes", "noscript", "object", "ol", "optgroup", "option", "output", "p", "param", "picture", "pre", 
                           "progress", "q", "rp", "rt", "ruby", "s", "samp", "script", "section", "select", "small", "source", "span", "strike", "strong", "style", "sub", 
                           "summary", "sup", "svg", "table", "tbody", "td", "template", "textarea", "tfoot", "th", "thead", "time", "title", "tr", "track", "tt", "u", "ul", 
                           "var", "video", "wbr",  "link", "meta", "br", "hr", "embed", "img", "input", "source", "col"};

int addTagToList(string);
void printTagList();
void checkOpeningClosing();
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

    checkOpeningClosing();
    // printTagList();
    if(checkOrder() == 1){
        cout << "^Error: Invalid HTML tag syntax caught above";
        exit(0);
    }
    cout << "\n==============================================\nCompilation Successful: No syntax errors found\n==============================================";
    //printTagList();
}


/* ===== Checking HTML tag and attribute syntax ===== */
bool checkAttribute(string str) {
    int equal=0, quote=0;
    char c;
    stack<char> symbol;
    for (int i = 0; i < str.size(); i++) {
        if(str[i] == '=' || str[i] == '"'){
            symbol.push(str[i]);
        }
    }
    while (!symbol.empty()) {
        c = symbol.top();
        if (c == '"') {
            quote++;
        }
        else if(c == '=' && quote%2 == 0){
            equal++;
        }
        symbol.pop();
    }
    return (quote == 2*equal) ;    
}

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
        size_t attr = opening.find(" ");
        if (attr != string::npos){
            return checkAttribute(opening.substr((opening.find(" ")+1), (opening.size()-1)));
        }
        if(find(elements.begin(), elements.end(), opening_element) == elements.end()) {
            return false;
        }
    }

    return true;
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
    int head_flag2 = -1;
    int head_flag1 = 0;
    int body_flag1 = 0;
    int body_flag2 = 0;
    char * head_tags[2] = {"meta", "title"};
    
    for(auto i : tags){

        body_flag2 = 0;
        head_flag2 = 0;
        if(i == "<head>") {
            head_flag1 = 1;
            continue;
        }
        if(i == "</head>") {
            head_flag1 = 0;
            continue;
        }

        if(i == "<body>") {
            body_flag1 = 1;
            continue;
        }
        if(i == "</body>") {
            body_flag1 = 0;
            continue;
        }

        if(head_flag1 == -1 && i == "<body>") {
            cout << "^Error: <body> tag must come after </head> tag.";
            return 1;
        }

        if(head_flag1 == 1) {
            for(auto j : head_tags) {
                if(i.find(j) != 4294967295) {
                    head_flag2 = 1;
                    break;
                }
            }
            if(head_flag2 == 0) {
                cout << "^Error: "<< i <<" tag must not come inside <head> tag.";
                return 1;
            }
        }

        if(body_flag1 == 0 && head_flag1 == 0) {
            for(auto j : body_valid_tags) {
                int pos = i.find(" ");
                string s = i.substr(1, pos-1);
                if(s.find(j) != 4294967295) {
                    body_flag2 = 1;
                    break;
                }
            }
            if(body_flag2 == 1) {
                cout << "^Error: "<< i <<" tag must come inside <body> tag.";
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
    cout << "------------------------------------------\n";
    cout << "------------------------------------------\n";
}