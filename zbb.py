"""
  /- filename -/
  zblib.py

  /- copyright -/
  Copyright (c) 2014 Alexej Magura

  This file is part of Zelda Battery.

  Zelda Battery is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Zelda Battery is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Zelda Battery.  If not, see <http://www.gnu.org/licenses/>.
"""
from subprocess import getoutput as run;
import re
import sys

_acBlink = False

def onAcPower():
  if sys.platform.startswith('linux'):
    return run('acpi -a').find('on-line') is not -1
  elif sys.platform.startswith('freebsd'):
    return re.search('AC', re.match('.*on-line.*', run('apm')).group()) is not None
  elif sys.platform.startswith('darwin'):
    return re.search('Power', re.match('.*\*.*', re.match('.*AC.*', run('pmset -g ps')))) is not None

def perc_tInt(perc):
  perc = float(perc)
  perc /= 100
  perc *= 10
  perc = int(perc)
  return perc

def powerLvl():
  if sys.platform.startswith('linux'):
    return re.search('([0-9]+)%', run('acpi')).group(1)
  #elif sys.platform.startswith('freebsd'):

def heart(boo, n):
  return [[ bytes('\u2665', 'utf-8').decode('utf-8', 'ignore'), bytes('\u2661', 'utf-8').decode('utf-8', 'ignore') ][~boo]]*n;
