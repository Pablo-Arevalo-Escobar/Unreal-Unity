using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Runtime.CompilerServices;


public class Player : MonoBehaviour
{
    bool isDead;

    [SerializeField, Range(0f,10.0f)]
    float jumpHeight;
    [SerializeField, Range(1f,10.0f)]
    float bounce = 5f;



    Vector2 velocity;
    bool desiredJump;
    Rigidbody2D body;

    public event Action OnPlayerDeath;

    void OnEnable() {
        body = GetComponent<Rigidbody2D>();
        isDead = false;
    }

    // Update is called once per frame
    void Update()
    {
        velocity = new Vector2(0.0f,0.0f);
        //Process Player Input
        if(!isDead) {
            Vector2 playerInput;
            playerInput.x = Input.GetAxis("Horizontal");
            playerInput.y = Input.GetAxis("Vertical");
            playerInput = Vector2.ClampMagnitude(playerInput, 1f);
            desiredJump |= Input.GetButtonDown("Jump");
        }
    }

    void FixedUpdate() {
        if(desiredJump && !isDead) {
            Jump();
            desiredJump = false;
            body.velocity = velocity;
        }
    }

    void OnCollisionEnter2D(Collision2D collision) {
        //Log(collision);
        float direction = collision.transform.localPosition.x > transform.localPosition.x? -1:1;
        HandleCollision(direction);
    }
    void Log(Collision2D collision, [CallerMemberName] string message = null)
    {
        Debug.Log($"{message} called on {name} because a collision with {collision.collider.name}");
    }

    void HandleCollision(float direction) {
        if(OnPlayerDeath != null && !isDead) {
            if(body.velocity.x == 0) { body.velocity += new Vector2(direction*bounce,0); }
            Debug.Log($"DIRECTION {direction}");
            OnPlayerDeath();
            isDead = true;
        }
        //Bird faces down
        //Quaternion target = Quaternion.Euler(0,0,-90.0f);
        //transform.rotation = Quaternion.Slerp(transform.rotation, target, Time.deltaTime*smooth);
    }

    void Jump() {
        velocity += new Vector2(0.0f,jumpHeight);
    }
    
}
