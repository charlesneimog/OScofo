# Events

`OScofo` for now supports four events, `NOTE`, `TRILL`, `CHORD` and `REST`. Before define then, I need to explain how to represent `PITCHES` and `DURATIONS`.

!!! tip "Check the MusicXML Importer"
    `OScofo` has a [MusicXML importer](../../Editor), it is very accurate and tested on MuseScore and Sibelius (but should work for all major programs). 


--- 
## Pitches and Durations

### `PITCH`

On OScofo pitches are represented by `name` or `MIDI`.

- `NOTENAME`: Things like `C4`, `Db5`, `C#5`, `Gb5`, etc...
- `MIDI`: Normal `MIDI`. 60 for `C4`, 67 for `G4`, etc...

---
### `DURATION`

Different from `Antescofo`, on `OScofo` you just represent `<DURATION>` using number of **tempos**.

So _fraction representation is not support_, mainly because something like `1` is ambiguous with `1/1`. And, for me, in fraction will be necessary to define the Time Unity to be a more precise language.

Because that `OScofo` uses time representation relative to the value of `BPM` define previously. For example, if in your score you have the `BPM` set as **:material-music-note-quarter: = 60** this means that

- :material-music-note-half: duration value is `2`;
- :material-music-note-quarter: duration value is `1`;
- :material-music-note-eighth: is `0.5`,
- :material-music-note-sixteenth: is `0.25`

if in your score you have the `BPM` set as **:material-music-note-eighth: = 60** this means that

- :material-music-note-half: duration value is `4`;
- :material-music-note-quarter: duration value is `2`;
- :material-music-note-eighth: is `1`,
- :material-music-note-sixteenth: is `0.5`

For duration with dot, you sum it.

!!! tip "Compound Time Signatures"
    Avoid to use Compound Time Signatures as **:material-music-note-quarter-dotted: = 60**, because this means that the :material-music-note-eighth: will be equal to 0.33, prefer to use **:material-music-note-eighth: = 180**.

---
## Events
---

### `NOTE`

`NOTE` events describes normal pitches. It must be defined as `NOTE <PITCH> <DURATION>`.

- `NOTE C4 2`
- `NOTE 60 2`
- `NOTE C#5 0.3`
- `NOTE Bb3 0.25`

---
### `TRILL`

`TRILL` events describes trill and tremolo events. It must be defined as `TRILL (<PITCH1> <PITCH2>) <DURATION>`.

- `TRILL (C4 D4) 2`
- `TRILL (60 67) 2`
- `TRILL (C#5 E5) 0.3`
- `TRILL (Bb4 D5) 0.25`

---
### `CHORD`

`CHORD` events describes chord, stable multiphonics, and others events. It must be defined as `CHORD (<PITCH1> <PITCH2>) <DURATION>`.

- `CHORD (C4 E4 G4) 2`
- `CHORD (60 64 67) 2`
- `CHORD (C#5 E5 Ab5) 0.3`
- `CHORD (Bb4 D5 F4) 0.25`

---
### `REST`

`REST` events describes rests. It must be defined as `REST <DURATION>`.

- `REST 0.2`
- `REST 4`



---
