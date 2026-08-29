#!/bin/sh
# Hide the dummy battery node from UPower by replacing its type with Unknown.
# This forces UPower to treat it as line-power instead of a battery.
echo Unknown > /tmp/bq24190_type
mount --bind /tmp/bq24190_type /sys/class/power_supply/bq24190-battery/type
