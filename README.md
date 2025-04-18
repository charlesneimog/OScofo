<p align="center">
  <h1 align="center">OScofo</h1>
  <h4 align="center">OScofo: OpenScore Follower</h4>
</p>

`OScofo` is an open-source project designed to provide score following capabilities for contemporary music applications. Originally developed as a PureData (Pd) object, OScofo has now been expanded into a versatile C++ library that integrates seamlessly with multiple environments, including a Max Object, Python package, and others comming. Currently under development, OScofo is already functional and serves as a valuable tool for researchers and musicians.

## Download

* Check the [Releases](https://github.com/charlesneimog/OScofo/releases/latest) Page.

## Examples

* [Cânticos de Silício](https://charlesneimog.github.io/Canticos-de-Silicio-I/) by Charles K. Neimog;
* [BWV-1013](https://charlesneimog.github.io/pd4web/tests/OScofo) by Bach;

## Goal

The aim of *OScofo* is to provide a straightforward and accessible tool for real-time score following. By keeping the software lightweight, it can run seamlessly on the web through the [pd4web](https://charlesneimog.github.io/pd4web/) platform, thanks to the ability to use PureData directly in web browsers. With _pd4web_ and _OScofo_ will be possible to use the software in rehearsals with just a single click, eliminating the need for external libraries, compatibility issues, or complex installations -- ultimately facilitating the sharing and performance of contemporary music.

## Collaboration and Contribution

I invite composers, researchers and developers to contribute to the *OScofo* project. Not just with code, but with theory, math, etc. I am trying to make OScofo acessible via a Python implementation, to test it should be easy. By sharing the source code, I am trying to provide access to the theories and mathematical formulas that drive the software, all this come from the amazing research work of Arshia Cont and Philippe Cuvillier at IRCAM. 

## Technical Foundations

*OScofo* uses several concepts developed by many researches (with focus on the research of Cont and Cuvillier).

* **Pitch Comparison**: Utilizes the Kullback-Leibler (KL) Divergence method for pitch comparison as presented by Christopher Raphael (2006), Arshia Cont in 2008 and 2010.
* **Rhythm Synchronization**: Integrates theories of rhythm synchronization developed by Edward Large and Mari Riess Jones (1999) and Edward Large and Caroline Palmer (2002), as presented for Cont (2010).
* **Forward Algorithm**: For now, *OScofo* uses the equation presented by Arshia Cont (2010) and developed by Yann Guédon (2005).
* **Score Language**: Based on the `scofo` (by Miller Puckette) and `antescofo~` (by Arshia Cont, Philippe Cuvillier, and others) language.

## Building

### Requirements

* On Windows, you need `mingw64`.

#### Optional
* treesitter (`npm install tree-sitter`) (If you want to change/update score syntax).
* pybind11 (optional): To build Python package.
* PureData (optional): To build the Pd Object.

#### Building Options

* `BUILD_ALL`: Build all OScofo modules (Python, Pd, Max).
* `BUILD_ALL_OBJECTS`: Build Pd and Max Objects.
* `BUILD_PY_MODULE`: Build or not the OScofo python module.
* `BUILD_PD_OBJECT`: Build or not the Pd Object.
* `BUILD_MAX_OBJECT`: Build or not the Max Object.

* `PDLIBDIR`: Where the Pd object will be installed.

#### Building Steps

``` bash
git clone https://github.com/charlesneimog/OScofo --recursive
cmake . -B build -DBUILD_ALL_OBJECTS=ON -G Ninja 
cmake --build build
```

To install use `cmake --install build`.

