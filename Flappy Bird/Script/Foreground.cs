using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Foreground : MonoBehaviour
{
    [SerializeField]
    Transform foreGroundPreFab;

    [SerializeField, Range(0f,1f)]
    float speed = 0.2f;


    Vector2[] positions = new Vector2[2];
    Transform[] foreGround = new Transform[2];

    int startXCoord = 32;
    int endXCoord = -66;

    GameLoop game;

    void Awake() {
        for(int i =0; i < positions.Length; i++) {
            foreGround[i] = Instantiate(foreGroundPreFab);
            positions[i] = new Vector2(startXCoord+((i)*78), foreGround[i].localPosition.y);
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
                foreGround[i].localPosition = new Vector3(positions[i].x,positions[i].y,0.0f);
            }
        }
    }

    void CheckBounds() {
        for(int i=0; i<positions.Length; i++) {
            if(positions[i].x <= endXCoord) {
                positions[i].x = startXCoord*2;
            }
        }
    }
}
