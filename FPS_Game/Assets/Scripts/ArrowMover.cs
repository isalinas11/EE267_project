using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ArrowMover : MonoBehaviour {

    private Rigidbody rb;
    public float arrowImpulse = 10f;

	// Use this for initialization
	void Start () 
    {
        Camera cam = Camera.main;

        rb = GetComponent<Rigidbody>();
        rb.AddForce(cam.transform.forward * arrowImpulse, ForceMode.Impulse);;	
	}
	
}
