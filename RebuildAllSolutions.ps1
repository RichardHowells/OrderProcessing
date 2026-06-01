#
# rem for /R %%f in (*.sln) do call e:\Course511Dev\VS2008Conv\RebuildSolution.cmd %%f %%~dpf
#
# for /R %%f in (*.sln) do call RebuildSolution.cmd %%f %%~dpf


# Source - https://stackoverflow.com/a/8677658
# Posted by Shay Levy, modified by community. See post 'Timeline' for change history
# Retrieved 2026-05-31, License - CC BY-SA 3.0

# Get-ChildItem -Path . -Filter *.slnx -Exclude *.vs -Recurse -ErrorAction SilentlyContinue -Force | Where-Object  {$_.FullName.Contains('\.vs\') -eq $false } | ForEach-Object { & msbuild.exe "$_" '/t:Rebuild' '/p:Configuration=Debug' '/p:Platform=Any CPU'  }


Get-ChildItem -Path . -Filter *.slnx -Exclude *.vs -Recurse -ErrorAction SilentlyContinue -Force | Where-Object  {$_.FullName.Contains('\.vs\') -eq $false } | ForEach-Object { 

Write-Output ""
Write-Output "----------------------- starting build - $_ -------------------"
Write-Output ""


& msbuild.exe "$_" '/t:Rebuild' '/p:Configuration=Debug' }


