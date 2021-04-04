# Panoramic Raytraced Animations
A submission for the Computer Graphics course competition. Our contribution creates short animated videos using raytracing. We hope to bring back some good memories of our Zernicke campus (Happy Easter). We'd also like to the a beautiful view from a hill on the Faroe islands. Of course, no panorama without flying raytraced geometric objects!

The rendered videos can be found in the `demo` folder or under the following links:
[![](http://img.youtube.com/vi/-m9zLEQgo_c/0.jpg)](http://www.youtube.com/watch?v=-m9zLEQgo_c "")
[![](http://img.youtube.com/vi/tPjY9bbU5_0/0.jpg)](https://www.youtube.com/watch?v=tPjY9bbU5_0 "")

To create an animation, a python script `genScene.py` or `butterflyGen.py` are used to create a scene `json` for each frame. In `render.sh` (or `renderWindows.sh` for Windows), these scenes are rendered and converted into image files. Then, using `ffmpeg`, the resulting images are concatenated into a video file. Lastly, this video is compressed.

Other examples of scenes can be found in the `Scenes` folder.

## Multithreading
The rendering script is currently not multithreaded. However, if the user wants this behaviour, they can copy the code from the render script responsible for rendering all scenes in a folder and duplicate it to make `n` new scripts. Then, by changing the directory name and manually dividing the scenes over the `n` directories, you can render it `n` times as fast (We recommend to only run 4 to 6 threads if you have a 8 core cpu to leave enough room to keep using the computer). We know the current solution is not ideal and it can be improved in further iterations.

## TLDR
Install `ffmpeg` and `cmake` \
Change `genScene.py` or `butterflyGen.py` to create the desired scenes. \
Run the following in the root directory of the project: \
`python3 genScene.py` (Føroyar Islands) or `python3 butterflyGen.py` (Linnaeusborg)\
`./render.sh` or `./renderWindows.sh` (for Windows)

# Credit
The main framework was provided by the University of Groningen during the Computer Graphics course. It was modified by Jeroen Lammers and Joris Peters for the final competition.
The skyboxes used in the videos are photos made by us on the Føroyar Islands and the Linnaeusborg.
