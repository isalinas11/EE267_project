using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CrossBowShooting : MonoBehaviour 
{

    public GameObject arrow;
    public float BowRange = 100f;
    float arrowImpulse = 100f;

    void Update() 
    {
        if(Input.GetButtonDown("Fire1"))
        {   // button for shooting
            Camera cam = Camera.main;
            Instantiate(arrow, transform.position, transform.rotation);
            //GameObject arrow = (GameObject)Instantiate(arrow, transform.position, transform.rotation);

        }    
    }    

}
