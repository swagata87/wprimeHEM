// -*- C++ -*-
//
// Package:    WPrimeToTau/MiniAODAnalyzer
// Class:      MiniAODAnalyzer
//
/**\class MiniAODAnalyzer MiniAODAnalyzer.cc WPrimeToTau/MiniAODAnalyzer/plugins/MiniAODAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Swagata Mukherjee
//         Created:  Tue, 05 Jul 2016 09:41:37 GMT
//
//


#include <vector>
#include "TTree.h"
#include <string>
#include <unordered_map>
#include <unordered_set>


//#ifdef __GNUC__
//#define SUPPRESS_NOT_USED_WARN __attribute__ ((unused))
//#else
//#define SUPPRESS_NOT_USED_WARN
//#endif

class Helper{
    public:
        virtual void Tree_Creater(std::unordered_map< std::string , float > *m, const char * name);
        virtual void Tree_Filler(const char * name);
        virtual void WriteAll(const char * name);
    private:
        std::unordered_map<std::string, TTree * > trees; /*!< Map of a string and a TTree histogram, for easy tree handling. */
        std::unordered_map<std::string, TH1D * > histo; /*!< Map of a string and a TH1D histogram, for easy 1D histogram handling. */
};

//SUPPRESS_NOT_USED_WARN
void Helper::Tree_Creater(std::unordered_map< std::string , float > *m, const char * name) {
    trees[name] = new TTree(name, name);
    for (std::unordered_map< std::string , float >::iterator it = m->begin(); it != m->end(); it++) {
        trees[name]->Branch(it->first.c_str(), &(it->second), Form("%s/F", it->first.c_str()));
    }
}
void Helper::Tree_Filler(const char * name) {
    trees[name]->Fill();
}
//*/
//#endif

void Helper::WriteAll(const char * name = "") {
    std::unordered_map<std::string, TH1D * >::iterator it;
    for (std::unordered_map<std::string, TH1D * >::iterator it = histo.begin(); it != histo.end(); ++it) {
        if (strcmp(name, "") != 0 && std::string::npos != it->first.find(name)) {
            it->second -> Write();
        } else if (strcmp(name, "") == 0) {
            it->second -> Write();
        }
    }
}





//define this as a plug-in
//DEFINE_FWK_MODULE(MiniAODAnalyzer);
