#!/usr/bin/env sage

# export PATH="/opt/sage/SageMath:$PATH"

import sys
from sage.all import *

def V(r, r2):
  return sqrt(mu*((2/(r+R))-(2/(r+r2+2*R))))

def SMA(r, r2):
  return (((r+R)+(r2+R))/2.0)

def SOE(r, r2):
  return (-mu/((r+R)+(r2+R)))

def srh(r, r2):
  return (V(r, r2)*(r+R))

def ecc(r, r2):
  return (((r2 + R) - (r + R)) / ((r2 + R) + (r + R)))

def DumpValue(x):
  return RealField(128)(x)

def PrintEntry(Alt, Ap):
  print 'EllipticalOrbitData{&%s'%body, ', '
  print DumpValue(Alt), ','
  print DumpValue(V(Alt, Ap)), ','
  print DumpValue(Ap), ','
  print DumpValue(SMA(Alt, Ap)), ','
  print DumpValue(SOE(Alt, Ap)), ','
  print DumpValue(srh(Alt, Ap)), ','
  print DumpValue(ecc(Alt, Ap)), '}, '

def PrintSweep(x):
  for ialt in range(len(x)):
    for jalt in range(ialt, len(x)):
      PrintEntry(x[ialt], x[jalt])

body = 'Kerbin'
mu = 3.5316000e+12
R = 600000
alts = [0.0, 70000, 100000, 2.86333406e+06]

PrintSweep(alts)

print ''

body = 'Earth'
mu = 3.986004418e+14
R = 6378136.6
alts = [0.0, 160000, 250000, 3.5786e+07]

PrintSweep(alts)
