# OrderProcessing



## Starting a new lab

(no longer valid - abandoned after Lab3) For each new lab we shold start with a delete of the `instructions.md` followed by creating an empty one.  There will still be a merge conflict with it after a hotfix merge/rebase.  Merge conflicts are a fact of life!

For each new lab create a new `Lnn-instructions.md` file - ie `L03-instructions.md`.  It turned out to be FAR too painful handling the unnecessary merge conflicts caused by delete/recreate of the `instructions.md` file.

`L03-instructions.md` is the first to use this convention. A whole set of `Lnn-instructions.md` files will build up towards the end of the labs.

The powershell script that creates actual lab directories needs to handle the different naming conventions

## How to handle a 'hotfix'

branch from the release tag ie (probably)
```
git checkout -b hotfix/2.3.1 tags/2.3.0

## do the work

git checkout master

git rebase -i tags/2.3.0
## edit to stop immediately

git merge hotfix/2.3.1

git rebase --continue
## might have to fix merge conflicts
git tag 2.3.1

# git push --tags origin master
git branch -d hotfix/2.3.1

## If there was a `feature/x.x.x` branch in progress at the time then it needs to be rebased on the new `main`

git switch feature/x.x.x
git rebase main
```