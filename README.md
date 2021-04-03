# Raytraced-Animations
A submission for the Computer Graphics course competition

[![](http://img.youtube.com/vi/-m9zLEQgo_c/0.jpg)](http://www.youtube.com/watch?v=-m9zLEQgo_c "")

To create an animation we use a python script `genScene.py` to create a scene `json` for each frame. We can render these into a video using `render.sh`. `render.sh` will convert all frames into images. Then using `ffmpeg` we will combine there images into a video. Lastly we will rerender this video to reduce the file size.

Examples of scenes can be found in the `Scenes` folder.

## Multithreading
The rendering script is currently not multithreaded. However, if the user wants this behaviour, then the user can copy the code from the render script responsible for rendering all scenes in a folder and duplicate it to make `n` new scripts. Then by changing the directory name and manually dividing the scenes over the `n` directories, you can render it `n` times as fast (I recommend to only run 4 to 6 threads if you have a 8 core cpu since it will leave enough room to keep using the computer). We know this solution is not ideal and it can be improved in further iterations.

## TLDR
Install `ffmpeg`. \
Change `genScene.sh` to create the desired scenes. \
Run these in the root directory of the project: \
`python3 genScene.sh` \
`./render.sh`

# Credit
The main framework was provided by the university of Groningen durring hte Computer Graphics course. Some changes where made by Jeroen Lammers and Joris Peters for the competition.
The skybox used in the video is a photo from Jeroen made on the Føroyar Islands.
