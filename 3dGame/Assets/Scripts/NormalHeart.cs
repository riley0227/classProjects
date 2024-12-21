using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NormalHeart : MonoBehaviour
{
    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            PlayerHealth playerHealth = other.GetComponent<PlayerHealth>();
            if (playerHealth != null)
            {
                //check if player's health is not already full
                if (!playerHealth.IsHealthFull())
                {
                    playerHealth.Heal(2f);
                    Destroy(gameObject); 
                }
            }
        }
    }
}

