/**
 *  This is the main file for pose tracking with the VRduino.
 */

#include <Wire.h>
#include "TestPose.h"
#include "PoseTracker.h"
#include "InputCapture.h"

//complementary filter value [0,1].
//1: ignore acc tilt, 0: use all acc tilt
double alphaImuFilter = 0.99;

//get simulated lighthouse timings (to test without physical lighthouse)
bool simulateLighthouse = false;

//if test is true, then run tests in Test.cpp and exit
bool test = false;

//mode of base station
//0:A, 1:B, 2: C
const int A = 0;
const int B = 1;
const int C = 2;
int baseStationMode = A;

//if true, measure the imu bias on start
bool measureImuBias = true;

//if measureImuBias is false, set the imu bias to the following
double imuBias[3] = {0, 0, 0};

PoseTracker tracker(alphaImuFilter, baseStationMode, simulateLighthouse);

void setup() {

  Serial.begin(115200);
  // while ( !Serial ) {
  // }

  if (test) {

    delay(500);
    testPoseMain();
    return;

  }

  tracker.initImu();

  if (measureImuBias) {

    tracker.measureImuBiasVariance();

  } else {

    tracker.setImuBias(imuBias);

  }

}

void loop() {

  if (test) {

    return;

  }

  if (Serial.available()) {

    int byteRead = Serial.read();
    int desiredMode  = byteRead - 48;

    if (desiredMode >= 0 && desiredMode <= 2) {

      tracker.setMode(desiredMode);

    } else if (byteRead == 'r') {

      //reset orientation tracking
      tracker.resetOrientation();

    } else if (byteRead == 'b') {

      //remeasure bias
      tracker.measureImuBiasVariance();

    }

  }


  //variables determining the success of imu and lighthouse tracking
  bool imuTrack = false;
  int hmTrack = -2;

  imuTrack = tracker.processImu();
  hmTrack = tracker.processLighthouse();

  //get values from tracker
  // double pitch = tracker.getBaseStationPitch();
  // double roll = tracker.getBaseStationRoll();
  // int mode = tracker.getBaseStationMode();
  // const unsigned long * numPulseDetections = tracker.getNumPulseDetections();
  // const double * position = tracker.getPosition();
  // const double * position2D = tracker.getPosition2D();
  const Quaternion& quaternionComp = tracker.getQuaternionComp();
  // const Quaternion& quaternionHm = tracker.getQuaternionHm();


//COMMENT OUT IF YOU DO NOT NEED POSITION
  // if (hmTrack == 1 ) {

  //   //print xyz position
  //  Serial.printf("PS %.3f %.3f %.3f\n",
  //     position[0], position[1], position[2]);
  // }
  
// UNCOMMENT IF YOU NEED ORIENTATION
  if (imuTrack == 1) {

  //print quaternion from imu
    delay(60);
    Serial.printf("QC %.3f %.3f %.3f %.3f\n",
      quaternionComp.q[0], quaternionComp.q[1],
      quaternionComp.q[2], quaternionComp.q[3]);

  }

}
