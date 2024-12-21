using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Hammer : Weapon
{
    public GameObject hammerSmashEffectPrefab;
    public float knockbackForce = 40f; //WE BRING THE BOOM!

    private void Awake()
    {
        cooldown = 1.5f; //high hammer cooldown
    }

    public override void Attack(Vector3 attackOrigin, Transform attacker)
    {
        if (isOnCooldown)
        {
            Debug.LogWarning("Hammer is on cooldown!");
            return;
        }

        Debug.Log("Hammer attack triggered!");

        //spawn smash effect
        if (hammerSmashEffectPrefab != null)
        {
            //spawn position with offsets
            Vector3 effectPosition = attackOrigin + attacker.forward * 2f;

            //hammer smash effect at the calculated position
            GameObject hammerSmashEffect = Instantiate(hammerSmashEffectPrefab, effectPosition, attacker.rotation);
            hammerSmashEffect.transform.localScale *= 2; //effect size for impact
            Destroy(hammerSmashEffect, 0.5f); //destroy affect 0.5s after animation
        }

        //damage and knockback logic
        Collider[] hitObjects = Physics.OverlapSphere(attackOrigin, range, targetLayer);
        foreach (Collider hit in hitObjects)
        {
            BaseEnemy enemy = hit.GetComponent<BaseEnemy>();
            if (enemy != null)
            {
                Vector3 knockbackDirection = (hit.transform.position - attacker.position).normalized;
                enemy.TakeDamage(damage, knockbackDirection, knockbackForce);
            }
        }

        //start cooldown
        StartCoroutine(CooldownRoutine());
    }

    private IEnumerator CooldownRoutine()
    {
        isOnCooldown = true;
        yield return new WaitForSeconds(cooldown);
        isOnCooldown = false;
        Debug.Log("Hammer cooldown complete.");
    }
}
