import os  
path = "test_files"
files=[]
for f in os.listdir(path):
    files.append(f) 

correct_files=[]
for f in files:
    fileName,fileExt = os.path.splitext( path + f)
    if( fileExt == '.cfg'):
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
    command = "./cfglp -icode " + f
    os.system(command)
    icfile = f+".ic";
    os.system("cp " + icfile + "  t2.txt");

    command = "./cfglp64 -icode " + f
    os.system(command)
    os.system("cp " + icfile + "  t1.txt");

    os.system("diff -bB t1.txt t2.txt");
    continue
