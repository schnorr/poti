Poti 
====

Poti is a library to create trace files in the [Paje file
format](http://paje.sf.net). You should not use it directly during the
tracing of your application (I won't stop you from doing this if you
want). I recommend its use after traces are collected in your
preferred file format (probably binary with memory buffers to avoid at
a maximum the tracing intrusion). Note that *the current version of
Poti does not provide any kind of correctness verification in the
parameters you pass for the library functions*, although we are
working on this to support some error verification with minimal memory
utilization.

Raw textual traces in the Paje file format are hard to be exploited. A
trace replay, in a simplistic simulation environment, is implemented
by [the PajeNG suite](http://github.com/schnorr/pajeng/) through the
`pj_dump` tool. It has an exhaustive set of semantic checks for
verification of the compliance to the Paje file format and model. As
output, the `pj_dump` dumps CSV files that can be easily exploited the
way you want with your preferred programming language.

Clone, Compilation and Installation
-----------------------------------

    git clone git://github.com/schnorr/poti.git
    cd poti
    mkdir build
    cd build
    cmake ..
    make install

Customized Installation
------------

Change the installation directory with:

    cmake -DCMAKE_INSTALL_PREFIX=/your/installation/directory/ ..
    make install

Examples
--------

There are many examples on how to use the poti API. You can execute them:

    ./examples/main_example
    ./examples/states

Roadmap
-------

* Check all function parameters and trace consistency according to the [Paje file format](http://paje.sf.net)
* Use data structures instead of strings for all parameters
* Alias management (get rid of user-generated aliases)