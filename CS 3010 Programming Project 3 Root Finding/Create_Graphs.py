# -*- coding: utf-8 -*-
"""
Created on Tue Nov 15 15:37:40 2022

@author: khale
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from scipy.interpolate import interp1d

BisectionA = pd.read_csv("BisectionA.txt", sep = " ", header=None, names=["Iteration", "Relative Approxomate Error"])
BisectionB = pd.read_csv("BisectionB.txt", sep = " ", header=None, names=["Iteration", "Relative Approxomate Error"])

NewtonA = pd.read_csv("NewtonA.txt", sep = " ", header=None, names=["Iteration", "Relative Approxomate Error"])
NewtonB = pd.read_csv("NewtonB.txt", sep = " ", header=None, names=["Iteration", "Relative Approxomate Error"])

FalseA = pd.read_csv("FalseA.txt", sep = " ", header=None, names=["Iteration", "Relative Approxomate Error"])
FalseB = pd.read_csv("FalseB.txt", sep = " ", header=None, names=["Iteration", "Relative Approxomate Error"])

SecantA = pd.read_csv("SecantA.txt", sep = " ", header=None, names=["Iteration", "Relative Approxomate Error"])
SecantB = pd.read_csv("SecantB.txt", sep = " ", header=None, names=["Iteration", "Relative Approxomate Error"])


axA = BisectionA.plot.line(x="Iteration", y="Relative Approxomate Error", label = "Bisection")
NewtonA.plot.line(ax = axA, x="Iteration", y="Relative Approxomate Error", label = "Newton")
FalseA.plot.line(ax = axA, x="Iteration", y="Relative Approxomate Error", label = "False")
SecantA.plot.line(ax = axA, x="Iteration", y="Relative Approxomate Error", label = "Secant")

plt.legend()
plt.xlabel("Iterations")
plt.ylabel("Relative Approxomate Error")
plt.title("Relatvie Approxomate Error vs Iterations For f(x)=2x^{3}-11.7x^{2}+17.7x-5 Root 1")
plt.show();



# axB = BisectionB.plot.line(x="Iteration", y="Relative Approxomate Error", label = "Bisection")
# NewtonB.plot.line(ax = axB, x="Iteration", y="Relative Approxomate Error", label = "Newton")
# FalseB.plot.line(ax = axB, x="Iteration", y="Relative Approxomate Error", label = "False")
# SecantB.plot.line(ax = axB, x="Iteration", y="Relative Approxomate Error", label = "Secant")


# plt.legend()
# plt.xlabel("Iterations")
# plt.ylabel("Relative Approxomate Error")
# plt.title("Relatvie Approxomate Error vs Iterations For f(x)=x+10-x\cosh(50/x) Root 1")
# plt.show();