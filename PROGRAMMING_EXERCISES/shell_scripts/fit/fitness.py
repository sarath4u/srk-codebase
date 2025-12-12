#!/usr/bin/env python

import argparse
parser = argparse.ArgumentParser(description = 'A fitness app to measure progress')
parser.add_argument('-s', '--squat', action = 'store_true', help='Squats')
parser.add_argument('-d', '--deadlift', action = 'store_true', help='Deadlift')
#parser.add_argument('Start_time', type=int, help='Starting timeset')
#parser.add_argument('T_first', type=int, help='Ending time step if only spacial averging(-s) is chosen')
#parser.add_argument('step', type=int, help='step size')
#parser.add_argument('step', type=int, help='step size')
#parser.add_argument('y_p', type=float, help = 'y+')
#parser.add_argument('N', type=int, help='No of elements')
args = parser.parse_args()

import os
import sys
import math
import datetime


#d1 = datetime.date(2019, 05, 19)
tdy = datetime.date.today()
bw = 65.0
unit = 0.0
#print(d1)
#print(tdy)
wts =[]
reps =[]

if args.squat:
    print("Enter weight and reps in the same order; Press '0 0' to stop")
    while(True):
        x, y = input().split()
        wt = float(x)
        rep = int(y)
        if wt == 0 and rep == 0: break
        wts.append(wt)
        reps.append(rep)
    for i in range(len(reps)):
        unit = unit + reps[i] * (1.0  + wts[i] / bw)**2
    print(unit)
    ans = input("Do you wish to save this data?(y/n)")
    if ans == 'y':
        with open("squat.dat", "a+") as fhandle:
            fhandle.write("%s\t%6f.2\n"%(tdy, unit))

if args.deadlift:
    print("Enter weight and reps in the same order; Press '0 0' to stop")
    while(True):
        x, y = input().split()
        wt = float(x)
        rep = int(y)
        if wt == 0 and rep == 0: break
        wts.append(wt)
        reps.append(rep)
    for i in range(len(reps)):
        unit = unit + reps[i] * (wts[i]/bw)**2
    print(unit)
    ans = input("Do you wish to save this data?(y/n)")
    if ans == 'y':
        with open("deadlift.dat", "a+") as fhandle:
            fhandle.write("%s\t%6.2f\n"%(tdy, unit))
#            os.system(gnuplot plot 'deadlift.dat')    
