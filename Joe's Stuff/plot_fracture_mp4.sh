#! /bin/bash

echo "Lmin, Lmax, color range min, color range max, frame rate"

for file in ./fracture_0*; do


parts=(${file//_/ })
echo  -ne "\r${parts[1]}"


gnuplot << EOF

set output "${parts[1]}.png"
set pm3d map

set format x ""
set format y ""
unset xtics
unset ytics
set xrange [0:$2]
set yrange [0:$1]
set size square
set cbrange [$3:$4]

set term png
splot "$file" with image
EOF

done


ffmpeg -qscale 5 -r $5 -b 9600 -i %05d.png fracture.mp4
#rm *.png
#rm fracture_*
