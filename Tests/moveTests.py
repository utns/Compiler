import os
import sys

moveTestNum = int(sys.argv[1])
testsCount = int(sys.argv[2])
for i in range(testsCount, moveTestNum - 1, -1):
      testNum = 'test{0:03d}'.format(i)
      newTestNum = 'test{0:03d}'.format(i + 1)
      os.rename("{0}.in".format(testNum), "{0}.in".format(newTestNum))
      os.rename("{0}.out".format(testNum), "{0}.out".format(newTestNum))
