set title "Comparaison de temps entre les différents Back Track"
set xlabel "taille permutation"
set ylabel "Temps d'exécution"
set xrang [4:11]
set yrange [0:5]
set grid

set terminal postscript eps color enhanced
set output "tempsBT.eps"
set multiplot
plot "time.dat" using 1:2 title 'BF' with linespoints 7, \
"time.dat" using 1:3 title 'BF opt' with linespoints 8
unset multiplot
