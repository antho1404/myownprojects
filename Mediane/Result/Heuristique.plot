set title "Resultats de l'Heuristique"
set xlabel "taille des permutations"
set ylabel "medianes non optimales trouvees (en %)"
set xrange [4:12]
set yrange [0:100]
set xtics 4,1,12
set ytics 0,20,100
#set key 9,60
set grid
set terminal postscript eps color enhanced font 'Times-Romant' 24
set output "Heuristique.eps"
set multiplot
plot "Result.dat" using 1:5 title 'medianes non optimales' with linespoints 7
#, \
#"Result.dat" using 1:4 title 'medianes optimales' with linespoints 8
unset multiplot
