<meta charset="UTF-8">

Bilibili av-bv converter
===

A minimalist tool for conversion between Bilibili AV and BV identifiers. Works on Windows.

Build from source
---

The source code can be compiled with both Microsoft Visual C++ (14.0 and above) and MinGW.

For Microsoft Visual C++, pass `/source-charset:UTF-8` to compiler options and "Use Unicode Character Set" must be set.

For MinGW, pass `-DUNICODE -mwindows -municode` flags to `gcc`.

Reference
---

* [Algorithm](https://www.zhihu.com/answer/1099438784) cracked by [mcfx](https://www.zhihu.com/people/-._.-)
