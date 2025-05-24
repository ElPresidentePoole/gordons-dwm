#!/usr/bin/env sh

while true; do
    STATUS="$(cat /sys/class/power_supply/BAT0/status)"
    if [ "$STATUS" = "Discharging" ]; then
        # no icon
        STATUS="󰁹"
    elif [ "$STATUS" = "Charging" ]; then
        # lightning bolt
        STATUS="󰂄"
    elif [ "$STATUS" = "Not Charging" ]; then
        # full battery icon
        STATUS="󰂄"
    fi

    xsetroot -name "$(date) $STATUS$(cat /sys/class/power_supply/BAT0/capacity)"
    sleep 1
done

