# -*- coding: utf-8 -*-
"""
Created on Wed Jul 25 14:39:26 2012

@author: jqnorris
"""


from numpy import *

a = arange(15).reshape(3, 5)

print a

print a.shape

print a.ndim

a.dtype.name

a.itemsize

a.size

type(a)

b = array([6, 7, 8])

b

type(b)

print 7 / 6
# Comment

print "this is something to print"

print "food is very nice"

v = 1

v = v + 1

print v * 5

a = 6
while a > 0:
    print a
    if a > 5:
        print "Big number!"
    elif a % 2 != 0:
        print "This is an odd number"
        print "It isn't greater than five, either"
    else:
        print "this number isn't greater than 5"
        print "nor is it odd"
        print "feeling special?"
    a = a - 1
    print "we just made 'a' one less that what it was!"
    print "and unless a is not greatern that 0, we'll do the loop again."
print "well, it seems as if 'a' is now no bigger than 0!"
print "the loop is now over, and without further adue, so is this program!"


loop = 1

choice = 0

while loop == 1:
    print "Welcome to calculator.py"

    print "your options are:"
    print " "
    print "1) Addition"
    print "2) Subtraction"
    print "3) Multiplication"
    print "4) Division"
    print "5) Quit calulator.py"
    print " "

    choice = input("Choose your option: ")
    if choice == 1:
        add1 = input("Add this: ")
        add2 = input("to this: ")
        print add1, "+", add2, "=", add1 + add2
    elif choice == 2:
        sub2 = input("Subtract this: ")
        sub1 = input("from this: ")
        print sub1, "-", sub2, "=", sub1 - sub2
    elif choice == 3:
        mul1 = input("Multiply this: ")
        mul2 = input("by this: ")
        print mul1, "*", mul2, "=", mul1 * mul2
    elif choice == 4:
        div1 = input("Divide this: ")
        div2 = input("by this: ")
        print div1, "/", div2, "=", div1 / div2
    elif choice == 5:
        loop = 0

print "Thankyou for using calculator.py!"