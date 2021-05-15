Date_interval is a date/time C++ class built using base C++ resources without any libraries, even C++ standard library. As such, it is suitable for embedded systems. The class launches a very fast program and occupies only 7 KB of memory.

All you need are two files, one head file and one .cpp file. Head file, as usual, is set using the keyword 'include':

#include "Date_interval.h"

In the program you initiate an object instantation in the normal way:

Date_interval d; // instantiation of an object 'd' of a type 'Date_interval'

After that, you can use the program options.
For now the program works only with dates. I planned to expand it so that it can work with time.

Program options and references can be found at:

http://mato-cica.github.io/Date_interval/
