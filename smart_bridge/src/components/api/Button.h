#ifndef __BUTTON__
#define __BUTTON__

constexpr bool BUTTON_PRESSED = true;
constexpr bool BUTTON_RELEASED = false;

/**
 * @class Button
 * @brief This class represents a button component.
 *
 * This class provides the basic functionalities of a button.
 * It should be inherited by specific button types.
 */
class Button
{

public:
    /**
     * @brief Default constructor for the Button class.
     *
     * @param pin The pin number where the button is connected.
     */
    Button(int pin);

    /**
     * @brief Check if the button is pressed.
     *
     * @return true if the button is pressed, false otherwise.
     */
    virtual bool checkButtonPressStatus() = 0;

    /**
     * @brief Check if the button is released.
     *
     * @return true if the button is released, false otherwise.
     */
    virtual bool checkButtonReleaseStatus() = 0;

    /**
     * @brief Synchronizes the button state with the actual physical button.
     */
    virtual void updateButtonState();

    /**
     * @brief Retrieves the last time the button state was synchronized.
     *
     * @return The last synchronization time.
     */
    long retrieveLastButtonSyncTime();

protected:
    /**
     * @brief Set the last synchronization time.
     *
     * @param time The new synchronization time.
     */
    void setLastButtonSyncTime(long time);

private:
    /**
     * @brief The last time the button state was synchronized.
     */
    long lastTimeButtonWasInSync;

    /**
     * @brief The pin number where the button is connected.
     */
    int buttonPin;

    /**
     * @brief The current state of the button (true if pressed, false otherwise).
     */
    bool buttonState;
};

#endif // __BUTTON__