<p align="center">
  <h1 align="center">OScofo</h1>
  <p align="center">
    <a href="https://charlesneimog.github.io/OScofo">
      <img src="./Documentation/assets/OScofo.svg" width="10%" alt="Logo">
    </a>
  </p>
  <h4 align="center">OScofo: OpenScore Follower</h4>
</p>

`OScofo` is an open-source project designed to provide score following capabilities for contemporary music applications. Originally developed as a PureData (Pd) object, OScofo has now been expanded into a versatile C++ library that integrates seamlessly with multiple environments, including a Python package. Currently under development, OScofo is already functional and serves as a valuable tool for researchers and musicians.

## Goal

The aim of *OScofo* is to provide a straightforward and accessible tool for real-time score following. By keeping the software lightweight, it can run seamlessly on the web through the [pd4web](https://charlesneimog.github.io/pd4web/) platform, thanks to the ability to use PureData directly in web browsers. With _pd4web_ and _OScofo_ will be possible to use the software in rehearsals with just a single click, eliminating the need for external libraries, compatibility issues, or complex installations -- ultimately facilitating the sharing and performance of contemporary music.

## Collaboration and Contribution

I invite composers, researchers and developers to contribute to the *OScofo* project. Not just with code, but with theory, math, etc. I am trying to make OScofo acessible via a Python implementation, to test it should be easy. By sharing the source code, I am trying to provide access to the theories and mathematical formulas that drive the software, all this come from the amazing research work of Arshia Cont and Philippe Cuvillier at IRCAM. This transparency is inspired by the amazing tools like IEM, SPARTA, and of course, PureData.

## Technical Foundations

*OScofo* uses several concepts developed by many researches (with focus on the research of Cont and Cuvillier).

* **Pitch Comparison**: Utilizes the Kullback-Leibler (KL) Divergence method for pitch comparison as presented by Christopher Raphael (2006), Arshia Cont in 2008 and 2010.
* **Rhythm Synchronization**: Integrates theories of rhythm synchronization developed by Edward Large and Mari Riess Jones (1999) and Edward Large and Caroline Palmer (2002), as presented for Cont (2010).
* **Forward Algorithm**: For now, *OScofo* uses the equation presented by Arshia Cont (2010) and developed by Yann Guédon (2005).
* **Score Language**: Based on the `scofo` (by Miller Puckette) and `antescofo~` (by Arshia Cont, Philippe Cuvillier, and others) language.

## Building

#### Requirements

* cmake and ninja;
* treesitter (`npm install tree-sitter`) (If you want to change/update score syntax)
* pybind11 (optional): To build Python package.
* PureData (optional): To build the Pd Object.

#### Building Options

* `PDLIBDIR`: Where the Pd object will be installed
* `BUILD_PY_MODULE`: Build or not the OScofo python module.
* `BUILD_PD_OBJECT`: Build or not the Pd Object.

``` bash
git clone https://github.com/charlesneimog/OScofo --recursive
cmake . -B build -DBUILD_PY_MODULE=ON -DBUILD_PD_OBJECT=ON -G Ninja 
cmake --build build
```

To install use `cmake --install build`.

