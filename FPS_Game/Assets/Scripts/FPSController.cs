using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent (typeof(CharacterController))]
public class FPSController : MonoBehaviour {

  public float movementSpeed = 10.0f;
  public float rotationSensitivity = 7.0f;

  float pitch = 0;
  float yaw = 0;
  public float pitchRange = 60.0f;

  float verticalVelocity = 0;
  float jumpSpeed = 15.0f;

  CharacterController characterController;

	// Use this for initialization
	void Start () {
		Screen.lockCursor = true;
    characterController = GetComponent<CharacterController>();
	}
	
	// Update is called once per frame
	void Update () {

    // Key-driven Rotation
    yaw += Input.GetAxis("Mouse X") * rotationSensitivity;
    pitch += Input.GetAxis("Mouse Y") * rotationSensitivity;
    pitch = Mathf.Clamp(pitch, -pitchRange, pitchRange);
    if (yaw != 0 || pitch != 0) {
      Camera.main.transform.localRotation *= Quaternion.Euler(pitch, yaw, 0);
      yaw = 0;
      pitch = 0;
    }

    // Jumping
    verticalVelocity += Physics.gravity.y * Time.deltaTime;
    if (characterController.isGrounded && Input.GetButtonDown("Jump")) {
      verticalVelocity = jumpSpeed;
    }

    // Movement
    float forwardSpeed = Input.GetAxis("Vertical") * movementSpeed;
		float lateralSpeed = Input.GetAxis("Horizontal") * movementSpeed;

    Vector3 speed = new Vector3(lateralSpeed, verticalVelocity, forwardSpeed);
    Quaternion q = new Quaternion(0, Camera.main.transform.rotation.y, 0, Camera.main.transform.rotation.w);
    speed = q * speed;

    characterController.Move(speed * Time.deltaTime);
	}
}
