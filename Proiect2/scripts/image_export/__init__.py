"""
This module will input the path to an image's data (text file), and use PIL.Image to convert it to a real image.
"""

from PIL.Image import fromarray

import numpy as np

if __name__ == '__main__':
    while True:
        img_filename = input('Please enter image data path: ')

        # create the array:

        try:
            with open(img_filename, 'r') as file:
                M, N = [int(s) for s in file.readline().split(' ')]
                pixels = []
                for i in range(M * N):
                    line: str
                     try:
                        line = file.readline().split(' ')
                        pixels.append(
                            [int(s) for s in line]
                        )
                    except BaseException as e:
                        continue
                        print(line, 'DOES NOT MATCH A PIXEL WITH 3 COLOR VALUES')
                # print(M, N, pixels)
                as_arr = np.array(pixels)
                img_data = np.reshape(as_arr, (M, N, 3))
                img_data = np.uint8(img_data)
                # print(img_data, img_data.shape)
                img = fromarray(img_data)
                try:
                    img.save(img_filename[:img_filename.rfind('.')] + '.out.png')
                except BaseException as e:
                    print(e, 'WHILE SAVING THE IMAGE')

            # # show the image
            # Image.fromarray(img_arr, 'RGB').show()

            # TODO save the image into the text format:
            '''
            M N
            P1
            P2
            ...
            Pmxn
            '''
            # try:
            #     with open(
            #             img_filename.replace(
            #                 img_filename[img_filename.rfind('.'):],
            #                 '.txt'),
            #             'w') as file:
            #         M, N = img_arr.shape[:2]
            #         file.write(f'{M} {N}\n')
            #         for pixel in reduce(lambda a, b: a + b, img_arr):
            #             r, g, b = pixel
            #             file.write(f'{r} {g} {b} \n')
            # except BaseException as e:
            #     print('ERROR: ', e, 'WHEN WRITING THE .txt FILE')
            break
        except BaseException as e:
            print(f'Couldn\'t find any image at location {img_filename}')

    input('Press Enter to end the program! :)')
