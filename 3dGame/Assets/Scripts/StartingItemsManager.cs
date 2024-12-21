using System.Collections.Generic;
using UnityEngine;

public class StartingItemsManager : MonoBehaviour
{
    private Dictionary<GameObject, float> originalYPositions = new Dictionary<GameObject, float>();

    private void Start()
    {
        Debug.Log("StartingItemsManager started.");
        HandleStartingItems();
    }

    private void HandleStartingItems()
    {
        //find all items tagged as "Starting"
        GameObject[] startingItems = GameObject.FindGameObjectsWithTag("Starting");
        //check if "Start with Everything" is enabled
        bool startWithEverything = PlayerPrefs.GetInt("StartWithEverything", 0) == 1;

        foreach (GameObject item in startingItems)
        {
            //store original Y position of items
            if (!originalYPositions.ContainsKey(item))
            {
                originalYPositions[item] = item.transform.position.y;
            }

            Vector3 newPosition = item.transform.position;

            if (startWithEverything)
            {
                newPosition.y = originalYPositions[item];
            }
            else
            {
                newPosition.y = -10f;
            }

            item.transform.position = newPosition;
        }
    }
}
