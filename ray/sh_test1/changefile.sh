#!/bin/bash
a=71
b=41
while(($a<=100))
do
	rm -r file$a
	let "a++"
done
while(($b<=70))
do
	mv file$b newfile$b
	let "b++"
done
