using System.Collections;
using UnityEngine;

public class Weapon : MonoBehaviour
{
    public int damage;
    public float range;
    public LayerMask targetLayer;
    public Vector3 spawnOffset; //position offset relative to WeaponHolder
    public Vector3 spawnRotation; //rotation offset relative to WeaponHolder

    protected bool isOnCooldown = false; 
    protected float cooldown = 1f; //default cooldown (can be overridden)
    public Sprite icon; // Icon to display in the UI

    public virtual void Attack(Vector3 attackOrigin, Transform attacker)
    {
        //base attack logic
    }

    public virtual void ResetCooldown()
{
    isOnCooldown = false; //still deciding if we want it like this
    Debug.Log($"{name}'s cooldown has been reset.");
}

}



