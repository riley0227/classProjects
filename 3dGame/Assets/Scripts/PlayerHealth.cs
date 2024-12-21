using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class PlayerHealth : MonoBehaviour
{
    public int maxHearts = 3; //maximum number of heart containers
    public float healthPerHeart = 2f; //each heart has 2 health (full = 2, half = 1, empty = 0)
    private float currentHealth;

    public Transform heartsPanel; //UI panel with heart icons
    public Sprite fullHeartSprite; 
    public Sprite halfHeartSprite; 
    public Sprite emptyHeartSprite; 

    private List<Image> heartImages = new List<Image>();

    private bool isInvincible = false; //invincibility state
    private float invincibilityDuration = 0.5f; //invincibility duration to avoid rapid collisions

    void Start()
    {
        currentHealth = maxHearts * healthPerHeart; //initialize health
        InitializeHearts();
        UpdateHeartsUI();
    }

    public void TakeDamage(float damage)
    {
        if (isInvincible) return; //ignore damage

        currentHealth -= damage;
        currentHealth = Mathf.Clamp(currentHealth, 0, maxHearts * healthPerHeart); //prevent negative health
        UpdateHeartsUI();

        if (currentHealth <= 0)
        {
            Die();
        }

        StartCoroutine(InvincibilityCoroutine());
    }

    private IEnumerator InvincibilityCoroutine()
    {
        isInvincible = true;
        yield return new WaitForSeconds(invincibilityDuration);
        isInvincible = false;
    }

    private void InitializeHearts()
    {
        //clear the existing heart icons
        foreach (Transform child in heartsPanel)
        {
            Destroy(child.gameObject);
        }
        heartImages.Clear();

        //heart containers based on maxHearts
        for (int i = 0; i < maxHearts; i++)
        {
            GameObject heart = new GameObject("Heart" + (i + 1), typeof(RectTransform), typeof(Image));
            heart.transform.SetParent(heartsPanel);

            RectTransform rectTransform = heart.GetComponent<RectTransform>();
            rectTransform.sizeDelta = new Vector2(30, 30); 
            rectTransform.anchoredPosition = new Vector3(i * 60, 0, 0); 

            Image heartImage = heart.GetComponent<Image>();
            heartImage.sprite = fullHeartSprite;

            heartImages.Add(heartImage);
        }
    }

    private void UpdateHeartsUI()
    {
        //heart image setting the appropriate sprite
        for (int i = 0; i < heartImages.Count; i++)
        {
            float heartValue = Mathf.Clamp(currentHealth - (i * healthPerHeart), 0, healthPerHeart);

            if (heartValue >= 2)
            {
                heartImages[i].sprite = fullHeartSprite;
            }
            else if (heartValue == 1)
            {
                heartImages[i].sprite = halfHeartSprite;
            }
            else
            {
                heartImages[i].sprite = emptyHeartSprite;
            }
        }
    }

    private void Die()
    {
        Debug.Log("Player died!");
        //TODO
    }

    public void AddHeart()
    {
        maxHearts++; 
        currentHealth += healthPerHeart; //heal the new heart
        currentHealth = Mathf.Clamp(currentHealth, 0, maxHearts * healthPerHeart); //ensure health doesn't exceed max
        InitializeHearts(); //recreate hearts UI
        UpdateHeartsUI(); 
    }

    public void Heal(float healAmount)
    {
        currentHealth += healAmount; //add the heal amount to current health
        currentHealth = Mathf.Clamp(currentHealth, 0, maxHearts * healthPerHeart); //do not exceed max health
        UpdateHeartsUI(); //reflect healed health
    }

    public bool IsHealthFull()
    {
        return currentHealth >= maxHearts * healthPerHeart;
    }
}
