from email.mime import base
import os, stat
import shutil
import subprocess
import itertools

def checkoutCode(repoDir:str, gitTag:str, directoryName:str):
    print(f"switching to tags/{gitTag}")

    # Grab the cwd, switch to the repo dir, because git switch has to be in that dir
    # then switch the cwd back
    currentWorkingDir = os.getcwd()

    os.chdir(repoDir)
    
    print(f"git switch to tags/{gitTag}")
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
    shutil.copytree(repoDir, directoryName, dirs_exist_ok=True, ignore=ignore_git_directory)


def identify_highest_numbered_patch_by_version(tags_as_string:str):
    # Given tags with the format major.minor.patch...
    # Picks out the latest patch in each tag, assuming latest == highest patch number
    # Returns a list of major.minor.patch numbers, in descending order
    # Method:

    tags = [str(s) for s in tags_as_string.split()]

    tags.sort()
    tags.reverse()

    def key_extractor(tag:str):
        parts = tag.split('.')
        # convert the two senior parts to two character numbers
        return f'{int(parts[0]):02d}.{int(parts[1]):02d}'

    return_value:list[str] = []
    for _, group in itertools.groupby(tags, key_extractor):
        # You can only pass over the iterator g once!
        highest_patch_for_this_version = next(iter(group))
        return_value.append(highest_patch_for_this_version)

    return return_value

def convert_tags_list_to_map(tag_list:list[str]):
    # converts a list of tags, each of the form major.minor.patch
    # (where minor is known to be 1 (exercise start point) or 2 (basic ex end point) or 3 (bonus part end point))
    # to a map of maps m[major][minor] -> patch
    
    mapped_tags = dict[str, dict[str, str]]()
    for tag in tag_list:
        major, minor, patch = tag.split('.')
        if major not in mapped_tags:
            mapped_tags[major] = dict[str, str]()
        mapped_tags[major][minor] = patch

    return mapped_tags

import os
def tags_as_str(repoDir:str):
    cwd = os.getcwd()
    os.chdir(repoDir)
    tags_as_a_str = str(subprocess.check_output(['git', 'tag', '-l', '*.*.*']).decode('utf-8'))

    os.chdir(cwd)
    return tags_as_a_str

def moveAndRenameInstructionsFiles(labName:str, majorVersion:str, baseDir:str, completedDir:str, completedBonusDir:str):
    # Find and rename the instructions
    # Rename Lnn-instructions.md to Exmm-instructions.md
    if len(majorVersion) == 1:
        majorVersion = "0" + majorVersion
    
    instructions_file_name = labName + "-instructions.md"
    print(f"{instructions_file_name=}")
    if os.path.isfile(completedBonusDir + "/OrderProcessing/" + "L" + majorVersion + "-instructions.md"):
        os.rename(completedBonusDir + "/OrderProcessing/" + "L" + majorVersion + "-instructions.md", completedBonusDir + "/OrderProcessing/" + instructions_file_name)

        #copy to the other directories
        shutil.copyfile(completedBonusDir + "/OrderProcessing/" + instructions_file_name, completedDir + "/OrderProcessing/" + instructions_file_name)
        shutil.copyfile(completedBonusDir + "/OrderProcessing/" + instructions_file_name, baseDir + "/OrderProcessing/" + instructions_file_name)
    else:
        print(f"Try the older style naming... looking in {completedBonusDir=}")
        if os.path.isfile(completedBonusDir + "/OrderProcessing/" + "instructions.md"):
            os.rename(completedBonusDir + "/OrderProcessing/" + "instructions.md", completedBonusDir + "/OrderProcessing/" + instructions_file_name)

            #copy to the other directories
            shutil.copyfile(completedBonusDir + "/OrderProcessing/" + instructions_file_name, completedDir + "/OrderProcessing/" + instructions_file_name)
            shutil.copyfile(completedBonusDir + "/OrderProcessing/" + instructions_file_name, baseDir + "/OrderProcessing/" + instructions_file_name)
        else:
            raise Exception(f"Cannot find the instructions file. {labName=} {majorVersion=} {completedBonusDir=}")

    print("delete unwanted instructions files...")
    import pathlib
    for dir in (completedBonusDir, completedDir, baseDir):
        dir += "/OrderProcessing"
        print(f"Looking in {dir=}")
        for p in pathlib.Path(dir).glob("L*-instructions.md"):
            print(f"Removing {p}")
            p.unlink()


