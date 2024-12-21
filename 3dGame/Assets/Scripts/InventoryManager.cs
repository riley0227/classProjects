using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

//manages inventory collection with a ton of debugs, so if you add more you dont miss anything
public class InventoryManager : MonoBehaviour
{
    public List<Weapon> hotbar = new List<Weapon>(); //references to instantiated weapon objects
    public WeaponHolder weaponHolder;
    public int maxSlots = 9; //maximum number of inventory slots
    private int currentSlot = 0; //current number of inventory 
    public Transform hotbarPanel; //HotbarPanel UI container
    public GameObject inventorySlotPrefab; //single inventory slot
    public TextMeshProUGUI inventorySpaceText; //inventory space text
    
    private void Update()
{
    //switch weapons(1,2,3... might add scroll wheel)
    if (Input.GetKeyDown(KeyCode.Alpha1)) SwitchWeapon(0);
    if (Input.GetKeyDown(KeyCode.Alpha2)) SwitchWeapon(1);
    if (Input.GetKeyDown(KeyCode.Alpha3)) SwitchWeapon(2);
    if (Input.GetKeyDown(KeyCode.Alpha4)) SwitchWeapon(3);

    //easier than I thought lol
    float scroll = Input.GetAxis("Mouse ScrollWheel");
    if (scroll > 0f)
    {
        int nextSlot = (currentSlot + 1) % hotbar.Count;
        SwitchWeapon(nextSlot);
    }
    else if (scroll < 0f)
    {
        int prevSlot = (currentSlot - 1 + hotbar.Count) % hotbar.Count;
        SwitchWeapon(prevSlot);
    }
}

    private void Start()
{
    if (weaponHolder == null)
    {
        weaponHolder = GetComponentInChildren<WeaponHolder>();
        if (weaponHolder == null)
        {
            Debug.LogError("WeaponHolder is not assigned or could not be found in children of InventoryManager!");
        }
    }
}


    public void AddWeapon(Weapon weaponPrefab)
{
    if (hotbar.Count >= maxSlots)
    {
        Debug.LogWarning("Hotbar is full!");
        return;
    }

    if (weaponPrefab == null)
    {
        Debug.LogError("WeaponPrefab is null. Cannot add weapon to inventory.");
        return;
    }

    //create the weapon
    GameObject weaponInstance = Instantiate(weaponPrefab.gameObject);
    Weapon weapon = weaponInstance.GetComponent<Weapon>();

    if (weapon == null)
    {
        Debug.LogError($"The prefab {weaponPrefab.name} does not have a Weapon component!");
        Destroy(weaponInstance); // Prevent orphaned objects
        return;
    }

    weaponInstance.SetActive(false); // Start as inactive
    hotbar.Add(weapon);
    UpdateHotbarUI();

    //auto equip the first weapon added
    if (hotbar.Count == 1)
    {
        EquipWeaponInSlot(0);
    }
    UpdateInventorySpaceUI();
}
    //cant switch to a (yet to) exist hotbar
    public void SwitchWeapon(int slotIndex)
    {
        if (slotIndex < 0 || slotIndex >= hotbar.Count)
        {
            Debug.LogWarning("Invalid hotbar slot!");
            return;
        }

        EquipWeaponInSlot(slotIndex);
    }

    private void EquipWeaponInSlot(int slotIndex)
{
    if (slotIndex < 0 || slotIndex >= hotbar.Count)
    {
        Debug.LogWarning("Invalid hotbar slot index!");
        return;
    }

    Weapon weaponToEquip = hotbar[slotIndex];

    if (weaponToEquip == null)
    {
        Debug.Log("Slot is empty. Unequipping weapon.");
        weaponHolder.EquipWeapon(null);
        UpdateHotbarUI();
        currentSlot = slotIndex;
        return;
    }

    weaponHolder.EquipWeapon(weaponToEquip);
    currentSlot = slotIndex;
    Debug.Log($"Equipped weapon in slot {slotIndex}: {weaponToEquip.name}");
    UpdateHotbarUI();
}

//used to add items to the hotbar-IE backpack item
public void ExpandHotbar()
{
    if (hotbar.Count < maxSlots)
    {
        hotbar.Add(null); 
        Debug.Log($"Hotbar expanded. Total slots: {hotbar.Count}");
        UpdateInventorySpaceUI();
    }
    else
    {
        Debug.LogWarning("Cannot expand hotbar beyond the maximum slots!");
    }
}

public void UpdateHotbarUI()
{
    //clear existing slots
    foreach (Transform child in hotbarPanel)
    {
        Destroy(child.gameObject);
    }

    //populate slots based on items in the hotbar
    for (int i = 0; i < hotbar.Count; i++)
    {
        GameObject slot = Instantiate(inventorySlotPrefab, hotbarPanel);

        Weapon weapon = hotbar[i];
        if (weapon != null)
        {
            Image iconImage = slot.transform.Find("Icon").GetComponent<Image>();
            if (iconImage != null && weapon.icon != null)
            {
                iconImage.sprite = weapon.icon;
                iconImage.enabled = true;
            }
        }

        //highlights the equipped weapon (yellow)
        Image slotBackground = slot.GetComponent<Image>();
        if (slotBackground != null)
        {
            slotBackground.color = (i == currentSlot) ? Color.yellow : Color.white;
        }
    }
}

public void UpdateInventorySpaceUI()
{
    if (inventorySpaceText != null)
    {
        inventorySpaceText.text = $"Inventory Size: {hotbar.Count}/{maxSlots}";
    }
}


}

