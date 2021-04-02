# Raytraced-Animations
A submission for the Computer Graphics course competition

[![](http://img.youtube.com/vi/-m9zLEQgo_c/0.jpg)](http://www.youtube.com/watch?v=-m9zLEQgo_c "")

To create an animation we use a python script `genScene.py` to create a scene `json` for each frame. We can render these into a video using `render.sh`. `render.sh` will convert all frames into images. Then using `ffmpeg` we will combine there images into a video. Lastly we will rerender this video to reduce the file size.

Examples of scenes can be found in the `Scenes` folder.

## TLDR
Change `genScene.sh` to create the desired scenes. \
Run these in the root directory of the project: \
`python3 genScene.sh` \
`./render.sh`

# Credit
The main framework was provided by the university of Groningen durring hte Computer Graphics course. Some changes where made by Jeroen Lammers and Joris Peters for the competition.
