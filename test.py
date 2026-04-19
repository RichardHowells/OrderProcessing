import subprocess
import itertools

def identify_highest_numbered_patch_by_version():
    # Given tags with the format major.minor.patch...
    # Picks out the latest patch in each tag, assuming latest == highest patch number

    # Method:
    # Use git tag -l *.*.* to get all the tags
    # Sort descending then pick out the highest numbered x's in eg 5.2.x, and 4.1.x
    # Assumes that major and minor do not exceed 2 digits

    # subprocess' result is in bytes, so convert to a str
    x = subprocess.check_output(['git', 'tag', '-l', '*.*.*']).decode('utf-8') 

    tags = [str(s) for s in x.split()]

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




print("Program start...")
print(identify_highest_numbered_patch_by_version())
print("Program completed")