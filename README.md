# Synthesizer

This synthesizer application was created for MSU'S CSE 471 Multi Media Processing course by Conner Smith
  

## Score File Format

### instrument
The synhtesizer is programmed to respond to changes to the instument value as well as the effect flags

### note
"measure", "beat, and "note" are all required fields. The rest are optional and only apply to the additive synth

### effect
The three implented effects are chorus, flange, and a noise gate. They are included in the xml a via an effect tag with the name of the effect as the value
the type tag then specifies the extent of the effect. 

```xml
<?xml version="1.0" encoding="utf-8"?>
<score bpm="100" beatspermeasure="2">
     <instrument instrument="AdditiveSynth" noisegate="0" chorus="0" flange="0">
          <note measure="1" beat="1" duration="0.25" crossFadeIn="0.55" crossFadeOut="0.35" ADSR="0.1 0.0 1.0 0.9" vibrato="4.0 1.5" amplitudes="1.0 0.8 0.6" note="Bb4"/>
          <note ...>
     </instrument>

     <effect effect="NoiseGate">
         <type threshold="50" wet="1" dry="0"/>
     </effect>

     <effect effect="Chorus">
 	 <type delay=".1" wet="1.0" dry="0" range=".5" rate="2"/>
     </effect>

     <effect effect="Flange">
          <type delay=".05" wet="1" dry="0" range=".5" rate="2" level="2"/>
     </effect>
</score>
```

# About

The additive synthesizer works by layering multiple sine waves, each with its own adjustable frequency and amplitude, 
to create complex sounds. Instead of shaping a single waveform, you’re working with a collection of individual sine 
waves, or partials, that combine to form the final sound. The synthesizer allows for detailed control over these partials,
meaning you can fine-tune how each one contributes to the overall tone and texture.

ADSR (Attack, Decay, Sustain, Release) envelopes are used to shape how the amplitude of each sine wave changes over time.
For example, you can set a slow attack for a more gradual onset or a fast decay for a quick drop-off in volume. By applying
different ADSR settings to various partials, you can make the sound feel more organic or give it a specific character.
Vibrato is another key element, which modulates the pitch of the sine waves to add a sense of movement or expression,
making the sound less static.

Crossfading plays a role in smoothly transitioning between different sets of oscillators. This is useful when you want 
the timbre to change over time, blending one sound into another without any harsh jumps. The amplitudes of the individual
sine waves are crucial as well, since they determine which harmonics are emphasized or softened. By carefully setting 
these amplitudes, you can craft anything from a bright, brassy tone to a mellow, flute-like sound. Each of these controls—ADSR,
crossfade, vibrato, and amplitude—interact to give you precise management over the synthesis process.
