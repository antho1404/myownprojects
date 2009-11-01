set output "All_Pattern_taille_29.eps"
set terminal postscript eps color enhanced font 'Times-Romant' 24

set title "Temps pour une permutation de taille 29"
set xlabel "taille pattern"
set ylabel "temps d'execution (s)"
set xrange [3:26]
set yrange [0:50]
set grid

set multiplot
plot "AllPattern.dat" using 1:2 title 'BackTrack' with linespoints 7,\
"AllPattern.dat" using 1:3 title 'Heuristique' with linespoints 8
unset multiplot

set output "All_Pattern_Evolve_time.eps"
set terminal postscript eps color enhanced font 'Times-Romant' 24

set title "Evolution du temps en fonction des pattern avec n = 2x"
set xlabel "taille pattern"
set ylabel "temps d'execution (s)"
set xrange [5:15]
set yrange [0:50]
set grid

set multiplot
plot "AllPattern.dat" using 4:5 title 'BackTrack' with linespoints 7,\
"AllPattern.dat" using 4:6 title 'Heuristique' with linespoints 8
unset multiplot
