using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class DeathScreenNavigation : MonoBehaviour
{
    public GameObject defaultButton;

    void OnEnable()
    {
        // Set the default button when the panel is shown
        EventSystem.current.SetSelectedGameObject(defaultButton);
    }

    void Update()
    {
        // Allow reselecting the button if no button is selected
        if (EventSystem.current.currentSelectedGameObject == null)
        {
            EventSystem.current.SetSelectedGameObject(defaultButton);
        }
    }
}

