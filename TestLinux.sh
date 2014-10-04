#!/bin/bash

>res/results.txt
declare -a val

Appel()
{
echo | ./proglinux $1 $2 >> res/results.txt
}


if test -f data/BOWMAN8.IN2; then
echo Bowman8 >> res/results.txt
val=(20);
for i in 0; do
	echo C = ${val[$i]} >> res/results.txt
	Appel data/BOWMAN8.IN2 ${val[$i]}
done
fi
echo >> res/results.txt


if test -f data/BUXEY.IN2; then
echo Buxey >> res/results.txt
val=(27 30 33 36 41 47 54);
for i in 0 1 2 3 4 5 6 ; do
	echo C = ${val[$i]} >> res/results.txt
	Appel data/BUXEY.IN2 ${val[$i]}
done
fi
echo >> res/results.txt



if test -f data/GUNTHER.IN2; then
echo Gunther >> res/results.txt
val=(41 44 49 54 61 69 81);
for i in 0 1 2 3 4 5 6; do
	echo C = ${val[$i]} >> res/results.txt
	Appel data/GUNTHER.IN2 ${val[$i]}
done
fi
echo >> res/results.txt



if test -f data/HESKIA.IN2; then
echo Heskiaoff >> res/results.txt
val=(138 205 216 256 324 342);
for i in 0 1 2 3 4 5; do
	echo C = ${val[$i]} >> res/results.txt
	Appel data/HESKIA.IN2 ${val[$i]}
done
fi
echo >> res/results.txt



if test -f data/JACKSON.IN2; then
echo Jackson >> res/results.txt
val=(7 9 10 13 14 21);
for i in 0 1 2 3 4 5; do
	echo C = ${val[$i]} >> res/results.txt
	Appel data/JACKSON.IN2 ${val[$i]}
done
fi
echo >> res/results.txt



if test -f data/JAESCHKE.IN2; then
echo Jaeschke >> res/results.txt
val=(6 7 8 10 18);
for i in 0 1 2 3 4; do
	echo C = ${val[$i]} >> res/results.txt
	Appel data/JAESCHKE.IN2 ${val[$i]}
done
fi
echo >> res/results.txt

if test -f data/HAHN.IN2; then
echo Hahn >> res/results.txt
val=(2004 2338 2806 3507 4676);
for i in 0 1 2 3 4; do
echo C = ${val[$i]} >> res/results.txt
Appel data/HAHN.IN2 ${val[$i]}
done
fi
echo >> res/results.txt


if test -f data/KILBRID.IN2; then
echo Kilbridge >> res/results.txt
val=(56 57 62 69 79 92 110 111 138 184);
for i in 0 1 2 3 4 5 6 7 8 9; do
	echo C = ${val[$i]} >> res/results.txt
	Appel data/KILBRID.IN2 ${val[$i]}
done
fi
echo >> res/results.txt


if test -f data/LUTZ1.IN2; then
echo Lutz1 >> res/results.txt
val=(1414 1572 1768 2020 2357 2828);
for i in 0 1 2 3 4 5; do
	echo C = ${val[$i]} >> res/results.txt
	Appel data/LUTZ1.IN2 ${val[$i]}
done
fi
echo >> res/results.txt


if test -f data/LUTZ2.IN2; then
echo Lutz2 >> res/results.txt
val=(11 12 13 14 15 16 17 18 19 20 21);
for i in 0 1 2 3 4 5 6 7 8 9 10; do
echo C = ${val[$i]} >> res/results.txt
Appel data/LUTZ2.IN2 ${val[$i]}
done
fi
echo >> res/results.txt


if test -f data/LUTZ3.IN2; then
echo Lutz3 >> res/results.txt
val=(75 79 83 87 92 97 103 110 118 127 137 150);
for i in 0 1 2 3 4 5 6 7 8 9 10 11; do
echo C = ${val[$i]} >> res/results.txt
Appel data/LUTZ3.IN2 ${val[$i]}
done
fi
echo >> res/results.txt



if test -f data/MANSOOR.IN2; then
echo Mansoor >> res/results.txt
val=(48 62 94);
for i in 0 1 2; do
	echo C = ${val[$i]} >> res/results.txt
	Appel data/MANSOOR.IN2 ${val[$i]}
done
fi
echo >> res/results.txt



if test -f data/MERTENS.IN2; then
echo Mertens >> res/results.txt
val=(6 7 8 10 15 18);
for i in 0 1 2 3 4 5; do
	echo C = ${val[$i]} >> res/results.txt
	Appel data/MERTENS.IN2 ${val[$i]}
