echo Stress test tp0
for ((i=1;i<100000;i*=10))
{
echo $i entries
./DataGenerator -n $i -d 10 -o TestPoints -I
./DataGenerator -n $i -d 10 -o TestQuery
START=$(date +%s%3N)
./tp0 -p TestPoints -i TestQuery -o TestOut
FINISH=$(date +%s%3N)
((duration=FINISH-START))
printf 'Tardó %f milisegundos\n' "$duration"
}
exit 0
