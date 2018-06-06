using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyByContact : MonoBehaviour {

    public GameObject explosion;
    public Score scoreboard1;
    public Score scoreboard2;

    //public int scoreValue;
    //private GameController gameController;

	// Use this for initialization
	/*
    void Start () 
    {
        GameObject gameControllerObject = GameObject.FindWithTag("GameController");
        if (gameControllerObject != null)
        {
            gameController = gameControllerObject.GetComponent<GameController>();
        }
        if (gameController == null)
        {
            Debug.Log("Cannot find 'Game Controller' script");
        }	
	}
	*/

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Target" || other.tag == "FlareTarget" )
        {
            scoreboard1.UpdateScore();
            scoreboard2.UpdateScore();
            //Destroy(other.transform.parent.gameObject);
            Destroy(other.gameObject);
            //Destroy(gameObject);
            Destroy(GameObject.Find("Arrow_Small(Clone)"));
            Instantiate(explosion, transform.position, transform.rotation);

        }   
        if (other.tag == "FlareTarget")
        {
            Destroy(other.transform.parent.gameObject);
        }
        if (other.tag == "Boundary")
        {
            //Destroy(gameObject);
            Destroy(GameObject.Find("Arrow_Small(Clone)"));

        }


	}
}
