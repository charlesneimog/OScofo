# Score Configuration

I chose to make all the configuration from `OScofo` using the score, this make easier to use the object on different programs. For example, instead of create a lot of code to handle the configuration for `Pd` object, and another object for `Max`, I can create a simple one where the composer can config the `OScofo` using the score. This allows that I use my time to develop the object itself, not the bridge between `OScofo` and `Pd`, `Max` or others.

!!! tip "Always try on `OScofo` Editor"
    Always try the examples on `OScofo` Online Editor, with highlight this becomes much easier.


---
## <h2 align="center">Time Configuration</h2>
---

### `BPM`

- `Default is 60`

`BPM` keyword set the `BPM` value for the next event.

```
BPM 50
```

---
### `PhaseCoupling`

- `Default is 0.5`
- `Range 0-2`

This value must be between 0 and 2 and captures the amount of force exerted on attentional rhythm, determining, among other factors, the speed at which the coupled system relaxes in relation to the attractor (Large and Jones, 1999, p. 128).

---

### `SyncStrength`

- `Default is 0.5`
- `Range 0-1`

The value of $\eta_s$ (Sync Strength) corresponds to what Large and Jones (1999) refer to as the adaptation rate. This value determines how much of the previous predictions will be considered for the next BPM prediction and must be between 0 and 1. According to Large and Jones (1999, p. 131), "if it is set to 1, each estimate of $\kappa$ will be based solely on the current onsets. If $\eta_s$ < 1, the focus adapts more slowly because the previous context is taken into account".

```
SyncStrength 0.4
```

---
## <h2 align="center">Listening Module Configuration</h2>
---

### `PitchSigma`

- `Default is 0.5`
- `Range 0-1`

Define the

```
PitchSigma 0.2
```

---

### `Entropy`

- `Default is 0`
- `Range 0-1`

Define the min value to entropy to trigger a new event. If they are very similar, the event is not triggered.

```
Entropy 0.02
```

---
## <h2 align="center">Audio Configuration</h2>
---

### `FFTSize`

- `Default is 4096`
- `Must be a power of 2, I recomend 1024, 2048 or 4096`

```
FFTSize 4096
```

---

### `HopSize`

- `Default is 1024`
- `Must be a power of 2, I recomend 256, 512 or 1024`

```
HopSize 4096
```


---


