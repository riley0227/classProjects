using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HotbarExpansionItem : MonoBehaviour
{
    private void OnTriggerEnter(Collider other)
    {
        InventoryManager inventoryManager = other.GetComponentInChildren<InventoryManager>();
        if (inventoryManager != null)
        {
            inventoryManager.ExpandHotbar();
            Destroy(gameObject); //remove item after use
        }
    }
}

