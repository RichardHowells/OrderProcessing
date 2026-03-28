## Program Organisation

### Namespaces
1. Working in the stockvalue.h/.cpp files; package the function in a nested namespace `mallon::cpp`. 
1. Adjust the code in `main` to call namespaces function.  Try
	1. A fully qualified name
	1. A `using namespace` declaration at the top of the file
1. Move the `getStockValue` function below the `main` function
1. Notice that the code will not compile.  C++ requires that the function is at least declared before use
1. Add a function declaration above `main`
1. Discover that auto cannot work in this case.  Change the function return type to `double` (two places)
1. The program should now run as before
