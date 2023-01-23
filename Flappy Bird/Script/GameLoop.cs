using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameLoop : MonoBehaviour
{
    public bool isGamePaused = false;
    

    int highScore = 0;
    int currentScore = 0;

    //Script Variables
    Player player;

    void playerDeath() {
        isGamePaused = true;
        highScore = System.Math.Max(highScore, currentScore);
    }

    void Start()
    {
        player = FindObjectOfType<Player>();
        player.OnPlayerDeath += playerDeath;
    }


}
