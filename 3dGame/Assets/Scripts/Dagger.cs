using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Dagger : Weapon
{
    public GameObject stabEffectPrefab;

    private void Awake()
    {
        cooldown = 0.15f; 
    }

    public override void Attack(Vector3 attackOrigin, Transform attacker)
    {
        if (isOnCooldown) return; 

        if (stabEffectPrefab != null)
        {
            GameObject stabEffect = Instantiate(stabEffectPrefab, attacker.position, attacker.rotation);
            stabEffect.transform.Translate(Vector3.forward * 2f); 
            Destroy(stabEffect, 0.2f); 
        }

        Collider[] hitObjects = Physics.OverlapSphere(attackOrigin, range, targetLayer);
        foreach (Collider hit in hitObjects)
        {
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
        yield return new WaitForSeconds(cooldown);
        isOnCooldown = false;
        Debug.Log($"{name}'s cooldown is complete.");
    }
}

