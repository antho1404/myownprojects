set title "Medianes Parfaites"
set xlabel "taille des permutations"
set ylabel "medianes parfaites existantes (en %)"
set xrange [4:12]
set yrange [0:100]
set xtics 4,1,12
set ytics 0,10,100
set grid
set terminal postscript eps color enhanced font 'Times-Romant' 24
set output "Pourcentage de Medianes Parfaites.eps"

plot "Result.dat" using 1:2 title 'medianes parfaites' with linespoints 7
