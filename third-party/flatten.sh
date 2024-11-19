#!/usr/bin/env bash

for dir in */ ; do
	cp -r $dir bkup-$dir
	git rm -f $dir
	mv bkup-$dir $dir
done
