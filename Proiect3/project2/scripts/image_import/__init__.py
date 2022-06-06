from functools import reduce
from PIL.Image import open

if __name__ == '__main__':
    while True:
        img_filename = input('Please enter image path: ')
        # print(img_filename)

        try:
            img_arr = open(img_filename).convert('RGB').__array__()
            # Image.fromarray(img_arr).show()
            # Image.fromarray(img_arr).save('../hello.jpg')
            # print(img_arr, img_arr.shape)

            # # apply gray filter
            # for line in image_arr:
            #     for i in range(len(line)):
            #         # print(line[i])
            #         line[i] = np.uint8([sum ( np.uint8(line[i] * [0.2989, 0.5870, 0.1140]) )] * 3)
            #         # print(line[i])
            #         # print()
            # # print(image_arr)

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
            try:
                with open(
                        img_filename.replace(
                            img_filename[img_filename.rfind('.'):],
                            '.txt'),
                        'w') as file:
                    M, N = img_arr.shape[:2]
                    file.write(f'{M} {N}\n')
                    for pixel in reduce(lambda a, b: list(a) + list(b), img_arr):
                        r, b, g = pixel
                        file.write(f'{r} {b} {g}\n')
            except BaseException as e:
                print('ERROR: ', e, 'WHEN WRITING THE .txt FILE')
            break
        except BaseException as e:
            print(f'Couldn\'t find any image at location {img_filename}')

    input('Press Enter to end the program! :)')
