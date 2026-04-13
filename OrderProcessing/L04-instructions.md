## IO formatting

### Display the floating point values in fixed point notation and with two digits after the decimal point

1. The intention is that jsut the results from calling `getStockValue` should be affected
1. (Most) manipulators are sticky so you only need one line of code in the right spot, and an extra `#include'

	### Bonus idea

1. Make the numbers line up in neat columns.  Suggested approach, notice that only variable width items are the integer result (`i * 10`) and teh result of calling `getStockValue`.  Apply a `setw()` manipulator to each of these to regularize theri output widths.