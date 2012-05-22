#! /bin/bash

##list='rs232 CImg.PlugIn  CImg.Tool CImg'
list='rs232'
#move code versions to temporary directory
for d in $list
do
  mkdir -p ../DoxIt.tmp/$d
  mv ../$d/*.v?.?.?.* ../DoxIt.tmp/$d
done
#get rs232 help output (xterm-color unformated)
dir=../rs232
for fb in get put
do
  bin=$dir/$fb
  out=serial_$fb.help
  $bin -h 2> $dir/$out; cat -v $dir/$out | sed 's/\^\[\[//g' | sed 's/1m//g' | sed 's/0;0;0m//g' | sed 's/0;35;59m//g' | sed 's/0;32;59m//g' | sed 's/4;31;59m//g' > $dir/$out.output;rm $dir/$out
done
#create documentation
cat rs232.Doxygen | sed 's/\ VERSION/\ '`cat VERSION`'/g' > rs232.Doxygen.version
doxygen rs232.Doxygen.version
rm rs232.Doxygen.version
#put back code versions
for d in $list
do
  mv ../DoxIt.tmp/$d/* ../$d/
  rmdir ../DoxIt.tmp/$d
done
rmdir ../DoxIt.tmp

