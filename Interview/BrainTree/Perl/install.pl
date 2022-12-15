#!/bin/bash

echo "Installing SQLite DBI"
wget http://search.cpan.org/CPAN/authors/id/T/TI/TIMB/DBI-1.625.tar.gz
tar xvfz DBI-1.625.tar.gz
cd DBI-1.625
perl Makefile.PL
make
make install
echo "Installation Finished"

sudo apt-get install sqlite3 libdbd-sqlite3-perl 
