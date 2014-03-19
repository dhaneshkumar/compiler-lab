import os  
path = "test_files"
files=[]
for f in os.listdir(path):
    files.append(f) 

correct_files=[]
for f in files:
    fileName,fileExt = os.path.splitext( path + f)
    if( fileExt == '.ecfg'):
        correct_files.append(path+"/"+ f)

"""

cfgFiles=[]
for f in correct_files:
    command = "make -f Makefile.cfg FILE=" + f+ " >/dev/null";
    os.system(command);
    cfgFiles.append(path+"/"+f+"s306.cfg")
"""
print("Done generating cfg files\n");

for f in correct_files:
    print("Testing file  " + f ); 
    command = "./cfglp -icode -d " + f +" 2> a"
    os.system(command)
   

    command = "./cfglp64 -icode -d " + f +" 2> b"
    os.system(command)
   

    os.system("diff -bB a b");
    continue
