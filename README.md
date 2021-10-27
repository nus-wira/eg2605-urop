# User Guide

Features are to be used on the Serial Monitor on Arduino.

## Features & Usage

The format of commands below keep to the following.

| :information_source: | Words in `UPPER_CASE` are parameters. |
|----------------------|:-------------------------------------|

### Move Effector
Move all actuators to the same absolute position.
`POS` will be parsed and converted to a value, following the table below.
It can interpreted as a percentage automatically.
`maxEncVal` was empirically determined to be `50000`.
| POS | Parsed as |
|-----|-----------|
|`POS < 0`|`0`|
|`0 <= POS <= 100`|`POS * maxEncVal / 100`|
|`100 <POS<= maxEncVal`|`POS`|
|`POS > maxEncVal`|`maxEncVal`|

Format: `m POS`

Example: `m 500`

### Move Actuator
Move chosen actuator to desired position

Format: `{a/b/c} 500`

Example: `b 500`

### Test Movement
Test predefined movement of the effector.
This can be used to determine actuators A, B & C.

Format: `t`

### Calibrate Encoders
Calibrate position and value of encoders.
The value will be 0 at the lowest position.

Format: `r`

### View Help
View help text - all commands as listed on this document -
on the Serial monitor.

Format: `h`


## Command summary

Action | Format, Examples
--------|------------------
**Move** | `m POS` <br> e.g., `m 500`
**Move Single** | `{a/b/c} POS` <br> e.g., `b 500`
**Test** | `t`
**Calibrate** | `r`
**Help** | `h`