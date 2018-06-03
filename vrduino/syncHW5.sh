#!/bin/bash

# copies over the following files from HW5 solution

files=(OrientationMath.cpp OrientationMath.h
  OrientationTracker.cpp OrientationTracker.h
  TestOrientation.cpp TestOrientation.h
  TestUtil.cpp TestUtil.h
  Imu.cpp Imu.h
  simulatedImuData.h)

hw5dir='../../../homework5/solution/vrduino/'

for i in "${files[@]}"
do
  rm $i
  cp $hw5dir$i ./
done
