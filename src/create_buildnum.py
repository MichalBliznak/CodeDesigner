#! /usr/bin/env python

import string

# read build number from file if exists
try:
	infile = open("BuildNum.h", "r")
	num = int(string.replace(infile.readline(), "#define udvBUILD_NUMBER ", ""))
	svnnum = infile.readline();
	infile.close()
except:
	num = 0
	svnnum = '#define udvSVN_REVISION wxT("$Rev: $")'

#read svn revision number
# try:
	#infile = open("../.svn/entries", "r")
	# go to 4th line
	#infile.readline()
	#infile.readline()
	#infile.readline()
	# read the svn revision
	#svnrev = infile.readline()
	#infile.close()
#except:
	#svnrev = "unknown"

# increase the build number
num +=1

# save modified build number
outfile = open("BuildNum.h", "w")
outfile.write("#define udvBUILD_NUMBER " + str(num) + "\n")
outfile.write(svnnum + "\n")
#outfile.write("#define udvSVN_REVISION " + svnrev + "\n")
outfile.close()
