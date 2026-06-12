#
# Expects to be in the parent directory above all the Exercise folders
#

Get-ChildItem -Path . -Filter *.slnx -Exclude *.vs -Recurse -ErrorAction SilentlyContinue -Force | Where-Object  {$_.FullName.Contains('\.vs\') -eq $false } | ForEach-Object { 

	Write-Output ""
	Write-Output "----------------------- starting build - $_ -------------------"
	Write-Output ""


	& msbuild.exe "$_" '/t:Rebuild' '/p:Configuration=Debug' 
	}


