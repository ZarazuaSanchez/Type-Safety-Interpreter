#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <regex>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[]) {

    string cmdln = argv[1];
    string filename = cmdln.substr(cmdln.find("=")+1);
    string outputfilename = filename.substr(0,filename.find(".py")) + ".out";
    ifstream input(filename);
    ofstream output(outputfilename);

    string line;

    map<string,string> varTable;
    map<string,string> varVal;
    map<string, string> listVal;

    const regex intassign_regex("([a-zA-Z0-9_][a-zA-Z0-9_]*)(=)(\\d+)");
    const regex strassign_regex("([a-zA-Z0-9_][a-zA-Z0-9_]*)(=)(\")(\\w*)(\")");
    const regex twovarsassign("([a-zA-Z0-9_][a-zA-Z0-9_]*)(=)(([a-zA-Z0-9_][a-zA-Z0-9_]*))");
    const regex emptylistassign_regex("([a-zA-Z0-9_][a-zA-Z0-9_]*)(=)(\\[\\])");
    const regex intlistassign_regex("([a-zA-Z0-9_][a-zA-Z0-9_]*)(=)(\\[)((\\d+,?)*)(\\])");
    const regex strlistassign_regex("([a-zA-Z0-9_][a-zA-Z0-9_]*)(=)(\\[)(((\")(\\w*)(\",?))*)(\\])");
    const regex appendint_regex("([a-zA-Z0-9_][a-zA-Z0-9_]*)(\\.append\\()(\\d+)(\\))");
    const regex appendstr_regex("([a-zA-Z0-9_][a-zA-Z0-9_]*)(\\.append\\()(\")(\\w*)(\")(\\))");

    while(getline(input, line)){

        smatch pieces_match;

        string statement = "x=[\"1\",\"2\",\"3\"]";

        line.erase(remove(line.begin(),line.end(), ' '));

        /*
        * Each case assumes the FIRST occurrence of the identifer
        */

        if(regex_match(line, pieces_match, intassign_regex)){

            //put in varTable
            ssub_match sub_match = pieces_match[1];
            string var = sub_match.str();

            if(varTable.find(var)!=varTable.end()){
                string type = varTable[var];
                if(type=="int"){
                    sub_match = pieces_match[3];
                    string literal = sub_match.str();
                    varVal[var] = literal;
                }
                else{
                    ouput << "#warning"
                }
            }
            else{
                varTable[var] = "int";

                sub_match = pieces_match[3];
                string literal = sub_match.str();
                varVal[var] = literal;
            }
        }

        if(regex_match(line, pieces_match,strassign_regex)){

            for (size_t i = 0; i < pieces_match.size(); i++) {
                ssub_match sub_match = pieces_match[i];
                string piece = sub_match.str();
                cout << "   submatch " << i << " " << piece << '\n';
            }
            ssub_match sub_match = pieces_match[1];
            string var = sub_match.str();
            varTable[var] = "str";

            sub_match = pieces_match[4];
            string literal = sub_match.str();
            varVal[var] = literal;
        }

        if(regex_match(line, pieces_match, emptylistassign_regex)){
            ssub_match sub_match = pieces_match[1];
            string var = sub_match.str();
            varTable[var] = "emptylist";

            listVal[var] = "";
        }

        if(regex_match(line, pieces_match, intlistassign_regex)){

            for (size_t i = 0; i < pieces_match.size(); i++) {
                ssub_match sub_match = pieces_match[i];
                string piece = sub_match.str();
                cout << "   submatch " << i << " " << piece << '\n';
            }

            ssub_match sub_match = pieces_match[1];
            string var = sub_match.str();
            varTable[var] = "intlist";

            sub_match = pieces_match[4];
            string elems = sub_match.str();
            listVal[var] = elems;
        }

        if(regex_match(line, pieces_match, strlistassign_regex)){
            for (size_t i = 0; i < pieces_match.size(); i++) {
                ssub_match sub_match = pieces_match[i];
                string piece = sub_match.str();
                cout << "   submatch " << i << " " << piece << '\n';
            }
        }

        if(regex_match(line, pieces_match, appendint_regex)){

            ssub_match sub_match = pieces_match[1];
            string var = sub_match.str(); //get int to be appended
            string type = varTable[var];

            sub_match = pieces_match[3];
            string intelem = sub_match.str();

            if(type=="intlist"){
                string elems = listVal[var];
                elems += ("," + intelem);
            }
            else{
                output << "#warning" << endl;
            }
        }

        if(regex_match(line, pieces_match, appendstr_regex)){
            ssub_match sub_match = pieces_match[1];
            string var = sub_match.str(); //get str to be appended
            string type = varTable[var];

            sub_match = pieces_match[3];
            string strelem = sub_match.str();

            if(type=="strlist"){
                string elems = listVal[var];
                elems += ("," + strelem);
            }
            else{
                output << "#warning" << endl;
            }
        }

        //case  x + y or z = x + y
        if(regex_match())

        // x=y
        if(regex_match(line, pieces_match, twovarsassign)){

            ssub_match sub_matchx = pieces_match[1];
            string x = sub_match.str();

            ssub_match sub_matchy = pieces_match[3];
            string y = sub_match.str();

            if(varTable.find(x)!=varTable.end()){

                if(varTable.find(y)!=varTable.end()){
                    string typex = varTable[x];
                    string typey = varTable[y];

                    if(typex==typey){
                        //assign value of y to x
                    }
                    else{
                        ouput << "#warning" << endl;
                    }
                }
            }
        }

        output << line << endl;
    }

    return 0;
}
