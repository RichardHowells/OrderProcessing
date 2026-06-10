from email.mime import base
from genericpath import isfile
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
    os.makedirs(directoryName)                # mkdirs makes any intermediate directories as well

    # Enclosed function.  Directs copytree to ignore the .git directory
    def ignore_git_directory(src_dir, files):
        # Passed a directory and a list of items in that directory
        # Returns a list of items to EXCLUDE
        if '.git' in files:
            return ['.git']
        else:
            return list[str]()
    shutil.copytree(repoDir, directoryName, dirs_exist_ok=True, ignore=ignore_git_directory)

    # Add a file with a versioning annotation
    with open(f'{directoryName}/versiontag.{gitTag}.txt', "w") as version_tag_file:
        version_tag_file.write(f'Extracted from the git repo tag: {gitTag}\n')


def convert_tags_list_to_map(tag_list:list[str]):
    # converts a list of tags, each of the form major.minor.patch
    # (where minor is known to be 1 (exercise start point) or 2 (basic ex end point) or 3 (bonus part end point))
    # to a map of maps m[major][minor] -> patch
    # ASSUMES the tags are sorted NUMERICALLY (not stringwise) ascending. So this captures ONLY the highest patch number
    
    mapped_tags = dict[str, dict[str, str]]()
    for tag in tag_list:
        major, minor, patch = tag.split('.')
        if major not in mapped_tags:
            mapped_tags[major] = dict[str, str]()
        mapped_tags[major][minor] = patch       # Will eventually capture the highest patch number

    return mapped_tags

def tags_as_str(repoDir:str):
    cwd = os.getcwd()
    os.chdir(repoDir)
    tags_as_a_str = str(subprocess.check_output(['git', 'tag', '-l', '*.*.*']).decode('utf-8'))

    os.chdir(cwd)
    return tags_as_a_str

def replace_in_slnx_file(slnx_file_name:str, old_string:str, replacement_string:str):
    if os.path.isfile(slnx_file_name):
        with open(slnx_file_name, "r+") as slnx_file:
            content = slnx_file.read()
            print(f"{old_string=}")
            new_content = content.replace(old_string, replacement_string)
            print(f"{replacement_string=}")
            slnx_file.seek(0, os.SEEK_SET)

            slnx_file.truncate()
            slnx_file.write(new_content)

    return


def moveAndRenameAndAnnotateInstructionsFiles(labName:str, majorVersion:str, baseDir:str, 
                                              completedDir:str, completedBonusDir:str,
                                              bonus_version_git_tag:str):
    # Find and rename the instructions
    # Rename Lnn-instructions.md to Exmm-instructions.md
    if len(majorVersion) == 1:
        majorVersion = "0" + majorVersion

    #If there is an instructions file at the solution level...
    if os.path.isfile(completedBonusDir + "/" + "L" + majorVersion + "-instructions.md"):
        # Rename it to the Exnn-instructions type format
        # if it happens to be in the slnx file then patch that too
        replace_in_slnx_file(completedBonusDir + "/OrderProcessing.slnx", "L" + majorVersion + "-instructions.md", labName + "-instructions.md")
    
    instructions_file_name = labName + "-instructions.md"

    instructions_file_from_repo = completedBonusDir + "/OrderProcessing/" + "L" + majorVersion + "-instructions.md"
    instructions_file_in_lab_directory = completedBonusDir + "/OrderProcessing/" + instructions_file_name
    print(f"{instructions_file_name=}")
    if os.path.isfile(instructions_file_from_repo):
        os.rename(instructions_file_from_repo, instructions_file_in_lab_directory)

        # Append a provenance annotation
        with open(instructions_file_from_repo, "a") as instructions_file:
            instructions_file.write(f'<p align="right">Extracted from the git repo tag: {bonus_version_git_tag}</p>\n')

        #copy to the parent directory
        print("**** Need to inject into the .slnx file")
        shutil.copyfile(instructions_file_in_lab_directory, completedDir + "/" + instructions_file_name)
        #copy to the other versions (base and completed), also into the parent directory
        shutil.copyfile(instructions_file_in_lab_directory, completedDir + "/" + instructions_file_name)
        shutil.copyfile(instructions_file_in_lab_directory, baseDir + "/" + instructions_file_name)
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


import sys
if 'test' in sys.argv:

    rv = convert_tags_list_to_map(['1.0.99', '2.0.3', '2.1.0', '2.2.3'])
    print(f'{rv=}')

