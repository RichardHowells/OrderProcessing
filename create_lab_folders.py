import os, stat
import shutil
import subprocess

def checkoutCode(repoDir:str, gitTag:str, directoryName:str):
    print(f"switching to tags/{gitTag}")

    # Grab the cwd, switch to the repo dir, because git switch has to be in that dir
    # then switch the cwd back
    currentWorkingDir = os.getcwd()

    os.chdir(repoDir)
    
    subprocess.run(["git", "switch", "--detach", f"tags/{gitTag}"])

    os.chdir(currentWorkingDir)

    #  Copy items to the target directory
    if os.path.isdir(directoryName):
        # The directory is already there - remove it recursively
        print(f"Removing directory {directoryName}")
        shutil.rmtree(directoryName)

    print(f"Creating and populating {directoryName}")
    os.mkdir(directoryName)

    def ignore_git_directory(src_dir, files):
        # Passed a directory and a list of items in that directory
        # Returns a list of items to EXCLUDE
        if '.git' in files:
            return ['.git']
        else:
            return []
    shutil.copytree('.', directoryName, dirs_exist_ok=True, ignore=ignore_git_directory)



#Need a data structure per lab...
#Where to put the start/end/bonus directories
#Instructions (from the bonus - if there is one) into all of them:


class Lab:
    def __init__(self, labName:str, startTag:str = None, endTag:str = None, bonusTag:str = None):
        self.labName = labName
        self.startTag = startTag if startTag is not None else labName + "-base"
        self.endTag=endTag if endTag is not None else labName + "-completed"
        self.bonusTag=bonusTag if bonusTag is not None else labName + "-completed-bonus"

labList = [
    Lab("Ex01")
    ]

# The lab drectories will be assembled under this
labsBaseDir = r"D:\Customers\Mallon\UpdatingMaterials\2026-cpp\labs-test-directory"

# The directory that the renote repo gets cloned into
repoDir = r"D:\Customers\Mallon\UpdatingMaterials\2026-cpp\labs-test-repo\OrderProcessing"
remoteRepoUrl = "https://github.com/RichardHowells/OrderProcessing.git"

#todo: Convert this to a lambda??
def remove_readonly(func, path, _):
    "Clear the readonly bit and reattempt the removal"
    os.chmod(path, stat.S_IWRITE)
    func(path)

# Clean out the repo directory and then clone from remote
if os.path.isdir(repoDir):
    # The directory is already there - remove it recursively
    print(f"Removing repository directory {repoDir}")
    shutil.rmtree(repoDir, onexc=remove_readonly)

subprocess.run(["git", "clone", remoteRepoUrl, repoDir])



for lab in labList:
    checkoutCode(repoDir, lab.startTag, labsBaseDir + "\\" + lab.labName + "-base")
    checkoutCode(repoDir, lab.endTag, labsBaseDir + "\\" + lab.labName + "-completed")
    checkoutCode(repoDir, lab.bonusTag, labsBaseDir + "\\" + lab.labName + "-completed-bonus")
