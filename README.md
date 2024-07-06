# o.scofo~

**O**pen **SCO**re **FO**llower (o.scofo~) is a PureData object designed for contemporary music applications. This project aims to encourage collaboration among researchers and musicians for contemporary music. Here's what you need to know:

## Goal

The goal of *o.scofo~* is to provide a simple, accessible tool for real-time score following. By keeping the software lightweight, it can be easily run on the web using the [pd4web](https://charlesneimog.github.io/pd4web/) platform, now the we can use PureData on Web Browsers. So finally we have something that can be run for rehearsals one click distance (without externals, OSs incompatibility, etc).

## Collaboration and Contribution

I invite researchers and developers to contribute to the *o.scofo~* project. By sharing the source code, I am trying to provide access to the theories and mathematical formulas that drive the software. This transparency is inspired by the amazing tools like IEM, SPARTA, and of course, PureData. My main aim is artistic, maybe your research can help me and a lot of others composers.

## Technical Foundations

*o.scofo~* uses several concepts developed by many researches:

* **Score Language**: Based on the `scofo` (by Miller Puckette) and `antescofo~` (by Arshia Cont) language.
* **Pitch Comparison**: Utilizes the Kullback-Leibler (KL) Divergence method for pitch comparison as presented by Arshia Cont in 2008 and 2010.
* **Rhythm Synchronization**: Integrates theories of rhythm synchronization developed by Edward Large and Mari Riess Jones (1999) and Edward Large and Caroline Palmer (2002), as presented for Cont (2010).
* **Descriptors**: Employs descriptors from Willian Brent's timbreIDLib project for analyzing and identifying timbral characteristics.
