#!/bin/env python
from plotlib import HistStorage,getColorList,getDictValue,HistStorageContainer,getRGBTColor
from configobj import ConfigObj
try:
    from collections import OrderedDict
except ImportError:
    from ordered import OrderedDict

def splitbg(whichbg,bglist,colorlist):
    for bg in bglist[whichbg]:
        bglist[bg]=[bg]
    randomColors=getColorList(len(bglist[whichbg]))
    for bg in bglist[whichbg]:
        colorlist[bg]=randomColors.pop()
    del bglist[whichbg]

class plotConfiguration:
    def __init__(self, useRoot=False ,basedir=None ,do_ddQCD=True):
        if basedir is None:
            self.basedir="/net/scratch_cms/institut_3a/materok/wprime/run1/crab_projects/merged"
        else:
            self.basedir=basedir
        self.useRoot=useRoot


        self.xs= ConfigObj("xsFile13TeV_25ns_wprime.cfg")

        #self.lumi= 2646 #RunC
        #self.lumi= 4353 #RunD
        #self.lumi= 4049 #RunE
        self.lumi= 11048 #RunC + RunD + RunE

        self.bghists=HistStorage(self.xs,self.lumi,path=self.basedir,useRoot=self.useRoot)
        self.bghists.setDataDriven("dataDrivenQCD")
        self.bghists.setDataDriven("dataDrivenTree")
        self.bghists.setDataDriven("dataDrivenTreept")
        self.bghists.setDataDriven("dataDrivenTreedecay_mode")
        self.bghists.setDataDriven("dataDrivenTreeeta")
        self.bghists.setDataDriven("dataDrivenTreelepton_n")
        self.bghists.setDataDriven("dataDrivenTree15_pt_base")
        self.bghists.setDataDriven("dataDrivenTree15_pt_baseFit")
        self.bghists.setDataDriven("dataDrivenTree15_pt_decay_base")
        self.bghists.setDataDriven("dataDrivenTree15_pt_decay_baseFit")
        self.bghists.setDataDriven("dataDrivenTree15_pt_eta_baseFit")
        self.bghists.setDataDriven("dataDrivenTree15_pt_eta_base")
        self.bghists.setDataDriven("dataDrivenTree15_lepton_n_base")
        self.bghists.setDataDriven("dataDrivenTree15_decay_mode_base")


        #do_ddQCD=False
        self.bglist=OrderedDict()
        self.bglist["Diboson"]=[
        "WW_TuneCUETP8M1_13TeV-pythia8",
        "WZ_TuneCUETP8M1_13TeV-pythia8",
        "ZZ_TuneCUETP8M1_13TeV-pythia8"
        ]

        if not do_ddQCD:
            self.bglist[r"$Z\rightarrow \nu\nu$"]=[
            "ZJetsToNuNu_HT-100To200_13TeV-madgraph",
            "ZJetsToNuNu_HT-200To400_13TeV-madgraph",
            "ZJetsToNuNu_HT-400To600_13TeV-madgraph",
            "ZJetsToNuNu_HT-600To800_13TeV-madgraph",
            "ZJetsToNuNu_HT-800To1200_13TeV-madgraph",
            "ZJetsToNuNu_HT-1200To2500_13TeV-madgraph",
            "ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph"
            ]
        self.bglist[r"$\mathsf{Z/\gamma}$"]=[
        "DYJetsToLL_M-5to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"
        ]

        self.bglist[r'$\mathsf{t\bar{t}}$']=[
        "TT_TuneCUETP8M1_13TeV-powheg-pythia8",
        "ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        "ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        "ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"
        ]
        if do_ddQCD:
            self.bglist["multijet"]=[
                "dataDrivenQCD",
            ]

        if not do_ddQCD:
            self.bglist["QCD"]=[
        "QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"
            ]



        #self.bglist[r'$\mathsf{W\rightarrow l \nu}$ $\mathsf{M_{W}<200 GeV}$']=[
        #"WJetsToLNu_HT-100To200_13TeV_MG",
        #"WJetsToLNu_HT-200To400_13TeV_MG",
        #"WJetsToLNu_HT-400To600_13TeV_MG",
        ##"WJetsToLNu_HT-600To800_13TeV_MG",
        #"WJetsToLNu_HT-600ToInf_13TeV_MG",
        ##"WJetsToLNu_HT-800To1200_13TeV_MG",
        ##"WJetsToLNu_HT-1200To2500_13TeV_MG",
        ##"WJetsToLNu_HT-2500ToInf_13TeV_MG",
        ##"WJetsToLNu_13TeV-FXFX_MC",
        ##"WJetsToLNu_13TeV_MG",
        #"WJetsToLNu_13TeV_AM",
        #]
        #self.bglist[r'$\mathsf{W\rightarrow l \nu}$ MCatNLO']=[
        ###"WJetsToLNu_13TeV-FXFX_MC",
        #"WJetsToLNu_13TeV_AM",
        ###"WJetsToLNu_13TeV-FXFX_MC",
        ##"WJetsToLNu_13TeVMLM_MG",
        #]

        self.bglist[r'$\mathsf{W\rightarrow l \nu}$']=[
        "WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"
        ]




        self.bghists.additionalWeight["dataDrivenQCD"]=0.938091502614

        self.bghists.additionalWeight["TT_13TeV_AM"]=1./3.
        self.bghists.additionalWeight["TT_13TeV_ext1_AM"]=1./3.
        self.bghists.additionalWeight["TTJets_13TeV_AM"]=1./3.

        self.bghists.additionalWeight["TT_13TeV_ext3_PH"]=1./2.
        self.bghists.additionalWeight["TT_13TeV_ext4_PH"]=1./2.


        self.bghists.additionalWeight["TT_Mtt-700to1000_13TeV_ext1_PH"]=1./2.
        self.bghists.additionalWeight["TT_Mtt-700to1000_13TeV_PH"]=1./2.

        self.bghists.additionalWeight["TT_Mtt-1000toInf_13TeV_ext1_PH"]=1./2.
        self.bghists.additionalWeight["TT_Mtt-1000toInf_13TeV_ext2_PH"]=1./2.

        self.bghists.additionalWeight["WWToLNuQQ_13TeV_ext1_PH"]=1./2.
        self.bghists.additionalWeight["WWToLNuQQ_13TeV_PH"]=1./2.



        #bghists.additionalWeight["WJetsToLNu_HT-100To200_13TeV_MG"]=0.5
        #bghists.additionalWeight["TT_13TeV_PH"]=0.5
        #bghists.additionalWeight["TT_13TeV_ext3_PH"]=0.5
        #bghists.additionalWeight["ST_t-channel_4f_leptonDecays_13TeV_AM"]=0.5
        #bghists.additionalWeight["DYJetsToLL_M-50_13TeV_ext1_AM"]=0.5
        #bghists.additionalWeight["ST_t-channel_4f_leptonDecays_13TeV_ext1_AM"]=0.5


        self.bgcolorList={}
        self.bgcolorList[r'$\mathsf{W\rightarrow l \nu}$']=getRGBTColor(861)
        self.bgcolorList["W"]=getRGBTColor(861)
        self.bgcolorList["W on shell"]="lightblue"
        self.bgcolorList[r'$\mathsf{W\rightarrow l \nu}$ MCatNLO']="brown"
        self.bgcolorList[r'$\mathsf{W\rightarrow l \nu}$ $\mathsf{M_{W}<200 GeV}$']="lightblue"
        self.bgcolorList["W HT"]="orange"
        self.bgcolorList["multijet"]=getRGBTColor(213)
        self.bgcolorList["multijet MC"]=getRGBTColor(216)
        self.bgcolorList["QCD from data"]=getRGBTColor(213)
        self.bgcolorList["QCD jet"]=getRGBTColor(213)
        self.bgcolorList["QCD MC"]="brown"
        self.bgcolorList["QCD"]="brown"
        self.bgcolorList["Z (inv)"]="darkblue"
        self.bgcolorList["Top"]=getRGBTColor(616)
        self.bgcolorList["$t\bar{t}$"]=getRGBTColor(616)
        self.bgcolorList[r'$\mathsf{t\bar{t}}$']="orange"
        self.bgcolorList["Diboson"]=getRGBTColor(413)
        self.bgcolorList[r"$\mathsf{Z/\gamma}$"]=getRGBTColor(810)
        self.bgcolorList["DY"]=getRGBTColor(810)
        self.bgcolorList[r"$\mathsf{\gamma  jets}$"]="yellow"
        self.bgcolorList[r"$Z\rightarrow \nu\nu$"]="yellow"

        # dummy signal
        #setup signals

        self.sghist=HistStorage(self.xs,self.lumi,path=self.basedir,useRoot=self.useRoot)
        self.sgList=OrderedDict()
        self.sgList["W' M=1TeV"]=["WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola"]

        self.sgcolorlist={}
        self.sgcolorlist["W' M=1TeV"]="darkred"

        self.dat_hist=HistStorage(self.xs,self.lumi,path=self.basedir,isData=True,useRoot=self.useRoot)

        #self.DataFiles=["TauRunC"]
        #self.DataFiles=["TauRunD"]
        #self.DataFiles=["TauRunE"]
        self.DataFiles=["TauRunC","TauRunD","TauRunE"]


    def compile_obj(self):
        self.bghists.addFileList(self.bglist)
        self.bghists.colorList=self.bgcolorList

        self.sghist.addFileList(self.sgList)
        self.sghist.colorList=self.sgcolorlist

        for data in self.DataFiles:
            self.dat_hist.addFile(data)
