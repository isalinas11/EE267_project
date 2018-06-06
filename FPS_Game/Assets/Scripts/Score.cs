using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour {

  int numTargets = 11;
  public Text scoreText;

  IEnumerator Start () {
    // Pause Update() script until kickoff sequence begins
    enabled = false;

    // Kickoff sequence
    yield return new WaitForSeconds(5.0f);
    scoreText.text = "Ready.";
    yield return new WaitForSeconds(1.0f);
    scoreText.text = "Set.";
    yield return new WaitForSeconds(1.0f);
    scoreText.text = "Go!!!";
    yield return new WaitForSeconds(2.0f);
    scoreText.text = "Targets Remaining: " + numTargets.ToString();

    // Start Updated() script
    enabled = true;
  }

  public void UpdateScore() {
    numTargets--;
    scoreText.text = "Targets Remaining: " + numTargets.ToString();
    if (numTargets <= 0) {
      GameOver();
    }
  }

  public void GameOver() {
    // End game sequence
    enabled = false;
    scoreText.text = "Game Over.";
  }
  
  void Update () {
    // Update time on screen
  }
}
