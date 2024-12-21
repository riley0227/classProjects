using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public abstract class BaseEnemy : MonoBehaviour
{
    public int maxHealth = 10; //default maximum health
    protected int currentHealth;

    public float knockbackForce = 2f; // default force
    public float knockbackMultiplier = 1f; //knockback modifier
    private Renderer[] enemyRenderers; //array to store renderers for all visible parts
    private Dictionary<Renderer, Color> originalColors = new Dictionary<Renderer, Color>();
    private bool isBlinking = false;

    protected Rigidbody rb;

    [SerializeField]
    private GameObject explosionPrefab;
    public event Action OnDeath;

    [SerializeField]
    private int coinValue = 1;
    protected Transform player;

    [SerializeField]
    private GameObject heartPrefab;

    protected virtual void Start()
    {
        currentHealth = maxHealth;
        rb = GetComponent<Rigidbody>();
        enemyRenderers = GetComponentsInChildren<Renderer>();

        //store the original color of each renderer
        foreach (Renderer renderer in enemyRenderers)
        {
            originalColors[renderer] = renderer.material.color;
        }

        player = GameObject.FindGameObjectWithTag("Player")?.transform;
    }

    protected virtual void Update()
    {
        //kill enemy if they get too low (shouldn't happen but sometimes does)
        if (transform.position.y < 1f)
        {
            Die();
        }
        FacePlayer();
    }

    private void FacePlayer()
    {
        if (player != null)
        {
            Vector3 directionToPlayer = (player.position - transform.position).normalized;
            directionToPlayer.y = 0;
            transform.forward = directionToPlayer; // face the player
        }
    }

    public virtual void TakeDamage(int damage, Vector3 knockbackDirection, float? knockbackForceOverride = null)
    {
        currentHealth -= damage;

        //knockback with weapon-specific or default force
        float appliedKnockbackForce = knockbackForceOverride ?? knockbackForce;
        if (rb != null)
        {
            rb.AddForce(knockbackDirection * appliedKnockbackForce, ForceMode.Impulse);
        }

        if (enemyRenderers != null && !isBlinking)
        {
            StartCoroutine(BlinkRed());
        }

        if (currentHealth <= 0)
        {
            Die();
        }
    }

    private IEnumerator BlinkRed()
    {
        isBlinking = true;

        //change the color of all renderers to red
        foreach (Renderer renderer in enemyRenderers)
        {
            if (renderer != null)
            {
                renderer.material.color = Color.red;
            }
        }

        yield return new WaitForSeconds(0.1f);

        //reset the color of all renderers to their original color
        foreach (Renderer renderer in enemyRenderers)
        {
            if (renderer != null)
            {
                renderer.material.color = originalColors[renderer];
            }
        }

        isBlinking = false;
    }

    protected virtual void Die()
{
    Debug.Log(gameObject.name + " died!");
    RewardPlayer();
    DropHeart(); //attempt to drop a heart
    SpawnExplosion();
    OnDeath?.Invoke();
    Destroy(gameObject);
}

private void DropHeart()
{
    //RNG for heart drop
    float dropChance = UnityEngine.Random.Range(0f, 1f);
    if (dropChance <= 0.1f) // 10% chance
    {
        Instantiate(heartPrefab, transform.position, Quaternion.identity);
    }
}

    private void RewardPlayer()
    {
        if (GameManager.Instance != null)
        {
            GameManager.Instance.AddCoins(coinValue);
        }
    }

    private void SpawnExplosion()
    {
        Instantiate(explosionPrefab, transform.position, Quaternion.identity);
    }
}
