cd build
cmake ..
make -j4

cd ..


echo "Converting .j -> .json -> .png"
for file in animation/*.j
do
#    echo "$file"
    OUT=$file"son"
    cat $file | tr \' \" > $OUT
    ./build/ray $OUT
    rm $file
    rm $OUT
done

echo "Adding all png files to list"
touch frameList.txt

for file in frams/*.png
do
    echo "file '$file'" >> frameList.txt
done

ffmpeg -f image2 -framerate 60 -i animation/%5d.png -vcodec libx264 -crf 0 video.mp4
ffmpeg -i video.mp4 video-compressed.mp4
rm frameList.txt