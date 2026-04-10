set datafile separator ","
set terminal pdfcairo font "Arial,12" size 5in,3in
set output 'plots/plot.png'

set title 'Titulo'
set xlabel 'Columna 1'
set ylabel 'Columna 2'
set grid
set key outside

files = system("ls db/*.csv 2>/dev/null")

if (strlen(files) == 0) {
	set label 1 "No hay archivos CSV en db/" at graph 0.5,0.5 center
	unset key
	set xrange [0:1]
	set yrange [0:1]
	unset xtics
	unset ytics
	plot '+' using (0.5):(0.5) with points pt 0 notitle
}
else {
	plot for [f in files] f using 1:2 with lines lw 2 title f
}