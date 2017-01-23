# bth_curtain_core

A simple design of an automatic curtain controller based on msp430g2553 core，bh1750fvi light senser，ds3231 rtc moudule，hc-05 bluetooth uart and ssd1331 96x96 rgb oled for display.

*Tips: This project contains source code only, CCS Project files has been removed to keep compatibility with version differerces of CCS-IDE, so you should create the CCS Project manually.*

** compiler flag： --cpp_default --printf_support=nofloat **

# How to compile ?

## Step 1: Clone the git
* Use command:
`git clone https://github.com/redchenjs/bth_curtain_core.git`

## Step 2: Create a new CCS Project

* Use "New Project" Wizard to create a new CCS Project.

* Type a project name you like(etc bth_curtain_core).

* Select the "Target" option to "MSP430GXXXX Family" and select the "MSP430G2553".

* Deselect the "Use default location" and locate it to the folder we just cloned(like /home/xxxx/bth_curtain_core).

* Select the "Empty Project" template, since our project has a main.c already, do not use the "Empty Project(with main.c)" template.

* Then click the "Finish" button to finish the wizard.

## Step 3：Compile
* Add the function you like and compile it.
