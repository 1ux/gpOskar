#!/usr/bin/gnuplot
#
# Autor: Michael Krause
#
#========================================
#Presentaion-Script for DSO_2090 raw data
#========================================

set terminal wxt size 800, 600
set key font ",14"
set grid xtics ytics
set xlabel 'Zeit t in ...' font "Helvetica,14"
set ylabel 'Spannung U in Volt' font "Helvetica,14"
#set size 1,0.5 #Seitenverhältnis ändern
set xtics ARG2/10

print "filename(ARG1):\t\t\t", ARG1
print "timebase(ARG2) \t in s:\t\t",ARG2 
print "samplerate(ARG3) in S/s:\t", ARG3
print "min voltage valure: \t\t", ARG4
print "max voltage valure: \t\t", ARG5
print "filename2(ARG6):\t\t", ARG6

plot [0:ARG2] [ARG4:ARG5] ARG1 using ($0/ARG3):1 w l lc rgb 'blue' title 'Kanal 1' smooth sbezier, ARG6 using ($0/ARG3):1 w l lc rgb 'green' title 'Kanal 2' 

pause -1
