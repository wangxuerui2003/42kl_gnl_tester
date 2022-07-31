# import climage
  
# converts the image to print in terminal
# inform of ANSI Escape codes
# output = climage.convert('sean.png')
  
# prints output on console.
# print(output)

# import cv2
# from PIL import Image
# img = cv2.imread("sean.png")
# img = Image.fromarray(img, "RGB")
# img.show()

from PIL import Image
from colorit import init_colorit, background
import time

# init_colorit()
image = Image.open("sean.bmp")
image = image.resize((120, 50))

for y in range(image.size[1]):
    for x in range(image.size[0]):
        print(background(" ", image.getpixel((x,y))), end='')
    time.sleep(0.01)
    print()
