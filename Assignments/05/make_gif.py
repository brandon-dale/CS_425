import glob
import os
from PIL import Image

# Set parameters for generation
base_dir = 'imgs'
out_file_path = base_dir + '/Chanelly_Edges'
duration = 1500

# Get the paths sorted
paths = glob.glob(base_dir + '/*.ppm')
paths.sort(key=lambda x: int(os.path.basename(x).split('_')[0]))

# Make the GIF
frames = [Image.open(image) for image in paths]
frame_one = frames[0]
frame_one.save(out_file_path + ".gif", format="GIF", append_images=frames,
            save_all=True, duration=duration, loop=0)
