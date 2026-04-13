# Script de gnuplot para los resultados de benchmarks.

set datafile separator ","
set terminal pngcairo font "Arial,12" size 1200,720
set xlabel 'n'
set ylabel 'Tiempo promedio (s)'
set grid
set key outside

set style data lines
set key autotitle columnhead

searchFile = 'db/search_benchmark.csv'
sortFile   = 'db/sort_benchmark.csv'

searchOut = 'plots/search_benchmark.png'
sortOut   = 'plots/sort_benchmark.png'

hasSearch = int(system(sprintf("test -f '%s' && echo 1 || echo 0", searchFile)))
hasSort   = int(system(sprintf("test -f '%s' && echo 1 || echo 0", sortFile)))

if (!hasSearch) {
	print sprintf("ERROR: no existe %s", searchFile)
	exit 1
}
if (!hasSort) {
	print sprintf("ERROR: no existe %s", sortFile)
	exit 1
}

set autoscale
set xtics
set ytics
set key outside

# Search benchmark
set output searchOut
set title 'Search benchmark'
columnCount = int(system(sprintf("awk -F, 'NR==2{print NF; exit}' \"%s\"", searchFile)))
if (columnCount < 2) {
	print sprintf("ERROR: CSV invalido (pocas columnas): %s", searchFile)
	exit 1
} else {
	plot for [col=2:columnCount] searchFile using 1:col lw 2 title columnhead(col)
}
unset output

# Sort benchmark
set output sortOut
set title 'Sort benchmark'
columnCount = int(system(sprintf("awk -F, 'NR==2{print NF; exit}' \"%s\"", sortFile)))
if (columnCount < 2) {
	print sprintf("ERROR: CSV invalido (pocas columnas): %s", sortFile)
	exit 1
} else {
	plot for [col=2:columnCount] sortFile using 1:col lw 2 title columnhead(col)
}
unset output
