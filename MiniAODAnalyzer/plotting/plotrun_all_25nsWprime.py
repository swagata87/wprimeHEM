#!/bin/env python

from DukePlotALot import *
from plotlib import HistStorage,getColorList,getDictValue,HistStorageContainer,getRGBTColor,makeTeXTable
from configobj import ConfigObj
try:
    from collections import OrderedDict
except ImportError:
    from ordered import OrderedDict

from rootpy.plotting.views import ScaleView
from rootpy.io import File
from basic13TeVconfig25Wprime import plotConfiguration,splitbg
#from basic13TeVconfig25v2WOnly import *
import os,math


def getStystPlot(hist):
    import os
    if os.path.exists("syst/"+hist.replace("/","")+"_syst.root"):
        systFile=File("syst/"+hist.replace("/","")+"_syst.root","read")
        stysthist=systFile.Get(hist)
        stysthist.SetDirectory(0)
        stysthist.SetLineWidth(0)
        stysthist.SetLineColor(0)
    else:
        raise IOError("no syst for %s"%(hist))
    if "Phi" in hist:
        stysthist.Smooth()
    return stysthist

def make_wprimeOverviewPlot(dir_name,hist,histContainer,mt_thresholds):
    rnd=rounding()
    #make a nice tex table
    mtBinOutTeX=open(dir_name+"/"+hist.replace("/","")+"Wprimeoutput.tex","w+")
    head=r"""\documentclass[a4paper,landscape]{article}
\usepackage[utf8]{inputenc}
\usepackage[landscape]{geometry}
\title{}
\date{\today}
\begin{document}


"""
    mtBinOutTeX.write(head)
    mtBinOutTeX.write(r"\begin{table}[h]")
    mtBinOutTeX.write(r"\begin{tabular}{"+" ".join(["l" for i in range(len(mt_thresholds)+2)])+r"}"+"\n")
    line=[" "," "]
    line+=["\MT>{0} GeV".format(mt) for mt in mt_thresholds]
    mtBinOutTeX.write(" & ".join(line) + r"\\"+"\n" )
    line=["Data"," "]
    line+=[rnd.latex(histContainer.getData().integral(xbin1=histContainer.getData().FindBin(mt))) for mt in mt_thresholds]
    mtBinOutTeX.write(" & ".join(line) + r"\\"+"\n" )
    line=["SM Background"," "]
    for mt in mt_thresholds:
        integ,err=histContainer.bg.getAllAdded().integral(xbin1=histContainer.getData().FindBin(mt),error=True)
        line.append(rnd.latex(integ,err))
    mtBinOutTeX.write(" & ".join(line) + r"\\"+"\n" )
    for sg in histContainer.sg.hists:
        line=[sg," "]
        for mt in mt_thresholds:
            integ,err=histContainer.sg.hists[sg].integral(xbin1=histContainer.getData().FindBin(mt),error=True)
            line.append(rnd.latex(integ,err))
        mtBinOutTeX.write(" & ".join(line) + r"\\"+"\n" )
    mtBinOutTeX.write(r"\end{tabular}"+"\n")
    mtBinOutTeX.write(r"\caption{}"+"\n")
    mtBinOutTeX.write(r"\label{tab:}"+"\n")
    mtBinOutTeX.write(r"\end{table}"+"\n")
    tail="""
\end{tabular}
\caption{}
\label{tab:}
\end{table}


\end{document}
"""
    mtBinOutTeX.write(tail)
    mtBinOutTeX.close()


