import math

def sphere_earth(t):
    return {
            "type": "sphere",
            "comment": "Earth sphere",
            "position": [0, 0, 0],
            "radius": 1100,
            "rotation": [0, 1, 0],
            "angle": t,
            "material":
            {
                "texture": "textures/Faroer.png",
                "ka": 0.2,
                "kd": 0.8,
                "ks": 0.0,
                "n": 1
            }
          }
          
def sphere_green(t):
    return {
            "type": "sphere",
            "position": [150*math.sin(t), math.cos(t)*250, 300],
            "radius": 40,
            "material":
            {
                "color": [0.0, 1.0, 0.0],
                "ka": 0.2,
                "kd": 0.7,
                "ks": 0.5,
                "n": 64
            }
          }
          
def sphere_red(t):
    return {
            "type": "sphere",
            "comment": "matt red",
            "position": [50*math.cos(t), 150*math.sin(t), 250],
            "radius": 50,
            "material":
            {
                "color": [1.0, 0.0, 0.0],
                "ka": 0.0,
                "kd": 0.6,
                "ks": 0.5,
                "n": 1
            }
          }
          
def sphere_mirror(t):
    return {
            "type": "sphere",
            "comment": "Mirror sphere",
            "position": [200*math.sin(t), 80*math.sin(2*t), 200*math.cos(t)],
            "radius": 80,
            "material":
            {
                "ka": 0.0,
                "kd": 0.0,
                "ks": 0.9,
                "n": 1
            }
          }
          
def sphere_trans(t):
    return {
            "type": "sphere",
            "comment": "Transparent sphere",
            "position": [300*math.cos(t), 250*math.sin(3*t), 400*math.sin(2*t)],
            "radius": 80,
            "material":
            {
                "color": [1.0, 1.0, 1.0],
                "ka": 0.0,
                "kd": 0.0,
                "ks": 0.0,
                "n": 16,
                "isTransparent": 'true',
                "nt": 1.30
            }
          }  
          
def cube_trans(t):
    return {
            "type": "mesh",
            "filename": "models/cube.obj",
            "position": [0, 0, 0],
            "rotation": [math.sin(3*t), math.cos(3*t), math.sin(2*t)],
            "scale": [50.0, 50.0, 50.0],
            "material":
            {
                "color": [1.0, 1.0, 1.0],
                "ka": 0.0,
                "kd": 0.0,
                "ks": 0.0,
                "n": 16,
                "isTransparent": 'true',
                "nt": 1.30
            }
          } 

scene = dict()
scene["Eye"] = [0, 0, 1000]
scene["MaxRecursionDepth"] = 3
#scene["SuperSamplingFactor"] = 2
scene["Lights"] = [{"position": [-200, 600, 800],
                    "color": [0.5, 0.5, 0.5]},
                   {"position": [400, 600, 800],
                    "color": [0.5, 0.5, 0.5]}]
                    
for idx in range(60):
    scene["Objects"] = [sphere_earth(idx), 
                        sphere_green(idx/360 * math.pi), 
                        sphere_red(idx/360 * math.pi), 
                        sphere_mirror(idx/360 * math.pi), 
                        sphere_trans(idx/360 * math.pi), 
                        cube_trans(idx/360 * math.pi)]
    my_data_file = open('animation/' + "{:05d}".format(idx) + '.j', 'w')
    my_data_file.write(str(scene))
    my_data_file.close()



