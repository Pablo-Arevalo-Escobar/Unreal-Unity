using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Pipes : MonoBehaviour
{
    [SerializeField]
    Transform pipePreFab;

    [SerializeField]
    Rect boundary = new Rect(-15,20,40,40);

    [SerializeField, Range(0f,1f)]
    float speed = 0.1f;

    

    static int numberOfPipes = 5;
    int spawnZoneXCoord = 30;
    int pipeGap = 10;
    Vector2[] positions = new Vector2[numberOfPipes];
    Transform[] pipes = new Transform[numberOfPipes];
    GameLoop game;


    void Awake()  {
        for(int i =0; i < positions.Length; i++) {
            pipes[i] = Instantiate(pipePreFab);
            positions[i] = new Vector2(pipeGap*(i+1), (int)Random.Range(-7,5));
        }

        game = FindObjectOfType<GameLoop>();
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if(!game.isGamePaused) {
            for(int i =0; i < positions.Length; i++) {
            positions[i] += Vector2.left*speed;
            }
            CheckBounds();
            for(int i =0; i<positions.Length; i++) {
                pipes[i].localPosition = new Vector3(positions[i].x,positions[i].y,0.0f);
            }
        }
        

    }

    void CheckBounds() {
        for(int i = 0; i <positions.Length; i++) {
            if( !boundary.Contains(positions[i]) ){
                positions[i] = new Vector2(spawnZoneXCoord, Random.Range(-7,5));
            }
        }
   
    }
}
