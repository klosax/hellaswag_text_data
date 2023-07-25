#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Requires json.hpp from https://github.com/nlohmann/json
#include "json.hpp"
using json = nlohmann::json;

void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

std::string preprocess_data( std::string datastr ) {

    ReplaceStringInPlace( datastr, "[header]", "");
    ReplaceStringInPlace( datastr, "[step]", "");
    ReplaceStringInPlace( datastr, "[substeps]", "");
    ReplaceStringInPlace( datastr, " [title]", ". ");
    ReplaceStringInPlace( datastr, "[title] ", "");
    ReplaceStringInPlace( datastr, "[title].", "");
    ReplaceStringInPlace( datastr, "  ", " ");

    if( datastr[0] == ' ' ) {
        datastr.erase( datastr.begin() );
    }
    if( datastr[datastr.size()-1] == ' ' ) {
        datastr.erase( datastr.end() );
    }

    return datastr;
}


int main(int argc, char ** argv) {

    // Requires hellaswag validation dataset file from https://github.com/rowanz/hellaswag/blob/master/data/hellaswag_val.jsonl

    std::string filename = "hellaswag_val.jsonl";
    std::string jsonl_data;
    std::ifstream file(filename);
    if (!file) {
        fprintf(stderr, "error: failed to open file '%s'\n", filename.c_str());
        return 0;
    }
    std::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), std::back_inserter(jsonl_data));

    std::vector<std::string> lines_inp;
    std::string line;
    std::istringstream strstream(jsonl_data);
    while (std::getline(strstream,line,'\n')) {
        lines_inp.push_back(line);
    }

    std::ofstream fout;

    // Parse hellaswag validation set and dump all tasks
    //
    // 6 lines per task:
    // activity_label + ": " + context
    // gold_ending_label
    // ending1
    // ending2
    // ending3
    // ending4

    fout = std::ofstream( "hellaswag_val_full.txt", std::ios::binary);
    std::string outline;

    for(size_t i=0;i< lines_inp.size();i++) {
        json hellaswag = json::parse( lines_inp[i] );

        outline = preprocess_data( hellaswag["activity_label"].get<std::string>() ) + ": " + preprocess_data( hellaswag["ctx"].get<std::string>() ) + "\n";
        fout.write((char *) outline.data(), outline.size() );

        outline = std::to_string( hellaswag["label"].get<int>() )+ "\n";
        fout.write((char *) outline.data(), outline.size() );

        for(size_t j=0;j<4;j++) {
            outline = preprocess_data( hellaswag["endings"][j].get<std::string>() ) + "\n";
            fout.write((char *) outline.data(), outline.size() );
        }
    }
    fout.close();

}
