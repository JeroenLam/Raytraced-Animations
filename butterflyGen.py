import math
import random
import colorsys

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
                "texture": "textures/LB.png",
                "ka": 0.2,
                "kd": 0.8,
                "ks": 0.0,
                "n": 1
            }
          }
class butterfly_orb:
    def __init__(self, DT, T, Z, EPS, COL):
        self.dt = DT
        self.t = T
        self.z = Z
        self.eps = EPS
        self.col = [COL[0], COL[1], COL[2]]
        
    def renderNext(self, rho):
        # Compute new points in the X,Y plane
        curve_point = ( math.exp(math.cos(self.t)) - 2 * math.cos(4*self.t) + math.pow(math.sin(self.t/12), 5.0) )
        x = math.sin(self.t) * curve_point
        y = math.cos(self.t) * curve_point
        
        # Increment time step
        self.t = self.t + self.dt
        
        # Move the orb randomly in the z direction
        self.z = self.z + (2*self.eps*random.random() - self.eps)
        
        x = x * 150
        y = y * 150
        z = self.z
        
        # Rotate points around y-axis
        x_bar = x * math.cos(rho) + z * math.sin(rho)
        y_bar = y
        z_bar = z * math.cos(rho) - x * math.sin(rho)
        
        return {
                    "type": "sphere",
                    "position": [x_bar, y_bar, z_bar],
                    "radius": 20,
                    "material":
                    {
                        "color": self.col,
                        "ka": 0.2,
                        "kd": 0.5,
                        "ks": 0.2,
                        "n": 1
                    }
               }
          

scene = dict()
scene["Eye"] = [0, 0, 1000]
scene["MaxRecursionDepth"] = 1
#scene["SuperSamplingFactor"] = 2
scene["Lights"] = [{"position": [-200, 600, 800],
                    "color": [0.5, 0.5, 0.5]},
                   {"position": [400, 600, 800],
                    "color": [0.5, 0.5, 0.5]}]
                    
factor = 200
orb_obj_ar = []
for idx in range(100):
    orb_obj_ar.append(butterfly_orb(1/factor, idx/100*6.25, (random.random() * 400) - 200, 5, colorsys.hsv_to_rgb(random.random(),1,1)))
  

for t in range(6000):
    scene["Objects"] = [sphere_earth(-t)]
    for orb in orb_obj_ar:
        scene["Objects"].append(orb.renderNext(t*math.pi / 90))
    
    my_data_file = open('animation/' + "{:05d}".format(t) + '.j', 'w')
    my_data_file.write(str(scene))
    my_data_file.close()


