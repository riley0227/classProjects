using UnityEngine;

public class WeaponHolder : MonoBehaviour
{
    public Weapon equippedWeapon; //currently equipped weapon
    public Transform weaponPivot; // Pivot for animations (could not get working if someone wants to use it)
    public Transform weaponHolderTransform; //same as weaponHolder

    private Weapon defaultWeapon; //hand

    private void Start()
    {
        //default weapon if one is already equipped
        if (equippedWeapon != null)
        {
            defaultWeapon = equippedWeapon;
            AttachWeaponToHolder(equippedWeapon.gameObject, equippedWeapon.spawnOffset, equippedWeapon.spawnRotation);
        }
    }

    public void EquipWeapon(Weapon newWeapon)
{
    //deactivate the currently equipped weapon, for no overlapping
    if (equippedWeapon != null)
    {
        equippedWeapon.gameObject.SetActive(false);
    }

    //equip for the new weapon
    if (newWeapon != null)
    {
        newWeapon.gameObject.SetActive(true);
        AttachWeaponToHolder(newWeapon.gameObject, newWeapon.spawnOffset, newWeapon.spawnRotation);
        equippedWeapon = newWeapon;

        //reset new weapon cooldown
        newWeapon.ResetCooldown();
    }
    else
    {
        Debug.LogWarning("No weapon to equip!");
        equippedWeapon = null;
    }
}

    public void Attack()
    {
        if (equippedWeapon != null)
        {
            //attack method on equipped weapon
            equippedWeapon.Attack(weaponPivot.position, transform);
        }
    }

    private void AttachWeaponToHolder(GameObject weaponInstance, Vector3 offset, Vector3 rotation)
    {
        weaponInstance.transform.SetParent(weaponHolderTransform);
        weaponInstance.transform.localPosition = offset;
        weaponInstance.transform.localRotation = Quaternion.Euler(rotation);
        weaponInstance.transform.localScale = Vector3.one;
    }
}
