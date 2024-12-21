using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackpackCollectible : MonoBehaviour
{
    public int inventoryIncrease = 1; //how much packpack increases inventory by

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            //find InventoryManager component
            InventoryManager inventoryManager = other.GetComponentInChildren<InventoryManager>();
            if (inventoryManager != null)
            {
                //increase capacity
                inventoryManager.maxSlots += inventoryIncrease;
                Debug.Log($"Inventory capacity increased by {inventoryIncrease}. New max capacity: {inventoryManager.maxSlots}");
                inventoryManager.UpdateInventorySpaceUI();
            }

            //destroy backpack on collection
            Destroy(gameObject);
        }
    }
}