done
fi
echo >> res/results.txt


if test -f data/MITCHELL.IN2; then
echo Mitchell >> res/results.txt
val=(14 15 21 26 35 39);
for i in 0 1 2 3 4 5; do
	echo C = ${val[$i]} >> res/results.txt
	Appel data/MITCHELL.IN2 ${val[$i]}
done
fi
echo >> res/results.txt



if test -f data/ROSZIEG.IN2; then
echo Roszieg >> res/results.txt
val=(14 16 18 21 25 32);
for i in 0 1 2 3 4 5; do
	echo C = ${val[$i]} >> res/results.txt
	Appel data/ROSZIEG.IN2 ${val[$i]}
done
fi
echo >> res/results.txt



if test -f data/SAWYER30.IN2; then
echo Sawyer30 >> res/results.txt
val=(25 27 30 33 36 41 47 54 75);
for i in 0 1 2 3 4 5 6 7 8; do
	echo C = ${val[$i]} >> res/results.txt
	Appel data/SAWYER30.IN2 ${val[$i]}
done
fi
echo >> res/results.txt



if test -f data/TONGE70.IN2; then
echo Tonge70 >> res/results.txt
val=(160 168 176 185 195 207 220 234 251 270 293 320 364 410 468 527);
for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15; do
echo C = ${val[$i]} >> res/results.txt
Appel data/TONGE70.IN2 ${val[$i]}
done
fi
echo >> res/results.txt



if test -f data/WARNECKE.IN2; then
echo Warnecke >> res/results.txt
val=(54 56 58 60 62 65 68 71 74 78 82 86 92 97 104 111);
for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15; do
echo C = ${val[$i]} >> res/results.txt
Appel data/WARNECKE.IN2 ${val[$i]}
done
fi
echo >> res/results.txt



if test -f data/WEE-MAG.IN2; then
echo Wee-mag >> res/results.txt
val=(28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 45 46 47 49 50 52 54 56);
for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23; do
echo C = ${val[$i]} >> res/results.txt
Appel data/WEE-MAG.IN2 ${val[$i]}
done
fi
echo >> res/results.txt



if test -f data/SCHOLL.IN2; then
echo Scholl >> res/results.txt
val=(1394 1422 1452 1483 1515 1548 1584 1620 1659 1699 1742 1787 1834 1883 1935 1991 2049 2111 2177 2247 2322 2402 2488 2580 2680 2787);
for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25; do
echo C = ${val[$i]} >> res/results.txt
Appel data/SCHOLL.IN2 ${val[$i]}
done
fi
echo >> res/results.txt


if test -f data/ARC83.IN2; then
echo Arc83 >> res/results.txt
val=(3786 3985 4206 4454 4732 5048 5408 5824 5853 6309 6842 6883 7571 8412 8898 10816);
for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15; do
echo C = ${val[$i]} >> res/results.txt
Appel data/ARC83.IN2 ${val[$i]}
done
fi
echo >> res/results.txt


if test -f data/ARC111.IN2; then
echo Arc111 >> res/results.txt
val=(5755 5785 6016 6267 6540 6837 7162 7520 7916 8356 8847 9400 10027 10743 11378 11570 17067);
for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16; do
echo C = ${val[$i]} >> res/results.txt
Appel data/ARC111.IN2 ${val[$i]}
done
fi
echo >> res/results.txt


if test -f data/BARTHOLD.IN2; then
echo Barthold >> res/results.txt
val=(403 434 470 513 564 626 705 805);
for i in 0 1 2 3 4 5 6 7; do
echo C = ${val[$i]} >> res/results.txt
Appel data/BARTHOLD.IN2 ${val[$i]}
done
fi
echo >> res/results.txt


if test -f data/BARTHOL2.IN2; then
echo Barthol2 >> res/results.txt
val=(84 85 87 89 91 93 95 97 99 101 104 106 109 112 115 118 121 125 129 133 137 142 146 152 157 163 170);
for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25; do
echo C = ${val[$i]} >> res/results.txt
Appel data/BARTHOL2.IN2 ${val[$i]}
done
fi
echo >> res/results.txt


if test -f data/Mukherje.IN2; then
echo Mukherje >> res/results.txt
val=(176 183 192 201 211 222 234 248 263 281 301 324 351);
for i in 0 1 2 3 4 5 6 7 8 9 10 11 12; do
echo C = ${val[$i]} >> res/results.txt
Appel data/Mukherje.IN2 ${val[$i]}
done
fi
echo >> res/results.txt


