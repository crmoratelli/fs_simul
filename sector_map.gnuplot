set term png 
set output "sector_map.png"
set border linewidth 0
unset key
unset colorbox
#unset tics
set lmargin screen 0.1
set rmargin screen 0.9
set tmargin screen 0.9
set bmargin screen 0.1
set palette grey
set pm3d map
splot 'log.dat'  matrix with image