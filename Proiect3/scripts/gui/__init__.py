import tkinter as tk


def show_entry_fields():
    print("First Name: %s\nLast Name: %s" % (e1.get(), e2.get()))


master = tk.Tk()
tk.Label(master,
         text="Input Image File").grid(row=0)
tk.Label(master,
         text="Output Text File").grid(row=1)

# add the input entry, and a click handler
from tkinter import filedialog as fd

e1: tk.Label
e1_var: tk.StringVar
e2_var: tk.StringVar


def choose_file(e):
    filename: str = fd.askopenfilename()
    global e1_var, e2_var
    if not filename:
        e1_var.set("Choose Image File")
        return

    e1_var.set(filename)
    txt_filename = filename[:filename.rfind('.')] + '.txt'
    e2_var.set(txt_filename)


e1_var = tk.StringVar()
e1_var.set("Choose Image File")
e1 = tk.Button(master, {'bg': 'whitesmoke'}, textvariable=e1_var)
e1.bind("<Button-1>", choose_file)

e2_var = tk.StringVar()
e2_var.set('Output File')
e2 = tk.Entry(master, textvariable=e2_var)
# e2.pack(side='left', fill='x', expand=True)

e1.grid(row=0, column=1)
e2.grid(row=1, column=1)

tk.Button(master,
          text='Quit',
          command=master.quit).grid(row=3,
                                    column=0,
                                    sticky=tk.W,
                                    pady=4)
tk.Button(master,
          text='Show', command=show_entry_fields).grid(row=3,
                                                       column=1,
                                                       sticky=tk.W,
                                                       pady=4)
master.geometry('600x400')
tk.mainloop()

# import tkinter as tk
# from tkinter import filedialog as fd
#
#
# def callback():
#     name = fd.askopenfilename()
#     print(name)
#
#
# errmsg = 'Error!'
# tk.Button(text='Click to Open File',
#           command=callback).pack(fill=tk.X)
# tk.mainloop()

# import tkinter as tk
#
#
# class Main(tk.Tk):
#     def __init__(self):
#         tk.Tk.__init__(self)
#         # the string variable
#         self.fin = tk.StringVar()
#         self.fin.set('')
#         #BUTTONS
#         tk.Button(self, text='Quit', command=self.destroy).pack()
#         tk.Button(self, text='+', command=self.plus_one).pack()
#         tk.Button(self, text='-', command=self.take_one).pack()
#         #ENTRY
#         self.fin_entry = tk.Entry(self, textvariable=str(self.fin), justify="center", width=4)
#         self.fin_entry.pack()
#
#     def plus_one(self):
#         x =  self.fin.get() + '+'
#         self.fin.set(x)
#
#     def take_one(self):
#         x =  self.fin.get()[:-1]
#         self.fin.set(x)
#
# app = Main()
# app.mainloop()
