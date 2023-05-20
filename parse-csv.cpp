#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <string>
#include <vector>
#include "rapidcsv.h"

//function to find most common words
std::vector<std::string> topKFrequent(std::vector<std::string>& nums, std::vector<int>& occurs, int k) {
    std::map<std::string, int> hashmap;
    std::vector<std::string> ans;
    std::priority_queue<int> maxHeap;
    for (auto &num:nums) {
        hashmap[num]++;
    }
    for (auto &it:hashmap) {
        maxHeap.push(it.second);
    }
    while (k>0) {
        int countFreq = maxHeap.top();
        maxHeap.pop();
        for (auto &it:hashmap) {
            if(countFreq == it.second) {
                ans.push_back(it.first);
                occurs.push_back(countFreq);
                hashmap.erase(it.first);
                k--;
                break;
            }
        }
    }
    return ans;

}

//parses CSV, further parses it into words, calls topKFrequent, then outputs a CSV containing the values.
int main(int argc, char** argv) {
    
    std::string inputFile;  //first cli argument
    std::string outputFile; //second cli argument
    int numLines = -1;      //third cli argument
    int topK;               //fourth cli argument
    
    bool doFullCSV = false;
    std::vector<std::string> allMsgs;
    std::string word;
    std::string msg;
    int i = 0;
    
    if(argc < 5) {
        std::cout << "usage: ./parse-csv input.csv output.csv NUM_LINES TOP_K" << std::endl;
        return 0;
    }
    
    inputFile = argv[1];
    outputFile = argv[2];
    if(atoi(argv[3]) == -1) {
        doFullCSV = true;
    } else {
        numLines = atoi(argv[3]);
    }
    topK = atoi(argv[4]);
    
    std::cout << "Reading input CSV..." << std::endl;
    rapidcsv::Document doc(inputFile, rapidcsv::LabelParams(0, 0));
    
    //parses each message into its individual words
    while(i < doc.GetRowCount()) {
        if(doFullCSV == false && i > numLines) {
            break;
        }
        
        std::cout << "Getting message #" << i + 1 << "... ";
        
        //this try/catch block basically tells the computer to just give up on getting a certain cell (and move to the next one) 
        //if it has trouble. this is a dumb solution!
        try {
            msg = doc.GetCell<std::string>(2, i);
        } catch (std::exception e) {
            std::cout << "Failed                          " << std::endl;
            i++;
            continue;
        }

        std::stringstream ss(msg);

        std::cout << "Parsing words...";
        while(ss >> word) {
            allMsgs.push_back(word);
        }
        std::cout << "Finished\r" << std::flush;
        i++;
    }



    //output csv
    std::cout << "\rCreating new CSV...                                   " << std::endl;
    std::ofstream newDocFile(outputFile);
    newDocFile << "K,Word,Occurences" << std::endl;
    newDocFile.close();
    rapidcsv::Document newDoc(outputFile);
    
    //find most common words in the entire channel
    std::vector<int> occurs;
    std::vector<std::string> ans = topKFrequent(allMsgs, occurs, topK);

    //push data from topKFrequent to output csv
    for(int i = 0; i < topK; i++) {
        std::vector<std::string> rowData;
        rowData.push_back(std::to_string(i + 1));
        rowData.push_back(ans[i]);
        rowData.push_back(std::to_string(occurs[i]));
        newDoc.InsertRow(i, rowData);
    }
    
    newDoc.Save(); 
    std::cout << "Done!                      " << std::endl;
}