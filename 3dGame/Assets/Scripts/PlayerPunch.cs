using System.Collections;
using UnityEngine;

public class PlayerPunch : MonoBehaviour
{
    public float punchRange = 2.5f; //punch range
    public Transform punchOrigin;  //origin of the punch 
    public LayerMask enemyLayer;  
    public Transform handTransform; //reference to hand 
    public Vector3 punchOffset = new Vector3(0, 0, 0.5f); //forward motion for the punch
    public float punchSpeed = 10f; //hand movement speed
    public int punchDamage = 1; //punch damage
    private Vector3 originalPosition; //original hand position
    private bool isPunching = false;

    public WeaponHolder weaponHolder; //WeaponHolder transform for positioning

    void Start()
    {
        //store the original position of the hand
        originalPosition = handTransform.localPosition;
    }

    void Update()
{
    if (Input.GetMouseButtonDown(0))
    {
        if (weaponHolder == null || weaponHolder.equippedWeapon == null)
        {
            //default punch
            if (!isPunching)
            {
                StartCoroutine(Punch());
            }
        }
        else
        {
            //weapon attack
            weaponHolder.Attack();
        }
    }
}


    private IEnumerator Punch()
    {
        isPunching = true;

        //hand movement
        Vector3 targetPosition = originalPosition + punchOffset;
        while (Vector3.Distance(handTransform.localPosition, targetPosition) > 0.01f)
        {
            handTransform.localPosition = Vector3.MoveTowards(handTransform.localPosition, targetPosition, punchSpeed * Time.deltaTime);
            yield return null;
        }

        //damage enemies
        Collider[] hitObjects = Physics.OverlapSphere(punchOrigin.position, punchRange, enemyLayer);
        foreach (Collider hit in hitObjects)
        {

            //check if enemy (from BaseEnemy)
            BaseEnemy enemy = hit.GetComponent<BaseEnemy>();
            if (enemy != null)
            {
                Vector3 knockbackDirection = (hit.transform.position - transform.position).normalized;
                enemy.TakeDamage(punchDamage, knockbackDirection);
            }
        }

        //move the hand back to its original position
        while (Vector3.Distance(handTransform.localPosition, originalPosition) > 0.01f)
        {
            handTransform.localPosition = Vector3.MoveTowards(handTransform.localPosition, originalPosition, punchSpeed * Time.deltaTime);
            yield return null;
        }

        isPunching = false;
    }

    private void OnDrawGizmosSelected()
    {
        Gizmos.color = Color.red;
        Gizmos.DrawWireSphere(punchOrigin.position, punchRange);
    }
}
