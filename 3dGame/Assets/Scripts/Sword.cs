using System.Collections;
using UnityEngine;

public class Sword : Weapon
{
    public GameObject slashEffectPrefab; //slash animation prefab

    private void Awake()
    {
        cooldown = 0.25f; //cooldown duration for the sword
    }

    public override void Attack(Vector3 attackOrigin, Transform attacker)
    {
        if (isOnCooldown)
        {
            return;
        }

        if (slashEffectPrefab != null)
        {
            //spwan the slash effect at the attacker's position and facing direction
            GameObject slashEffect = Instantiate(slashEffectPrefab, attacker.position, attacker.rotation);
            slashEffect.transform.Translate(Vector3.forward * 2f); //move forward slightly, in front of player

            //destroy the effect after 0.3s
            Destroy(slashEffect, 0.3f); 
        }

        Collider[] hitObjects = Physics.OverlapSphere(attackOrigin, range, targetLayer);
        foreach (Collider hit in hitObjects)
    {

    //check for any enemy inheriting from BaseEnemy
    BaseEnemy enemy = hit.GetComponent<BaseEnemy>();
    if (enemy != null)
    {
        Vector3 knockbackDirection = (hit.transform.position - attacker.position).normalized;
        enemy.TakeDamage(damage, knockbackDirection);
    }
    }
        StartCoroutine(CooldownRoutine());
    }

    private IEnumerator CooldownRoutine()
    {
        isOnCooldown = true;
        yield return new WaitForSeconds(cooldown); //sword's specific cooldown
        isOnCooldown = false;
        Debug.Log("Sword cooldown complete.");
    }
}
