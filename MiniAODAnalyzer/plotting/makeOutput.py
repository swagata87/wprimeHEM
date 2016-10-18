import os
import shutil

directory="/net/scratch_cms/institut_3a/materok/wprime/okt14/crab_projects"
filepath="/results/hist.root"

MCfile = open(directory+'/MClist.txt', 'w')

number=len(os.listdir(directory))
counter=0

if not os.path.exists(directory+"/merged"):
    print (directory+"/merged"), " does not exist yet, creating now"
    os.makedirs(directory+"/merged")

for name in os.listdir(directory):
    path=directory+"/"+name+filepath
    print "working on: ", name.replace("crab_","")

    if name=="merged" or name=="MClist.txt" or name=="crab.log":
        counter+=1
        print "done with ",counter, " out of ", number, " directories"
        continue
    if os.path.isfile(path):
        #print directory+name.replace("crab_","/merged/")+".root"
        if not os.path.isfile(directory+name.replace("crab_","/merged/")+".root"):
            print "doesnt exist in merged yet, will copy"
            shutil.copy2(path,directory+name.replace("crab_","/merged/")+".root")
        else:
            print "exists and is skipped"
        MCfile.write(name.replace("crab_",""))
        MCfile.write("\n")
    counter+=1
    print "done with ",counter, " out of ", number, " directories"
MCfile.close()
print "done"