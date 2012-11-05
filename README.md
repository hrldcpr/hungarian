This module is just a simple wrapper for a C++ implementation of Knuth's Hungarian algorithm, a.k.a. Munkres' algorithm, for the linear assignment problem.

**It has not been updated since 2008, so may need some changes &mdash; pull requests are welcome!**

Note that this module depends on the numpy module. You must install numpy before you can compile this module. Numpy can be downloaded from http://numpy.scipy.org

If you have any problems with this module, you should contact me, not Mr. Battre.


To build this module run:

    > python setup.py build

Then you can either put the file build/lib-<YOUR-PLATFORM>/hungarian.so in the same directory as the code that will be using it, or you can install it so that all of your python programs can see it:

    > python setup.py install

For the module's documentation, type at a Python prompt:

    >>> help('hungarian')


Additional Information:

This wrapper for the algorithm uses double precision (i.e. 64-bit) floating point arithmetic. To change it to single precision, integer, or anything else, simply change the corresponding types in asp.h
