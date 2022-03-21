import os
import sys


def from_xlsx_to_dict_list():
    import pandas as pd
    import openpyxl

    df = pd.read_excel('./Grupa 152.xlsx', sheet_name='Grupa 152', skiprows=5 + 1 + 30, usecols='B:F')
    print(df.head(5))

    students = {}

    as_dict = df.to_dict()
    for column in as_dict:
        for student_idx in as_dict[column]:
            if student_idx not in students.keys():
                students[student_idx] = {}
            students[student_idx][column] = as_dict[column][student_idx]
    from pprint import pprint
    pprint(students)

    print(list(students.values()))


def generate_group_folders(output_dir, groups):
    import os


    group_names = groups.keys()

    for group_name in group_names:
        try:
            path = f'{output_dir}/{group_name}'
            if not os.path.exists(path):
                os.mkdir(path)
        except:
            continue

    for group_name, group in zip(group_names, groups.values()):
        dir = f'{output_dir}/{group_name}'
        for name in [student['Numele si prenumele'] for student in group]:
            path = f'{dir}/{name}'
            if not os.path.exists(path):
                os.mkdir(path)


cmakelists_draft = '''cmake_minimum_required(VERSION 3.21)

project(POO)

set(CMAKE_CXX_STANDARD 17)'''


# def generate_CMakeLists_dot_txt(path: str, groups: list[dict]):
#     for group_name,
#     # add_executable(POO ex1_a.cpp)
#     pass


# extract archive()
"""
You need to install patool:

pip install patool
"""
def extract_archive(path):
    import patoolib
    out_dir = path[:path.rfind('.')]
    try:
        patoolib.extract_archive(path, outdir=out_dir)
    except BaseException as e:
        print('ERROR in unzipping:', e)

if __name__ == '__main__':
    from data import grupa_143, grupa_152

    groups = {
        '143': grupa_143,
        '152': grupa_152,
    }

    # generate_group_folders('../Proiect1', groups)
    # generate_CMakeLists_dot_txt('../Proiect1', groups)
    extract_archive(r'D:\UB\POO\Proiect1\143\Cazacu Cristian-Gabriel\problema1_proiect1.rar')
