using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class ShopManager : MonoBehaviour
{
    public GameObject shopUI; 
    public Transform dropPoint; //where purchased items spawn
    public TextMeshProUGUI moneyText; //player's current money
    public TextMeshProUGUI shopLabel;

    public List<ShopItem> quality1Items;
    public List<ShopItem> quality2Items; 
    public List<ShopItem> quality3Items; 

    public Button dummyButton;     //dummy button to be the default
    public Button quality1Button; 
    public Button quality2Button; 
    public Button quality3Button; 
    public Button closeButton;    

    private List<Button> shopButtons; //all buttons for navigation
    private int currentButtonIndex = 0; //currently highlighted button

    private ShopItem selectedQuality1Item;
    private ShopItem selectedQuality2Item;
    private ShopItem selectedQuality3Item;

    private bool quality1SoldOut = false;
    private bool quality2SoldOut = false;
    private bool quality3SoldOut = false;

    private GameManager gameManager;

    private void Start()
    {
        gameManager = GameManager.Instance;
        shopUI.SetActive(false);

        dummyButton.onClick.AddListener(() => { /* arbitrary Dummy button */ });
        quality1Button.onClick.AddListener(() => PurchaseItem(1));
        quality2Button.onClick.AddListener(() => PurchaseItem(2));
        quality3Button.onClick.AddListener(() => PurchaseItem(3));
        closeButton.onClick.AddListener(CloseShop);

        //button navigation
        shopButtons = new List<Button> { dummyButton, quality1Button, quality2Button, quality3Button, closeButton };
    }

    private void Update()
    {
        if (shopUI.activeSelf)
        {
            HandleButtonNavigation();
        }
    }

    public void OpenShop()
    {
        UpdateMoneyText();
        SelectRandomItemsForSale();
        ResetSoldOutFlags();
        UpdateButtonLabels();
        shopLabel.text = "Buy somethin' will ya?";

        shopUI.SetActive(true);
        currentButtonIndex = 0; //dummy button to start on, shop was being weird
        HighlightButton(); 
        Time.timeScale = 0; //pause the game
    }

    public void CloseShop()
    {
        shopUI.SetActive(false);
        Time.timeScale = 1; //resume
    }

    private void UpdateMoneyText()
    {
        moneyText.text = $"Coins: {gameManager.GetTotalCoins()}";
    }

    private void SelectRandomItemsForSale()
    {
        selectedQuality1Item = quality1Items[Random.Range(0, quality1Items.Count)];
        selectedQuality2Item = quality2Items.Count > 0
            ? quality2Items[Random.Range(0, quality2Items.Count)]
            : null;
        selectedQuality3Item = quality3Items[Random.Range(0, quality3Items.Count)];
    }

    private void ResetSoldOutFlags()
    {
        quality1SoldOut = false;
        quality2SoldOut = false;
        quality3SoldOut = false;
    }

    private void PurchaseItem(int quality)
{
    ShopItem itemToPurchase = null;
    bool purchaseSuccessful = false;

    switch (quality)
    {
        case 1:
            if (!quality1SoldOut)
            {
                itemToPurchase = selectedQuality1Item;
                purchaseSuccessful = gameManager.GetTotalCoins() >= itemToPurchase.price;
                if (purchaseSuccessful) quality1SoldOut = true;
            }
            break;

        case 2:
            if (!quality2SoldOut)
            {
                itemToPurchase = selectedQuality2Item;
                purchaseSuccessful = gameManager.GetTotalCoins() >= itemToPurchase.price;
                if (purchaseSuccessful)
                {
                    quality2SoldOut = true; //mark as sold out for this visit
                    quality2Items.Remove(itemToPurchase); //remove the purchased item from the array (only used for weapons)
                }
            }
            break;

        case 3:
            if (!quality3SoldOut)
            {
                itemToPurchase = selectedQuality3Item;
                purchaseSuccessful = gameManager.GetTotalCoins() >= itemToPurchase.price;
                if (purchaseSuccessful) quality3SoldOut = true;
            }
            break;
    }

    if (purchaseSuccessful)
    {
        gameManager.SpendCoins(itemToPurchase.price);
        Instantiate(itemToPurchase.itemPrefab, dropPoint.position, Quaternion.identity);

        UpdateMoneyText();
        UpdateButtonLabels();
        HighlightButton(); //select current button
        shopLabel.text = "Sold!";
    }
    else if (itemToPurchase != null)
    {
        shopLabel.text = "Not enough money for that!";
    }
}
    //upon purchasing update buttons
    private void UpdateButtonLabels()
{
    quality1Button.GetComponentInChildren<TextMeshProUGUI>().text =
        quality1SoldOut ? "SOLD OUT" : $"{selectedQuality1Item.itemName}\n{selectedQuality1Item.price} Coins";
    quality1Button.interactable = !quality1SoldOut;

    if (quality2SoldOut || selectedQuality2Item == null)
    {
        quality2Button.GetComponentInChildren<TextMeshProUGUI>().text = "SOLD OUT";
        quality2Button.interactable = false;
    }
    else
    {
        quality2Button.GetComponentInChildren<TextMeshProUGUI>().text =
            $"{selectedQuality2Item.itemName}\n{selectedQuality2Item.price} Coins";
        quality2Button.interactable = true;
    }
    quality3Button.GetComponentInChildren<TextMeshProUGUI>().text =
        quality3SoldOut ? "SOLD OUT" : $"{selectedQuality3Item.itemName}\n{selectedQuality3Item.price} Coins";
    quality3Button.interactable = !quality3SoldOut;
}

    private void HandleButtonNavigation()
    {
        if (Input.GetKeyDown(KeyCode.UpArrow) || Input.GetKeyDown(KeyCode.W))
        {
            currentButtonIndex = (currentButtonIndex - 1 + shopButtons.Count) % shopButtons.Count;
            HighlightButton();
        }
        else if (Input.GetKeyDown(KeyCode.DownArrow) || Input.GetKeyDown(KeyCode.S))
        {
            currentButtonIndex = (currentButtonIndex + 1) % shopButtons.Count;
            HighlightButton();
        }

        if (Input.GetKeyDown(KeyCode.Return) || Input.GetKeyDown(KeyCode.Space))
        {
            shopButtons[currentButtonIndex].onClick.Invoke();
        }
    }

    private void HighlightButton()
    {
        EventSystem.current.SetSelectedGameObject(shopButtons[currentButtonIndex].gameObject);

        for (int i = 0; i < shopButtons.Count; i++)
        {
            ColorBlock colors = shopButtons[i].colors;
            colors.normalColor = (i == currentButtonIndex) ? colors.highlightedColor : colors.normalColor;
            shopButtons[i].colors = colors;
        }
    }
}



