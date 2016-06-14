#!/usr/bin/env sage

# export PATH="/opt/sage/SageMath:$PATH"

import sys
from sage.all import *

def V(r):
  return sqrt(mu/(r+R))

def SMA(r):
  return (r+R)

def SOE(r):
  return ((((V(r))^2)/2) - (mu/(r+R)))

def srh(r):
  return (V(r)*(r+R))

def ecc(r):
  return (0.0)

def DumpValue(x):
  return RealField(128)(x)

def PrintEntry(Alt):
  print 'CircularOrbitData{&%s'%body, ', '
  print DumpValue(Alt), ','
  print DumpValue(V(Alt)), ','
  print DumpValue(SMA(Alt)), ','
  print DumpValue(SOE(Alt)), ','
  print DumpValue(srh(Alt)), ','
  print DumpValue(ecc(Alt)), '}, '

body = 'Kerbin'
mu = 3.5316000e+12
R = 600000
alts = [0.0, 70000, 100000, 2.86333406e+06]

for alt in alts:
  PrintEntry(alt)

body = 'Earth'
mu = 3.986004418e+14
R = 6378136.6
alts = [0.0, 160000, 250000, 3.5786e+07]

for alt in alts:
  PrintEntry(alt)
