#pragma once

#include "../Hardware/Button.h"
#include "Abstract/CCOut.h"

/**
 * @brief   A class for latching buttons and switches that send MIDI Controller 
 *          change events.
 * 
 * The switch is debounced.
 * 
 * @see     Button
 */
class CCButtonLatching : public DigitalCCOut {
  public:
    /**
     * @brief   Construct a new CCButtonLatching.
     * 
     * @param   pin
     *          The digital input pin with the switch connected.  
     *          The internal pull-up resistor will be enabled.
     * @param   address
     *          The MIDI Controller number. [0, 119]
     * @param   channel
     *          The MIDI Channel. [1, 16]
     * @param   offValue
     *          The Controller value to send when the control is turned on.
     *          [0, 127]
     * @param   onValue
     *          The Controller value to send when the control is turned off.
     *          [0, 127]
     */
    CCButtonLatching(pin_t pin, uint8_t address, uint8_t channel,
                     uint8_t offValue = 0, uint8_t onValue = 127)
        : DigitalCCOut(address, channel, offValue, onValue), button{pin} {}

  private:
    void refresh() {
        Button::State state = button.getState();
        if (state == Button::Falling || state == Button::Rising) {
            sendOn();
            sendOff();
        }
    }

    Button button;
};