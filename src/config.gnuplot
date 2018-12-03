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
set xlabel "Zeit t in Sekunden" font "Helvetica,14"
set ylabel 'Spannung U in Volt' font "Helvetica,14"
#set size 1,0.5 #Seitenverhältnis ändern
set xtics ARG2/10
set format x '%0.1s\%c'

print "\nlog data output\n--------------\n"
print sprintf("filename(ARG1):\t\t\t%s",ARG1)
print sprintf("timebase(ARG2): \t\t%s\tseconds",ARG2)
print sprintf("samplerate(ARG3) \t\t%s\tsamples/sec", ARG3)
print sprintf("min voltage value(ARG4): \t%s\tvoltage", ARG4)
print sprintf("max voltage value(ARG5): \t%s\tvoltage", ARG5)

stats ARG1

if (ARG6 eq '') {
    plot [0:ARG2] [(ARG4+ARG4*0.1):(ARG5+ARG5*0.1)] ARG1 using ($0/ARG3):1 w l lc rgb '#4466ad' title "Kanal 1" 
    }
else {
    print sprintf("filename2(ARG6):\t\t%s", ARG6)
    plot [0:ARG2] [(ARG4+ARG4*0.1):(ARG5+ARG5*0.1)] ARG1 using ($0/ARG3):1 w l lc rgb '#c94f7c' title 'Kanal 1', ARG6 using ($0/ARG3):1 w l lc rgb '#75ccb9' title 'Kanal 2'
    }

pause -1
