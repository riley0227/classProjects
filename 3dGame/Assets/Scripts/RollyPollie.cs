using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RollyPollie : BaseEnemy
{
    public float speed = 5f;
    public float detectionRange = 100f;

    protected override void Start()
    {
        base.Start();
        player = GameObject.FindGameObjectWithTag("Player")?.transform;
        knockbackMultiplier = 5f;
    }

    private void FixedUpdate()
    {
            float distanceToPlayer = Vector3.Distance(transform.position, player.position);
            if (distanceToPlayer <= detectionRange)
            {
                RollTowardsPlayer();
            }
    }

    private void RollTowardsPlayer()
    {
        Vector3 direction = (player.position - transform.position).normalized;
        rb.AddForce(direction * speed, ForceMode.Acceleration);
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.CompareTag("Player"))
        {
            PlayerHealth playerHealth = collision.gameObject.GetComponent<PlayerHealth>();
            if (playerHealth != null)
            {
                playerHealth.TakeDamage(1); //deal half a heart (1 = half, 2 = full)
            }
        }
    }

    protected override void Die()
    {
        base.Die();
    }
}
