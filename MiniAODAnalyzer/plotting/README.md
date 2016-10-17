# WPrimeToTau TAPAS Plotter

First setup TAPAS to have access to the plotlib. Instructions for the setup can be found on https://gitlab.cern.ch/aachen-3a/tapas
In order to achieve compatability with the WPrimeToTau analyser, one has to change in line 522 of plotlib/lib/plotlib.py "h_counters" to "demo/histoDir/eventCount".

Once the plotlib is compatible, one can execute the plotting script with:
python plotrun_all_25nsWprime.py

The cross sections have to be entered in "xsFile13TeV_25ns_wprime.cfg" while the list of backgrounds, data and signals is entered in "basic13TeVconfig25Wprime.py". Also the lumi has to be written in there.

At the moment the x and y labels are not implemented correctly