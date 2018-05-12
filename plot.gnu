set yrange [273:373]
set xrange [0:600]

plot "out.dat" using 1:3 title 'Set Point' with lines,\
	"out.dat" using 1:2 title 'Load' with lines,\
     "out.dat" u ($1):($4 + 273) title 'Amps' with lines

pause -1 "return to reread"
reread