function checkoutCode {
	param (
		[string] $repoDir,
		[string] $gitTag,
		[string] $directoryName
		)


	"switching to tags/$gitTag" | Write-Output
	git switch --detach tags/$gitTag

	if (Test-Path $directoryName) {
		"Removing old directory $directoryName" | Write-Output
		Remove-Item -Recurse -Force  $directoryName
	}
	
	New-Item -ItemType Directory -Path $directoryName
	Copy-Item -Recurse -Force -Path .\OrderProcessing -Destination $directoryName\

	#if (Test-Path $directoryName\.git) {
	#	"nuking the .git directory" | Write-Output
	#	Remove-Item -Recurse -Force $directoryName\.git
	#}
}








$mapTagToDirectory = @{ 
	"1.0.0" = "Ex0101-base"
	"2.0.0" = "Ex0101-completed"
	"3.0.1" = "Ex0101-completed-bonus"
	"4.0.0" = "Ex0102-base"
	"5.0.0" = "Ex0102-completed"
	"6.0.0" = "Ex0102-completed-bonus"
}

This is not right yet.  Should work in some safe test Directory
Should do a clone first


foreach($key in $mapTagToDirectory.keys){
	"The value of $key is $($mapTagToDirectory[$key])"

	checkoutCode . $key $($mapTagToDirectory[$key])
}

git switch main

