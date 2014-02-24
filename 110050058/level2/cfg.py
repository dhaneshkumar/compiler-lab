import os  
path = "test_files"
files=[]
for f in os.listdir(path):
    files.append(f) 

correct_files=[]
for f in files:
    fileName,fileExt = os.path.splitext( path + f)
    if( fileExt == '.c'):
        correct_files.append(f)



cfgFiles=[]
for f in correct_files:
    command = "make -f Makefile.cfg FILE=" + f+ " >/dev/null";
    os.system(command);
    cfgFiles.append(path+"/"+f+"s306.cfg") 

print("Done generating cfg files\n")

for f in cfgFiles:
    print("Testing file  " + f ); 
    command = "./cfglp32 "+ f + " -ast -d > " +f+".ast" 
    print(command)
    os.system(command) 

    command = "./cfglp32 -tokens -d " + f  + " > expected"
    print(command)
    os.system(command) 
    """print(f);"""
    

    command = "./cfglp -tokens -d " + f + " > generated " 
    os.system(command)
    os.system("diff -bB expected generated")
    

print("\n*****Done with the checking cfg files EXCEPT infi loops!!***\n")
"""
error_files=[]
for f in files:
    fileName,fileExt = os.path.splitext( path + f)
    if( fileExt == '.ecfg'):
        error_files.append(path + "/" +f)


for f in error_files:
    print("Testing file  " + f ); 
    command = "./cfglp32 -tokens  " + f + " 2> expected " 
    os.system(command) 
    command = "./cfglp -tokens " + f + " 2> generated " 
    os.system(command)
   
    #print("diff starts here \n");
    os.system("diff -B expected generated")
    

print("\n*****Done with the checking ecfg files!!***\n")
"""

#print cfgFiles



