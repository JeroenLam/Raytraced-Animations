# Raytraced-Animations
A submission for the Computer Graphics course competition

[![](http://img.youtube.com/vi/-m9zLEQgo_c/0.jpg)](http://www.youtube.com/watch?v=-m9zLEQgo_c "")

To create an animation, a python script `genScene.py` is used to create a scene `json` for each frame. In `render.sh`, these scenes are rendered and converted into image files. Then, using `ffmpeg`, the resulting images are concatenated into a video file. Lastly, this video is compressed.

Examples of scenes can be found in the `Scenes` folder.

## Multithreading
The rendering script is currently not multithreaded. However, if the user wants this behaviour, then the user can copy the code from the render script responsible for rendering all scenes in a folder and duplicate it to make `n` new scripts. Then by changing the directory name and manually dividing the scenes over the `n` directories, you can render it `n` times as fast (I recommend to only run 4 to 6 threads if you have a 8 core cpu since it will leave enough room to keep using the computer). We know this solution is not ideal and it can be improved in further iterations.

## TLDR
Install `ffmpeg`. \
Change `genScene.py` to create the desired scenes. \
Run one of the following in the root directory of the project (depending on your OS): \
`python3 genScene.py` \
`./render.sh`
`./renderWindows.sh`

# Credit
The main framework was provided by the University of Groningen during the Computer Graphics course. It was modified by Jeroen Lammers and Joris Peters for the final competition.
The skybox used in the video is a photo from Jeroen made on the Føroyar Islands.
