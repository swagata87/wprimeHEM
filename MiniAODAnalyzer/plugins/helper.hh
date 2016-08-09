// Original Author:  Marcel Materok
//         Created:  Thu, 4 Jul 2016 10:28:57 GMT


#include <vector>
#include "TTree.h"
#include "TString.h"
#include <string>
#include <unordered_map>
#include <unordered_set>



class Helper{
    public:
        Helper(edm::Service<TFileService> fileService);
        virtual void Tree_Creater(std::unordered_map< std::string , float > *m, const char * name);
        virtual void Tree_Filler(const char * name);
        virtual void WriteAll(const char * name);
        virtual void CreateHistoUnchangedName(const char* name, Int_t nbinsx, Double_t xlow, Double_t xup, TString xtitle);
        virtual void WriteTree(const char * name);
    private:
        edm::Service<TFileService> fs2;
        TFileDirectory treeDir;
        std::unordered_map<std::string, TTree * > trees; /*!< Map of a string and a TTree histogram, for easy tree handling. */
        std::unordered_map<std::string, TH1D * > histo; /*!< Map of a string and a TH1D histogram, for easy 1D histogram handling. */
};

Helper::Helper(edm::Service<TFileService> fileService){
    fs2 = fileService;
    treeDir = fs2->mkdir( "treeDir" );
}
void Helper::Tree_Creater(std::unordered_map< std::string , float > *m, const char * name) {
    trees[name] = treeDir.make<TTree>(name, name);
    for (std::unordered_map< std::string , float >::iterator it = m->begin(); it != m->end(); it++) {
        trees[name]->Branch(it->first.c_str(), &(it->second), Form("%s/F", it->first.c_str()));
    }
}
void Helper::Tree_Filler(const char * name) {
    trees[name]->Fill();
}
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
void Helper::WriteTree(const char * name = "") {
    trees[name]->Write();
}

void Helper::CreateHistoUnchangedName(const char* name, Int_t nbinsx, Double_t xlow, Double_t xup, TString xtitle = "") {
        TH1D * tmphist = new TH1D(Form("%s", name), xtitle, nbinsx, xlow, xup);
        tmphist->SetXTitle(xtitle);
        tmphist->Sumw2();
        histo[Form("%s", name)] = tmphist;
    }

