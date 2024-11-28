#!/bin/bash
cat /etc/passwd | sed '/^#/d' | sed -n '2~2p' | cut -d ':' -f 1 | rev | sort -r | awk "NR >= $FT_LINE1 && NR <= $FT_LINE2" | paste -sd ', ' - | sed 's/$/./'

