import lcm
import time
import numpy as np
from block_goal_msg import block_goal_t

def read_goal(fname):
    transformation = None
    # --- Your code here

    with open(fname, 'r') as f:
        transformation = [[float(num) for num in line.split()] for line in f]
    
    transformation = np.array(transformation)
    transform = np.eye(4)
    transform[0:3, 0:3] = transformation[1:4, 0:3]
    transform[0:3, -1] = transformation[0, :]

    #print(transform)
    # ---
    return transform

def publish_transform(transform):
    # --- Your code here

    lc = lcm.LCM()
    block_goal_msg = block_goal_t()
    block_goal_msg.transform = transform

    lc.publish('BLOCK_GOAL', block_goal_msg.encode())

    # ---

if __name__ == "__main__":
 
    transform = read_goal('inputs1.txt')
    
    
    while True:
        publish_transform(transform)
        time.sleep(0.1)
