#include "parser.h"
#include <iostream>
#include <sstream>
#include <fstream>
//#include <string>
//#include <map>
//#include <vector>

using namespace std;

txf_object parse_recursive(ifstream& stream, string& parent_tag_name) {
    txf_object obj;
    string line;
    while (getline(stream, line))
    {
        auto firstChar = line[0];
        auto rest = line.substr(1);
        
        switch (firstChar) {
            case '$': {
                auto idx = rest.find_first_of('=');
                
                if (idx == -1) {
                    ostringstream o;
                    o << "no = sign: " << line;
                    throw o.str();
                }
                auto key = rest.substr(0,idx);
                auto value = rest.substr(idx+1);
                obj.properties[key] = value;
                break;
            }
            case '#': {
                auto sub_obj = parse_recursive(stream, rest);
                obj.sub_objects[rest].push_back(sub_obj);
                break;
            }
            case '/':
                if(rest != parent_tag_name) {
                    ostringstream o;
                    o << "mismatch end of object " << rest << " != " << parent_tag_name;
                    throw o.str();
                } else {
                    return obj;
                }
                break;
            default:
                ostringstream o;
                o << "mismatch line " << line;
                throw o.str();
                break;
        }
        
    }
    
    throw "I don't know why I'm here. Probably because the file is missing an end of object marker";
}


/* from the parser.h */

txf_object parse(const std::string& file_path) {
    txf_object result;
    
    ifstream stream(file_path);
    string line;
    if (getline(stream, line))
    {
        string tag_name = line.substr(1);
        result = parse_recursive(stream, tag_name);
    } else {
        throw "file is empty or does not exist";
    }
    
    return result;
}

void visualise(const txf_object& object, int indent) {
    for(auto& property : object.properties) {
        cout << string(indent, '\t') << property.first << " = " << property.second << endl;
    }
    
    for(auto& sub_objects : object.sub_objects) {
        for(auto& subObject : sub_objects.second) {
            cout << string(indent, '\t') << sub_objects.first << ": " << endl;
            visualise(subObject, indent + 1);
        }
    }
}





