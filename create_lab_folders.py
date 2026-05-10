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

def tags_as_str(repoDir:str):
    cwd = os.getcwd()
    os.chdir(repoDir)
    tags_as_a_str = str(subprocess.check_output(['git', 'tag', '-l', '*.*.*']).decode('utf-8'))

    os.chdir(cwd)
    return tags_as_a_str

def moveAndRenameAndAnnotateInstructionsFiles(labName:str, majorVersion:str, baseDir:str, 
                                              completedDir:str, completedBonusDir:str,
                                              bonus_version_git_tag:str):
    # Find and rename the instructions
    # Rename Lnn-instructions.md to Exmm-instructions.md
    if len(majorVersion) == 1:
        majorVersion = "0" + majorVersion
    
    instructions_file_name = labName + "-instructions.md"
    instructions_file_from_repo = completedBonusDir + "/OrderProcessing/" + "L" + majorVersion + "-instructions.md"
    instructions_file_in_lab_directory = completedBonusDir + "/OrderProcessing/" + instructions_file_name
    print(f"{instructions_file_name=}")
    if os.path.isfile(instructions_file_from_repo):
        os.rename(instructions_file_from_repo, instructions_file_in_lab_directory)

        # Append a provenance annotation
        with open(instructions_file_in_lab_directory, "a") as instructions_file:
            instructions_file.write(f'<p align="right">Extracted from the git repo tag: {bonus_version_git_tag}</p>\n')

        #copy to the other directories
        shutil.copyfile(instructions_file_in_lab_directory, completedDir + "/OrderProcessing/" + instructions_file_name)
        shutil.copyfile(instructions_file_in_lab_directory, baseDir + "/OrderProcessing/" + instructions_file_name)
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
    # Run tests
    rv = identify_highest_numbered_patch_by_version("1.0.0 1.0.1 2.3.0 2.4.5")
    print(f'{rv=}')

    rv = convert_tags_list_to_map(['1.0.99', '2.0.3', '2.1.0', '2.2.3'])
    print(f'{rv=}')

else:
    
    # In development I run this as...
    # python3 ./create_lab_folders.py https://github.com/RichardHowells/OrderProcessing.git D:/Customers/Mallon/UpdatingMaterials/2026-cpp/labs-test-repo/OrderProcessing D:/Customers/Mallon/UpdatingMaterials/2026-cpp/labs-test-directory
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