#Need a data structure per lab...
#Where to put the start/end/bonus directories
#Instructions (from the bonus - if there is one) into all of them:


# class Lab:
#     def __init__(self, labName:str, startTag:str = None, endTag:str = None, bonusTag:str = None):
#         self.labName = labName
#         self.startTag = startTag if startTag is not None else labName + "-base"
#         self.endTag=endTag if endTag is not None else labName + "-completed"
#         self.bonusTag=bonusTag if bonusTag is not None else labName + "-completed-bonus"

class Lab:
    def __init__(self, labName:str, labMajorVersion, tagMap:dict[str:dict[str,str]]):
        self.labName = labName
        self.startTag = startTag if startTag is not None else labName + "-base"
        self.endTag=endTag if endTag is not None else labName + "-completed"
        self.bonusTag=bonusTag if bonusTag is not None else labName + "-completed-bonus"



import sys
if 'test' in sys.argv:
    # Run tests
    rv = identify_highest_numbered_patch_by_version("1.0.0 1.0.1 2.3.0 2.4.5")
    print(f'{rv=}')

    rv = convert_tags_list_to_map(['1.0.99', '2.0.3', '2.1.0', '2.2.3'])
    print(f'{rv=}')

else:
       
    # import argparse
    # parser = argparse.ArgumentParser(
    #                 prog='ProgramName',
    #                 description='What the program does',
    #                 epilog='Text at the bottom of help')
    # parser.add_argument('filename')           # positional argument
    # parser.add_argument('-c', '--count')      # option that takes a value
    # parser.add_argument('-v', '--verbose',
    #                 action='store_true')
    # args = parser.parse_args()
    # print(args.filename, args.count, args.verbose)

    # Map the labname to the repo major version
    labList = { "Ex01": "1" #,
               # "Ex02": "2",
               # "Ex03": "3",
               # "Ex04": "4"
               }
        

    # The lab directories will be assembled under this
    labsBaseDir = r"D:/Customers/Mallon/UpdatingMaterials/2026-cpp/labs-test-directory"

    # The directory that the remote repo gets cloned into
    repoDir = r"D:/Customers/Mallon/UpdatingMaterials/2026-cpp/labs-test-repo/OrderProcessing"
    remoteRepoUrl = "https://github.com/RichardHowells/OrderProcessing.git"

    def remove_readonly(func, path, _):
        "Enclosed function to clear the readonly bit and reattempt the removal"
        os.chmod(path, stat.S_IWRITE)
        func(path)

    # Clean out the repo directory and then clone from remote
    if os.path.isdir(repoDir):
        # The directory is already there - remove it recursively
        print(f"Removing repository directory {repoDir}")
        shutil.rmtree(repoDir, onexc=remove_readonly)

    subprocess.run(["git", "clone", remoteRepoUrl, repoDir])

    # Get all of the tags in the repo
    taglist = tags_as_str(repoDir).split()

    tagMap = convert_tags_list_to_map(taglist)


    for labName, repoMajorVersion in labList.items():
        checkoutCode(repoDir, f"{repoMajorVersion}.0.{tagMap[repoMajorVersion]["0"]}", labsBaseDir + "/" + labName + "-base")
        checkoutCode(repoDir, f"{repoMajorVersion}.1.{tagMap[repoMajorVersion]["1"]}", labsBaseDir + "/" + labName + "-completed")
        checkoutCode(repoDir, f"{repoMajorVersion}.2.{tagMap[repoMajorVersion]["2"]}", labsBaseDir + "/" + labName + "-completed-bonus")

        # Fix lab instruction files...
        # The final version of the lab instructions ends up in the -completed-bonus directory.
        # Plus the various Lnn-instructions files stack up in all the directories

        # Plus the early labs did this differently

        # Required results...
        #   - copy the right instructions file, renamed as labname-instructions.md from the bonus directory to both the other directories
        #   - retain it in the bonus directory as well
        #   - something like Ex01-instructions.md
        #   - delete all the unwanted instructions files
        moveAndRenameInstructionsFiles(labName, repoMajorVersion, labsBaseDir + "/" + labName + "-base", labsBaseDir + "/" + labName + "-completed", labsBaseDir + "/" + labName + "-completed-bonus")
