
`OScofo` support actions as consequences of `EVENTS`, these actions are very tied with the program where `OScofo` is running and for now just are supported on `PureData`. 

The actions can be run immediately after the `EVENT` detection or after some delay specified using the `delay` keyword. There are two types of actions for now `sendto` and `luacall`. Both functions can be delay specified as followed: 

--- 
## Delayed Messages
--- 

#### Absolute time delay 


Absolute time are clock time, and they don't change if the performer plays your must faster or slower, always have the same duration.

* `delay 2000 ms`: Has a delay of 2 seconds after the `EVENT` detection.
* `delay 2 sec`: Has a delay of 2 seconds after the `EVENT` detection.

For example:

```
NOTE C4 2 
    delay 2000 ms sendto e1 [1 2 3 4]
```

!!! note "The syntax highlight of the Editor make this easier to read!!!"

Will send the list `1 2 3 4` to the receiver `e1` after 2 seconds. 

--- 

#### Relative time delay 

Relative time are music time, they change if the performer plays your must faster or slower.

* `delay 1 tempo`: Has a delay of 1 tempo after the `EVENT` detection. 
* `delay 0.5 tempo`: Has a delay of 0.5 tempo after the `EVENT` detection. 


---
## Actions

### `sendto`

* `sendto e1`: Send a bang to the receiver `e1`
* `sendto myreceiver [hello world]`: Send `hello world` to the receiver `myreceiver`.
* `delay 1 tempo sendto e1`: Send a bang to the receiver `e1` after the duration on 1 tempo.

### `luacall`

---
!!! warning "Advanced Users"
    This is designed for advances users, but if you are starting you can ask questions using the `OScofo` Github Discussions.

---

Lua function are executed immediately after the event detection of after some delay time.

* `luacall(myluafunc("hello world")`: Execute the function `myluafunc` immediately.
* `delay 1 tempo luacall(myluafunc("hello after 1 tempo")`: Execute the function after 1 tempo.

!!! tip "Lua Functions definition"
    Lua Functions must be defined inside the `LUA {}`, for example: 
    ``` lua
    LUA {
        function myluafunc(s)
            pd.post(s)
        end
    }
    ```

---


