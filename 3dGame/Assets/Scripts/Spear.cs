using System.Collections;
using UnityEngine;

public class Spear : Weapon
{
    private bool isAttacking = false;
    public float knockbackForce = 20f; //knockback specific to this weapon

    private Coroutine attackCoroutine; //currently running attack animation

    private void Awake()
    {
        cooldown = 0.75f; //cooldown duration for the spear
    }

    public override void Attack(Vector3 attackOrigin, Transform attacker)
    {
        if (isOnCooldown)
        {
            Debug.LogWarning("Spear is on cooldown!");
            return;
        }

        if (isAttacking)
        {
            return;
        }

        //attack animation coroutine
        if (attackCoroutine != null)
        {
            StopCoroutine(attackCoroutine); //stop any running attack animation
        }
        attackCoroutine = StartCoroutine(SpearThrustAnimation(attacker));

        //hit detection 
        Collider[] hitObjects = Physics.OverlapSphere(attackOrigin, range, targetLayer);
        foreach (Collider hit in hitObjects)
        {
            //check if enemy is of type BaseEnemy
            BaseEnemy enemy = hit.GetComponent<BaseEnemy>();
            if (enemy != null)
            {
                Vector3 knockbackDirection = (hit.transform.position - attacker.position).normalized;
                enemy.TakeDamage(damage, knockbackDirection, knockbackForce);
            }
        }
        StartCoroutine(CooldownRoutine());
    }

    private IEnumerator SpearThrustAnimation(Transform attacker)
    {
        isAttacking = true;

        //move the spear forward and then reset
        float duration = 0.3f;
        float elapsed = 0f;
        Vector3 originalPosition = spawnOffset; //start at the spawn offset
        Vector3 targetPosition = originalPosition + new Vector3(0, 0, 1f); //thrust distance

        while (elapsed < duration)
        {
            elapsed += Time.deltaTime;
            transform.localPosition = Vector3.Lerp(originalPosition, targetPosition, elapsed / duration);
            yield return null;
        }

        //reset position
        transform.localPosition = spawnOffset;
        isAttacking = false;
    }

    private IEnumerator CooldownRoutine()
    {
        isOnCooldown = true;
        yield return new WaitForSeconds(cooldown); // Weapon-specific cooldown
        isOnCooldown = false;
        Debug.Log("Spear cooldown complete.");
    }

    //reset states if switching weapons or interrupted (TODO??)
    public override void ResetCooldown()
    {
        base.ResetCooldown(); 
        isAttacking = false;

        //stop ongoing attack animation
        if (attackCoroutine != null)
        {
            StopCoroutine(attackCoroutine);
            attackCoroutine = null;
        }

        //spear returns to its spawn offset position
        transform.localPosition = spawnOffset;
    }
}

