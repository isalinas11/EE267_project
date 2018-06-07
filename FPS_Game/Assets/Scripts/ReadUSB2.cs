using UnityEngine;
using System.Collections;
using System.IO.Ports;
using UnityEditor;
using System;
using System.Collections.Generic;

public class ReadUSB2 : MonoBehaviour {

  const int baudrate = 115200;

  // Specify Correct Port Name
  const string portName = "/dev/cu.usbmodem2822651";

  SerialPort serialPort = new SerialPort(portName, baudrate);

  void Start () {
    serialPort.ReadTimeout = 100;
    serialPort.Open();

    if( !serialPort.IsOpen ) {

      Debug.LogError("Couldn't open " + portName);

    }

  }
    
  void Update () {

    List<byte> buffer = new List<byte>();

    // Reading 1024 bytes
    for (int i = 0; i < 64; i++)
    {
      buffer.Add((byte)serialPort.ReadByte());
    }

    // Convert list of bytes to string
    string te = System.Text.Encoding.UTF8.GetString(buffer.ToArray());
    //Debug.Log(te);

    // Split string into lines
    string[] lines = te.Split( '\n' );

    if ( lines.Length >= 2) {

      // Split line by spaces
      string[] line = lines[lines.Length - 2].Split( ' ' );

      // If the line starts with "QC", parse the Quaternion
      if ( line[0] == "QC" && line.Length >= 5 ) {
        
        Quaternion q = new Quaternion( float.Parse(line[2]),
          float.Parse(line[3]),
          -float.Parse(line[4]),
          float.Parse(line[1]));

        transform.rotation = Quaternion.Inverse(q);

      }

    }

  }


  void OnGUI()
  {
    string euler = "Euler angle: " + transform.eulerAngles.x + ", " +
      transform.eulerAngles.y + ", " + transform.eulerAngles.z;
  }
}

