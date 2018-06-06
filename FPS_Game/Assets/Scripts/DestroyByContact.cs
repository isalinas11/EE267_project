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
        if (other.tag == "Target")
        {
            scoreboard1.UpdateScore();
            scoreboard2.UpdateScore();
            Destroy(other.gameObject);
            //Destroy(gameObject);
            Instantiate(explosion, transform.position, transform.rotation);

            //gameController.AddScore(scoreValue);
        }

	}
}
