# o.scofo~

**O**pen **SCO**re **FO**llower (o.scofo~) is a PureData object designed for contemporary music applications. This project aims to foster collaboration among researchers and musicians in the field. Here's what you need to know:

# Goal

The goal of `o.scofo~` is to provide a simple, accessible tool for real-time score following. By keeping the software lightweight and user-friendly, it can be easily run on the web using the [pd4web](https://charlesneimog.github.io/pd4web/) platform. So finally we have something that can be run for rehearsals one click distance (without externals, OSs incompatibility, etc).

# Collaboration and Contribution

We invite researchers and developers to contribute to the o.scofo~ project. By sharing the source code, we provide access to the underlying theories and mathematical formulas that drive the software. This transparency is inspired by the amazing tools like IEM, SPARTA, and of course, PureData.

# Technical Foundations

o.scofo~ leverages several concepts developed by many researches:

* Pitch Comparison: Utilizes the Kullback-Leibler (KL) Divergence method for pitch comparison as presented by Arshia Cont in 2008 and 2010.
* Rhythm Synchronization: Integrates theories of rhythm synchronization developed by Edward Large and Mari Riess Jones (1999) and Edward Large and Caroline Palmer (2002).
* Descriptors: Employs descriptors from Willian Brent's timbreIDLib project for analyzing and identifying timbral characteristics.
