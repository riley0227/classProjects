using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OrbskiEnemy : BaseEnemy
{
    public float moveSpeed = 5f; 
    public float hoverAmplitude = 0.5f; //height amplitude for floating
    public float hoverFrequency = 2f; //frequency of floating
    public float detectionRange = 100f;

    private Vector3 originalPosition;

    protected override void Start()
    {
        base.Start();
        originalPosition = transform.position; 
    }

    protected override void Update()
    {
        base.Update();
        FloatMovement(); 
        MoveTowardsPlayer(); 
    }

    //apply a floating effect using a sine wave
    private void FloatMovement()
    {
        float newY = originalPosition.y + Mathf.Sin(Time.time * hoverFrequency) * hoverAmplitude;
        transform.position = new Vector3(transform.position.x, newY, transform.position.z);
    }

    private void MoveTowardsPlayer()
    {
        if (player == null) return;

        //detection range check
        float distanceToPlayer = Vector3.Distance(transform.position, player.position);
        if (distanceToPlayer <= detectionRange)
        {
            //move toward player
            Vector3 direction = (player.position - transform.position).normalized;
            transform.position += direction * moveSpeed * Time.deltaTime;
        }
    }

    private void OnCollisionEnter(Collision collision)
{
    if (collision.collider.CompareTag("Player"))
    {
        PlayerHealth playerHealth = collision.collider.GetComponent<PlayerHealth>();
        if (playerHealth != null)
        {
            playerHealth.TakeDamage(1f); //OUCH!
        }
    }
}


    protected override void Die()
    {
        base.Die();
    }
}

