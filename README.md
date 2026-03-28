# OrderProcessing



## Starting a new lab

For each new lab I want to try starting with a delete of the `instructions.md` followed by creating an empty one.  I think it will help with evading merge conflicts in the rebase part of a hotfix.  Try it!


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
```