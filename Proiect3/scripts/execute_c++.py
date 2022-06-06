# import subprocess
#
# # read jpg and print the data:
#
# from PIL import Image
#
# print(subprocess.run(['C:/Windows/System32/where.exe', 'ls'], capture_output=True, text=True).stdout)
#
# # try:
# #     # proc = subprocess.run(['ls'], capture_output=True, text=True)
# #     # print(proc)
# #     cmd = subprocess.run(['C:/Windows/System32/where.exe', 'ls'], capture_output=True, text=True).stdout
# #     ls_response = subprocess.Popen([cmd],  capture_output=True, text=True).stdout
# #
# #     print(ls_response)
# # except:
# #     print("COULDN'T RUN 'ls'")
#
# # with Image.open('./sample.jpg') as im:
# #     im.rotate(45).show()

def to_txt(arr, filename):
    with open(filename, 'w') as file:
        W, H, _ = arr.shape
        file.write(f'{W}, {H}\n')
        for line in arr:
            for r,g,b in line:
                file.write(f'{r} {g} {b}\n')


from PIL import Image
import numpy as np

data = Image.open('./sample.jpg').__array__()
to_txt(data, 'initial.jpg.txt')
