# :simple-lua: Lua for Interactive Actions 

Lua is an amazing language to create interactive events. You can read its 88 pages manual on English [here](https://www.lua.org/manual/5.4){target="_blank"} or in Portuguese [here](https://www.lua.org/manual/5.2/pt){target="_blank"}.

I am not present the language here, there are a lot of tutorials on the internet and YouTube.

* Very Complete [here](https://youtu.be/zi-svfdcUc8?si=-JpbobE-0T-zS4_z&t=1393){target="_blank"}.
* Very Fast, Complex but yet Complete tutorial [here](https://www.youtube.com/watch?v=jUuqBZwwkQw){target="_blank"}.
* If you know how to program in another language [here](https://www.youtube.com/watch?v=kgiEF1frHQ8){target="_blank"}.
* Text [here](https://tylerneylon.com/a/learn-lua/){target="_blank"}.

What I will present is how to create these actions using `lua` and `oscofo`, `pd` and `max` module.


### :simple-lua: `oscofo` Lua Module

The `oscofo` module inside Lua can be used to get and set values of `oscofo` on the fly. It exposes several functions:

- **`oscofo.getKappa`**  
    - `input`: No input.
    - `output`: Value of Kappa $\kappa$.
    - `description`: Get the value for Kappa. The closer it is to 10, the more synchronized the algorithm and the performance are.

---
- **`oscofo.getBPM`**  
    - `input`: No input.
    - `output`: Value of the current BPM;
    - `description`: Get the current BPM.

---
- **`oscofo.getPitchProb`**  
    - `input`: Frequency value in Hz, for example `oscofo.getPitchProb(440)` will return the probability of the pitch 440Hz being played.
    - `output`: Value of the probability.
    - `description`: Get the probability of being a specified pitch using the pitch templates.

---
- **`oscofo.getSpectrumPower`**  
    - `input`: No input.
    - `output`: Value of the probability.
    - `description`: Returns a table with the current FFT magnitude of all the bins.


### :simple-lua: `pd` Lua Module

The `pd` module inside Lua allows interaction with Pure Data functionalities, exposing the following functions:

- **`pd.print`**  
    - **`input`**: A string message to print.  
    - **`output`**: no output.
    - **`description`**: Logs a message to the console, similar to Pure Data's `print` object.

---
- **`pd.post`**  
    - **`input`**: A string message to post.  
    - **`output`**: no output.
    - **`description`**: Posts a message at the default verbosity level, used for general logging.

---
- **`pd.error`**  
    - **`input`**: A string error message.  
    - **`output`**: no output.
    - **`description`**: Logs an error message in the Pure Data console, similar to a `print` with error severity.

---
- **`pd.sendBang`**  
    - **`input`**: A string representing the destination symbol in Pure Data.  
    - **`output`**: no output.
    - **`description`**: Sends a bang message to a specified destination in Pure Data.

---
- **`pd.sendFloat`**  
    - **`input`**: A float value and a string representing the destination symbol in Pure Data.  
    - **`output`**: no output.
    - **`description`**: Sends a floating-point number to a specified destination in Pure Data.

---
- **`pd.sendSymbol`**  
    - **`input`**: A string symbol and a string representing the destination symbol in Pure Data.  
    - **`output`**: no output.
    - **`description`**: Sends a symbol to a specified destination in Pure Data.

---
- **`pd.sendList`**  
    - **`input`**: A list of values (mixed types) and a string representing the destination symbol in Pure Data.  
    - **`output`**: no output.
    - **`description`**: Sends a list of values to a specified destination in Pure Data.

