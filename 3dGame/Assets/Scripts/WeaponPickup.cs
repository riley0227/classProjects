using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WeaponPickup : MonoBehaviour
{
    public Weapon weaponPrefab; //reference to weapon prefab

    private void OnTriggerEnter(Collider other)
{
    InventoryManager inventoryManager = other.GetComponentInChildren<InventoryManager>();
    if (inventoryManager != null)
    {   
        //debugging if forgot to add prefab
        if (weaponPrefab == null)
        {
            Debug.LogError("WeaponPickup has no weaponPrefab assigned!");
            return;
        }

        //check for room in the hotbar
        if (inventoryManager.hotbar.Count >= inventoryManager.maxSlots)
        {
            Debug.LogWarning("Cannot pick up weapon: Hotbar full.");
            return;
        }

        //prevent duplicates
        foreach (Weapon weapon in inventoryManager.hotbar)
        {
            if (weapon != null && weapon.name == weaponPrefab.name)
            {
                Debug.LogWarning("Weapon already in hotbar!");
                return;
            }
        }

        //add weapon
        inventoryManager.AddWeapon(weaponPrefab);
        Debug.Log($"Picked up weapon: {weaponPrefab.name}");
        Destroy(gameObject);
    }
}

}






