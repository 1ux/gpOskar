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
#set xtics 0.00002
set xtics ARG2/10

print "ARG2:", ARG2 #plot [0:0.0002048]
print "ARG3:", ARG3

plot [0:ARG2] [-5:5] ARG1 using ($0/ARG3):1 w l lc rgb 'blue' title 'Kanal 1' smooth sbezier

pause -1