def main():

    cfg=plotConfiguration(do_ddQCD=False)
    #cfg=plotConfiguration(do_ddQCD=True)

    hists=[
        #make a list of histograms to be drawn
        #give the path to the histogram in rootfile
        "demo/histoDir/mT_Stage1",
        "demo/histoDir/tauPt_Stage1"

    ]
    #cfg.DataFiles=["Data_MET"]
    if "multijet" in cfg.bglist:
        cfg.bglist["multijet"]=[
                   "dataDrivenQCD",
                    ]
    #splitbg(r'$\mathsf{t\bar{t}}$',cfg.bglist,cfg.bgcolorList)
    #cfg.bghists.additionalWeight["dataDrivenTree15_pt_baseFit"]=0.5
    systematics={}
    for hist in hists:
        try:
            syst_hist=getStystPlot(hist)
            systematics[hist]=syst_hist
        except:
            continue
    for bg in cfg.bghists.files:
        print bg
    cfg.compile_obj()

    #draw bg, sg and data
    histContainer=HistStorageContainer(bg=cfg.bghists,sg=cfg.sghist,data=cfg.dat_hist)
    #draw bg and data
    #histContainer=HistStorageContainer(bg=bghists,data=dat_hist)

    #set binning for different histograms
    binning={
            #variable binning
            #"_MT":range(200,300,20)+range(300,400,50)+range(400,1600,100)+range(1600,2000,200),
            #"_mt":range(150,400,25)+range(400,1401,50),
            #binned in 20 GeV
            "demo/histoDir/mT_Stage1":20,
            "demo/histoDir/tauPt_Stage1":20,
            "_pt":20,
            "_mt":30,
            "_met":20,
            "MC_W_m_Gen":10,
            "_jet_ht":10,
    }

    xranges={
            #set xrange to be drawn
            "demo/histoDir/mT_Stage1":[0,2000],
            "demo/histoDir/tauPt_Stage1":[0,1500],
            "_pt":[0,1000],
            "_jet_ht":[0,1600],
            "_mt":[150,1600],
            "boson_qt":[0,600],
            "_met":[0,1300],
            "_ET_MET":[0,4],
            "_DeltaPhi":[math.pi/40.*3,math.pi],
            "MC_W_m_Gen":[0,1300],
            "relIso":[0,0.05],
    }
    yranges={
            #set yrange to be drawn
            "_ET_MET":[1.01e-3,1e8],
            "_DeltaPhi":[1.01e-3,1e8],
            #"Taus/":[1.01e-3,1e4],
    }

    #set drawing style for bg and signal
    cfg.bghists.initStyle(style="bg")
    cfg.sghist.initStyle(style="sg")

    for hist in hists:
        dir_name="outFirstTest"
        #dir_name="out13_pfMET"
        if not os.path.exists(dir_name):
            os.mkdir(dir_name)

        #see Plotlib/lib/plotlib.py for functions
        hist_style = sc.style_container(style = 'CMS', useRoot=cfg.useRoot,cmsPositon="upper left",lumi=cfg.lumi,cms=13)    #setup the histograms with lumi and CMS decoration
        hist_style._error_bands_fcol=["grey","yellow"]  #set errorband colors
        hist_style._error_bands_ecol=["lightgrey","yellow"] #set errorband colors
        hist_style._error_bands_alph=0.4    #set errorband alpha?
        hist_style.Set_error_line_width(0.0000000001)
        hist_style.Set_poisson_error_off()  #set error calculation
        hist_style.Set_minor_ticks()  #set tick style
        hist_style.Set_n_legend_columns(2)  #change number of columns to 2
        hist_style.Set_xerr()
        #hist_style.Set_error_bands_center("ref")
        hist_style.Set_do_overflowbin()
        hist_style.SetBatchMode(False)


        print "Working on",hist

        if "W_m_Gen" in hist:
            histContainer=HistStorageContainer(bg=cfg.bghists,data=cfg.bghists)

        histContainer.getHist(hist)

        #if "W_m_Gen" in hist:
            #wbg=filter(lambda x: r"{W\rightarrow l \nu" in x.GetTitle(),   histContainer.getBGList())
            #for bg in wbg:
                #print bg.GetTitle()
            #for bg in histContainer.getBGList():
                #print bg.GetTitle()
            #sumbg=sum(filter(lambda x: r"{W\rightarrow l \nu" in x.GetTitle(),   histContainer.getBGList()))
            #sumbg.GetXaxis().SetTitle("M_{W} [GeV]")
            #sumbg.SaveAs("Wmass.root")
            #continue

        #set binning
        binf=getDictValue(hist,binning)
        if binf is not None:
            if "_phi" not in hist and "jet_ht_lep_pt" not in hist:
                if isinstance(binf,list):
                    histContainer.rebin(vector=binf)
                else:
                    histContainer.rebin(width=binf)

        if "_mt" in hist or "_ET_MET" in hist:

            if "_mt" in hist:
                make_wprimeOverviewPlot(dir_name,hist,histContainer,[500,1000,1400])
                #make_OverviewPlot(dir_name,hist,histContainer,[500,1000,1400])

            makeTeXTable(dir_name,hist,histContainer)


            #generate some output
            mtBinOut=open(dir_name+"/"+hist.replace("/","")+"output.txt","w+")



            #generate some output
            for ibin in range(histContainer.getData().GetNbinsX()):
                mtBinOut.write( "------------------\n")
                mtBinOut.write( "{0}-{1}\n".format(histContainer.getData().xedgesl(ibin),histContainer.getData().xedgesl(ibin+1)))
                sumbg=0.
                for bg in cfg.bghists.hists:
                    weight=1.
                    for ibg in cfg.bglist[bg]:

                        if ibg in cfg.bghists.weight:
                            weight*=cfg.bghists.weight[ibg]

                    mtBinOut.write( "{0}  {1}  {2}\n".format(bg,cfg.bghists.hists[bg].integral(xbin1=ibin),weight))
                    sumbg+=cfg.bghists.hists[bg].integral(xbin1=ibin)
                mtBinOut.write( "data {0}  \n".format(histContainer.getData().integral(xbin1=ibin)))
                mtBinOut.write( "sumbg {0} \n".format(sumbg))

        #generate some output
        if "_pt" in hist:
            makeTeXTable(dir_name,hist,histContainer)

        #generate some output
        if "_ET_MET" in hist:
            mtBinOut=open(dir_name+"/"+hist.replace("/","")+"output2.txt","w+")
            #for ibin in range(histContainer.getData().GetNbinsX()):
            mtBinOut.write( "------------------\n")
            #mtBinOut.write( "{0}\n".format(histContainer.getData().xedgesl(ibin)))
            sumbg=0.
            qcd=0.
            for bg in cfg.bghists.hists:
                weight=1.
                for ibg in cfg.bglist[bg]:

                    if ibg in cfg.bghists.weight:
                        weight*=cfg.bghists.weight[ibg]

                mtBinOut.write( "{0}  {1}  {2}\n".format(bg,cfg.bghists.hists[bg].integral(xbin1=0,xbin2=histContainer.getData().FindBin(0.4))+cfg.bghists.hists[bg].integral(xbin1=histContainer.getData().FindBin(1,5)),weight))
                #mtBinOut.write( "{0}  {1}  {2}\n".format(bg,bghists.hists[bg].integral(xbin1=histContainer.getData().FindBin(1,4)),weight))
                if "multijet" not in bg:
                    sumbg+=cfg.bghists.hists[bg].integral(xbin1=0,xbin2=histContainer.getData().FindBin(0.4))+cfg.bghists.hists[bg].integral(xbin1=histContainer.getData().FindBin(1,5))
                    #sumbg+=bghists.hists[bg].integral(xbin1=histContainer.getData().FindBin(1,4))
                else:
                    qcd=cfg.bghists.hists[bg].integral(xbin1=0,xbin2=histContainer.getData().FindBin(0.4))+cfg.bghists.hists[bg].integral(xbin1=histContainer.getData().FindBin(1,5))
                    #qcd=bghists.hists[bg].integral(xbin1=histContainer.getData().FindBin(1,4))
            alldata=histContainer.getData().integral(xbin1=0,xbin2=histContainer.getData().FindBin(0.4))+histContainer.getData().integral(xbin1=histContainer.getData().FindBin(1,5))
            #alldata=histContainer.getData().integral(xbin1=histContainer.getData().FindBin(1,4))
            mtBinOut.write( "data {0}  \n".format(alldata))
            mtBinOut.write( "sumbg {0} \n".format(sumbg))
            if qcd!=0:
                mtBinOut.write( "qcd_factor {0} \n".format((alldata-sumbg)/qcd))


        if "nPrimaryVertices" in hist:
            mc_vertex_reco=ROOT.TFile("mc_vertex_reco.root","RECREATE")
            h=histContainer.bg.getAllAdded()
            mc_vertex_reco.cd()
            h.Write("pileup")
            mc_vertex_reco.Close()
            data_vertex_reco=ROOT.TFile("data_vertex_reco.root","RECREATE")
            h=histContainer.getData()
            data_vertex_reco.cd()
            h.Write("pileup")
            data_vertex_reco.Close()


        if "Tau_decayMode" in hist:
            for ih in histContainer.allStored:
                for h in ih.hists.values():
                    h.GetXaxis().SetTitle(h.GetXaxis().GetTitle().replace(r"#N_",r"N_"))
        #if "h1_7_Tau_met" in hist:
            #ratio=histContainer.getData().clone()
            #ratio/=sum(histContainer.getBGList())
            #for ibin in ratio.bins():
                #print ibin.x.low, ibin.x.high, ibin.value


        #possibility to make cumulative plot
        #histContainer.makeCumulative()

        #plot backgrounds with or without signals
        test = plotter(hist=histContainer.getBGList(),sig=histContainer.getSGList(),style=hist_style)
        #test = plotter(hist=histContainer.getBGList(),style=hist_style)
        #test = plotter(hist=histContainer.getBGList(),sig=[]  ,style=hist_style)

        lumi_err=histContainer.getData().empty_clone()
        for ibin in lumi_err:
            ibin.value=0.027
        #lumi_err.Draw()
        #raw_input()
        if hist in systematics:
            hist_style._error_bands_fcol=["grey","yellow"]
            hist_style._error_bands_ecol=["lightgrey","yellow"]
            realSyst=histContainer.getData().empty_clone()
            for ibin in range(realSyst.GetNbinsX()):
                realSyst[ibin].value=systematics[hist][systematics[hist].FindBin(realSyst[ibin].x.center)].value
                #print realSyst[ibin].x.center ,realSyst[ibin].value
            test.Add_error_hist(histo = [realSyst,lumi_err],labels=["Syst. uncer.","lumi Uncert"],band_center = "ref",stacking = "linear")
        else:
            hist_style._error_bands_fcol=["yellow"]
            hist_style._error_bands_ecol=["yellow"]
            test.Add_error_hist(histo = [lumi_err],labels=["lumi Uncert"],band_center = "ref",stacking = "linear")

        #add data to plot
        test.Add_data(histContainer.getData())




        #set x and y ranges for plot
        ymax=.5e4
        if ("h1_4_" in hist) and not "phi" in hist:
            ymax=.5e5
        if "h1_0" in hist:
            ymax=.5e11
        myrange=getDictValue(hist,yranges)
        if myrange is not None:
            ymax=myrange[1]
        test.Set_axis(ymin=1.01e-3,ymax=ymax)
        mxrange=getDictValue(hist,xranges)
        if mxrange is not None:
            if "_phi" not in hist and "jet_ht_lep_pt" not in hist:
                test.Set_axis(ymin=1.01e-3,ymax=ymax,xmin=mxrange[0],xmax=mxrange[1])
            if "jet_ht_lep_pt" in hist:
                test.Set_axis(ymin=1.01e-3,ymax=ymax,xmin=0,xmax=5)
                #test.Set_axis(ymin=1.01e-3,ymax=.5e3,xmin=mxrange[0],xmax=mxrange[1])
            #if "_mt" in hist:
                #test.Set_axis(ymin=1.01e-3,ymax=.5e3,xmin=mxrange[0],xmax=mxrange[1])
        #else:
            #test.Set_axis(ymin=1.01e-1,ymax=.5e4)
        #name=hist.replace("/","")
        name=hist.split("/")[-1]

        #if useRoot:
            #test.Add_plot('DiffRatio_width_increase',pos=0, height=15)
        #elif not "h1_0" in hist:
            ##test.Add_plot('Signi',pos=0, height=15)
            #test.Add_plot('Ratio',pos=1, height=15)
            ##test.Add_plot('DiffRatio_width_increase',pos=2, height=15)

        #set additional plots like ratio plot
        """
        if "mt" in hist and not "_syst_iso_QCD" in hist:
            test.Add_plot('Ratio_width_increase',pos=1, height=15)
            test.Add_plot('DiffRatio_width_increase',pos=2, height=15)
        elif not "_syst_iso_QCD" in hist:
            test.Add_plot('Ratio_width_increase',pos=1, height=15)
        """
        #test.Add_plot('Signi',pos=2, height=15)
        #test.Add_plot('Diff',pos=2, height=15)
        #test.Add_plot('Ratio',pos=1, height=15)
        #test.Add_error_hist([sys_hist_2,sys_hist], band_center = 'ref')
        #test.ChangeStyle(cms_val=8,lumi_val=lumi)


        #drawing
        print "make plot",name
        mplt=test.create_plot()
        part="e"
        if "Tau" in hist:
                part="\\tau"
        mplt.text(hist_style.Get_cmsTextPosition().getX()+ 0.16, hist_style.Get_cmsTextPosition().getY()-0.03, r'$\mathsf{%s+E_{T}^{miss}}$'%(part), va='bottom', ha='left', color=hist_style.Get_annotation_text_color(), size=14, weight='normal')
        print "save plot", '%s/%s.png'%(dir_name,name)
        #test.SavePlot('%s/%s_C.png'%(dir_name,name))
        #test.SavePlot('%s/%s_C.pdf'%(dir_name,name))
        #test.SavePlot('%s/%s_D.png'%(dir_name,name))
        #test.SavePlot('%s/%s_D.pdf'%(dir_name,name))
        #test.SavePlot('%s/%s_E.png'%(dir_name,name))
        #test.SavePlot('%s/%s_E.pdf'%(dir_name,name))
        test.SavePlot('%s/%s_CDE.png'%(dir_name,name))
        test.SavePlot('%s/%s_CDE.pdf'%(dir_name,name))
        #test.make_plot('out13_new/%s.pdf'%(name))
        #test.make_plot('out13_new/%s.png'%(name))
        #test.SavePlot('out13_new/%s.pdf'%(name))
        #test.make_plot('%s_cumulative.pdf'%(name))
    sys.exit()



main()
