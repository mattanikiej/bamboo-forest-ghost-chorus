# Bamboo Forest Ghost Chorus and Delay VST3/AU Plugin
Introducing the **Bamboo Forest** from Cool Panda Software

<p>
    <img alt="Bamboo Forest Interface" src="/Assets/interface.png" max-height="400" aspect-ratio="7:4">
</p>

For a twinlking delay and a spacious chorus, the Bamboo forest can give a surreal effect to your audio. Increasing Ghost decreases the initial chorus effect, while keeping it intact in the delay signal. This creates a cool vibe as if a chorus of ghosts is helping you along.

Experience the short demo below:

https://www.youtube.com/watch?v=yq-T4vw3dbU

## Parameters
The parameters are laid out according to their respective effect
* Delay Params 🔄
    * Wet - amount of delayed signal to add
    * Feedback - amount of signal to feed back to delay
    * Delay Time - time between delay (max 2 seconds)

* Chorus Params (for each voice) 🐼
    * Wet - amount of voice to add
    * Feedback - amount of voice signal to feed back to delay
    * Rate - frequency of phased signal

* Ghost Params 👻
    * Ghost - how much of chorus voices to add to the output
    * Dry - amount of input signal to add to output

## What is Ghost?
Ghost is a very cool effect that allows the dry signal to go through unchanged, and then adds the effects only onto the delayed signal. What this does with a chorus, is make the delay very twinkly and sounds great with single notes and chords alike. It's an interesting effect that has a ton of potential uses! The Ghost parameter essentially works as a wet mixer for the chorus effect as a whole on the input signal.

## Files Supported
Currently **Bamboo Forest** is only available as a **VST3** or **AU** plugin, which is supported by most types of DAWs. It also works as a standalone app without the need for a DAW. It has not been tested or compiled as an AAX file for Pro Tools, but it should build and work if you have the license and SDK.

## Build
This plugin is built using the JUCE framework. See their [repository](https://github.com/juce-framework/JUCE) or [website](https://juce.com/) for instructions on downloading and building projects with Projucer. Once the project is built, move the AU or VST3 file where those files are generally installed on your machine.

Some tips for development:
The [JUCE Plugin Tutorial Part 1](https://docs.juce.com/master/tutorial_create_projucer_basic_plugin.html) has a very good tutorial on how to set up their host to connect to the plugin. This is extremely useful as it becomes much easier to use your IDE's debugger, and you're not reliant on a DAW to hear your plugin.

<a href="https://www.coolxpanda.com/">
    <img alt="Cool Panda Logo" src="/Assets/coolxpandapng.png" height="200">
</a>

