set title "Temps du Brute Force"
set xlabel "taille permutation"
set ylabel "temps (s)"
set xrang [5:12]
#set logscale y
set yrange [0:80]
set grid

set terminal postscript eps color enhanced
set output "tempsBF.eps"

plot "BF_non_opt.dat" using 1:2 title 'temps' with linespoints 7
