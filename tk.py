#!/usr/bin/python

from tkinter import *

def hello():
    print("hello")


root=Tk()
button=Button(root,text='click me',command=hello)
button.pack()
root.mainloop()
