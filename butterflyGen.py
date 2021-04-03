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

def sphere_mirror(t):
    curve_point = ( math.exp(math.cos(t)) - 2 * math.cos(4*t) + math.pow(math.sin(t/12), 5.0) )
    x = math.sin(t) * curve_point
    y = math.cos(t) * curve_point
    return {
            "type": "sphere",
            "position": [150 * x, 150 * y, 0],
            "radius": 40,
            "material":
            {
                "ka": 0.0,
                "kd": 0.0,
                "ks": 0.9,
                "n": 1
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
                    
factor = 200
for t in range(400):
    scene["Objects"] = [sphere_earth(0), 
                        sphere_mirror( 1 * t / factor), 
                        sphere_mirror( 2 * t / factor), 
                        sphere_mirror( 3 * t / factor), 
                        sphere_mirror( 5 * t / factor), 
                        sphere_mirror( 7 * t / factor), 
                        sphere_mirror(11 * t / factor), 
                        sphere_mirror(13 * t / factor), 
                        sphere_mirror(17 * t / factor), 
                        sphere_mirror(19 * t / factor), 
                        sphere_mirror(23 * t / factor), 
                        sphere_mirror(29 * t / factor), 
                        sphere_mirror(31 * t / factor), 
                        sphere_mirror(37 * t / factor), 
                        sphere_mirror(41 * t / factor), 
                        sphere_mirror(43 * t / factor), 
                        sphere_mirror(47 * t / factor), 
                        sphere_mirror(53 * t / factor), 
                        sphere_mirror(59 * t / factor), 
                        sphere_mirror(61 * t / factor), 
                        sphere_mirror(67 * t / factor), 
                        sphere_mirror(71 * t / factor)]
    my_data_file = open('animation/' + "{:05d}".format(t) + '.j', 'w')
    my_data_file.write(str(scene))
    my_data_file.close()