else:
    
    # In development I run this as...
    # python3 ./create_lab_folders.py https://github.com/RichardHowells/OrderProcessing.git D:/Customers/Mallon/UpdatingMaterials/2026-cpp/labs-test-repo/OrderProcessing D:/Customers/Mallon/UpdatingMaterials/2026-cpp/labs-test-directory
    # Also works with a local directory as the clone source
    # python3 ./create_lab_folders.py file://D:\Customers\Mallon\UpdatingMaterials\2026-cpp\labs\OrderProcessing D:/Customers/Mallon/UpdatingMaterials/2026-cpp/labs-test-repo/OrderProcessing D:/Customers/Mallon/UpdatingMaterials/2026-cpp/labs-test-directory
    #
    import argparse
    parser = argparse.ArgumentParser(
                    prog='create_lab_folders',
                    description='Checks out the lab code repo.  Creates directories for exercise start point, completed point, and bonus completed point',
                    epilog='')
    parser.add_argument('remoteRepoUrl', default="https://github.com/RichardHowells/OrderProcessing.git")           # Where to get the code from
    parser.add_argument('repoDir', default="D:/Customers/Mallon/UpdatingMaterials/2026-cpp/labs-test-repo/OrderProcessing")                 # Where to clone the code to
    parser.add_argument('labsBaseDir', default="D:/Customers/Mallon/UpdatingMaterials/2026-cpp/labs-test-directory")             # Where to assemble all the lab directories

    args = parser.parse_args()
    print(args.remoteRepoUrl, args.repoDir, args.labsBaseDir)

    # Map the labname to the repo major version
    labList = { "Ex01": "1",
               "Ex02": "2",
               "Ex03": "3",
               "Ex04": "4",
               "Ex05": "5",
               "Ex06": "6",
               "Ex07": "7",
               "Ex08": "8",
               "Ex09": "9",
               "Ex10": "10",
               "Ex11": "11",
               "Ex12": "12",
               }
        

    # The lab directories will be assembled under this
    labsBaseDir = args.labsBaseDir

    # The directory that the remote repo gets cloned into
    repoDir = args.repoDir
    remoteRepoUrl = args.remoteRepoUrl

    def remove_readonly(func, path, _ = None):
        "Enclosed function to clear the readonly bit and reattempt the removal"
        os.chmod(path, stat.S_IWRITE)
        func(path)

    # Clean out the repo directory and then clone from remote
    if os.path.isdir(repoDir):
        # The directory is already there - remove it recursively
        print(f"Removing repository directory {repoDir}")
        #shutil.rmtree(repoDir, onexc=remove_readonly)  # onexc requires 3.12
        shutil.rmtree(repoDir, onerror=remove_readonly)

    subprocess.run(["git", "clone", remoteRepoUrl, repoDir])

    # Get all of the tags in the repo
    taglist = tags_as_str(repoDir).split()

    # Sort the tags using numeric rules rather than text rules
    # Enclosed function to provide the sort key.  
    # Maps (say) 1.2.5 to 01.02.05
    def key_extractor(tag:str):
        parts = tag.split('.')
        # convert the tag parts to two digit numbers
        return f'{int(parts[0]):02d}.{int(parts[1]):02d}.{int(parts[2]):02d}'

    taglist.sort(key=key_extractor)
    #print(f'{taglist=}')

    tagMap = convert_tags_list_to_map(taglist)


    for labName, repoMajorVersion in labList.items():
        checkoutCode(repoDir, f"{repoMajorVersion}.0.{tagMap[repoMajorVersion]['0']}", labsBaseDir + "/" + labName + "-base")
        checkoutCode(repoDir, f"{repoMajorVersion}.1.{tagMap[repoMajorVersion]['1']}", labsBaseDir + "/" + labName + "-completed")
        bonus_version_git_tag = f"{repoMajorVersion}.2.{tagMap[repoMajorVersion]['2']}"
        checkoutCode(repoDir, bonus_version_git_tag, labsBaseDir + "/" + labName + "-completed-bonus")

        # Fix lab instruction files...
        # The final version of the lab instructions ends up in the -completed-bonus directory.
        # Plus the various Lnn-instructions files stack up in all the directories

        # Plus the early labs did this differently

        # Required results...
        #   - identify the right instructions file
        #   - annotate it's provenance
        #   - rename it as labname-instructions.md 
        #   - copy it from the bonus directory to both the other directories
        #   - retain it in the bonus directory as well
        #   - something like Ex01-instructions.md
        #   - delete all the unwanted instructions files

        moveAndRenameAndAnnotateInstructionsFiles(labName, repoMajorVersion, 
                                                  labsBaseDir + "/" + labName + "-base", 
                                                  labsBaseDir + "/" + labName + "-completed", 
                                                  labsBaseDir + "/" + labName + "-completed-bonus",
                                                  bonus_version_git_tag)
