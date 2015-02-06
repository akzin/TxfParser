
#ifndef __parser__
#define __parser__


#include <iostream>
#include <map>
#include <vector>

struct txf_object {
    std::map<std::string,std::string> properties;
    std::map<std::string,std::vector<txf_object>> sub_objects;
};


txf_object parse(const std::string& file_path);
void visualise(const txf_object& object, int indent = 0);


#endif /* defined(__parser__) */
